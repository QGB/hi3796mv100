/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology	5th	Rd.
 * Science-based Industrial	Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2006, Ralink Technology, Inc.
 *
 * All rights reserved.	Ralink's source	code is	an unpublished work	and	the
 * use of a	copyright notice does not imply	otherwise. This	source code
 * contains	confidential trade secret material of Ralink Tech. Any attemp
 * or participation	in deciphering,	decoding, reverse engineering or in	any
 * way altering	the	source code	is stricitly prohibited, unless	the	prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:
	wsc.h

	Abstract:

	Revision History:
	Who			When			What
	--------	----------		----------------------------------------------
	Name		Date			Modification logs
	Paul Lin	06-08-08		Initial
*/

#ifndef	__WSC_H__
#define	__WSC_H__

/* WSC OUI SMI */
#define WSC_OUI				0x0050f204
#define	WSC_SMI				0x00372A
#define	WSC_VENDOR_TYPE		0x00000001

/* EAP code */
#define	EAP_CODE_REQ		0x01
#define	EAP_CODE_RSP		0x02
#define	EAP_CODE_FAIL		0x04
#define EAP_TYPE_ID			0x01
#define EAP_TYPE_NOTIFY		0x02
#define	EAP_TYPE_WSC		0xfe

#ifdef CON_WPS
typedef struct GNU_PACKED _WSC_UPNP_CTRL_WSC_BAND_STOP {
	char ifName[IFNAMSIZ];
	CHAR is2gBand;
	CHAR isApCli;
	INT status;
} WSC_UPNP_CTRL_WSC_BAND_STOP, *PWSC_UPNP_CTRL_WSC_BAND_STOP;
#endif /* CON_WPS */

/* structure to store Simple Config Attributes Info */
typedef struct GNU_PACKED _WSC_LV_INFO {
	USHORT ValueLen;
	UCHAR Value[512];
} WSC_LV_INFO;

typedef struct GNU_PACKED _WSC_IE_HEADER {
	UCHAR elemId;
	UCHAR length;
	UCHAR oui[4];
} WSC_IE_HEADER;

/* WSC IE structure */
typedef struct GNU_PACKED _WSC_IE {
	USHORT Type;
	USHORT Length;
	UCHAR Data[1];		/* variable length data */
} WSC_IE, *PWSC_IE;

/* WSC fixed information within EAP */
typedef struct GNU_PACKED _WSC_FRAME {
	UCHAR SMI[3];
	UINT VendorType;
	UCHAR OpCode;
	UCHAR Flags;
} WSC_FRAME, *PWSC_FRAME;

/* EAP frame format */
typedef struct GNU_PACKED _EAP_FRAME {
	UCHAR Code;		/* 1 = Request, 2 = Response */
	UCHAR Id;
	USHORT Length;
	UCHAR Type;		/* 1 = Identity, 0xfe = reserved, used by WSC */
} EAP_FRAME, *PEAP_FRAME;

static inline BOOLEAN WscCheckWSCHeader(UCHAR *pData)
{
	WSC_FRAME *pWsc = (WSC_FRAME *) pData;

	/* Verify SMI first */
	if (((pWsc->SMI[0] * 256 + pWsc->SMI[1]) * 256 + pWsc->SMI[2]) != WSC_SMI)
		return FALSE;	/* Wrong WSC SMI Vendor ID, Update WSC status */

	/* Verify Vendor Type */
	if (cpu2be32(get_unaligned32(&pWsc->VendorType)) != WSC_VENDOR_TYPE)
		return FALSE;	/* Wrong WSC Vendor Type, Update WSC status */

	return TRUE;
}

#ifdef WSC_INCLUDED

#ifdef IWSC_SUPPORT
/*
	IP Address Configuration Methods
*/
#define IWSC_IPV4_ASSIGNMENT					0x0001
#define IWSC_DHCP_IPV4							0x0002
#define IWSC_STATIC_IPV4						0x0004
#define IWSC_LINK_LOCAL_IPV4					0x0008
#define IWSC_NFC_IPV4_ASSIGNMENT				0x0010
#define IWSC_NFC_LINK_LOCAL_IPV4				0x0020
#define IWSC_IPV6_DEVICE_UNIQUE					0x0040

#define IWSC_DEFAULT_REG_IPV4_ADDR				0x0a000001
#define IWSC_DEFAULT_IPV4_SUBMASK				0xFF000000
#define IWSC_DEFAULT_IPV4_RANGE					0xFFFFFFC0
#define IWSC_IPV4_RANGE0						0xFFFFFFC0
#define IWSC_IPV4_RANGE1						0xFFFFF03F
#define IWSC_IPV4_RANGE2						0xFFFC0FFF
#define IWSC_IPV4_RANGE3						0xFF03FFFF

#define IWSC_MAX_IP_DEV_COUNT					62
#endif /* IWSC_SUPPORT */

/* WSC HDR PSH BTN FUNC */
/* WSC hardware push button function 0811 */
#define WSC_HDR_BTN_CHECK_PERIOD	MLME_TASK_EXEC_INTV	/* unit: ms, check pin every 100ms */
#define WSC_HDR_BTN_PRESS_TIME		2000	/* unit: ms, press button for 2s */
#define WSC_HDR_BTN_CONT_TIMES		(WSC_HDR_BTN_PRESS_TIME/WSC_HDR_BTN_CHECK_PERIOD)
#define WSC_HDR_BTN_GPIO_0			((UINT32)0x00000001)	/* bit 0 for RT2860/RT2870 */
#define WSC_HDR_BTN_GPIO_3			((UINT32)0x00000008)	/* bit 3 for RT2860/RT2870 */

/* bit7: WPS PBC (0:off, 1:on) */
#define WSC_HDR_BTN_MR_HDR_SUPPORT_SET(__pAd, __FlgIsSup)	\
		((__pAd)->WscHdrPshBtnFlag = __FlgIsSup)

/* check if hardware push button is supported */
#define WSC_HDR_BTN_MR_IS_HDR_SUPPORT(__pAd)				\
		((__pAd)->WscHdrPshBtnFlag)

/* run hardware push button handler */
#define WSC_HDR_BTN_MR_HANDLE(__pAd)						\
	do {                                                    \
		if ((__pAd)->WscHdrPshBtnFlag)                      \
			WSC_HDR_BTN_CheckHandler(__pAd);                \
	} while (0)

