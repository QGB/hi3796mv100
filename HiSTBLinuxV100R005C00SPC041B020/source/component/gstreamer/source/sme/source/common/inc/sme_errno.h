/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sme_errno.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2011��10��26��
  ����޸�   :
  ��������   : ICS�ն����ƽ̨�Ĵ����빫��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��10��26��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __ICS_ERRNO_H__
#define __ICS_ERRNO_H__

#include "osal_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

/*����ƽ̨����*/
#define ICS_ASSERT(a) ((void *)0)

/**
 *@ingroup linux_sme_base Linux
 *����:����ģ���ڵ�˽�д����롣(ģ��ID + ģ���ھ�������� = �����Ĵ�����)
 *������˵����ERRNO����
 *1�����ڱ�ʶһ�����ռ�������ֽ�
 *2�����á����������룫˽�д����롱�Ķ��巽ʽ
 *3������������ȫ��Ψһ��ϵͳ�д󲿷ֵķ���ֵ�����ù��������룩
 *4��˽�д��������ģ���ڲ�Ψһ���ɣ���ͬģ����ERRNO������ͬ��
 *��Χ˵��:
 *0     ICS_OK����������룬����ɹ�
 *0X1000 - 0X1FFF ģ��˽�д����룬˳����
 *0X2000 - 0X2FFF ���������룬����˳����
 *0X3000 - 0XFFFF ��ʱ���������в����ֶα���Ϣ��ʶʹ��
 *-1 ICS_ERROR�����������
 *����ID��ERRID����
 *1�����ڱ�ʶĳ��ģ���ĳ�����ռ���ĸ��ֽڣ�Ϊ���������㶨���������
 *2������ MID���������ֽڣ���ERRNO���������ֽڣ�
 *---------------------------------
 *|31-----------16|15-------------0|
 *---------------------------------
 *ģ��ID         ģ���ڵĴ�����id
*/
#define ICS_ERRNO_BEGIN_USER              0X1000                     /* ģ���ڵ�˽�д��������ֵ */
#define ICS_ERRNO_BEGIN_COMM              0X2000                     /* ģ���ڵĹ������������ֵ */
#define ICS_ERRNO_MK_USERNO(n)            (ICS_ERRNO_BEGIN_USER+(n)) /* ����ģ���ڵ�˽�д����� n+����ֵ */
#define ICS_ERRNO_MK_COMMNO(n)            (ICS_ERRNO_BEGIN_COMM+(n)) /* ����ģ���ڵĹ��������� n+����ֵ */
#define ICS_MID_MK_HI16(MID)              ((MID) << 16)              /* ģ��ID */
#define ICS_ERRNO_MK_MODUSER(MID, n)      ICS_MID_MK_HI16(MID) + ICS_ERRNO_MK_USERNO(n) /* ģ����˽�д����� */
#define ICS_ERRNO_MK_MODCOMM(MID, n)      ICS_MID_MK_HI16(MID) + ICS_ERRNO_MK_COMMNO(n) /* ģ���ڹ��д����� */

/**
 *@ingroup linux_sme_base Linux
 *����:�û�ֱ��ʹ�õ���Ϣ��ֵ��(ģ��ID + ģ���ھ�����Ϣ�� = ��������Ϣ��)
 *��ϢID������ID����ͳһ�ı�����򣬱��뷶Χ�ֶΣ�
 *1����Ϣ��ռ�������ֽ�
 *2����ϢID �� ģ��ID���������ֽڣ� �� ��Ϣ�루�������ֽڣ�
 *3����Ϣ��ֶ�����:
 *��Χ˵��:
 *0X0000 - 0X2FFF ������
 *0X3000 - 0X2FFF �û�ֱ��ʹ�õ���Ϣ��
 *0X3FFF - 0X7FFF ��־ɨ�蹤�����ɵ���Ϣ��
 *0X8000 - 0XFFFF ����
 *���ڲ�Ʒ���ж��������£�ֻҪ��ģ��ID�Ķ��屣��Ψһ����Ϣ���
 *���嶨�������ȫ�ɲ�Ʒ���о���
 */
#define ICS_INFNO_BEGIN                   0X3000
#define ICS_INFID_MAKE(MID, INFNO)        ((MID<<16) + ICS_INFNO_BEGIN + INFNO)

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

#ifndef ICS_SUCCESS
#define ICS_SUCCESS 0
#endif

#ifndef ICS_FAIL
#define ICS_FAIL 1
#endif

