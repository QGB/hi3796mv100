#ifdef HI_DISP_BUILD_FULL
#include <linux/kernel.h>
#endif

#include "drv_disp_rwzb.h"

#if  (VIDEO_BUFF_YPBPR == VIDEO_BUFF_YPBPR_NONE)
static HI_U32 u32aDATESrc13Coef[][18]=
{
    {0x00000000, 0x07fb07fe, 0x00080000, 0x07f107ff, 0x00190001, 0x07d807ff, 0x00420000, 0x07870003,
     0x015207ee, 0x01520224, 0x078707ee, 0x00420003, 0x07d80000, 0x001907ff, 0x07f10001, 0x000807ff,
     0x07fb0000, 0x000007fe
    },
    {0x0      ,  0x7fb07fe,  0x80000  ,  0x7f107ff,  0x190001 ,  0x7d807ff,  0x420000 ,  0x7870003,
     0x15207ee,  0x1520224,  0x78707ee,  0x420003 ,  0x7d80000,  0x1907ff ,  0x7f10001,  0x807ff  ,
     0x7fb0000,  0x7fe    ,
    },
    {0x00010000, 0x07fd0000, 0x00070000, 0x07f30000, 0x00160000, 0x07db0000, 0x003d07ff, 0x078e0003,
     0x014c07f2, 0x014c0218, 0x078e07f2, 0x003d0003, 0x07db07ff, 0x00160000, 0x07f30000, 0x00070000,
     0x07fd0000, 0x00010000
    },
    {
    /*0x0      ,  0x7ff0000,  0x30000  ,  0x7f807ff,  0x120003 ,  0x7dc07fb,  0x440006 ,  0x77a07fd,
     0x15a07e6,  0x15a0234,  0x77a07e6,  0x4407fd ,  0x7dc0006,  0x1207fb ,  0x7f80003,  0x307ff  ,
     0x7ff0000,  0x0      ,*/
     0x0      ,  0x7fe07fd,  0x60004,    0x7f207fa,  0x1b0009 ,  0x7d007f6,  0x530009 ,  0x76807ff,
     0x16407d8,  0x164024e,  0x76807d8,  0x5307ff ,  0x7d00009,  0x1b07f6 ,  0x7f20009,  0x607fa,
     0x7fe0004,  0x7fd,
    },
};

#elif (VIDEO_BUFF_YPBPR == VIDEO_BUFF_YPBPR_FMS6363)

static HI_U32 u32aDATESrc13Coef[][18]=
{
    /*hard ware add capacitance  ,in order pass emi ,so need change para */
    {0x0,0x0,0x10000,0x7fc0000,0xc0000,0x7e30000,0x3f07ff,0x77c0007,
    0x15a07d6,0x15a0248,0x77c07d6,0x3f0007,0x7e307ff,0xc0000,0x7fc0000,0x10000,
    0x0,0x0
    },
    {0x0      ,  0x7fb07fe,  0x80000  ,  0x7f107ff,  0x190001 ,  0x7d807ff,  0x420000 ,  0x7870003,
     0x15207ee,  0x1520224,  0x78707ee,  0x420003 ,  0x7d80000,  0x1907ff ,  0x7f10001,  0x807ff  ,
     0x7fb0000,  0x7fe    ,
    },
    {0x0      ,  0x0,  0x10000  ,  0x7fc0001,  0xc07fd ,  0x7e50005,  0x3907f7 ,  0x787000f,
     0x15207d7,  0x152023f,  0x78707d7,  0x39000f ,  0x7e507f7,  0xc0005 ,  0x7fc07fd,  0x10001  ,
     0x0,  0x0  ,
    },
    {0x0      ,  0x0,  0x107ff  ,  0x7fa0002,  0x1007fc ,  0x7db0008,  0x4d07f2 ,  0x764001e,
     0x16807a9,  0x1680285,  0x76407a9,  0x4d001e ,  0x7db07f2,  0x100008 ,  0x7fa07fc,  0x10002  ,
     0x7ff,  0x0  ,
    },

};

#elif  (VIDEO_BUFF_YPBPR == VIDEO_BUFF_YPBPR_DIO2176)


