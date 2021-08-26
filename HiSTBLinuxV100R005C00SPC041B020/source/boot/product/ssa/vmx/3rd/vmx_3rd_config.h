/*******************************************************************
                   Copyright 2008 - 2013, Hisilicon Tech. Co., Ltd.
                             ALL RIGHTS RESERVED

Filename      : vmx_config.h
Author        : 
Creation time : 2016/1/16
Description   : 

Version       : 1.0
********************************************************************/
#include "hi_type.h"

#define RSA_N_LEN    (256)
#define RSA_E_LEN    (256)
#define KEY_LEN      (16)
#define HASH_SIZE (20*1024*1024)    //20M per round inside this interface for hash


HI_U8 g_au8VMX3RDRsaN[RSA_N_LEN]=
{
	0xae,0xef,0x07,0x01,0x6d,0xc3,0x93,0xa6,0x98,0x63,0xb0,0x70,0x9c,0x99,0x91,0xa5,
	0xc3,0x2f,0x2a,0x1c,0x74,0x56,0xb7,0xf9,0x9c,0xb4,0x45,0xc2,0xa8,0x42,0x8e,0x72,
	0x3b,0x12,0x05,0x44,0xf6,0x56,0xa2,0xd6,0xd7,0x57,0x39,0x1b,0xa7,0x65,0xd7,0x9a,
	0xcd,0x89,0x90,0x79,0xe7,0xb1,0x0b,0x54,0xa8,0x87,0xc6,0x37,0x85,0x28,0x72,0x8e,
	0x9d,0x40,0xa7,0x76,0x2e,0x23,0x68,0x34,0x48,0xe1,0x49,0x1e,0xcd,0xdb,0x4e,0x48,
	0x22,0x9b,0xd1,0x51,0xcf,0x02,0xfc,0x7c,0x63,0x0c,0x21,0x85,0x6e,0x96,0xe5,0x10,
	0x15,0x06,0x22,0x9f,0xc5,0x7a,0x83,0xba,0x5d,0x8e,0x09,0xf9,0x73,0x0f,0x23,0x08,
	0x4b,0xc5,0x3e,0x6d,0x78,0x3c,0x93,0xe2,0x68,0x3d,0xd5,0x6b,0x1c,0x06,0x0a,0x00,
	0x15,0xda,0x0c,0xdf,0x13,0xf5,0xaa,0x11,0xf7,0xba,0xeb,0xdc,0x05,0x15,0x66,0x99,
	0x5d,0x38,0x85,0x0c,0xc7,0xd0,0xfb,0xe7,0x47,0x36,0xf3,0x2d,0xad,0x65,0x65,0xfe,
	0xc8,0xf8,0x51,0x47,0x2b,0xa7,0xeb,0x83,0xb4,0x2e,0x5f,0x7f,0xb3,0xde,0x22,0x66,
	0x67,0x12,0xff,0x0d,0xd2,0x71,0x0d,0xc2,0x98,0x9a,0xc2,0xa0,0x07,0xe4,0xea,0x4d,
	0x4e,0xba,0x15,0xac,0xad,0x28,0xd5,0x11,0x07,0xf0,0x73,0x06,0x19,0x90,0x7d,0x89,
	0x8c,0xc4,0x70,0x37,0x74,0x41,0xa0,0xd6,0xc9,0x38,0x7e,0xfd,0xcf,0x14,0x4b,0x55,
	0xe4,0xa3,0xb7,0x01,0xbf,0x7e,0xb1,0x48,0x56,0xd9,0xef,0x78,0x3c,0x2c,0x08,0x55,
	0x48,0x37,0xad,0xe5,0xdd,0x35,0x65,0xd2,0xe4,0x8a,0xaf,0x64,0x39,0xc6,0x8c,0x29
};

HI_U8 g_au8VMX3RDRsaE[RSA_E_LEN] = 
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01
};

//Misc input config
HI_U8 g_u8MiscInput1[KEY_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
HI_U8 g_u8MiscInput2[KEY_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
HI_U8 g_u8MiscInput3[KEY_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
HI_U8 g_u8MiscInput4[KEY_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
HI_U8 g_u8MiscInput5[KEY_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

HI_U8 g_u8MiscInput6[KEY_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

//Encrypt SWPK config
HI_U8 g_u8EncryptedSWPK[KEY_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
