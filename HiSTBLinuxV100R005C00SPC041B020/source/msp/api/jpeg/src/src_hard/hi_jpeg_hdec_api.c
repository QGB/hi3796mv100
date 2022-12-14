/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hi_jpeg_hdec_api.c
Version            : Initial Draft
Author            :
Created            : 2014/06/20
Description        : The user will use this api to realize some function
Function List     :


History           :
Date                Author                Modification
2014/06/20            y00181162              Created file
******************************************************************************/

/****************************  add include here     ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"
#include "jpeg_hdec_adp.h"
#include "hi_jpeg_api.h"
#include "hi_gfx_sys.h"

/***************************** Macro Definition     ***************************/

#define JPEG_CHECK_FD() \
    do {                                 \
        if(-1 == gs_s32JpegFd){          \
            return HI_FAILURE;          \
        }                                \
    } while (0)

/***************************** Structure Definition ***************************/

/********************** Global Variable declaration **************************/

#ifdef CONFIG_JPEG_OMX_FUNCTION

static HI_S32 gs_s32JpegFd  = -1;
static HI_S32 gs_s32JpegRef = 0;

#endif

/********************** API forward declarations    **************************/

/**********************       API realization       **************************/

/**
 \brief Sets dec output message. CNcomment:???????????????????????? CNend
 \attention \n
HI_JPEG_SetOutDesc should have called create jpeg decoder.set the output address \n
and output stride,set whether crop, set crop rect \n
CNcomment:???????????????????????????????????????????????????????????????????????? \n
          ?????????????????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    *pstSurfaceDesc. CNcomment:???????????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetOutDesc
 */

HI_S32  HI_JPEG_SetOutDesc(const struct jpeg_decompress_struct *cinfo,
                           const HI_JPEG_SURFACE_DESCRIPTION_S *pstSurfaceDesc)
{
    HI_S32 s32Cnt = 0;
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (NULL == pstSurfaceDesc)
    {
        return HI_FAILURE;
    }

    for (s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++)
    {
        pJpegHandle->stOutDesc.stOutSurface.u32OutPhy[s32Cnt]   = pstSurfaceDesc->stOutSurface.u32OutPhy[s32Cnt];
        pJpegHandle->stOutDesc.stOutSurface.pOutVir[s32Cnt]     = pstSurfaceDesc->stOutSurface.pOutVir[s32Cnt];
        pJpegHandle->stOutDesc.stOutSurface.u32OutStride[s32Cnt]= pstSurfaceDesc->stOutSurface.u32OutStride[s32Cnt];
    }

    pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem = pstSurfaceDesc->stOutSurface.bUserPhyMem;

    if (HI_TRUE == pstSurfaceDesc->bCrop)
    {
        if ( (pstSurfaceDesc->stCropRect.w <= 0)||(pstSurfaceDesc->stCropRect.h <= 0))
        {
            return HI_FAILURE;
        }
        pJpegHandle->stOutDesc.stCropRect.x = pstSurfaceDesc->stCropRect.x;
        pJpegHandle->stOutDesc.stCropRect.y = pstSurfaceDesc->stCropRect.y;
        pJpegHandle->stOutDesc.stCropRect.w = pstSurfaceDesc->stCropRect.w;
        pJpegHandle->stOutDesc.stCropRect.h = pstSurfaceDesc->stCropRect.h;
    }

    pJpegHandle->stOutDesc.bCrop = pstSurfaceDesc->bCrop;

    return HI_SUCCESS;

}

/**
 \brief Get Jpeg information. CNcomment:????jpeg???????? CNend
 \attention \n
if you want to get input format and input width and input height,you should set bOutInfo false.\n
others you can get the information as follows: output rgb widht/height/stride/size or output \n
yuvsp lu width/height/stride/size and ch width/height/stride/size.\n
you call this function should after read header and set the ouput parameter.\n
CNcomment:??bOutInfo??????FALSE????????????????????????????????????????????????????????????TRUE?? \n
          ??????????????????????????????????RGB????????????/????/??????/????,????????????yuvsp??\n
          ????????????????????????????/????/??????/???????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[out] pJpegInfo.    CNcomment:????jpeg??????????  CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetJpegInfo
 */
