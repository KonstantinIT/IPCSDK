#ifndef __HS_NETSTRUCTDEF_H__
#define __HS_NETSTRUCTDEF_H__
#include <list>

/********************************************************************************************/
/*******************************    Macro、Struct、Callback  *********************************/
/********************************************************************************************/
#define MAX_HOST_LEN				128
#define MAX_SERVER_NAME_LEN			32
#define MAX_USER_NAME_LEN			32
#define MAX_PASSWORD_LEN			32
#define MAX_IPSTR_LEN				16
#define MAX_MACSTR_LEN				18
#define MAX_FILENAME_LEN			255
#define MAX_BLOCK					8
#define MAX_REGION					12
#define MAX_RESOLUTIONSTR_LEN		1024
#define MAX_DEVICE_NAME_LEN			32
#define MAX_PTZ_PRESET_POINT_NUM          128               
#define MAX_PTZ_CRUISE_LINE_NUM           4                
#define MAX_PTZ_CRUISE_POINT_NUM          32                
#define MAX_PTZ_NAME_LEN                  64


///////////////////////////////////////////////////////////////////////////////
// 

typedef enum
{
    HS_Searchall_Device = 0,

}HS_SEARCH_TYPE;

typedef struct _HS_SEARCH_INFO
{
    unsigned char   ucDevType[16];          /*设备类型*/
    unsigned char   ucDevName[64];          /*设备名称*/
    unsigned char   ucFirmwareVersion[64];  /*固件版本*/
    unsigned char   ucIpAddr[16];           /*ip地址*/
    unsigned char   ucNetmaskAddr[16];      /*子网掩码*/
    unsigned char   ucGatewayAddr[16];      /*网关地址*/
    unsigned char   ucDnsAddr1[16];         /*dns1地址*/
    unsigned char   ucMacAddr[18];          /*mac地址*/
    unsigned int    iWebPort;
    unsigned int    iRtspPort;
    unsigned int    imobilePort;		    /*Mobileport*/
    unsigned int	iChNum;			        /*通道数*/
    unsigned char   ucDhcp[16];
    unsigned long   ucPlatformType;         /*平台类型*/
    _HS_SEARCH_INFO()
    {
        memset(this,0,sizeof(_HS_SEARCH_INFO));
    }

}HS_SEARCH_INFO;


///////////////////////////////////////////////////////////////////////////////
// 

typedef struct _HS_STREAM_INFO
{
	unsigned short	videoCoder;		//Video encoding type
	unsigned short	audioCoder;		//Audio encoding type
	unsigned short	frameRate;		//frame rate
	unsigned short	bitRate;		//bit rate
	unsigned short	nWidth;			//video width
	unsigned short	nHeight;		//video width
	unsigned short	frameType;		//frame type. ex: H264 I¡¢P¡¢B
	unsigned short  isKeyFrame;		//is key frame
	unsigned short	type;			//data type. 0 video£¬ 1 audio  2 stream header
	unsigned short	res;			//reserve
	long			nStamp;			//Time stamp£¬unit: millisecond
}HS_STREAM_INFO;

typedef struct _HS_FRAME_INFO_
{ 
	long nWidth;	 
	long nHeight;	 
	long nStamp;	 
	long nType;		 
	long nFrameRate; 
}HS_FRAME_INFO; 

typedef struct _HS_CLIENTINFO
{	
	char host[MAX_HOST_LEN];
	int  port;							
	char username[MAX_USER_NAME_LEN];   
	char password[MAX_PASSWORD_LEN];    
	char model;							//device type. must be 0
	int  channel;						//must be 0
	int  streamtype;					//stream type. 0 main stream 1 second stream
	HWND hwnd;							//handle is used to play
}HS_CLIENTINFO;

typedef enum HsNetCaptureType
{
	HS_NET_CAPTURE_JPEG = 0,//
	HS_NET_CAPTURE_BMP
}HsNetCaptureType;

typedef enum{
	HS_LANGUAGE_CHINESE = 0x00,              
	HS_LANGUAGE_ENGLISH,                     
	HS_LANGUAGE_RUSSIAN,                     
	HS_LANGUAGE_KOREAN,                      
	HS_LANGUAGE_POLAND,                      
	HS_LANGUAGE_FRENCH,                      
	HS_LANGUAGE_JAPANSES,                    
	HS_LANGUAGE_SPAIN,                       
	HS_LANGUAGE_PORTUGAL,                    
	HS_LANGUAGE_ITALY,                       
	HS_LANGUAGE_HEBREW,                      
	HS_LANGUAGE_TURKISH,                     
	HS_LANGUAGE_ARAB,                        
	HS_LANGUAGE_GERMAN,                      
}HS_LANGUAGE_TYPE;

typedef struct HS_RECT{  
	unsigned long x1;
	unsigned long y1;
	unsigned long x2;
	unsigned long y2;
}HS_RECT;

typedef enum HS_AREA_DELIMIT_TYPE{
    HS_AREA_DELIMIT_PIXAL      =    0x00,          /*Actual coordinates*/

    HS_AREA_DELIMIT_HUNDRED     =   0x10,          /*Percentage*/
    HS_AREA_DELIMIT_THOUSAND,                      /*Permill*/
    HS_AREA_DELIMIT_TEN_THOUSAND,                  /*Extremely ratio*/

    HS_AREA_DELIMIT_8_8         =   0x20,          /*Block 8*8*/
    HS_AREA_DELIMIT_22_18,                         /*Block 22*18*/
}HS_AREA_DELIMIT_TYPE;

typedef struct HS_AREA_INFO{
	unsigned char        ucDelimitType;         /*HS_AREA_DELIMIT_TYPE;*/
	union{
		HS_RECT         rect[8];              
		unsigned long    ulBlock[32];           
	}area;
}HS_AREA_INFO;

typedef enum HS_SWITCH_TYPE{
	HS_SWITCH_DISABLE         = 0x00,       
	HS_SWITCH_ENABLE          = 0x01       
}HS_SWITCH_TYPE;

typedef enum HS_TIME_WEEK_DAY{
	HS_TIME_WEEK_SUN         = (1<<1),             
	HS_TIME_WEEK_MON         = (1<<2),             
	HS_TIME_WEEK_TUE         = (1<<3),             
	HS_TIME_WEEK_WED         = (1<<4),             
	HS_TIME_WEEK_THU         = (1<<5),             
	HS_TIME_WEEK_FRI         = (1<<6),             
	HS_TIME_WEEK_SAT         = (1<<7),             
}HS_TIME_WEEK_DAY;

typedef enum HS_TIME_SCOPE_MODE{
	HS_TIME_SCOPE_NULL       = 0,                  
	HS_TIME_SCOPE_ALL,                             
	HS_TIME_SCOPE_SAME,                            
	HS_TIME_SCOPE_DIFF,                            
}HS_TIME_SCOPE_MODE;

typedef struct HS_TIME_DATE_INFO{
	unsigned short  usYear;              
	unsigned char   ucMonth;             
	unsigned char   ucDay;               
}HS_TIME_DATE_INFO;

typedef struct HS_TIME_HOUR_INFO{
	unsigned char   ucHour;               /*0-23*/
	unsigned char   ucMinute;             /*0-59*/
	unsigned char   ucSecond;             /*0-59*/
}HS_TIME_HOUR_INFO;

typedef struct HS_TIME_HOUR_SCOPE{
	HS_TIME_HOUR_INFO  beginHour;
	HS_TIME_HOUR_INFO  endHour;
}HS_TIME_HOUR_SCOPE;

typedef struct HS_TIME_DAY_HOUR_SCOPE{
	unsigned char         ucSocpeMode;          
	HS_TIME_HOUR_SCOPE    hourScope[6];         
}HS_TIME_DAY_HOUR_SCOPE;


typedef struct HS_TIME_WEEK_SCOPE{
    unsigned char			ucScopeModel;     
    HS_TIME_DAY_HOUR_SCOPE  dayScope[7];    
}HS_TIME_WEEK_SCOPE;

/********************************************************************************************/
/*******************************       Image Property       ***************************************/
/********************************************************************************************/
/*(DNR means DigitalNoiseReduction)*/
typedef enum HS_DNRMODE_TYPE{
	HS_DNRMODE_CLOSE   = 0x00,          
	HS_DNRMODE_2D      = 0x01,          
	HS_DNRMODE_3D      = 0x02,          
	HS_DNRMODE_2D_3D   = 0x03,          
}HS_DNRMODE_TYPE;

typedef struct HS_IMAGE_PROPERTY{
	unsigned char ucCH;                  /*0*/
	unsigned char ucStreamType;          /*HS_STREAM_TYPE*/

	unsigned char ucBrightness;          
	unsigned char ucContrast;            
	unsigned char ucSaturation;          
	unsigned char ucHue;                 

	unsigned char ucGainCtrl;            /*0-255*/

	unsigned char ucGainRCtrl;           /*0-255*/
	unsigned char ucGainGCtrl;           /*0-255*/
	unsigned char ucGainBCtrl;           /*0-255*/
	unsigned char ucWhiteBalance;        /*0 auto 1 manual 2:锁定白平衡 3:日光灯 4:白炽灯 5:暖光灯 6:自然光 */

	unsigned char ucBLCEable;            /*0 close 1 open*/
	unsigned char ucBLCStrength;         /*0 Low 1 Medium 2 High.*/
	unsigned char ucExposureCtrl;        /*0 close 1 open*/

	unsigned char ucWideDynamicEnable;   /*reserve*/
	unsigned char ucWideDynamicLevel;    /*0 close 1 auto 2 weak 3 strong 4 super*/ 
	unsigned char ucFlickerCtrlEnable;   /*reserve*/
	unsigned char ucFlickerCtrlModel;    /*0:Indoor NTSC 1:IndoorPAL 2:Outdoor*/

	unsigned char ucDNRModel;            /* HS_DNRMODE_TYPE*/
	unsigned char ucDNR2DStrength;       /*0-255 */
	unsigned char ucDNR3DStrength;       /*0-255 */

	unsigned char ucDefogEnable;         /*0:close 1:open 2:auto*/
	unsigned char ucDefogStrength;       /*0-255*/

	unsigned char ucSLInhibition;        /*0:close 1:open*/
	unsigned char ucSLInhibitionStreangth;/*0-255*/

	unsigned char ucHdrEnable; 			/*0:close 1:open*/
	unsigned char ucSceneMode;			/*场景模式: 0:室内 1:室外*/

	unsigned char ucElectronicAntiShakeEnable;  /*电子防抖: 0:关闭 1:使能*/
}HS_IMAGE_PROPERTY;

/********************************************************************************************/
/*******************************   Network Property   ***************************************/
/********************************************************************************************/
typedef struct HS_NET_PROPERTY{
	unsigned char ucNetCardNum;						
	unsigned char ucEnDHCP;							
	unsigned char ucIP[MAX_IPSTR_LEN];              
	unsigned char ucSubNetMask[MAX_IPSTR_LEN];      
	unsigned char ucGateway[MAX_IPSTR_LEN];         
	unsigned char ucDNS1Ip[MAX_IPSTR_LEN];          
	unsigned char ucDNS2Ip[MAX_IPSTR_LEN];          
	unsigned char ucMacIp[MAX_MACSTR_LEN];			/*Mac ex: A1:B2:C3:D4:E5:F6*/
}HS_NET_PROPERTY;

/********************************************************************************************/
/*******************************       Time       ***************************************/
/********************************************************************************************/
/*
 * 0  - 24  East [12.0] [11.5] [11.0] ~ [1.0] [0.5] [0.0] 
 * 25 - 48  Western [0.5] [1.0] [1.5] ~ [11.0] [11.5] [12.0]
*/
typedef struct HS_TIME_INFO{
	unsigned short usYear;               
	unsigned char  ucMonth;              
	unsigned char  ucDay;                
	unsigned char  ucHour;               
	unsigned char  ucMinute;             
	unsigned char  ucSecond;             
	unsigned char  ucModel;					/*0 manual 1 Synchronization with PC  2 NTP*/
	unsigned char  ucTimeZoon;				/*Please refer to the corresponding time zone rules*/
	unsigned char  ucNVRModify;				/*Whether to allow nvr modify ipc time. 0 no 1 yes*/
	unsigned char  ucSNTPServerAddr[200];	/*NTP address */
}HS_TIME_INFO;