/* bit3: WPS PBC function is controlled through GPIO[3] */
/* currently only for RT2860 & RT2870 */
#define WSC_HDR_BTN_MR_PRESS_FLG_GET(__pAd, __FlgIsPressed)				\
	{                                                                   \
		UINT32 __gpio_value, mask;	                                    \
		RTMP_IO_READ32(__pAd, GPIO_CTRL_CFG, (&__gpio_value));			\
		if (RTMP_TEST_MORE_FLAG(__pAd, fRTMP_ADAPTER_WSC_PBC_PIN0))		\
			mask = WSC_HDR_BTN_GPIO_0;                                  \
		else                                                            \
			mask = WSC_HDR_BTN_GPIO_3;                                  \
		if (__gpio_value & mask)                                        \
			__FlgIsPressed = 0;	                                        \
		else                                                            \
			__FlgIsPressed = 1;	                                        \
	}
/* WSC HDR PSH BTN FUNC */

#define WSC_TIMER_INIT(_pAd, _pData, _time_var, _time_flg, _time_fn) \
	do { \
		RTMPInitTimer((_pAd), (_time_var), GET_TIMER_FUNCTION(_time_fn), (_pData), FALSE); \
		(_time_flg) = FALSE; \
	} while (0)

/*Messages for the WSC state machine, */
#define	WSC_MACHINE_BASE		34
#define	WSC_EAPOL_PACKET_MSG	34
#define	WSC_EAPOL_START_MSG		35
#define	WSC_EAPOL_UPNP_MSG		36

#define	MAX_WSC_MSG			    3

/* WSC Opcode */
#define	WSC_OPCODE_START		0x01
#define	WSC_OPCODE_ACK			0x02
#define	WSC_OPCODE_NACK			0x03
#define	WSC_OPCODE_MSG			0x04
#define	WSC_OPCODE_DONE			0x05
#define	WSC_OPCODE_FRAG_ACK		0x06

/* Flags */
#define	WSC_MSG_FLAG_MF			0x01	/* More fragments */
#define WSC_MSG_FLAG_LF			0x02	/* Length field */

#define WSC_OPCODE_UPNP_MASK	0x10
#define WSC_OPCODE_UPNP_DATA	0x11
#define WSC_OPCODE_UPNP_MGMT	0x12
#define WSC_OPCODE_UPNP_CTRL	0x13

#define WSC_UPNP_MGMT_SUB_PROBE_REQ		0x01
#define WSC_UPNP_MGMT_SUB_CONFIG_REQ	0x02
#define WSC_UPNP_MGMT_SUB_REG_SELECT	0x03

/*patch for Atheros External registrar */
#define WSC_UPNP_DATA_SUB_INCLUDE_MAC	0x0100

#define WSC_UPNP_DATA_SUB_NORMAL		0x00
#define WSC_UPNP_DATA_SUB_TO_ALL		0x01
#define WSC_UPNP_DATA_SUB_TO_ONE		0x02
#define WSC_UPNP_DATA_SUB_ACK			0x03
#define WSC_UPNP_DATA_SUB_M1			0x04
#define WSC_UPNP_DATA_SUB_M2			0x05
#define WSC_UPNP_DATA_SUB_M2D			0x06
#define WSC_UPNP_DATA_SUB_M3			0x07
#define WSC_UPNP_DATA_SUB_M4			0x08
#define WSC_UPNP_DATA_SUB_M5			0x09
#define WSC_UPNP_DATA_SUB_M6			0x0A
#define WSC_UPNP_DATA_SUB_M7			0x0B
#define WSC_UPNP_DATA_SUB_M8			0x0C
#define WSC_UPNP_DATA_SUB_WSC_ACK		0x0D
#define WSC_UPNP_DATA_SUB_WSC_NACK		0x0E
#define WSC_UPNP_DATA_SUB_WSC_DONE		0x0F
#define WSC_UPNP_DATA_SUB_PBC_OVERLAP		0x10
#define WSC_UPNP_DATA_SUB_WSC_TIMEOUT		0x20
#define WSC_UPNP_DATA_SUB_WSC_UNKNOWN	0xff

/* Wsc EAP Messges type */
#define	WSC_MSG_EAP_RSP_ID			0x21
#define	WSC_MSG_EAP_REG_RSP_ID      0x22
#define	WSC_MSG_EAP_ENR_RSP_ID      0x23
#define	WSC_MSG_EAP_UPNP_RSP_ID     0x24
#define	WSC_MSG_EAP_REQ_ID			0x25
#define	WSC_MSG_EAP_REQ_START		0x26
#define	WSC_MSG_EAP_FAIL			0x27
#define WSC_MSG_EAP_FRAG_ACK		0x28
#define	WSC_MSG_PROB_RSP			0x01
#define WSC_MSG_EAPOL_START         0x02
#define	WSC_MSG_M1					0x04
#define	WSC_MSG_M2					0x05
#define	WSC_MSG_M2D					0x06
#define	WSC_MSG_M3					0x07
#define	WSC_MSG_M4					0x08
#define	WSC_MSG_M5					0x09
#define	WSC_MSG_M6					0x0A
#define	WSC_MSG_M7					0x0B
#define	WSC_MSG_M8					0x0C
#define	WSC_MSG_WSC_ACK				0x0D
#define	WSC_MSG_WSC_NACK			0x0E
#define	WSC_MSG_WSC_DONE			0x0F
#define	WSC_MSG_UNKNOWN				0xff

/* WSC connection mode */
#define	WSC_PIN_MODE		        1
#define	WSC_PBC_MODE		        2
#define WSC_SMPBC_MODE				3

/* Value of WSC_IE_DEV_PASS_ID 0x1012 */
#define	DEV_PASS_ID_PIN				0x0000
#define	DEV_PASS_ID_USER			0x0001
#define	DEV_PASS_ID_MACHINE			0x0002
#define	DEV_PASS_ID_REKEY			0x0003
#define	DEV_PASS_ID_PBC				0x0004
#define	DEV_PASS_ID_REG				0x0005
#define DEV_PASS_ID_SMPBC			0x0006
#ifdef WSC_NFC_SUPPORT
#define DEV_PASS_ID_NFC_HANDOVER	0x0007	/* 0006 */
#endif /* WSC_NFC_SUPPORT */
#define	DEV_PASS_ID_NOSPEC			0xffff

/* Common definition */
#define	WSC_VERSION					0x10
#define WSC_CONFIG_METHODS			0x008C