HI_S32  HI_JPEG_GetJpegInfo(j_decompress_ptr cinfo, HI_JPEG_INFO_S *pJpegInfo)
{
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

     if (NULL == cinfo)
     {
         JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
         return HI_FAILURE;
     }

     pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
     if (NULL == pJpegHandle)
     {
         JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
         return HI_FAILURE;
     }

     if (NULL == pJpegInfo)
     {
         return HI_FAILURE;
     }

     if (HI_FALSE == pJpegInfo->bOutInfo)
     {
         HI_GFX_Memset(pJpegInfo, 0, sizeof(HI_JPEG_INFO_S));
         pJpegInfo->u32Width[0]  = cinfo->image_width;
         pJpegInfo->u32Height[0] = cinfo->image_height;
         pJpegInfo->enFmt = pJpegHandle->enImageFmt;
         return HI_SUCCESS;
     }

     JPEG_HDEC_GetImagInfo(cinfo);

     /**
     ** output message,the output stride should 16byte align by tde request
     ** CNcomment: ???????? CNend\n
     **/
     switch (cinfo->out_color_space)
     {
         case JCS_YUV400_SP:
         case JCS_YUV444_SP:
         case JCS_YUV420_SP:
         case JCS_YUV422_SP_12:
         case JCS_YUV422_SP_21:
             pJpegInfo->u32Width[0]     = pJpegHandle->stJpegSofInfo.u32YWidth;
             pJpegInfo->u32Width[1]     = pJpegHandle->stJpegSofInfo.u32CWidth;
             pJpegInfo->u32Height[0]    = pJpegHandle->stJpegSofInfo.u32YHeight;
             pJpegInfo->u32Height[1]    = pJpegHandle->stJpegSofInfo.u32CHeight;
             pJpegInfo->u32McuHeight[0] = pJpegHandle->stJpegSofInfo.u32YMcuHeight;
             pJpegInfo->u32McuHeight[1] = pJpegHandle->stJpegSofInfo.u32CMcuHeight;
             pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.u32YStride;
             pJpegInfo->u32OutStride[1] = pJpegHandle->stJpegSofInfo.u32CbCrStride;
             pJpegInfo->u32OutSize[0]   = pJpegHandle->stJpegSofInfo.u32YSize;
             pJpegInfo->u32OutSize[1]   = pJpegHandle->stJpegSofInfo.u32CSize;
             break;
          default:
             pJpegInfo->u32Width[0]     = cinfo->output_width;
             pJpegInfo->u32Height[0]    = cinfo->output_height;
             pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.u32DisplayStride;
             pJpegInfo->u32OutSize[0]   = pJpegInfo->u32OutStride[0] * pJpegInfo->u32Height[0];
             break;
     }

     /**
     ** now use save dec width and height and stride and size.
     ** CNcomment: ???????????????????? CNend\n
     **/
     pJpegInfo->u32Width[2]     = pJpegHandle->stJpegSofInfo.u32DecW;
     pJpegInfo->u32Height[2]    = pJpegHandle->stJpegSofInfo.u32DecH;
     pJpegInfo->u32OutStride[2] = pJpegHandle->stJpegSofInfo.u32DecStride;
     pJpegInfo->u32OutSize[2]   = pJpegInfo->u32OutStride[2] * pJpegInfo->u32Height[2];

     return HI_SUCCESS;

}

/**
 \brief set jpeg dec inflexion. CNcomment:???????????????????????????????????????????? CNend
 \attention \n
HI_JPEG_SetInflexion should have called jpeg_create_decompress.if no call this \n
function,use the default flexion \n
CNcomment:?????????????????????????????????????????????????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    u32flexionSize. CNcomment:???????????????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetInflexion
 */
HI_S32 HI_JPEG_SetInflexion(const struct jpeg_decompress_struct *cinfo, const HI_U32 u32flexionSize)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    pJpegHandle->u32Inflexion = u32flexionSize;

    return HI_SUCCESS;
}

/**
 \brief get jpeg dec inflexion. CNcomment:???????????????????????? CNend
 \attention \n
HI_JPEG_GetInflexion should have called jpeg_create_decompress.\n
CNcomment:??????HI_JPEG_GetInflexion?????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[out] pu32flexionSize. CNcomment:???????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetInflexion
 */
HI_S32 HI_JPEG_GetInflexion(const struct jpeg_decompress_struct *cinfo, HI_U32 *pu32flexionSize)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (NULL == pu32flexionSize)
    {
        return HI_FAILURE;
    }

    *pu32flexionSize = pJpegHandle->u32Inflexion;

    return HI_SUCCESS;
}

