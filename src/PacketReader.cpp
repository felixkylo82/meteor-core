/*
 * OmdPacket.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: felix
 */

#include <PacketReader.hpp>

using namespace meteor;

namespace meteor {
	namespace core {
		PacketReader::PacketReader() :
				buffer(0), current(0) {
		}

		PacketReader::~PacketReader() {
		}

		void PacketReader::reopen(const omd::packet_buffer& buffer) {
			this->buffer = &buffer;
			current = 0;
		}

		const unsigned char *PacketReader::getMessage(omd::Uint16& msgSize, omd::Uint16& msgType) const {
			if (current >= getPktSize())
				return 0;

			const unsigned char* message = buffer->data + current;
			const omd::message_header* header = (const omd::message_header*) message;

			msgSize = header->msg_size;
			msgType = header->msg_type;

			current += msgSize;

			return message;
		}

		omd::Uint16 PacketReader::getPktSize() const {
			return ((omd::packet_header* const ) buffer->data)->pkt_size;
		}

		omd::Uint8 PacketReader::getMsgCount() const {
			return ((omd::packet_header* const ) buffer->data)->msg_count;
		}

		omd::Uint32 PacketReader::getSeqNum() const {
			return ((omd::packet_header* const ) buffer->data)->seq_num;
		}

		omd::Uint64 PacketReader::getSendTime() const {
			return ((omd::packet_header* const ) buffer->data)->send_time;
		}
	} /* namespace core */
} /* namespace meteor */