static HI_U32 u32aDATESrc13Coef[][18]=
{
        /*96c 98c  video buff change to DIO02673*/
    {0x0,0x0,0x0,0x107fe,0x7f70005,0x150000,0x7ed07ea,0x7de0042,
    0x128078d,0x128028a,0x7de078d,0x7ed0042,0x1507ea,0x7f70000,0x10005,0x7fe,
    0x0,0x0
    },
    {0x0      ,  0x7fb07fe,  0x80000  ,  0x7f107ff,  0x190001 ,  0x7d807ff,  0x420000 ,  0x7870003,
     0x15207ee,  0x1520224,  0x78707ee,  0x420003 ,  0x7d80000,  0x1907ff ,  0x7f10001,  0x807ff  ,
     0x7fb0000,  0x7fe  ,
    },
    {0x0      ,  0x7fc0001,  0x7f70009  ,  0x1c07fa,  0x7e607ec ,  0x7f80037,  0x3b07b6 ,  0x77b004e,
     0x15d07a5,  0x15d0260,  0x77b07a5,  0x3b004e ,  0x7f807b6,  0x7e60037 ,  0x1c07ec,  0x7f707fa  ,
     0x7fc0009,  0x1  ,
    },
    
    {0x0      ,  0x607fe,  0x7f107fe  ,  0x90018,  0x1507ca ,  0x7bc004a,  0x7b07b1 ,  0x73a0053,
     0x179077b,  0x17902b4,  0x73a077b,  0x7b0053 ,  0x7bc07b1,  0x15004a ,  0x907ca,  0x7f10018  ,
     0x607fe,  0x7fe  ,
    },
};
#elif  (VIDEO_BUFF_YPBPR == VIDEO_BUFF_YPBPR_TT_FILTER)