/**
 \brief set jpeg dec coef when output argb. CNcomment:??????????ARGB???????????????????? CNend
 \attention \n
HI_JPEG_SetDecCoef should have called jpeg_create_decompress.set whether horizontal \n
and vertical fliter,whether set horizontal and ver sample, whether set csc coefficient, \n
and set there coefficient.if no call this function, use the default parameter. \n
CNcomment:???????????????????????????????????????????????????????????????????????????????? \n
          ??????????????????CSS???????????????????????????????????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    *pstDecCoef. CNcomment:???????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetDecCoef
 */
HI_S32 HI_JPEG_SetDecCoef(const struct jpeg_decompress_struct *cinfo, const HI_JPEG_DEC_COEF_S *pstDecCoef)
{
#ifdef CONFIG_JPEG_HARDDEC2ARGB
    HI_S32 s32Cnt1 = 0;
    HI_S32 s32Cnt2 = 0;

    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (NULL == pstDecCoef)
    {
        return HI_FAILURE;
    }

    pJpegHandle->stDecCoef.bEnHorMedian = pstDecCoef->bEnHorMedian;
    pJpegHandle->stDecCoef.bEnVerMedian = pstDecCoef->bEnVerMedian;
    pJpegHandle->stDecCoef.bSetHorSampleCoef = pstDecCoef->bSetHorSampleCoef;
    pJpegHandle->stDecCoef.bSetVerSampleCoef = pstDecCoef->bSetVerSampleCoef;
    pJpegHandle->stDecCoef.bSetCSCCoef = pstDecCoef->bSetCSCCoef;

    for(s32Cnt1 = 0; s32Cnt1 < MAX_HORCOEF_ROW; s32Cnt1++){
        for(s32Cnt2 = 0; s32Cnt2 < MAX_HORCOEF_COL; s32Cnt2++){
           pJpegHandle->stDecCoef.s16HorCoef[s32Cnt1][s32Cnt2] = pstDecCoef->s16HorCoef[s32Cnt1][s32Cnt2];
        }
    }
    for(s32Cnt1 = 0; s32Cnt1 < MAX_VERCOEF_ROW; s32Cnt1++){
        for(s32Cnt2 = 0; s32Cnt2 < MAX_VERCOEF_COL; s32Cnt2++){
           pJpegHandle->stDecCoef.s16VerCoef[s32Cnt1][s32Cnt2] = pstDecCoef->s16VerCoef[s32Cnt1][s32Cnt2];
        }
    }
    for(s32Cnt1 = 0; s32Cnt1 < MAX_CSCCOEF_ROW; s32Cnt1++){
        for(s32Cnt2 = 0; s32Cnt2 < MAX_CSCCOEF_COL; s32Cnt2++){
           pJpegHandle->stDecCoef.s16CSCCoef[s32Cnt1][s32Cnt2] = pstDecCoef->s16CSCCoef[s32Cnt1][s32Cnt2];
        }
    }

    return HI_SUCCESS;

#else
    if(NULL == cinfo || NULL == pstDecCoef)/** deal with warning **/
            return HI_FAILURE;
    else
            return HI_FAILURE;
#endif

}

/**
 \brief get jpeg dec coef when output argb. CNcomment:??????????ARGB?????????????????????????? CNend
 \attention \n
HI_JPEG_GetDecCoef should have called HI_JPEG_SetDecCoef.\n
CNcomment:??????HI_JPEG_GetDecCoef????????????HI_JPEG_SetDecCoef CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[out]    pstOutDecCoef. CNcomment:???????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetDecCoef
 */