/********************************************************************************************/
/*******************************       Motion Detection       ***************************************/
/********************************************************************************************/
typedef struct HS_MOTION_DETECT_INFO
{
	unsigned char ucEnable;            
	unsigned char ucType;              
	unsigned char ucSensitivity;       
	unsigned char ucBlock[MAX_BLOCK];  /*ucBlock [0] 0 is the first cut a 64-point first one area to the left of the first line. 1 is open, 0 is off*/
	HS_RECT ucArea[MAX_REGION];		   
}HS_MOTION_DETECT_INFO;

typedef struct HS_MOTIONDETECTION_EX_PROPERTY{
	unsigned char ucCH;               /*0*/
	unsigned char ucEnable;           /*HS_SWITCH_TYPE*/
	unsigned char ucSensitivity;      /*0-10  0lowest,10highest*/
	HS_AREA_INFO  region;             
}HS_MOTIONDETECTION_EX_PROPERTY;

typedef struct HS_NVR_MOTIONDETECTION_PROPERTY{
	unsigned char       ucCh;
	unsigned char       ucEnable;
	unsigned char       ucBeepEnable;
	unsigned char       ucBeepTime;
	unsigned char       ucRecordEnable;
	unsigned char       ucRecordTime;
	unsigned char       ucSmtpEnable;
	unsigned char       ucFtpEnable;
	unsigned char       ucSensitive;                 
	HS_AREA_INFO        region;                      
	unsigned char       ucRecordMark[64];            
	HS_TIME_WEEK_SCOPE     schedTime;                
	unsigned char       ucPrerecord;                 
	unsigned char       ucDelayRecord;               
}HS_NVR_MOTIONDETECTION_PROPERTY;

/********************************************************************************************/
/*******************************       Video Cover       ***************************************/
/********************************************************************************************/
typedef struct HS_VIDEOCOVER_PROPERTY{
	unsigned char ucCH;
	unsigned char ucEnable;           /*0 close 1 open*/
	unsigned char ucType;             /*1*/
	unsigned char ucSensitivity;      /*0-10*/   
	unsigned char ucBlock[MAX_BLOCK]; /*reserve*/
	HS_RECT  ucArea[MAX_REGION];	  /*3 group percentage area, x1 x coordinate of the upper left corner, 
									  y1 y coordinate of the upper left corner, x2 x coordinate of the lower right corner, 
									  y2 y coordinate of the lower right corner, the value is a percentage of total 
									  length of the coordinate point values.*/
}HS_VIDEOCOVER_PROPERTY;

typedef struct HS_NVR_VIDEOCOVER_PROPERTY{
	unsigned char ucCH;               
	unsigned char ucEnable;           
	HS_AREA_INFO  region;             
}HS_NVR_VIDEOCOVER_PROPERTY;

/********************************************************************************************/
/*******************************   Encoding property  ***************************************/
/********************************************************************************************/
typedef struct HS_ENCODING_SCOPE{
	unsigned char  ucMaxFrameRate;		
	unsigned char  ucResolutions[MAX_RESOLUTIONSTR_LEN]; 
}HS_ENCODING_SCOPE;

typedef enum{
	HS_ENCODING_H264 = 0x00,
	HS_ENCODING_H265,
	HS_ENCODING_MPEG,

	HS_ENCODING_G711A = 0x10,
	HS_ENCODING_G711U,
	HS_ENCODING_G726,
	HS_ENCODING_ADPCM,

	HS_ENCODING_JPEG = 0x20,
	HS_ENCODING_PNG,
	HS_ENCODING_BMP,
}HS_ENCODING_TYPE;

typedef struct HS_VIDEO_ENCODING_PROPERTY{
	unsigned char  ucEncodingType;      /*HS_ENCODING_TYPE*/
	unsigned char  ucPicQuality;        /*0-100*/

	unsigned short usWidth;             
	unsigned short usHeight;            
	unsigned short ucFrameRate;         
	unsigned short ucBitRate;           

	unsigned char  ucKeyFrameInterval;  /*1-5*/
	unsigned char  ucBitrateType;       /*0:Fixed rate£¬1:VBR*/

	unsigned char  ucProfile;			/*编码复杂度 0:baseline profile 1:main profile 2:high profile*/
}HS_VIDEO_ENCODING_PROPERTY;

typedef enum HS_SAMPLERATE_TYPE{
	HS_SAMPLERATE_8K = 0,
	HS_SAMPLERATE_16K = 10,
	HS_SAMPLERATE_32K = 20,
	HS_SAMPLERATE_64K = 30
}HS_SAMPLERATE_TYPE;

typedef enum HS_BITWIDTH_TYPE{
	HS_BITWIDTH_8 = 0,
	HS_BITWIDTH_16,
	HS_BITWIDTH_32,
}HS_BITWIDTH_TYPE;

typedef struct HS_AUDIO_ENCODING_PROPERTY{
	unsigned char  ucEncodingType;     /*HS_ENCODING_TYPE*/
	unsigned char  ucSampleRate;       /*HS_SAMPLERATE_TYPE*/
	unsigned char  ucBitWidth;         /*HS_BITWIDTH_TYPE*/
	unsigned char  ucSoundMode;        /*0 momo 1 steror*/
}HS_AUDIO_ENCODING_PROPERTY;

typedef enum HS_STREAM_TYPE{
	HS_STREAM_VIDEOSTREAM_0 = 0,      
	HS_STREAM_VIDEOSTREAM_1,          
	HS_STREAM_VIDEOSTREAM_2,          
	HS_STREAM_VIDEOSTREAM_3,          

	HS_STREAM_AUDIOSTREAM_0 = 10,     
	HS_STREAM_AUDIOSTREAM_1,          
	HS_STREAM_AUDIOSTREAM_2,          
	HS_STREAM_AUDIOSTREAM_3,          

	HS_STREAM_ALL  = 50,              
	HS_STREAM_VIDEO_ALL,
	HS_STREAM_AUDIO_ALL,
	HS_STREAM_NULL,                   
}HS_STREAM_TYPE;

typedef struct HS_ENCODING_PROPERTY{
	unsigned char  ucStreamType;      /*HS_STREAM_TYPE*/

	union{
		HS_VIDEO_ENCODING_PROPERTY  video;
		HS_AUDIO_ENCODING_PROPERTY  audio;
	}property;

	unsigned char  ucEnable;          
}HS_ENCODING_PROPERTY;

/********************************************************************************************/
/*******************************     OSD Property     ***************************************/
/********************************************************************************************/
typedef enum{
	HS_POSITION_LT = 0x00,                  
	HS_POSITION_MT,                         
	HS_POSITION_RT,                         
	HS_POSITION_LM,                         
	HS_POSITION_MM,                         
	HS_POSITION_RM,                         
	HS_POSITION_LB,                         
	HS_POSITION_MB,                         
	HS_POSITION_RB,                         
}HS_POSITON_TYPE;

typedef enum HS_ROTATE_TYPE{
	HS_ROTATE_NULL   = 0x0,        

	HS_ROTATE_P_45   = 0x10,       
	HS_ROTATE_P_90,                
	HS_ROTATE_P_135,               
	HS_ROTATE_P_180,               
	HS_ROTATE_P_225,               
	HS_ROTATE_P_270,               
	HS_ROTATE_P_315,               
	HS_ROTATE_P_360,               

	HS_ROTATE_N_45   = 0x20,       
	HS_ROTATE_N_90,                
	HS_ROTATE_N_135,               
	HS_ROTATE_N_180,               
	HS_ROTATE_N_225,               
	HS_ROTATE_N_270,               
	HS_ROTATE_N_315,               
	HS_ROTATE_N_360,               
}HS_ROTATE_TYPE;

typedef enum{
	HS_SHUTTERSPEED_1_1 = 0,
	HS_SHUTTERSPEED_1_4,
	HS_SHUTTERSPEED_1_8,
	HS_SHUTTERSPEED_1_15,
	HS_SHUTTERSPEED_1_30,
	HS_SHUTTERSPEED_1_60,
	HS_SHUTTERSPEED_1_90,
	HS_SHUTTERSPEED_1_100,
	HS_SHUTTERSPEED_1_125,
	HS_SHUTTERSPEED_1_180,
	HS_SHUTTERSPEED_1_250,
	HS_SHUTTERSPEED_1_350,
	HS_SHUTTERSPEED_1_500,
	HS_SHUTTERSPEED_1_725,
	HS_SHUTTERSPEED_1_1000,
	HS_SHUTTERSPEED_1_1500,
	HS_SHUTTERSPEED_1_2000,
	HS_SHUTTERSPEED_1_3000,
	HS_SHUTTERSPEED_1_4000,
	HS_SHUTTERSPEED_1_6000,
	HS_SHUTTERSPEED_1_10000,
}HS_SHUTTERSPEED_TYPE;

typedef struct HS_DISPLAY_PROPERTY{
	unsigned char ucCH;                /*0*/
	unsigned char ucMirrorMode;        /*0:No 1:Horizontal 2:Vertical 3:Both*/
	unsigned char ulElectronicShutter; /*HS_SHUTTERSPEED_TYPE*/
	unsigned char ucIRLEDEnable;       /*0:close 1:open */
	unsigned char ucIRCutMode;         /*0:LDR atuo 1:video auto 2:Color Mode 3:Black and white*/
	unsigned char ucIRCutSwitchTime;   /*3-120 second*/
	unsigned char ucIRCutSensitivity;  /*ircut:0-7*/
	unsigned char ucOSDVisiable;       /*0 no, 1 yes*/
	unsigned char ucOSDPostion;        /*HS_POSITON_TYPE*/
	unsigned char ucDateVisiable;      /*0 no  1 yes*/
	unsigned char ucDateFormat;        /*0:y/m/d 1:m/d/y 2:d/m/y*/
	unsigned char ucIPCNameVisiable;   /*0 no 1 yes*/
	unsigned char ucOSDText[200];      /*osd text*/
	unsigned char ucRotateAngle;       /*HS_ROTATE_TYPE*/
}HS_DISPLAY_PROPERTY;

/********************************************************************************************/
/*******************************        Log       ***************************************/
/********************************************************************************************/
typedef struct HS_LOG_GREP_INFO{
	unsigned long ulLanguage;        
	unsigned long ulStartNo;         
	unsigned long ulNum;			 
	unsigned long ulStartTime;       
	unsigned long ulEndTime;         
	unsigned char ucType;			 
}HS_LOG_GREP_INFO;

#define HS_LOGTYPE_ALL       0xff     
#define HS_LOGTYPE_SYS       0x01     
#define HS_LOGTYPE_USER      0x02     
#define HS_LOGTYPE_CONFIG    0x04     
#define HS_LOGTYPE_FILE      0x08     
#define HS_LOGTYPE_STAT      0x10     
#define HS_LOGTYPE_ALARM     0x20     

typedef struct HS_LOG_INFO{
	unsigned long totleNum;         
	unsigned long suitableNum;      
	unsigned long ulLanguage;       
	unsigned long ulEncodeType;              
}HS_LOG_INFO;

typedef struct HS_LOG_EVENT_INFO{
	unsigned long ulNo;              
	unsigned long ulType;            
	unsigned long ulCh;              
	unsigned long ulTIme;            
	unsigned char ucMes[100];        
}HS_LOG_EVENT_INFO;

