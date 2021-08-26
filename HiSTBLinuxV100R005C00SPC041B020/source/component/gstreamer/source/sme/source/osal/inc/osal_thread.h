/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : vos_thread.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2012��9��11��
  ����޸�   :
  ��������   : vos �̣߳����⣬����ͬ����˯�ߣ�ϵͳʱ��ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OSAL_THREAD__
#define __OSAL_THREAD__
#include <stdio.h>
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

/* ��Ч��� */
#define VOS_INVALIDE_THD_HANDLE (VOSTHDHDL)NULL

/* �߳̾������ */
typedef V_VOID* VOSTHDHDL;

/* ����������� */
typedef V_VOID* VOSCONDHDL;

/* �߳�ID */
typedef unsigned long VOS_TID_T;

/* ����ID */
typedef unsigned long VOS_PID_T;

/* �߳����� */
typedef struct _tag_VOSThdAttr
{
    V_INT32 i32StackSize;  //ջ��С��Ĭ��Ϊϵͳ�Զ�����,����עʱ���ó�С��0
    V_INT32 i32Sched;      //���Ȳ��ԣ������E_VOS_THD_SCHED
    V_INT32 i32Prioty;     //���ȼ��������E_VOS_THD_PRI
}ST_VOS_THDATTR,PST_VOS_THDATTR;

/* INOUT V_VOID* pvCtx:���룬Ϊ���߳������� */
typedef V_UINT32 (*PFNVOSTHD)(INOUT V_VOID* pvCtx);

/* �̵߳��Ȳ��� */
typedef enum _tag_VosThdSched
{
    E_VOS_THD_SCHED_INVALID = -1,  // ��Ч
    E_VOS_THD_SCHED_OTHER = 0,     // Ĭ�ϵ���
    E_VOS_THD_SCHED_FIFO,          // ʵʱ���Ƚ��ȳ�
    E_VOS_THD_SCHED_RR,            // ʵʱ��ʱ����ѯʽ
}E_VOS_THD_SCHED;

/* �߳����ȼ��ȼ�,��Χ��E_VOS_THD_PRI_INVALID ~ E_VOS_THD_PRI_BUTT֮�䣬��1~99
 * �����ȼ����ν���
 * �����E_VOS_THD_PRI_HIGHEST �� E_VOS_THD_PRI_LOWEST֮��ĺ궨��ĵȼ� */
typedef enum _tag_VosThdPriority
{
    E_VOS_THD_PRI_INVALID = 0,  //����עʱ���óɸ�ֵ
    E_VOS_THD_PRI_HIGH = 95,
    E_VOS_THD_PRI_ABOVE_NORMAL,
    E_VOS_THD_PRI_NORMAL,
    E_VOS_THD_PRI_BELOW_NORMAL,
    E_VOS_THD_PRI_LOWEST,
    E_VOS_THD_PRI_BUTT,
}E_VOS_THD_PRI;

/* ����ֵ */
typedef enum _tag_VOSThdERR
{
    E_VOS_THD_ERR_NONE = ICS_SUCCESS,   //�ɹ�
    E_VOS_THD_ERR_ARGS = ICS_FAIL + 1,  //��������
    E_VOS_THD_ERR_NOMORE_RES,           //û��Դ��,�����ĸ�����Դ����ϵͳ���,������
    E_VOS_THD_ERR_THD_DEAD_LOCK,        //�߳����������Լ����Լ���
    E_VOS_THD_ERR_COND_TIMEOUT,         //����ͬ���ȴ���ʱ
    E_VOS_THD_ERR_UNKOWN,               //δ֪����
    E_VOS_THD_ERR_NOTSUPPORT,           //��֧��
    E_VOS_THD_ERR_LOCK,
    E_VOS_THD_ERR_UNLOCK,
    E_VOS_THD_ERR_COND_SIGNAL,
    E_VOS_THD_ERR_COND_WAIT,
    E_VOS_THD_ERR_FAIL,                 //ʧ��
}E_VOS_THD_ERR;

