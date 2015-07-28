/*
 * context.h
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <boost/shared_ptr.hpp>

namespace meteor {
	namespace core {
		class MarketDataPipe;

		class MarketDataDispatcherThread;
		class TradeDecisionThread;
	}

	class Context {
	public:
		static const boost::shared_ptr<meteor::core::MarketDataPipe> mdPipe;

		static const boost::shared_ptr<meteor::core::MarketDataDispatcherThread> mddThread;
		static const boost::shared_ptr<meteor::core::TradeDecisionThread> tdThread;
	};
}

#endif /* CONTEXT_HPP_ */