/********************************************************************************************/
/*******************************        SMTP FTP P2P DDNS       ***************************************/
/********************************************************************************************/
typedef struct HS_SMTP_PROPERTY{
	unsigned char ucCh;                              /*通道*/
	unsigned char ucEnable;                          /*是否打开 0不需要, 1启动,*/
	unsigned char ucAttfileformat;					 /*上传附件格式, 0:Message 1:JPEG 2:AVI*/
	unsigned char ucAlarmDuration;                	 /*报警上传间隔,0:10秒 1:30秒 2:1分钟 3:5分钟 4:10分钟 5:一直有效 6:1秒*/
	unsigned long ulPort;                            /*端口: 填写 25 或大于 1024*/
	unsigned long ulAnonymity;                       /*匿名 0匿名,1不匿名*/
	unsigned long ulEncryptionType;                  /*加密类型 0不加密,1SSL*/
	unsigned long ulTime;                            /*发送间隔时间 1-999*/
	unsigned long ulAccessory;                       /*是否加附件, 0加, 1不加*/
	unsigned long ulAccessoryType;                   /*附件类型(暂时没用)*/
	unsigned char ucUserName[64];                    /*用户名*/
	unsigned char ucPasswd[64];                      /*密码*/

	unsigned char ucServerAddr[200];   
	unsigned char ucSenderAddr[200];   
	unsigned char ucRecverAddr1[200];  
	unsigned char ucRecverAddr2[200];  
	unsigned char ucRecverAddr3[200];  
	unsigned char ucTheme[200];        
	unsigned char ucSmtpTestEnable;					 /*邮箱测试 0:不使能 1:收件箱1使能 2:收件箱2使能 3:收件箱3使能*/
	unsigned char ucSmtpTestStatus;					 /*邮箱测试状态 0:成功 1:不成功*/
	unsigned char ucRes2[14];                        /*保留2*/
}HS_SMTP_PROPERTY;

typedef struct HS_FTP_PROPERTY{
	unsigned char ucCh;                              /*通道*/
	unsigned char ucEnable;                          /*是否打开 0不需要, 1启动,*/
	unsigned char ucAttfileformat;					 /*上传附件格式, 0:Message 1:JPEG 2:AVI*/
	unsigned char ucAnonymousEnable;                 /*匿名 0:不使能 1:使能*/
	unsigned long ulPort;                            /*端口: 填写 21 或大于 1024*/
	unsigned char ucUserName[32];      /*用户名*/
	unsigned char ucPasswd[32];          /*密码*/
	unsigned char ucServerAddr[200];                 /*服务器地址*/
	unsigned char ucPath[200];                       /*路径*/
	unsigned char ucAutoCoverEnable;				 /*自动覆盖 0:不使能 1:使能*/
	unsigned char ucFtpTestEnable;					 /*邮箱测试 0:不使能 1:使能*/
	unsigned char ucFtpTestStatus;					 /*邮箱测试状态 0:成功 1:不成功*/
}HS_FTP_PROPERTY;

/*DDNS ·þÎñÆ÷ÀàÐÍÃ¶¾Ù*/
typedef enum HS_DDNS_SERVER_TYPE{
	HS_DDNS_SERVER_ORAY           = 0x00,               /*Peanut shells*/
	HS_DDNS_SERVER_NO_IP,                               /*noip*/
	HS_DDNS_SERVER_DYN,                                 /*dyn*/
	HS_DDNS_SERVER_CHANGEIP,                            /*changeip*/
	HS_DDNS_SERVER_A_PRESS,                             /*a-press*/
	HS_DDNS_SERVER_3322,                                /*3322*/
	HS_DDNS_SERVER_MAGUS,                               
	HS_DDNS_SERVER_SMART_EYES,

	HS_DDNS_SERVER_ALL            = 0x50                
}HS_DDNS_SERVER_TYPE;

typedef struct HS_DDNS_PROPERTY{
	unsigned char ucCh; 
	unsigned char ucEnable;                    /*0 close  1 open*/
	unsigned char ucServerType;                /*HS_DDNS_SERVER_TYPE*/
	unsigned char ucState;                     /*0 success, 1 connecting*/

	unsigned char ucServerIp[32];              
	unsigned long ulServerPort;                
	unsigned char ucDomainName[32];            
	unsigned char ucDefaultDomainName[32];     
	unsigned char ucUserName[MAX_USER_NAME_LEN];              
	unsigned char ucPasswd[MAX_PASSWORD_LEN];                 
	unsigned char ucAlias[MAX_USER_NAME_LEN];                 

	unsigned long ulAlivePeriod;               /*60-999999 second*/
	unsigned long ulServiceType;               /*0-user 1-admin*/
}HS_DDNSSERVER_PROPERTY;

/*P2P 区域类型枚举*/
typedef enum HS_P2P_REGION_TYPE{
	HS_P2P_REGION_LONGSE					= 0,								/*长视*/
	HS_P2P_REGION_THAILAND					= 1,								/*泰国*/
	HS_P2P_REGION_CHINA						= 30,								/*中国*/
	HS_P2P_REGION_AMERICA					= 40, 								/*美洲*/
	HS_P2P_REGION_EUROPE					= 50,								/*欧洲*/
	HS_P2P_REGION_ASIA_AND_AFRICA 			= 60								/*亚非*/
}HS_P2P_REGION_TYPE;

typedef struct HS_P2P_PROPERTY{
	unsigned char ucFreeIpEnable;              
	unsigned char ucFreeIpSerialNumber[100];   
	unsigned char ucFreeIpIOSAppAddr[100];     
	unsigned char ucFreeIpAndroidAppAddr[100]; 
	unsigned char ucFreeIpRegion;			   /*填写 HS_P2P_REGION_TYPE*/
}HS_P2P_PROPERTY;

typedef struct HS_P2P_INFO{
	unsigned char ucFreeIpIsOnline;                  /*0 no 1 yes*/
	unsigned char ucDanaleIsOnline;                  /*0 no 1 yes*/
}HS_P2P_INFO;

/********************************************************************************************/
/*******************************        STORAGE       ***************************************/
/********************************************************************************************/
typedef enum HS_STORAGE_TYPE{
	HS_STORAGE_NULL      =  0x00,   
	HS_STORAGE_SDCARE    =  0x01,   
	HS_STORAGE_USBDISK   =  0x02,   
	HS_STORAGE_HARDDISK  =  0x04,   
	HS_STORAGE_FTP       =  0x08,   
	HS_STORAGE_SMTP      =  0x10,   
	HS_STORAGE_CLOUD     =  0x20,   
	HS_STORAGE_ALL       =  0xff    
}HS_STORAGE_TYPE;

typedef enum HS_STORAGE_ID_TYPE{
	HS_STORAGE_ID_1    =   0x01,         
	HS_STORAGE_ID_2    =   0x02,         
	HS_STORAGE_ID_3    =   0x04,         
	HS_STORAGE_ID_4    =   0x08,         
	
	HS_STORAGE_ID_5    =   0x10,         
	HS_STORAGE_ID_6    =   0x20,         
	HS_STORAGE_ID_7    =   0x40,         
	HS_STORAGE_ID_8    =   0x80,         
	
	HS_STORAGE_ID_NULL =   0x00,         
	HS_STORAGE_ID_ALL  =   0xff,         
}HS_STORAGE_ID_TYPE;

typedef struct HS_STORAGE_PROPERTY{
	unsigned char ucCh;
	unsigned char ucStorageType;       /*HS_STORAGE_TYPE*/

	unsigned char ucPackingModel;      /*0 by time 1 by size 2 None*/
	union{
		unsigned char ucPackingTime;   /*0-255 min*/
		unsigned char ucPackingSize;   /*0:125M, 1:256M, 2:512M, 3:1G, 4:2G, 5:4G*/
	}ucPackingValue;

	unsigned char ucLackSpaceModel;    /*0:stop 1:Cycle cover, 2:Validity of the cover, */
	unsigned char ucId;                /*HS_STORAGE_ID_TYPE*/
}HS_STORAGE_PROPERTY;

typedef struct HS_STORAGE_INFO{
	unsigned char ucCh; 
	unsigned char ucStorageType;       /*HS_STORAGE_TYPE*/
	unsigned char ucState;             /*0available 1unavailable 2formating */
	unsigned char ucPercent;           /*0-100*/
	unsigned long ulTotle;             /*unit(MB)*/
	unsigned long ulFree;              /*unit(MB)*/
	unsigned char ucId;                /*HS_STORAGE_ID_TYPE*/
}HS_STORAGE_INFO;

typedef enum HS_STORAGE_OPTION_TYPE{
	HS_STORAGE_OPTION_FORMAT = 0,         
	HS_STORAGE_OPTION_CLEAN,              
}HS_STORAGE_OPTION_TYPE;

typedef struct HS_STORAGE_OPTION{
	unsigned char ucCh;
	unsigned char ucStorageType;       /*HS_STORAGE_TYPE*/
	unsigned char ucOptType;           /*HS_STORAGE_OPTION_TYPE*/
	unsigned char ucId;                /*HS_STORAGE_ID_TYPE*/
}HS_STORAGE_OPTION;

/********************************************************************************************/
/*******************************        PLAYBACK       ***************************************/
/********************************************************************************************/
typedef struct HS_PLAYBACK_GREP_INFO{
	unsigned char  ucCh;              
	unsigned short ulType;            
	unsigned long  ulStartNo;         
	unsigned long  ulNum;             
	unsigned long  ulStartTime;       
	unsigned long  ulStopTime;        
	unsigned long  ulMaxFileLen;      
	unsigned long  ulMinFileLen;      
}HS_PLAYBACK_GREP_INFO;

typedef enum HS_PLAYBACK_TYPE{
	HS_PLAYBACK_TYPE_ALL    = 0x07,    
	HS_PLAYBACK_TYPE_ALARM  = 0x01,    
	HS_PLAYBACK_TYPE_TIME   = 0x02,    
	HS_PLAYBACK_TYPE_MANUAL = 0x04,    
}HS_PLAYBACK_TYPE;

typedef struct HS_PLAYBACK_FILE_INFO{
	unsigned char  ucCh;             
	unsigned short ulType;           
	unsigned long  ulFileNo;         
	unsigned long  ulStartTime;      
	unsigned long  ulStopTime;       
	unsigned long  ulFileLen;        
	unsigned char  ucFileName[128];  
}HS_PLAYBACK_FILE_INFO;

typedef enum{
	HS_MULTIPLY_P_1_1 = 0,           
	HS_MULTIPLY_P_2_1,               
	HS_MULTIPLY_P_4_1,               
	HS_MULTIPLY_P_8_1,               
	HS_MULTIPLY_P_16_1,              
	HS_MULTIPLY_P_32_1,              
	HS_MULTIPLY_P_64_1,              
	HS_MULTIPLY_P_128_1,             

	HS_MULTIPLY_P_1_2 = 10,          
	HS_MULTIPLY_P_1_4,               
	HS_MULTIPLY_P_1_8,               
	HS_MULTIPLY_P_1_16,              
	HS_MULTIPLY_P_1_32,              
	HS_MULTIPLY_P_1_64,              
	HS_MULTIPLY_P_1_128,             

	HS_MULTIPLY_N_2_1 = 20,          
	HS_MULTIPLY_N_4_1,               
	HS_MULTIPLY_N_8_1,               
	HS_MULTIPLY_N_16_1,              
	HS_MULTIPLY_N_32_1,              
	HS_MULTIPLY_N_64_1,              
	HS_MULTIPLY_N_128_1,             

	HS_MULTIPLY_N_1_2 = 30,          
	HS_MULTIPLY_N_1_4,               
	HS_MULTIPLY_N_1_8,               
	HS_MULTIPLY_N_1_16,              
	HS_MULTIPLY_N_1_32,              
	HS_MULTIPLY_N_1_64,              
	HS_MULTIPLY_N_1_128,             
}HS_MULTIPLY_TYPE;

/********************************************************************************************/
/*******************************        PTZ       ***************************************/
/********************************************************************************************/
typedef struct HS_PTZ_PROPERTY{
	unsigned char      ucCh;                               /*0*/
	unsigned char      ucStep;                             /*1-8*/
	unsigned char      ucDuration;                         /*1-100*/
	unsigned char      ucApertureMode;                     /*0atuo  1manual*/
	unsigned char      ucApertureVal;                      /*0-100 */
	unsigned char      ucFocusingModel;                    /*0 auto 1 manual*/
}HS_PTZ_PROPERTY;

