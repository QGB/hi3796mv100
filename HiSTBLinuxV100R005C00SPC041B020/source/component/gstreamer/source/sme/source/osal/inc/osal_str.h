/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : vos_str.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年7月4日
  最近修改   :
  功能描述   : 字符串操作函数适配(目的:不同操作系统可能不同实现，尤其涉及到安全函数时)
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月4日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OSAL_STR__
#define __OSAL_STR__

#include <stdarg.h>
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

#ifdef OLD_VOS_VERSION
/*****************************************************************************
 函 数 名  : VOS_Strcpy
 功能描述  : 字符串拷贝,pszDst与pszSrc不能有地址重叠。
 输入参数  : V_CHAR* pszDst       :目标字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
             const V_CHAR* pszSrc :源字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
 输出参数  : V_CHAR* pszDst       :目标内存指针，不能为NULL，否则不可预知后果，
                                   可能crash。
 返 回 值  : V_CHAR*,返回指向pszDst内存块的指针。
 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_CHAR*
VOS_Strcpy(INOUT V_CHAR* pszDst, IN const V_CHAR* pszSrc);


/*****************************************************************************
 函 数 名  : VOS_Strncpy
 功能描述  : 字符串拷贝,pszDst与pszSrc不能有地址重叠。
 输入参数  : V_CHAR* pszDst       :目标字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
             const V_CHAR* pszSrc :源字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
             V_SIZE szLen         :拷贝的长度，字节数。
 输出参数  : V_CHAR* pszDst       :目标内存指针，不能为NULL，否则不可预知后果，
                                   可能crash。
 返 回 值  : V_CHAR*,返回指向pszDst内存块的指针。
 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_CHAR*
VOS_Strncpy(INOUT V_CHAR* pszDst, IN const V_CHAR* pszSrc, IN V_SIZE szLen);

/*****************************************************************************
 函 数 名  : VOS_Sprintf
 功能描述  : 格式化字符串拷贝
 输入参数  : V_CHAR* pszDst       :目标字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
             const V_CHAR* pszFmt :格式化字符串，可变参数，不能为NULL，
                                   否则不可预知后果，可能crash。
 输出参数  : V_CHAR* pszDst       :目标内存指针，不能为NULL，否则不可预知后果，
                                   可能crash。
 返 回 值  : V_INT32,出错返回小于0；否则返回拷贝的字节数,错误码见errno(linux).
 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Sprintf(INOUT V_CHAR* pszDst, IN const V_CHAR* pszFmt, ...);

/*****************************************************************************
 函 数 名  : VOS_Snprintf
 功能描述  : 格式化字符串拷贝
 输入参数  : V_CHAR* pszDst       :目标字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
             V_SIZE szLen         :拷贝的长度，字节数。如果格式化字符串<szLen，
                                   那么全部拷贝，然后添加'\0';如果格式化字符串
                                   >=szLen，那么拷贝szLen-1,最后添加'\0'。it must > 1.
             const V_CHAR* pszFmt :格式化字符串，可变参数，不能为NULL，
                                   否则不可预知后果，可能crash。
 输出参数  : V_CHAR* pszDst       :目标内存指针，不能为NULL，否则不可预知后果，
                                   可能crash。
 返 回 值  : V_INT32,出错返回小于0；否则返回拷贝的字节数,错误码见errno(linux).
 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Snprintf(INOUT V_CHAR* pszDst, IN V_SIZE szLen, IN const V_CHAR* pszFmt, ...);

/*****************************************************************************
 函 数 名  : VOS_Vsnprintf
 功能描述  : 格式化字符串拷贝
 输入参数  : V_CHAR* pszDst       :目标字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
             V_SIZE szLen         :拷贝的长度，字节数,it must > 1.
             const V_CHAR* pszFmt :格式化字符串，可变参数，不能为NULL，
                                   否则不可预知后果，可能crash。
             va_list stVa         :可变参数列表结构
 输出参数  : V_CHAR* pszDst       :目标内存指针，不能为NULL，否则不可预知后果，
                                   可能crash。
 返 回 值  : V_INT32,出错返回小于0；否则返回拷贝的字节数,错误码见errno(linux).
 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Vsnprintf(INOUT V_CHAR* pszDst, IN V_SIZE szLen, IN const V_CHAR* pszFmt,
    IN va_list stVar);

/*****************************************************************************
 函 数 名  : VOS_Sscanf
 功能描述  : 格式化字符串拷贝
 输入参数  : V_CHAR* pszSrc       :源字符串指针，不能为NULL，否则不可预知后果，
                                   可能crash。
             const V_CHAR* pszFmt :格式化字符串，可变参数，不能为NULL，
                                   否则不可预知后果，可能crash。
 输出参数  : V_CHAR* pszDst       :目标内存指针，不能为NULL，否则不可预知后果，
                                   可能crash。
 返 回 值  : V_INT32,出错返回小于0；否则返回参数个数,错误码见errno(linux).
 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Sscanf(IN const V_CHAR* pszSrc, IN const V_CHAR* pszFmt, ...);
#endif


//安全函数接口定义:

typedef enum __tagVOSStrErr
{
    E_VOS_STR_ENONE         = 0, //正确
    E_VOS_STR_EINVAL        = 22,    //参数非法
    E_VOS_STR_ERANGE        = 34,//参数超出范围
    E_VOS_STR_EINVAL_RST    = (22 | 0x80),  //参数非法，并复位dest
    E_VOS_STR_ERANGE_RST    = (34 | 0x80),//参数超出范围，并复位dest
    E_VOS_STR_EOVERLAP_RST  = (54 | 0x80),//内存重叠，并复位dest
}E_VOS_STR_ERR;

//#define S_STR_MAX SECUREC_STRING_MAX_LEN //((0x7fffffffUL))
/*****************************************************************************
 函 数 名  : VOS_Strcpy_S
 功能描述  : 字符串拷贝,pszDst与pszSrc不能有地址重叠。
 输入参数  : IN V_SIZE szDstMax   :目标字符串内存最大size(B)
             const V_CHAR* pszSrc :源字符串指针
 输出参数  : V_CHAR* pszDst       :目标内存指针
 返 回 值  : E_VOS_STR_ERR,成功返回E_VOS_STR_ENONE，其他见下表
 ---------------------------------------------------------------------------------------|
 | pszDst  | szDstMax         | pszSrc      | 返回值               | pszDst内容         |
 ---------------------------------------------------------------------------------------|
 | 任何    | 0 或 > S_STR_MAX | 任何        | E_VOS_STR_ERANGE     |  不修改            |
 ---------------------------------------------------------------------------------------|
 | NULL    | > 0且<= S_STR_MAX| 任何        | E_VOS_STR_EINVAL     |  不修改            |
 ---------------------------------------------------------------------------------------|
 | 非NULL  | > 0且<= S_STR_MAX| NULL        | E_VOS_STR_EINVAL_RST | strDest[0] = '\0'  |
 ---------------------------------------------------------------------------------------|
 | 非NULL  | > 0且<= S_STR_MAX| 非NULL      | E_VOS_STR_ERANGE_RST | strDest[0] = '\0'  |
 |         |且小于（源缓冲区长|             |                      |                    |
 |         |度 + 1）          |             |                      |                    |
 ---------------------------------------------------------------------------------------
 | 非NULL，|> 0且<= S_STR_MAX | 非NULL,     |E_VOS_STR_EOVERLAP_RST| strDest[0] = '\0'  |
 | 与strSrc|                  |与strDest重叠|                      |                    |
 | 重叠    |                  |             |                      |                    |
 ----------------------------------------------------------------------------------------
 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API E_VOS_STR_ERR
VOS_Strcpy_S(INOUT V_CHAR* pszDst, IN V_SIZE szDstMax, IN const V_CHAR* pszSrc);

/*****************************************************************************
 函 数 名  : VOS_Strncpy_S
 功能描述  : 字符串拷贝,pszDst与pszSrc不能有地址重叠。
 输入参数  : IN V_SIZE szDstMax   :目标字符串内存最大size(B)
             const V_CHAR* pszSrc :源字符串指针
             V_SIZE szCount       :要拷贝的字符个数
 输出参数  : V_CHAR* pszDst       :目标内存指针
 返 回 值  : E_VOS_STR_ERR,成功返回E_VOS_STR_ENONE，其他见下表
 ----------------------------------------------------------------------------------------------------------|
 | pszDst  | szDstMax         | pszSrc      | szCount          | 返回值               | pszDst 内容        |
 ----------------------------------------------------------------------------------------------------------|
 | 任何    | 0 或 > S_STR_MAX | 任何        | 任何             | E_VOS_STR_ERANGE     |  不修改            |
 ----------------------------------------------------------------------------------------------------------|
 | NULL    | > 0且<= S_STR_MAX| 任何        | 任何             | E_VOS_STR_EINVAL     |  不修改            |
 ----------------------------------------------------------------------------------------------------------|
 | 非NULL  | > 0且<= S_STR_MAX| NULL        | 任何             | E_VOS_STR_EINVAL_RST | strDest[0] = '\0'  |
 ----------------------------------------------------------------------------------------------------------|
 | 非NULL  | > 0且<= S_STR_MAX| 非NULL      | > S_STR_MAX      | E_VOS_STR_ERANGE_RST | strDest[0] = '\0'  |
 ----------------------------------------------------------------------------------------------------------|
 | 非NULL  | > 0且<= S_STR_MAX| 非NULL      | <= S_STR_MAX     | E_VOS_STR_ERANGE_RST | strDest[0] = '\0'  |
 |         |且小于szCount     |             |                  |                      |                    |
 ----------------------------------------------------------------------------------------------------------
 | 非NULL，|> 0且<= S_STR_MAX | 非NULL,     | <= S_STR_MAX     |E_VOS_STR_EOVERLAP_RST| strDest[0] = '\0'  |
 | 与strSrc|                  |与strDest重叠|                  |                      |                    |
 | 重叠    |                  |             |                  |                      |                    |
 -----------------------------------------------------------------------------------------------------------

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API E_VOS_STR_ERR
VOS_Strncpy_S(INOUT V_CHAR* pszDst, IN V_SIZE szDstMax, IN const V_CHAR* pszSrc,
  IN V_SIZE szCount);

/*****************************************************************************
 函 数 名  : VOS_Sprintf_S
 功能描述  : 格式化字符串输出
 输入参数  : IN V_SIZE szDstMax   :目标字符串内存最大size(B)
             const V_CHAR* pszFmt :格式化字符串，可变参数，
 输出参数  : V_CHAR* pszDst       :目标内存指针
 返 回 值  : 成功返回写入的字符个数，其他见下表
 ---------------------------------------------------------------------------------------|
 | pszDst  | szDstMax         | pszFmt      | 返回值               | pszDst内容         |
 ---------------------------------------------------------------------------------------|
 | NULL    | 任何             | 任何        | -1                   |  不修改            |
 ---------------------------------------------------------------------------------------|
 | 任何    | 0                | 任何        | -1                   |  不修改            |
 ---------------------------------------------------------------------------------------|
 | 非NULL  | > S_STR_MAX      | 任何        | -1                   | strDest[0] = '\0'  |
 ---------------------------------------------------------------------------------------|
 | 非NULL  | > 0              | NULL        | -1                   | strDest[0] = '\0'  |
 ---------------------------------------------------------------------------------------
 | 非NULL，|小于等于格式化后的| 合法,       | -1                   | strDest[0] = '\0'  |
 |         |实际字符串长度    |             |                      |                    |
 ----------------------------------------------------------------------------------------
 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Sprintf_S(INOUT V_CHAR* pszDst, IN V_SIZE szDstMax, IN const V_CHAR* pszFmt, ...);

/*****************************************************************************
 函 数 名  : VOS_Snprintf_S
 功能描述  : 格式化字符串输出
 输入参数  : IN V_SIZE szDstMax   :目标字符串内存最大size(B)
             V_SIZE szCount       :要输出的字符个数
             const V_CHAR* pszFmt :格式化字符串
 输出参数  : V_CHAR* pszDst       :目标内存指针
 返 回 值  : 成功返回输出字符个数，其他见下表
  ----------------------------------------------------------------------------------------------------------|
 | pszDst  | szDstMax         | szCount          | pszFmt      | 返回值               | pszDst 内容        |
 ----------------------------------------------------------------------------------------------------------|
 | 任何    | 任何             | 任何             | NULL        | -1                   | 若pszDst!=NULL且   |
 |         |                  |                  |             |                      | szDstMax>0,则      |
 |         |                  |                  |             |                      | strDest[0] = '\0'; |
 |         |                  |                  |             |                      | 否则不修改         |
 ----------------------------------------------------------------------------------------------------------|
 | NULL    | 任何             | 任何             | 任何        | -1                   |  不修改            |
 ----------------------------------------------------------------------------------------------------------|
 | 任何    | 0                | 任何             | 任何        | -1                   |  不修改            |
 ----------------------------------------------------------------------------------------------------------|
 | 非NULL  | > S_STR_MAX      | 任何             | 任何        | -1                   | strDest[0] = '\0'  |
 ----------------------------------------------------------------------------------------------------------|
 | 非NULL  | <= min(count,格式| <= S_STR_MAX - 1 | 合法        | -1                   | strDest[0] = '\0'  |
 |         |化后实际字符长度) |                  |             |                      |                    |
 ----------------------------------------------------------------------------------------------------------
 | 非NULL，|> 0且<= S_STR_MAX | <格式化后实际长度| 任何        | -1                   | strDest包含截断的  |
 |         |                  |                  |             |                      | count个字符        |
 -----------------------------------------------------------------------------------------------------------

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Snprintf_S(INOUT V_CHAR* pszDst, IN V_SIZE szDstMax, IN V_SIZE szCount,
  IN const V_CHAR* pszFmt, ...);

/*****************************************************************************
 函 数 名  : VOS_Vsnprintf_S
 功能描述  : 格式化字符串输出
 输入参数  : IN V_SIZE szDstMax   :目标字符串内存最大size(B)
             V_SIZE szCount       :要输出的字符个数
             const V_CHAR* pszFmt :格式化字符串
             IN va_list stVarLst  :指向参数化列表的指针
 输出参数  : V_CHAR* pszDst       :目标内存指针
 返 回 值  : 成功返回输出字符个数，其他见下表
  ----------------------------------------------------------------------------------------------------------|
 | pszDst  | szDstMax         | szCount          | pszFmt      | 返回值               | pszDst 内容        |
 ----------------------------------------------------------------------------------------------------------|
 | 任何    | 任何             | 任何             | NULL        | -1                   | 若pszDst!=NULL且   |
 |         |                  |                  |             |                      | szDstMax>0,则      |
 |         |                  |                  |             |                      | strDest[0] = '\0'; |
 |         |                  |                  |             |                      | 否则不修改         |
 ----------------------------------------------------------------------------------------------------------|
 | NULL    | 任何             | 任何             | 任何        | -1                   |  不修改            |
 ----------------------------------------------------------------------------------------------------------|
 | 任何    | 0                | 任何             | 任何        | -1                   |  不修改            |
 ----------------------------------------------------------------------------------------------------------|
 | 非NULL  | > S_STR_MAX      | 任何             | 任何        | -1                   | strDest[0] = '\0'  |
 ----------------------------------------------------------------------------------------------------------|
 | 非NULL  | <= min(count,格式| <= S_STR_MAX - 1 | 合法        | -1                   | strDest[0] = '\0'  |
 |         |化后实际字符长度) |                  |             |                      |                    |
 ----------------------------------------------------------------------------------------------------------
 | 非NULL，|> 0且<= S_STR_MAX | <格式化后实际长度| 任何        | -1                   | strDest包含截断的  |
 |         |                  |                  |             |                      | count个字符        |
 -----------------------------------------------------------------------------------------------------------

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Vsnprintf_S(INOUT V_CHAR* pszDst, IN V_SIZE szDstMax, IN V_SIZE szCount,
  IN const V_CHAR* pszFmt, IN va_list stVarLst);

/*****************************************************************************
 函 数 名  : VOS_Sscanf_S
 功能描述  : 格式化字符串输入
 输入参数  : const V_CHAR* pszSrc :要从中读取数据的buffer
             const V_CHAR* pszFmt :格式化字符串，可变参数，
 输出参数  : 无
 返 回 值  : 成功返回读取的字段数，当未读取到数据时返回0;当错误发生或者初次转换就到达结尾，
             具体其他见下表
 ---------------------------------------------------------------------------------------|
 | pszSrc  | pszFmt      | ...可选参数      | 返回值               | pszDst内容         |
 ---------------------------------------------------------------------------------------|
 | NULL    | 任何        | 任何             | -1                   |  不修改            |
 ---------------------------------------------------------------------------------------|
 | 任何    | NULL        | 任何             | -1                   |  不修改            |
 ---------------------------------------------------------------------------------------|
 | 非NULL  | 非NULL      | 合法             | -1                   |  不修改            |
 | 且长度为|             |                  |                      |                    |
 | 0或>    |             |                  |                      |                    |
 |S_STR_MAX|             |                  |                      |                    |
 ---------------------------------------------------------------------------------------|
 | 非NULL  | 非法        | 任何             | -1                   |  不修改            |
 | 且长度< |             |                  |                      |                    |
 |S_STR_MAX|             |                  |                      |                    |
 ---------------------------------------------------------------------------------------|
 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_API V_INT32
VOS_Sscanf_S(INOUT const V_CHAR* pszSrc, IN const V_CHAR* pszFmt, ...);


#ifdef __cplusplus
}
#endif

#endif// __OSAL_MEM__