#ifndef ICS_ERROR
#define ICS_ERROR 0xffffffff
#endif

/**Common Error Code */
#define ICS_OK                     (0)  /* ��ȷ */

/**
*@ingroup ICS_base
*0x1 ����Ȩ�����ޡ�
*/
#define ICS_ERRNO_PERM             (1)  /* Operation not permitted */

/**
*@ingroup sme_base
*0x2 �ļ������ļ��в����ڡ�
*/
#define ICS_ERRNO_NOENT            (2)  /* No such file or directory */

/**
*@ingroup sme_base
*0x3 ���̻����̲߳����ڡ�
*/
#define ICS_ERRNO_SRCH             (3)  /* No such process */

/**
*@ingroup sme_base
*0x4 �������ж��µ��á�
*/
#define ICS_ERRNO_INTR             (4)  /* Interrupted system call */

/**
*@ingroup sme_base
*0x5 IO����ʧ�ܡ�
*/
#define ICS_ERRNO_IO               (5)  /* I/O error */

/**
*@ingroup sme_base
*0x6 ������豸���ߵ�ַ��
*/
#define ICS_ERRNO_NXIO             (6)  /* No such device or address */

/**
*@ingroup sme_base
*0x7 �����б������
*/
#define ICS_ERRNO_2BIG             (7)  /* Argument list too long */

/**
*@ingroup sme_base
*0x8 ��ִ���ļ���ʽ����
*/
#define ICS_ERRNO_NOEXEC           (8)  /* ICS_ERRNO_xec format error */

/**
*@ingroup sme_base
*0x9 �ļ���������
*/
#define ICS_ERRNO_BADF             (9)  /* Bad file number */

/**
*@ingroup sme_base
*0xA �ӽ��̲����ڡ�
*/
#define ICS_ERRNO_CHILD           (10)  /* No child processes */

/**
*@ingroup sme_base
*0xB ���Ժ����ԡ�
*/
#define ICS_ERRNO_AGAIN           (11)  /* Try again */

/**
*@ingroup sme_base
*0xC �ڴ治�㡣
*/
#define ICS_ERRNO_NOMEM           (12)  /* Out of memory */

/**
*@ingroup sme_base
*0xD Ȩ�����ޡ�
*/
#define ICS_ERRNO_ACCES           (13)  /* Permission denied */

/**
*@ingroup sme_base
*0xE ��ַ����
*/
#define ICS_ERRNO_FAULT           (14)  /* Bad address */

/**
*@ingroup sme_base
*0xF ���豸����ʧ�ܡ�
*/
#define ICS_ERRNO_NOTBLK          (15)  /* Block device required */

/**
*@ingroup sme_base
*0x10 �豸������Դ��æ��
*/
#define ICS_ERRNO_BUSY            (16)  /* Device or resource busy */

/**
*@ingroup sme_base
*0x11 �ļ��Ѿ����ڡ�
*/
#define ICS_ERRNO_EXIST           (17)  /* File exists */

/**
*@ingroup sme_base
*0x12 ���豸����ʧ�ܡ�
*/
#define ICS_ERRNO_XDEV            (18)  /* Cross-device link */

/**
*@ingroup sme_base
*0x13 �豸�����ڡ�
*/
#define ICS_ERRNO_NODEV           (19)  /* No such device */

/**
*@ingroup sme_base
*0x14 ��Ŀ¼�ļ���
*/
#define ICS_ERRNO_NOTDIR          (20)  /* Not a directory */

/**
*@ingroup sme_base
*0x15 Ŀ¼�ļ���
*/
#define ICS_ERRNO_ISDIR           (21)  /* Is a directory */

/**
*@ingroup sme_base
*0x16 ��������
*/
#define ICS_ERRNO_INVAL           (22)  /* Invalid argument */

/**
*@ingroup sme_base
*0x17 �ļ��б������
*/
#define ICS_ERRNO_NFILE           (23)  /* File table overflow */

/**
*@ingroup sme_base
*0x18 ���ļ����ࡣ
*/
#define ICS_ERRNO_MFILE           (24)  /* Too many open files */

/**
*@ingroup sme_base
*0x19 �Ǵ�ӡ�豸��
*/
#define ICS_ERRNO_NOTTY           (25)  /* Not a typewriter */

/**
*@ingroup sme_base
*0x1A �ı��ļ���æ��
*/
#define ICS_ERRNO_TXTBSY          (26)  /* Text file busy */

