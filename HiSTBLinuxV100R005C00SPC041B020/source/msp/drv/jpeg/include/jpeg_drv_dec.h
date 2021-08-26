/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_drv_dec.c
Version            : Initial Draft
Author            :
Created            : 2016/02/03
Description        : ���ֻ����boot��OMX������ʹ�ã�������ʹ��
Function List     :


History           :
Date                Author                Modification
2016/02/03            y00181162              Created file
******************************************************************************/
#ifndef __JPEG_DRV_DEC_H__
#define __JPEG_DRV_DEC_H__


/*********************************add include here******************************/
#ifndef HI_BUILD_IN_BOOT
    #include <linux/syscalls.h>
    #include <linux/ipc.h>
#endif

#include "hi_jpeg_config.h"
#include "hi_drv_jpeg.h"
#include "hi_type.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */



     /***************************** Macro Definition ******************************/
     /** \addtogroup      JPEG */
     /** @{ */    /** <!--[JPEG]*/


     /** @} */  /** <!-- ==== Macro Definition end ==== */

     /*************************** Enum Definition ****************************/
    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /** @} */  /** <!-- ==== enum Definition end ==== */

    /*************************** Structure Definition ****************************/
    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /** @} */  /** <!-- ==== Structure Definition End ==== */

    /********************** Global Variable declaration **************************/

    /******************************* API declaration *****************************/

    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    #ifndef HI_BUILD_IN_BOOT
    /***************************************************************************************
     * func          : jpg_dec_getintstatus
     * description     :
                       CNcomment: ��ȡ�ж�״̬ CNend\n
     * param[in]     : irq
     * param[in]     : * devId
     * param[in]     : * ptrReg
     * retval         : HI_SUCCESS �ɹ�
     * retval         : HI_FAILURE ʧ��
     * others:         : NA
     ***************************************************************************************/
    HI_S32 JPEG_DRV_GetIntStatusValue(JPG_GETINTTYPE_S *pstIntType);

    /***************************************************************************************
     * func          : JPEG_DRV_SetDecState
     * description     : set dec state
                       CNcomment: ���ý���״̬ CNend\n
     * param[in]     : bDecState : ����״̬
     * others:         : NA
     ***************************************************************************************/
    HI_VOID JPEG_DRV_SetDecState(HI_BOOL bDecState);

    /***************************************************************************************
     * func          : JPEG_DRV_UnLock
     * description     : release dec mutex
                       CNcomment: �ͷŽ����ź��� CNend\n
     * param[in]     : eIntType : ����״̬
     * retval         : HI_SUCCESS �ɹ�
     * retval         : HI_FAILURE ʧ��
     * others:         : NA
     ***************************************************************************************/
    HI_VOID JPEG_DRV_UnLock(JPG_INTTYPE_E eIntType);


    /***************************************************************************************
     * func          : JPEG_DRV_Lock
     * description     : lock dec
                       CNcomment: ��״̬ CNend\n
     * retval         : HI_SUCCESS �ɹ�
     * retval         : HI_FAILURE ʧ��
     * others:         : NA
     ***************************************************************************************/
    HI_S32 JPEG_DRV_Lock(HI_VOID);


    /***************************************************************************************
     * func          : HI_DRV_JPEG_Init
     * description   : init drv dec struct information
     * others:       : NA
     ***************************************************************************************/
     HI_VOID HI_DRV_JPEG_Init(HI_VOID);

    #endif

    /** @} */  /** <!-- ==== API Declaration End ==== */

    /****************************************************************************/

#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_DRV_DEC_H__*/
