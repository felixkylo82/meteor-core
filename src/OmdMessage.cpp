/*
 * omd_message.c
 *
 *  Created on: Jul 19, 2015
 *      Author: felix
 */

#include <omd_message.h>

#include <assert.h>
#include <stdio.h>

namespace meteor {
	namespace omd {
		void verify_message_size() {
			printf("start verifying OMD message size\r\n");

			assert(sizeof(struct packet_header) == 16);
			assert(sizeof(struct sequence_reset) == 8);
			assert(sizeof(struct logon) == 16);
			assert(sizeof(struct logon_response) == 8);
			assert(sizeof(struct retransmission_request) == 16);
			assert(sizeof(struct retransmission_response) == 16);
			assert(sizeof(struct refresh_complete) == 8);

			// OMD Reference Data
			assert(sizeof(struct market_definition) == 40);
			assert(sizeof(struct security_definition) == 280);
			assert(sizeof(struct security_definition_underlying_security) == 8);
			assert(sizeof(struct liquidity_provider) == 10);
			assert(sizeof(struct liquidity_provider_liquidity_provider) == 2);
			assert(sizeof(struct currency_rate) == 16);

			// OMD Status Data
			assert(sizeof(struct trading_session_status) == 32);
			assert(sizeof(struct security_status) == 12);

			// OMD Order Book Data
			assert(sizeof(struct add_order) == 32);
			assert(sizeof(struct modify_order) == 28);
			assert(sizeof(struct delete_order) == 20);
			assert(sizeof(struct add_odd_lot_order) == 28);
			assert(sizeof(struct delete_odd_lot_order) == 20);
			assert(sizeof(struct aggregate_order_book_update) == 12);
			assert(sizeof(struct aggregate_order_book_update_entry) == 24);
			assert(sizeof(struct broker_queue) == 12);
			assert(sizeof(struct broker_queue_item) == 4);

			// OMD Trade and Price Data
			assert(sizeof(struct trade) == 32);
			assert(sizeof(struct trade_cancel) == 12);
			assert(sizeof(struct trade_ticker) == 36);
			assert(sizeof(struct closing_price) == 16);
			assert(sizeof(struct nominal_price) == 12);
			assert(sizeof(struct indicative_equilibrium_price) == 20);

			printf("end verifying OMD message size\r\n");
		}
	}
}
