/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : cx_verify_api.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2016-01-15
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __CX_VERIFY_API_H__
#define __CX_VERIFY_API_H__

#include "hi_type.h"
#include "cx_verify_def.h"
#include "cx_adp.h"


/**
\brief  verify flash contents by partion name
CNcomment:����flash������У��flash����
\attention \n
����Ǽ��ܴ洢��flash�ľ��񣬻ᱻ�Ƚ��ܣ�Ȼ��У��ǩ������������ľ���ֱ��У��ǩ����
\param[in] pPartionName Flash partion name    CNcomment:pPartionName  flash ������
\param[in] u32RamAddr   RAM address for image CNcomment:pPartionName  ���image���ڴ��ַ
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pu32CodeAddr After Authenticate finished ,image address in DDR CNcomment:ImgInDDRAddress У����ɺ󣬿��þ�����DDR�е�λ��
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CX_VerifyFlashPartitionByName(HI_CHAR* pPartionName, HI_U32 u32RamAddr, HI_CA_AuthInfo_S *pstAuthInfo, HI_U32 *pu32CodeAddr);


/**
\brief  Verify flash contents by address of flash partion
CNcomment:����flash������ַУ��flash����
\attention \n
����Ǽ��ܴ洢��flash�ľ��񣬻ᱻ�Ƚ��ܣ�Ȼ��У��ǩ������������ľ���ֱ��У��ǩ����
\param[in] PartionAddr The address of flash partion       CNcomment:PartionAddr  flash ������ַ
\param[in] u32RamAddr   RAM address for image             CNcomment:pPartionName  ���image���ڴ��ַ
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pu32CodeAddr After Authenticate finished ,image address in DDR CNcomment:ImgInDDRAddress У����ɺ󣬿��þ�����DDR�е�λ��
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CX_VerifyFlashPartitionByAddr(HI_U32 PartionAddr,HI_U32 u32RamAddr, HI_CA_AuthInfo_S *pstAuthInfo, HI_U32 *pu32CodeAddr);



/**
\brief  Get image header structure by flash partition name
CNcomment:ͨ��flash���������ֻ�ȡimageͷ����Ϣ
\attention \n
\param[in] pPartionName Flash partion name                CNcomment:pPartionName  flash ������
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pstImgInfo  Image header info                 CNcomment:pstAuthInfo  ����ͷ����Ϣ
\param[out] pIsEncrypt  Is the image encrypted            CNcomment:ImgInDDRAddress �����Ƿ����
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CX_GetFlashImgInfoByName(HI_CHAR* pPartionName, HI_CA_AuthInfo_S *pstAuthInfo, HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt);

/**
\brief  Get image header structure by flash partition name
CNcomment:ͨ��flash���������ֻ�ȡimageͷ����Ϣ
\attention \n
\param[in] PartionAddr The address of flash partion       CNcomment:PartionAddr  flash ������ַ
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pstImgInfo  Image header info                 CNcomment:pstAuthInfo  ����ͷ����Ϣ
\param[out] pIsEncrypt  Is the image encrypted            CNcomment:ImgInDDRAddress �����Ƿ����
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CX_GetFlashImgInfoByAddr(HI_U32 PartionAddr, HI_CA_AuthInfo_S *pstAuthInfo, HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt);


/*
Verify initialization
*/
HI_S32 HI_CX_VerifyInit(HI_VOID);


#endif /*__CX_VERIFY_API_H__*/

