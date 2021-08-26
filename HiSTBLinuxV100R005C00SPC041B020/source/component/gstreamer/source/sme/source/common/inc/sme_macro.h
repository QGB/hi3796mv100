/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sme_macro.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2012��12��6��
  ����޸�   :
  ��������   : ͨ�õĺ꣬���жϼ���־�ȵ�
  �����б�   :
  �޸���ʷ   :
  1.��    �� : 2012��12��6��
    ��    �� :
    �޸����� : �����ļ�

******************************************************************************/

#ifndef __UTILS_MACRO_H__
#define __UTILS_MACRO_H__

#include "sme_log.h"
#include <stdio.h>
#include <stdlib.h>
//#define FNAME __func__
//#define FNAME "[HMP_SMT]"

#ifdef ICS_LOG_PRINTV
#undef ICS_LOG_PRINTV
#endif
#define ICS_LOG_PRINTV ICS_LOGV

#ifdef ICS_LOG_PRINTD
#undef ICS_LOG_PRINTD
#endif
#define ICS_LOG_PRINTD ICS_LOGD

#ifdef ICS_LOG_PRINTI
#undef ICS_LOG_PRINTI
#endif
#define ICS_LOG_PRINTI ICS_LOGI

#ifdef ICS_LOG_PRINTW
#undef ICS_LOG_PRINTW
#endif
#define ICS_LOG_PRINTW ICS_LOGW

#ifdef ICS_LOG_PRINTE
#undef ICS_LOG_PRINTE
#endif
#define ICS_LOG_PRINTE ICS_LOGE


#ifdef WIN32
#ifndef strcasecmp
#define strcasecmp strcmpi
#endif
#endif

#define UTILS_ASSERT(cond)

#define UTILS_MSAFEDEL(pobj) \
	if(NULL != pobj)\
	{\
		delete pobj;\
		pobj = NULL;\
	}

#define UTILS_MTMPDEL(pobj) \
	if(NULL != pobj)\
	{\
		delete pobj;\
	}

#define UTILS_MSAFEDELA(pobj) \
	if(NULL != pobj)\
	{\
		delete [] pobj;\
		pobj = NULL;\
	}

#define UTILS_MTMPDELA(pobj) \
	if(NULL != pobj)\
	{\
		delete [] pobj;\
	}

#define UTILS_MSAFEFREE(p) \
	if(NULL != p)\
	{\
		free(p);\
		p = NULL;\
	}

#define UTILS_MTMPFREE(pobj) \
	if(NULL != pobj)\
	{\
		free(pobj);\
	}


#define UTILS_MAX(a, b) ((a) > (b) ? (a) : (b))

#define UTILS_MLOGD_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTD pszlog;\
	}

#define UTILS_MLOGE_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTE pszlog;\
	}

#define UTILS_MLOGW_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTW pszlog;\
	}

#define UTILS_RET_VAL_IF(cond, val) \
	if(cond)\
	{\
		return val;\
	}

#define UTILS_MLOGE_RET_VAL_IF(cond, val, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTE pszlog;\
		return val;\
	}

#define UTILS_MLOGW_RET_VAL_IF(cond, val, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTW pszlog;\
		return val;\
	}

#define UTILS_MLOGW_RET_IF(cond, pszlog) \
		if(cond)\
		{\
			ICS_LOG_PRINTW pszlog;\
			return ;\
		}


#define UTILS_MLOGE_RET_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTE pszlog;\
		return ;\
	}

#define UTILS_M_RET_IF(cond) \
	if(cond)\
	{\
		return;\
	}

#define UTILS_M_RET_VAL_IF(cond, val) \
	if(cond)\
	{\
		return (val);\
	}

#define UTILS_MLOGE_BRK_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTE pszlog;\
		break;\
	}

#define UTILS_MLOGW_BRK_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTW pszlog;\
		break;\
	}

#define UTILS_MLOGE_BRK_VAL_IF(cond, ret, val, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTE pszlog;\
		ret = val;\
		break;\
	}

#define UTILS_M_BRK_VAL_IF(cond, ret, val) \
		if(cond)\
		{\
			ret = val;\
			break;\
		}

#define UTILS_M_BRK_IF(cond) \
		if(cond)\
		{\
			break;\
		}


#define UTILS_MLOGW_BRK_VAL_IF(cond, ret, val, pszlog) \
		if(cond)\
		{\
			ICS_LOG_PRINTW pszlog;\
			ret = val;\
			break;\
		}

#define UTILS_MLOGE_BRK_FREE_IF(cond, val, pszlog) \
        if (cond)\
        {\
            ICS_LOGE pszlog;\
            free(val);\
            val = NULL;\
            break;\
        }

#define UTILS_MLOGE_BRK_DELTMP_IF(cond, val, pszlog) \
        if (cond)\
        {\
            ICS_LOGE pszlog;\
            delete val;\
            break;\
        }

#define UTILS_MLOGW_CTN_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTW pszlog;\
		continue;\
	}

#define UTILS_MLOGE_CTN_IF(cond, pszlog) \
	if(cond)\
	{\
		ICS_LOG_PRINTE pszlog;\
		continue;\
	}

#define UTILS_CTN_IF(cond) \
	if(cond)\
	{\
		continue;\
	}

#define UTILS_M_INVALID_ARGS(x) {(V_VOID)(x);}

#define UTILS_MMAX_VAL_TWO(a,b) (((a) > (b)) ? (a) : (b))
#define UTILS_MMIN_VAL_TWO(a,b) (((a) > (b)) ? (b) : (a))

//��������ʹ�ñ����ĺ궨�� ��������澯 �ڱ���ǰ��������
#define UTILS_PERMIT_UNUSE __attribute__((unused))

#ifdef  __cplusplus
# define UTILS_EXTERN_C_BEGIN  extern "C" {
# define UTILS_EXTERN_C_END    }
#else
# define UTILS_EXTERN_C_BEGIN
# define UTILS_EXTERN_C_END
#endif


#define UTILS_DUMP_TO_FILE(pszfName, data, len, pszfAttr)\
{\
    FILE* fp = fopen(pszfName, pszfAttr);\
    if(fp)\
    {\
        fwrite(data, 1, len, fp);\
        fclose(fp);\
    }\
}


#endif /* __UTILS_MACRO_H__ */
