/*
 * IRealtimeMarketDataMessageFilter.hpp
 *
 *  Created on: Jul 26, 2015
 *      Author: felix
 */

#ifndef IREALTIMEMARKETDATAMESSAGEFILTER_HPP_
#define IREALTIMEMARKETDATAMESSAGEFILTER_HPP_

#include <OmdMessage.hpp>

namespace meteor {
	namespace core {
		struct market_data_message;

		class IRealtimeMarketDataMessageFilter {
		public:
			virtual bool filter(meteor::omd::Uint16 msgType) const = 0;
		};
	}
}

#endif /* IREALTIMEMARKETDATAMESSAGEFILTER_HPP_ */
