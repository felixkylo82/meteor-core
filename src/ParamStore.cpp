/*
 * ParamStore.cpp
 *
 *  Created on: Jul 27, 2015
 *      Author: felix
 */

#include <ParamStore.hpp>

using namespace meteor;

namespace meteor {
	namespace core {
		ParamStore::ParamStore(const unsigned int algoId2IndexMap[]) : algoId2IndexMap(algoId2IndexMap) {
			// TODO Auto-generated constructor stub

		}

		ParamStore::~ParamStore() {
			// TODO Auto-generated destructor stub
		}

		ConcurrentLinkedList<IParam>& ParamStore::getParamList(omd::Uint32 securityCode, ALGO_ID algoId) {
			return data[securityCode][algoId2IndexMap[algoId]];
		}
	} /* namespace core */
} /* namespace meteor */
