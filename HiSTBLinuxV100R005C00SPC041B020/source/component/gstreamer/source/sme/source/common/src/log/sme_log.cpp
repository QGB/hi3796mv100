/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sme_log.c
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2011��10��10��
  ����޸�   :
  ��������   : ICS�ն����ƽ̨��־ϵͳ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��10��10��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/
#include <string.h>
#include <stdarg.h>
#include "sme_log.h"
#include "sme_dlist.h"
#include "osal_type.h"
#include "osal_thread.h"
#include "osal_str.h"
#include "osal_mem.h"
#ifndef GST_SME_NO_LOGCAT
#include <cutils/log.h>
#ifdef __LINUX__
#include <utils/Logger.h>
#endif
#endif

#ifdef WIN32
#pragma warning(disable: 4996)
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/
/*lint -save -e* */
V_VOID ICS_Log(IN E_ICS_LOG_LEVEL eLogLevel,
               IN const V_CHAR* pcszModName,
               IN const V_CHAR* pcszFileName,
               IN const V_CHAR* pcszFuncName,
               IN V_UINT32 u32LineNum,
               IN const V_CHAR* pcszFmt, ...);
/*lint -restore * */

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/
/*������������־����*/
static E_ICS_LOG_SWITCH g_aeLogSwitch[ICS_LOG_BUTT] = {ICS_LOG_SWITCH_ON, \
        ICS_LOG_SWITCH_ON, ICS_LOG_SWITCH_ON, \
        ICS_LOG_SWITCH_ON, ICS_LOG_SWITCH_ON
                                                      };
/*������־������*/
static E_ICS_LOG_STYLE g_eLogStyle = ICS_LOG_STYLE_DETAILED;

/*������־������*/
static ST_VOS_THD_MUTEX g_stLogLock = VOS_PTHREAD_MUTEX_INITIALIZER;


/*log file list*/
#define LOG_FILE_NAME_MAX_LENGTH 256
typedef struct LogFileItem
{
    V_CHAR cFileName[LOG_FILE_NAME_MAX_LENGTH];
}ST_LOG_FILE_ITEM;

class LogFileDList : public ICS::DList
{
public:
    LogFileDList() {};
    virtual ~LogFileDList() {};

    virtual V_VOID OnItemFree(IN V_VOID* pvItem, IN V_VOID* /*pvUserData*/)
    {
        ST_LOG_FILE_ITEM* pLogFileItem = (ST_LOG_FILE_ITEM*)pvItem;
        delete pLogFileItem;
        return;
    };

    virtual V_UINT32 OnCompareItem(IN V_VOID* /*pvItemA*/, IN V_VOID* /*pvItemB*/, IN V_VOID* /*pvUserData*/)
    {
        return 0;
    };
};

LogFileDList* g_LogList = new LogFileDList();
#define LOG_FILE_COUNT_MAX 6

/* FIXME: static buffer for log */
#define LOG_FILE_SIZE_MAX (50*1024*1024)
#define LOG_BUF_SIZE    65535
static V_INT8 g_acLogBuf[LOG_BUF_SIZE] = {0};
static V_INT32 g_iLogBufIdx = 0;
//static const V_BOOL g_sbLogNotCache = ICS_TRUE;//log not print to buf.
static const V_BOOL g_sbLogNotCache = ICS_FALSE;//log print to buf first.

#ifdef WIN32
static FILE* g_hfLog = NULL;
#else
static V_INT32 g_fdLog = -1;
static V_UINT32 g_u32LogSize = 0;
#endif
#ifdef __LINUX__
static V_INT32 g_fdAdaptLog = -1;
#endif
#define SME_LOG_DIR "/data/smelog"

#define LOG_TO_BUF

//lint -esym(530, stArgList)
//lint -e1784
//lint -esym(1055, strlen, LOG_PRI)

