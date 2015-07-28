/*
 * MarketDataDispatcherThread.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#include <MarketDataDispatcherThread.hpp>

#include <Context.hpp>

#include <MarketDataPipe.hpp>

#include <boost/thread/locks.hpp>

using namespace boost;

namespace meteor {
	namespace core {
		void MarketDataDispatcherThread::run(boost::shared_ptr<MarketDataDispatcherThread> me) {
			// Full memory fence should have been enforced automatically during the thread starts
			const shared_ptr<MarketDataPipe> mdPipe = me->mdPipe;

			const char* const listenAddress = me->listenAddress;
			const short multicastPort = me->multicastPort;
			const char* const * const multicastAddresses = me->multicastAddresses;
			const unsigned int multicastCount = me->multicastCount;

			//lockfree::spsc_queue& queue = mdPipe->queue;

			printf("start startup MarketDataDispatcherThread\r\n");

			// Create the socket so that multiple may be bound to the same address.
			asio::ip::udp::endpoint listen_endpoint(asio::ip::address::from_string(listenAddress), multicastPort);
			asio::io_service io_service;
			asio::ip::udp::socket* _socket = new asio::ip::udp::socket(io_service);
			me->socket.store(_socket, memory_order::memory_order_release);
			_socket->open(listen_endpoint.protocol());
			_socket->set_option(asio::ip::udp::socket::reuse_address(true));
			_socket->bind(listen_endpoint);

			// Join the multicast groups.
			for (unsigned int i = 0; i < multicastCount; ++i) {
				_socket->set_option(asio::ip::multicast::join_group(asio::ip::address::from_string(multicastAddresses[i])));
			}

			printf("end startup MarketDataDispatcherThread\r\n");

			system::error_code error;
			while ((_socket = me->socket.load(memory_order::memory_order_consume))) {
				market_data_message message;
				_socket->receive_from(asio::buffer(message.buffer.data, sizeof(message.buffer.data)), message.senderEndpoint, 0, error);

				if (error) {
					fprintf(stderr, "%d | %s\r\n", error.value(), error.message().data());
					continue;
				}

				{
					lock_guard<mutex>(mdPipe->queueLock);
					mdPipe->queue.push(message);
					mdPipe->queueNotEmpty.notify_one();
				}
			}
		}

		MarketDataDispatcherThread::MarketDataDispatcherThread(const shared_ptr<MarketDataPipe>& mdPipe, const char* listenAddress, short multicastPort,
				const char* const * multicastAddresses, unsigned int multicastCount) :
				mdPipe(mdPipe), listenAddress(listenAddress), multicastPort(multicastPort), multicastAddresses(multicastAddresses), multicastCount(
						multicastCount) {
			socket.store(0, memory_order::memory_order_release);
		}

		MarketDataDispatcherThread::~MarketDataDispatcherThread() {
		}

		void MarketDataDispatcherThread::stop() {
			printf("start shutdown MarketDataDispatcherThread\r\n");

			asio::ip::udp::socket* _socket = socket.exchange(0);

			system::error_code error;
			if (_socket) {
				_socket->shutdown(asio::socket_base::shutdown_both, error);
				delete _socket;

				if (error)
					fprintf(stderr, "%d | %s\r\n", error.value(), error.message().data());
			}

			printf("end shutdown MarketDataDispatcherThread\r\n");
		}
	} /* namespace core */
} /* namespace meteor */