#ifdef CONFIG_JPEG_HARDDEC2ARGB
HI_S32 HI_JPEG_GetDecCoef(const struct jpeg_decompress_struct *cinfo, HI_JPEG_DEC_COEF_S *pstOutDecCoef)
{
    HI_S32 s32Cnt1 = 0;
    HI_S32 s32Cnt2 = 0;

    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (NULL == pstOutDecCoef){
        return HI_FAILURE;
    }

    pstOutDecCoef->bEnHorMedian = pJpegHandle->stDecCoef.bEnHorMedian;
    pstOutDecCoef->bEnVerMedian = pJpegHandle->stDecCoef.bEnVerMedian;
    pstOutDecCoef->bSetHorSampleCoef = pJpegHandle->stDecCoef.bSetHorSampleCoef;
    pstOutDecCoef->bSetVerSampleCoef = pJpegHandle->stDecCoef.bSetVerSampleCoef;
    pstOutDecCoef->bSetCSCCoef = pJpegHandle->stDecCoef.bSetCSCCoef;

    for(s32Cnt1 = 0; s32Cnt1 < MAX_HORCOEF_ROW; s32Cnt1++){
        for(s32Cnt2 = 0; s32Cnt2 < MAX_HORCOEF_COL; s32Cnt2++){
           pstOutDecCoef->s16HorCoef[s32Cnt1][s32Cnt2] = pJpegHandle->stDecCoef.s16HorCoef[s32Cnt1][s32Cnt2];
        }
    }
    for(s32Cnt1 = 0; s32Cnt1 < MAX_VERCOEF_ROW; s32Cnt1++){
        for(s32Cnt2 = 0; s32Cnt2 < MAX_VERCOEF_COL; s32Cnt2++){
           pstOutDecCoef->s16VerCoef[s32Cnt1][s32Cnt2] = pJpegHandle->stDecCoef.s16VerCoef[s32Cnt1][s32Cnt2];
        }
    }
    for(s32Cnt1 = 0; s32Cnt1 < MAX_CSCCOEF_ROW; s32Cnt1++){
        for(s32Cnt2 = 0; s32Cnt2 < MAX_CSCCOEF_COL; s32Cnt2++){
           pstOutDecCoef->s16CSCCoef[s32Cnt1][s32Cnt2] = pJpegHandle->stDecCoef.s16CSCCoef[s32Cnt1][s32Cnt2];
        }
    }
    return HI_SUCCESS;

}
#else
HI_S32 HI_JPEG_GetDecCoef(const struct jpeg_decompress_struct *cinfo, HI_JPEG_DEC_COEF_S *pstOutDecCoef)
{
    UNUSED(cinfo);
    UNUSED(pstOutDecCoef);
    return HI_FAILURE;
}
#endif

/**
 \brief set alpha value. CNcomment:????alpha???? CNend
 \attention \n
HI_JPEG_SetAlpha should have called jpeg_create_decompress.when decode output \n
argb8888 and argb8888,we can call this function,if no call it,use the default value. \n
CNcomment:??????????????????????????????????????????????ARGB8888??ABGR8888?????????? \n
?????????????????????????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    s32Alpha. CNcomment:????alpha?? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetAlpha
 */
HI_S32 HI_JPEG_SetAlpha(const struct jpeg_decompress_struct *cinfo, const HI_U32 u32Alpha)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    pJpegHandle->u32Alpha = u32Alpha;

    return HI_SUCCESS;
}

/**
 \brief set stream from flag of use phy mem    or virtual mem. CNcomment:???????????????????????????? CNend
 \attention \n
if want to use this function,should call between create decompress and
jpeg_stdio_src or jpeg_mem_src.if not call this we should check\n
CNcomment:?????????????????????????????????????????????????????????????????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    pStreamPhyAddr. CNcomment:???????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetStreamPhyMem
 */
HI_S32 HI_JPEG_SetStreamPhyMem(const struct jpeg_decompress_struct *cinfo, HI_U32 u32StreamPhyAddr)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (0 == u32StreamPhyAddr)
    {
        return HI_FAILURE;
    }

    pJpegHandle->stHDecDataBuf.u32PhyBuf = u32StreamPhyAddr;
    pJpegHandle->stHDecDataBuf.bUserPhyMem = HI_TRUE;

    return HI_SUCCESS;
}

/**
 \brief set stream mem information. CNcomment:???????????????? CNend
 \attention \n
 if want to use this function,should call between create decompress and
 jpeg_stdio_src or jpeg_mem_src.if not call this we should check\n
 CNcomment:?????????????????????????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    pPhyStremBuf.         CNcomment:????buffer???????????? CNend
 \param[in]    u32StremBufLen.       CNcomment:????buffer????         CNend
 \param[in]    pVirSaveReturnBuf.    CNcomment:????buffer???????????? CNend
 \param[in]    s32StrmReturnSize.    CNcomment:????????????           CNend
 \param[in]    bStreamBufNeedReturn. CNcomment:????buffer????????     CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
 ::HI_JPEG_SetBufInfo
 */
HI_S32 HI_JPEG_SetBufInfo(const struct jpeg_decompress_struct *cinfo,HI_U32 u32StremBuf,HI_U32 u32StremBufLen, HI_CHAR* pVirSaveReturnBuf,HI_S32 s32StrmReturnSize,HI_BOOL bStreamBufNeedReturn)
{

    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (0 == u32StremBuf)
    {
        /** ???????????????????????????????????? **/
        return HI_FAILURE;
    }

#ifdef CONFIG_JPEG_STREAMBUF_4ALIGN
    if(0 != u32StremBuf % 4){/**????????4?????????????????? **/
        return HI_FAILURE;
    }
#endif
    pJpegHandle->stHDecDataBuf.u32StartBufPhy     = u32StremBuf;
    pJpegHandle->stHDecDataBuf.s32BufLen          = u32StremBufLen;
    pJpegHandle->stHDecDataBuf.pDataVirBufReturn  = pVirSaveReturnBuf;
    pJpegHandle->stHDecDataBuf.s32StreamReturnLen = s32StrmReturnSize;
    pJpegHandle->stHDecDataBuf.bNeedStreamReturn  = bStreamBufNeedReturn;

    return HI_SUCCESS;

}


