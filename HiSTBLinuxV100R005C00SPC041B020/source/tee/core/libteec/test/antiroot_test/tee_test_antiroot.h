#ifndef _TEE_TEST_ANTIROOT_H_
#define _TEE_TEST_ANTIROOT_H_

#define SCAN_CYCLE (1*10*1000)   /* 10 seconds */

#define MAGIC 0x53525748
#define VERSION 1

#define KERNEL_CODE_LENGTH_SHA 20
#define SYSTEM_CALL_LENGTH_SHA 20
#define SELINUX_HOOKS_LENGTH_SHA 20
#define CHALLENGE_MAX_LENGTH 15

#define CHALLENGE_KEY_LENGTH		32
#define CHALLENGE_REQ_KEY_LENGTH	CHALLENGE_KEY_LENGTH
#define RESPONSE_COUNTER_LENGTH		CHALLENGE_KEY_LENGTH
#define CHALLENGE_NOUNCE_LENGTH		CHALLENGE_KEY_LENGTH

/*
 * TEEK_InvokeCommand buffer (Max 4K):
 * IV + struct RAGENT_COMMAND + RPROCS
 * 16   max320                  max 3680
 */
/* MAX_RPROC_SIZE is defined in hw_rscan_interface.h or rscan_dummy.h */
#define ROOTAGENT_RPROCS_MAX_LENGTH	3680
#define IV_SIZE 16
/* 320 is reserved for sizeof(struct RAGENT_COMMAND) */
#define ANTIROOT_SRC_LEN             (320 + ROOTAGENT_RPROCS_MAX_LENGTH)
#define ANTIROOT_DST_LEN             (IV_SIZE + ANTIROOT_SRC_LEN)

/**
 * @ingroup root agent cmd
 *
 * @brief: root agent command id.
 *
 */
enum ROOTAGENT_CMD {
	ROOTAGENT_CONFIG_ID = 0x01,      /** set the white information */
	ROOTAGENT_CHALLENGE_ID = 0x02,   /** request a challenge */
	ROOTAGENT_RESPONSE_ID = 0x03      /** return the scanning result */
};

enum ROOTAGENT_OPID {
	RAOPID_TERM = 0,
	RAOPID_KCODE,
	RAOPID_SYSCALL,
	RAOPID_RPROCS,
	RAOPID_SELINUX_STATUS,
	RAOPID_SELINUX_HOOK,
	RAOPID_SELINUX_POLICY,
	RAOPID_HIDDENTHREAD,
	RAOPID_FRAMEWORK,
	RAOPID_SYSAPP,
	RAOPID_CPULOAD,
	RAOPID_BATTERY,
	RAOPID_CHARGING,
	RAOPID_TIME,
	RAOPID_NOOP,
	RAOPID_MAXID
};

enum {
	/**AntiRoot Response verify failed*/
	TEE_ERROR_ANTIROOT_RSP_FAIL    = 0xFFFF9110,
	/**AntiRoot ERROR during invokecmd */
	TEE_ERROR_ANTIROOT_INVOKE_ERROR = 0xFFFF9111
};


/** communication with TEE-OS start */

struct RAGENT_WHITE_LIST {
	/**build version of REE,
	 * 0 for ENG, other for USER */
	uint32_t dStatus;
	uint8_t kcodes[KERNEL_CODE_LENGTH_SHA];   /** kernel code SHA1 */
	uint8_t syscalls[SYSTEM_CALL_LENGTH_SHA];  /** system call table SHA1 */
	uint32_t selinux;                         /** SE-Linux state */
	uint8_t sehooks[SELINUX_HOOKS_LENGTH_SHA]; /** struct security_operations SHA1 */
	uint32_t proclength;
};

struct RAGENT_CIPHER_KEY {
	/** 16 byte aes key cipher challenge request  */
	uint8_t cha_req_key[CHALLENGE_REQ_KEY_LENGTH];
	/** 16 byte aes key cipher challenge  */
	uint8_t cha_key[CHALLENGE_KEY_LENGTH];
};

struct RAGENT_CONFIG {
	struct RAGENT_CIPHER_KEY cipher_key;		/** cipher key */
	struct RAGENT_WHITE_LIST white_list;		/** white listi */
};

/**
 * @ingroup  RAGENT_CHALLENGE
 *
 * @brief: challenge information
 *
 */
struct RAGENT_CHALLENGE {
	/** CPU Usage 0~100 */
	uint32_t cpuload;
	/** remaining battery 0~100 */
	uint32_t battery;
	/** Charging or not 0~1 */
	uint32_t charging;
	/** Current time in UNIX Epoch time. same as the time() systemcall */
	uint32_t time;
	/** Timezone in minutes.
	 * see tz_minuteswest in gettimeofday().
	 * e.g. Beijing +8 is -480 */
	uint32_t timezone;
	/** nounce as key for responce */
	uint8_t nounce[CHALLENGE_NOUNCE_LENGTH];
	/** challenge association */
	uint32_t challengeid[CHALLENGE_MAX_LENGTH];
};

struct RAGENT_RESPONSE {
	/** white information in runtime */
	struct RAGENT_WHITE_LIST runtime_white_list;
	/** integrated of process chain  */
	uint32_t proc_integrated;
	/** Heartbeat */
	uint32_t noop;
};

/**
 * @ingroup  TEE_RM_CONTENT
 *
 * @brief: specific content
 *
 */
union RAGENT_CONTENT {
	struct RAGENT_CONFIG config;       /** white information */
	struct RAGENT_CHALLENGE challenge; /** challenge generated by TEE */
	struct RAGENT_RESPONSE response;   /** response (the result of scanning) */
};

/**
 * @ingroup  TEE_RM_COMMAND
 *
 * @brief: root monitor command information.
 *
 */
struct RAGENT_COMMAND {
	uint32_t magic;          /** scanner identify */
	uint32_t version;        /** version */
	/** interface type,
	 * corresponding to content*/
	uint32_t interface;
	/** specific content
	 * (configuration,
	 * challenge, response),
	 * depend on interface */
	union RAGENT_CONTENT content;
};

/** communication with TEE-OS end */

/**
 * @ingroup  TEE_RM_ROOTPROC
 *
 * @brief: root process list
 *
 */
struct RAGENT_ROOTPROC {
	uint32_t length;
	uint8_t *procid;
};
#endif
