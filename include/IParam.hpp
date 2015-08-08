/*
 * IParam.hpp
 *
 *  Created on: Jul 27, 2015
 *      Author: felix
 */

#ifndef IPARAM_HPP_
#define IPARAM_HPP_

#include <IAlgo.hpp>

namespace meteor {
	namespace core {
		class IParam {
		public:
			IParam() {}
			virtual ~IParam() {}

			virtual ALGO_ID getAlgoId() const = 0;
		};
	}
}

#endif /* IPARAM_HPP_ */
