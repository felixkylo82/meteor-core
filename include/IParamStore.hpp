/*
 * IParamStore.hpp
 *
 *  Created on: Jul 27, 2015
 *      Author: felix
 */

#ifndef IPARAMSTORE_HPP_
#define IPARAMSTORE_HPP_

#include <IAlgo.hpp>
#include <ConcurrentLinkedList.hpp>

#include <OmdMessage.hpp>

namespace meteor {
	namespace core {
		class IParam;

		class IParamStore {
		public:
			virtual ConcurrentLinkedList<IParam>& getParamList(meteor::omd::Uint32 securityCode, ALGO_ID algoId) = 0;
		};
	}
}

#endif /* IPARAMSTORE_HPP_ */
