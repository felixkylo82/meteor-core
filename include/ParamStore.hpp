/*
 * ParamStore.hpp
 *
 *  Created on: Jul 27, 2015
 *      Author: felix
 */

#ifndef PARAMSTORE_HPP_
#define PARAMSTORE_HPP_

#include <IAlgo.hpp>
#include <IParam.hpp>
#include <ConcurrentLinkedList.hpp>

#include <OmdMessage.hpp>

namespace meteor {
	namespace core {
		class ParamStore {
		public:
			static const int MAX_SECURITY_CODE = 100000;
			static const int MAX_ALGO_COUNT = 5;

		private:
			ConcurrentLinkedList<IParam> data[MAX_SECURITY_CODE][MAX_ALGO_COUNT];
			const unsigned int* const algoId2IndexMap;

		public:
			ParamStore(const unsigned int algoId2IndexMap[]);
			virtual ~ParamStore();

			ConcurrentLinkedList<IParam>& getParamList(meteor::omd::Uint32 securityCode, ALGO_ID algoId);
		};
	} /* namespace core */
} /* namespace meteor */

#endif /* PARAMSTORE_HPP_ */
