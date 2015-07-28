/*
 * omd_message.h
 *
 *  Created on: Jul 18, 2015
 *      Author: felix
 */

#ifndef OMD_MESSAGE_H_
#define OMD_MESSAGE_H_

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;
typedef short Int16;
typedef int Int32;
typedef long long Int64;

enum MSG_TYPE {
	MSG_TYPE_SEQUENCE_RESET = 100,
	MSG_TYPE_LOGON = 101,
	MSG_TYPE_LOGON_RESPONSE = 102,
	MSG_TYPE_RETRANSMISSION_REQUEST = 201,
	MSG_TYPE_RETRANSMISSION_RESPONSE = 202,
	MSG_TYPE_REFRESH_COMPLETE = 203,
	MSG_TYPE_MARKET_DEFINITION = 10,
	MSG_TYPE_SECURITY_DEFINITION = 11,
	MSG_TYPE_LIQUIDITY_PROVIDER = 13,
	MSG_TYPE_CURRENCY_RATE = 14,
	MSG_TYPE_TRADING_SESSION_STATUS = 20,
	MSG_TYPE_SECURITY_STATUS = 21,
	MSG_TYPE_ADD_ORDER = 30,
	MSG_TYPE_MODIFY_ORDER = 31,
	MSG_TYPE_DELETE_ORDER = 32,
	MSG_TYPE_ADD_ODD_LOT_ORDER = 33,
	MSG_TYPE_DELETE_ODD_LOT_ORDER = 34,
	MSG_TYPE_AGGREATE_ORDER_BOOK_UPDATE = 53,
	MSG_TYPE_BROKER_QUEUE = 54,
	MSG_TYPE_TRADE = 50,
	MSG_TYPE_TRADE_CANCEL = 51,
	MSG_TYPE_TRADE_TICKER = 52,
	MSG_TYPE_CLOSING_PRICE = 62,
	MSG_TYPE_NOMINAL_PRICE = 40,
	MSG_TYPE_INDICATIVE_EQUILIBRIUM_PRICE = 41,
};

struct packet_buffer {
	unsigned char data[1500];
}__attribute__ ((packed));

struct packet_header {
	Uint16 pkt_size;
	Uint8 msg_count;
	// The compiler will automatically add 1-byte filler
	Uint32 seq_num;
	Uint64 send_time;
}__attribute__ ((aligned(4)));

struct message_header {
	Uint16 msg_size;
	Uint16 msg_type;
}__attribute__ ((packed));

struct sequence_reset {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 new_seq_no;
}__attribute__ ((aligned(4)));

struct logon {
	Uint16 msg_size;
	Uint16 msg_type;
	unsigned char username[12];
}__attribute__ ((aligned(4)));

struct logon_response {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint8 session_status;
	// The compiler will automatically add 3-byte filler
}__attribute__ ((aligned(4)));

struct retransmission_request {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint16 channel_id;
	// The compiler will automatically add 2-byte filler
	Uint32 begin_seq_num;
	Uint32 end_seq_num;
}__attribute__ ((aligned(4)));

struct retransmission_response {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint16 channel_id;
	Uint8 retrans_status;
	// The compiler will automatically add 1-byte filler
	Uint32 begin_seq_num;
	Uint32 end_seq_num;
};

struct refresh_complete {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 last_seq_num;
}__attribute__ ((aligned(4)));

////////////////////////////////////////
// OMD Reference Data
////////////////////////////////////////

struct market_definition {
	Uint16 msg_size;
	Uint16 msg_type;
	unsigned char market_code[4];
	unsigned char market_name[25];
	unsigned char currency_code[3];
	Uint32 number_of_securities;
}__attribute__ ((packed));

struct security_definition {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	unsigned char market_code[4];
	unsigned char isin_code[12];
	unsigned char instrument_type[4];
	unsigned char spread_table_code[2];
	unsigned char security_short_name[40];
	unsigned char currency_code[3];
	unsigned char security_code_gccs[60];
	unsigned char security_code_gb[60];
	Uint32 lot_size;
	Int32 previous_closing_price;
	unsigned char filler[1];
	unsigned char short_sell_flag[1];
	unsigned char filler2[1];
	unsigned char ccass_flag[1];
	unsigned char dummy_security_flag[1];
	unsigned char test_security_flag[1];
	unsigned char stamp_duty_flag[1];
	unsigned char filler3[1];
	Uint32 listing_date;
	Uint32 delisting_date;
	unsigned char free_text[38];
	unsigned char efn_flag[1];
	Uint32 accrued_interest;
	Uint32 coupon_rate;
	Uint32 conversion_ratio;
	Int32 strike_price;
	Uint32 maturity_date;
	unsigned char call_pull_flag[1];
	unsigned char style[1];
	Uint16 no_underlying_securities;
}__attribute__ ((packed));