/**
 \brief set if dec output yuv420sp. CNcomment:????????????????yuv420sp???? CNend
 \attention \n
HI_JPEG_SetYCbCr420spFlag should have called jpeg_create_decompress.\n
CNcomment:??????HI_JPEG_SetYCbCr420spFlag?????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    bOutYCbCr420sp. CNcomment:????????????????yuv420sp???? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetYCbCr420spFlag
 */
HI_S32 HI_JPEG_SetYCbCr420spFlag(const struct jpeg_decompress_struct *cinfo, const HI_BOOL bOutYCbCr420sp)
{
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    pJpegHandle->bOutYUV420SP = bOutYCbCr420sp;

    return HI_SUCCESS;

#else
    UNUSED(cinfo);
    UNUSED(bOutYCbCr420sp);

    return HI_FAILURE;
#endif

}

/**
 \brief set if output lu pixle sum value. CNcomment:?????????????????????? CNend
 \attention \n
HI_JPEG_SetLuPixSumFlag should have called jpeg_create_decompress.\n
CNcomment:??????HI_JPEG_SetLuPixSumFlag?????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[in]    bLuPixSum. CNcomment:?????????????????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetLuPixSumFlag
 */
HI_S32 HI_JPEG_SetLuPixSumFlag(const struct jpeg_decompress_struct *cinfo, HI_BOOL bLuPixSum)
{
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    pJpegHandle->bLuPixSum = bLuPixSum;

    return HI_SUCCESS;

#else
    UNUSED(cinfo);
    UNUSED(bLuPixSum);
    return HI_FAILURE;
#endif

}

/**
 \brief get lu pixle sum value. CNcomment:?????????? CNend
 \attention \n
If you want to get the luminance value, you can call this function, \n
but you should call it after jpeg_start_decompress and have call HI_JPEG_SetLuPixSumFlag.\n
CNcomment:??????????????????????????????????????????jpeg_start_decompress???????????????? \n
          ??????????HI_JPEG_SetLuPixSumFlag CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[out] u64LuPixSum. CNcomment:?????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetLuPixSum
 */
HI_S32 HI_JPEG_GetLuPixSum(const struct jpeg_decompress_struct *cinfo, HI_U64 *u64LuPixSum)

{
    if (NULL == u64LuPixSum){
        return HI_FAILURE;
    }

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (HI_TRUE == pJpegHandle->bLuPixSum)
    {
        *u64LuPixSum = pJpegHandle->u64LuPixValue;
    }

    return HI_SUCCESS;

#else
    UNUSED(cinfo);
    *u64LuPixSum = 0;
    return HI_FAILURE;
#endif

}

/**
 \brief get jpeg dec time. CNcomment:????jpeg???????? CNend
 \attention \n
If you want to know how much the decode cost time ,you can call HI_JPEG_GetDecTime, \n
but should have called it after jpeg_finish_decompress.\n
CNcomment:?????????????????????????????????????????????????????????????????? CNend\n

 \param[in]    cinfo. CNcomment:???????? CNend
 \param[out] pu32DecTime. CNcomment:???????????????? CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetDecTime
 */
HI_S32 HI_JPEG_GetDecTime(const struct jpeg_decompress_struct *cinfo, HI_U32 *pu32DecTime)
{
#ifdef CONFIG_JPEG_GETDECTIME

    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (NULL == pu32DecTime)
    {
        return HI_FAILURE;
    }

    *pu32DecTime = pJpegHandle->u32DecTime;

    return HI_SUCCESS;

#else
    UNUSED(cinfo);
    UNUSED(pu32DecTime);

    return HI_FAILURE;

#endif
}