/* Wsc status code */
#define	STATUS_WSC_NOTUSED						0
#define	STATUS_WSC_IDLE							1
#define STATUS_WSC_FAIL				        2	/* WSC Process Fail */
#define	STATUS_WSC_LINK_UP						3	/* Start WSC Process */
#define	STATUS_WSC_EAPOL_START_RECEIVED			4	/* Received EAPOL-Start */
#define	STATUS_WSC_EAP_REQ_ID_SENT				5	/* Sending EAP-Req(ID) */
#define	STATUS_WSC_EAP_RSP_ID_RECEIVED			6	/* Receive EAP-Rsp(ID) */
#define	STATUS_WSC_EAP_RSP_WRONG_SMI			7	/* Receive EAP-Req with wrong WSC SMI Vendor Id */
#define	STATUS_WSC_EAP_RSP_WRONG_VENDOR_TYPE	8	/* Receive EAPReq with wrong WSC Vendor Type */
#define	STATUS_WSC_EAP_REQ_WSC_START			9	/* Sending EAP-Req(WSC_START) */
#define	STATUS_WSC_EAP_M1_SENT					10	/* Send M1 */
#define	STATUS_WSC_EAP_M1_RECEIVED				11	/* Received M1 */
#define	STATUS_WSC_EAP_M2_SENT					12	/* Send M2 */
#define	STATUS_WSC_EAP_M2_RECEIVED				13	/* Received M2 */
#define	STATUS_WSC_EAP_M2D_RECEIVED				14	/* Received M2D */
#define	STATUS_WSC_EAP_M3_SENT					15	/* Send M3 */
#define	STATUS_WSC_EAP_M3_RECEIVED				16	/* Received M3 */
#define	STATUS_WSC_EAP_M4_SENT					17	/* Send M4 */
#define	STATUS_WSC_EAP_M4_RECEIVED				18	/* Received M4 */
#define	STATUS_WSC_EAP_M5_SENT					19	/* Send M5 */
#define	STATUS_WSC_EAP_M5_RECEIVED				20	/* Received M5 */
#define	STATUS_WSC_EAP_M6_SENT					21	/* Send M6 */
#define	STATUS_WSC_EAP_M6_RECEIVED				22	/* Received M6 */
#define	STATUS_WSC_EAP_M7_SENT					23	/* Send M7 */
#define	STATUS_WSC_EAP_M7_RECEIVED				24	/* Received M7 */
#define	STATUS_WSC_EAP_M8_SENT					25	/* Send M8 */
#define	STATUS_WSC_EAP_M8_RECEIVED				26	/* Received M8 */
#define	STATUS_WSC_EAP_RAP_RSP_ACK				27	/* Processing EAP Response (ACK) */
#define	STATUS_WSC_EAP_RAP_REQ_DONE_SENT		28	/* Processing EAP Request (Done) */
#define	STATUS_WSC_EAP_RAP_RSP_DONE_SENT		29	/* Processing EAP Response (Done) */
#define STATUS_WSC_EAP_FAIL_SENT                30	/* Sending EAP-Fail */
#define STATUS_WSC_ERROR_HASH_FAIL              31	/* WSC_ERROR_HASH_FAIL */
#define STATUS_WSC_ERROR_HMAC_FAIL              32	/* WSC_ERROR_HMAC_FAIL */
#define STATUS_WSC_ERROR_DEV_PWD_AUTH_FAIL      33	/* WSC_ERROR_DEV_PWD_AUTH_FAIL */
#define STATUS_WSC_CONFIGURED					34
#define	STATUS_WSC_SCAN_AP						35	/* Scanning AP */
#define	STATUS_WSC_EAPOL_START_SENT				36
#define STATUS_WSC_EAP_RSP_DONE_SENT			37
#define STATUS_WSC_WAIT_PIN_CODE                38
#define STATUS_WSC_START_ASSOC					39
#define STATUS_WSC_IBSS_WAIT_NEXT_SMPBC_ENROLLEE	40
#define STATUS_WSC_IBSS_NEW_RANDOM_PIN			41
#define STATUS_WSC_IBSS_FIXED_PIN				42

/* All error message dtarting from 0x0100 */
#define	STATUS_WSC_PBC_TOO_MANY_AP				0x0101	/* Too many PBC AP avaliable */
#define	STATUS_WSC_PBC_NO_AP					0x0102	/* No PBC AP avaliable */
#define	STATUS_WSC_EAP_FAIL_RECEIVED			0x0103	/* Received EAP-FAIL */
#define	STATUS_WSC_EAP_NONCE_MISMATCH			0x0104	/* Receive EAP with wrong NONCE */
#define	STATUS_WSC_EAP_INVALID_DATA	0x0105	/* Receive EAP without integrity (Hmac mismatch) */
#define STATUS_WSC_PASSWORD_MISMATCH			0x0106	/* Error PIN Code (R-Hash mismatch) */
#define	STATUS_WSC_EAP_REQ_WRONG_SMI			0x0107	/* Receive EAP-Req with wrong WPS SMI Vendor Id */
#define	STATUS_WSC_EAP_REQ_WRONG_VENDOR_TYPE	0x0108	/* Receive EAPReq with wrong WPS Vendor Type */
#define	STATUS_WSC_PBC_SESSION_OVERLAP			0x0109	/* AP PBC session overlap */
#define	STATUS_WSC_SMPBC_TOO_MANY_REGISTRAR		0x010a	/* Too many SMPBC Registrars avaliable */
#define STATUS_WSC_EMPTY_IPV4_SUBMASK_LIST		0x010b	/* Empty available IPv4 Submask list */
#define	STATUS_WSC_SMPBC_NO_AP					0x010c	/* No SMPBC AP avaliable */

#define WSC_DISABLE		    0x0
#define WSC_ENROLLEE     0x1
#define WSC_PROXY        0x2
#define WSC_REGISTRAR    0x4
#define WSC_ENROLLEE_PROXY           (WSC_ENROLLEE | WSC_PROXY)
#define WSC_ENROLLEE_REGISTRAR       (WSC_ENROLLEE | WSC_REGISTRAR)
#define WSC_PROXY_REGISTRAR          (WSC_PROXY | WSC_REGISTRAR)
#define WSC_ENROLLEE_PROXY_REGISTRAR (WSC_ENROLLEE | WSC_PROXY | WSC_REGISTRAR)

/* Device request/response type */
#define WSC_MSGTYPE_ENROLLEE_INFO_ONLY		0x00
#define WSC_MSGTYPE_ENROLLEE_OPEN_8021X		0x01
#define WSC_MSGTYPE_REGISTRAR				0x02
#define WSC_MSGTYPE_AP_WLAN_MGR				0x03
#ifdef IWSC_SUPPORT
#define WSC_MSGTYPE_IWSC_NOTIFIER			0x04
#endif /* IWSC_SUPPORT */

