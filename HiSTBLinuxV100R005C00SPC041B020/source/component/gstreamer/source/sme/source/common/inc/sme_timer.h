/**************************************************************************//**

  Copyright (C), 2001-2012, Huawei Tech. Co., Ltd.
******************************************************************************
 * @file    sme_timer.h
 * @brief   ��sme_threadʵ��timer�ඨ��
 * @author
 * @date    2014/6/4
 * @version VFP xxxxxxxxx
 * History:
 *
 * Number : V1.00
 * Date   : 2014/6/4
 * Author :
 * Desc   : Created file
 *
******************************************************************************/
#ifndef __ICS_TIMER_H__
#define __ICS_TIMER_H__

#include "osal_thread.h"
#include "sme_thread.h"

namespace ICS
{
#define ICS_TIMER_INTERVAL_DEFAULT  1000 //ms
#define ICS_TIMER_INTERVAL_MIN      1    //ms

class Timer : protected ICS::Thread
{
public:
     typedef V_VOID(*pfTimerFunc)(IN V_VOID* pvCtx);
public:
    Timer(IN const V_CHAR* pszTimerName, IN pfTimerFunc pfnTimer,
        IN V_VOID* pvCtx = NULL,
        IN V_UINT32 u32IntervalVal = ICS_TIMER_INTERVAL_DEFAULT);
    virtual ~Timer();

    V_UINT32 SetIntervalVal(V_UINT32 u32Val);
    V_UINT32 Open();
    V_VOID   Close();
    V_UINT32 Start();
    V_UINT32 Pause();

private:
    virtual V_VOID OnStartup();
    virtual V_VOID Process();
    virtual V_VOID OnExit();
    Timer();

private:
    pfTimerFunc         m_pfnTimer;         //��ʱ���ص�����
    V_VOID*             m_pvCtx;            //��ʱ���ص�����������
    V_UINT32            m_u32IntervalVal;   //��ʱ�������
    V_BOOL              m_bRun;             //Timer�Ƿ����С�
    V_BOOL              m_bExit;            //�Ƿ��˳�Timer��
    V_BOOL              m_bInited;          //�Ƿ��ʼ����
    V_CHAR*             m_pszTimerName;     //Timer����
    VOSCONDHDL          m_hdlCond;          //�ȴ�����������
    ST_VOS_THD_MUTEX    m_stMutex;          //��������
};

}

#endif