/**
\brief set the leave memory size. CNcomment:?????????????????????????????? CNend
\attention \n
should have called it after  create jpeg decoder.\n
CNcomment:???????????????????????? CNend\n

\param[in]    cinfo. CNcomment:???????? CNend
\param[int] sMemSizeInfo. CNcomment:???????? CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_JPEG_SetLeaveMemSize
*/
HI_S32 HI_JPEG_SetLeaveMemSize(const struct jpeg_decompress_struct *cinfo, HI_JPEG_MEMSIZE_INFO_S sMemSizeInfo)
{

    HI_U32 u32MemSize = 0;
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    switch (sMemSizeInfo.eCheckType)
    {
        case JPEG_MEMCHECK_MEMSIZE:
            u32MemSize = sMemSizeInfo.u32MemSize;
            break;
        case JPEG_MEMCHECK_RESOLUTION:
            u32MemSize = sMemSizeInfo.u32Width * sMemSizeInfo.u32Height * 4;
            break;
        default:
            break;
    }

    pJpegHandle->u32LeaveMemSize = u32MemSize;

    return HI_SUCCESS;

}

/**
\brief set low delay information. CNcomment:?????????????? CNend
\attention the s32LineNum value should in [1 ~ output height]\n
NA.\n
CNcomment:CNend\n

\param[in]    cinfo.         CNcomment:????????                     CNend
\param[in]    u32PhyLineBuf. CNcomment:????????????????             CNend
\param[in]    pVirLineBuf.   CNcomment:????????????????             CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_JPEG_SetLowDelayInf
*/
HI_S32 HI_JPEG_SetLowDelayInf(const struct jpeg_decompress_struct *cinfo, HI_U32 u32PhyLineBuf, HI_CHAR* pVirLineBuf)
{
#ifndef CONFIG_JPEG_LOW_DELAY_SUPPORT
    UNUSED(cinfo);
    UNUSED(u32PhyLineBuf);
    UNUSED(pVirLineBuf);
    return HI_FAILURE;
#else
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

    if (NULL == cinfo)
    {
        return HI_FAILURE;
    }

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (NULL == pVirLineBuf || 0 == u32PhyLineBuf)
    {
        pJpegHandle->bLowDelayEn   = HI_FALSE;
        pJpegHandle->u32PhyLineBuf = 0;
        pJpegHandle->pVirLineBuf   = NULL;
        return HI_FAILURE;
    }
    /** only support yuv sp that output color space **/
    pJpegHandle->bLowDelayEn   = HI_TRUE;
    pJpegHandle->u32PhyLineBuf = u32PhyLineBuf;
    pJpegHandle->pVirLineBuf   = pVirLineBuf;
    return HI_SUCCESS;
#endif
}

/**
\brief open jpeg device. CNcomment:????jpeg???? CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  NULL. CNcomment:???????????? CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_JPEG_Open
*/
HI_S32 HI_JPEG_Open(HI_VOID)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION

    if (-1 != gs_s32JpegFd){
        gs_s32JpegRef++;
        return HI_SUCCESS;
    }

    gs_s32JpegFd = open(JPG_DEV, O_RDWR | O_SYNC);
    if (gs_s32JpegFd < 0){
        return HI_FAILURE;
    }
    gs_s32JpegRef++;

    return HI_SUCCESS;
#else
    return HI_FAILURE;
#endif
}

/**
\brief close jpeg device. CNcomment:????jpeg???? CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  NULL. CNcomment:???????????? CNend

\retval ::NA
\retval ::NA

\see \n
::HI_JPEG_Close
*/
HI_VOID HI_JPEG_Close(HI_VOID)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION
   if (-1 == gs_s32JpegFd){
        return;
    }
    gs_s32JpegRef--;

    if(gs_s32JpegRef > 0){
        return ;
    }else{
        gs_s32JpegRef = 0;
    }

    close(gs_s32JpegFd);

    gs_s32JpegFd = -1;

#endif

    return;
}



HI_S32 HI_JPEG_CreateDec(HI_U32 *pDecHandle)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION
    HI_U32 DecHandle = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();

    if (NULL == pDecHandle)
    {
       return HI_FAILURE;
    }

    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_CREATEDEC, &DecHandle);
    if (HI_SUCCESS != s32Ret)
    {
        JPEG_TRACE("=====HI_JPEG_CreateDec failure\n");
        return HI_FAILURE;
    }

    *pDecHandle = DecHandle;

    return HI_SUCCESS;
#else
    UNUSED(pDecHandle);
    return HI_FAILURE;
#endif

}


