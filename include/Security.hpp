/*
 * omd_security_status.h
 *
 *  Created on: Jul 24, 2015
 *      Author: felix
 */

#ifndef SECURITY_HPP_
#define SECURITY_HPP_

#include <CircularBuffer.hpp>

#include <OmdMessage.hpp>

namespace meteor {
	namespace core {
		const int SECURITY_MAX = 100000;
		const int PRICE_LEVEL_MAX = 10;

		struct Security {
			meteor::omd::Int32 nominal_price;
			meteor::omd::Int32 last_trade_price;
			CircularBuffer<meteor::omd::Int32, PRICE_LEVEL_MAX> bid_queue;
			CircularBuffer<meteor::omd::Int32, PRICE_LEVEL_MAX> ask_queue;
		}__attribute__ ((aligned(4)));
	}
}

#endif /* SECURITY_HPP_ */
