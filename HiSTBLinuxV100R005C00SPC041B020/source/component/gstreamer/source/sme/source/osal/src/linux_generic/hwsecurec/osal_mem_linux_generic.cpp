/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : vos_mem_android.cpp
  �� �� ��   : ����
  ��    ��   : l00180035
  ��������   : 2014��7��4��
  ����޸�   :
  ��������   : android/linuxƽ̨�ڴ������������(Ŀ��:��ͬ����ϵͳ���ܲ�ͬʵ�֣�
               �����漰����ȫ����ʱ)
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��4��
    ��    ��   : l00180035
    �޸�����   : �����ļ�

******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "osal_mem.h"

#include "securec.h"

#define VOS_STR_PRINT printf

//lint -e1784
//lint -e713 //pclint can not see the declaration of V_SIZE

VOS_API V_VOID*
VOS_Memset(INOUT V_VOID* pvSrcMem, IN V_INT32 i32Val, IN V_SIZE szLen)
{
    errno_t err;

    err = memset_s(pvSrcMem, szLen, i32Val, szLen);
    if(0 != err)
    {
        VOS_STR_PRINT("memset_s failed !\n");
        return NULL;
    }

    return pvSrcMem;
}

VOS_API V_VOID*
VOS_Memcpy(INOUT V_VOID* pvDstMem, IN const V_VOID* pvSrcMem, IN V_SIZE szLen)
{
    errno_t err;

    err = memcpy_s(pvDstMem, szLen, pvSrcMem, szLen);
    if(0 != err)
    {
        VOS_STR_PRINT("memcpy_s failed !\n");
        return NULL;
    }

    return pvDstMem;
}

VOS_API V_INT32
VOS_Memcmp(IN const V_VOID* pvSrcMem1, IN const V_VOID* pvSrcMem2, IN V_SIZE szLen)
{
    return memcmp(pvSrcMem1, pvSrcMem2, szLen);
}

VOS_API V_VOID*
VOS_Memmove(INOUT V_VOID* pvDstMem, IN const V_VOID* pvSrcMem, IN V_SIZE szLen)
{
    errno_t err;

    err = memmove_s(pvDstMem, szLen, pvSrcMem, szLen);
    if(0 != err)
    {
        VOS_STR_PRINT("memmove_s failed !\n");
        return NULL;
    }

    return pvDstMem;
}

//////////////////////////////////////////////////////////////////////////////
VOS_API E_SME_MEM_SECURE_RET
VOS_Memset_S(INOUT V_VOID* pvDestMem, IN V_SIZE szDestMax, IN V_INT32 i32Val, IN V_SIZE szCount)
{
    errno_t ret = memset_s(pvDestMem, szDestMax, i32Val, szCount);

    if (0 != ret)
    {
        VOS_STR_PRINT("SECURE_MEM failed, memset_s ret=%d(%#x) \n",
            ret, ret);
    }

    return (E_SME_MEM_SECURE_RET)ret;
}

VOS_API E_SME_MEM_SECURE_RET
VOS_Memcpy_S(INOUT V_VOID* pvDstMem, IN V_SIZE szDestMax, IN const V_VOID* pvSrcMem, IN V_SIZE szCount)
{
    errno_t ret = memcpy_s(pvDstMem, szDestMax, pvSrcMem, szCount);

    if (0 != ret)
    {
        VOS_STR_PRINT("SECURE_MEM failed, memcpy_s ret=%d(%#x) \n",
            ret, ret);
    }

    return (E_SME_MEM_SECURE_RET)ret;
}

VOS_API E_SME_MEM_SECURE_RET
VOS_Memmove_S(INOUT V_VOID* pvDstMem, IN V_SIZE szDestMax, IN const V_VOID* pvSrcMem, IN V_SIZE szCount)
{
    errno_t ret = memmove_s(pvDstMem, szDestMax, pvSrcMem, szCount);

    if (0 != ret)
    {
        VOS_STR_PRINT("SECURE_MEM failed, memmove_s ret=%d(%#x) \n",
            ret, ret);
    }

    return (E_SME_MEM_SECURE_RET)ret;
}
