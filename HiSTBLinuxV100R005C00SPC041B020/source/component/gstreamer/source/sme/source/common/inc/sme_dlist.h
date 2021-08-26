/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sme_dlist.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2013��4��29��
  ����޸�   :
  ��������   : ����upnpЭ��ջ�е�C˫�������װ��C++˫������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��29��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __ICS_DLIST_H__
#define __ICS_DLIST_H__

#include "osal_type.h"
#include <stdio.h>

namespace ICS
{

class DList
{
public:
    struct Node
    {
        Node* pPrev;
        Node* pNext;
        V_VOID* pvItem;
    };

public:
    DList(IN V_VOID* pvUserData = NULL);
    virtual ~DList();

    Node* AddHead(IN V_VOID* pvItem);

    Node* AddTail(IN V_VOID* pvItem);

    Node* AddAfter(IN V_VOID* pvItem, IN Node* pNode);

    Node* AddBefore(IN V_VOID* pvItem, IN Node* pNode);

    /* ���bFreeItem=TRUE�򷵻�NULL�����bFreeItem=FALSE,�򷵻ؽڵ��е�item */
    V_VOID* DelNode(IN Node* pNode, IN V_BOOL bFreeItem);

    V_VOID DelAll(IN V_BOOL bFreeItem);

    Node* GetHead() const;

    Node* GetTail() const;

    Node* GetNext(IN Node* pNode) const;

    Node* GetPrev(IN Node* pNode) const ;

    Node* Find(IN V_VOID* pvItem, IN Node* pNodeStart = NULL);

    V_UINT32 GetSize();

public:
    virtual V_VOID OnItemFree(IN V_VOID* pvItem, IN V_VOID* pvUserData) = 0;

    /* ���� =0��ʾ����������� !=0��ʾ������������(���ڲ�����) */
    virtual V_UINT32 OnCompareItem(IN V_VOID* pvItemA, IN V_VOID* pvItemB, IN V_VOID* pvUserData) = 0;

private:
    V_VOID* m_pvListHdl;
};

}

#endif