#if  (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) )
static HI_U32 u32aDATESrc13Coef[][18]=
{   

    #ifdef HI_VO_VDAC_FULL_DRIVE

	/*default setting.*/
    {0x0,0x7ff0000,0x40000,0x7f60001,0x1307fe,0x7dd0004,0x3e07fa,0x788000b,
    0x15007e2,0x150022d,0x78807e2,0x3e000b,0x7dd07fa,0x130004,0x7f607fe,0x40001,
    0x7ff0000,0x0
    },
    
    /*480p/576p*/
    {0x0      ,  0x7fd07ff,  0x60000  ,  0x7f50001,  0x1407fd ,  0x7dd0006,  0x3c07f7 ,  0x78e000d,
     0x14d07e6,  0x14d0227,  0x78e07e6,  0x3c000d ,  0x7dd07f7,  0x140006 ,  0x7f507fd,  0x60001  ,
     0x7fd0000,  0x7ff,
    },
    
     /*720p/1080i.*/
    {0x0,0x7ff0000,0x40000,0x7f60001,0x1307fe,0x7dd0004,0x3e07fa,0x788000b,
    0x15007e2,0x150022d,0x78807e2,0x3e000b,0x7dd07fa,0x130004,0x7f607fe,0x40001,
    0x7ff0000,0x0
    },
	
	/*1080p*/
    {0x0      ,  0x7fe0000,  0x50000  ,  0x7f50001,  0x1507fd ,  0x7d90006,  0x4507f6 ,  0x77d0012,
     0x15707d1,  0x1570247,  0x77d07d1,  0x450012 ,  0x7d907f6,  0x150006 ,  0x7f507fd,  0x50001  ,
     0x7fe0000,  0x0  ,
    },
    #endif

    #ifdef HI_VO_VDAC_HALF_DRIVE
	
	/*default setting.*/
    {0x0,0x7ff0000,0x40000,0x7f60001,0x1307fe,0x7dd0004,0x3e07fa,0x788000b,
    0x15007e2,0x150022d,0x78807e2,0x3e000b,0x7dd07fa,0x130004,0x7f607fe,0x40001,
    0x7ff0000,0x0
    },
    
    /*480p/576p*/
    {0x0      ,  0x7fd07ff,  0x60000  ,  0x7f50001,  0x1407fd ,  0x7dd0006,  0x3c07f7 ,  0x78e000d,
     0x14d07e6,  0x14d0227,  0x78e07e6,  0x3c000d ,  0x7dd07f7,  0x140006 ,  0x7f507fd,  0x60001  ,
     0x7fd0000,  0x7ff,
    },
    
     /*720p/1080i.*/
    {0x0,0x7ff0000,0x40000,0x7f60001,0x1307fe,0x7dd0004,0x3e07fa,0x788000b,
    0x15007e2,0x150022d,0x78807e2,0x3e000b,0x7dd07fa,0x130004,0x7f607fe,0x40001,
    0x7ff0000,0x0
    },
    
	/*1080p*/
    {0x7ff0000 ,  0x7ff07fd,  0x50005  ,  0x7f407f8,  0x19000c ,  0x7d307f2,  0x4f000f ,  0x76d07f7,
     0x16207e4,  0x162023e,  0x76d07e4,  0x4f07f7 ,  0x7d3000f,  0x1907f2 ,  0x7f4000c,  0x507f8  ,
     0x7ff0005,  0x7ff07fd ,
    },
    #endif


	#ifdef HI_VO_VDAC_QUARTER_DRIVE
	
	 /*720p/1080i.*/
    {0x7ff0000,0x7fe,0x30006,0x7f807f7,0x13000f,0x7db07ed,0x450017,0x77b07eb,
    0x15707fa,0x157021b,0x77b07fa,0x4507eb,0x7db0017,0x1307ed,0x7f8000f,0x307f7,
    0x6,0x7ff07fe
    },
    
    /*480p/576p*/
    {0x0      ,  0x7fd0000,  0x607ff  ,  0x7f50003,  0x1407fa ,  0x7dd0009,  0x3e07f3 ,  0x78b0013,
     0x14f07dd,  0x14f0233,  0x78b07dd,  0x3e0013 ,  0x7dd07f3,  0x140009 ,  0x7f507fa,  0x60003  ,
     0x7fd07ff,  0x0,
    },
    
     /*720p/1080i.*/
    {0x7ff0000,0x7fe,0x30006,0x7f807f7,0x13000f,0x7db07ed,0x450017,0x77b07eb,
    0x15707fa,0x157021b,0x77b07fa,0x4507eb,0x7db0017,0x1307ed,0x7f8000f,0x307f7,
    0x6,0x7ff07fe
    },
    
	/*1080p*/
    {0x7ff0000 ,  0x7ff07fd,  0x60005  ,  0x7f207f7,  0x1d000d ,  0x7cc07f0,  0x5c0010 ,  0x75907fb,
     0x16e07d0,  0x16e0260,  0x75907d0,  0x5c07fb ,  0x7cc0010,  0x1d07f0 ,  0x7f2000d,  0x607f7  ,
     0x7ff0005,  0x7ff07fd ,
    },
    #endif

	
};

#else

static HI_U32 u32aDATESrc13Coef[][18]=
{
    /*96c 98c  video buff change to DIO02673*/
    {0x0,0x0,0x0,0x107fe,0x7f70005,0x150000,0x7ed07ea,0x7de0042,
    0x128078d,0x128028a,0x7de078d,0x7ed0042,0x1507ea,0x7f70000,0x10005,0x7fe,
    0x0,0x0
    },
    {0x0      ,  0x7fb07fe,  0x80000  ,  0x7f107ff,  0x190001 ,  0x7d807ff,  0x420000 ,  0x7870003,
     0x15207ee,  0x1520224,  0x78707ee,  0x420003 ,  0x7d80000,  0x1907ff ,  0x7f10001,  0x807ff  ,
     0x7fb0000,  0x7fe  ,
    },
    {0x0      ,  0x7fc0001,  0x7f70009  ,  0x1c07fa,  0x7e607ec ,  0x7f80037,  0x3b07b6 ,  0x77b004e,
     0x15d07a5,  0x15d0260,  0x77b07a5,  0x3b004e ,  0x7f807b6,  0x7e60037 ,  0x1c07ec,  0x7f707fa  ,
     0x7fc0009,  0x1  ,
    },
    
    {0x0      ,  0x607fe,  0x7f107fe  ,  0x90018,  0x1507ca ,  0x7bc004a,  0x7b07b1 ,  0x73a0053,
     0x179077b,  0x17902b4,  0x73a077b,  0x7b0053 ,  0x7bc07b1,  0x15004a ,  0x907ca,  0x7f10018  ,
     0x607fe,  0x7fe  ,
    },
};



