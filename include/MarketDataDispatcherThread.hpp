/*
 * MarketDataDispatcherThread.h
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#ifndef MARKETDATADISPATCHERTHREAD_HPP_
#define MARKETDATADISPATCHERTHREAD_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/atomic.hpp>

namespace meteor {
	namespace core {
		class MarketDataPipe;

		class MarketDataDispatcherThread {
		private:
			const boost::shared_ptr<MarketDataPipe> mdPipe;

			const char* const listenAddress;
			const short multicastPort;
			const char* const * const multicastAddresses;
			const unsigned int multicastCount;
			boost::atomic<boost::asio::ip::udp::socket*> socket;

		public:
			static void run(boost::shared_ptr<MarketDataDispatcherThread> me);

			MarketDataDispatcherThread(const boost::shared_ptr<MarketDataPipe>& mdPipe, const char* listenAddress, short multicastPort,
					const char* const * multicastAddresses, unsigned int multicastCount);
			virtual ~MarketDataDispatcherThread();

			void stop();
		};
	}
}

#endif /* MARKETDATADISPATCHERTHREAD_HPP_ */