typedef enum HS_PTZ_OPTION_TYPE{
	HS_PTZ_OPTION_STOP = 0,             
	HS_PTZ_OPTION_CONTINUE,             

	HS_PTZ_OPTION_UP    =  10,          
	HS_PTZ_OPTION_DOWN,                 
	HS_PTZ_OPTION_LEFT,                 
	HS_PTZ_OPTION_RIGHT,                
	HS_PTZ_OPTION_LEFTUP,               
	HS_PTZ_OPTION_LEFTDOWN,             
	HS_PTZ_OPTION_RIGHTUP,              
	HS_PTZ_OPTION_RIGHTDOWN,            

	HS_PTZ_OPTION_ADDZOOM = 20,         
	HS_PTZ_OPTION_DECZOOM,              
	HS_PTZ_OPTION_ADDFOCUS,             
	HS_PTZ_OPTION_DECFOCUS,             
	HS_PTZ_OPTION_ADDAPERTURE,          
	HS_PTZ_OPTION_DECAPERTURE,          
	HS_PTZ_OPT_ZOOM_STOP, 				/*变倍停*/
	HS_PTZ_OPT_FOCUS_STOP,				/*变焦停*/

	HS_PTZ_OPTION_LAMP = 30,            
	HS_PTZ_OPTION_ONEKEYFOCUS,          
	HS_PTZ_OPTION_INITLENS,             
	HS_PTZ_OPT_LENS_CORRECITON,          /*镜头矫正*/

	HS_PTZ_OPT_MOVEPOINT = 40,          
	HS_PTZ_OPT_STARTLOOP,               
	HS_PTZ_OPT_STARTPANCRUISE,          
	HS_PTZ_OPT_STARTLINESCAN,           

	HS_PTZ_OPT_PRESET_SET,				  /*设置预置点*/			
	HS_PTZ_OPT_PRESET_DEL,	              /*删除预置点*/
	HS_PTZ_OPT_TOUR_STOP,	              /*巡航停止*/
}HS_PTZ_OPTION_TYPE;

typedef enum HS_PTZ_OPT_TYPE_EX {
	HS_NVR_PTZ_OPT_UP_START = 0x001,
	HS_NVR_PTZ_OPT_UP_STOP,
	HS_NVR_PTZ_OPT_DOWN_START,
	HS_NVR_PTZ_OPT_DOWN_STOP,
	HS_NVR_PTZ_OPT_LEFT_START,
	HS_NVR_PTZ_OPT_LEFT_STOP,
	HS_NVR_PTZ_OPT_RIGHT_START,
	HS_NVR_PTZ_OPT_RIGHT_STOP,
	HS_NVR_PTZ_OPT_LEFT_UP_START,
	HS_NVR_PTZ_OPT_LEFT_UP_STOP,
	HS_NVR_PTZ_OPT_RIGHT_UP_START,
	HS_NVR_PTZ_OPT_RIGHT_UP_STOP,
	HS_NVR_PTZ_OPT_LEFT_DOWN_START,
	HS_NVR_PTZ_OPT_LEFT_DOWN_STOP,
	HS_NVR_PTZ_OPT_RIGHT_DOWN_START,
	HS_NVR_PTZ_OPT_RITHT_DOWN_STOP,
	HS_NVR_PTZ_OPT_PRESET_SET,
	HS_NVR_PTZ_OPT_PRESET_CALL,
	HS_NVR_PTZ_OPT_PRESET_DEL,
	HS_NVR_PTZ_OPT_ZOOM_ADD_START,
	HS_NVR_PTZ_OPT_ZOOM_ADD_STOP,
	HS_NVR_PTZ_OPT_ZOOM_SUB_START,
	HS_NVR_PTZ_OPT_ZOOM_SUB_STOP,
	HS_NVR_PTZ_OPT_FOCUS_ADD_START,
	HS_NVR_PTZ_OPT_FOCUS_ADD_STOP,
	HS_NVR_PTZ_OPT_FOCUS_SUB_START,
	HS_NVR_PTZ_OPT_FOCUS_SUB_STOP,
	HS_NVR_PTZ_OPT_IRIS_ADD_START,
	HS_NVR_PTZ_OPT_IRIS_ADD_STOP,
	HS_NVR_PTZ_OPT_IRIS_SUB_START,
	HS_NVR_PTZ_OPT_IRIS_SUB_STOP,
	HS_NVR_PTZ_OPT_GOTO_ZERO_PAN,
	HS_NVR_PTZ_OPT_FLIP_180,
	HS_NVR_PTZ_OPT_SET_PATTERN_START,
	HS_NVR_PTZ_OPT_SET_PATTERN_STOP,
	HS_NVR_PTZ_OPT_RUN_PATTERN,
	HS_NVR_PTZ_OPT_SET_AUXILIARY,
	HS_NVR_PTZ_OPT_CLEAR_AUXILIARY,
	HS_NVR_PTZ_OPT_TOUR_START,	               
	HS_NVR_PTZ_OPT_TOUR_STOP,	               
	HS_NVR_PTZ_OPT_AUTO_SCAN_START,
	HS_NVR_PTZ_OPT_AUTO_SCAN_STOP,
	HS_NVR_PTZ_OPT_LEFT_OFFSET,
	HS_NVR_PTZ_OPT_RIGHT_OFFSET,
	HS_NVR_PTZ_OPT_DOWN_OFFSET,
	HS_NVR_PTZ_OPT_UP_OFFSET,
	HS_NVR_PTZ_OPT_ZOOM_MULTIPLE,
	HS_NVR_PTZ_OPT_POINT_CENTER,
	HS_NVR_PTZ_OPT_VIEW_CENTER,
	HS_NVR_PTZ_OPT_ENTER,
	HS_NVR_PTZ_OPT_ENTER_MENU,                
	HS_NVR_PTZ_OPT_OPEN_ADD_START,
	HS_NVR_PTZ_OPT_OPEN_ADD_STOP,
	HS_NVR_PTZ_OPT_OPEN_SUB_START,
	HS_NVR_PTZ_OPT_OPEN_SUB_STOP,
	HS_NVR_PTZ_OPT_EXIT,                      
	HS_NVR_PTZ_OPT_BUTT,
}HS_PTZ_OPT_TYPE_EX;

typedef struct HS_PTZ_OPTION{
	unsigned char ucCh;               
	unsigned char ucOptType;            
	union{
		unsigned char ucPresetPointIndex;   
		unsigned char ucCruiseLineIndex;  
	}opt;
}HS_PTZ_OPTION;

/*ptz 信息*/
typedef struct HS_PTZ_INFO{
	unsigned char	   ucCh;
	unsigned char      ucZoomPos;                          /*0-100 倍率*/
	unsigned char      ucRes[2];
	int      	       ucPanPos;			
	int      	       ucTiltPos;
	unsigned char      ucRes1[8];                          /*保留*/
}HS_PTZ_INFO;

typedef enum HS_TYPICALNUM_TYPE{
	HS_TYPICALNUM_INVALID          =   0xf0,  
	HS_TYPICALNUM_ALL              =   0xf1,   
	HS_TYPICALNUM_ENABLE,
	HS_TYPICALNUM_DISABLE,
}HS_TYPICALNUM_TYPE;

typedef struct HS_PRESET_POINT_PROPERTY{
	unsigned char      ucCh;                               
	unsigned char      ucIndex;                            																																																												
	unsigned char      ucEnable;                           
	unsigned char      ucNodeName[MAX_PTZ_NAME_LEN];       
}HS_PRESET_POINT_PROPERTY;

typedef struct HS_CRUISE_POINT_PROPERTY{
	unsigned char      ucCh;                               
	unsigned char      ucCruiseLineIndex;                  
	unsigned char      ucCruisePointIndex;                 
	unsigned char      ucEnable;                           
	unsigned char      ucPresetPointIndex;                 
	unsigned char      ucStep;                             
	unsigned long      ulDwelltime;                        
}HS_CRUISE_POINT_PROPERTY;

typedef struct HS_CRUISE_LINE_PROPERTY{
	unsigned char              ucCh;                                       
	unsigned char              ucIndex;                                    
	unsigned char              ucEnable;                                   
	unsigned char              ucLineName[MAX_PTZ_NAME_LEN];               
	HS_CRUISE_POINT_PROPERTY   ucPoints[MAX_PTZ_CRUISE_POINT_NUM];         
}HS_CRUISE_LINE_PROPERTY;

typedef enum HS_BAUD_RATE
{
	HS_BAUD_RATE_110 = 110,
	HS_BAUD_RATE_300 = 300,
	HS_BAUD_RATE_600 = 600,
	HS_BAUD_RATE_1200 = 1200,
	HS_BAUD_RATE_2400 = 2400,
	HS_BAUD_RATE_4800 = 4800,
	HS_BAUD_RATE_9600 = 9600,
	HS_BAUD_RATE_19200 = 19200,
	HS_BAUD_RATE_38400 = 38400,
	HS_BAUD_RATE_57600 = 57600,
	HS_BAUD_RATE_115200 = 115200,
	HS_BAUD_RATE_230400 = 230400,
	HS_BAUD_RATE_460800 = 460800,
	HS_BAUD_RATE_921600 = 921600,
}HS_BAUD_RATE;

typedef enum HS_DATA_BIT
{
	HS_DATA_BIT_6 = 6,
	HS_DATA_BIT_7 = 7,
	HS_DATA_BIT_8 = 8,
	HS_DATA_BIT_BUTT,
}HS_DATA_BIT;

typedef enum HS_STOP_BIT
{
	HS_STOP_BIT_1 = 1,
	HS_STOP_BIT_2 = 2,
	HS_STOP_BIT_BUTT,
}HS_STOP_BIT;

typedef enum HS_CHECKTYPE_BIT
{
	HS_PTZ_CRCCHECK_TYPE_NONE = 0,	   
	HS_PTZ_CRCCHECK_TYPE_ODD  = 1,    
	HS_PTZ_CRCCHECK_TYPE_EVEN = 2,    
	HS_PTZ_CRCCHECK_TYPE_BUTT
}HS_CHECKTYPE_BIT;

typedef enum HS_PTZ_PROTOCOL
{
	HS_PTZ_PROTOCOL_HY = 0,
	HS_PTZ_PROTOCOL_PANASONIC = 1,
	HS_PTZ_PROTOCOL_PELCO9750 = 2,
	HS_PTZ_PROTOCOL_PELCOD = 3,
	HS_PTZ_PROTOCOL_PELCOD1 = 4,
	HS_PTZ_PROTOCOL_PELCODS1 = 5,
	HS_PTZ_PROTOCOL_PELCOP = 6,
	HS_PTZ_PROTOCOL_PELCOP1 = 7,
	HS_PTZ_PROTOCOL_PELCOP5 = 8,
	HS_PTZ_PROTOCOL_PHILIPS = 9,
	HS_PTZ_PROTOCOL_SAMSUNG = 10,
	HS_PTZ_PROTOCOL_SANLI = 11,
	HS_PTZ_PROTOCOL_SANTANCHI = 12,
	HS_PTZ_PROTOCOL_SHARP = 13,
	HS_PTZ_PROTOCOL_SONY = 14,
	HS_PTZ_PROTOCOL_YAAN = 15,
	HS_PTZ_PROTOCOL_BUTT,
}HS_PTZ_PROTOCOL;

typedef struct HS_PTZ_SERIAL_PROPERTY{
	unsigned char ucCh;
	unsigned char ucAddr;                	
	unsigned char ucDataBit;            	
	unsigned char ucStopBit;                
	unsigned char ucCheckType;              
	unsigned char ucProtocol;       			
	unsigned long ulBaudRate;       		
}HS_PTZ_SERIAL_PROPERTY;

/********************************************************************************************/
/*******************************      AGREEMENT PROPERTY  ***************************************/
/********************************************************************************************/
typedef struct HS_RTSP_AGREEMENT_PROPERTY{
	unsigned short usPort;                          
	unsigned char  ucAuthentication;                /*0close 1 open*/
}HS_RTSP_AGREEMENT_PROPERTY;

typedef struct HS_XM_AGREEMENT_PROPERTY{
	unsigned short usPort;                       
}HS_XM_AGREEMENT_PROPERTY;