/* �������� */
typedef struct _tag_VOSthread_mutexattr
{
     V_UINT32 u32Reserve;  //������������չ.//androidƽ̨u32ReserveΪ��0ʱ�ǵݹ���
}ST_VOS_THD_MUTEX_ATTR;

/* ����ṹ */
typedef struct _tag_VOSThread_Mutex
{
    V_UINT32 u32Res[16];
}ST_VOS_THD_MUTEX, *PST_VOS_THD_MUTEX;

/* ����ͬ������ */
typedef struct _tag_VOSthread_condattr
{
     V_UINT32 u32Reserve;  //����
}ST_VOS_THD_COND_ATTR;

/* ����ʱ�� */
typedef struct _tagVOS_SysTime
{
    V_UINT32 u32MilliSec;  //����
    V_UINT32 u32Sec;       //��
    V_UINT32 u32Min;       //��
    V_UINT32 u32Hour;      //ʱ
    V_UINT32 u32Day;       //��
    V_UINT32 u32Mon;       //��
    V_UINT32 u32Year;      //��
}ST_VOS_SYSTIME, *PST_VOS_SYSTIME;

/* EVENT */
typedef V_VOID* VOSEVENTHDL;

/* ��Ч��� */
#define VOS_INVALIDE_EVENT_HANDLE (VOSEVENTHDL)NULL

/* Semaphore���� */
typedef struct _tag_VOSEventAttr
{
     V_UINT32 u32Reserve;  //����
}ST_VOS_THD_EVENT_ATTR;

/* �ź��� */
typedef V_VOID* VOSSEMHDL;


