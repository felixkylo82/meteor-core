/*
 * OmdPacket.hpp
 *
 *  Created on: Jul 19, 2015
 *      Author: felix
 */

#ifndef PACKETREADER_HPP_
#define PACKETREADER_HPP_

#include <OmdMessage.hpp>

namespace meteor {
	namespace core {
		class PacketReader {
		private:
			const meteor::omd::packet_buffer* buffer;
			mutable unsigned short current;

		public:
			PacketReader();
			virtual ~PacketReader();

			void reopen(const meteor::omd::packet_buffer& buffer);
			const unsigned char *getMessage(meteor::omd::Uint16& msgSize, meteor::omd::Uint16& msgType) const;

		private:
			inline meteor::omd::Uint16 getPktSize() const;
			inline meteor::omd::Uint8 getMsgCount() const;
			inline meteor::omd::Uint32 getSeqNum() const;
			inline meteor::omd::Uint64 getSendTime() const;
		};

	} /* namespace core */
} /* namespace meteor */

#endif /* PACKETREADER_HPP_ */