typedef struct HS_PRIVATE_AGREEMENT_PROPERTY{
	unsigned short  usPort;                         
}HS_PRIVATE_AGREEMENT_PROPERTY;

typedef struct HS_ONVIF_AGREEMENT_PROPERTY{
	unsigned short  usPort;                          
	unsigned char  ucAuthentication;                /*0close 1 open*/
}HS_ONVIF_AGREEMENT_PROPERTY;

typedef struct HS_HTTP_AGREEMENT_PROPERTY{
	unsigned short usPort;                          
}HS_HTTP_AGREEMENT_PROPERTY;

typedef struct HS_TCP_AGREEMENT_PROPERTY{
	unsigned short usPort;                         
}HS_TCP_AGREEMENT_PROPERTY;

typedef enum HS_AGREEMENT_TYPE{
	HS_AGREEMENT_NULL        = 0x00,       
	HS_AGREEMENT_RTSP        = 0x01,       
	HS_AGREEMENT_XM          = 0x02,       
	HS_AGREEMENT_PRIVATE     = 0x04,       
	HS_AGREEMENT_ONVIF       = 0x08,       
	HS_AGREEMENT_HTTP		 = 0x10,       
	HS_AGREEMENT_TCP         = 0x20,       
	HS_AGREEMENT_HTTPS       = 0x40,
	HS_AGREEMENT_ALL         = 0xff        
}HS_AGREEMENT_TYPE;

/*https 属性配置*/
typedef struct HS_HTTPS_AGREEMENT_PROPERTY{
	unsigned short usPort;                          /*协议端口: 需填写大于 1024 或 80*/
}HS_HTTPS_AGREEMENT_PROPERTY;

typedef struct HS_AGREEMENT_PROPERTY{
	unsigned char     ucEnable;                     
	unsigned char     ucArgType;                    /*ARG_AGREEMENT_TYPE */

	union{
		HS_RTSP_AGREEMENT_PROPERTY      rtspPro;       
		HS_XM_AGREEMENT_PROPERTY        xmPro;         
		HS_PRIVATE_AGREEMENT_PROPERTY   privatePro;    
		HS_ONVIF_AGREEMENT_PROPERTY     onvifPro;      
		HS_HTTP_AGREEMENT_PROPERTY      httpPro;       
		HS_TCP_AGREEMENT_PROPERTY       tcpPro;        
		HS_HTTPS_AGREEMENT_PROPERTY     httpsPro;	    /*https 协议*/
	}property;
}HS_AGREEMENT_PROPERTY;

/********************************************************************************************/
/*******************************      ALARM  ***************************************/
/********************************************************************************************/

typedef enum HS_ALARM_TYPE{
	HS_ALARM_NULL               = 0x00,       
	HS_ALARM_MOTIONDETECTION    = 0x01,       
	HS_ALARM_IO                 = 0x02,       
	HS_ALARM_VIDEOCOVER         = 0x04,       
	HS_ALARM_ALL                = 0xff,       
}HS_ALARM_TYPE;

typedef enum HS_ALARM_ENABLE_TYPE{
	HS_ALARM_ENABLE_NULL			= 0x00,   	
	HS_ALARM_ENABLE_USBDISK     	= 0x02,   	
	HS_ALARM_ENABLE_HARDDISK    	= 0x04,   	
	HS_ALARM_ENABLE_FTP				= 0x08,		
	HS_ALARM_ENABLE_SMTP			= 0x10,   	
	HS_ALARM_ENABLE_CLOUD			= 0x20,		
	HS_ALARM_ENABLE_IO				= 0x40,   	

	HS_ALARM_ENABLE_ALL				= 0xff			
}HS_ALARM_ENABLE_TYPE;

typedef enum HS_ALARM_DURATION_TYPE{
	HS_ALARM_DURATION_1S     = 0,               
	HS_ALARM_DURATION_3S,                       
	HS_ALARM_DURATION_5S,                       
	HS_ALARM_DURATION_10S,                      
	HS_ALARM_DURATION_15S,                      
	HS_ALARM_DURATION_30S,                      
	HS_ALARM_DURATION_45S,                      

	HS_ALARM_DURATION_1MIN   = 10,              
	HS_ALARM_DURATION_3MIN,                     
	HS_ALARM_DURATION_5MIN,                     
	HS_ALARM_DURATION_10MIN,                    
	HS_ALARM_DURATION_15MIN,                    
	HS_ALARM_DURATION_30MIN,                    

	HS_ALARM_DURATION_LIVE   = 20,              
}HS_ALARM_DURATION_TYPE;


typedef struct HS_STREAM_RECORD_PROPERTY{
	unsigned char     ucEnable;              
	unsigned char     ucStorageType;         
	unsigned char     ucVideoStreamType;     
	unsigned char     ucAudioStreamType;     
	unsigned char     ucValidWeek;           
	unsigned char     ucDuration;            
}HS_STREAM_RECORD_PROPERTY;

typedef struct HS_STREAM_SNAPSHOOT_PROPERTY{
	unsigned char     ucEnable;              
	unsigned char     ucStorageType;         
	unsigned char     ucVideoStreamType;     
	unsigned char     ucValidWeek;           
	unsigned char     ucShootNum;            
	unsigned char     ucSingalShootInterval; 
	unsigned char     ucDuration;            
}HS_STREAM_SNAPSHOOT_PROPERTY;

typedef struct HS_TEXT_RECORD_PROPERTY{
	unsigned char     ucEnable;               
	unsigned char     ucStorageType;          
	unsigned char     ucText[32];             
}HS_TEXT_RECORD_PROPERTY;

typedef struct HS_BUZZER_PROPERTY{
	unsigned char     ucEnable;              
	unsigned char     ucDuration;            
}HS_BUZZER_PROPERTY;

typedef struct HS_REGULAR_RECORD_PROPERTY{
	HS_STREAM_RECORD_PROPERTY     videoRecord;            
	HS_TIME_HOUR_SCOPE            timeSocpeTab[7][6];     
}HS_REGULAR_RECORD_PROPERTY;

typedef struct HS_NVR_REGULAR_RECORD_PROPERTY{
	unsigned char					 ucCh;                   /*通道号*/
	unsigned char					 ucRes[3]; 
	HS_STREAM_RECORD_PROPERTY        videoRecord;           
	HS_TIME_WEEK_SCOPE               weekScop;              
}HS_NVR_REGULAR_RECORD_PROPERTY;

typedef struct HS_REGULAR_SNAP_PROPERTY{
	unsigned char                 ucShootInterval;        
	HS_STREAM_SNAPSHOOT_PROPERTY  snapshoot;              
	HS_TIME_HOUR_SCOPE            timeSocpeTab[7][6];     
}HS_REGULAR_SNAP_PROPERTY;

typedef struct HS_NVR_REGULAR_SNAP_PROPERTY{
	unsigned char                 ucCh; 
	unsigned char                 ucShootInterval;        
	HS_STREAM_SNAPSHOOT_PROPERTY     snapshoot;           
	HS_TIME_WEEK_SCOPE               weekScop;            
}HS_NVR_REGULAR_SNAP_PROPERTY;

typedef struct HS_ALARM_PROPERTY{
	unsigned char                ucAlarmType;            
	unsigned char                ucDuration;             
	unsigned char                ucEnable;               

	HS_STREAM_RECORD_PROPERTY       videoRecord;         
	HS_STREAM_SNAPSHOOT_PROPERTY    snapshoot;           
	HS_TEXT_RECORD_PROPERTY         message;             
	HS_BUZZER_PROPERTY              buzzer;              

	unsigned char                ucTimeScopeMode;        
	HS_TIME_HOUR_SCOPE           timeSocpeTab[7][6];     
}HS_ALARM_PROPERTY;

typedef struct HS_NVR_ALARM_PROPERTY{
	unsigned char                ucAlarmType;            
	unsigned char                ucDuration;             
	unsigned char                ucEnable;               

	HS_STREAM_RECORD_PROPERTY       videoRecord;         
	HS_STREAM_SNAPSHOOT_PROPERTY    snapshoot;           
	HS_TEXT_RECORD_PROPERTY         message;             
	HS_BUZZER_PROPERTY              buzzer;              

	HS_TIME_WEEK_SCOPE              weekScop;            
}HS_NVR_ALARM_PROPERTY;

typedef struct HS_ALARM_SCOPE{
	unsigned char  ucAlarmTypeScope;            

	unsigned char  ucStreamRecordEnable;        
	unsigned char  ucStreamRecordStorageScope;  

	unsigned char  ucSnapshootEnable;           
	unsigned char  ucSnapshootScope;            

	unsigned char  ucMessageEnable;             
	unsigned char  ucMessageScope;              
	unsigned char  ucBuzzer;                    
}HS_ALARM_SCOPE;

typedef enum HS_ACTION_TYPE{
	HS_ACTION_NULL     =  0x00,   
	HS_ACTION_AVI      =  0x01,   
	HS_ACTION_JPEG     =  0x02,   
	HS_ACTION_MESSAGE  =  0x04,   
	HS_ACTION_ALL	   =  0xff    
}HS_ACTION_TYPE;

typedef struct HS_ALARM_SCOPE_V2{
	unsigned char  ucFtpActionScope;	/*Ftp: HS_ACTION_TYPE .*/
	unsigned char  ucSmtpActionScope;	/*Smtp: HS_ACTION_TYPE .*/
}HS_ALARM_SCOPE_V2;

typedef struct HS_ALARM_PROPERTY_V2{
	unsigned char  ucEnable;				/*0:close 1:open*/
	unsigned char  ucDuration;				/*HS_ALARM_DURATION_TYPE*/
	unsigned char  ucFtpActionEnable;		/*0:close 1:open*/
	unsigned char  ucFtpActionType;			/*HS_ACTION_TYPE*/
	unsigned char  ucSmtpActionEnable;		/*0:close 1:open*/
	unsigned char  ucSmtpActionType;		/*HS_ACTION_TYPE*/
}HS_ALARM_PROPERTY_V2;

typedef struct HS_MOTIONDETECTION_INFO{
	unsigned char ucCH;               
	unsigned char ucAlarmType;        
	unsigned char ucStatus;           
	unsigned char ucLevel;            
	unsigned long ulTime;             
}HS_MOTIONDETECTION_INFO;

/********************************************************************************************/
/*******************************      ROI  ***************************************/
/********************************************************************************************/
typedef enum HS_ROI_QP_TYPE{
	HS_ROI_QP_ABSOLUTE = 0,              
	HS_RIO_QP_RELATIVE = 1               
}HS_ROI_QP_TYPE;

typedef struct HS_ROI_REGION{
	HS_RECT      area;               
	unsigned char ucQpType;          
	char cQpVal;					 
	unsigned char ucEnbale;          
}HS_ROI_REGION;

typedef struct HS_ROI_PROPERTY{
	unsigned char ucCh;
	unsigned char ucEnable;           
	unsigned char ucBgFrameRate;      
	HS_ROI_REGION    region[8];
}HS_ROI_PROPERTY;

/********************************************************************************************/
/*******************************           LDC        ***************************************/
/********************************************************************************************/
typedef struct HS_LDC_PROPERTY{
	unsigned char ucCh;
	unsigned char  ucViewType;    
	int  lCenterXOffset;		  
	int  lCenterYOffset;		  
	unsigned int  ulRatio;       
}HS_LDC_PROPERTY;


/********************************************************************************************/
/*******************************        USER       ***************************************/
/********************************************************************************************/
typedef enum HS_USER_ROLE_TYPE{
	HS_USER_ROLE_ROOT    =  0x00,       
	HS_USER_ROLE_ADMIN   =  0x01,       
	HS_USER_ROLE_USER    =  0x02,       
}HS_USER_ROLE_TYPE;