//:if can create log file we log to file.
//:else
//:for android we log to logcat
//:for linux, we log to stdout
#if defined (LOG_TO_BUF) && !defined (SME_RLS)
static V_VOID LogOut(E_ICS_LOG_LEVEL level, const V_CHAR* pszModName, const V_CHAR* pszFmt, ...)
{
    va_list stArgList;
    ST_VOS_SYSTIME stSysTime;
    V_INT32 iLen = 0;
    VOS_PID_T iPid = 0;
    V_CHAR cFileName[256] = {0};
    V_INT32 i32PrintStrRes = 0;

    if(g_fdLog >= 0)
    {
        if(g_u32LogSize >= LOG_FILE_SIZE_MAX)
        {
            close(g_fdLog);
            g_fdLog = -1;
            g_u32LogSize = 0;
        }
    }

    //lint -e429  //Custodial pointer 'pNewFileItem' (line 176) has not been freed or returned
    if (g_fdLog < 0)
    {
        iPid = VOS_GetSelfPid();
        VOS_GetLocalTime(&stSysTime, NULL);
        i32PrintStrRes = VOS_Snprintf_S(cFileName, sizeof(cFileName) - 1,
            sizeof(cFileName) - 2,  "%s/sme_log_%d_%02d_%02d_%02d_%02d_%02d.txt",
            SME_LOG_DIR, iPid, stSysTime.u32Mon, stSysTime.u32Day,
            stSysTime.u32Hour, stSysTime.u32Min, stSysTime.u32Sec);
        if(i32PrintStrRes <= 0)
        {
            printf("VOS_Snprintf_S failed!\n");
        }
        /** FIXME: the file descriptor was not explictly released
         */
        g_fdLog = open(cFileName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

        if(g_fdLog > 0)
        {
            if(g_LogList->GetSize() > LOG_FILE_COUNT_MAX)
            {
                //delete file
                ICS::DList::Node* pHead = g_LogList->GetHead();
                ST_LOG_FILE_ITEM* pFileItem = (ST_LOG_FILE_ITEM*)(pHead->pvItem);
                if (0 != remove(pFileItem->cFileName))
                {
                    printf("delete old log file failed!\n");
                }

                //delete node and item
                g_LogList->DelNode(pHead, ICS_TRUE);
                //pHead = NULL;
            }

            ST_LOG_FILE_ITEM* pNewFileItem = new ST_LOG_FILE_ITEM;
            if(E_SME_MEM_OK != VOS_Memset_S(
                pNewFileItem->cFileName,
                LOG_FILE_NAME_MAX_LENGTH,
                0,
                LOG_FILE_NAME_MAX_LENGTH))
            {
                printf("SECURE: reset log file node failed.\n");
            }
            if(E_SME_MEM_OK != VOS_Memcpy_S(
                pNewFileItem->cFileName,
                LOG_FILE_NAME_MAX_LENGTH - 1,
                cFileName,
                LOG_FILE_NAME_MAX_LENGTH - 2))
            {
                printf("SECURE: copy log file node failed.\n");
            }
            if(NULL == g_LogList->AddTail(pNewFileItem))
            {
                printf("add new log file node failed.\n");
            }
        }
    }
    //lint +e429

    if(g_fdLog < 0)
    {
        va_start(stArgList, pszFmt);
#ifdef __ANDROID__
        i32PrintStrRes = VOS_Vsnprintf_S(g_acLogBuf,
            LOG_BUF_SIZE - 1, LOG_BUF_SIZE - 2, pszFmt, stArgList);
        if(i32PrintStrRes <= 0)
        {
            printf("VOS_Vsnprintf_S failed\n");
        }
        LOG_PRI(level, pszModName, "%s", g_acLogBuf);
#else
#if 0
        VOS_GetLocalTime(&stSysTime, NULL);
        printf("[%02d:%02d:%02d:%03d] [%#lx] ", stSysTime.u32Hour,
            stSysTime.u32Min, stSysTime.u32Sec,
            stSysTime.u32MilliSec, VOS_GetSelfThreadId());
        vprintf(pszFmt, stArgList);

        printf("\n");
        fflush(stdout);
#endif
#endif
        va_end(stArgList);

        return;
    }

    va_start(stArgList, pszFmt);
    VOS_GetLocalTime(&stSysTime, NULL);
    i32PrintStrRes = VOS_Snprintf_S(g_acLogBuf + g_iLogBufIdx,
        (V_SIZE)((LOG_BUF_SIZE - g_iLogBufIdx) - 1),
        (V_SIZE)((LOG_BUF_SIZE - g_iLogBufIdx) - 2),
        "[%02d:%02d:%02d:%03d] [%p] ",
        stSysTime.u32Hour, stSysTime.u32Min,
        stSysTime.u32Sec, stSysTime.u32MilliSec,
        VOS_GetSelfThreadId());
    if(i32PrintStrRes <= 0)
    {
        printf("VOS_Snprintf_S failed!\n");
        iLen = 0;
    }
    else
    {
        iLen = i32PrintStrRes;
    }

    g_iLogBufIdx += iLen;

    i32PrintStrRes = VOS_Vsnprintf_S(g_acLogBuf + g_iLogBufIdx,
        (V_SIZE)((LOG_BUF_SIZE - g_iLogBufIdx) - 1),
        (V_SIZE)((LOG_BUF_SIZE - g_iLogBufIdx) - 2),
        pszFmt, stArgList);
    if(i32PrintStrRes <= 0)
    {
        printf("VOS_Vsnprintf_S failed\n");
        iLen = 0;
    }
    else
    {
        iLen = i32PrintStrRes;
    }

    g_iLogBufIdx += iLen;

    g_acLogBuf[g_iLogBufIdx] = '\n';
    g_iLogBufIdx++;

    va_end(stArgList);
    //lint -e774
    if (g_sbLogNotCache || (g_iLogBufIdx > (LOG_BUF_SIZE >> 1)))
    {
    //lint +e774
        V_INT32 i32Ret = write(g_fdLog, g_acLogBuf, g_iLogBufIdx);
        if(i32Ret != g_iLogBufIdx)
        {
            printf("write error!");
        }
        if(i32Ret < 0)
        {
            i32Ret = 0;
        }
        g_u32LogSize += (V_UINT32)i32Ret;
        g_iLogBufIdx = 0;
    }

    return ;
}
#else
static V_VOID LogOut(E_ICS_LOG_LEVEL level, const V_CHAR* pszModName,
    const V_CHAR* pszFmt, ...)
{
    va_list stArgList;
    va_start(stArgList, pszFmt);

#ifdef __ANDROID__
    V_INT32 i32PrintStrRes = 0;

    i32PrintStrRes = VOS_Vsnprintf_S(g_acLogBuf,
        LOG_BUF_SIZE - 1, LOG_BUF_SIZE - 2, pszFmt, stArgList);
    if(i32PrintStrRes <= 0)
    {
        printf("VOS_Vsnprintf_S failed\n");
    }
    LOG_PRI(level, pszModName, "%s", g_acLogBuf);
#else
    ST_VOS_SYSTIME stSysTime;

    VOS_GetLocalTime(&stSysTime, NULL);
    printf("[%02d:%02d:%02d:%03d] [%#x] ", stSysTime.u32Hour, stSysTime.u32Min, stSysTime.u32Sec,
        stSysTime.u32MilliSec, VOS_GetSelfThreadId());
    vprintf(pszFmt, stArgList);

    printf("\n");
    fflush(stdout);
#endif
    va_end(stArgList);

    return;
}
#endif

static V_UINT32 LevelMap(E_ICS_LOG_LEVEL eLevel)
{
#if defined WIN32 || defined __LINUX__
    return (V_UINT32)eLevel;
#else
    switch (eLevel)
    {
        case ICS_LOG_VERBOSE:
            return (V_UINT32)ANDROID_LOG_VERBOSE;
        case ICS_LOG_INFO:
            return (V_UINT32)ANDROID_LOG_INFO;
        case ICS_LOG_WARNING:
            return (V_UINT32)ANDROID_LOG_WARN;
        case ICS_LOG_DEBUG:
            return (V_UINT32)ANDROID_LOG_DEBUG;
        case ICS_LOG_ERROR:
            return (V_UINT32)ANDROID_LOG_ERROR;
        default:
            return (V_UINT32)ANDROID_LOG_VERBOSE;
    }
#endif
}

const V_CHAR* RStrStr(const V_CHAR* pszSrc, const V_CHAR needle)
{
    V_INT32 i32Len = strlen(pszSrc);
    for (V_INT32 i = i32Len - 1; i >= 0; i--)
    {
        if (pszSrc[i] == needle)
        {
            return &pszSrc[i];
        }
    }

    return NULL;
}

/*****************************************************************************
 �� �� ��  : ICS_Log
 ��������  : ��ӡ��־�������
 �������  : IN E_ICS_LOG_LEVEL eLogLevel     :��־����
             IN const V_CHAR *pcszModName     :��־ģ����
             IN const V_CHAR *pcszFileName    :��־�����ļ���
             IN const V_CHAR *pcszFuncName    :��־���ں�����
             IN V_UINT32 u32LineNum           :��־�����к�
             IN const V_CHAR * pcszFmt        :��־��ʽ���ַ���
             ...
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -save -e* */
#ifdef __LINUX__
V_VOID ICS_Adapter_Log(IN E_ICS_LOG_LEVEL eLogLevel,
                       IN const V_CHAR* pcszModName,
                       IN const V_CHAR* pcszFileName,
                       IN const V_CHAR* pcszFuncName,
                       IN V_UINT32 u32LineNum,
                       IN const V_CHAR* acBuf)
{

#ifndef GST_SME_NO_LOGCAT
    switch (eLogLevel)
    {
        case ICS_LOG_VERBOSE:
            LOGGER(HI_LOGGER_VERBOSE, pcszModName, pcszFileName, u32LineNum, acBuf);
            break;

        case ICS_LOG_INFO:
            LOGGER(HI_LOGGER_INFO, pcszModName, pcszFileName, u32LineNum, acBuf);
            break;

        case ICS_LOG_WARNING:
            LOGGER(HI_LOGGER_WARN, pcszModName, pcszFileName, u32LineNum, acBuf);
            break;

        case ICS_LOG_DEBUG:
            LOGGER(HI_LOGGER_DEBUG, pcszModName, pcszFileName, u32LineNum, acBuf);
            break;

        case ICS_LOG_ERROR:
            LOGGER(HI_LOGGER_ERROR, pcszModName, pcszFileName, u32LineNum, acBuf);
            break;

        default:
            break;
    }
#endif

    return;
}
#endif

V_VOID ICS_Log(IN E_ICS_LOG_LEVEL eLogLevel,
               IN const V_CHAR* pcszModName,
               IN const V_CHAR* pcszFileName,
               IN const V_CHAR* pcszFuncName,
               IN V_UINT32 u32LineNum,
               IN const V_CHAR* pcszFmt, ...)
{
    va_list stArgList;
    V_CHAR acBuf[ICS_LOG_BUF_SIZE] = {0,};
    V_UINT32 u32LogLength = 0;
    V_INT32 i32PrintStrRes = 0;

    VOS_ThdMutexLock(&g_stLogLock);
    if (ICS_LOG_SWITCH_ON == g_aeLogSwitch[eLogLevel])
    {
        va_start(stArgList, pcszFmt);
        i32PrintStrRes = VOS_Vsnprintf_S(acBuf, sizeof(acBuf), sizeof(acBuf) - 1,
            pcszFmt, stArgList);
        if(i32PrintStrRes <= 0)
        {
            printf("VOS_Vsnprintf_S failed\n");
        }

        va_end(stArgList);


        const V_CHAR* pszSimpleFileName = RStrStr(pcszFileName, '/');
        if (NULL == pszSimpleFileName)
        {
            pszSimpleFileName = pcszFileName;
        }
        else
        {
            pszSimpleFileName += 1;
        }

        if (ICS_LOG_STYLE_DETAILED == g_eLogStyle)
        {
            u32LogLength = strlen(acBuf);
            i32PrintStrRes = VOS_Snprintf_S(acBuf + u32LogLength,
                ICS_LOG_BUF_SIZE - u32LogLength - 1,
                ICS_LOG_BUF_SIZE - u32LogLength - 2,
                "[%s, %s, %d]", pszSimpleFileName, pcszFuncName, u32LineNum);
            if(i32PrintStrRes <= 0)
            {
                printf("VOS_Snprintf_S failed(%d)!\n",i32PrintStrRes);
            }
        }

        /*�������ģ����Ϊ�ⲿ����������������������ڲ������ģ��ʴ˴�ֻ��ģ����
        ���кϷ��Դ���*/
        if (NULL == pcszModName)
        {
            pcszModName = "ICS_LOG";
        }
        else if (ICS_LOG_TAG_LENGTH <= strlen(pcszModName))
        {
            pcszModName = "ICS_LOG";
        }

#ifdef __LINUX__
#if !defined (SME_RLS)
        if(g_fdAdaptLog < 0)
        {
            g_fdAdaptLog = open(SME_LOG_DIR, O_RDONLY, S_IRUSR);
        }
        if (g_fdAdaptLog >= 0)
        {
            //close(g_fdAdaptLog);
            //g_fdAdaptLog = -1;
            V_UINT32 u32Level = LevelMap(eLogLevel);
            LogOut((E_ICS_LOG_LEVEL)u32Level, pcszModName, "%s", acBuf);
            VOS_ThdMutexUnLock(&g_stLogLock);
            return;
        }
#endif
        ICS_Adapter_Log(eLogLevel, pcszModName, pszSimpleFileName, pcszFuncName, u32LineNum, acBuf);
#else
        V_UINT32 u32Level = LevelMap(eLogLevel);
        LogOut((E_ICS_LOG_LEVEL)u32Level, pcszModName, "%s", acBuf);
#endif
    }
    VOS_ThdMutexUnLock(&g_stLogLock);

    return;
}
/*lint -restore * */

/*****************************************************************************
 �� �� ��  : ICS_SetLogSwitch
 ��������  : ����ĳ������־����
 �������  : IN E_ICS_LOG_LEVEL eLogLevel      :��־����
             IN E_ICS_LOG_SWITCH eDebugSwitch  :��־����
 �������  : ��
 �� �� ֵ  : V_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_SetLogSwitch(IN E_ICS_LOG_LEVEL eLogLevel,
                        IN E_ICS_LOG_SWITCH eDebugSwitch)
{
    if (eLogLevel < ICS_LOG_BUTT && eLogLevel >= ICS_LOG_VERBOSE
        && (ICS_LOG_SWITCH_OFF == eDebugSwitch
            || ICS_LOG_SWITCH_ON == eDebugSwitch))
    {
        VOS_ThdMutexLock(&g_stLogLock);
        g_aeLogSwitch[eLogLevel] = eDebugSwitch;
        VOS_ThdMutexUnLock(&g_stLogLock);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ICS_GetLogSwitchStatus
 ��������  : ��ȡĳ������־����
 �������  : IN E_ICS_LOG_LEVEL eLogLevel        :��־����
 �������  : OUT E_ICS_LOG_SWITCH *peDebugSwitch :��־���� ָ��
 �� �� ֵ  : V_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_UINT32 ICS_GetLogSwitchStatus(IN E_ICS_LOG_LEVEL eLogLevel,
                                OUT E_ICS_LOG_SWITCH* peDebugSwitch)
{
    V_UINT32 u32Result = ICS_FAIL;

    if (NULL != peDebugSwitch && eLogLevel < ICS_LOG_BUTT
        && eLogLevel >= ICS_LOG_VERBOSE)
    {
        VOS_ThdMutexLock(&g_stLogLock);
        *peDebugSwitch = g_aeLogSwitch[eLogLevel];
        u32Result = ICS_SUCCESS;
        VOS_ThdMutexUnLock(&g_stLogLock);
    }

    return u32Result;
}

/*****************************************************************************
 �� �� ��  : ICS_SetLogLevel
 ��������  : ������־����Ⱥ������ָ������֮��(����ָ�����)����־���ض��򿪣�
             ֮�µĶ��ر�
 �������  : IN E_ICS_LOG_LEVEL eLogLevel  :��־����
 �������  : ��
 �� �� ֵ  : V_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_SetLogLevel(IN E_ICS_LOG_LEVEL eLogLevel)
{
    V_UINT32 u32Inc;

    VOS_ThdMutexLock(&g_stLogLock);

    for (u32Inc = ICS_LOG_VERBOSE; u32Inc < ICS_LOG_BUTT; u32Inc++)
    {
        g_aeLogSwitch[u32Inc] = ICS_LOG_SWITCH_OFF;
    }
    //lint -e825
    switch (eLogLevel)
    {
        case ICS_LOG_VERBOSE:
            g_aeLogSwitch[ICS_LOG_VERBOSE] = ICS_LOG_SWITCH_ON;
            /*�˴�Ҫֱ�ӽ����¸�case������ʡȥbreak*/
        case ICS_LOG_DEBUG:
            g_aeLogSwitch[ICS_LOG_DEBUG] = ICS_LOG_SWITCH_ON;
            /*�˴�Ҫֱ�ӽ����¸�case������ʡȥbreak*/
        case ICS_LOG_INFO:
            g_aeLogSwitch[ICS_LOG_INFO] = ICS_LOG_SWITCH_ON;
            /*�˴�Ҫֱ�ӽ����¸�case������ʡȥbreak*/
        case ICS_LOG_WARNING:
            g_aeLogSwitch[ICS_LOG_WARNING] = ICS_LOG_SWITCH_ON;
            /*�˴�Ҫֱ�ӽ����¸�case������ʡȥbreak*/
        case ICS_LOG_ERROR:
            g_aeLogSwitch[ICS_LOG_ERROR] = ICS_LOG_SWITCH_ON;
            break;
            /* BEGIN: modified by y00207417 for coverity, ����2014/4/12*/
        default:
            g_aeLogSwitch[ICS_LOG_ERROR] = ICS_LOG_SWITCH_ON;
            break;
            /* END: modified by y00207417 for coverity, ����2014/4/12*/
    }
    //lint +e825
    VOS_ThdMutexUnLock(&g_stLogLock);

    return;
}

