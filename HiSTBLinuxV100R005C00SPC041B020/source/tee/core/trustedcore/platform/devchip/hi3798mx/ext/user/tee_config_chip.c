#include "tee_common.h"
#include "uuid_disp.h"
#include "tee_config.h"
#include "tee_internal_api.h"
#include "ta_framework.h"
#include "sre_access_control.h"

#define DEFAULT_STACK_SIZE      0x4000
#define DEFAULT_HEAP_SIZE       0x10000
#ifdef TEE_DISABLE_CA_SIGN
int g_tee_disable_ca_auth = TEE_DISABLE_CA_SIGN;
#else
int g_tee_disable_ca_auth;
#endif
#define VFMW_TASK_STACK_SIZE    0x19000

/*build in service propertys */
TA_property_t build_in_service_property[] = {
	/* uuid               stack  heap  permissions  instance  sessin  alive*/
#ifdef WITH_TEST_TA
	{TEE_SERVICE_ECHO,    DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true,     true,   true, '0', NULL, 0},
	{TEE_SERVICE_UT,      DEFAULT_STACK_SIZE * 2, DEFAULT_HEAP_SIZE*4, true,     false,  true, '0', NULL, 0},
#else
	{TEE_SERVICE_ECHO,    DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true,     true,   false, '0', NULL, 0},
	{TEE_SERVICE_UT,      DEFAULT_STACK_SIZE * 2, DEFAULT_HEAP_SIZE*4, true,     false,  false, '0', NULL, 0},
#endif
	{TEE_SERVICE_STORAGE, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true,     false,   true, '0', NULL, 0},
	{TEE_SERVICE_REET, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, false,   true, '0', NULL, 0},
	{TEE_SERVICE_SSA, DEFAULT_STACK_SIZE * 2, DEFAULT_HEAP_SIZE * 8, true,     false,   true, '0', NULL, 0},
#ifdef WITH_HISI_DEMO
	{TEE_SERVICE_HISI_DEMO, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, false, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_SEC_MMZ
	{TEE_SERVICE_SEC_MMZ, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_VFMW
	{TEE_SERVICE_VFMW, VFMW_TASK_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_TEST
	{TEE_SERVICE_HISI_TEST, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_SMMU
	{TEE_SERVICE_SMMU, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_WIDEVINE
	{TEE_SERVICE_WIDEVINE, DEFAULT_STACK_SIZE*12, DEFAULT_HEAP_SIZE*12, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_PLAYREADY
    {TEE_SERVICE_PLAYREADY, DEFAULT_STACK_SIZE*12, DEFAULT_HEAP_SIZE*18, true, true,   true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_DMX
	{TEE_SERVICE_DMX, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_PVR
	{TEE_SERVICE_PVR, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_SEC_HDMI
	{TEE_SERVICE_HDMI, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#ifdef WITH_HISI_VDP
	{TEE_SERVICE_HISI_VDP, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#if defined(WITH_COMPONENT_VMX_ULTRA) || defined(WITH_COMPONENT_VMX_ULTRA_VMXTAC_TEST) \
	|| defined(WITH_COMPONENT_VMX_ULTRA_ITAC_TEST)
	{TEE_SERVICE_STB_VMX_ULTRA_VMXTA, DEFAULT_STACK_SIZE * 4, DEFAULT_HEAP_SIZE * 4, true, true, true, '0', NULL, 0},
	{TEE_SERVICE_STB_VMX_ULTRA_videomarkTA, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true, true, true, '0', NULL, 0},
#endif
#if defined(WITH_COMPONENT_VMX_ULTRA_VMXTAC_TEST) || defined(WITH_COMPONENT_VMX_ULTRA_ITAC_TEST)
	{TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA2, DEFAULT_STACK_SIZE * 2, DEFAULT_HEAP_SIZE * 2, true, true, true, '0', NULL, 0},
	{TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA3, DEFAULT_STACK_SIZE * 2, DEFAULT_HEAP_SIZE * 2, true, true, true, '0', NULL, 0},
#endif

};

uint32_t build_in_service_property_num = sizeof(build_in_service_property) / sizeof(build_in_service_property[0]);


TEE_UUID build_in_uuid[] = {
	TEE_SERVICE_GLOBAL,
	TEE_SERVICE_STORAGE,
	TEE_SERVICE_REET,
	TEE_SERVICE_SSA,
#ifdef WITH_HISI_DEMO
	TEE_SERVICE_HISI_DEMO,
#endif
#ifdef WITH_HISI_SEC_MMZ	
	TEE_SERVICE_SEC_MMZ,
#endif
#ifdef WITH_HISI_VFMW
	TEE_SERVICE_VFMW,
#endif
#if WITH_HISI_TEST
	TEE_SERVICE_HISI_TEST,
#endif
#ifdef WITH_HISI_SMMU
	TEE_SERVICE_SMMU,
#endif
#ifdef WITH_HISI_WIDEVINE
	TEE_SERVICE_WIDEVINE,
#endif
#ifdef WITH_HISI_DMX
	TEE_SERVICE_DMX,
#endif
#ifdef WITH_HISI_PVR		
	TEE_SERVICE_PVR,
#endif
#ifdef WITH_HISI_SEC_HDMI
	TEE_SERVICE_HDMI,
#endif
#ifdef WITH_HISI_VDP
	TEE_SERVICE_HISI_VDP,
#endif
#if defined(WITH_COMPONENT_VMX_ULTRA) || defined(WITH_COMPONENT_VMX_ULTRA_VMXTAC_TEST) || defined(WITH_COMPONENT_VMX_ULTRA_ITAC_TEST)
	TEE_SERVICE_STB_VMX_ULTRA_VMXTA,
	TEE_SERVICE_STB_VMX_ULTRA_videomarkTA,
#endif
#if defined(WITH_COMPONENT_VMX_ULTRA_VMXTAC_TEST) || defined(WITH_COMPONENT_VMX_ULTRA_ITAC_TEST)
	TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA2,
	TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA3,
#endif
};
uint32_t build_in_service_num = sizeof(build_in_uuid) / sizeof(build_in_uuid[0]);

//TA permission control
TA_permission_t ta_permission_config[] = {
	/*internal tasks*/
	{TEE_SERVICE_STORAGE, GENERAL_GROUP_PERMISSION},
	{TEE_SERVICE_REET, SMC_GROUP_PERMISSION},
    {TEE_SERVICE_SSA, (GENERAL_GROUP_PERMISSION | CC_KEY_GROUP2_PERMISSION | MM_GROUP_PERMISSION)},
    /*dymanic tasks*/
    {TEE_SERVICE_ECHO, ALL_GROUP_PERMISSION},
    {TEE_SERVICE_UT,      ALL_GROUP_PERMISSION},
    {TEE_SERVICE_TIMER_UT,    TIMER_GROUP_PERMISSION},
	
#ifdef WITH_HISI_DEMO
	{TEE_SERVICE_HISI_DEMO, ALL_GROUP_PERMISSION},
#endif
#if defined(WITH_COMPONENT_VMX_ULTRA) || defined(WITH_COMPONENT_VMX_ULTRA_VMXTAC_TEST) || defined(WITH_COMPONENT_VMX_ULTRA_ITAC_TEST)
	{TEE_SERVICE_STB_VMX_ULTRA_VMXTA,           GENERAL_GROUP_PERMISSION | MM_GROUP_PERMISSION},
	{TEE_SERVICE_STB_VMX_ULTRA_videomarkTA,     GENERAL_GROUP_PERMISSION | MM_GROUP_PERMISSION},
#endif
#if defined(WITH_COMPONENT_VMX_ULTRA_VMXTAC_TEST) || defined(WITH_COMPONENT_VMX_ULTRA_ITAC_TEST)
	{TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA2, GENERAL_GROUP_PERMISSION | MM_GROUP_PERMISSION},
	{TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA3, GENERAL_GROUP_PERMISSION | MM_GROUP_PERMISSION},
#endif
#ifdef WITH_HISI_WIDEVINE
	{TEE_SERVICE_WIDEVINE,    GENERAL_GROUP_PERMISSION | MM_GROUP_PERMISSION},
#endif
#ifdef WITH_HISI_SEC_MMZ	
	{TEE_SERVICE_SEC_MMZ, GENERAL_GROUP_PERMISSION | MM_GROUP_PERMISSION},
#endif
#ifdef WITH_HISI_VFMW
	{TEE_SERVICE_VFMW, GENERAL_GROUP_PERMISSION},
#endif
#if WITH_HISI_TEST
	{TEE_SERVICE_HISI_TEST, GENERAL_GROUP_PERMISSION | TIMER_GROUP_PERMISSION | MM_GROUP_PERMISSION},
#endif
#ifdef WITH_HISI_SMMU
	{TEE_SERVICE_SMMU, GENERAL_GROUP_PERMISSION | MM_GROUP_PERMISSION},
#endif
#ifdef WITH_HISI_DMX
	{TEE_SERVICE_DMX, GENERAL_GROUP_PERMISSION},
#endif
#ifdef WITH_HISI_VDP
	{TEE_SERVICE_HISI_VDP, GENERAL_GROUP_PERMISSION | TIMER_GROUP_PERMISSION | MM_GROUP_PERMISSION},
#endif
#ifdef WITH_HISI_PVR		
	{TEE_SERVICE_PVR, GENERAL_GROUP_PERMISSION | TIMER_GROUP_PERMISSION},
#endif	
#ifdef WITH_HISI_SEC_HDMI
	{TEE_SERVICE_HDMI, GENERAL_GROUP_PERMISSION},
#endif
};
uint32_t dynamic_ta_num = sizeof(ta_permission_config) / sizeof(ta_permission_config[0]);

TA_rpmb_threshold_t ta_rpmb_threshold_config[] = {
	/* DO NOT EDIT */
	{TEE_SERVICE_UT, 0},
	/* DO NOT EDIT */
#ifdef WITH_HISI_DEMO
	{TEE_SERVICE_HISI_DEMO, 32 * 1024},
#endif
};
uint32_t g_rpmb_ta_num = sizeof(ta_rpmb_threshold_config) / sizeof(ta_rpmb_threshold_config[0]);

