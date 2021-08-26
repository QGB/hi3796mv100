/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : osal_type.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2011��9��28��
  ����޸�   :
  ��������   : �ն����ƽ̨�����Ͷ���Ĺ���ͷ�ļ�
  �����б�   : ��
  �޸���ʷ   : ��
  1.��    ��   : 2011��9��28��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OSAL_TYPE_H__
#define __OSAL_TYPE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>

/*----------------------------------------------*
 * �����ض���                                     *
 *----------------------------------------------*/

typedef char V_CHAR;
typedef unsigned char V_UCHAR;
typedef char V_INT8;
typedef unsigned char V_UINT8;
typedef short int V_INT16;
typedef unsigned short int V_UINT16;
typedef int V_INT32;
typedef unsigned int V_UINT32;
typedef long long int V_INT64;
typedef unsigned long long int V_UINT64;

typedef long V_LONG;
typedef unsigned long V_ULONG;

typedef float V_FLOAT;
typedef double V_DOUBLE;
typedef void V_VOID;

#ifdef __PC_LINT__
#define V_SIZE V_UINT32
#else
typedef size_t V_SIZE;
#endif



#ifdef __cplusplus
typedef bool V_BOOL;
#else
typedef unsigned char V_BOOL;
#endif

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#ifndef IN
#define IN
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef OUT
#define OUT
#endif

#ifndef ICS_FALSE
#ifdef __cplusplus
#define ICS_FALSE false
#else
#define ICS_FALSE ((V_BOOL)0)
#endif
#endif

#ifndef ICS_TRUE
#ifdef __cplusplus
#define ICS_TRUE true
#else
#define ICS_TRUE ((V_BOOL)1)
#endif
#endif

/*----------------------------------------------*
 * ���������붨��                               *
 *----------------------------------------------*/
#ifndef ICS_SUCCESS
#define ICS_SUCCESS 0
#endif

#ifndef ICS_FAIL
#define ICS_FAIL 1
#endif

#ifndef ICS_INVALID_PARA
#define ICS_INVALID_PARA 0x00000002
#endif

#ifdef WIN32

#ifndef ut_virtual
#define ut_virtual virtual
#endif

#ifndef ut_protected
#define ut_protected public
#endif

#ifndef ut_private
#define ut_private public
#endif

#else

#ifndef ut_virtual
#define ut_virtual
#endif

#ifndef ut_protected
#define ut_protected protected
#endif

#ifndef ut_private
#define ut_private private
#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ICS_TYPE_H__ */