/* RF Band */
#define WSC_RFBAND_24GHZ    0x01
#define WSC_RFBAND_50GHZ    0x02

/* Simple Config state */
#define WSC_SCSTATE_UNCONFIGURED	0x01
#define WSC_SCSTATE_CONFIGURED		0x02

/* Common definition */
#define	WSC_MANUFACTURE		"Ralink Technology, Corp."
#ifdef CONFIG_AP_SUPPORT
#define	AP_WSC_MODEL_NAME		"Ralink Wireless Access Point"
#define	AP_WSC_DEVICE_NAME		"RalinkAPS"
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
#define	STA_WSC_MODEL_NAME		"Ralink Wireless Linux Client"
#define	STA_WSC_DEVICE_NAME		"RalinkLinuxClient"
#define	WSC_DEVICE_NAME_R	"Ralink EX-Registrar"
#endif /* CONFIG_STA_SUPPORT */
#define	WSC_MODEL_NUMBER	"RT2860"
#define	WSC_MODEL_SERIAL	"12345678"

/* Time-Out, param for timer func, count by micro-sec, not ticks */
#define WSC_EAPOL_START_TIME_OUT    2000
#define WSC_EAP_ID_TIME_OUT         5000
#define WSC_EAP_MSG_TIME_OUT        5000
#define WSC_EAP_MSG_ACK_TIME_OUT    1000
#define WSC_EAP_EAP_FAIL_TIME_OUT   1000
#define WSC_TWO_MINS_TIME_OUT       120000
#define WSC_UPNP_M2D_TIME_OUT		15000
#define WSC_UPNP_MSG_TIME_OUT		15000
#define	WSC_PROFILE_RETRY_TIME_OUT	10000
#ifdef WSC_LED_SUPPORT
#define WSC_SUCCESSFUL_LED_PATTERN_TIMEOUT		300000	/* 300 seconds */
#define WSC_WPS_FAIL_LED_PATTERN_TIMEOUT		15000	/* 15 seconds. */
#define WSC_WPS_SKIP_TURN_OFF_LED_TIMEOUT		2500	/* 2.5 seconds. */
#define WSC_WPS_TURN_OFF_LED_TIMEOUT			1000	/* 1 second. */
#endif /* WSC_LED_SUPPORT */

#ifdef WSC_V2_SUPPORT
#define WSC_WPS_AP_SETUP_LOCK_TIME				60	/* 60 mins */
#define WSC_WPS_AP_MAX_PIN_ATTACK				3
#define WSC_LOCK_FOREVER_PIN_ATTACK				10
#endif /* WSC_V2_SUPPORT */

#define WSC_INIT_ENTRY_APIDX        0xFF
#define WSC_MAX_DATA_LEN            1024

#define WSC_ENTRY_GET_EAPOL_START   0x1
#define WSC_ENTRY_GET_EAP_RSP_ID    0x2

/* Pack struct to align at byte */
/*#pragma pack(1) */

/* General used field */

/* UUID related definition */
#define UUID_LEN_HEX 16		/* 128 bits => 16 bytes */
#define UUID_LEN_STR 37		/* hex to string, plus 4 dash, plus 1 '\0' */
#define UUID_VERSION 1		/* We currently just support version 1 */

/* user define length add by woody */
#define WSC_MANUFACTURE_LEN		64
#define WSC_MODELNAME_LEN		32
#define WSC_MODELNUNBER_LEN		32
#define	WSC_DEVICENAME_LEN		32
#define WSC_SERIALNUNBER_LEN	32
#define MAX_2ND_DEV_TYPE_LIST	2
#define MAX_2ND_DEV_TYPE_LIST_BUFFER	(1+(8*MAX_2ND_DEV_TYPE_LIST))

typedef struct _WSC_UUID_T {
	UINT32 timeLow;
	UINT16 timeMid;
	UINT16 timeHi_Version;
	UCHAR clockSeqHi_Var;
	UCHAR clockSeqLow;
	UCHAR node[6];
} WSC_UUID_T;

/* For WSC state machine states. */
/* We simplified it */
typedef enum _WscState {
	WSC_STATE_OFF,
	WSC_STATE_INIT,
	WSC_STATE_START,
	WSC_STATE_FAIL,
	WSC_STATE_CONFIGURED,
	WSC_STATE_LINK_UP,
	WSC_STATE_SEND_EAPOL_START,
	WSC_STATE_WAIT_EAPOL_START,
	WSC_STATE_WAIT_UPNP_START,
	WSC_STATE_WAIT_REQ_ID,
	WSC_STATE_WAIT_RESP_ID,
	WSC_STATE_WAIT_WSC_START,
	WSC_STATE_WAIT_M1,
	WSC_STATE_SENT_M1,
	WSC_STATE_SENT_M2D,
	WSC_STATE_WAIT_M2,
	WSC_STATE_RX_M2D,
	WSC_STATE_WAIT_PIN,
	WSC_STATE_WAIT_M3,
	WSC_STATE_WAIT_M4,
	WSC_STATE_WAIT_M5,
	WSC_STATE_WAIT_M6,
	WSC_STATE_WAIT_M7,
	WSC_STATE_WAIT_M8,
	WSC_STATE_WAIT_DONE,
	WSC_STATE_WAIT_ACK,
	WSC_STATE_WAIT_EAPFAIL,
	WSC_STATE_WAIT_DISCONN
} WSC_STATE;

/* WSC saved message */
typedef struct _WSC_MESSAGE {
	INT Length;		/* Length of saved message */
	UCHAR Data[2048];	/* Contents */
} WSC_MESSAGE, *PWSC_MESSAGE;


/* Data structure to hold Enrollee and Registrar information */
typedef struct _WSC_DEV_INFO {
	UCHAR Version;
	UCHAR Version2;
	UCHAR Uuid[16];
	UCHAR MacAddr[6];
	UCHAR DeviceName[32];
	UCHAR PriDeviceType[8];
	UCHAR SecDevTypList[MAX_2ND_DEV_TYPE_LIST_BUFFER];	/* 2nd Device Type List, ref. P2P Spec. v1.1 Table 29 */
	USHORT AuthTypeFlags;
	USHORT EncrTypeFlags;
	UCHAR ConnTypeFlags;
	USHORT ConfigMethods;
	UCHAR ScState;
	UCHAR Manufacturer[64];
	UCHAR ModelName[32];
	UCHAR ModelNumber[32];
	UCHAR SerialNumber[32];
	UCHAR RfBand;
	UINT OsVersion;
	UINT FeatureId;
	USHORT AssocState;
	USHORT DevPwdId;
	USHORT ConfigError;
	UCHAR Ssid[32];
	UCHAR NewKey[64 + 1];	/* not sure sprintf would add '\0' or not, add one byte for \0' */
	INT NewKeyLen;
	UCHAR NewKeyIndex;
} WSC_DEV_INFO, *PWSC_DEV_INFO;