/**
*@ingroup sme_base
*0x1B �ļ�����
*/
#define ICS_ERRNO_FBIG            (27)  /* File too large */

/**
*@ingroup sme_base
*0x1C �豸û���㹻�Ŀռ䡣
*/
#define ICS_ERRNO_NOSPC           (28)  /* No space left on device */

/**
*@ingroup sme_base
*0x1D �Ƿ�����
*/
#define ICS_ERRNO_SPIPE           (29)  /* Illegal seek */

/**
*@ingroup sme_base
*0x1E ֻ���ļ�ϵͳ��
*/
#define ICS_ERRNO_ROFS            (30)  /* Read-only file system */

/**
*@ingroup sme_base
*0x1F ���ӹ��ࡣ
*/
#define ICS_ERRNO_MLINK           (31)  /* Too many links */

/**
*@ingroup sme_base
*0x20 �ܵ��Ͽ���
*/
#define ICS_ERRNO_PIPE            (32)  /* Broken pipe */

/**
*@ingroup sme_base
*0x21 ����������Χ��
*/
#define ICS_ERRNO_DOM             (33)  /* Math argument out of domain of func */

/**
*@ingroup sme_base
*0x22 ��ѧ����������������Χ��
*/
#define ICS_ERRNO_RANGE           (34)  /* Math result not representable */

/* Posix defines these to be the same */
/**
*@ingroup sme_base
*0x23 ���ᷢ����Դ������
*/
#define ICS_ERRNO_DEADLK          (35)             /* Resource deadlock would occur */

/**
*@ingroup sme_base
*0x23 ���ᷢ����Դ������
*/
#define ICS_ERRNO_DEADLOCK        ICS_ERRNO_DEADLK /* Resource deadlock would occur */

/**
*@ingroup sme_base
*0x24 �ļ���������
*/
#define ICS_ERRNO_NAMETOOLONG     (36)  /* File name too long */

/**
*@ingroup sme_base
*0x25 �޼�¼�����á�
*/
#define ICS_ERRNO_NOLCK           (37)  /* No record locks available */

/**
*@ingroup sme_base
*0x26 ����û��ʵ�֡�
*/
#define ICS_ERRNO_NOSYS           (38)  /* Function not implemented */

/**
*@ingroup sme_base
*0x27 Ŀ¼��Ϊ�ա�
*/
#define ICS_ERRNO_NOTEMPTY        (39)  /* Directory not empty */

/**
*@ingroup sme_base
*0x28 ���ӻ��ߵ��÷���ѭ����
*/
#define ICS_ERRNO_LOOP            (40)  /* Too many symbolic links encountered */

/* It is not suggested to use unknown error number */
/**
*@ingroup sme_base
*0x29 δ֪�����룬�û��������ʼ�����롣
*/
#define ICS_ERRNO_UNKNOWN         (41)     /* Unkown reason */

/**
*@ingroup sme_base
*0x2A ������ֹ��
*/
#define ICS_ERRNO_WOULDBLOCK      (42)  /* Operation would block */

/**
*@ingroup sme_base
*0x2B û���������͵���Ϣ��
*/
#define ICS_ERRNO_NOMSG           (43)  /* No message of desired type */

/**
*@ingroup sme_base
*0x2C ��ʶ���Ƴ���
*/
#define ICS_ERRNO_IDRM            (44)  /* Identifier removed */

/**
*@ingroup sme_base
*0x2D ͨ����������Χ��
*/
#define ICS_ERRNO_CHRNG           (45)  /* Channel number out of range */

/**
*@ingroup sme_base
*0x2E ����2δͬ����
*/
#define ICS_ERRNO_L2NSYNC         (46)  /* Level 2 not synchronized */

/**
*@ingroup sme_base
*0x2F ����3ֹͣ��
*/
#define ICS_ERRNO_L3HLT           (47)  /* Level 3 halted */

/**
*@ingroup sme_base
*0x30 ����3������
*/
#define ICS_ERRNO_L3RST           (48)  /* Level 3 reset */

/**
*@ingroup sme_base
*0x31 ���������������ơ�
*/
#define ICS_ERRNO_LNRNG           (49)  /* Link number out of range */

/**
*@ingroup sme_base
*0x32 Э������δ�ҽӡ�
*/
#define ICS_ERRNO_UNATCH          (50)  /* Protocol driver not attached */