/*****************************************************************************
 �� �� ��  : ICS_GetLogLevel
 ��������  : ��ȡ��־����
 �������  : ��
 �������  : ��
 �� �� ֵ  : E_ICS_LOG_LEVEL :��־����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��8��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
E_ICS_LOG_LEVEL ICS_GetLogLevel()
{
    V_UINT32 u32Inc;

    VOS_ThdMutexLock(&g_stLogLock);

    for (u32Inc = ICS_LOG_VERBOSE; u32Inc < ICS_LOG_BUTT; u32Inc++)
    {
        if (ICS_LOG_SWITCH_ON == g_aeLogSwitch[u32Inc])
            break;
    }

    VOS_ThdMutexUnLock(&g_stLogLock);

    return (E_ICS_LOG_LEVEL)u32Inc;
}


/*****************************************************************************
 �� �� ��  : ICS_SetLogStyle
 ��������  : ������־�ķ�񣬰�����Լ�ͺ���ϸ��
 �������  : IN E_ICS_LOG_STYLE eLogStyle  :��־���
 �������  : ��
 �� �� ֵ  : V_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   : t00164602
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_SetLogStyle(IN E_ICS_LOG_STYLE eLogStyle)
{
    if (ICS_LOG_STYLE_SIMPLE == eLogStyle || ICS_LOG_STYLE_DETAILED == eLogStyle)
    {
        VOS_ThdMutexLock(&g_stLogLock);
        g_eLogStyle = eLogStyle;
        VOS_ThdMutexUnLock(&g_stLogLock);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ICS_FlushLogBuff
 ��������  : ������������־��Ϣ������ļ�
 �������  :
             ...
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_FlushLogBuff()
{
#if !defined (SME_RLS)
    VOS_ThdMutexLock(&g_stLogLock);
#ifdef WIN32
    if(g_hfLog)
    {
        fwrite(g_acLogBuf, 1, g_iLogBufIdx, g_hfLog);
        fflush(g_hfLog);
        g_iLogBufIdx = 0;
    }
#else
    if(g_fdLog >= 0)
    {
        V_INT32 i32Ret = write(g_fdLog, g_acLogBuf, g_iLogBufIdx);
        if(i32Ret != g_iLogBufIdx)
        {
            printf("write error!");
        }
        if(i32Ret < 0)
        {
            i32Ret = 0;
        }
        g_u32LogSize += (V_UINT32)i32Ret;
        g_iLogBufIdx = 0;
    }
#endif
    VOS_ThdMutexUnLock(&g_stLogLock);
#endif

    return;
}

/*lint -restore * */