/*****************************************************************************
 �� �� ��  : VOS_CreateThread
 ��������  : �����߳�
 �������  : IN const ST_VOS_THDATTR* stAttr:�߳����ԣ��ṹ���ṹ�嶨�壬
                                             ��ѡ����������ע�ɴ���NULL
             IN const PFNVOSTHD pfnThd:�߳��庯��ָ�룬���봫�����ʧ��
             INOUT V_VOID* pvCtx:�߳��庯�������ģ��߳��庯���Ĳ�������ѡ��
                                 ����ע�ɴ���NUL
 �������  : OUT VOSTHDHDL* pThdHdl:�߳̾��ָ�룬�̷߳��سɹ�����㣬����Ϊ0
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_NOMORE_RES:�������߳������࣬���δ������ɹ���������.
                      E_VOS_THD_ERR_ARGS: �������Դ�������߳��庯��ָ��ΪNULL
                      E_VOS_THD_ERR_UNKOWN:δ֪����
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_CreateThread(OUT VOSTHDHDL* pThdHdl,
                        IN const ST_VOS_THDATTR* pstAttr,
                        IN const PFNVOSTHD pfnThd,
                        INOUT V_VOID* pvCtx);

/*****************************************************************************
 �� �� ��  : VOS_DetachThread
 ��������  : �߳�������̷߳��룬��������߳��˳�ʱ���߳���ȫ���٣�
             �����߳��˳����ܾ�ȷ����
 �������  : IN VOSTHDHDL hThdHdl:�߳̾����VOS_CreateThread��һ���������ֵ
 �������  : ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_FAIL: ʧ��
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_DetachThread(IN VOSTHDHDL hThdHdl);

/*****************************************************************************
 �� �� ��  : VOS_JoinThread
 ��������  : ͬ���ȴ��߳��˳�
 �������  : INOUT VOSTHDHDL hThdHdl:�߳̾����VOS_CreateThread��һ���������ֵ
 �������  : ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_FAIL: ʧ��
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_JoinThread(INOUT VOSTHDHDL hThdHdl);

/*****************************************************************************
 �� �� ��  : VOS_SetThreadPriority
 ��������  : ��̬�����߳����ȼ�
 �������  : IN VOSTHDHDL hThdHdl:Ҫ���õ��߳̾����ͨ��VOS_CreateThread��õ�
             IN V_INT32 i32Sched:Ҫ���õĵ��Ȳ��ԣ���E_VOS_THD_SCHED
             IN V_INT32 i32Priority:Ҫ���õ����ȼ�����E_VOS_THD_PRI
 �������  : ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_THD_DEAD_LOCK:�̱߳������ˣ��Ȳ�������
                      E_VOS_THD_ERR_UNKOWN:δ֪����
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_SetThreadPriority(IN VOSTHDHDL hThdHdl,
                                       IN V_INT32 i32Sched,
                                       IN V_INT32 i32Priority);

/*****************************************************************************
 �� �� ��  : VOS_GetThreadPriority
 ��������  : ��ȡ�߳����ȼ�
 �������  : IN VOSTHDHDL hThdHdl:Ҫ���õ��߳̾����ͨ��VOS_CreateThread��õ�
 �������  : OUT V_INT32* pi32Sched:Ҫ��ȡ�ĵ��Ȳ���
             OUT V_INT32* pi32Priority:Ҫ��ȡ�����ȼ�ָ�룬��E_VOS_THD_PRI
             �������������ѡ������ĸ���������ע�Ŀɴ���NULL����������һ����ΪNULL
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_ARGS: �����������ȷ
                      E_VOS_THD_ERR_UNKOWN:δ֪����
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_GetThreadPriority(IN VOSTHDHDL hThdHdl,
                                       OUT V_INT32* pi32Sched,
                                       OUT V_INT32* pi32Priority);

/*****************************************************************************
 �� �� ��  : VOS_GetSelfThreadId
 ��������  : ��ȡ�����߳�ID
 �������  : ��
 �� �� ֵ  : VOS_TID_T:�����߳�ID
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API VOS_TID_T VOS_GetSelfThreadId();

/*****************************************************************************
 �� �� ��  : VOS_GetSelfThdHdl
 ��������  : ���������߳̾��,�������ʹ�øýӿڣ��ýӿڷ��صľ����ʹ��������ʹ��
             VOS_DetachThread()����VOS_JoinThread���ͷŸþ��
 �������  : ��
 �� �� ֵ  : VOSTHDHDL:���������߳̾��
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API VOSTHDHDL VOS_GetSelfThdHdl();

/*****************************************************************************
 �� �� ��  : VOS_GetThdIdByHandle
 ��������  : ���߳̾����ȡ���Ӧ���߳�ID
 �������  : IN VOSTHDHDL hHdl:�߳̾����ͨ��VOS_CreateThread��õ�
 �������  : OUT V_UINT32 *pu32ThdId:�߳�IDָ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_ARGS: �����������ȷ
                      ����:ʧ��
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_GetThdIdByHandle(IN VOSTHDHDL hThdHdl, OUT VOS_TID_T *pThdId);

/*****************************************************************************
 �� �� ��  : VOS_GetSelfPid
 ��������  : ��ȡ������ID
 �������  : ��
 �� �� ֵ  : VOS_API VOS_PID_T:���ؽ��̺�
 �޸���ʷ      :
  1.��    ��   : 2012��9��14��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API VOS_PID_T VOS_GetSelfPid();

/* ���� */
/* Ĭ�ϳ�ʼ�����������������ֻ����ȫ�ֱ��� */
#ifdef WIN32
#define VOS_PTHREAD_MUTEX_INITIALIZER  (VOS_InitThdMutex_Def())
VOS_API ST_VOS_THD_MUTEX VOS_InitThdMutex_Def();
#else
#define VOS_PTHREAD_MUTEX_INITIALIZER {{0,}}
#endif