/* data structure to store info of the instance of Registration protocol */
typedef struct _WSC_REG_DATA {
	/* filled in by device self */
	WSC_DEV_INFO SelfInfo;
	/* filled in by wps peer */
	WSC_DEV_INFO PeerInfo;

	/*Diffie Hellman parameters */
/*	BIGNUM		*DH_PubKey_Peer; //peer's pub key stored in bignum format */
/*	DH			*DHSecret;       //local key pair in bignum format */
	UCHAR EnrolleeRandom[192];	/* Saved random byte for public key generation */

	UCHAR ReComputePke;
	UCHAR Pke[192];		/*enrollee's raw pub key */
	UCHAR Pkr[192];		/*registrar's raw pub key */

	UCHAR SecretKey[192];	/* Secret key calculated by enrollee */

	UCHAR StaEncrSettings[128];	/* to be sent in M2/M8 by reg & M7 by enrollee */
	UCHAR ApEncrSettings[1024];

	/* Saved Message content for authenticator calculation */
	WSC_MESSAGE LastTx;
	WSC_MESSAGE LastRx;

	/* Device password */
	UCHAR PIN[8];
	UCHAR PinCodeLen;

	/* From KDF Key */
	UCHAR AuthKey[32];
	UCHAR KeyWrapKey[16];
	UCHAR Emsk[32];

	USHORT EnrolleePwdId;
	UCHAR EnrolleeNonce[16];	/*N1, from enrollee */
	UCHAR RegistrarNonce[16];	/*N2, from registrar */
	UCHAR SelfNonce[16];

	UCHAR Psk1[16];
	UCHAR Psk2[16];

	UCHAR EHash1[32];
	UCHAR EHash2[32];
	UCHAR Es1[16];
	UCHAR Es2[16];

	UCHAR RHash1[32];
	UCHAR RHash2[32];
	UCHAR Rs1[16];
	UCHAR Rs2[16];
} WSC_REG_DATA, *PWSC_REG_DATA;

/* WSC UPnP node info. */
typedef struct _WSC_UPNP_NODE_INFO {
	BOOLEAN bUPnPInProgress;
	BOOLEAN bUPnPMsgTimerRunning;
	BOOLEAN bUPnPMsgTimerPending;
	UINT registrarID;
	RALINK_TIMER_STRUCT UPnPMsgTimer;
} WSC_UPNP_NODE_INFO, *PWSC_UPNP_NODE_INFO;

#define MAX_PBC_STA_TABLE_SIZE	4
typedef struct _WSC_STA_PBC_PROBE_INFO {
	ULONG ReciveTime[MAX_PBC_STA_TABLE_SIZE];
	UCHAR WscPBCStaProbeCount;
	UCHAR StaMacAddr[MAX_PBC_STA_TABLE_SIZE][MAC_ADDR_LEN];
	UCHAR Valid[MAX_PBC_STA_TABLE_SIZE];
} WSC_STA_PBC_PROBE_INFO, *PWSC_STA_PBC_PROBE_INFO;

#ifdef IWSC_SUPPORT
typedef struct _IWSC_INFO {
	RALINK_TIMER_STRUCT IWscT1Timer;
	RALINK_TIMER_STRUCT IWscT2Timer;
	RALINK_TIMER_STRUCT IWscEntryTimer;
	RALINK_TIMER_STRUCT IWscDevQueryTimer;
	UCHAR DialogToken;
	UCHAR PeerDialogToken;
	BOOLEAN bSelRegStart;
	BOOLEAN bReStart;
	BOOLEAN bIWscT1TimerRunning;
	BOOLEAN bIWscT2TimerRunning;
	BOOLEAN bIWscEntryTimerRunning;
	BOOLEAN bIWscDevQueryReqTimerRunning;
	BOOLEAN bIWscDevQueryRspTimerRunning;
	BOOLEAN bLimitedUI;	/* own device is limited UI device */
	BOOLEAN bSinglePIN;	/* use Physical PIN */
	BOOLEAN bDoNotChangeBSSID;
	BOOLEAN bSendEapolStart;
	UCHAR RegMacAddr[MAC_ADDR_LEN];
	UINT8 IWscSmpbcAcceptCount;
	USHORT IpConfMethod;	/* Bitwise OR values */
	USHORT IpMethod;	/* Single Method in WSC Credential */
	UINT32 SelfIpv4Addr;	/* Device own IPv4 Address */
	UINT32 PeerIpv4Addr;	/* IPv4 Address for peer in credtential */
	UINT32 RegIpv4Addr;	/* Registrar's IPv4 Address */
	UINT32 Ipv4SubMask;	/* 255.0.0.0 */
	UINT32 CurrentIpRange;
	UINT32 AvaSubMaskList[IWSC_MAX_SUB_MASK_LIST_COUNT];
	UINT8 IpDevCount;	/* Maximal value is 62 */
	UINT8 RegDepth;		/* 0: Root Regitrar */
	UINT8 AvaSubMaskListCount;	/* Available Submask List Count for peer. Maximal value is 3 */
	BOOLEAN bAssignWscIPv4;	/* TRUE: Can be registrar and assign WSC IPv4 to peer,
				* FALSE: Cannot assign WSC IPv4 to peer anymore
				*/
	BOOLEAN bDoNotStop;
	UCHAR IWscDevQueryReqMacAddr[MAC_ADDR_LEN];
	UINT8 SmpbcEnrolleeCount;
#ifdef IWSC_TEST_SUPPORT
	UINT8 IWscConfMode;	/* 1: Enrollee, 2: Registrar */
	UINT8 IWscDefaultSecurity;	/* 1: OPEN-NONE, 2: OPEN-WEP, 3: WPA2PSK-AES */
	BOOLEAN bIwscSmpbcScanningOnly;
	BOOLEAN bEmptySubmaskList;
	BOOLEAN bBlockConnection;	/* TRUE: block connection with peers
					* (i.e. Not to do security handshaking with peers)
					*/
#endif				/* IWSC_TEST_SUPPORT // */
} IWSC_INFO, *PIWSC_INFO;
#endif /* IWSC_SUPPORT // */

#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */

