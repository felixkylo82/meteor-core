/*
 * ITradeDecisionThread.h
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#ifndef TRADEDECISIONTHREAD_HPP_
#define TRADEDECISIONTHREAD_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/atomic.hpp>
#include <Security.hpp>

namespace meteor {
	namespace core {
		struct market_data_message;

		class MarketDataPipe;
		class PacketReader;
		class IRealtimeMarketDataPacketFilter;
		class IRealtimeMarketDataMessageFilter;
		class IAlgo;
		class ParamStore;

		class TradeDecisionThread {
		private:
			class MessageProcessor {
			private:
				const boost::shared_ptr<TradeDecisionThread> tdThread;
				const boost::shared_ptr<PacketReader> packetReader;
				const boost::shared_ptr<ParamStore> paramStore;
				const boost::shared_ptr<IAlgo> algo;
				Security* const securities;

			public:
				MessageProcessor(const boost::shared_ptr<TradeDecisionThread>& tdThread);

				inline void operator()(const market_data_message& buffer) const;

			private:
				inline void doProcess(meteor::omd::Uint16 msgType, const unsigned char* omd_message) const;
			};

			unsigned char filler[1] __attribute__ ((aligned(64)));
			// unused security is only stored in main memory
			Security securities[SECURITY_MAX];

			const boost::shared_ptr<PacketReader> packetReader;
			const boost::shared_ptr<MarketDataPipe> mdPipe;
			const boost::shared_ptr<IRealtimeMarketDataPacketFilter> packetFilter;
			const boost::shared_ptr<IRealtimeMarketDataMessageFilter> messageFilter;
			const boost::shared_ptr<ParamStore> paramStore;
			const boost::shared_ptr<IAlgo> algo;
			boost::atomic<bool> isRunning;

		public:
			static void run(boost::shared_ptr<TradeDecisionThread> me);

			TradeDecisionThread(const boost::shared_ptr<MarketDataPipe>& mdPipe, const boost::shared_ptr<IRealtimeMarketDataPacketFilter>& packetFilter,
					const boost::shared_ptr<IRealtimeMarketDataMessageFilter>& messageFilter, const boost::shared_ptr<IAlgo>& algo,
					const boost::shared_ptr<ParamStore>& paramStore);
			virtual ~TradeDecisionThread();

			void stop();
		}__attribute__ ((aligned(64)));
	}
}

#endif /* TRADEDECISIONTHREAD_HPP_ */
