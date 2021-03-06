/*
 * RS232.h
 *
 *  Created on: Feb 21, 2012
 *      Author: Mike
 */

#ifndef RS232_H_
#define RS232_H_

#define RX_IDEL		0
#define RX_START		1
#define RX_READY		2
#define RX_CRC_ERROR	3
#define RX_TIMEOUT		4

#define RX_FRAME_TIMEOUT	5000 // 500ms, which is based on 100us

#define RS232_BAUDRATE_9600		487
#define RS232_BUF_DEPTH		128

typedef struct RS_BUF_struct RsBufObj;

struct RS_BUF_struct {
	Uint16 Cnt;
	Uint16 Buf[RS232_BUF_DEPTH];
	//function pointer
	void (*push)(RsBufObj *RsBuf, Uint16 InData);
	Uint16 (*pop)(RsBufObj *RsBuf);
};

typedef struct RS232_struct RS232Obj;

//rx and tx are all in words format!
struct RS232_struct {
	RsBufObj TxBuf;
	Uint16 RxBuf[RS232_BUF_DEPTH >> 1];
	Uint16 TxFrameBuf[RS232_BUF_DEPTH >> 1];
	Uint16 TxFrameCnt;
	Uint16 RxCnt;
	Uint16 RxStatus;
	Uint32 TimeStamp;
	//function pointer
	void (*tx)(RS232Obj *Rs232);
	void (*tx_frame_word)(RS232Obj *RS232, Uint16 word);
	void (*rx)(RS232Obj *Rs232);
	void (*rest_Rx)(RS232Obj *Rs232);
	void (*tx_a_Frame)(RS232Obj *RS232);
};

void init_SCI(void);
void init_RS_BUF(RsBufObj *RsBuf);

extern RS232Obj RS232;

typedef union word_union Aword;

struct Aword_Struct {
	Uint16 Lo :8;
	Uint16 Hi :8;
};

union word_union {
	Uint16 all;
	struct Aword_Struct bits;
};

#endif /* RS232_H_ */