typedef struct GNU_PACKED _WSC_PEER_DEV_INFO {
	UCHAR WscPeerDeviceName[32];
	UCHAR WscPeerManufacturer[64];
	UCHAR WscPeerModelName[32];
	UCHAR WscPeerModelNumber[32];
	UCHAR WscPeerSerialNumber[32];
	UCHAR WscPeerMAC[6];
} WSC_PEER_DEV_INFO, *PWSC_PEER_DEV_INFO;

#ifdef WSC_V2_SUPPORT
#define WSC_PIN_ATTACK_CHECK	600
#define WSC_V2_VERSION			0x20
#define		TLV_ASCII	0
#define		TLV_HEX		1

#ifdef WSC_NFC_SUPPORT
/*
		0 �V Command Result (1 byte)
		1 -  Configuration (WSC TLV)
		2 �V Password (32 bytes)
		3 �V IP address (4 bytes)
		4 �V RTSP port (4 bytes)
		5 �V NFC Status (1 byte)
		6 �V Wireless Radio Status (1byte)
*/
#define TYPE_CMD_RESULT			0
#define TYPE_CONFIGURATION		1
#define TYPE_PASSWORD				2
#define TYPE_IP_ADDR				3
#define TYPE_RTSP_PORT				4
#define TYPE_NFC_STATUS			5
#define TYPE_WIFI_RADIO_STATUS	6
#define TYPE_PASSWDHO_S			7	/* handover Select */
#define TYPE_PASSWDHO_R			8	/* handover Request */

#define NFC_DEV_PASSWD_LEN		32
#define NFC_DEV_PASSWD_HASH_LEN		20

/* NFC usage models */
#define MODEL_PASSWORD_TOKEN		0
#define MODEL_CONFIGURATION_TOKEN	1
#define MODEL_HANDOVER				2
#endif /* WSC_NFC_SUPPORT */

typedef struct _WSC_TLV {
	USHORT TlvTag;
	USHORT TlvLen;
	PUCHAR pTlvData;
	UCHAR TlvType;		/* 0: ASCII, 1: Hex */
} WSC_TLV, *PWSC_TLV;

typedef struct _WSC_V2_INFO {
	WSC_TLV ExtraTlv;
	BOOLEAN bWpsEnable;	/* FALSE: disable WSC , TRUE: enable WSC */
	BOOLEAN bEnableWpsV2;	/* FALSE: not support WSC 2.0, TRUE: support WSC 2.0 */
#ifdef CONFIG_STA_SUPPORT
	BOOLEAN bForceSetAP;	/* FALSE: do not change AP's setting when AP is configured,
				* TRUE: force to change AP's setting when AP is configured
				*/
#endif				/* CONFIG_STA_SUPPORT */
} WSC_V2_INFO, *PWSC_V2_INFO;
#endif /* WSC_V2_SUPPORT */