/**
*@ingroup sme_base
*0x33û�п��õ�CSI�豸��
*/
#define ICS_ERRNO_NOCSI           (51)  /* No CSI structure available */

/**
*@ingroup sme_base
*0x34 ����2ֹͣ��
*/
#define ICS_ERRNO_L2HLT           (52)  /* Level 2 halted */

/**
*@ingroup sme_base
*0x35 ��������
*/
#define ICS_ERRNO_BADE            (53)  /* Invalid exchange */

/**
*@ingroup sme_base
*0x36 ��Ч��������������
*/
#define ICS_ERRNO_BADR            (54)  /* Invalid request descriptor */

/**
*@ingroup sme_base
*0x37 ����������
*/
#define ICS_ERRNO_XFULL           (55)  /* ICS_ERRNO_xchange full */

/**
*@ingroup sme_base
*0x38 û�н�㡣
*/
#define ICS_ERRNO_NOANO           (56)  /* No anode */

/**
*@ingroup sme_base
*0x39 ��Ч�������롣
*/
#define ICS_ERRNO_BADRQC          (57)  /* Invalid request code */

/**
*@ingroup sme_base
*0x3A ��Ч�Ĳۡ�
*/
#define ICS_ERRNO_BADSLT          (58)  /* Invalid slot */

/**
*@ingroup sme_base
*0x3B ���������ļ���ʽ��
*/
#define ICS_ERRNO_BFONT           (59)  /* Bad font file format */

/**
*@ingroup sme_base
*0x3C �������豸��
*/
#define ICS_ERRNO_NOSTR           (60)  /* Device not a stream */

/**
*@ingroup sme_base
*0x3D �޿��õ����ݡ�
*/
#define ICS_ERRNO_NODATA          (61)  /* No data available */

/**
*@ingroup sme_base
*0x3E ��ʱ��ֹͣ��
*/
#define ICS_ERRNO_TIME            (62)  /* Timer expired */

/**
*@ingroup sme_base
*0x3F ����Դ���㡣
*/
#define ICS_ERRNO_NOSR            (63)  /* Out of streams resources */

/**
*@ingroup sme_base
*0x40 ����δ�������硣
*/
#define ICS_ERRNO_NONET           (64)  /* Machine is not on the network */

/**
*@ingroup sme_base
*0x41 ��δ��װ��
*/
#define ICS_ERRNO_NOPKG           (65)  /* Package not installed */

/**
*@ingroup sme_base
*0x42 Զ��Ŀ�ꡣ
*/
#define ICS_ERRNO_REMOTE          (66)  /* Object is remote */

/**
*@ingroup sme_base
*0x43 �����жϡ�
*/
#define ICS_ERRNO_NOLINK          (67)  /* Link has been severed */

/**
*@ingroup sme_base
*0x44 �㲥ʧ�ܡ�
*/
#define ICS_ERRNO_ADV             (68)  /* Advertise error */

/**
*@ingroup sme_base
*0x45 ����ʧ�ܡ�
*/
#define ICS_ERRNO_SRMNT           (69)  /* Srmount error */

/**
*@ingroup sme_base
*0x46 ����ʧ�ܡ�
*/
#define ICS_ERRNO_COMM            (70)  /* Communication error on send */

/**
*@ingroup sme_base
*0x47 Э�����
*/
#define ICS_ERRNO_PROTO           (71)  /* Protocol error */

/**
*@ingroup sme_base
*0x48 ��һ�����ԡ�
*/
#define ICS_ERRNO_MULTIHOP        (72)  /* Multihop attempted */

/**
*@ingroup sme_base
*0x49 Զ���ļ�ϵͳ����
*/
#define ICS_ERRNO_DOTDOT          (73)  /* RFS specific error */

/**
*@ingroup sme_base
*0x4A ��Ϣ����������Ч��
*/
#define ICS_ERRNO_BADMSG          (74)  /* Not a data message */

/**
*@ingroup sme_base
*0x4B ��ֵ�����������Ͷ���ȡֵ��Χ��
*/
#define ICS_ERRNO_OVERFLOW        (75)  /* Value too large for defined data type */

/**
*@ingroup sme_base
*0x4C ����������
*/
#define ICS_ERRNO_NOTUNIQ         (76)  /* Name not unique on network */

/**
*@ingroup sme_base
*0x4D �ļ���������������
*/
#define ICS_ERRNO_BADFD           (77)  /* File descriptor in bad state */