typedef enum HS_USER_POWER_TYPE{
	HS_USER_POWER_REBOOT_OPTION                    = (1<<1),  
	HS_USER_POWER_UPGRADE_OPTION                   = (1<<2),  
	HS_USER_POWER_RESET_OPTION                     = (1<<3),  
	
	HS_USER_POWER_USER_OPTION                      = (1<<8),  
	HS_USER_POWER_STORAGE_OPTION                   = (1<<9),  
	HS_USER_POWER_NET_CONFIG                       = (1<<10), 
	HS_USER_POWER_PTZ_OPTION                       = (1<<11), 
	HS_USER_POWER_SYS_COMMON_CONFIG                = (1<<12), 
	HS_USER_POWER_AUTO_MAINTAIN                    = (1<<13), 
	
	HS_USER_POWER_VIDEO_RECORDING_DOWNLOAD         = (1<<16), 
	HS_USER_POWER_VIDEO_RECORDING_CONFIG           = (1<<17), 
	HS_USER_POWER_VIDEO_OUPUT_CONFIG               = (1<<18), 
	HS_USER_POWER_LOGFILE_OPTION                   = (1<<19), 
	HS_USER_POWER_TERNINAL_CONFIG                  = (1<<20), 
	HS_USER_POWER_CHANNEL_CONFIG                   = (1<<21), 
	HS_USER_POWER_PRIVIEW_CONFIG                   = (1<<22), 

	HS_USER_POWER_ENCODING_CONFIG                  = (1<<24), 
	HS_USER_POWER_MOTIONDETECTION_CONFIG           = (1<<25), 
}HS_USER_POWER_TYPE;

typedef enum HS_USER_CONFIG_TYPE
{
	HS_USER_ADD,
	HS_USER_DEL,
	HS_USER_EDIT
}HS_USER_CONFIG_TYPE;

typedef struct HS_USER_INFO{
	unsigned char ucUsername[MAX_USER_NAME_LEN];    
	unsigned char ucPassWord[MAX_PASSWORD_LEN];     
	unsigned char ucRole;                            /*0admin 1operator 2user*/
	unsigned long ulPower;                           /*reserve*/
}HS_USER_INFOR;

/********************************************************************************************/
/*******************************        搜索设备       ***************************************/
/********************************************************************************************/
typedef struct HS_SEARCH_DEV_INFO{
	unsigned char   ucNum;                             /*序号*/
	unsigned char   ucArgType;                         /*协议类型: 填写 HS_AGREEMENT_ONVIF 或 HS_AGREEMENT_PRIVATE */
	unsigned char   ucDevType;                         /*设备类型: 填写 HS_DEV_TYPE*/
	unsigned char   ucDevIP[MAX_IPSTR_LEN];            /*IP地址*/
	unsigned short  usDevPort;                         /*设备端口号*/
}HS_SEARCH_DEV_INFO;

/********************************************************************************************/
/*******************************        CHANNEL       ***************************************/
/********************************************************************************************/
typedef struct HS_CHANNEL_SCOPE{
	unsigned char ucCHScope[64];     
	unsigned long ulCHValidNum;       /* 0-64*/
}HS_CHANNEL_SCOPE;

typedef struct  HS_CHANNEL_PROPERTY{
	unsigned char   ucCh;                              /*0-254, 255:ALL*/
	unsigned char   ucArgType;                         /*HS_AGREEMENT_ONVIF or HS_AGREEMENT_PRIVATE */
	unsigned char   ucDevType;                         /*HS_DEV_TYPE*/
	unsigned char   ucPreviewStream;                   /*HS_STREAM_TYPE*/
	unsigned char   ucTransportPro;                    /*0tcp 1udp*/
	unsigned char   ucEnable;                          /*0close, 1 open*/
	unsigned char   ucUserName[MAX_USER_NAME_LEN];     
	unsigned char   ucPasswd[MAX_PASSWORD_LEN];        
	unsigned char   ucDevIP[MAX_IPSTR_LEN];            
	unsigned short  usDevPort;                         
}HS_CHANNEL_PROPERTY;

/********************************************************************************************/
/*******************************      AV Input Output     ************************************/
/********************************************************************************************/
typedef enum HS_RESOLUTION_TYPE{
	HS_RESOLUTION_QVGA     =  0x00,   /*qvga    320*240*/
	HS_RESOLUTION_WQVGA,              /*wqvga   400*240*/
	HS_RESOLUTION_HVGA,               /*hvga    480*320*/
	HS_RESOLUTION_VGA,                /*vga     640*480*/
	HS_RESOLUTION_WVGA,               /*wvga    800*480*/
	HS_RESOLUTION_SVGA,               /*svga    800*600*/
	HS_RESOLUTION_WSVAG,              /*wsvga   1024*600*/
	HS_RESOLUTION_XGA,                /*xga     1024*768*/
	
	HS_RESOLUTION_720P     =  0x10,   /*720P    1280*720*/
	HS_RESOLUTION_WXGA,               /*wxga    1280*800*/
	HS_RESOLUTION_SXGA,               /*sxga    1280*1024*/
	HS_RESOLUTION_WXGA_PLUS,          /*wxga+   1400*900*/
	HS_RESOLUTION_SXGA_PLUS,          /*sxga+   1400*1050*/
	HS_RESOLUTION_WSXGA,              /*wsxga   1600*1024*/
	HS_RESOLUTION_WSXGA_PLUS,         /*wsxga   1680*1050*/
	HS_RESOLUTION_UXGA,               /*uxga    1600*1200*/

	HS_RESOLUTION_1080P    =  0x20,   /*1080P   1920*1080*/
	HS_RESOLUTION_WUXGA,              /*wuxga   1920*1200*/
	HS_RESOLUTION_QXGA,               /*qxga    2048¡Á1536*/
	HS_RESOLUTION_WQXGA,              /*wuxga   2560*1600*/
}HS_RESOLUTION_TYPE;

typedef enum HS_VIDEO_FORMAT_TYPE{
	HS_VIDEO_FORMAT_NTSC   =   0x00,      /*NTSC*/
	HS_VIDEO_FORMAT_PAL,                  /*PAL*/
}HS_VIDEO_FORMAT_TYPE;

typedef struct HS_VIDEO_OUTPUT_PROPERTY{
	unsigned char   ucCh;
	unsigned char   ucFormat;          /*HS_VIDEO_FORMAT_TYPE*/
	unsigned char   ucResolutionType;  /*HS_RESOLUTION_TYPE*/
}HS_VIDEO_OUTPUT_PROPERTY;

typedef struct HS_AUDIO_PROPERTY{
	unsigned char ucCh;
	unsigned char ucEnable;           /*0:close,1:open*/
	unsigned char ucOutputVolume;     /*0-100*/
	unsigned char ucInputVolume;      /*0-100*/
	unsigned char ucInputModel;       /*0:mic input 1:Active input*/
}HS_AUDIO_PROPERTY;

/********************************************************************************************/
/*******************************       SYSREBOOT      ***************************************/
/********************************************************************************************/
typedef struct HS_SYSREBOOT_PROPERTY{
	unsigned char ucEnable;                    /*0:close, 1:open*/
	unsigned char ucHour;                      /*Unit:hour*/
	unsigned char ucWeekData;                  /*0-6, 7:every day*/
}HS_SYSREBOOT_PROPERTY;

typedef struct HS_COMMON_SYS_PROPERTY{
	unsigned char ucCh;                        
	unsigned char ucLanguageType;              
	unsigned char ucStandbyTime;               
	unsigned char ucBootGuide;                 
	unsigned char ucDevName[32];               
	unsigned char ucDevId;                     
	unsigned char ucRecordDayLimit;            
}HS_COMMON_SYS_PROPERTY;

typedef enum HS_RESET_SYS_TYPE{
	HS_RESET_SYS_COMMON_PROPERTY      =  (1<<1),     
	HS_RESET_SYS_USER_MANAGEMENT      =  (1<<2),     
	
	HS_RESET_SYS_NET                  =  (1<<8),     
	HS_RESET_SYS_SMTP                 =  (1<<9),     
	HS_RESET_SYS_FTP                  =  (1<<10),    
	HS_RESET_SYS_DDNS                 =  (1<<11),    
	
	HS_RESET_SYS_ENCODING_PROPERTY    =  (1<<16),    
	HS_RESET_SYS_MOTIONDETECTION      =  (1<<17),    
	HS_RESET_SYS_VIDEO_RECORDIG       =  (1<<18),    
	HS_RESET_SYS_CHANNEL_PROPERTY     =  (1<<19),    

	HS_RESET_SYS_OUPUT                =  (1<<20),    
	HS_RESET_SYS_PTZ                  =  (1<<21),    
	HS_RESET_SYS_IMAGE                =  (1<<22),    
	HS_RESET_SYS_P2P                  =  (1<<23),    
}HS_RESET_SYS_TYPE;

typedef enum{
	HS_DEV_IPCAMERA = 0x00,
	HS_DEV_DVS,
	HS_DEV_NVS,
	HS_DEV_DECODER
}HS_DEV_TYPE;

typedef enum HS_PLATFORM_TYPE{
	HS_PLATFORM_PC = 0,

	HS_PLATFORM_HISI3516A = 5,
	HS_PLATFORM_HISI3518E,
	HS_PLATFORM_HISI3531,
	HS_PLATFORM_HISI3521,
	HS_PLATFORM_HISI3535,
	HS_PLATFORM_HISI3520D,
	HS_PLATFORM_HISI3516C,
	HS_PLATFORM_HISI3518C,
	HS_PLATFORM_HISI3516C_SDCARD,

	HS_PLATFORM_NXP8850 = 40,

	HS_PLATFORM_AMBA_A5 = 60,
	HS_PLATFORM_AMBA_S2L,
	HS_PLATFORM_AMBA_S2L_124,
	HS_PLATFORM_AMBA_S2L_322,
	HS_PLATFORM_AMBA_S2L_4689,
	HS_PLATFORM_AMBA_S2L_FISH,
	HS_PLATFORM_AMBA_S2L_322_WIFI,

	HS_PLATFORM_A5S66_PTZ = 70,

	HS_PLATFORM_SONY4145 = 80,

	HS_PLATFORM_HISI3518E_V200 = 90,
	HS_PLATFORM_HISI3518E_V200_WIFI,
	HS_PLATFORM_HISI3518E_V200_IMX225,
	HS_PLATFORM_HISI3518E_V200_SDCard,

	HS_PLATFORM_GM8136 = 100,
	HS_PLATFORM_GM8138,
	HS_PLATFORM_GM8135,
	HS_PLATFORM_GM8135_9732,
	HS_PLATFORM_GM8135_9750,

	HS_PLATFORM_HISI3516D = 200,
	HS_PLATFORM_HISI3516D_QJ,
	HS_PLATFORM_HISI3516D_SDCard,
	HS_PLATFORM_HISI3516D_WIFI,

	HS_PLATFORM_HISI3519 = 220,
}HS_PLATFORM_TYPE;

typedef struct HS_DEV_INFO{
	unsigned char ucDevType;                  /*HS_DEV_TYPE*/
	unsigned char ucPlatformType;             /*HS_PLATFORM_TYPE*/
	unsigned char ucDevName[64];              
	unsigned char ucDEVID[100];               
	unsigned char ucManufacturers[100];       
	unsigned char ucSoftwareVersion[100];      
	unsigned char ucFirmwareVersion[64];	  /*固件版本*/
	unsigned char ucPlatform[16];             /*平台类型*/
	unsigned char ucDevSensor[16];			  /*sensor类型*/
}HS_DEV_INFO;


/********************************************************************************************/
/*******************************           CLOUD      ***************************************/
/********************************************************************************************/
typedef enum HS_CLOUD_BRAND_TYPE{
	HS_CLOUD_BRAND_NULL              =   0x00,

	HS_CLOUD_BRAND_BAIDU             =   0x10,
	HS_CLOUD_BRAND_GOOGLE,
	HS_CLOUD_BRAND_DROPBOX
}HS_CLOUD_BRAND_TYPE;

typedef struct HS_CLOUD_BIND_INFO{
	unsigned char ucCh;                      /*0*/
	unsigned char ucBindType;                /*CLOUD_BRAND_TYPE*/
	unsigned char ucWebsite[256];            
	unsigned char ucVerificationCode[64];    
}HS_CLOUD_BIND_INFO;

