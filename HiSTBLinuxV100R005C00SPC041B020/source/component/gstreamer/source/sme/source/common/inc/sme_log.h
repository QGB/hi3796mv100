/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sme_log.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2011��10��10��
  ����޸�   :
  ��������   : ICS�ն����ƽ̨��־ϵͳ�������־�ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��10��10��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __ICS_LOG_H__
#define __ICS_LOG_H__

#include "osal_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/
/*������־ϵͳ�Ŀ���ö��*/
typedef enum e_ICS_LogSwitch{
    ICS_LOG_SWITCH_OFF    = 0,
    ICS_LOG_SWITCH_ON     = 1,
}E_ICS_LOG_SWITCH;

/*������־ϵͳ�ĸ�ʽö�٣����������־����ϸ�̶ȶ�������������־
1. ������־��ֻ������־�����ݣ�
2. ��������־��������־���ݡ��ļ������кţ�*/
typedef enum e_ICS_LogStyle{
    ICS_LOG_STYLE_SIMPLE    = 0,
    ICS_LOG_STYLE_DETAILED  = 1,
}E_ICS_LOG_STYLE;

/*��һ��־����ö��*/
typedef enum e_ICS_LogLevel{
    ICS_LOG_VERBOSE    = 0,
    ICS_LOG_DEBUG      = 1,
    ICS_LOG_INFO       = 2,
    ICS_LOG_WARNING    = 3,
    ICS_LOG_ERROR      = 4,
    ICS_LOG_BUTT
}E_ICS_LOG_LEVEL;

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
/*������־��ģ�������ⲿʹ����־ϵͳʱ�趨���Լ���ģ�������������壬ϵͳĬ��
��ģ��������ΪICS_LOG,������ƽ̨������*/
#ifndef MOD_NAME
#define MOD_NAME "SME"
#endif

/*����ƽ̨����־��ӡ���������־ϵͳ�Ŀ���
1. ��ƽ̨��־���뿪��ICS_RELEASE_VERSIONδ�������򿪣���ô����־ϵͳ�������־*/

#ifdef ICS_RELEASE_VERSION
#define ICS_LOGV(pccFmt,...) ((V_VOID)0)
#define ICS_LOGI(pccFmt,...) ((V_VOID)0)
#define ICS_LOGW(pccFmt,...) ICS_Log(ICS_LOG_WARNING, MOD_NAME,\
                                                __FILE__, __FUNCTION__, __LINE__, pccFmt,##__VA_ARGS__)
#define ICS_LOGD(pccFmt,...) ((V_VOID)0)
#define ICS_LOGE(pccFmt,...) ICS_Log(ICS_LOG_ERROR, MOD_NAME,\
                                                __FILE__, __FUNCTION__, __LINE__, pccFmt,##__VA_ARGS__)
#else
#define ICS_LOGV(pccFmt,...) ICS_Log(ICS_LOG_VERBOSE, MOD_NAME,\
                                                __FILE__, __FUNCTION__, __LINE__, pccFmt,##__VA_ARGS__)
#define ICS_LOGI(pccFmt,...) ICS_Log(ICS_LOG_INFO, MOD_NAME,\
                                                __FILE__, __FUNCTION__, __LINE__, pccFmt,##__VA_ARGS__)
#define ICS_LOGW(pccFmt,...) ICS_Log(ICS_LOG_WARNING, MOD_NAME,\
                                                __FILE__, __FUNCTION__, __LINE__, pccFmt,##__VA_ARGS__)
#define ICS_LOGD(pccFmt,...) ICS_Log(ICS_LOG_DEBUG, MOD_NAME,\
												__FILE__, __FUNCTION__, __LINE__, pccFmt,##__VA_ARGS__)
#define ICS_LOGE(pccFmt,...) ICS_Log(ICS_LOG_ERROR, MOD_NAME,\
                                                __FILE__, __FUNCTION__, __LINE__, pccFmt,##__VA_ARGS__)
#endif

/*���嵥����־������buff��С*/
#ifndef ICS_LOG_BUF_SIZE
#define ICS_LOG_BUF_SIZE 4096
#endif

/*������־ģ��ų��ȴ�С*/
#ifndef ICS_LOG_TAG_LENGTH
#define ICS_LOG_TAG_LENGTH 256
#endif

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
 /*****************************************************************************
 �� �� ��  : ICS_SetLogSwitch
 ��������  : ����ĳ������־����
 �������  : IN E_ICS_LOG_LEVEL eLogLevel      :��־����
             IN E_ICS_LOG_SWITCH eDebugSwitch  :��־����
 �������  : ��
 �� �� ֵ  : V_VOID
 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_SetLogSwitch(IN E_ICS_LOG_LEVEL eLogLevel, \
                        IN E_ICS_LOG_SWITCH eDebugSwitch);

/*****************************************************************************
 �� �� ��  : ICS_GetLogSwitchStatus
 ��������  : ��ȡĳ������־����
 �������  : IN E_ICS_LOG_LEVEL eLogLevel        :��־����
 �������  : OUT E_ICS_LOG_SWITCH *peDebugSwitch :��־���� ָ��
 �� �� ֵ  : V_UINT32
 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_UINT32 ICS_GetLogSwitchStatus(IN E_ICS_LOG_LEVEL eLogLevel, \
                                OUT E_ICS_LOG_SWITCH *peDebugSwitch);

/*****************************************************************************
 �� �� ��  : ICS_SetLogLevel
 ��������  : ������־����Ⱥ������ָ������֮��(����ָ�����)����־���ض��򿪣�
             ֮�µĶ��ر�
 �������  : IN E_ICS_LOG_LEVEL eLogLevel  :��־����
 �������  : ��
 �� �� ֵ  : V_VOID
 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_SetLogLevel(IN E_ICS_LOG_LEVEL eLogLevel);

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

E_ICS_LOG_LEVEL ICS_GetLogLevel();


/*****************************************************************************
 �� �� ��  : ICS_SetLogStyle
 ��������  : ������־�ķ�񣬰�����Լ�ͺ���ϸ��
 �������  : IN E_ICS_LOG_STYLE eLogStyle  :��־���
 �������  : ��
 �� �� ֵ  : V_VOID
 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_SetLogStyle(IN E_ICS_LOG_STYLE eLogStyle);

/*****************************************************************************
 �� �� ��  : ICS_Log
 ��������  : ��ӡ��־�������(�˽ӿڲ������ⲿʹ�ã��ⲿ��ʹ��ICS_LOGV/I/W/D/E)
 �������  : IN E_ICS_LOG_LEVEL eLogLevel     :��־����
             IN const V_CHAR *pcszModName     :��־ģ����
             IN const V_CHAR *pcszFileName    :��־�����ļ���
             IN const V_CHAR *pcszFuncName    :��־���ں�����
             IN V_UINT32 u32LineNum           :��־�����к�
             IN const V_CHAR * pcszFmt        :��־��ʽ���ַ���
             ...
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
V_VOID ICS_Log(IN E_ICS_LOG_LEVEL eLogLevel,
               IN const V_CHAR *pcszModName,
               IN const V_CHAR *pcszFileName,
               IN const V_CHAR *pcszFuncName,
               IN V_UINT32 u32LineNum,
               IN const V_CHAR *pcszFmt, ...);

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
V_VOID ICS_FlushLogBuff();


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ICS_LOG_H__ */
