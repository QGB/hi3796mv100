/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_hdmi_reg_sec_cfg.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/07/13
  Description   :
  History       :
  Date          : 2016/07/13
  Author        : t00273561
  Modification  :
*******************************************************************************/


#ifndef __TEE_REG_HDMI_SEC_H__
#define __TEE_REG_HDMI_SEC_H__

#include "hi_type.h"

#define HDMI_BASE_ADDR_SEC_CFG          0xF8A80000
#define REG_ADDR_PERI_HDMITX_AVCTTPT    (HDMI_BASE_ADDR_SEC_CFG +  0x0038)  



/*
*breaf      PERI_HDMITX_AVCTTPT	HDMI����Ƶ���ƼĴ���
*base       0xF8A80000
*addr       0x0038	
*data       32	
*default    0xF0000000
*/
typedef union
{
    struct{
        HI_U32 hdcp2x_video_mute   : 1  ;//[0    ]  RW  0x0 "����Ƶ��δ��HDCP2.2���ܱ���ʱ����Ƶ������ơ�0�����������1���ضϡ�"
        HI_U32 hdcp2x_audio_mute   : 2  ;//[2:1  ]  RW  0x0 "����Ƶ��δ��HDCP2.2���ܱ���ʱ����Ƶ������ơ�01����Ƶ������0��10����Ƶ���ݶ��������������������"
        HI_U32 hdcp1x_video_mute   : 1  ;//[3    ]  RW  0x0 "����Ƶ��δ��HDCP1.4���ܱ���ʱ����Ƶ������ơ�0�����������1���ضϡ�"
        HI_U32 hdcp1x_audio_mute   : 2  ;//[5:4  ]  RW  0x0 "����Ƶ��δ��HDCP1.4���ܱ���ʱ����Ƶ������ơ�01����Ƶ������0��10����Ƶ���ݶ��������������������"
        HI_U32 reserved            : 2  ;//[7:6  ]  RW  0x0 ������
        HI_U32 hdcp2p2_req         : 1  ;//[8    ]  RW  0x0 "Security �Ƿ�Ҫ��ֻ����hdcp2.2���ܡ�0����Ҫ��ֻ����hdcp2.2���ܣ�1��Ҫ��ֻ����hdcp2.2���ܡ�"
        HI_U32 hdcpx_req           : 1  ;//[9    ]  RW  0x0 "Security �Ƿ�Ҫ����hdcp2.2����hdcp1.4���ܡ�0����Ҫ����hdcp2.2����hdcp1.4���ܣ�1��Ҫ����hdcp2.2����hdcp1.4���ܡ�"
        HI_U32 downscale_check_v0  : 1  ;//[10   ]  RW  0x0 "VDP V0��downscale Checkʹ�ܿ��ơ�0��ʹ�ܣ�1����ʹ�ܡ�"
        HI_U32 downscale_check_v1  : 1  ;//[11   ]  RW  0x0 "VDP V1��downscale Checkʹ�ܿ��ơ�0��ʹ�ܣ�1����ʹ�ܡ�"
        HI_U32 hdmitx_sec_access_en: 1  ;//[12   ]  RW  0x0 "HDMI ��������������ʹ�ܼĴ�����0�������ְ�ȫ���ǰ�ȫ���ʣ�1�����ְ�ȫ���ǰ�ȫ���ʣ�˵����������Ϊ1ʱ���ǰ�ȫCPU���ܷ���HDMI�ڲ��ض��Ĵ�����"
        HI_U32 hdmitx_vdp_mute_en  : 1  ;//[13   ]  RW  0x0 "VDP����MUTEʹ�ܼĴ�����0�� ������1�� MUTE��"
        HI_U32 hdcp1x_apb_sec_en   : 1  ;//[14   ]  RW  0x0 "HDCP1.4 �Ĵ�����������ʹ�ܼĴ�����0�������ְ�ȫ���ǰ�ȫ���ʣ�1�����ְ�ȫ���ǰ�ȫ���ʡ�"
        HI_U32 hdcp2x_apb_sec_en   : 1  ;//[15   ]  RW  0x0 "HDCP2.2 �Ĵ�����������ʹ�ܼĴ�����0�������ְ�ȫ���ǰ�ȫ���ʣ�1�����ְ�ȫ���ǰ�ȫ���ʡ�"
        HI_U32 reserved1           : 15 ;//[31:16]  RW  0xF000  ������        
    }bits;

    HI_U32 u32;
    
}REG_PERI_HDMITX_AVCTTPT;

HI_VOID REG_HDMI_SEC_hdcp2x_video_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp2x_audio_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp1x_video_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp1x_audio_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp2p2_req_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcpx_req_Set(HI_U32);
HI_VOID REG_HDMI_SEC_downscale_check_v0_Set(HI_U32);
HI_VOID REG_HDMI_SEC_downscale_check_v1_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdmitx_sec_access_en_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp1x_apb_sec_en_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp2x_apb_sec_en_Set(HI_U32);

HI_U32 REG_HDMI_SEC_hdcp2x_video_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp2x_audio_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp1x_video_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp1x_audio_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp2p2_req_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcpx_req_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_downscale_check_v0_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_downscale_check_v1_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdmitx_sec_access_en_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp1x_apb_sec_en_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp2x_apb_sec_en_Get(HI_VOID);


#endif //__TEE_REG_HDMI_SEC_H__


