/*
 * OmdMessage.hpp
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#ifndef OMDMESSAGE_HPP_
#define OMDMESSAGE_HPP_

#include <boost/asio.hpp>

namespace meteor {
	namespace omd {
		extern "C" {
#include "omd_message.h"
		}

		////////////////////////////////////////
		// Helper functions
		////////////////////////////////////////

		void verify_message_size();
	}
}

#endif /* OMDMESSAGE_HPP_ */