typedef struct HS_CLOUD_STATE_INFO{
	unsigned char ucCh;                     /*0*/
	unsigned char ucBindState;              /*CLOUD_BRAND_TYPE*/
	unsigned char ucUserName[64];           
	unsigned char ucTotleSize[64];          
	unsigned char ucUsedSize[64];           
}HS_CLOUD_STATE_INFO;

/********************************************************************************************/
/*******************************   导入导出配置文件   ***************************************/
/********************************************************************************************/
typedef enum HS_FILE_TYPE{
	HS_LONGSE_FILE_CFG= 0,
	HS_LONGSE_FILE_CUSTOM_CFG,
	HS_LONGSE_FILE_INI,
	HS_LONGSE_FILE_OCX,
	HS_LONGSE_FILE_UPGRADE,
	HS_LONGSE_FILE_END
}HS_FILE_TYPE;

typedef struct HS_FILE_PROPERTY{
	unsigned char ucFileName[256];          /*文件名*/
	unsigned char ucFileType;				/*文件类型*/	
	unsigned char ucUpdateStatus;			/*更新状态*/
	unsigned char ucRes[10];
}HS_FILE_PROPERTY;

/********************************************************************************************/
/*****************************************   WIFI   *****************************************/
/********************************************************************************************/
/*WIFI安全类型*/
typedef enum HS_SSIDSAFE_TYPE{
	HS_SSIDSAFE_NOVERIFICATION = 0,		/*无身份验证*/
	HS_SSIDSAFE_WPA2PERSONA,				/*WPA2-个人*/									 
	HS_SSIDSAFE_WPA2COMPANY,				/*WPA2-企业*/
	HS_SSIDSAFE_8021X,						/*802.1X*/
}HS_SSIDSAFE_TYPE;

/*WIFI加密类型*/
typedef enum HS_SSIDPASSWD_TYPE{
	HS_SSIDPASSWD_AES = 0, 				/*AES*/
}HS_SSIDPASSWD_TYPE;

typedef struct HS_WIFI_INFO{
	unsigned char ucCh;                         /*通道号*/
	unsigned char ucNetCardNum;                 /*网卡号*/
	unsigned char ucRes1[2];					/*保留*/
	unsigned char ucSSID[128];              	/*wifi名*/
	unsigned char ucSSIDPasswd[128];            /*wifi密码*/
	unsigned char ucSSIDSafeKey[128];			/*网络安全密钥*/
	unsigned char ucSSIDType;              		/*加密类型,填写HS_SSIDPASSWD_TYPE*/
	unsigned char ucSSIDSafeType;          		/*安全类型,填写HS_SSIDSAFE_TYPE*/
	unsigned char ulStrength;         			/*0-100 100最强*/
	unsigned char ulIsScane;          			/*0扫描得到,1手动添加*/
	unsigned char ucPasswdType;					/*密码类型, 0:无密码, 1:有密码*/
	unsigned char ucConnectStatue;				/*连接状态, 0:未连typedef接, 1:已连接*/
	unsigned char ucDhcpEnable;					/*DHCP使能, 0:关闭, 1:使能*/
	unsigned char ucRes2[5];
	unsigned char ucIP[16];						/*IP地址*/
	unsigned char ucSubNetMask[16];				/*子网掩码*/
	unsigned char ucGateway[16];				/*网关*/
	unsigned char ucDNS1Ip[16];					/*dns 服务器1*/
	unsigned char ucDNS2Ip[16];					/*dns 服务器2*/
	unsigned char ucMacIp[18];                  /*Mac服务器地址: 填写字符串例如 "A1:B2:C3:D4:E5:F6"*/
	unsigned char ucRes3[128]; 
}HS_WIFI_INFO;

typedef enum HS_WIFI_OPERATE_TYPE
{
	HS_WIFI_ADD,
	HS_WIFI_DEL,
	HS_WIFI_CONNECT,
	HS_WIFI_DISCONNECT
}HS_WIFI_OPERATE_TYPE;

/********************************************************************************************/
/*****************************************   夏令时   *****************************************/
/********************************************************************************************/
typedef struct HS_DST_TIME_CTRL{
	unsigned char  ucMonth;                /*月*/
	unsigned char  ucDay;                  /*日*/
	unsigned char  ucHour;                 /*时*/
	unsigned char  ucweekDay;              /*周*/
	unsigned char  ucWeekNumber;           /*周序号*/
	unsigned char  ucRes[16];              /*保留*/
}HS_DST_TIME_CTRL;

typedef struct HS_DST_PROPERTY{
	unsigned char		ucEnDST;                /*DST开关, 1开启 0关闭*/
	unsigned char		ucDSTType;              /*DST模式, 0日期  1周*/
	HS_DST_TIME_CTRL	ucDSTStart;             /*开始时间*/
	HS_DST_TIME_CTRL    ucDSTEnd;				/*结束时间*/
	unsigned char		offsetTime;				/*偏移时间，默认为一个小时*/
	unsigned char		ucRes[16];              /*保留*/
}HS_DST_PROPERTY;

typedef struct HS_SYSREBOOT_EX_PROPERTY{
	unsigned char ucEnable;                    /*是否开启定时重启, 0关闭, 1开启*/
	unsigned char ucRebootModel;			   /*重启模式, 0每天, 1每周, 2每月*/
	unsigned char ucDay;					   /*重启时间, 单位日*/
	unsigned char ucHour;                      /*重启时间, 单位时*/
	unsigned char ucMinute;					   /*重启时间, 单位分*/
	unsigned char ucSecond;                    /*重启时间, 单位秒*/
	unsigned char ucWeekData;                  /*重启时间, 单位星期, 0-6 分别为星期天到星期六*/
	unsigned char ucRes[57];				   /*保留*/
}HS_SYSREBOOT_EX_PROPERTY;

/********************************************************************************************/
/************************************        IO配置       ***********************************/
/********************************************************************************************/
typedef struct HS_IO_PROPERTY{
	unsigned char ucCh;				/*通道号*/
	unsigned char ucInputEnable;	/*IO输入报警使能: 0关闭 1使能*/
	unsigned char ucInputLevel;		/*输入电平: 0低电平 1高电平*/
	unsigned char ucOutputEnable;	/*IO输出报警使能: 0关闭 1使能*/
	unsigned char ucOutputLevel;	/*输出电平: 0低电平 1高电平*/
	unsigned char ucRes[27];		/*保留*/
}HS_IO_PROPERTY;


/********************************************************************************************/
/*******************************        视频编码扩展配置       ******************************/
/********************************************************************************************/
#define VIDEO_STREAM_MAXNUM		3

/*编码支持枚举类型*/
typedef enum HS_ENCODING_SCOPE_TYPE{
	HS_ENCODING_SCOPE_NULL = 0x00,
	HS_ENCODING_SCOPE_H264 = 0x01,
	HS_ENCODING_SCOPE_H265 = 0x02,
	HS_ENCODING_SCOPE_MPEG = 0x04,

}HS_ENCODING_SCOPE_TYPE;


/*通道类型枚举*/
typedef enum HS_CHANNEL_TYPE{
	HS_CHANNEL_0 = 0,
	HS_CHANNEL_1,
	HS_CHANNEL_2,
	HS_CHANNEL_3,

	HS_CHANNEL_ALL = 256,
}HS_CHANNEL_TYPE;


typedef struct HS_RESOLUTION_PARAM{
	int width;
	int height;
}HS_RESOLUTION_PARAM;


typedef struct HS_RESOLUTION_AVAILABLE_PARAM{
	int sizeResolutions;
	HS_RESOLUTION_PARAM Resolutions[5];
}HS_RESOLUTION_AVAILABLE_PARAM;


/*视频编码属性*/
typedef struct HS_VIDEO_ENCODING_PROPERTY_EX{
	unsigned char  ucEncodingType;      /*视频编码 填写 (HS_ENCODING_TYPE)的视频部分*/
	unsigned char  ucPicQuality;        /*图象质量 0-最好 1-次好 2-较好 3-一般 4-较差 5-差*/
	unsigned char  ucStreamType;		/*码流类型: 0:主码流,1:子码流*/
	unsigned char  ucProfile;			/*编码复杂度 0-低 1-中 3-高*/

	unsigned short usWidth;             /*宽度*/
	unsigned short usHeight;            /*高度*/
	unsigned short ucFrameRate;     	/*帧率*/
	unsigned short ucBitRate;           /*码率 单位k byte(大B)*/

	unsigned char  ucKeyFrameInterval;  /* I帧间隔,(ucEncodingType为h264时有效)*/
	unsigned char  ucBitrateType;       /*码率类型 0:定码率，1:变码率*/

	unsigned char  ucVideoType;			/*视频类型: 0:视频流 1:复合流*/

	unsigned char  ucRes1[21];

	HS_RESOLUTION_AVAILABLE_PARAM ReSolution; /*分辨率有效值*/

}HS_VIDEO_ENCODING_PROPERTY_EX;


typedef struct HS_ENCODING_PROPERTY_EX{
	unsigned char  ucCh;              /*通道号 HS_CHANNEL_TYPE*/

	unsigned char  ucChStreamMode;    /*通道码流模式 0:单码流,1:双码流,2:三码流*/
	unsigned char  ucMaxFrameRate;
	unsigned char  ucMinFrameRate;
	unsigned char  ucEncodingScope;   /*视频编码支持类型,填写 HS_ENCODING_SCOPE_TYPE*/	 

	unsigned char  ucRes[11];

	HS_VIDEO_ENCODING_PROPERTY_EX  Video[VIDEO_STREAM_MAXNUM];	

}HS_ENCODING_PROPERTY_EX;


/********************************************************************************************/
/*********************************        鱼眼参数配置       ********************************/
/********************************************************************************************/
typedef enum HS_STREAM_MODE_TYPE{
	HS_STREAM_MODE_ONE = 0,          /*模式1: 鱼眼+全景+3*PTZ*/
	HS_STREAM_MODE_TWO,     	      /*模式2: 鱼眼或者4*PTZ*/
	HS_STREAM_MODE_THREE,     	      /*模式3: 鱼眼主码流+鱼眼子码流+3PTZ*/
	HS_STREAM_MODE_FOUR,   	      /*模式4: 全景主码流+全景子码流*/
}HS_STREAM_MODE_TYPE;

typedef struct HS_FISH_EYE_PROPERTY{
	unsigned char ucCh;

	unsigned char ucStreamMode;     	/*码流模式 填写 HS_STREAM_MODE_TYPE*/
	unsigned char ucInstallMode;		/*安装方式 0:墙面 1:桌面 2:吸顶*/

	unsigned char ucRes[61];
}HS_FISH_EYE_PROPERTY;


/********************************************************************************************/
/**************************       不同分辨率下编码参数最优配置       ************************/
/********************************************************************************************/
typedef struct HS_SUITABLE_ENCODING_PARAM{
	unsigned char  	ucEncodingType;      		/*视频编码 填写 (HS_ENCODING_TYPE)的视频部分*/
	unsigned char 	ucRes[3]; 
	int 			iWidth;		     			/*宽*/
	int 			iHeight;	     			/*高*/
	int 			iSuitableFrameRate;  		/*最优帧率*/
	int				iSuitableBitRate;    		/*最优比特率*/
	int				iMaxFrameRatetRate;    		/*最大帧率*/
	unsigned char 	ucRes1[40];
}HS_SUITABLE_ENCODING_PARAM;

typedef struct HS_SUITABLE_ENCODING_PROPERTY{
	unsigned char 	ucCh;						/*通道*/
	unsigned char  	iSizeResolutions;			/*分辨率个数*/
	unsigned char   ucRes[2];					/*保留*/
	HS_SUITABLE_ENCODING_PARAM 	Resolutions[10];
}HS_SUITABLE_ENCODING_PROPERTY;


