/*
 * TradeDecisionThread.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#include <TradeDecisionThread.hpp>

#include <Context.hpp>

#include <MarketDataPipe.hpp>
#include <IRealtimeMarketDataPacketFilter.hpp>
#include <IRealtimeMarketDataMessageFilter.hpp>
#include <IAlgo.hpp>
#include <IParamStore.hpp>
#include <IParam.hpp>
#include <ConcurrentLinkedList.hpp>

#include <boost/thread/locks.hpp>
#include <PacketReader.hpp>

#include <cstring>

using namespace boost;

using namespace meteor;

namespace meteor {
	namespace core {
		TradeDecisionThread::MessageProcessor::MessageProcessor(const boost::shared_ptr<TradeDecisionThread>& tdThread) :
				tdThread(tdThread), packetReader(tdThread->packetReader), securities(tdThread->securities), algo(tdThread->algo), paramStore(
						tdThread->paramStore) {
		}

		void TradeDecisionThread::MessageProcessor::operator()(const market_data_message& message) const {
			if (tdThread->packetFilter->filter(message))
				return;

			packetReader->reopen(message.buffer);

			const unsigned char* omd_message;
			omd::Uint16 msgSize;
			omd::Uint16 msgType;
			while ((omd_message = packetReader->getMessage(msgSize, msgType))) {
				if (tdThread->messageFilter->filter(msgType))
					continue;

				doProcess(msgType, omd_message);
			}
		}

		void TradeDecisionThread::MessageProcessor::doProcess(omd::Uint16 msgType, const unsigned char* omd_message) const {
			omd::Uint32 securityCode = 0U;
			switch (msgType) {
			case omd::MSG_TYPE_NOMINAL_PRICE: {
				omd::nominal_price* nominal_price = (omd::nominal_price*) omd_message;
				securityCode = nominal_price->security_code;
				securities[securityCode].nominal_price = nominal_price->nominal_price;
				break;
			}
			case omd::MSG_TYPE_AGGREATE_ORDER_BOOK_UPDATE: {
				omd::aggregate_order_book_update* aggregate_order_book_update = (omd::aggregate_order_book_update*) omd_message;
				securityCode = aggregate_order_book_update->security_code;
				break;
			}
			case omd::MSG_TYPE_TRADE: {
				omd::trade* trade = (omd::trade*) omd_message;
				securityCode = trade->security_code;
				securities[securityCode].last_trade_price = trade->price;
				break;
			}
			case omd::MSG_TYPE_TRADE_CANCEL: {
				omd::trade_cancel* trade_cancel = (omd::trade_cancel*) omd_message;
				securityCode = trade_cancel->security_code;
				break;
			}
			default:
				break;
			}

			ConcurrentLinkedList<IParam>& paramList = paramStore->getParamList(securityCode, algo->getId());
		}

		void TradeDecisionThread::run(boost::shared_ptr<TradeDecisionThread> me) {
			// Full memory fence should have been enforced automatically during the thread starts
			shared_ptr<MarketDataPipe> mdPipe = me->mdPipe;

			MessageProcessor processor(me);
			while (me->isRunning.load(memory_order::memory_order_consume)) {
				{
					unique_lock<boost::mutex> lock(mdPipe->queueLock);
					if (!mdPipe->queue.read_available()) {
						mdPipe->queueNotEmpty.wait(lock);
					}
					if (!mdPipe->queue.read_available()) {
						continue;
					}
				}
				mdPipe->queue.consume_all(processor);
			}
		}

		TradeDecisionThread::TradeDecisionThread(const boost::shared_ptr<MarketDataPipe>& mdPipe,
				const boost::shared_ptr<IRealtimeMarketDataPacketFilter>& packetFilter,
				const boost::shared_ptr<IRealtimeMarketDataMessageFilter>& messageFilter, const boost::shared_ptr<IAlgo>& algo,
				const boost::shared_ptr<IParamStore>& paramStore) :
				packetReader(new PacketReader()), mdPipe(mdPipe), packetFilter(packetFilter), messageFilter(messageFilter), algo(algo), paramStore(paramStore) {
			memset(securities, 0, SECURITY_MAX * sizeof(Security));
			isRunning.store(true, memory_order::memory_order_release);
		}

		TradeDecisionThread::~TradeDecisionThread() {
		}

		void TradeDecisionThread::stop() {
			isRunning.store(false, memory_order::memory_order_release);
			{
				lock_guard<mutex>(mdPipe->queueLock);
				mdPipe->queueNotEmpty.notify_one();
			}
		}
	} /* namespace core */
} /* namespace meteor */