/*****************************************************************************
 �� �� ��  : VOS_InitThdMutex
 ��������  : ��ʼ���̼߳以�����
 �������  : IN const ST_THD_MUTEX_ATTR* stAttr:�������ԣ��������ṹ���崦��
                                                �ò���Ϊ��ѡ������ע����NULL��
                                                ������ʱ����
 �������  : OUT PST_VOS_THD_MUTEX pstMutex:Mutex����ָ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_ARGS: �����������ȷ
                      ����:ʧ��
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_InitThdMutex(OUT PST_VOS_THD_MUTEX pstMutex,
                                  IN const ST_VOS_THD_MUTEX_ATTR* pstAttr);

/*****************************************************************************
 �� �� ��  : VOS_DestroyThdMutex
 ��������  : ȥ��ʼ���̻߳������
 �������  : INOUT PST_VOS_THD_MUTEX pstMutex:Mutex����ָ�룬������ΪNULLʱ��
                                              ֱ�ӷ���E_VOS_THD_ERR_ARGS
 �������  : ��
 �� �� ֵ  : V_VOID:��
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_DeInitThdMutex(INOUT PST_VOS_THD_MUTEX pstMutex);

/*****************************************************************************
 �� �� ��  : VOS_ThdMutexLock
 ��������  : ����̻߳�����
 �������  : IN PST_VOS_THD_MUTEX pstMutex:Mutex����ָ�룬������ΪNULLʱ�����ش���
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_ThdMutexLock(IN PST_VOS_THD_MUTEX pstMutex);

/*****************************************************************************
 �� �� ��  : VOS_ThdMutexUnLock
 ��������  : �ͷ��̻߳�����
 �������  : IN PST_VOS_THD_MUTEX pstMutex:Mutex����ָ�룬������ΪNULLʱ�����ش���
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_ThdMutexUnLock(IN PST_VOS_THD_MUTEX pstMutex);

//�߳�����ͬ��
/*****************************************************************************
 �� �� ��  : VOS_CreateThdCond
 ��������  : �����߳�ͬ������
 �������  : IN const ST_THD_COND_ATTR* pstAttr:����ͬ�����ԣ��������ṹ���崦��
                                                �ò���Ϊ��ѡ������ע����NULL��������ʱ����
 �������  : ��
 �� �� ֵ  : V_VOID*:NULLʧ�ܣ������ɹ�
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API VOSCONDHDL VOS_CreateThdCond(IN const ST_VOS_THD_COND_ATTR* pstAttr);

/*****************************************************************************
 �� �� ��  : VOS_DestroyThdCond
 ��������  : �����߳�ͬ������
 �������  : INOUT V_VOID* pvCond:VOS_CreateThdCond�ӿڴ����Ķ��󣬵�����ΪNULLʱ��
                                  ֱ�ӷ���
 �������  : ��
 �� �� ֵ  : V_VOID
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_DestroyThdCond(INOUT VOSCONDHDL hCond);

/*****************************************************************************
 �� �� ��  : VOS_ThdCondSignal
 ��������  : ����ͬ������ź�
 �������  : IN V_VOID* pvCond:VOS_CreateThdCond�ӿڴ����Ķ��󣬵�����ΪNULLʱ��
                               ֱ�ӷ���
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_ThdCondSignal(IN VOSCONDHDL hCond);

/*****************************************************************************
 �� �� ��  : VOS_ThdCondBrodcast
 ��������  : �㲥�������ͬ���ź�
 �������  : IN V_VOID* pvCond:VOS_CreateThdCond�ӿڴ����Ķ��󣬵�����ΪNULLʱ��
                               ֱ�ӷ���
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_ThdCondBrodcast(IN VOSCONDHDL hCond);

/*****************************************************************************
 �� �� ��  : VOS_ThdCondWait
 ��������  : ���޵ȴ��߳�����ͬ���ź�
 �������  : IN V_VOID* pvCond:VOS_CreateThdCond�ӿڴ����Ķ��󣬵�����ΪNULLʱ��
                               ֱ�ӷ���
             IN PST_VOS_THD_MUTEX pvMutex:���������󣬵��䲻Ϊ��ʱ�����ͷ�����
 �������  : ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_ARGS: ��������
                      ����:������
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_ThdCondWait(IN VOSCONDHDL hCond, IN PST_VOS_THD_MUTEX pstMutex);

/*****************************************************************************
 �� �� ��  : VOS_ThdCondTimeWait
 ��������  : ��ʱ�ȴ��߳�����ͬ���ź�
 �������  : IN V_VOID* pvCond:VOS_CreateThdCond�ӿڴ����Ķ��󣬵�����ΪNULLʱ��
                               ֱ�ӷ��ش���
             IN PST_VOS_THD_MUTEX pstMutex:���������󣬵��䲻ΪNULLʱ�����ͷ�����
                                           ΪNULLʱ���ԡ�
             IN V_UINT32 u32MiliSecTimeOut://��ʱʱ�䣬��λms
 �������  : ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_ARGS: ��������
                      E_VOS_THD_ERR_COND_TIMEOUT:��ʱ
                      ����:������
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_ThdCondTimeWait(IN VOSCONDHDL hCond,
                                    IN PST_VOS_THD_MUTEX pstMutex,
                                    IN V_UINT32 u32MiliSecTimeOut);

//˯��
/*****************************************************************************
 �� �� ��  : VOS_Sleep
 ��������  : �뼶˯��
 �������  : IN V_UINT32 u32Sec:˯��ʱ�䣬��λs
 �������  : ��
 �� �� ֵ  : V_VOID
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_Sleep(IN V_UINT32 u32Sec);

/*****************************************************************************
 �� �� ��  : VOS_MSleep
 ��������  : ���뼶˯��
 �������  : IN V_UINT32 u32MilliSec:˯��ʱ�䣬��λms
 �������  : ��
 �� �� ֵ  : V_VOID
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_MSleep(IN V_UINT32 u32MilliSec);

//ʱ��
/*****************************************************************************
 �� �� ��  : VOS_GetTimeTicks
 ��������  : ��ȡϵͳʱ���
 �������  : ��
 �� �� ֵ  : V_UINT32:ʧ��:0XFFFFFFFF
                      ������ϵͳʱ���
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_GetTimeTicks();

VOS_API V_UINT64 VOS_GetTimeTicks64();

/*****************************************************************************
 �� �� ��  : VOS_GetLocalTime
 ��������  : ��ȡϵͳ����ʱ��
 �������  : ��
 �������  : OUT ST_VOS_SYSTIME* pstSysTime: ����ʱ��ṹָ��
             OUT V_CHAR* pszTime:����ʱ���ַ�������ʽ����YYYY:MM:DD:HH:MM:SS:MMM
                                 �䳤��>=24���ַ�
            ������������ѡ������עʱ����NULL����
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      ����:������
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_GetLocalTime(OUT ST_VOS_SYSTIME* pstSysTime,
                                  OUT V_CHAR* pszTime);


/* Event:��֧�֣�һʱ�̵���Ŀ��ȴ��������ѣ�ͬһʱ��ͬʱ�ȴ�ʱ����֤����˳�� */
/*****************************************************************************
 �� �� ��  : VOS_CreateThdEvent
 ��������  : �����¼�����
 �������  : IN const ST_VOS_THD_EVENT_ATTR* pstAttr:Event���ԣ��������ṹ
                                                   ���崦���ò���Ϊ��ѡ������ע
                                                   ����NULL��������ʱ����
 �������  : ��
 �� �� ֵ  : V_VOID*:VOS_INVALIDE_EVENT_HANDLEʧ�ܣ������ɹ�
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API VOSEVENTHDL VOS_CreateThdEvent(IN const ST_VOS_THD_EVENT_ATTR* pstAttr);

/*****************************************************************************
 �� �� ��  : VOS_DestroyThdEvent
 ��������  : �����¼�����
 �������  : INOUT VOSEVENTHDL pvCond: IN VOSCONDHDL hCondVOS_CreateThdSemaphore
                                   �ӿڴ����Ķ��󣬵�����ΪVOS_INVALIDE_THDSEM_HANDLE
                                   ʱ��ֱ�ӷ���
 �������  : ��
 �� �� ֵ  : V_VOID
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_DestroyThdEvent(IN VOSEVENTHDL pvEvent);

/*****************************************************************************
 �� �� ��  : VOS_ThdEventSignal
 ��������  : �¼�����
 �������  : IN VOSEVENTHDL pvCond:VOS_CreateThdEvent�ӿڴ����Ķ���
                                       ������ΪVOS_INVALIDE_EVENT_HANDLEʱ��
                                       ֱ�ӷ���
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_ThdEventSignal(IN VOSEVENTHDL pvEvent);

/*****************************************************************************
 �� �� ��  : VOS_ThdEventTimeWait
 ��������  : ��ʱ�ȴ��¼�
 �������  : IN VOSEVENTHDL pvCond:VOS_CreateThdEvent�ӿڴ����Ķ���
                                       ������ΪVOS_INVALIDE_EVENT_HANDLEʱ��
                                       ֱ�ӷ��ش���
             IN V_UINT32 u32TimeOutMs://��ʱʱ�䣬��λms
 �������  : ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_ARGS: ��������
                      E_VOS_THD_ERR_COND_TIMEOUT:��ʱ
                      ����:������
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_ThdEventTimeWait(IN VOSEVENTHDL pvEvent,
                                      IN V_UINT32 u32TimeOutMs);

/*****************************************************************************
 �� �� ��  : VOS_ThdEventWait
 ��������  : ���޵ȴ��߳�semaphore�ź�
 �������  : IN VOSEVENTHDL pvCond:VOS_CreateThdEvent�ӿڴ����Ķ���
                                       ������ΪVOS_INVALIDE_EVENT_HANDLEʱ��
                                       ֱ�ӷ���
 �������  : ��
 �� �� ֵ  : V_UINT32:E_VOS_THD_ERR_NONE���ɹ�.
                      E_VOS_THD_ERR_ARGS: ��������
                      ����:������
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_ThdEventWait(IN VOSEVENTHDL pvEvent);

/* �ź������� */
/*****************************************************************************
 �� �� ��  : VOS_CreateThdSem
 ��������  : ��������ʼ���ź���
 �������  : V_UINT32 u32InitValue  : �ź�����ʼֵ
 �������  : ��
 �� �� ֵ  : VOS_API VOSSEMHDL NULL ʧ��
 �޸���ʷ      :
  1.��    ��   : 2013��5��3��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API VOSSEMHDL VOS_CreateThdSem(IN V_UINT32 u32InitValue);

/*****************************************************************************
 �� �� ��  : VOS_DestroyThdSem
 ��������  : �����ź���
 �������  : IN VOSSEMHDL hSem  : �ź������
 �������  : ��
 �� �� ֵ  : VOS_API V_VOID
 �޸���ʷ      :
  1.��    ��   : 2013��5��3��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_DestroyThdSem(IN VOSSEMHDL hSem);

/*****************************************************************************
 �� �� ��  : VOS_TmdSemPost
 ��������  : ����һ���ź���
 �������  : IN VOSSEMHDL hSem  : �ź������
 �������  : ��
 �� �� ֵ  : VOS_API V_VOID
 �޸���ʷ      :
  1.��    ��   : 2013��5��3��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_VOID VOS_ThdSemPost(IN VOSSEMHDL hSem);

/*****************************************************************************
 �� �� ��  : VOS_ThdSemWait
 ��������  : �ȴ��ź���
 �������  : IN VOSSEMHDL hSem  : �ź������
 �������  : ��
 �� �� ֵ  : VOS_API V_UINT32 : E_VOS_THD_ERR_NONE���ɹ�
                              : E_VOS_THD_ERR_FAIL: ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��3��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_ThdSemWait(IN VOSSEMHDL hSem);

/*****************************************************************************
 �� �� ��  : VOS_ThdSemTimedWait
 ��������  : ��ʱ�ȴ��ź���
 �������  : IN VOSSEMHDL hSem         : �ź������
             IN V_UINT32 u32TimeOutMs  : ��ʱʱ��(����)
 �������  : ��
 �� �� ֵ  : VOS_API V_UINT32 : E_VOS_THD_ERR_NONE���ɹ�
                              : E_VOS_THD_ERR_COND_TIMEOUT: ��ʱ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��3��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_API V_UINT32 VOS_ThdSemTimedWait(IN VOSSEMHDL hSem, IN V_UINT32 u32TimeOutMs);



#ifdef __cplusplus
}
#endif

#endif// __OSAL_THREAD__