/**
*@ingroup sme_base
*0x4E Զ�̵�ַ���������
*/
#define ICS_ERRNO_REMCHG          (78)  /* Remote address changed */

/**
*@ingroup sme_base
*0x4F �޷����ʱ�Ҫ�Ĺ���⡣
*/
#define ICS_ERRNO_LIBACC          (79)  /* Can not access a needed shared library */

/**
*@ingroup sme_base
*0x50 �����𻵵Ĺ���⡣
*/
#define ICS_ERRNO_LIBBAD          (80)  /* Accessing a corrupted shared library */


/**
*@ingroup sme_base
*0x51 a.out�ļ���.lib�������ƻ���
*/
#define ICS_ERRNO_LIBSCN          (81)  /* .lib section in a.out corrupted */

/**
*@ingroup sme_base
*0x52 ���ӵĹ������ࡣ
*/
#define ICS_ERRNO_LIBMAX          (82)  /* Attempting to link in too many shared libraries */

/**
*@ingroup sme_base
*0x53 ����ֱ��ִ�й���⡣
*/
#define ICS_ERRNO_LIBEXEC         (83)  /* Cannot exec a shared library directly */

/**
*@ingroup sme_base
*0x54 �ֽ�����ȷ��
*/
#define ICS_ERRNO_ILSEQ           (84)  /* Illegal byte sequence */

/**
*@ingroup sme_base
*0x55 ϵͳ���ñ���ϣ�Ӧ������������
*/
#define ICS_ERRNO_RESTART         (85)  /* Interrupted system call should be restarted */

/**
*@ingroup sme_base
*0x56 ���ܵ�����
*/
#define ICS_ERRNO_STRPIPE         (86)  /* Streams pipe error */

/**
*@ingroup sme_base
*0x57 �û����ࡣ
*/
#define ICS_ERRNO_USERS           (87)  /* Too many users */

/**
*@ingroup sme_base
*0x58 û���׽��ֿɹ�������
*/
#define ICS_ERRNO_NOTSOCK         (88)  /* Socket operation on non-socket */

/**
*@ingroup sme_base
*0x59 Ŀ�ĵ�ַ����ʧ�ܡ�
*/
#define ICS_ERRNO_DESTADDRREQ     (89)  /* Destination address required */

/**
*@ingroup sme_base
*0x5A ��Ϣ������
*/
#define ICS_ERRNO_MSGSIZE         (90)  /* Message too long */

/**
*@ingroup sme_base
*0x5B �����Э�����͡�
*/
#define ICS_ERRNO_PROTOTYPE       (91)  /* Protocol wrong type for socket */

/**
*@ingroup sme_base
*0x5C Э�鲻���á�
*/
#define ICS_ERRNO_NOPROTOOPT      (92)  /* Protocol not available */

/**
*@ingroup sme_base
*0x5D Э�鲻֧�֡�
*/
#define ICS_ERRNO_PROTONOSUPPORT  (93)  /* Protocol not supported */

/**
*@ingroup sme_base
*0x5E �׽������Ͳ�֧�֡�
*/
#define ICS_ERRNO_SOCKTNOSUPPORT  (94)  /* Socket type not supported */

/**
*@ingroup sme_base
*0x5F ����˲�֧�ִ˲�����
*/
#define ICS_ERRNO_OPNOTSUPP       (95)  /* Operation not supported on transport endpoint */

/**
*@ingroup sme_base
*0x60 Э���岻֧�֡�
*/
#define ICS_ERRNO_PFNOSUPPORT     (96)  /* Protocol family not supported */

/**
*@ingroup sme_base
*0x61 ��ַ���ܷ��ʡ�
*/
#define ICS_ERRNO_AFNOSUPPORT     (97)  /* Address family not supported by protocol */

/**
*@ingroup sme_base
*0x62 ��ַ�Ѿ�ʹ�á�
*/
#define ICS_ERRNO_ADDRINUSE       (98)  /* Address already in use */

/**
*@ingroup sme_base
*0x63 �����ַ����ʧ�ܡ�
*/
#define ICS_ERRNO_ADDRNOTAVAIL    (99)  /* Cannot assign requested address */

/**
*@ingroup sme_base
*0x64 ����رա�
*/
#define ICS_ERRNO_NETDOWN         (100) /* Network is down */

/**
*@ingroup sme_base
*0x65 ���粻�ɴ
*/
#define ICS_ERRNO_NETUNREACH      (101) /* Network is unreachable */

