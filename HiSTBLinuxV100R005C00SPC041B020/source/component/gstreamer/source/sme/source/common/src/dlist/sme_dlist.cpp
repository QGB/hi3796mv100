/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sme_dlst.cpp
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


#include "sme_dlist.h"
#include "linked_list.h"
#include "sme_log.h"
#include "sme_macro.h"

#undef MOD_NAME
#define MOD_NAME "utils"

using namespace ICS;

DList::DList(IN V_VOID* pvUserData/* = NULL*/)
{
    //lint -e10
    m_pvListHdl = (V_VOID *)malloc(sizeof(LinkedList));
    //lint +e10
    if (NULL == m_pvListHdl)
    {
        ICS_LOGW("dlist malloc fail");
        return;
    }

    if (ICS_SUCCESS != ListInit((LinkedList *)m_pvListHdl, this, pvUserData))
    {
        ICS_LOGW("dlist ListInit fail");
        UTILS_MSAFEFREE(m_pvListHdl);
    }
}

DList::~DList()
{
    V_INT32 i32Ret;

    if (NULL != m_pvListHdl)
    {
        i32Ret = ListDestroy((LinkedList *)m_pvListHdl, 0);
        UTILS_MLOGW_IF(0 != i32Ret, ("destroy list fail."));
    }

    UTILS_MSAFEFREE(m_pvListHdl);
}

DList::Node* DList::AddHead(V_VOID* pvItem)
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListAddHead((LinkedList *)m_pvListHdl, pvItem);
}

DList::Node* DList::AddTail(V_VOID* pvItem)
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListAddTail((LinkedList *)m_pvListHdl, pvItem);
}

DList::Node* DList::AddAfter(V_VOID* pvItem, DList::Node* pNode)
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListAddAfter((LinkedList *)m_pvListHdl, pvItem, (ListNode *)pNode);
}

DList::Node* DList::AddBefore(V_VOID* pvItem, DList::Node* pNode)
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListAddBefore((LinkedList *)m_pvListHdl, pvItem, (ListNode *)pNode);
}

V_VOID* DList::DelNode(DList::Node* pNode, V_BOOL bFreeItem)
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (V_VOID*)ListDelNode((LinkedList *)m_pvListHdl, (ListNode *)pNode, (V_INT32)bFreeItem);
}

V_VOID DList::DelAll(IN V_BOOL bFreeItem)
{
    ListDelAll((LinkedList *)m_pvListHdl, (int)bFreeItem);
}

DList::Node* DList::GetHead() const
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListHead((LinkedList *)m_pvListHdl);
}

DList::Node* DList::GetTail() const
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListTail((LinkedList *)m_pvListHdl);
}

DList::Node* DList::GetNext(DList::Node* pNode) const
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListNext((LinkedList *)m_pvListHdl, (ListNode *)pNode);
}

DList::Node* DList::GetPrev(DList::Node* pNode) const
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListPrev((LinkedList *)m_pvListHdl, (ListNode *)pNode);
}

DList::Node* DList::Find(V_VOID* pvItem, DList::Node* pNodeStart/* = NULL*/)
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, NULL);
    return (DList::Node *)ListFind((LinkedList *)m_pvListHdl, (ListNode *)pNodeStart, pvItem);
}

V_UINT32 DList::GetSize()
{
    UTILS_RET_VAL_IF(NULL == m_pvListHdl, 0);
    return (V_UINT32)ListSize((LinkedList *)m_pvListHdl);
}