#endif

#endif
/*w00217574 for cvbs  hadrware add cap   for emi  */
//HI_U32 u32aSDDATEDefSrcCoef[]=
//{0x07FF07FF,  0x07FF0204,  0x000007FF,   0x07BF000C,  0x01350135,  0x000C07BF};
#if  (VIDEO_BUFF_CVBS == VIDEO_BUFF_CVBS_NONE)

HI_U32 u32aSDDATESrcCoef[][10]=
{
    /*default para*/
{ 0x1f07e8,  0x1f01f2,  0x7e8,   0x7b6000b,  0x13f013f,  0xb07b6},
    /* FIDELITY_576I_YPBPR FIDELITY_480I_YPBPR */
{0x07FF07FF,  0x07FF0204,  0x000007FF,   0x07BF000C,  0x01350135,  0x000C07BF},

};
#elif   (VIDEO_BUFF_CVBS == VIDEO_BUFF_CVBS_FMS6143a)

HI_U32 u32aSDDATESrcCoef[][10]=
{
    {0x7d10000 ,  0x69b00b2 ,  0x2e2 ,   0x120000 ,  0x79207f5 ,  0x13a012d,
        0x00000001, 0x00808080, 0x00808080,0x00000001},
    {0x07FF07FF,  0x07FF0204,  0x000007FF,   0x07BF000C,  0x01350135,0x000C07BF,
        0x00000001, 0x00808080, 0x00808080,0x00010000},
    {0x7d10000 ,  0x69b00b2 ,  0x2e2 ,   0x120000 ,  0x79207f5 ,  0x13a012d,
        0x00000001, 0x00808080, 0x00808080,0x00000102},
    {0x7d10000 ,  0x69b00b2 ,  0x2e2 ,   0x120000 ,  0x79207f5 ,  0x13a012d,
        0x00000001, 0x00808080, 0x00808080,0x00000011},/*vector*/
    {0x7d10000 ,  0x69b00b2 ,  0x2e2 ,   0x120000 ,  0x79207f5 ,  0x13a012d,
        0x00000001, 0x00808080, 0x80807D7D,0x00000001},
    {0x7d10000 ,  0x69b00b2 ,  0x2e2 ,   0x120000 ,  0x79207f5 ,  0x13a012d,
        0x00000001, 0x00808080, 0x00808080,0x00000001},
};

#elif   (VIDEO_BUFF_CVBS == VIDEO_BUFF_CVBS_TT_FILTER)

#if  (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) )

HI_U32 u32aSDDATESrcCoef[][10]=
{
    /*default para*/
    {0x7f9 ,  0x20e ,  0x7f9 ,   0x79f0014 ,  0x14d014d ,  0x14079f,
        0x00000001, 0x80808181, 0x00808080,0x113},
        
        /* FIDELITY_576I_YPBPR FIDELITY_480I_YPBPR 3796c 3798c */
    {0x7d20007,  0x7d2024e,  0x7,   0x7af000d,  0x1430143,0xd07af,
        0x00000001, 0x80808181, 0x00808080,0x113},

    /* 3719m  FIDELITY_SKN FIDELITY_ZDN  */
    {0x7f9,  0x20e,  0x7f9,   0x79f0014,  0x14d014d,0x14079f,
        0x00000001, 0x80808181, 0x00808080,0x00000102},
        
        /* 3719m FIDELITY_MOTO_CVBS  luma Noline */
    {0x7f9,  0x20e,  0x7f9,   0x79f0014,  0x14d014d,0x14079f,
        0x00000001, 0x80808181, 0x00808080,0x113},/*vector*/
        /* 3719m FIDELITY_033   Vector */
    {0x7f9,  0x20e,  0x7f9,   0x79f0014,  0x14d014d,0x14079f,
        0x00000001, 0x80808181, 0x00808080,0x113},

    /* 3719m   FIDELITY_MATRIX525 Vector */
    {0x7f1,  0x21e,  0x7f1,   0x7760021,  0x1690169,0x210776,
        0x00000001, 0x80808181, 0x00808080,0x113},
};

#else