/* WSC control block */
typedef struct _WSC_CTRL {
	INT WscConfMode;	/* 0 Wsc not enable; 1 un-configure AP ; 3 un-configure AP with Proxy ; */
	/* 5 un-configure AP with Registrar ; 7 un-configure AP with proxy and Registrar */
	INT WscMode;		/* 1 PIN ;2 PBC set from UI dynamically */
	UCHAR WscConfStatus;	/* 1 un-configured; 2 configured; need to update to .dat */
	USHORT WscConfigMethods;	/* Registrar support list. The List is bitwise.
					* PBC:0x0080 Lable:0x0004 Display:0x0008
					*/
	INT WscStatus;		/* for user to monitor the status */
	INT WscState;		/* WSC Protocl State: M1 to M8 */
	UINT WscPinCode;	/* record the UI's PIN code input when we are registrar */
	UCHAR WscPinCodeLen;	/* record the UI's PIN code input length when we are registrar */
	BOOLEAN WscEnrollee4digitPinCode;	/* flag to use 4 or 8 digit Device own PIN code. */
	UINT WscEnrolleePinCode;	/* recored Device own PIN code. */
	UCHAR WscEnrolleePinCodeLen;	/* recored Device own PIN code length */
	INT WscSelReg;		/* record the UI's PIN code input when we are registrar */
	NDIS_802_11_SSID WscSsid;	/* select a desired ssid to connect for PIN mode */
	UCHAR WscPBCBssCount;	/* Count of PBC activated APs. */
	UCHAR WscBssid[MAC_ADDR_LEN];	/* select a desired bssid to connect */
#ifdef CONFIG_STA_SUPPORT
	BOOLEAN WscEnAssociateIE;	/* Add WSC IE on Associate frame. */
	BOOLEAN WscEnProbeReqIE;	/* Add WSC IE on Probe-Req frame. */
	UCHAR WscPeerMAC[MAC_ADDR_LEN];	/* peer Mac Address */
#endif				/* CONFIG_STA_SUPPORT */
	WSC_REG_DATA RegData;	/* Registrar pair data */
	UCHAR lastId;
	UCHAR WscUseUPnP;
	BOOLEAN EapMsgRunning;	/* already recived Eap-Rsp(Identity) and sent M1 or Eap-Req(Start) */
	UCHAR WscRetryCount;
	UCHAR EntryIfIdx;
	UCHAR EntryAddr[MAC_ADDR_LEN];
	BOOLEAN Wsc2MinsTimerRunning;
	RALINK_TIMER_STRUCT Wsc2MinsTimer;
	WSC_PROFILE WscProfile;	/* Saved WSC profile after M8 */
#ifdef CONFIG_STA_SUPPORT
	WSC_PROFILE WscM7Profile;	/* Saved WSC profile from AP Settings in M7 */
	BOOLEAN bConfiguredAP;	/* True: AP is in the configured state. FALSE: others */
#endif				/* CONFIG_STA_SUPPORT */
	WSC_UPNP_NODE_INFO WscUPnPNodeInfo;	/*Use to save UPnP node related info. */

	BOOLEAN EapolTimerRunning;
	BOOLEAN EapolTimerPending;
	RALINK_TIMER_STRUCT EapolTimer;

	BOOLEAN WscPBCTimerRunning;
	RALINK_TIMER_STRUCT WscPBCTimer;
	BOOLEAN WscScanTimerRunning;
	RALINK_TIMER_STRUCT WscScanTimer;
	BOOLEAN WscProfileRetryTimerRunning;
	RALINK_TIMER_STRUCT WscProfileRetryTimer;
#ifdef CONFIG_STA_SUPPORT
	/* 0x00: disable, 0x01: Auto Connect first credential only, 0x02: Auto Connect and rotate all crentials */
	UCHAR WscDriverAutoConnect;
#endif				/* CONFIG_STA_SUPPORT */
#ifdef WSC_LED_SUPPORT
	ULONG WscLEDMode;	/* WPS LED mode: LED_WPS_XXX definitions. */
	ULONG WscLastWarningLEDMode;	/* LED_WPS_ERROR or LED_WPS_SESSION_OVERLAP_DETECTED */
	BOOLEAN bSkipWPSTurnOffLED;	/* Skip the WPS turn off LED command. */
	BOOLEAN WscLEDTimerRunning;
	RALINK_TIMER_STRUCT WscLEDTimer;
	BOOLEAN WscSkipTurnOffLEDTimerRunning;
	RALINK_TIMER_STRUCT WscSkipTurnOffLEDTimer;
	/* This variable is TRUE after the 120 seconds WPS walk time expiration. */
	/* Note that in the case of LED mode 9, the error LED should be turned on only after WPS walk time expiration */
	/* if the NIC cannot find any WPS PBC-enabled APs in the last scanning result. */
	BOOLEAN bWPSWalkTimeExpiration;
#endif				/* WSC_LED_SUPPORT */
	UCHAR WpaPsk[64];
	INT WpaPskLen;
	BOOLEAN bWscTrigger;	/* TRUE: AP-Enrollee & AP-Registrar work,
				* FALSE: AP-Enrollee & AP-Registrar stop working
				*/
	PVOID pAd;
	UINT WscLastPinFromEnrollee;
	BOOLEAN WscRejectSamePinFromEnrollee;
#ifdef CONFIG_AP_SUPPORT
	NDIS_802_11_SSID WscDefaultSsid;	/* Default WPS SSID after WPS process complete
						* with Enrollee when AP is un-configured Registrar.
									*/
	BOOLEAN bWCNTest;
#endif				/* CONFIG_AP_SUPPORT */
	INT WscKeyASCII;	/*WscKeyASCII (0:Hex, 1:ASCII(random length), others: ASCII length(8~63, default 8)) */
	INT WscActionMode;
	UCHAR Wsc_Uuid_E[UUID_LEN_HEX];
	UCHAR Wsc_Uuid_Str[UUID_LEN_STR];

	UCHAR WpsApBand;	/* Preferred WPS AP PHY type. Ref: PREFERRED_WPS_AP_PHY_TYPE */
/*add by woody */
	UCHAR Flags;

	WSC_PEER_DEV_INFO WscPeerInfo;
	BOOLEAN bCheckMultiByte;
#ifdef WSC_V2_SUPPORT
	WSC_V2_INFO WscV2Info;
#endif				/* WSC_V2_SUPPORT */
	RALINK_TIMER_STRUCT WscUpdatePortCfgTimer;
	BOOLEAN WscUpdatePortCfgTimerRunning;
#ifdef CONFIG_AP_SUPPORT
	RALINK_TIMER_STRUCT WscSetupLockTimer;
	BOOLEAN WscSetupLockTimerRunning;
	RALINK_TIMER_STRUCT WscPinAttackCountCheckTimer;
	BOOLEAN WscPinAttackCountCheckTimerRunning;
	BOOLEAN bSetupLock;
	UCHAR PinAttackCount;
	UCHAR MaxPinAttack;
	UINT SetupLockTime;	/* unit: minute */
#endif				/* CONFIG_AP_SUPPORT */
	BOOLEAN bWscAutoTigeer;
	BOOLEAN bWscFragment;
	PUCHAR pWscRxBuf;
	INT WscRxBufLen;
	USHORT WscFragSize;
	INT WscTxBufLen;
	PUCHAR pWscTxBuf;
	BOOLEAN bWscLastOne;
	BOOLEAN bWscFirstOne;
	PUCHAR pWscCurBufIdx;
	NDIS_SPIN_LOCK WscPeerListSemLock;
	LIST_HEADER WscPeerList;
	RALINK_TIMER_STRUCT M2DTimer;
	BOOLEAN bM2DTimerRunning;
	INT M2DACKBalance;
#ifdef IWSC_SUPPORT
	NDIS_SPIN_LOCK WscConfiguredPeerListSemLock;
	LIST_HEADER WscConfiguredPeerList;
#endif				/* IWSC_SUPPORT */
#ifdef WSC_NFC_SUPPORT
	BOOLEAN bTriggerByNFC;
	UCHAR NfcPasswdLen;
	UCHAR NfcPasswd[NFC_DEV_PASSWD_LEN];
	USHORT NfcPasswdID;
	UCHAR NfcPasswdHash[NFC_DEV_PASSWD_HASH_LEN];
	UCHAR PeerNfcPasswdLen;
	UCHAR PeerNfcPasswd[NFC_DEV_PASSWD_LEN];
	USHORT PeerNfcPasswdID;
	UCHAR PeerNfcPasswdHash[NFC_DEV_PASSWD_HASH_LEN];
	UCHAR NfcStatus;	/* b'0: 1 - ON, 0 - OFF;     b'1: 1 - nfc device detect */
	UCHAR NfcPasswdCaculate;
	BOOLEAN bRegenPublicKey;	/* For negative test */
	UCHAR NfcModel;		/* 0:Password_Token, 1:Configuration_Token, 2:Handover */
#endif				/* WSC_NFC_SUPPORT */
} WSC_CTRL, *PWSC_CTRL;

typedef struct GNU_PACKED _WSC_CONFIGURED_VALUE {
	USHORT WscConfigured;	/* 1 un-configured; 2 configured */
	UCHAR WscSsid[32 + 1];
	UCHAR WscSsidLen;
	USHORT WscAuthMode;	/* mandatory, 0x01: open, 0x02: wpa-psk, 0x04: shared,
						* 0x08:wpa, 0x10: wpa2, 0x20: wpa2-psk
						*/
	USHORT WscEncrypType;	/* 0x01: none, 0x02: wep, 0x04: tkip, 0x08: aes */
	UCHAR DefaultKeyIdx;
	UCHAR WscWPAKey[64 + 1];
	UCHAR WscWPAKeyLen;
} WSC_CONFIGURED_VALUE;

/*
	Following definitions are used for UPnP module to communicate msg.
*/

/* Ralink specific message header for Linux specific NETLINK socket. */

/*signature(8) + envID(4) + ackID(4) + msgLen(4) + Flag(2) + segLen(2) + devAddr(6) */
#define RTMP_WSC_NLMSG_HDR_LEN		30

