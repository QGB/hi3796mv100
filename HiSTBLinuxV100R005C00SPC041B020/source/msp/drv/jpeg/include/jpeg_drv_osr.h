/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_drv_osr.h
Version            : Initial Draft
Author            :
Created            : 2015/02/02
Description        : The user will use this api to realize some function
Function List     :


History           :
Date                Author                Modification
2015/02/02            y00181162              Created file
******************************************************************************/
#ifndef __JPEG_DRV_OSR_H__
#define __JPEG_DRV_OSR_H__


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

     #define CONFIG_JPEG_FIND_SYSTEM_ABNORMAL_TIMES   20

     /*************************** Enum Definition *********************************/

    /*************************** Structure Definition *****************************/
    /** jpeg device imformation */
    /** CNcomment:jpeg�豸��Ϣ */
    typedef struct hiJPG_OSRDEV_S
    {
        HI_BOOL bSuspendSignal;        /**< whether get suspend signal  *//**<CNcomment:��ȡ�����ź�         */
        HI_BOOL bResumeSignal;         /**< whether get resume signal   *//**<CNcomment:��ȡ���������ź�  */
        HI_BOOL bDecTask;              /**< whether have jpeg dec task  *//**<CNcomment:�Ƿ���jpeg��������    */
        HI_BOOL bLock;                 /**< �Ѿ�������״̬              **/
        HI_U32  SystemAbnormalTimes;
        wait_queue_head_t  QWaitInt;   /**< waite halt queue            **/
        wait_queue_head_t  QWaitMutex; /**< �ͷ��ź���                  **/
        JPG_INTTYPE_E       IntType;    /**< lately happened halt type  **/
     #ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
        HI_JPEG_OUTPUTINFO_S stOutputInfo;
     #endif
    }JPG_OSRDEV_S;

    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/


    /** @} */  /** <!-- ==== Structure Definition End ==== */

    /********************** Global Variable declaration **************************/

    /******************************* API declaration *****************************/

    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /***************************************************************************************
    * func          : DRV_JPEG_OffClock
    * description   : close the jpeg clock
                      CNcomment: �ر�jpegʱ�� CNend\n
    * param[in]     : HI_VOID
    * retval        : NA
    * others:       : NA
    ***************************************************************************************/
    HI_VOID DRV_JPEG_OffClock(HI_VOID);


    /***************************************************************************************
    * func          : DRV_JPEG_OnClock
    * description   : open the jpeg clock
                      CNcomment: ��jpegʱ�� CNend\n
    * param[in]     : HI_VOID
    * retval        : NA
    * others:       : NA
    ***************************************************************************************/
    HI_VOID DRV_JPEG_OnClock(HI_VOID);

    /** @} */  /** <!-- ==== API Declaration End ==== */

    /****************************************************************************/



#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_DRV_OSR_H__*/