HI_S32 HI_JPEG_DecInfo(HI_U32 DecHandle,HI_JPEG_INMSG_S *stInMsg)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION
    HI_DRV_JPEG_INMSG_S stImgInfo;
    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();

    if (NULL == stInMsg)
    {
        return HI_FAILURE;
    }

    HI_GFX_Memset(&stImgInfo,0,sizeof(HI_DRV_JPEG_INMSG_S));

    stImgInfo.u32AllPhy      = stInMsg->u32AllPhy;
    stImgInfo.u32SavePhy     = stInMsg->u32SavePhy;
    stImgInfo.u64SaveVir[0]  = (HI_U64)(unsigned long)stInMsg->pSaveVir[0];
    stImgInfo.u64SaveVir[1]  = (HI_U64)(unsigned long)stInMsg->pSaveVir[1];
    stImgInfo.u32AllLen      = stInMsg->u32AllLen;
    stImgInfo.u32SaveLen[0]  = stInMsg->u32SaveLen[0];
    stImgInfo.u32SaveLen[1]  = stInMsg->u32SaveLen[1];
    stImgInfo.s32InWidth     = stInMsg->s32InWidth;
    stImgInfo.s32InHeight    = stInMsg->s32InHeight;
    stImgInfo.bUserPhyMem    = stInMsg->bUserPhyMem;
    stImgInfo.enInFmt        = (JPG_FMT_E)stInMsg->enInFmt;
    stImgInfo.DecHandle      = DecHandle;

    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DECINFO, &stImgInfo);
    if (HI_SUCCESS != s32Ret)
    {
        JPEG_TRACE("=====HI_JPEG_DecInfo failure\n");
        return HI_FAILURE;
    }

    stInMsg->s32InWidth  = stImgInfo.s32InWidth;
    stInMsg->s32InHeight = stImgInfo.s32InHeight;
    stInMsg->enInFmt     = (HI_JPEG_FMT_E)stImgInfo.enInFmt;

    return HI_SUCCESS;
#else
    UNUSED(DecHandle);
    UNUSED(stInMsg);
    return HI_FAILURE;
#endif
}


HI_S32 HI_JPEG_DecOutInfo(HI_U32 DecHandle,HI_JPEG_OUTMSG_S *stOutMsg)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION
    HI_DRV_JPEG_OUTMSG_S stOutInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Cnt = 0;

    JPEG_CHECK_FD();

    if (NULL == stOutMsg)
    {
        return HI_FAILURE;
    }

    HI_GFX_Memset(&stOutInfo,0,sizeof(HI_DRV_JPEG_OUTMSG_S));

    for (s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++)
    {
        stOutInfo.u32OutPhy[s32Cnt]     = stOutMsg->u32OutPhy[s32Cnt];
        stOutInfo.u32OutVir[s32Cnt]     = stOutMsg->u32OutVir[s32Cnt];
        stOutInfo.u32OutWidth[s32Cnt]   = stOutMsg->u32OutWidth[s32Cnt];
        stOutInfo.u32OutHeight[s32Cnt]  = stOutMsg->u32OutHeight[s32Cnt];
        stOutInfo.u32OutStride[s32Cnt]  = stOutMsg->u32OutStride[s32Cnt];
        stOutInfo.u32OutSize[s32Cnt]    = stOutMsg->u32OutSize[s32Cnt];
    }
    stOutInfo.s32Scale      = stOutMsg->s32Scale;
    stOutInfo.bOutYuvSp420  = stOutMsg->bOutYuvSp420;
    stOutInfo.bLuPixSum     = stOutMsg->bLuPixSum;
    stOutInfo.enOutFmt      = (JPG_FMT_E)stOutMsg->enOutFmt;
    stOutInfo.DecHandle     = DecHandle;

    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DECOUTINFO, &stOutInfo);
    if (HI_SUCCESS != s32Ret){
        JPEG_TRACE("=====HI_JPEG_DecOutInfo failure\n");
        return HI_FAILURE;
    }
    for (s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++){
        stOutMsg->u32OutWidth[s32Cnt]  = stOutInfo.u32OutWidth[s32Cnt];
        stOutMsg->u32OutHeight[s32Cnt] = stOutInfo.u32OutHeight[s32Cnt];
        stOutMsg->u32OutStride[s32Cnt] = stOutInfo.u32OutStride[s32Cnt];
        stOutMsg->u32OutSize[s32Cnt]   = stOutInfo.u32OutSize[s32Cnt];
    }
    stOutMsg->enOutFmt = (HI_JPEG_FMT_E)stOutInfo.enOutFmt;

    return HI_SUCCESS;
#else
    UNUSED(DecHandle);
    UNUSED(stOutMsg);
    return HI_FAILURE;
#endif
}