typedef struct GNU_PACKED _RTMP_WSC_NLMSG_HDR {
	/* Signature used to identify that this's a Ralink specific NETLINK message.
	* MUST be "RAWSCMSG" currently.
	*/
	UCHAR signature[8];
	UINT envID;		/* Unique event Identification assigned by sender. */
	/* Notify that this message is a repsone for the message whose event identifier
	* is "ackID".
	*/
	UINT ackID;
	UINT msgLen;		/* Totally length for this message. This message may seperate in serveral packets. */
	USHORT flags;
	/* The "segLen" means the actual data length in this one msg packet. Because the
	* NETLINK socket just support 256bytes for "IWCUSTOM" typed message,
	* so we may  need to do fragement for our msg. If one message
	* was fragemented as several pieces, the user space receiver need to re-assemble it.
	*/
	USHORT segLen;
	UCHAR devAddr[MAC_ADDR_LEN];	/* MAC address of the net device which send this netlink msg. */
} RTMP_WSC_NLMSG_HDR;

/*
	Ralink specific WSC Mesage Header definition.
*/
#define RTMP_WSC_MSG_HDR_LEN		12	/*msgType(2) + msgSubType(2) + ipAddr(4) + len(4) */
typedef struct GNU_PACKED _RTMP_WSC_MSG_HDR {
	USHORT msgType;
	USHORT msgSubType;
	UINT ipAddr;
	UINT msgLen;		/*Not include this header. */
} RTMP_WSC_MSG_HDR;

#define WSC_MSG_TYPE_ENROLLEE    0x1
#define WSC_MSG_TYPE_PROXY	 0x2
#define WSC_MSG_TYPE_REGISTRAR   0x3
#define WSC_MSG_TYPE_CTRL	 0x4
#define WSC_MSG_TYPE_MGMT	 0x5

PSTRING WscGetAuthTypeStr(IN USHORT authFlag);

PSTRING WscGetEncryTypeStr(IN USHORT encryFlag);

#define IWEVCUSTOM_MSG_MAX_LEN  255	/*refer to kernel definition. <linux/wireless.h> */
#define IWEVCUSTOM_PAYLOD_MAX_LEN  (IWEVCUSTOM_MSG_MAX_LEN - RTMP_WSC_NLMSG_HDR_LEN)

#define WSC_U2KMSG_HDR_LEN	41
typedef struct GNU_PACKED _RTMP_WSC_U2KMSG_HDR {
	UINT envID;		/*Event ID. */
	UCHAR Addr1[MAC_ADDR_LEN];	/*RA, should be the MAC address of the AP. */
	UCHAR Addr2[MAC_ADDR_LEN];	/*TA, should be the ipAddress of remote UPnP Device/CotrnolPoint. */
	UCHAR Addr3[MAC_ADDR_LEN];	/*DA, Not used now. */
	UCHAR rsvWLHdr[2];	/*Reserved space for remained 802.11 hdr content. */
	UCHAR rsv1HHdr[LENGTH_802_1_H];	/*Reserved space for 802.1h header */
	IEEE8021X_FRAME IEEE8021XHdr;	/*802.1X header */
	EAP_FRAME EAPHdr;	/*EAP frame header. */
} RTMP_WSC_U2KMSG_HDR;
/*--- Used for UPnP module to communicate msg. */

/* define OpMode for WscSendMessage */
#undef     AP_MODE
#undef     AP_CLIENT_MODE
#undef     STA_MODE

#define     AP_MODE		0x00
#define     AP_CLIENT_MODE	0x01
#define     STA_MODE		0x02
#define		REGISTRAR_ACTION	0x40
#define	ENROLLEE_ACTION		0x80

/* Definition for Config Methods */
#define		WPS_CONFIG_METHODS_USBA			0x0001
#define		WPS_CONFIG_METHODS_ETHERNET		0x0002
#define		WPS_CONFIG_METHODS_LABEL		0x0004
#define		WPS_CONFIG_METHODS_DISPLAY		0x0008
#define		WPS_CONFIG_METHODS_ENT			0x0010	/* External NFC Token */
#define		WPS_CONFIG_METHODS_INT			0x0020	/* Integrated NFC Token */
#define		WPS_CONFIG_METHODS_NFCI			0x0040	/* NFC Interface */
#define		WPS_CONFIG_METHODS_PBC			0x0080
#define		WPS_CONFIG_METHODS_KEYPAD		0x0100

typedef struct _UUID_BSSID_CH_INFO {
	UCHAR Uuid[16];
	UCHAR Bssid[MAC_ADDR_LEN];
	UCHAR Channel;
	UCHAR Band;
	UCHAR Ssid[MAX_LEN_OF_SSID];
	UCHAR SsidLen;
	UCHAR MacAddr[MAC_ADDR_LEN];
#ifdef IWSC_SUPPORT
	UINT8 RspType;
#endif				/* IWSC_SUPPORT */
} UUID_BSSID_CH_INFO, *PUUID_BSSID_CH_INFO;

/*
	 Preferred WPS AP type.

	 a) PREFERRED_WPS_AP_PHY_TYPE_2DOT4_G_FIRST
	     Select 2.4G WPS AP first. Otherwise select 5G WPS AP.
	 b) PREFERRED_WPS_AP_PHY_TYPE_5_G_FIRST
	     Select the 5G WPS AP first. Otherwise select the 2.4G WPS AP.
	 c) PREFERRED_WPS_AP_PHY_TYPE_AUTO_SELECTION
	     Automactically select WPS AP.
*/
typedef enum _PREFERRED_WPS_AP_PHY_TYPE {
	PREFERRED_WPS_AP_PHY_TYPE_2DOT4_G_FIRST = 0,
	PREFERRED_WPS_AP_PHY_TYPE_5_G_FIRST,
	PREFERRED_WPS_AP_PHY_TYPE_AUTO_SELECTION,
	PREFERRED_WPS_AP_PHY_TYPE_MAXIMUM,
} PREFERRED_WPS_AP_PHY_TYPE;

typedef enum _WscSecurityMode {
	WPA2PSKAES,
	WPA2PSKTKIP,
	WPAPSKAES,
	WPAPSKTKIP,
} WSC_SECURITY_MODE;

typedef struct _WSC_PEER_ENTRY {
	struct _WSC_PEER_ENTRY *pNext;
	ULONG receive_time;
	UCHAR mac_addr[MAC_ADDR_LEN];
#ifdef IWSC_SUPPORT
	BOOLEAN bIWscSmpbcAccept;
#endif				/* IWSC_SUPPORT */
} WSC_PEER_ENTRY, *PWSC_PEER_ENTRY;


#endif /* WSC_INCLUDED */

#endif /* __WSC_H__ */
