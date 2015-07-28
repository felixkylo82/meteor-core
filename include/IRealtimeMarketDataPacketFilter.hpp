/*
 * IRealtimeMarketDataMessageFilter.hpp
 *
 *  Created on: Jul 26, 2015
 *      Author: felix
 */

#ifndef IREALTIMEMARKETDATPACKETFILTER_HPP_
#define IREALTIMEMARKETDATPACKETFILTER_HPP_

namespace meteor {
	namespace core {
		struct market_data_message;

		class IRealtimeMarketDataPacketFilter {
		public:
			virtual bool filter(const market_data_message&) const = 0;
		};
	}
}

#endif /* IREALTIMEMARKETDATAPACKETFILTER_HPP_ */