/**
*@ingroup sme_base
*0x66 ��λ�����������ӶϿ���
*/
#define ICS_ERRNO_NETRESET        (102) /* Network dropped connection because of reset */

/**
*@ingroup sme_base
*0x67 ���ԭ����������ֹ��
*/
#define ICS_ERRNO_CONNABORTED     (103) /* Software caused connection abort */

/**
*@ingroup sme_base
*0x68 ͬ���������ӡ�
*/
#define ICS_ERRNO_CONNRESET       (104) /* Connection reset by peer */

/**
*@ingroup sme_base
*0x69 û�п��õĻ��档
*/
#define ICS_ERRNO_NOBUFS          (105) /* No buffer space available */

/**
*@ingroup sme_base
*0x6A ����˵��Ѿ��������ӡ�
*/
#define ICS_ERRNO_ISCONN          (106) /* Transport endpoint is already connected */

/**
*@ingroup sme_base
*0x6B ����˵�û�н������ӡ�
*/
#define ICS_ERRNO_NOTCONN         (107) /* Transport endpoint is not connected */

/**
*@ingroup sme_base
*0x6C ����˹رպ��޷����͡�
*/
#define ICS_ERRNO_SHUTDOWN        (108) /* Cannot send after transport endpoint shutdown */

/**
*@ingroup sme_base
*0x6D ���ù����޷���Ƭ��
*/
#define ICS_ERRNO_TOOMANYREFS     (109) /* Too many references: cannot splice */

/**
*@ingroup sme_base
*0x6E ���ӳ�ʱ��
*/
#define ICS_ERRNO_TIMEDOUT        (110) /* Connection timed out */

/**
*@ingroup sme_base
*0x6F �ܾ��������ӡ�
*/
#define ICS_ERRNO_CONNREFUSED     (111) /* Connection refused */

/**
*@ingroup sme_base
*0x70 �����ػ���
*/
#define ICS_ERRNO_HOSTDOWN        (112) /* Host is down */

/**
*@ingroup sme_base
*0x71 ������û��·�ɡ�
*/
#define ICS_ERRNO_HOSTUNREACH     (113) /* No route to host */

/**
*@ingroup sme_base
*0x72 ����������
*/
#define ICS_ERRNO_ALREADY         (114) /* Operation already in progress */

/**
*@ingroup sme_base
*0x73 ���������С�
*/
#define ICS_ERRNO_INPROGRESS      (115) /* Operation now in progress */

/**
*@ingroup sme_base
*0x74 �ɵ�NFS�ļ������
*/
#define ICS_ERRNO_STALE           (116) /* Stale NFS file handle */

/**
*@ingroup sme_base
*0x75 �ṹ��Ҫ����
*/
#define ICS_ERRNO_UCLEAN          (117) /* Structure needs cleaning */

/**
*@ingroup sme_base
*0x76 ��XENIX���������ļ���
*/
#define ICS_ERRNO_NOTNAM          (118) /* Not a XENIX named type file */

/**
*@ingroup sme_base
*0x77 XENIX�ź�����Դ�ľ���
*/
#define ICS_ERRNO_NAVAIL          (119) /* No XENIX semaphores available */

/**
*@ingroup sme_base
*0x78 һ���������͵��ļ���
*/
#define ICS_ERRNO_ISNAM           (120) /* Is a named type file */

/**
*@ingroup sme_base
*0x79 Զ��IO����ʧ�ܡ�
*/
#define ICS_ERRNO_REMOTEIO        (121) /* Remote I/O error */

/**
*@ingroup sme_base
*0x7A ����������ơ�
*/
#define ICS_ERRNO_DQUOT           (122) /* Quota exceeded */

/**
*@ingroup sme_base
*0x7B �������Ͳ����ڡ�
*/
#define ICS_ERRNO_NOMEDIUM        (123) /* No medium found */

/**
*@ingroup sme_base
*0x7C �������ʹ���
*/
#define ICS_ERRNO_MEDIUMTYPE      (124) /* Wrong medium type */

/**
*@ingroup sme_base
*0x7D ģ��û�г�ʼ����
*/
#define ICS_ERRNO_NOTINIT         (125) /* module not init */

/**
*@ingroup sme_base
*0x7E �׽��־���쳣��ʧЧ��
*/
#define ICS_ERRNO_INVASOCHANDLE         (126) /* socket handle invalid or exception */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* __ICS_ERRNO_H__ */