/********************************************************************************************/
/**********************************        OSD扩展配置       ********************************/
/********************************************************************************************/
typedef enum HS_DATE_FORMAT_TYPE{
	HS_DATE_FORMAT_0 = 0,		/*XXXX-XX-XX(年月日)*/
	HS_DATE_FORMAT_1,			/*XX-XX-XXXX(月日年)*/
	HS_DATE_FORMAT_2,			/*XX-XX-XXXX(日月年)*/
	HS_DATE_FORMAT_3,			/*XXXX年XX月XX日*/
	HS_DATE_FORMAT_4,			/*XX月XX日XXXX年*/
	HS_DATE_FORMAT_5,   		/*XX日XX月XXXX年*/
	HS_DATE_FORMAT_6,			/*XX/XX/XXXX(月日年)*/				
	HS_DATE_FORMAT_7,			/*XXXX/XX/XX(年月日)*/
	HS_DATE_FORMAT_8			/*XX/XX/XXXX(日月年)*/

}HS_DATE_FORMAT_TYPE;

typedef enum HS_DISPLAY_MODE_TYPE{
	HS_DISPLAY_MODE_0 = 0,		/*透明,闪烁*/
	HS_DISPLAY_MODE_1,			/*透明,不闪烁*/
	HS_DISPLAY_MODE_2,			/*闪烁,不透明*/
	HS_DISPLAY_MODE_3			/*不透明,不闪烁*/

}HS_DISPLAY_MODE_TYPE;

typedef enum HS_FONTSIZE_MODE_TYPE{
	HS_FONTSIZE_MODE_16_16 = 0x01,	/*16*16*/
	HS_FONTSIZE_MODE_32_32 = 0x02,	/*32*32*/
	HS_FONTSIZE_MODE_48_48 = 0x04,	/*48*48*/
	HS_FONTSIZE_MODE_64_64 = 0x10,	/*64*64*/
	HS_FONTSIZE_MODE_AUTO  = 0x20	/*自适应*/
}HS_FONTSIZE_MODE_TYPE;

typedef struct HS_OSD_PROPERTY_EX{
	unsigned char ucCh;					/*通道*/

	unsigned char ucOsdNameVisiable;	/*显示名称:0:不显示 1:显示*/
	unsigned char ucOsdDateVisiable;	/*显示日期:0:不显示 1:显示*/
	unsigned char ucOsdWeekVisiable;	/*显示星期:0:不显示 1:显示*/

	unsigned char ucOsdTimeFormat;		/*时间格式:0:12小时制 1:24小时制*/
	unsigned char ucOsdDateFormat;		/*日期格式:填写 HS_DATE_FORMAT_TYPE*/
	unsigned char ucOsdDisplayMode;		/*OSD属性:填写 HS_DISPLAY_MODE_TYPE*/
	unsigned char ucOsdFontSizeMode;	/*OSD字体大小:填写HS_FONTSIZE_MODE_TYPE*/

	unsigned char ucOsdFontSizeScope;	/*OSD字体大小支持列表: 填写 HS_FONTSIZE_MODE_TYPE*/

	unsigned char ucOsdTime_X_Coordinate;	/*OSD时间X坐标位置: 0-100 百分比*/
	unsigned char ucOsdTime_Y_Coordinate; 	/*OSD时间Y坐标位置: 0-100 百分比*/  	
	unsigned char ucOsdText_X_Coordinate;	/*OSD字体X坐标位置: 0-100 百分比*/ 
	unsigned char ucOsdText_Y_Coordinate;	/*OSD字体Y坐标位置: 0-100 百分比*/ 

	unsigned char ucRes[51];

	unsigned char ucOsdText[64];		/*OSD显示文本*/

}HS_OSD_PROPERTY_EX;


/********************************************************************************************/
/**********************************      报警布防配置   **************************************/
/********************************************************************************************/
/*报警联动枚举*/
typedef enum HS_ALARM_LINK_TYPE{
	HS_ALARM_LINK_NULL =  0x00, 		/*无*/
	HS_ALARM_LINK_SMTP   =  0x01,   	/*smtp联动 */
	HS_ALARM_LINK_FTP    =  0x02,   	/*ftp联动*/
	HS_ALARM_LINK_CLOUD  =  0x04,   	/*上传云 */
	HS_ALARM_LINK_RECORD =  0x08,   	/*录像联动*/
	HS_ALARM_LINK_IO     =  0x10,   	/*IO输出 */

	HS_ALARM_LINK_ALL    =  0xff    	/*所有*/
}HS_ALARM_LINK_TYPE;

typedef struct HS_ALARM_PROCESS{
	unsigned char 	ucAlarmSmtpEnable;		   /*SMTP联动使能*/
	unsigned char 	ucAlarmFtpEnable;		   /*FTP联动使能*/
	unsigned char 	ucAlarmCloudEnalbe;		   /*上传云使能*/
	unsigned char 	ucAlarmRecordEnable;	   /*录像使能*/
	unsigned char 	ucAlarmIOEnable;		   /*IO联动使能*/
	unsigned char 	ucRes[11];
}HS_ALARM_PROCESS;

typedef struct HS_ALARM_PROPERTY_EX{
	unsigned char       ucCh;                   /*通道*/
	unsigned char       ucAlarmType;            /*报警类型: 填写 HS_ALARM_TYPE*/
	unsigned char       ucAlarmLinkScope;		/*报警联动类型,填写HS_ALARM_LINK_TYPE*/
	unsigned char       ucRes1[29];             /*保留1*/
	HS_TIME_HOUR_SCOPE  timeSocpeTab[7][8];     /*时间表: 7天每天8个时段*/
	HS_ALARM_PROCESS	process;	    		/*报警联动处理*/
	unsigned char       ucRes3[64];             /*保留3*/
}HS_ALARM_PROPERTY_EX;

/********************************************************************************************/
/**********************************      遮挡报警配置   *************************************/
/********************************************************************************************/
/*矩形结构体*/
typedef struct HS_RECT_EX{
	unsigned char	x1;                         /*左上角x坐标百分比*/
	unsigned char 	y1;                         /*左上角y坐标百分比*/
	unsigned char 	x2;                         /*右下角x坐标百分比*/
	unsigned char 	y2;                         /*右下角y坐标百分比*/
}HS_RECT_EX;

typedef struct HS_VIDEOCOVER_ALARM_PROPERTY{
	unsigned char 	ucCH;               	/*通道*/
	unsigned char 	ucEnable;           	/*0:关闭遮盖报警, 1:开启遮盖报警*/
	unsigned char 	ucSensitivity;      	/*灵敏度 0:低 1:中 2:高*/ 
	unsigned char   ucAlarmLinkScope;   	/*报警联动类型,填写HS_ALARM_LINK_TYPE*/  
	unsigned char 	ucRes[4];           	/*保留*/   
	HS_RECT_EX      ucArea[6];          	/*6组百分比区域*/
	HS_TIME_HOUR_SCOPE timeSocpeTab[7][8];  /*时间表: 7天每天8个时段*/
	HS_ALARM_PROCESS	process;	    	/*报警联动处理*/
	unsigned char 	ucRes1[16];          	/*保留*/
}HS_VIDEOCOVER_ALARM_PROPERTY;

/********************************************************************************************/
/*******************************       TCP/IP网络配置扩展   *********************************/
/********************************************************************************************/
#define HS_IPV6STR_LEN       40
#define HS_IPV4STR_LEN		 16

/*网卡枚举类型*/
typedef enum HS_NETCARD_TYPE{
	HS_NetCard_NULL = 0x00,				/*无*/
	HS_NetCard_10M_HALFDUPLEX,        	/*10M半双工*/
	HS_NetCard_10M_FULLDUPLEX,        	/*10M全双工*/
	HS_NetCard_100M_HALFDUPLEX,        	/*10M半双工*/
	HS_NetCard_100M_FULLDUPLEX,        	/*10M半双工*/
	HS_NetCard_AUTO,        			/*自适应*/
}HS_NETCARD_TYPE;

typedef enum HS_IPV6MODE_TYPE{
	HS_IPV6MODE_NULL = 0x00,        /*无*/
	HS_IPV6MODE_MANUAL,				/*手动*/
	HS_IPV6MODE_DHCP,				/*自动获取*/
	HS_IPV6MODE_ROUTE,				/*路由公告*/
}HS_IPV6MODE_TYPE;

/*TCP/IP配置*/
typedef struct HS_NET_PROPERTY_EX{
	unsigned char ucCh;                              /*通道号*/
	unsigned char ucNetCardType;                     /*网卡类型,填写ARG_NETCARD_TYPE*/
	unsigned char ucEnDHCP;                          /*使能dhcp, 0开启 1关闭*/
	unsigned char ucIPAddrTestEnable;				 /*使能IP地址测试, 0:关闭 1:开启*/
	unsigned char ucIPAddrStatus;					 /*IP地址状态,0:可用 1:不可用*/
	unsigned char ucRes1[11];                        /*保留*/
	unsigned char ucIPV4[16];						 /*IPV4地址*/
	unsigned char ucSubNetMaskV4[16];				 /*IPV4子网掩码*/
	unsigned char ucGatewayV4[16];					 /*IPV4网关*/
	unsigned char ucDNS1Ip[16];						 /*dns 服务器1*/
	unsigned char ucDNS2Ip[16];						 /*dns 服务器2*/
	unsigned char ucIPV6Mode;			     		 /*IPV6模式:填写ARG_IPV6MODE_TYPE*/
	unsigned char ucRes2[3];
	int 	  iMaxTransUnit;		     			 /*MTU*/
	unsigned char ucIPV6[40];						 /*IPV6地址*/
	int       iSubNetMaskV6;				         /*IPV6子网掩码*/
	unsigned char ucGatewayV6[40];					 /*IPV6网关*/
	unsigned char ucMulticast[40];					 /*多播地址*/
	unsigned char ucMacIp[20];                       /*Mac服务器地址: 填写字符串例如 "A1:B2:C3:D4:E5:F6"*/
	unsigned char ucRes3[36];                        /*保留*/
}HS_NET_PROPERTY_EX;

/********************************************************************************************/
/***********************************      异常事件    ***************************************/
/********************************************************************************************/
typedef enum HS_ABNORMAL_TYPE{
	HS_ABNORMAL_NULL = 0x00,		
	HS_ABNORMAL_NETLOSS,			/*网线断开*/
	HS_ABNORMAL_IPCONFLICT,			/*IP地址冲突*/
	HS_ABNORMAL_ILLEGALVISIT,    	/*非法访问*/
}HS_ABNORMAL_TYPE;

typedef struct HS_ABNORMAL_EVENT_PROPERTY{
	unsigned char 	ucCh;                      /*通道号*/	
	unsigned char 	ucAbnormalType;			   /*异常类型,填写HS_ABNORMAL_TYPE*/
	unsigned char   ucAlarmLinkScope;	   	   /*报警联动类型,填写HS_ALARM_LINK_TYPE*/
	unsigned char 	ucRes[45];			       /*保留*/
	HS_ALARM_PROCESS	process;		       /*报警联动处理*/		
}HS_ABNORMAL_EVENT_PROPERTY;

/********************************************************************************************/
/************************************      消息       ***************************************/
/********************************************************************************************/
//状态消息
enum HSMSG_TYPE
{
	MSG_RECORD_BEGIN = 0x100,		
	MSG_RECORD_WRITE_ERROR,			
	MSG_RECORD_PACKET_FINISH,		

	MSG_RECORD_BEGIN_ANOTHER,			
	MSG_RECORD_WRITE_ERROR_ANOTHER,		
	MSG_RECORD_PACKET_FINISH_ANOTHER,	

	MSG_MOTION_DETECT = 0x200,	

	MSG_REPLAY_FINISHED = 0x300,	

	MSG_UPGRADE_POS = 0x400,		// void *lpstruct = int* pos, Percentage send files, 
	MSG_UPGRADE_OK,
	MSG_UPGRADE_FAILED,

	MSG_PLAYBACK_FINISH = 0x500,
	MSG_DOWNLOAD_POS, 
	MSG_DOWNLOAD_FINISH,

	//导入导出配置文件
	MSG_IMPORT_FILE_OK = 0x600,
	MSG_IMPORT_FILE_FAILED,
	MSG_IMPORT_FILE_PER,
	MSG_EXPORT_FILE_OK,
	MSG_EXPORT_FILE_FAILED,
	MSG_EXPORT_FILE_PER,
};

#endif