struct security_definition_underlying_security {
	Uint32 underlying_security_code;
	Uint32 underlying_security_weight;
}__attribute__ ((packed));

struct liquidity_provider {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint16 no_liquidity_provider;
}__attribute__ ((packed));

struct liquidity_provider_liquidity_provider {
	Uint16 lp_broker_number;
}__attribute__ ((packed));

struct currency_rate {
	Uint16 msg_size;
	Uint16 msg_type;
	unsigned char currency_code[3];
	// The compiler will automatically add 1-byte filler
	Uint16 currency_factor;
	// The compiler will automatically add 2-byte filler
	Uint32 currency_rate;
}__attribute__ ((aligned(4)));

////////////////////////////////////////
// OMD Status Data
////////////////////////////////////////

struct trading_session_status {
	Uint16 msg_size;
	Uint16 msg_type;
	unsigned char market_code[4];
	Uint8 trading_session_id;
	Uint8 trading_session_sub_id;
	Uint8 trading_ses_status;
	unsigned char trading_ses_control_flag[1];
	// The compiler will automatically add 4-byte filler
	Uint64 start_date_time;
	Uint64 end_date_time;
}__attribute__ ((aligned(4)));

struct security_status {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint8 security_trading_status;
	// The compiler will automatically add 3-byte filler
}__attribute__ ((aligned(4)));

////////////////////////////////////////
// OMD Order Book Data
////////////////////////////////////////

struct add_order {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint64 order_id;
	Int32 price;
	Uint32 quantity;
	Uint16 side;
	unsigned char order_type[1];
	// The compiler will automatically add 1-byte filler
	Int32 order_book_position;
}__attribute__ ((aligned(4)));

struct modify_order {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint64 order_id;
	Uint32 quantity;
	Uint16 side;
	unsigned char filler[2];
	Int32 order_book_position;
}__attribute__ ((packed));

struct delete_order {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint64 order_id;
	Uint16 side;
	unsigned char filler[2];
}__attribute__ ((packed));

struct add_odd_lot_order {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint64 order_id;
	Int32 price;
	Uint32 quantity;
	Uint16 broker_id;
	Uint16 side;
}__attribute__ ((packed));

struct delete_odd_lot_order {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint64 order_id;
	Uint16 broker_id;
	Uint16 side;
}__attribute__ ((packed));

struct aggregate_order_book_update {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	unsigned char filler[3];
	Uint8 no_entries;
}__attribute__ ((aligned(4)));

struct aggregate_order_book_update_entry {
	Uint64 aggregate_quantity;
	Int32 price;
	Uint32 number_of_orders;
	Uint16 side;
	Uint8 price_level;
	Uint8 update_action;
	unsigned char filler[4];
}__attribute__ ((aligned(4)));

struct broker_queue {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint8 item_count;
	Uint16 side;
	unsigned char bq_more_flag[1];
}__attribute__ ((packed));

struct broker_queue_item {
	Uint16 item;
	unsigned char type[1];
}__attribute__ ((aligned(4)));

////////////////////////////////////////
// OMD Trade and Price Data
////////////////////////////////////////

struct trade {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint32 trade_id;
	Int32 price;
	Uint32 quantity;
	Int16 trd_type;
	// The compiler will automatically add 2-byte filler
	Uint64 trade_time;
}__attribute__ ((aligned(4)));

struct trade_cancel {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint32 trade_id;
}__attribute__ ((aligned(4)));

struct trade_ticker {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Uint32 ticker_id;
	Int32 price;
	Uint64 aggregate_quantity;
	Uint64 trade_time;
	Int16 trd_type;
	unsigned char trd_cancel_flag[1];
	unsigned char filler[1];
}__attribute__ ((packed));

struct closing_price {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Int32 closing_price;
	Uint32 number_of_trades;
}__attribute__ ((aligned(4)));

struct nominal_price {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Int32 nominal_price;
}__attribute__ ((aligned(4)));

struct indicative_equilibrium_price {
	Uint16 msg_size;
	Uint16 msg_type;
	Uint32 security_code;
	Int32 price;
	Uint64 aggregate_quantity;
}__attribute__ ((packed));

#endif /* OMD_MESSAGE_H_ */
