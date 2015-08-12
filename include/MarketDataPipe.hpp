/*
 * MarketDataStore.h
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#ifndef MARKETDATAPIPE_HPP_
#define MARKETDATAPIPE_HPP_

#include <OmdMessage.hpp>

#include <boost/asio.hpp>
#include <boost/lockfree/spsc_queue.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace meteor {
	namespace core {
		struct market_data_message {
			meteor::omd::packet_buffer buffer;
			boost::asio::ip::udp::endpoint senderEndpoint;
		}__attribute((aligned(4)));

		class MarketDataPipe {
		public:
			boost::lockfree::spsc_queue<market_data_message, boost::lockfree::capacity<10000>> queue;

			// No encapsulation
			// Let the programmers knows what they are doing
			boost::mutex queueLock;
			boost::condition_variable queueNotEmpty;
		};
	}
}

#endif /* MARKETDATAPIPE_HPP_ */
