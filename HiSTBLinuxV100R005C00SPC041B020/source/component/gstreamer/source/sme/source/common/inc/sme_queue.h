/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sme_queue.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2013��4��29��
  ����޸�   :
  ��������   : ����˫����������Ķ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��29��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __ICS_QUEUE_H__
#define __ICS_QUEUE_H__

#include "osal_type.h"
#include "sme_dlist.h"
#include "osal_thread.h"

namespace ICS
{

class QueDList;

class Queue
{
friend class QueDList;
public:
    /* u32MaxSize=0�����ƶ��д�С */
    Queue(V_UINT32 u32MaxSize = 0);
    virtual ~Queue();

    V_UINT32 Push(V_VOID* pvItem);

    V_UINT32 Pop(V_VOID*& pvItem);

    V_VOID ClearQueue(V_BOOL bFree = ICS_TRUE);

    //V_UINT32 Peek(V_VOID*& pvItem);

    V_UINT32 GetSize();

protected:
    virtual V_VOID OnFreeMsg(V_VOID* pvItem) {pvItem = pvItem;};

private:
    DList* m_pobjDlist;
    V_UINT32 m_u32MaxSize;
    ST_VOS_THD_MUTEX m_stMutex;
};

}

#endif