HI_S32 HI_JPEG_Decode(HI_U32 DecHandle,HI_JPEG_INMSG_S *stInMsg,HI_JPEG_OUTMSG_S *stOutMsg)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION
    HI_JPEG_DECINFO_S stDecInfo;
    HI_S32 s32Cnt = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();

    if ((NULL == stInMsg) || (NULL == stOutMsg))
    {
        return HI_FAILURE;
    }

    HI_GFX_Memset(&stDecInfo,0,sizeof(HI_JPEG_DECINFO_S));

    stDecInfo.stInMsg.u32AllPhy      = stInMsg->u32AllPhy;
    stDecInfo.stInMsg.u32SavePhy     = stInMsg->u32SavePhy;
    stDecInfo.stInMsg.u64SaveVir[0]  = (HI_U64)(unsigned long)stInMsg->pSaveVir[0];
    stDecInfo.stInMsg.u64SaveVir[1]  = (HI_U64)(unsigned long)stInMsg->pSaveVir[1];
    stDecInfo.stInMsg.u32AllLen      = stInMsg->u32AllLen;
    stDecInfo.stInMsg.u32SaveLen[0]  = stInMsg->u32SaveLen[0];
    stDecInfo.stInMsg.u32SaveLen[1]  = stInMsg->u32SaveLen[1];
    stDecInfo.stInMsg.s32InWidth     = stInMsg->s32InWidth;
    stDecInfo.stInMsg.s32InHeight    = stInMsg->s32InHeight;
    stDecInfo.stInMsg.bUserPhyMem    = stInMsg->bUserPhyMem;
    stDecInfo.stInMsg.enInFmt        = (JPG_FMT_E)stInMsg->enInFmt;
    stDecInfo.stInMsg.DecHandle      = DecHandle;

    for (s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++)
    {
        stDecInfo.stOutMsg.u32OutPhy[s32Cnt]     = stOutMsg->u32OutPhy[s32Cnt];
        stDecInfo.stOutMsg.u32OutVir[s32Cnt]     = stOutMsg->u32OutVir[s32Cnt];
        stDecInfo.stOutMsg.u32OutWidth[s32Cnt]   = stOutMsg->u32OutWidth[s32Cnt];
        stDecInfo.stOutMsg.u32OutHeight[s32Cnt]  = stOutMsg->u32OutHeight[s32Cnt];
        stDecInfo.stOutMsg.u32OutStride[s32Cnt]  = stOutMsg->u32OutStride[s32Cnt];
        stDecInfo.stOutMsg.u32OutSize[s32Cnt]    = stOutMsg->u32OutSize[s32Cnt];
    }
    stDecInfo.stOutMsg.s32Scale      = stOutMsg->s32Scale;
    stDecInfo.stOutMsg.bOutYuvSp420  = stOutMsg->bOutYuvSp420;
    stDecInfo.stOutMsg.bLuPixSum     = stOutMsg->bLuPixSum;
    stDecInfo.stOutMsg.enOutFmt      = (JPG_FMT_E)stOutMsg->enOutFmt;
    stDecInfo.stOutMsg.DecHandle     = DecHandle;

    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DECODE, &stDecInfo);
    if (HI_SUCCESS != s32Ret)
    {
        JPEG_TRACE("=====CMD_JPG_DECODE failure\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
#else
    UNUSED(DecHandle);
    UNUSED(stInMsg);
    UNUSED(stOutMsg);
    return HI_FAILURE;
#endif

}


HI_S32 HI_JPEG_GetOmxLuPixSum(HI_U32 DecHandle,HI_U64 *u64LuPixSum)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION
    HI_DRV_JPEG_OUTMSG_S stOutInfo;
    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();

    if (NULL == u64LuPixSum)
    {
        return HI_FAILURE;
    }

    HI_GFX_Memset(&stOutInfo,0,sizeof(HI_DRV_JPEG_OUTMSG_S));

    stOutInfo.DecHandle = DecHandle;

    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_GETLUPIXSUM, &stOutInfo);
    if (HI_SUCCESS != s32Ret){
        JPEG_TRACE("=====HI_JPEG_GetOmxLuPixSum failure\n");
        return HI_FAILURE;
    }
    *u64LuPixSum  = stOutInfo.u64LuPixValue;

    return HI_SUCCESS;
#else
    UNUSED(DecHandle);
    UNUSED(u64LuPixSum);
    return HI_FAILURE;
#endif
}


HI_S32 HI_JPEG_DestoryDec(HI_U32 DecHandle)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION
    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();

    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DESTORYDEC,&DecHandle);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;

#else
    UNUSED(DecHandle);

    return HI_FAILURE;
#endif

}