HI_U32 u32aSDDATESrcCoef[][10]=
{
    /*default para*/
    {0x7f1 ,  0x21e ,  0x7f1 ,   0x7760021 ,  0x1690169 ,  0x210776,
        0x00000001, 0x00808080, 0x00808080,0x00000001},
        
        /* FIDELITY_576I_YPBPR FIDELITY_480I_YPBPR 3796c 3798c */
    {0x7f1,  0x21e,  0x7f1,   0x7760021,  0x1690169,0x210776,
        0x00000001, 0x00808080, 0x00808080,0x00010000},

    /* 3719m  FIDELITY_SKN FIDELITY_ZDN  */
    {0x7f1,  0x21e,  0x7f1,   0x7760021,  0x1690169,0x210776,
        0x00000001, 0x80808282, 0x00808080,0x00000102},
        
        /* 3719m FIDELITY_MOTO_CVBS  luma Noline */
    {0x7f1,  0x21e,  0x7f1,   0x7760021,  0x1690169,0x210776,
        0x00000001, 0x00808080, 0x00808080,0x00000011},/*vector*/
        /* 3719m FIDELITY_033   Vector */
    {0x7f1,  0x21e,  0x7f1,   0x7760021,  0x1690169,0x210776,
        0x00000001, 0x00808080, 0x00808080,0x00000001},

    /* 3719m   FIDELITY_MATRIX525 Vector */
    {0x7f1,  0x21e,  0x7f1,   0x7760021,  0x1690169,0x210776,
        0x00000001, 0x00808080, 0x00808080,0x00000001},
};

#endif

#else

    /*default  VIDEO_BUFF_CVBS_FMS6141 */
//#elif (VIDEO_BUFF_CVBS == VIDEO_BUFF_CVBS_FMS6141)
HI_U32 u32aSDDATESrcCoef[][10]=
{
    /*default para*/
    {0x78d0010 ,  0x5c70145 ,  0x357 ,   0x1b07fa ,  0x75c0003 ,  0x1630129,
        0x00000001, 0x00808080, 0x00808080,0x00000001},
		
#if (VIDEO_BUFF_YPBPR == VIDEO_BUFF_YPBPR_DIO2176)
    /* FIDELITY_576I_YPBPR FIDELITY_480I_YPBPR 3796c 3798c */
     {0x7f1,  0x21e,  0x7f1,   0x7760021,  0x1690169,0x210776,
        0x00000001, 0x00808080, 0x00808080,0x00010000},
#else
    /* FIDELITY_576I_YPBPR FIDELITY_480I_YPBPR  3719m*/
    {0x07FF07FF,  0x07FF0204,  0x000007FF,   0x07BF000C,  0x01350135,0x000C07BF,
        0x00000001, 0x00808080, 0x00808080,0x00010000},
#endif		
     /* 3719m  FIDELITY_SKN FIDELITY_ZDN  */
    {0x78d0010 ,  0x5c70145 ,  0x357 ,   0x1b07fa ,  0x75c0003 ,  0x1630129,
        0x00000001, 0x80808282, 0x00808080,0x00000102},

        /* 3719m FIDELITY_MOTO_CVBS  luma Noline */
    {0x78d0010 ,  0x5c70145 ,  0x357 ,   0x1b07fa ,  0x75c0003 ,  0x1630129,
        0x00000001, 0x00808080, 0x00808080,0x00000011},

    /* 3719m FIDELITY_033   Vector */
    {0x78d0010 ,  0x5c70145 ,  0x357 ,   0x1b07fa ,  0x75c0003 ,  0x1630129,
        0x00000001, 0x00808080, 0x00808080,0x00000001},
        /* 3719m   FIDELITY_MATRIX525 Vector */
    {0x78d0010 ,  0x5c70145 ,  0x357 ,   0x1b07fa ,  0x75c0003 ,  0x1630129,
        0x00000001, 0x00808080, 0x00808080,0x00000001},
};

#endif



HI_U32 * VDP_Get_HDateSrc13Coef( HI_U32 u32Fmt)
{
    return u32aDATESrc13Coef[u32Fmt];
}
HI_U32 * VDP_Get_SDateSrcCoef( HI_U32 Index)
{
    return u32aSDDATESrcCoef[Index];
}


