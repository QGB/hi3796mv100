/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : vos_mem.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2014��7��4��
  ����޸�   :
  ��������   : �ڴ������������(Ŀ��:��ͬ����ϵͳ���ܲ�ͬʵ�֣������漰����ȫ����ʱ)
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��4��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OSAL_MEM__
#define __OSAL_MEM__

#include "osal_type.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifdef WIN32
#ifdef VOSDLL_EXPORTS
#define VOS_API /*__declspec(dllexport)*/
#else
#define VOS_API /*__declspec(dllimport)*/
#endif
#else
#define VOS_API
#endif


/*****************************************************************************
 �� �� ��  : VOS_Memset
 ��������  : ���ڴ�鸳ֵ��
 �������  : V_VOID* pvSrcMem :Ҫ��ֵ���ڴ�ָ��,����ΪNULL�����򲻿�Ԥ֪�����
                               ����crash��
             V_INT32 i32Val   :�ڴ��ÿ���ֽ�Ҫ����ֵ��
             V_SIZE szLen     :��ֵ�ĳ��ȣ��ֽ�����
 �������  : V_VOID* pvSrcMem :Ҫ��ֵ���ڴ�ָ�롣
 �� �� ֵ  : ����ָ��pvSrcMem�ڴ���׵�ָ�롣
 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID*
VOS_Memset(INOUT V_VOID* pvSrcMem, IN V_INT32 i32Val, IN V_SIZE szLen);

/*****************************************************************************
 �� �� ��  : VOS_Memcpy
 ��������  : �ڴ濽��,pvDstMem��pvSrcMem�����е�ַ�ص���
 �������  : V_VOID* pvDstMem       :Ŀ���ڴ�ָ�룬����ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
             const V_VOID* pvSrcMem :Դ�ڴ�ָ�룬����ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
             V_SIZE szLen           :�����ĳ��ȣ��ֽ�����
 �������  : V_VOID* pvDstMem       :Ŀ���ڴ�ָ�룬����ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
 �� �� ֵ  : ����ָ��DstMem�ڴ���ָ�롣
 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID*
VOS_Memcpy(INOUT V_VOID* pvDstMem, IN const V_VOID* pvSrcMem, IN V_SIZE szLen);

/*****************************************************************************
 �� �� ��  : VOS_Memcmp
 ��������  : �ڴ�Ƚ�,pvSrcMem1��pvSrcMem2,�����ַ������pvSrcMem1-pvSrcMem2��
 �������  : const V_VOID* pvSrcMem1:Ҫ�Ƚϵ��ڴ�1������ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
             const V_VOID* pvSrcMem2:Ҫ�Ƚϵ��ڴ�2������ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
             V_SIZE szLen           :Ҫ�Ƚϵĳ��ȣ��ֽ�����
 �������  : NULL.
 �� �� ֵ  : 0,�Ƚϵ��ڴ�һ��;����,pvSrcMem1-pvSrcMem2,�����ַ�����Ľ����
 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_INT32
VOS_Memcmp(IN const V_VOID* pvSrcMem1, IN const V_VOID* pvSrcMem2, IN V_SIZE szLen);

/*****************************************************************************
 �� �� ��  : VOS_Memmove
 ��������  : �ڴ濽��,pvDstMem��pvSrcMem�����е�ַ�ص���
 �������  : V_VOID* pvDstMem       :Ŀ���ڴ�ָ�룬����ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
             const V_VOID* pvSrcMem :Դ�ڴ�ָ�룬����ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
             V_SIZE szLen           :�����ĳ��ȣ��ֽ�����
 �������  : V_VOID* pvDstMem       :Ŀ���ڴ�ָ�룬����ΪNULL�����򲻿�Ԥ֪�����
                                     ����crash��
 �� �� ֵ  : ����ָ��DstMem�ڴ���ָ�롣
 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID*
VOS_Memmove(INOUT V_VOID* pvDstMem, IN const V_VOID* pvSrcMem, IN V_SIZE szLen);

/////////////////////////////////////////////////////////////////////////////////////////////////////
// For security function start.

typedef enum _MemSecureRet
{
    E_SME_MEM_OK = 0,
    E_SME_MEM_ERANGE = 34,
    E_SME_MEM_EINVAL = 22,
    E_SME_MEM_EINVAL_AND_RESET = 150,
    E_SME_MEM_ERANGE_AND_RESET = 162,
    E_SME_MEM_EOVERLAP_AND_RESET = 182,
} E_SME_MEM_SECURE_RET;

// return value:
//   =0:      succeed.
//   >0:      failed; detailed information, refer to "secure function library manual".

VOS_API E_SME_MEM_SECURE_RET
VOS_Memset_S(INOUT V_VOID* pvDestMem, IN V_SIZE szDestMax, IN V_INT32 i32Val, IN V_SIZE szCount);

VOS_API E_SME_MEM_SECURE_RET
VOS_Memcpy_S(INOUT V_VOID* pvDstMem, IN V_SIZE szDestMax, IN const V_VOID* pvSrcMem, IN V_SIZE szCount);

VOS_API E_SME_MEM_SECURE_RET
VOS_Memmove_S(INOUT V_VOID* pvDstMem, IN V_SIZE szDestMax, IN const V_VOID* pvSrcMem, IN V_SIZE szCount);

// For security function end.
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif// __OSAL_MEM__
