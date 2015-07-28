/*
 * IAlgo.hpp
 *
 *  Created on: Jul 27, 2015
 *      Author: felix
 */

#ifndef IALGO_HPP_
#define IALGO_HPP_

namespace meteor {
	namespace core {
		enum ALGO_ID {
			ALGO_ID_MOCK,
		};

		class IAlgo {
		public:
			virtual ALGO_ID getId() const = 0;
		};
	}
}

#endif /* IALGO_HPP_ */
