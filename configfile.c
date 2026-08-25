#define __CONFIGFILE_C__
#include "version.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "util.h"
//#include "configfile.h"
//ttom
#include "lssproto_util.h"
#include "configfile.h"
#include "net.h"
//ttom end
#include "npcutil.h"
// Arminius 7.12 login announce
#include "char.h"
#include "char_data.h"
// CoolFish: add 
#include "lssproto_serv.h"

#ifdef _ANGEL_SUMMON
extern struct MissionInfo missionlist[MAXMISSION];
extern struct MissionTable missiontable[MAXMISSIONTABLE];
#endif

/* ÀßÄê¤òÊÝ  ¤¹¤ë¹½Â¤   */
typedef struct tagConfig
{
    /*¥×¤Ò¥°¥é¥à  (¼«  Åª¤Ëµá¤á¤¿¤¤¤±¤É¤Þ¤ÀÂÌ  */
  char    progname[8];
  char    configfilename[32]; /* config¥Õ¥¡¥¤¥ë   */
    unsigned int debuglevel;   /* ¥Ç¥Ð¥Ã¥°¥ì¥Ù¥ë */
  unsigned int  usememoryunit;    /*¥á¥â¥ê¤Î¥æ¥Ë¥Ã¥È¥µ¥¤³N */
  unsigned int  usememoryunitnum; /*¥á¥â¥ê¤Î¥æ¥Ë¥Ã¥È¿ô */
  char    asname[32];         /*¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤Î  Á°*/
  unsigned short  acservport; /*¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤Î¥Ý¡¼¥È  */
  char    acpasswd[32];       /*¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤Ø¤Î¥Ñ¥¹¥ï¡¼¥É*/
  char    gsnamefromas[32];   /*
                                 * ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤«¤é¸«¤¨¤ë
                                 * ¥²¡¼¥à¥µ¡¼¥Ð¤È¤·¤Æ¤Î  Á°
                                 */
                                 
    // Arminius 7.24 manor pk
  char gsid[32];	// game server chinese id
  unsigned short allowmanorpk;	// is this server allow manor pk
  unsigned short port;        /* ¥µ¡¼¥Ð¤ÎÂÔ¤Á¼õ¤±¥Ý¡¼¥È */
	int				servernumber;	/* ¥²¡¼¥à¥µ¡¼¥Ð¤Î  ¹æ */
	int				reuseaddr;	/* Address already used... ¤¬»ß¤Þ¤é¤Ê¤¤»þ¤Î¤¿¤á¤Ë */
  int             do_nodelay;     /* TCP_NODELAY ¤Ë¤¹¤ë¤«¤É¤¦¤« */
  int             log_write_time; /* ½ñ¤­¤³¤ß¤Ò¥°¤ò¤¹¤ë¤«¤É¤¦¤«¡e */
  int             log_io_time;    /* I/OÁ´  ¤Î»þ´Ö¤Ï¤«¤ë¤«¤É¤¦¤«¡e */
  int             log_game_time;  /* ¥²¡¼¥à¤Î½è  Á´  ¤Î»þ´Ö¤ò¤Ï¤«¤ë */
  int             log_netloop_faster; /* netloop_faster ¤Î¤Ò¥° */
	int				saacwritenum;	/* ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤Ø¤Î²¿¿Í  ¤Ëwrite¤¹¤ë¤« */
	int				saacreadnum;	/* ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤«¤é¤Îdispatch ¤ò²¿²ó¤¹¤ë¤« */
  unsigned short fdnum;           /*¤É¤ì¤À¤±¥³¥Í¥¯¼³¥ç¥ó¤òÊÝ  ¤¹¤ë¤« */
  unsigned int   othercharnum;    /*  ¤½¤ÎÂ¾¤Î¥­¥ã¥é¤Î¿ô  */
  unsigned int objnum;            /* ¥ª¥Ö¥¸¥§¥¯¥È¤Î    ¿ô*/
  unsigned int   petcharnum;   	/* ¥Ú¥Ã¥È¤Î¿ô    */
  unsigned int itemnum;           /* ¥¢¥¤  ¥à¤Î    ¿ô*/
  unsigned int battlenum;         /* ¥Ð¥È¥ë¤Î    */
  unsigned int battleexp;         /* ¥Ð¥È¥ë¤Î    */
  char    topdir[32];         	/* ¥È¥Ã¥×¥Ç¥£¥ì¥¯¥È¥ê  */
  char    mapdir[32];         	/* ¥Þ¥Ã¥×¥Ç¥£¥ì¥¯¥È¥ê  */
  char    maptilefile[32];    	/* ¥Þ¥Ã¥×ÀßÄê¥Õ¥¡¥¤¥ë  */
  char    battlemapfile[32];    	/* ¥Ð¥È¥ë¥Þ¥Ã¥×ÀßÄê¥Õ¥¡¥¤¥ë  */
  char    itemfile[32];       	/* ¥¢¥¤  ¥àÀßÄê¥Õ¥¡¥¤¥ë  */
  char    invfile[32];        	/*   Å¨ÀßÄê¥Õ¥¡¥¤¥ë  */
  char    appearfile[32];     	/* ½Ð¸½°Ì  ÀßÄê¥Õ¥¡¥¤¥ë  */
	char	titlenamefile[32];		/* ¾Î¹æ¥Õ¥¡¥¤¥ë   */
	char	titleconfigfile[32];	/* ¾Î¹æÀßÄê¥Õ¥¡¥¤¥ë   */
	char	encountfile[32];		/* ¥¨¥ó¥«¥¦¥ó¥ÈÀßÄê¥Õ¥¡¥¤¥ë   */
	char	enemybasefile[32];		/* Å¨´ð  ÀßÄê¥Õ¥¡¥¤¥ë   */
	char	enemyfile[32];			/* Å¨ÀßÄê¥Õ¥¡¥¤¥ë   */
	char	groupfile[32];			/* ¥°¥ë¡¼¥×ÀßÄê¥Õ¥¡¥¤¥ë   */
	char	magicfile[32];			/* ¼ö½ÑÀßÄê¥Õ¥¡¥¤¥ë   */
#ifdef _ATTACK_MAGIC
  char    attmagicfile[32];       // §ðÀ»©Ê©G³N
#endif

	char	petskillfile[32];		/* ¥Ú¥Ã¥È  ¼ö½ÑÀßÄê¥Õ¥¡¥¤¥ë   */
  char    itematomfile[32];       /* ¥¢¥¤  ¥à¤Îºà    ¥Õ¥¡¥¤¥ë */
  char    effectfile[32];     	/* ±é½ÐÀßÄê¥Õ¥¡¥¤¥ë  */
  char    quizfile[32];     		/* ¥¯¥¤³NÀßÄê¥Õ¥¡¥¤¥ë  */
  char    lsgenlog[32];       /*¥µ¡¼¥Ð¤Îlsgen ¥¢¥¦¥È¥×¥Ã¥È¥Õ¥¡¥¤¥ë  */
  char    storedir[128];       /*¥¹¥È¥¢¥Ç¥£¥ì¥¯¥È¥ê    */
  char    npcdir[32];         /*NPC¤ÎÀßÄê¥Õ¥¡¥¤¥ë¤ò  ¤¯¥Ç¥£¥ì¥¯¥È¥ê   */
  char    logdir[32];         /*
                               * ¤Ò¥°¥Ç¥£¥ì¥¯¥È¥ê
                               */
  char    logconfname[32];    /*
                               * ¤Ò¥°ÀßÄê¥Õ¥¡¥¤¥ë  
                               */
  char	chatmagicpasswd[32];	/* ¥Á¥ã¥Ã¥È  Ë¡¥Ñ¥¹¥ï¡¼¥É */
#ifdef _STORECHAR
  char	storechar[32];
#endif
	unsigned int 	chatmagiccdkeycheck;	/* ¥Á¥ã¥Ã¥È  Ë¡¤ÇCDKEY¤ò¥Á¥§¥Ã¥¯¤¹¤ë¤« */
  unsigned int    filesearchnum;     /*¥Õ¥¡¥¤¥ë¤ò¸¡º÷¤Ç¤­¤ë¥Õ¥¡¥¤¥ë¤Î¿ô*/
  unsigned int    npctemplatenum;     /*NPC¤Î  ¥ó¥×¥ì¡¼¥È¥Õ¥¡¥¤¥ë¤Î¿ô*/
  unsigned int    npccreatenum;       /*NPC¤ÎÀ¸»º¥Õ¥¡¥¤¥ë¤Î¿ô*/
  unsigned int    walksendinterval;   /* ¬¤¤¯¤Î¤òÁ÷¤ë´Ö³Ö */
  unsigned int    CAsendinterval_ms;     /* CA¤òÁ÷¤ë´Ö³Ö (ms)*/
  unsigned int    CDsendinterval_ms;     /* CD¤òÁ÷¤ë´Ö³Ö (ms)*/
  unsigned int    Onelooptime_ms;     	/* 1¥ë¡¼¥×¤Ë¤«¤±¤ë»þ´Ö */
	unsigned int	Petdeletetime;		/* ¥Ú¥Ã¥È¤¬¾Ã  ¤¹¤ë»þ´Ö */
	unsigned int	Itemdeletetime;		/* ¥¢¥¤  ¥à¤¬¾Ã  ¤¹¤ë»þ´Ö */
    /* ¤Ò¥°¥¤¥ó  ¤Î¥­¥ã¥é¤Î¥»¡¼¥Ö¤ò¤¹¤ë´Ö³Ö */
  unsigned int    CharSavesendinterval;
  unsigned int    addressbookoffmsgnum;  /*
                                          * ¥¢¥É¥ì¥¹¥Ö¥Ã¥¯¤Ë¥ª¥Õ¥é¥¤¥ó
                                          * ¥á¥Ã¥»¡¼¥¸¤ò
                                          * ²¿¥á¥Ã¥»¡¼¥¸»Ä¤»¤ë¤«
                                          */
  unsigned int    protocolreadfrequency;  /*
                                           * ¥×¤Ò¥È¥³¥ë¤ò²¿¥ß¥ê    
                                           * ¤Ë  ¤à¤«
                                           */
  unsigned int    allowerrornum;          /*
                                           * ¥¨¥é¡¼¤ò²¿¸Ä¤Þ¤Çµö¤¹¤«
                                           */
  unsigned int    loghour;          		/*
                                           * ¤Ò¥°¤òÊÝÂ¸¤¹¤ë»þ¹ï  ¡ª»þ  
                                           */
  unsigned int    battledebugmsg;    		/*
                                           * ¥Ð¥È¥ë  ¤Î¥Ç¥Ð¥Ã¥°¥á¥Ã¥»¡¼¥¸¤ò½Ð¤¹¤«¡e£°¤Ê¤é½Ð¤µ¤Ê¤¤
                                           */
  //ttom add this because the second had this                                         
  unsigned int    encodekey;              
  unsigned int    acwbsize;             
  unsigned int    acwritesize;
  unsigned int    ErrUserDownFlg;
  //ttom end
#ifdef _GMRELOAD
	char	gmsetfile[32];				/* GM±b¸¹¡BÅv­­³]©wÀÉ */
#endif

#ifdef _PROFESSION_SKILL			// WON ADD ¤Hª«Â¾·~§Þ¯à
	char profession[32];
#endif
#ifdef _ITEM_QUITPARTY
    char itemquitparty[32];
#endif

#ifdef _DEL_DROP_GOLD	
	unsigned int	Golddeletetime;
#endif
#ifdef _Ip_Restrict //yang ADD ­­¨îIPµn¤J
	int	iprestrict;
#endif
#ifdef _Set_Born_Player //yang ADD ¦Û©w¸q¥X¥ÍÂà¼Æ+µ¥¯Å+ÂI¼Æ
	int	newplayerBornPoint;
	int	newplayertrans;
	int	newplayerlv;
#endif
#ifdef _ANGELOPEN //yang ADD ºëÆF¥l³ê§PÂ_¶}Ãö
	char AngelOpen;
#endif
#ifdef _Eggfeed //yang ADD ¦Û©w¸qÁý³J¦¸¼Æ
	int Eggfeed;
#endif
#ifdef _Proexp //yang ADD Â¾·~¸gÅç­¿²v
	int Proexp;
#endif
#ifdef _RideTransLimit   //yang ADD ­­¨îÃMÃd¤£±o¶W¹L¤@Âà
	int Ridets;
#endif
#ifdef _Compel_Store             //yang ADD ±j¦s¶}Ãö
	int CompelStore;
#endif
#ifdef _Pettranslimit            //yang ADD Ãdª«Âà¥Í¯à¤O­­¨î
	int Pettranslimit;
#endif
#ifdef _Join_Forbid  			//yang ADD ¸T¤î¥[¤J¹Î¶¤
	int joinforbidnum[10];
	char joinforbid[256];
#endif
#ifdef _Eventlock  		  	    //yang ADD ¥u¯à°µ¤@¦¸ªº¥ô°È
	int endeventnum[10];
	char endevent[256];
	int noweventnum[10];
	char nowevent[256];
#endif
#ifdef _NEW_PLAYER_CF
	int	newplayergivepet[5];
	int newplayergiveitem[15];
	int	newplayerpetlv;
	int newplayergivegold;
	int ridepetlevel;
#ifdef _VIP_SERVER
	int	newplayerpetvip;
#endif
#endif
#ifdef _USER_EXP_CF
	char	expfile[64];
#endif
#ifdef _UNLAW_WARP_FLOOR
	int	unlawwarpfloor[10];
#endif
#ifdef _WATCH_FLOOR
	int	watchfloor[6];
#endif
#ifdef _BATTLE_FLOOR
	int	battlefloor[6];
#endif
#ifdef _UNREG_NEMA
	char	unregname[5][16];
#endif
#ifdef _TRANS_LEVEL_CF
	int chartrans;
	int pettrans;
	int yblevel;
	int maxlevel;
#endif
#ifdef _POINT
	int point;
	int transpoint[8];
#endif
#ifdef _VIP_SERVER
	int vippoint;
#endif
#ifdef _PET_UP
	int petup;
#endif
#ifdef _LOOP_ANNOUNCE
	char loopannouncepath[32];
	int loopannouncetime;
	char loopannounce[10][1024];
	int loopannouncemax;
#endif
#ifdef _SKILLUPPOINT_CF
	int skup;
#endif
#ifdef _RIDELEVEL
	int ridelevel;
#endif
#ifdef _REVLEVEL
	int revlevel;
#endif
#ifdef _NEW_PLAYER_RIDE
	int npride;
#endif
#ifdef _FIX_CHARLOOPS
	int charloops;
#endif
#ifdef _PLAYER_ANNOUNCE
	int pannounce;
#endif
#ifdef _PLAYER_MOVE
	int pmove;
#endif
	int recvbuffer;
	int sendbuffer;
	int recvlowatbuffer;
	int runlevel;
#ifdef _SHOW_VIP_CF
	int showvip;
#endif
#ifdef _PLAYER_NUM
	int playernum;
#endif
#ifdef _BATTLE_GOLD
	int battlegold;
#endif
#ifdef _ANGEL_TIME
	int angelplayertime;
	int angelplayermun;
#endif
#ifdef _RIDEMODE_20
	int ridemode;
#endif
#ifdef _FM_POINT_PK
	int fmpointpk;
#endif
#ifdef _ENEMY_ACTION
	int	enemyact;
#endif
#ifdef _FUSIONBEIT_TRANS
	char	fusionbeittrans;
#endif
#ifdef _CHECK_PEPEAT
	int	CheckRepeat;
#endif
	int	cpuuse;

#ifdef _FM_JOINLIMIT
	int	joinfamilytime;
#endif
}Config;

Config config;

#ifdef _USER_EXP_CF
int NeedLevelUpTbls[200];
#endif

/*
 *  ¥³¥ó¥Õ¥£¥°¥Õ¥¡¥¤¥ë¤ò  ¤à»þ¤Ë»È¤¦¹½Â¤  
 *  xxxx=yyyy ¤ß¤¿¤¤¤Ê¤Î¤ò  ¤à
 */

typedef struct tagReadConf
{
    char    name[32];       /*xxxx¤Ë¤¢¤¿¤ëÃÍ*/

    /*±­¤Î2¤Ä¤ÏNULL¤ò  ¤ì¤ë¤È²¿¤â½è  ¤·¤Ê¤¤*/
    char  *charvalue;      /*yyyy¤ò¤½¤Î¤Þ¤ÞÂå  ¤¹¤ë»þ¤ÎÂå  Àè*/
    size_t  charsize;       /*charvalue¤Î¥µ¥¤³N*/

    /*
     *     »Å  ¤È¤·¤Æ=¤Î  ¤¬ "ON"¤À¤Ã¤¿¤é intvalue ¤Ë¤Ï1¤òÂå  ¤¹¤ë
     * ¤½¤ì°Ê³°¤Ï atoi ¤Î·ë²Ì
     */
    void*    value;       /*yyyy¤ò  ´¹¤¹¤ëÂå  ¤¹¤ë»þ¤ÎÂå  Àè*/
    CTYPE    valuetype;
}ReadConf;

ReadConf readconf[]=
{
    { "debuglevel"      , NULL ,0 , (void*)&config.debuglevel      ,CHAR},

    { "usememoryunit"   , NULL ,0 , (void*)&config.usememoryunit   ,INT},
    { "usememoryunitnum", NULL ,0 , (void*)&config.usememoryunitnum,INT},

    { "acserv",			config.asname,sizeof(config.asname) ,NULL , 0},
    { "acservport",		NULL ,0 , (void*)&config.acservport     ,SHORT},
    { "acpasswd",		config.acpasswd,sizeof( config.acpasswd),NULL,0},
    { "gameservname",	config.gsnamefromas,sizeof(config.gsnamefromas),
     NULL,0},

    // Arminius 7.24 manor pk
    { "gameservid", config.gsid, sizeof(config.gsid), NULL, 0}, 
    { "allowmanorpk", NULL, 0, (void*)&config.allowmanorpk, SHORT},

    { "port",			NULL ,0 , (void*)&config.port           ,SHORT},
    { "servernumber",	NULL ,0 , (void*)&config.servernumber           ,INT},

    { "reuseaddr",			NULL ,0 , (void*)&config.reuseaddr  ,		INT},
    { "nodelay",			NULL , 0 , (void*)&config.do_nodelay ,		INT},
    { "log_write_time", 	NULL, 0 , (void*)&config.log_write_time,	INT},
    { "log_io_time", 		NULL, 0 , (void*)&config.log_io_time, 		INT},
    { "log_game_time",		NULL, 0 , (void*)&config.log_game_time,		INT},
    { "log_netloop_faster", NULL,0,(void*)&config.log_netloop_faster,	INT},
    { "saacwritenum",		NULL,0,(void*)&config.saacwritenum, 		INT},
    { "saacreadnum",		NULL,0,(void*)&config.saacreadnum, 			INT},
    { "fdnum",				NULL ,0 , (void*)&config.fdnum,				SHORT},
    { "petnum",				NULL ,0 , (void*)&config.petcharnum,		INT},
    { "othercharnum",		NULL ,0 , (void*)&config.othercharnum,		INT},

    { "objnum",			NULL ,0 , (void*)&config.objnum,				INT},
    { "itemnum",		NULL ,0 , (void*)&config.itemnum,				INT},
    { "battlenum",		NULL ,0 , (void*)&config.battlenum,				INT},
    { "battleexp",		NULL ,0 , (void*)&config.battleexp,				INT},
    { "topdir"          , config.topdir,sizeof(config.topdir),NULL,0},
    { "mapdir"          , config.mapdir,sizeof(config.mapdir),NULL,0},
    { "maptilefile"     , config.maptilefile,sizeof(config.maptilefile),NULL,0},
    { "battlemapfile"   , config.battlemapfile,sizeof(config.battlemapfile),NULL,0},

#ifdef _ITEMSET6_TXT
	{ "itemset6file",	config.itemfile,	sizeof(config.invfile),	NULL,	0},
#else
#ifdef _ITEMSET5_TXT
	{ "itemset5file",	config.itemfile,	sizeof(config.invfile),	NULL,	0},
#else
#ifdef _ITEMSET4_TXT
	{ "itemset4file"  , config.itemfile,sizeof(config.invfile),NULL,0},
#else
#ifdef _ITEMSET3_ITEM
	{ "itemset3file"  , config.itemfile,sizeof(config.invfile),NULL,0},
#endif
#endif
#endif
#endif
  { "invinciblefile"  , config.invfile,sizeof(config.invfile),NULL,0},
  { "appearpositionfile"  , config.appearfile,sizeof(config.appearfile),NULL,0},
	{ "titlenamefile", config.titlenamefile, sizeof( config.titlenamefile),NULL,0},
	{ "titleconfigfile", config.titleconfigfile, sizeof( config.titleconfigfile),NULL,0},
	{ "encountfile", config.encountfile, sizeof( config.encountfile),NULL,0},
	{ "enemyfile", config.enemyfile, sizeof( config.enemyfile),NULL,0},
	{ "enemybasefile", config.enemybasefile, sizeof( config.enemybasefile),NULL,0},
	{ "groupfile", config.groupfile, sizeof( config.groupfile),NULL,0},
	{ "magicfile", config.magicfile, sizeof( config.magicfile),NULL,0},
#ifdef _ATTACK_MAGIC
	{ "attmagicfile" , config.attmagicfile , sizeof( config.attmagicfile )  , NULL , 0 },
#endif

#ifdef _PETSKILL2_TXT
	{ "petskillfile2", config.petskillfile, sizeof( config.petskillfile),NULL,0},
#else
	{ "petskillfile1", config.petskillfile, sizeof( config.petskillfile),NULL,0},
#endif

    { "itematomfile" , config.itematomfile, sizeof( config.itematomfile),NULL,0},
    { "effectfile"  , config.effectfile,sizeof(config.effectfile),NULL,0},
    { "quizfile"  , config.quizfile,sizeof(config.quizfile),NULL,0},

    { "lsgenlogfilename", config.lsgenlog,sizeof(config.lsgenlog),NULL,0},
#ifdef _GMRELOAD
	{ "gmsetfile", config.gmsetfile, sizeof( config.gmsetfile),NULL,0},
#endif

    { "storedir"        ,config.storedir,sizeof(config.storedir),NULL,0},
    { "npcdir"          ,config.npcdir,sizeof(config.npcdir),NULL,0},
    { "logdir"          ,config.logdir,sizeof(config.logdir),NULL,0},
    { "logconfname"     ,config.logconfname,sizeof(config.logconfname),NULL,0},
    { "chatmagicpasswd", config.chatmagicpasswd, sizeof( config.chatmagicpasswd),NULL,0},
#ifdef _STORECHAR
    { "storechar", config.storechar, sizeof( config.storechar),NULL,0},
#endif
    { "chatmagiccdkeycheck",  NULL,0, &config.chatmagiccdkeycheck,INT},
    { "filesearchnum",  NULL,0, &config.filesearchnum,INT},
    { "npctemplatenum",  NULL,0, &config.npctemplatenum,INT},
    { "npccreatenum",    NULL,0, &config.npccreatenum,INT},
    { "walkinterval" ,NULL,0,(void*)&config.walksendinterval,INT},
    { "CAinterval" ,NULL,0,(void*)&config.CAsendinterval_ms,INT},
    { "CDinterval" ,NULL,0,(void*)&config.CDsendinterval_ms,INT},
    { "CharSaveinterval" ,NULL,0,(void*)&config.CharSavesendinterval,INT},
    { "Onelooptime" ,NULL,0,(void*)&config.Onelooptime_ms,INT},
    { "Petdeletetime" ,NULL,0,(void*)&config.Petdeletetime,INT},
    { "Itemdeletetime" ,NULL,0,(void*)&config.Itemdeletetime,INT},
	 { "addressbookoffmesgnum" ,NULL,0,
      (void*)&config.addressbookoffmsgnum,INT},

    { "protocolreadfrequency" ,NULL,0,
      (void*)&config.protocolreadfrequency,INT},

    { "allowerrornum" ,NULL,0,(void*)&config.allowerrornum,INT},
    { "loghour" ,NULL,0,(void*)&config.loghour,INT},
    { "battledebugmsg" ,NULL,0,(void*)&config.battledebugmsg,INT},
    //ttom add because the second had
    { "encodekey" ,NULL,0,(void*)&config.encodekey,INT},
    { "acwritesize" ,NULL,0,(void*)&config.acwritesize,INT},
    { "acwbsize" ,NULL,0,(void*)&config.acwbsize,INT},
    { "erruser_down" ,NULL,0,(void*)&config.ErrUserDownFlg,INT},    

#ifdef _PROFESSION_SKILL			// WON ADD ¤Hª«Â¾·~§Þ¯à
    { "profession",		config.profession, sizeof(config.profession) ,NULL , 0},
#endif

#ifdef _ITEM_QUITPARTY
    { "itemquitparty",	config.itemquitparty, sizeof(config.itemquitparty) ,NULL , 0},
#endif

#ifdef _DEL_DROP_GOLD
	{ "Golddeletetime" ,NULL,0,(void*)&config.Golddeletetime,	INT},
#endif
#ifdef _Ip_Restrict //yang ADD ­­¨îIPµn¤J
	{ "iprestrict" ,NULL,0,(void*)&config.iprestrict,	INT},
#endif
#ifdef _Set_Born_Player          //yang ADD ¦Û©w¸q¥X¥ÍÂà¼Æ+µ¥¯Å+ÂI¼Æ
	{ "TRANS" ,NULL,0,(void*)&config.newplayertrans,	INT},
	{ "BornPoint" ,NULL,0,(void*)&config.newplayerBornPoint,	INT},
	{ "LV" ,NULL,0,(void*)&config.newplayerlv,	INT},	
#endif
#ifdef _ANGELOPEN    //yang ADD ºëÆF¥l³ê§PÂ_¶}Ãö
		{ "AngelOpen"      , NULL ,0 , (void*)&config.AngelOpen      ,CHAR},
#endif
#ifdef _Eggfeed //yang ADD ¦Û©w¸qÁý³J¦¸¼Æ
		{ "Eggfeed"      , NULL ,0 , (void*)&config.Eggfeed      ,INT},
#endif
#ifdef _Proexp //yang ADD Â¾·~¸gÅç­¿²v
		{ "Proexp"      , NULL ,0 , (void*)&config.Proexp      ,INT},
#endif
#ifdef _RideTransLimit   //yang ADD ­­¨îÃMÃd¤£±o¶W¹L¤@Âà
		{ "Ridets"      , NULL ,0 , (void*)&config.Ridets      ,INT},
#endif
#ifdef _Compel_Store             //yang ADD ±j¦s¶}Ãö
		{ "CompelStore"      , NULL ,0 , (void*)&config.CompelStore      ,INT},
#endif
#ifdef _Pettranslimit            //yang ADD Ãdª«Âà¥Í¯à¤O­­¨î
		{ "Pettranslimit"      , NULL ,0 , (void*)&config.Pettranslimit      ,INT},
#endif
#ifdef _Join_Forbid  			//yang ADD ¸T¤î¥[¤J¹Î¶¤
	{ "joinforbid" ,config.joinforbid, sizeof( config.joinforbid),NULL,0},
#endif
#ifdef _Eventlock  		  	    //yang ADD ¥u¯à°µ¤@¦¸ªº¥ô°È
	{ "endevent" ,config.endevent, sizeof( config.endevent),NULL,0},
	{ "nowevent" ,config.nowevent, sizeof( config.nowevent),NULL,0},
#endif
#ifdef _NEW_PLAYER_CF
	{ "PET0" ,NULL,0,(void*)&config.newplayergivepet[0],	INT},
	{ "PET1" ,NULL,0,(void*)&config.newplayergivepet[1],	INT},
	{ "PET2" ,NULL,0,(void*)&config.newplayergivepet[2],	INT},	
	{ "PET3" ,NULL,0,(void*)&config.newplayergivepet[3],	INT},	
	{ "PET4" ,NULL,0,(void*)&config.newplayergivepet[4],	INT},	
	{ "ITEM1" ,NULL,0,(void*)&config.newplayergiveitem[0],	INT},
	{ "ITEM2" ,NULL,0,(void*)&config.newplayergiveitem[1],	INT},	
	{ "ITEM3" ,NULL,0,(void*)&config.newplayergiveitem[2],	INT},	
	{ "ITEM4" ,NULL,0,(void*)&config.newplayergiveitem[3],	INT},	
	{ "ITEM5" ,NULL,0,(void*)&config.newplayergiveitem[4],	INT},
	{ "ITEM6" ,NULL,0,(void*)&config.newplayergiveitem[5],	INT},	
	{ "ITEM7" ,NULL,0,(void*)&config.newplayergiveitem[6],	INT},	
	{ "ITEM8" ,NULL,0,(void*)&config.newplayergiveitem[7],	INT},	
	{ "ITEM9" ,NULL,0,(void*)&config.newplayergiveitem[8],	INT},
	{ "ITEM10" ,NULL,0,(void*)&config.newplayergiveitem[9],	INT},	
	{ "ITEM11" ,NULL,0,(void*)&config.newplayergiveitem[10],	INT},	
	{ "ITEM12" ,NULL,0,(void*)&config.newplayergiveitem[11],	INT},	
	{ "ITEM13" ,NULL,0,(void*)&config.newplayergiveitem[12],	INT},	
	{ "ITEM14" ,NULL,0,(void*)&config.newplayergiveitem[13],	INT},	
	{ "ITEM15" ,NULL,0,(void*)&config.newplayergiveitem[14],	INT},
	{ "PETLV" ,NULL,0,(void*)&config.newplayerpetlv,	INT},	
	{ "GOLD" ,NULL,0,(void*)&config.newplayergivegold,	INT},
	{ "RIDEPETLEVEL" ,NULL,0,(void*)&config.ridepetlevel,	INT},
#ifdef _VIP_SERVER
	{ "GIVEVIPPOINT" ,NULL,0,(void*)&config.newplayerpetvip,	INT},
#endif
#endif

#ifdef _USER_EXP_CF
	{ "USEREXP", config.expfile, sizeof( config.expfile),NULL,0},
#endif

#ifdef _UNLAW_WARP_FLOOR
	{ "FLOOR1" ,NULL,0,(void*)&config.unlawwarpfloor[0],	INT},
	{ "FLOOR2" ,NULL,0,(void*)&config.unlawwarpfloor[1],	INT},	
	{ "FLOOR3" ,NULL,0,(void*)&config.unlawwarpfloor[2],	INT},	
	{ "FLOOR4" ,NULL,0,(void*)&config.unlawwarpfloor[3],	INT},	
	{ "FLOOR5" ,NULL,0,(void*)&config.unlawwarpfloor[4],	INT},
	{ "FLOOR6" ,NULL,0,(void*)&config.unlawwarpfloor[5],	INT},
	{ "FLOOR7" ,NULL,0,(void*)&config.unlawwarpfloor[6],	INT},	
	{ "FLOOR8" ,NULL,0,(void*)&config.unlawwarpfloor[7],	INT},	
	{ "FLOOR6" ,NULL,0,(void*)&config.unlawwarpfloor[8],	INT},	
	{ "FLOOR10" ,NULL,0,(void*)&config.unlawwarpfloor[9],	INT},
#endif

#ifdef _WATCH_FLOOR
	{ "WATCHFLOOR" ,NULL,0,(void*)&config.watchfloor[0],	INT},
	{ "WATCHFLOOR1" ,NULL,0,(void*)&config.watchfloor[1],	INT},
	{ "WATCHFLOOR2" ,NULL,0,(void*)&config.watchfloor[2],	INT},	
	{ "WATCHFLOOR3" ,NULL,0,(void*)&config.watchfloor[3],	INT},	
	{ "WATCHFLOOR4" ,NULL,0,(void*)&config.watchfloor[4],	INT},	
	{ "WATCHFLOOR5" ,NULL,0,(void*)&config.watchfloor[5],	INT},
#endif

#ifdef _BATTLE_FLOOR
	{ "BATTLEFLOOR" ,NULL,0,(void*)&config.battlefloor[0],	INT},
	{ "BATTLEFLOOR1" ,NULL,0,(void*)&config.battlefloor[1],	INT},
	{ "BATTLEFLOOR2" ,NULL,0,(void*)&config.battlefloor[2],	INT},	
	{ "BATTLEFLOOR3" ,NULL,0,(void*)&config.battlefloor[3],	INT},	
	{ "BATTLEFLOOR4" ,NULL,0,(void*)&config.battlefloor[4],	INT},	
	{ "BATTLEFLOOR5" ,NULL,0,(void*)&config.battlefloor[5],	INT},
#endif

#ifdef _UNREG_NEMA
	{ "NAME1" ,config.unregname[0], sizeof( config.unregname[0]),NULL,0},
	{ "NAME2" ,config.unregname[1], sizeof( config.unregname[1]),NULL,0},
	{ "NAME3" ,config.unregname[2], sizeof( config.unregname[2]),NULL,0},
	{ "NAME4" ,config.unregname[3], sizeof( config.unregname[3]),NULL,0},
	{ "NAME5" ,config.unregname[4], sizeof( config.unregname[4]),NULL,0},
#endif
#ifdef _TRANS_LEVEL_CF
	{ "CHARTRANS" ,NULL,0,(void*)&config.chartrans,	INT},
	{ "PETTRANS" ,NULL,0,(void*)&config.pettrans,	INT},	
	{ "LEVEL" ,NULL,0,(void*)&config.yblevel,	INT},	
	{ "MAXLEVEL" ,NULL,0,(void*)&config.maxlevel,	INT},	
#endif
#ifdef _POINT
	{ "POINT" ,NULL,0,(void*)&config.point,	INT},
	{ "TRANS0" ,NULL,0,(void*)&config.transpoint[0],	INT},	
	{ "TRANS1" ,NULL,0,(void*)&config.transpoint[1],	INT},	
	{ "TRANS2" ,NULL,0,(void*)&config.transpoint[2],	INT},	
	{ "TRANS3" ,NULL,0,(void*)&config.transpoint[3],	INT},	
	{ "TRANS4" ,NULL,0,(void*)&config.transpoint[4],	INT},	
	{ "TRANS5" ,NULL,0,(void*)&config.transpoint[5],	INT},	
	{ "TRANS6" ,NULL,0,(void*)&config.transpoint[6],	INT},	
	{ "TRANS7" ,NULL,0,(void*)&config.transpoint[7],	INT},	
#endif

#ifdef _PET_UP
	{ "PETUP" ,NULL,0,(void*)&config.petup,	INT},
#endif
#ifdef _LOOP_ANNOUNCE
	{ "ANNOUNCEPATH" ,config.loopannouncepath, sizeof( config.loopannouncepath),NULL,0},
	{ "ANNOUNCETIME" ,NULL,0,(void*)&config.loopannouncetime,	INT},
#endif
#ifdef _SKILLUPPOINT_CF
	{ "SKILLUPPOINT" ,NULL,0,(void*)&config.skup,	INT},	
#endif
#ifdef _RIDELEVEL
	{ "RIDELEVEL" ,NULL,0,(void*)&config.ridelevel,	INT},	
#endif

#ifdef _REVLEVEL
	{ "REVLEVEL" ,NULL,0,(void*)&config.revlevel,	INT},	
#endif
#ifdef _NEW_PLAYER_RIDE
	{ "NPRIDE" ,NULL,0,(void*)&config.npride,	INT},	
#endif
#ifdef _FIX_CHARLOOPS
	{ "CHARLOOPS" ,NULL,0,(void*)&config.charloops,	INT},	
#endif
#ifdef _PLAYER_ANNOUNCE
	{ "PANNOUNCE" ,NULL,0,(void*)&config.pannounce,	INT},
#endif
#ifdef _PLAYER_MOVE
	{ "PMOVE" ,NULL,0,(void*)&config.pmove,	INT},
#endif

	{ "recvbuffer" ,NULL,0,(void*)&config.recvbuffer,	INT},
	{ "sendbuffer" ,NULL,0,(void*)&config.sendbuffer,	INT},
	{ "recvlowatbuffer" ,NULL,0,(void*)&config.recvlowatbuffer,	INT},
	{ "runlevel" ,NULL,0,(void*)&config.runlevel,	INT},
	
#ifdef _SHOW_VIP_CF
	{ "SHOWVIP" ,NULL,0,(void*)&config.showvip,	INT},
#endif

#ifdef _PLAYER_NUM
	{ "PLAYERNUM" ,NULL,0,(void*)&config.playernum,	INT},
#endif

#ifdef _BATTLE_GOLD
	{ "BATTLEGOLD" ,NULL,0,(void*)&config.battlegold,	INT},
#endif
#ifdef _ANGEL_TIME
	{ "ANGELPLAYERTIME" ,NULL,0,(void*)&config.angelplayertime,	INT},
	{ "ANGELPLAYERMUN" ,NULL,0,(void*)&config.angelplayermun,	INT},
#endif
#ifdef _RIDEMODE_20
	{ "RIDEMODE" ,NULL,0,(void*)&config.ridemode,	INT},
#endif
#ifdef _FM_POINT_PK
	{ "FMPOINTPK" ,NULL,0,(void*)&config.fmpointpk,	INT},
#endif
#ifdef _ENEMY_ACTION
	{ "ENEMYACTION" ,NULL,0,(void*)&config.enemyact,	INT},
#endif
#ifdef _FUSIONBEIT_TRANS
	{ "FUSIONBEIT" ,NULL,0,(void*)&config.fusionbeittrans,	INT},
#endif
#ifdef _CHECK_PEPEAT
	{ "CHECKPEPEAT" ,NULL,0,(void*)&config.CheckRepeat,	INT},
#endif
	{ "CPUUSE" ,NULL,0,(void*)&config.cpuuse,	INT},

#ifdef _FM_JOINLIMIT
	{ "JOINFAMILYTIME" ,NULL,0,(void*)&config.joinfamilytime,	INT},
#endif
};

// Arminius 7.12 login announce
char announcetext[8192];
void AnnounceToPlayer(int charaindex)
{
  char *ptr,*qtr;
  
  ptr=announcetext;
  while ((qtr=strstr(ptr,"\n"))!=NULL) {
    qtr[0]='\0';
//    printf("ptr=%s\n",ptr);
    CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);
    qtr[0]='\n';
    ptr=qtr+1;
  }
  CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);
  
}

// Robin 0720
void AnnounceToPlayerWN(int fd)
{
	char buf[8192];
	lssproto_WN_send( fd , WINDOW_MESSAGETYPE_LOGINMESSAGE,
		WINDOW_BUTTONTYPE_OK,
		-1, -1,
		makeEscapeString( announcetext, buf, sizeof(buf))
		);
}


void LoadAnnounce(void)
{
    FILE *f;

    memset(announcetext, 0, sizeof(announcetext));
    if ((f=fopen("./announce.txt","r"))!=NULL) {
      fread(announcetext, sizeof(announcetext), 1, f);
      announcetext[sizeof(announcetext)-1]='\0';
      fclose(f);
    }
}
#ifdef _PET_TALKPRO
PTALK pettalktext[PETTALK_MAXID];

void LoadPetTalk(void)
{
	FILE *fp;
	char fn[256];
	char line[ 4096];
	char talkmem[4096];
	int maxid=0;
	char buf1[256], buf2[256], buf3[256];
	int talkNO=-1, mark=-1, i;
	int len = sizeof( talkmem);
	
	memset(talkmem, 0, sizeof(talkmem));
	sprintf(fn, "%s/pettalk/pettalk.menu", getNpcdir());

	for( i=0;i<PETTALK_MAXID;i++)	{
		pettalktext[i].ID = -1;
		strcpy( pettalktext[i].DATA, "\0");
	}

	print("\n¸Ë¸üÃdª«¹ï¸Ü¤å¥ó:%s...", fn);
	fp = fopen( fn, "r");
    if( fp != NULL ) {
		while( fgets( line, sizeof( line), fp)) {
			if( strlen( talkmem) != 0 ) {
				if( talkmem[strlen( talkmem) -1] != '|' ) {
					strcatsafe( talkmem, len, "|");		
				}
			}
			chompex( line);
			strcatsafe( talkmem,len,  line);
		}
		fclose( fp);
    }else	{
		print("¿ù»~:§ä¤£¨ì¤å¥ó!");
	}

	talkNO=1;
	while( getStringFromIndexWithDelim( talkmem,"END",talkNO, buf1, sizeof( buf1)) != FALSE	){
		talkNO++;
		if( NPC_Util_GetStrFromStrWithDelim( buf1, "PETTEMPNO", buf2, sizeof( buf2)) == NULL  )
			continue;
		mark=1;
		strcpy( fn,"\0");

		if( getStringFromIndexWithDelim( buf2,",", mark+1,buf3,sizeof( buf3)) != FALSE )	{
			pettalktext[maxid].ID = atoi( buf3);
			if( getStringFromIndexWithDelim( buf2,",", mark,buf3,sizeof( buf3)) != FALSE )	{
				sprintf(fn, "%s/pettalk/%s", getNpcdir(), buf3);
				//print("\n ...file:%s", fn);
				fp = fopen( fn, "r");
				if( fp != NULL )	{
					char line[4096];
					while( fgets( line, sizeof( line), fp ) ) {
						if( strlen( pettalktext[maxid].DATA) != 0 ) {
							if( pettalktext[maxid].DATA[strlen( pettalktext[maxid].DATA) -1] != '|' ) {
								strcatsafe( pettalktext[maxid].DATA, sizeof( pettalktext[maxid].DATA), "|");
							}
						}
						chompex( line);
						strcatsafe( pettalktext[maxid].DATA, sizeof( pettalktext[maxid].DATA), line);
					}
					maxid++;
					fclose( fp);
				}else	{
					print("¿ù»~:[%s] §ä¤£¨ì!", fn);
					pettalktext[maxid].ID=-1;
				}
			}else	{
				pettalktext[maxid].ID=-1;
			}
		}
		print(".");
		if( maxid >= PETTALK_MAXID )
			break;
	}
	print("³Ì¤jID=%d...", maxid);
	{
		int haveid=0;
		for( i=0;i<PETTALK_MAXID;i++)	{
			if( pettalktext[i].ID >= 0 )	{
				haveid++;
			}
		}
		print("¸ü¤JÁ`¼Æ=%d", haveid);
	}

}

#else
char pettalktext[4096];
void LoadPetTalk(void)
{
  FILE *fp;
  char fn[256];
  char	line[ 4096];
  int len = sizeof( pettalktext);
  
  memset(pettalktext, 0, sizeof(pettalktext));
  sprintf(fn, "%s/pettalk/pettalk.mem", getNpcdir());
  
  fp = fopen( fn, "r");
    if( fp != NULL ) {
		print("\n\n Åª¨ú pettalk.mem");
		while( fgets( line, sizeof( line), fp)) {
			if( strlen( pettalktext) != 0 ) {
				if( pettalktext[strlen( pettalktext) -1] != '|' ) {
					strcatsafe( pettalktext, len, "|");		
				}
			}
			chompex( line);
			strcatsafe( pettalktext,len,  line);
		}
		fclose( fp);
		print("\n %s", pettalktext);
    }else	{
		print("\n ¤£¯à§ä¨ì pettalk.mem");
	}
}
#endif

#ifdef _GAMBLE_BANK
GAMBLEBANK_ITEMS GB_ITEMS[GAMBLEBANK_ITEMSMAX];

void Load_GambleBankItems( void)
{

	FILE *fp;
	char filename[256];
	char buf1[256];
	char name[128];
	int num,ID,type;
	int i=0;
	sprintf(filename, "./data/gambleitems.txt" );
	print("\n¥[¸ü½ä³Õª««~¤å¥ó %s ...", filename);
	fp = fopen( filename, "r");
    if( fp != NULL ) {
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			if( strstr( buf1, "#") != 0 ) continue;
			sscanf( buf1,"%s %d %d %d", name, &ID, &num , &type);
			strcpy( GB_ITEMS[i].name, name);
			GB_ITEMS[i].Gnum = num;
			GB_ITEMS[i].ItemId = ID;
			GB_ITEMS[i].type = type;
			i++;
		}
		print("³Ì¤jID: %d ", i);
		fclose( fp);
    }else	{
		print("¿ù»~ §ä¤£¨ì¤å¥ó %s", filename);
	}

}
#endif


#ifdef _CFREE_petskill
PETSKILL_CODES Code_skill[PETSKILL_CODE];
void Load_PetSkillCodes( void)
{
	FILE *fp;
	char filename[256];
	char buf1[256];
	char name[128];
	char type[256];
	int num,ID;
	int i=0;
	sprintf(filename, "./data/skillcode.txt" );
	print("\n¥[¸üÃdª«§Þ¯à½s½X¤å¥ó:%s...", filename);
	fp = fopen( filename, "r");
    if( fp != NULL ) {
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			sscanf( buf1,"%s %d %d %s", name, &num, &ID, type);
			strcpy( Code_skill[i].name, name);
			Code_skill[i].TempNo = num;
			Code_skill[i].PetId = ID;
			strcpy( Code_skill[i].Code, type);
			//print("\n %s|%d|%d|%s|", Code_skill[i].name, Code_skill[i].TempNo, 
			//	Code_skill[i].PetId, Code_skill[i].Code);
			i++;
			if( i >= PETSKILL_CODE ) break;
		}
		fclose( fp);
    }else	{
		print("¥´¤£¨ì¤å¥ó %s", filename);
	}
	print("§¹¦¨\n");
}
#endif
#ifdef _Join_Forbid  			//yang ADD ¸T¤î¥[¤J¹Î¶¤
void LoadJoinForbid(void)
{
	char tmpjoinforbidnum[12];
	int i;
	for( i = 0; i < 10; i ++ ){
	getStringFromIndexWithDelim( config.joinforbid, ",", i+1, tmpjoinforbidnum, sizeof(tmpjoinforbidnum));
	config.joinforbidnum[i] = atoi(tmpjoinforbidnum);
	}
}
#endif
#ifdef _Eventlock  		  	    //yang ADD ¥u¯à°µ¤@¦¸ªº¥ô°È
void LoadEventlock(void)
{
	char temp[12];
	int i;
	for( i = 0; i < 10; i ++ ){ //Åª¨ú¤w§¹¦¨¥ô°È
	getStringFromIndexWithDelim( config.endevent, ",", i+1, temp, sizeof(temp));
	config.endeventnum[i] = atoi(temp);
	}
	for( i = 0; i < 10; i ++ ){ //Åª¨ú¶i¦æ¤¤¥ô°È
	getStringFromIndexWithDelim( config.nowevent, ",", i+1, temp, sizeof(temp));
	config.noweventnum[i] = atoi(temp);
	}
}
#endif
#ifdef _GMRELOAD
BOOL LoadGMSet( char* filename )
{
	FILE* fp;
	int i = 0, gm_num = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		print("µLªk¥´¶}¤å¥ó\n");
		return FALSE;
	}
	for (i = 0; i < GMMAXNUM; i++)
	{
		strcpy(gminfo[i].cdkey, "");
		gminfo[i].level = 0;
	}
	while(1){
		char	line[64], cdkey[64], level[64];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		chop(line);
		//change ¨Ïgmset.txt¥i¥H¼W¥[µù¸Ñ*******
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************
		gm_num = gm_num + 1;
		if (gm_num > GMMAXNUM)	break;
		easyGetTokenFromString(line, 1, cdkey, sizeof(cdkey));
		if (strcmp(cdkey, "") == 0)	break;
		strncpy(gminfo[gm_num].cdkey, cdkey, sizeof(gminfo[gm_num].cdkey));
		easyGetTokenFromString(line, 2, level, sizeof(level));
		if (strcmp(level, "") == 0)	break;
		gminfo[gm_num].level = atoi(level);
//		print("\ncdkey:%s, level:%d", gminfo[gm_num].cdkey, gminfo[gm_num].level);
	}
	fclose(fp);
	return TRUE;
}
#endif

/*------------------------------------------------------------
 * ¥×¤Ò¥°¥é¥à  ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  cahr*
 ------------------------------------------------------------*/
char* getProgname( void )
{
    return config.progname;
}
/*------------------------------------------------------------
 * configfilename ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getConfigfilename( void )
{
    return config.configfilename;
}
/*------------------------------------------------------------
 * configfilename ¤òÀßÄê¤¹¤ë¡e
 * °ú¿ô
 *  newv    char*   ¿·¤·¤¤ÃÍ
 * ÊÖ¤êÃÍ
 *  ¤Ê¤·
 ------------------------------------------------------------*/
void setConfigfilename( char* newv )
{
    strcpysafe( config.configfilename, sizeof( config.configfilename ),
                newv );
}

/*------------------------------------------------------------
 * ¥Ç¥Ð¥Ã¥°¥ì¥Ù¥ë¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getDebuglevel( void )
{
    return config.debuglevel;
}
/*------------------------------------------------------------
 * ¥Ç¥Ð¥Ã¥°¥ì¥Ù¥ë¤òÀßÄê¤¹¤ë
 * °ú¿ô
 *  newv    int     ¿·¤·¤¤ÃÍ
 * ÊÖ¤êÃÍ
 *  unsigned int    ÀÎ¤ÎÃÍ
 ------------------------------------------------------------*/
unsigned int setDebuglevel( unsigned int newv )
{
    int old;
    old = config.debuglevel;
    config.debuglevel = newv;
    return old;
}
/*------------------------------------------------------------
 * memoryunit ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getMemoryunit( void )
{
    return config.usememoryunit;
}
/*------------------------------------------------------------
 * memoryunitnum ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getMemoryunitnum( void )
{
    return config.usememoryunitnum;
}

/*------------------------------------------------------------
 * ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤Î¥¢¥É¥ì¥¹¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char*   getAccountservername( void )
{
    return config.asname;
}
/*------------------------------------------------------------
 * ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤Î¥Ý¡¼¥È¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned short
 ------------------------------------------------------------*/
unsigned short   getAccountserverport( void )
{
    return config.acservport;
}
/*------------------------------------------------------------
 * ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤Ø¤Î¥Ñ¥¹¥ï¡¼¥É¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned short
 ------------------------------------------------------------*/
char*   getAccountserverpasswd( void )
{
    return config.acpasswd;
}
/*------------------------------------------------------------
 * ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¤«¤é¸«¤¨¤ë¥²¡¼¥à¥µ¡¼¥Ð¤È¤·¤Æ¤Î  Á°¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned short
 ------------------------------------------------------------*/
char*   getGameservername( void )
{
    return config.gsnamefromas;
}

// Arminius 7.24 manor pk
char* getGameserverID( void )
{
    if (config.gsid[strlen(config.gsid)-1]=='\n')
      config.gsid[strlen(config.gsid)-1]='\0';
      
    return config.gsid;
}

unsigned short getAllowManorPK( void )
{
    return config.allowmanorpk;
}

unsigned short getPortnumber( void )
{
    return config.port;
}
/*------------------------------------------------------------
 * ¥²¡¼¥à¥µ¡¼¥Ð¤Î  ¹æ   ¹æ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned short
 ------------------------------------------------------------*/
int getServernumber( void )
{
    return config.servernumber;
}
/*------------------------------------------------------------
 * reuseaddr ¤ÎÃÍ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned short
 ------------------------------------------------------------*/
int getReuseaddr( void )
{
    return config.reuseaddr;
}

int getNodelay( void )
{
    return config.do_nodelay;
}
int getLogWriteTime(void)
{
    return config.log_write_time;
}
int getLogIOTime( void)
{
    return config.log_io_time;
}
int getLogGameTime(void)
{
    return config.log_game_time;
}
int getLogNetloopFaster(void)
{
    return config.log_netloop_faster;
}

/*------------------------------------------------------------
 * saacwritenum ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *   int
 ------------------------------------------------------------*/
int getSaacwritenum( void )
{
    return config.saacwritenum;
}
/*------------------------------------------------------------
 * saacwritenum ¤òÀßÄê¤¹¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *   int
 ------------------------------------------------------------*/
void setSaacwritenum( int num )
{
    config.saacwritenum = num;
}
/*------------------------------------------------------------
 * saacreadnum ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *   int
 ------------------------------------------------------------*/
int getSaacreadnum( void )
{
    return config.saacreadnum;
}
/*------------------------------------------------------------
 * saacreadnum ¤òÀßÄê¤¹¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *   int
 ------------------------------------------------------------*/
void setSaacreadnum( int num )
{
    config.saacreadnum = num;
}
/*------------------------------------------------------------
 * fdnum ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getFdnum( void )
{
    return config.fdnum;
}
/*------------------------------------------------------------
 * petcharanum ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getPetcharnum( void )
{
    return config.petcharnum;
}


/*------------------------------------------------------------
 * othercharnum ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getOtherscharnum( void )
{
    return config.othercharnum;
}

/*------------------------------------------------------------
 * objnum ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getObjnum( void )
{
    return config.objnum;
}

/*------------------------------------------------------------
 * itemnum ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getItemnum( void )
{
    return config.itemnum;
}


/*------------------------------------------------------------
 * battlenum ¤ò  ¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getBattlenum( void )
{
    return config.battlenum;
}

#ifdef _GET_BATTLE_EXP
unsigned int getBattleexp( void )
{
    return config.battleexp;
}
#endif
/*------------------------------------------------------------
 * topdir ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getTopdir( void )
{
    return config.topdir;
}
/*------------------------------------------------------------
 * mapdir ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getMapdir( void )
{
    return config.mapdir;
}
/*------------------------------------------------------------
 * maptilefile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getMaptilefile( void )
{
    return config.maptilefile;
}
/*------------------------------------------------------------
 * battlemapfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getBattleMapfile( void )
{
    return config.battlemapfile;
}
/*------------------------------------------------------------
 * itemfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getItemfile( void )
{
    return config.itemfile;
}
/*------------------------------------------------------------
 * invfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getInvfile( void )
{
    return config.invfile;
}
/*------------------------------------------------------------
 * appearfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getAppearfile( void )
{
    return config.appearfile;
}
/*------------------------------------------------------------
 * effectfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getEffectfile( void )
{
    return config.effectfile;
}
/*------------------------------------------------------------
 * titlenamefile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getTitleNamefile( void )
{
    return config.titlenamefile;
}
/*------------------------------------------------------------
 * titleconfigfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getTitleConfigfile( void )
{
    return config.titleconfigfile;
}
/*------------------------------------------------------------
 * encountfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getEncountfile( void )
{
    return config.encountfile;
}
/*------------------------------------------------------------
 * enemyfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getEnemyfile( void )
{
    return config.enemyfile;
}
/*------------------------------------------------------------
 * enemybasefile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getEnemyBasefile( void )
{
    return config.enemybasefile;
}
/*------------------------------------------------------------
 * groupfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getGroupfile( void )
{
    return config.groupfile;
}
/*------------------------------------------------------------
 * magicfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getMagicfile( void )
{
    return config.magicfile;
}

#ifdef _ATTACK_MAGIC

/*------------------------------------------------------------
 * ¨ú±o§ðÀ»©Êªº©G³N
 * °Ñ¼Æ
 * None
 * ªð¦^­È
 * char*
 ------------------------------------------------------------*/
char* getAttMagicfileName( void )
{
    return config.attmagicfile;
}

#endif


char* getPetskillfile( void )
{
    return config.petskillfile;
}

#ifdef _PROFESSION_SKILL			// WON ADD ¤Hª«Â¾·~§Þ¯à
char* getProfession( void )
{
    return config.profession;
}
#endif

#ifdef _ITEM_QUITPARTY
char* getitemquitparty( void )
{
    return config.itemquitparty;
}
#endif

char *getItematomfile( void )
{
    return config.itematomfile;
}


char* getQuizfile( void )
{
    return config.quizfile;
}

/*------------------------------------------------------------
 * lsgenlogfile ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getLsgenlogfilename( void )
{
    return config.lsgenlog;
}

#ifdef _GMRELOAD
char* getGMSetfile( void )
{
    return config.gmsetfile;
}
#endif

/*------------------------------------------------------------
 * storedir ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getStoredir( void )
{
    return config.storedir;
}
#ifdef _STORECHAR
/*------------------------------------------------------------
 ------------------------------------------------------------*/
char* getStorechar( void )
{
    return config.storechar;
}
#endif

/*------------------------------------------------------------
 * NPC ÍÑ¤Î¥Ç¥£¥ì¥¯¥È¥ê¤ò  ¤Æ¤¯¤ë´Ø¿ô
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getNpcdir( void )
{
    return config.npcdir;
}
/*------------------------------------------------------------
 * ¤Ò¥°¥Ç¥£¥ì¥¯¥È¥ê¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getLogdir( void )
{
    return config.logdir;
}

/*------------------------------------------------------------
 * ¤Ò¥°ÀßÄê¥Õ¥¡¥¤¥ë  ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getLogconffile( void )
{
    return config.logconfname;
}
/*------------------------------------------------------------
 * ¥Á¥ã¥Ã¥È  Ë¡¥Ñ¥¹¥ï¡¼¥É ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
char* getChatMagicPasswd( void )
{
    return config.chatmagicpasswd;
}
/*------------------------------------------------------------
 * ¥Ç¥Ð¥Ã¥°¥Á¥ã¥Ã¥È  Ë¡¤Ç¤ÎCDKEY¥Á¥§¥Ã¥¯¤ò¤¹¤ë¤«¤É¤¦¤«¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  char*
 ------------------------------------------------------------*/
unsigned getChatMagicCDKeyCheck( void )
{
    return config.chatmagiccdkeycheck;
}

/*------------------------------------------------------------
 * filesearchnum¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getFilesearchnum( void )
{
    return config.filesearchnum;
}
/*------------------------------------------------------------
 * npctemplatenum¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getNpctemplatenum( void )
{
    return config.npctemplatenum;
}
/*------------------------------------------------------------
 * npccreatenum¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getNpccreatenum( void )
{
    return config.npccreatenum;
}

/*------------------------------------------------------------
 * walksendinterval¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getWalksendinterval( void )
{
    return config.walksendinterval;
}
/*------------------------------------------------------------
 * walksendinterval¤ò¥»¥Ã¥È¤¹¤ë¡e
 * °ú¿ô
 *  unsigned int 	interval	»þ´Ö  ¥ß¥ê    
 * ÊÖ¤êÃÍ
 *  void
 ------------------------------------------------------------*/
void setWalksendinterval( unsigned int interval )
{
    config.walksendinterval = interval;
}
/*------------------------------------------------------------
 * CAsendinterval¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getCAsendinterval_ms( void )
{
    return config.CAsendinterval_ms;
}
/*------------------------------------------------------------
 * CAsendinterval¤ò¥»¥Ã¥È¤¹¤ë¡e
 * °ú¿ô
 *  unsigned int interval
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
void setCAsendinterval_ms( unsigned int interval_ms )
{
    config.CAsendinterval_ms = interval_ms;
}
/*------------------------------------------------------------
 * CDsendinterval¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getCDsendinterval_ms( void )
{
    return config.CDsendinterval_ms;
}
/*------------------------------------------------------------
 * CDsendinterval¤ò¥»¥Ã¥È¤¹¤ë¡e
 * °ú¿ô
 *  interval		unsigned int
 * ÊÖ¤êÃÍ
 * void
 ------------------------------------------------------------*/
void setCDsendinterval_ms( unsigned int interval_ms )
{
	config.CDsendinterval_ms = interval_ms;
}
/*------------------------------------------------------------
 * Onelooptime¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getOnelooptime_ms( void )
{
    return config.Onelooptime_ms;
}
/*------------------------------------------------------------
 * Onelooptime¤ò¥»¥Ã¥È¤¹¤ë¡e
 * °ú¿ô
 *  interval		unsigned int
 * ÊÖ¤êÃÍ
 * void
 ------------------------------------------------------------*/
void setOnelooptime_ms( unsigned int interval_ms )
{
	config.Onelooptime_ms = interval_ms;
}
/*------------------------------------------------------------
 * Petdeletetime¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getPetdeletetime( void )
{
    return config.Petdeletetime;
}
/*------------------------------------------------------------
 * Petdeletetime¤ò¥»¥Ã¥È¤¹¤ë¡e
 * °ú¿ô
 *  interval		unsigned int
 * ÊÖ¤êÃÍ
 * void
 ------------------------------------------------------------*/
void setPetdeletetime( unsigned int interval )
{
	config.Petdeletetime = interval;
}
/*------------------------------------------------------------
 * Itemdeletetime¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getItemdeletetime( void )
{
    return config.Itemdeletetime;
}
/*------------------------------------------------------------
 * Itemdeletetime¤ò¥»¥Ã¥È¤¹¤ë¡e
 * °ú¿ô
 *  interval		unsigned int
 * ÊÖ¤êÃÍ
 * void
 ------------------------------------------------------------*/
void setItemdeletetime( unsigned int interval )
{
	config.Itemdeletetime = interval;
}

/*------------------------------------------------------------
 * CharSavesendinterval¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getCharSavesendinterval( void )
{
    return config.CharSavesendinterval;
}
/*------------------------------------------------------------
 * CharSavesendinterval¤ò¥»¥Ã¥È¤¹¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
void setCharSavesendinterval( unsigned int interval)
{
	config.CharSavesendinterval = interval;
}

/*------------------------------------------------------------
 * Addressbookoffmsgnum ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getAddressbookoffmsgnum( void )
{
    return config.addressbookoffmsgnum;
}
/*------------------------------------------------------------
 * Protocolreadfrequency ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getProtocolreadfrequency( void )
{
    return config.protocolreadfrequency;
}

/*------------------------------------------------------------
 * Allowerrornum ¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getAllowerrornum( void )
{
    return config.allowerrornum;
}

/*------------------------------------------------------------
 * ¤Ò¥°¤ò¼è  ¤¹¤ë»þ¹ï¤ò  ¤ë¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getLogHour( void )
{
    return config.loghour;
}

/*------------------------------------------------------------
 * ¥Ð¥È¥ë  ¤Î¥Ç¥Ð¥Ã¥°¥á¥Ã¥»¡¼¥¸¤ò½Ð¤¹¤«¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int 1¤Ê¤é½Ð¤¹
 ------------------------------------------------------------*/
unsigned int getBattleDebugMsg( void )
{
    return config.battledebugmsg;
}
/*------------------------------------------------------------
 * ¥Ð¥È¥ë  ¤Î¥Ç¥Ð¥Ã¥°¥á¥Ã¥»¡¼¥¸¤ò½Ð¤¹¤«¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int 1¤Ê¤é½Ð¤¹
 ------------------------------------------------------------*/
void setBattleDebugMsg( unsigned int num )
{
    config.battledebugmsg = num;
}



/*
 * Config¤Î¥Ç¥Õ¥©¥ë¥ÈÃÍ¤ò·è¤á¤ë´Ø¿ô
 * °ú¿ô
 *  argv0   char*   ¥³¥Þ¥ó¥É¥é¥¤¥ó°ú¿ô¤Î  ½é
 */
void  defaultConfig( char* argv0 )
{
    char* program;                  /* program  ¤òµá¤á¤ë¤Î¤Ë»È¤¦ */

    /* ¥Ç¥Õ¥©¥ë¥ÈÃÍ¤ò  ¤ì¤ë */

    /*¥×¤Ò¥°¥é¥à  */
    program = rindex(argv0, '/');
    if (program == NULL)
        program = argv0;
    else
        program++;   /* "/"¤Î±­¤«¤é¤Ë¤·¤¿¤¤¤Î¤Ç++¤¹¤ë*/
    strcpysafe( config.progname , sizeof( config.progname ) ,program );

    /*ÀßÄê¥Õ¥¡¥¤¥ë  */
    strcpysafe( config.configfilename,
                sizeof( config.configfilename ),"setup.cf" );

}

/*
 * ÀßÄê¥Õ¥¡¥¤¥ë  ¤ò  ¤ó¤À  ¤Ç¤Î½è  ¤ò¹Ô¤¦¡e
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  ¤Ê¤·
 */
void lastConfig( void )
{
    char    entry[256];
    /*  ¥Þ¥Ã¥×¥Ç¥£¥ì¥¯¥È¥ê¤ÎÀßÄê    */
    snprintf(entry, sizeof(entry), "%s/%s", config.topdir, config.mapdir);
    strcpysafe(config.mapdir, sizeof(config.mapdir), entry);

    /*  ¥Þ¥Ã¥×ÀßÄê¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry),"%s/%s",
             config.topdir,config.maptilefile);
    strcpysafe(config.maptilefile, sizeof(config.maptilefile), entry);

    /*  ¥Ð¥È¥ë¥Þ¥Ã¥×ÀßÄê¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry),"%s/%s",
             config.topdir,config.battlemapfile);
    strcpysafe(config.battlemapfile, sizeof(config.battlemapfile), entry);

    /*  ¥¢¥¤  ¥àÀßÄê¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.itemfile);
    strcpysafe(config.itemfile, sizeof(config.itemfile), entry);

    /*    Å¨ÀßÄê¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.invfile);
    strcpysafe(config.invfile, sizeof(config.invfile), entry);

    /*  ½Ð¸½°Ì  ÀßÄê¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.appearfile);
    strcpysafe(config.appearfile, sizeof(config.appearfile), entry);

    /*  ±é½ÐÀßÄê¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.effectfile);
    strcpysafe(config.effectfile, sizeof(config.effectfile), entry);

    /*  ¥¯¥¤³NÀßÄê¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.quizfile);
    strcpysafe(config.quizfile, sizeof(config.quizfile), entry);

    /*  ¾Î¹æ  ¥Õ¥¡¥¤¥ë  ¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.titlenamefile);
    strcpysafe(config.titlenamefile, sizeof(config.titlenamefile), entry);

    /*  lsgen ¥¢¥¦¥È¥×¥Ã¥È¥Õ¥¡¥¤¥ë      */
    snprintf(entry,sizeof(entry),"%s/%s", config.topdir,config.lsgenlog);
    strcpysafe(config.lsgenlog, sizeof(config.lsgenlog), entry);

    /*  ¥¹¥È¥¢¥Ç¥£¥ì¥¯¥È¥ê¤ÎÀßÄê    */
/*
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.storedir);
    strcpysafe(config.storedir, sizeof(config.storedir), entry);
*/
    /*  NPCÀßÄê¥È¥Ã¥×¥Ç¥£¥ì¥¯¥È¥ê¤ÎÀßÄê    */
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.npcdir);
    strcpysafe(config.npcdir, sizeof(config.npcdir), entry);

#ifdef _STORECHAR
    /*   */
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.storechar);
    strcpysafe(config.storechar, sizeof(config.storechar), entry);
#endif

}


/*
 * ¥Ý¥¤¥ó¥¿¡¼¤ÈÅ¬ÀÚ¤Ê·¿¾ð  ¤ò  ¤Ã¤ÆÂå  ¤ò¤¹¤ë´Ø¿ô
 * °ú¿ô
 *  to      void*   ÃÍ¤òÂå  ¤¹¤ë¥Ý¥¤¥ó¥¿
 *  type    CTYPE   to¤Î·¿¤ò·è¤á¤ë
 *  value   double  to¤ËÂå  ¤¹¤ëÃÍ
 * ÊÖ¤êÃÍ
 *  ¤Ê¤·
 */
void substitutePointerFromType( void* to , CTYPE type ,double value)
{
    switch( type  ){
    case CHAR:
        *(char*)to = (char)value;
        break;
    case SHORT:
        *(short*)to = (short)value;
        break;
    case INT:
        *(int*)to = (int)value;
        break;
    case DOUBLE:
        *(double*)to = (double)value;
        break;
    }
}


/*------------------------------------------------------------
 * ÀßÄê¥Õ¥¡¥¤¥ë¤ò  ¤à
 * °ú¿ô
 *      filename            ¥Õ¥¡¥¤¥ë  
 * ÊÖ¤êÃÍ
 *      TRUE(1)     ©¨  
 *      FALSE(0)    ¼º      -> ¥Õ¥¡¥¤¥ë¤Î¥ª¡¼¥×¥ó¤Ë¼º  ¤·¤¿
 ------------------------------------------------------------*/
BOOL readconfigfile( char* filename )
{
    FILE* f=NULL;
    char linebuf[256];                  /* °ì¹Ô  ¤ß  ¤à¥Ð¥Ã¥Õ¥¡ */
    int linenum=0;                      /* ¹Ô¿ô¤ò¿ô¤¨¤ë */
    char    realopenfilename[256];      /*    ºÝ¤Ëopen ¤¹¤ë¥Õ¥¡¥¤¥ë  */

    char    hostname[128];

    /*  ¥Û¥¹¥È  ¤òµá¤á¤ë    */
    if( gethostname( hostname, sizeof(hostname) ) != -1 ){
        char*   initdot;
        initdot = index( hostname, '.' );
        if( initdot != NULL )
            *initdot = '\0';
        snprintf( realopenfilename, sizeof(realopenfilename),
                  "%s.%s" , filename, hostname);

        /* ¥Õ¥¡¥¤¥ë¤Î¥ª¡¼¥×¥ó */
        f=fopen( realopenfilename, "r" );
        if( f == NULL )
            print( "Can't open %s.  use %s instead\n", realopenfilename,
                   filename );
    }
    if( f == NULL ){
        f=fopen( filename , "r" );          /* ¥Õ¥¡¥¤¥ë¤Î¥ª¡¼¥×¥ó */
        if( f == NULL ){
            print( "Can't open %s\n", filename );
            return FALSE;
        }
    }

    /* °ì¹Ô¤Å¤Ä  ¤ß  ¤à */
    while( fgets( linebuf , sizeof( linebuf ), f ) ){
        char firstToken[256];       /*1    ¤Î  »ú  */
        int i;                      /*¥ë¡¼¥×  ¿ô*/
        int ret;                    /*¥ê¥¿¡¼¥ó¥³¡¼¥É*/

        linenum ++;

        deleteWhiteSpace(linebuf);          /* remove whitespace    */

        if( linebuf[0] == '#' )continue;        /* comment */
        if( linebuf[0] == '\n' )continue;       /* none    */

        chomp( linebuf );                    /* remove tail newline  */

        /* delim "=" ¤Ç  ½é(1)¤Î¥È¡¼¥¯¥ó¤ò  ¤ë*/
        ret = getStringFromIndexWithDelim( linebuf , "=",  1, firstToken,
                                           sizeof(firstToken) );
        if( ret == FALSE ){
            print( "Find error at %s in line %d. Ignore\n",
                     filename , linenum);
            continue;
        }

        /* readconf ¤Î¥µ¥¤³N¤Ç¥ë¡¼¥× */
        for( i = 0 ; i < arraysizeof( readconf ) ; i ++ ){
            if( strcmp( readconf[i].name ,firstToken ) == 0 ){
                /* match */
                char secondToken[256];      /*2    ¤Î  »ú  */
                /* delim "=" ¤Ç2    ¤Î¥È¡¼¥¯¥ó¤ò  ¤ë*/
                ret = getStringFromIndexWithDelim( linebuf , "=" , 2
                                                   , secondToken ,
                                                   sizeof(secondToken) );

                /* NULL  »ú¤«¤É¤¦¤«¤òÄ´¤Ù¤ë */
                if( ret == FALSE ){
                    print( "Find error at %s in line %d. Ignore",
                           filename , linenum);
                    break;
                }


                /*NULL¤À¤Ã¤¿¤éÂå  ¤·¤Ê¤¤*/
                if( readconf[i].charvalue != NULL )
                    strcpysafe( readconf[i].charvalue
                                ,readconf[i].charsize, secondToken);

                /*NULL¤À¤Ã¤¿¤éÂå  ¤·¤Ê¤¤*/
                if( readconf[i].value != NULL ) {
                    if( strcmp( "ON" ,secondToken ) == 0 ) {
                        /*ON¤À¤Ã¤¿¤é1¤ò  ¤ì¤ë*/
                        substitutePointerFromType( readconf[i].value,
                                                   readconf[i].valuetype,
                                                   1.0);

                    }else if( strcmp( "OFF" ,secondToken ) == 0 ) {
                        /*OFF¤À¤Ã¤¿¤é1¤ò  ¤ì¤ë*/
                        substitutePointerFromType( readconf[i].value,
                                                   readconf[i].valuetype,
                                                   1.0);
                    }else {
                        strtolchecknum(secondToken,
                                       (int*)readconf[i].value,
                                       10, readconf[i].valuetype);
					}
				}
                break;
            }
        }
    }
    fclose( f );
    lastConfig();
    return TRUE;
}
//ttom add this becaus the second had this function 
/*------------------------------------------------------------
 * ¥¨¥ó¥³¡¼¥É¥­¡¼¤òÀßÄê¤¹¤ë
 * °ú¿ô
 *  ¤Ê¤·
 * ÊÖ¤êÃÍ
 *  unsigned int ¥­¡¼¤òÊÖ¤¹
------------------------------------------------------------*/
unsigned int setEncodeKey( void )
{
   JENCODE_KEY = config.encodekey;
   return JENCODE_KEY;
}
/*------------------------------------------------------------
* ¥¢¥«¥¦¥ó¥È¥µ¡¼¥Ð¡¼¤Ë½ñ¤­  ¤à¥Ð¥Ã¥Õ¥¡¤Î¥µ¥¤³N¤òÀßÄê¤¹¤ë
* °ú¿ô
*  ¤Ê¤·
* ÊÖ¤êÃÍ
*  unsigned int ¥­¡¼¤òÊÖ¤¹
------------------------------------------------------------*/
unsigned int setAcWBSize( void )
{
    AC_WBSIZE = config.acwbsize;
    return AC_WBSIZE;
}
unsigned int getAcwriteSize( void )
{
    return config.acwritesize;
}
unsigned int getErrUserDownFlg( void )
{
    return config.ErrUserDownFlg;
}
    

#ifdef _DEL_DROP_GOLD
unsigned int getGolddeletetime( void )
{
    if( config.Golddeletetime > 0 )
		return config.Golddeletetime;
	else
		return config.Itemdeletetime;
}
void setIGolddeletetime( unsigned int interval )
{
	config.Golddeletetime = interval;
}
#endif
#ifdef _Ip_Restrict //­­¨îIPµn¤J
int getiprestrict( void ) //¨ú±o­­¨îIPµn¤J
{
  if(config.iprestrict > 0 )
		return config.iprestrict;
  else
		return 0;
}
#endif
#ifdef _Set_Born_Player	//¦Û©w¸q¥X¥ÍÂà¼Æ+µ¥¯Å+ÂI¼Æ
int getNewplayerBornPoint( void ) //¨ú±o¦Û©w¸q¥X¥ÍÂI¼Æ
{
  if(config.newplayerBornPoint > 0 )
		return config.newplayerBornPoint - 20;
  else
		return 0;
}
#ifdef _ANGELOPEN //yang ADD ºëÆF¥l³ê§PÂ_¶}Ãö
char getAngelOpen(void)
{
	return config.AngelOpen;
}
#endif
#ifdef _Eggfeed //yang ADD ¦Û©w¸qÁý³J¦¸¼Æ
int getEggfeed( void ) 
{
	  if(config.Eggfeed > 0 )
		return config.Eggfeed;
  else
		return 0;
}
#endif
#ifdef _Proexp //yang ADD Â¾·~¸gÅç­¿²v
int getProexp( void ) 
{
	  if(config.Proexp > 0 )
		return config.Proexp;
  else
		return 1;
}
#endif
#ifdef _RideTransLimit   //yang ADD ­­¨îÃMÃd¤£±o¶W¹L¤@Âà
int getRidets( void ) 
{
		return config.Ridets;
}
#endif
#ifdef _Compel_Store             //yang ADD ±j¦s¶}Ãö
int getCompelStore( void ) 
{
		return config.CompelStore;
}
#endif
#ifdef _Pettranslimit            //yang ADD Ãdª«Âà¥Í¯à¤O­­¨î
int getPettranslimit( void ) 
{
  if(config.Pettranslimit < 150)
		return 150;
  else
		return config.Pettranslimit;
}
#endif
#ifdef _Join_Forbid  			//yang ADD ¸T¤î¥[¤J¹Î¶¤
int getjoinforbidnum(int Num) 
{
	int i = config.joinforbidnum[Num];
	if (i <= 0)return -1;
	return i;
}
#endif
#ifdef _Eventlock  		  	    //yang ADD ¥u¯à°µ¤@¦¸ªº¥ô°È
int getendevent(int Num) 
{
	int i = config.endeventnum[Num];
	if (i <= 0)return -1;
	return i;
}
int getnowevent(int Num) 
{
	int i = config.noweventnum[Num];
	if (i <= 0)return -1;
	return i;
}
#endif
int getNewplayertrans( void )
{
  if(config.newplayertrans > 7)
		return 7;
	else if(config.newplayertrans >= 0)
		return config.newplayertrans;
	else
		return 0;
}
int getNewplayerlv( void )
{
  if(config.newplayerlv > 160)
		return 160;
	else if(config.newplayerlv >0)
		return config.newplayerlv;
	else
		return 0;
}
#endif
#ifdef _NEW_PLAYER_CF
int getNewplayerpetlv( void )
{
  if(config.newplayerpetlv > 160)
		return 160;
	else if(config.newplayerpetlv > 0)
		return config.newplayerpetlv;
	else
		return 0;
}

int getNewplayergivepet( unsigned int index )
{
  if(config.newplayergivepet[index] > 0 )
		return config.newplayergivepet[index];
	else
		return -1;
}

int getNewplayergiveitem( unsigned int index )
{
  if(config.newplayergiveitem[index] > 0 )
		return config.newplayergiveitem[index];
	else
		return -1;
}

void setNewplayergivepet( unsigned int index ,unsigned int interval)
{
	config.newplayergivepet[index] = interval;
}

int getNewplayergivegold( void )
{
  if(config.newplayergivegold > 1000000)
		return 1000000;
	else if(config.newplayergivegold < 0)
		return 0;
	else
		return config.newplayergivegold;
}
int getRidePetLevel( void )
{
  if(config.ridepetlevel > 0 )
		return config.ridepetlevel;
	else
		return -1;
}
#ifdef _VIP_SERVER
int getNewplayergivevip( void )
{
	return config.newplayerpetvip < 0?0:config.newplayerpetvip;
}
#endif
#endif

#ifdef _UNLAW_WARP_FLOOR
int getUnlawwarpfloor( unsigned int index )
{
  if(config.unlawwarpfloor[index] > 0 )
		return config.unlawwarpfloor[index];
	else
		return -1;
}
#endif

#ifdef _WATCH_FLOOR
int getWatchFloor( unsigned int index )
{
  if(config.watchfloor[index] > 0 )
		return config.watchfloor[index];
	else
		return -1;
}
char* getWatchFloorCF( void )
{
	return (config.watchfloor[0]>0)? "¬O":"§_";
}
#endif

#ifdef _BATTLE_FLOOR
int getBattleFloor( unsigned int index )
{
  if(config.battlefloor[index] > 0 )
		return config.battlefloor[index];
	else
		return -1;
}
char* getBattleFloorCF( void )
{
	return (config.battlefloor[0]>0)? "¬O":"§_";
}
#endif

#ifdef _ANGEL_SUMMON

extern int mission_num;

BOOL LoadMissionList( )
{
	FILE* fp;
	int i = 0;

	mission_num = 0;

	fp = fopen("./data/mission.txt", "r");
	if (fp == NULL)
	{
		print("¥ô°È¤å¥ó¥´¶}¿ù»~\n");
		return FALSE;
	}
	
	memset( missionlist, 0, sizeof(missionlist));

	while(1){
		char	line[1024];
		char	token[1024];
		int		mindex;
		if (fgets(line, sizeof(line), fp) == NULL)	break;
//		print("\n %s ", line);
		chop(line);
		// ¥H#¬°µù¸Ñ*******
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************

		//®æ¦¡ #¥ô°È½s¸¹,¥²­nµ¥¯Å,¥ô°È»¡©ú,¼ú«~ID,­­¨î®É¶¡(¤p®É)
		
		getStringFromIndexWithDelim(line, ",", 1, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		mindex = atoi( token);

		if( mindex <= 0 || mindex >= MAXMISSION) 
			break;

		missionlist[mindex].id = mindex;

		getStringFromIndexWithDelim(line, ",", 2, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missionlist[mindex].level = atoi( token);

		getStringFromIndexWithDelim(line, ",", 3, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missionlist[mindex].eventflag, token);

		getStringFromIndexWithDelim(line, ",", 4, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missionlist[mindex].detail, token);

		//getStringFromIndexWithDelim(line, ",", 4, token, sizeof(token));
		//if (strcmp(token, "") == 0)	break;
		//strcpy( missionlist[mindex].bonus, token);

		getStringFromIndexWithDelim(line, ",", 5, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missionlist[mindex].limittime = atoi( token);
/*
		print("\nMISSION[%d] lv:%d ef:%s detail:%s limit:%d ", mindex,
			missionlist[mindex].level, missionlist[mindex].eventflag,
			missionlist[mindex].detail, missionlist[mindex].limittime );
*/
		mission_num++;
		//if (mission_num > MAXMISSION)	break;
	}
	fclose(fp);
	return TRUE;
}



BOOL LoadMissionCleanList( )
{
	// ®æ¦¡... ¨ÏªÌ,«iªÌ,¥ô°È,¼ú½à
	FILE* fp;
	int	listindex =0;
	int i = 0;

	memset( missiontable, 0, sizeof(missiontable));
	fp = fopen("./data/missionclean.txt", "r");
	if (fp == NULL)
	{
		print("²M°£¥ô°È¤å¥ó¥´¶}¿ù»~\n");
		return FALSE;
	}

	while(1){
		char	line[1024];
		char	token[1024];
		
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		print("\n %s ", line);
		chop(line);
		// ¥H#¬°µù¸Ñ*******
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		
		getStringFromIndexWithDelim(line, ",", 1, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missiontable[listindex].angelinfo, token);

		getStringFromIndexWithDelim(line, ",", 2, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missiontable[listindex].heroinfo, token);

		getStringFromIndexWithDelim(line, ",", 3, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missiontable[listindex].mission = atoi( token);
		
		getStringFromIndexWithDelim(line, ",", 4, token, sizeof(token));
		//if (strcmp(token, "") == 0)	break;
		missiontable[listindex].flag = atoi( token);

		getStringFromIndexWithDelim(line, ",", 5, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missiontable[listindex].time = atoi( token);

		print("\nMISSIONCLEAN[%d] %s %s %d %d %d", listindex,
			missiontable[listindex].angelinfo,
			missiontable[listindex].heroinfo,
			missiontable[listindex].mission,
			missiontable[listindex].flag,
			missiontable[listindex].time );

		listindex++;
		if ( listindex >= MAXMISSIONTABLE)	break;
	}
	fclose(fp);
	return TRUE;
}


#endif

#ifdef _JOBDAILY
extern  DailyFileType dailyfile[MAXDAILYLIST];
BOOL LoadJobdailyfile(void)
{
	char	line[20000];
	char	token[16384];
	int		listindex =0;
	int     i;
	FILE* fp;

	fp = fopen("./data/jobdaily.txt", "r");
	if (fp == NULL)
	{
		print("¤é±`¤u§@¤å¥ó¥´¶}¿ù»~\n");
		return FALSE;
	}

	memset( dailyfile, 0, sizeof(dailyfile));

	while(1){		
		line[0]='\0';	
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		//print("\n %s ", line);
		chop(line);

		// #¬°µù¸Ñ
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		
		getStringFromIndexWithDelim(line, "|", 1, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		dailyfile[listindex].jobid = atoi(token);

		getStringFromIndexWithDelim(line, "|", 2, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( dailyfile[listindex].rule, token);

		getStringFromIndexWithDelim(line, "|", 3, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		if(strlen(token)>64){
			print("\n¥ô°È»¡©ú¹Lªø:%d\n",strlen(token));
			return FALSE;
		}
		strcpy( dailyfile[listindex].explain, token);
		
		getStringFromIndexWithDelim(line, "|", 4, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( dailyfile[listindex].state, token);

		/*print("\ndailyfile[%d] %s %s %s %s", listindex,
			dailyfile[listindex].jobid,
			dailyfile[listindex].rule,
			dailyfile[listindex].explain,
			dailyfile[listindex].state);	
		*/
		listindex++;
		if ( listindex >= MAXDAILYLIST)	break;
	}
	fclose(fp);
	return TRUE;
}
#endif

#ifdef _USER_EXP_CF
BOOL LoadEXP( char* filename )
{
	FILE* fp;
	int i = 0;
	int MaxLevel=0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		print("µLªk¥´¶}¤å¥ó\n");
		return FALSE;
	}

	while(1){
		char	line[64], exp[64];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		chop(line);

		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************
		MaxLevel = MaxLevel + 1;
		if (MaxLevel >= 200)	break;
		easyGetTokenFromString(line, 2, exp, sizeof(exp));
		NeedLevelUpTbls[MaxLevel]=atoi(exp);
	}
	fclose(fp);
	return TRUE;
}

char* getEXPfile( void )
{
    return config.expfile;
}

int getNeedLevelUpTbls( int level )
{
    return NeedLevelUpTbls[level];
}

#endif

#ifdef _UNREG_NEMA
char* getUnregname( int index )
{
    return config.unregname[index];
}
#endif

#ifdef _TRANS_LEVEL_CF
int getChartrans( void )
{
		if(config.chartrans>6)
			config.chartrans=6;
    return config.chartrans;
}
int getPettrans( void )
{
		if(config.pettrans>2)
			return 2;
		else if(config.pettrans<-1)
			return -1;
    return config.pettrans;
}
int getYBLevel( void )
{
		if(config.yblevel>config.maxlevel)
			config.yblevel=config.maxlevel;
    return config.yblevel;
}
int getMaxLevel( void )
{
    return config.maxlevel;
}
#endif

#ifdef _POINT
char* getPoint( void )
{
		return (config.point>0)? "¬O":"§_";
}
int getTransPoint( int index )
{
		return config.transpoint[index];
}
#endif

#ifdef _PET_UP
char* getPetup( void )
{
		return (config.petup>0)? "¬O":"§_";
}
#endif
#ifdef _LOOP_ANNOUNCE
char* getLoopAnnouncePath( void )
{
		return config.loopannouncepath;
}
int loadLoopAnnounce( void )
{
	FILE* fp;
	int i = 0;
	config.loopannouncemax=0;
	fp = fopen(config.loopannouncepath, "r");
	if (fp == NULL)
	{
		print("µLªk¥´¶}¤å¥ó\n");
		return FALSE;
	}
	while(1){
		char	line[1024];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		chop(line);

		if( line[0] == '#' )
			continue;
		for( i=0; i<10; i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************
		strcpy(config.loopannounce[config.loopannouncemax],line);
		config.loopannouncemax++;
	}
	fclose(fp);
	return TRUE;
}
int getLoopAnnounceTime( void )
{
    return (config.loopannouncetime<0)?-1:config.loopannouncetime;
}
int getLoopAnnounceMax( void )
{
    return (config.loopannouncemax>0)?config.loopannouncemax:0;
}
char* getLoopAnnounce( int index )
{
    return config.loopannounce[index];
}
#endif

#ifdef _SKILLUPPOINT_CF
int getSkup( void )
{
    return (config.skup>0)?config.skup:0;
}
#endif
#ifdef _RIDELEVEL
int getRideLevel( void )
{
    return config.ridelevel;
}
#endif
#ifdef _REVLEVEL
char* getRevLevel( void )
{
		return (config.revlevel>0)?"¬O":"§_";
}
#endif
#ifdef _NEW_PLAYER_RIDE
char* getPlayerRide( void )
{
		if(config.npride>2)
			return "°t®M°eªê¥[¹p";
		else if(config.npride==2)
			return "°t®M°e¹p";
		else if(config.npride==1)
			return "°t®M°eªê";
		else
			return "¤£°e°t®MÃMÃd";
}
#endif

#ifdef _FIX_CHARLOOPS
int getCharloops( void )
{
    return config.charloops-1;
}
#endif

#ifdef _PLAYER_ANNOUNCE
int getPAnnounce( void )
{
    return (config.pannounce>-1)?config.pannounce:-1;
}
#endif
#ifdef _PLAYER_MOVE
int getPMove( void )
{
    return (config.pmove>-1)?config.pmove:-1;
}
#endif

int getrecvbuffer( void )
{
		if(config.recvbuffer<0)
	    return 0;
	  else if(config.recvbuffer>128)
	    return 128;
	  else
	  	return config.recvbuffer;
}

int getsendbuffer( void )
{
		if(config.sendbuffer<0)
	    return 0;
	  else if(config.sendbuffer>128)
	    return 128;
	  else
	  	return config.sendbuffer;
}

int getrecvlowatbuffer( void )
{
		if(config.recvlowatbuffer<0)
	    return 0;
	  else if(config.recvlowatbuffer>1024)
	    return 1024;
	  else
	  	return config.recvlowatbuffer;
}

int getrunlevel( void )
{
		if(config.runlevel<-20)
	    return -20;
	  else if(config.runlevel>19)
	    return 19;
	  else
	  	return config.runlevel;

}

#ifdef _SHOW_VIP_CF
int getShowVip( void )
{
		if(config.showvip>2)
			return 2;
		else if(config.showvip<0)
			return 0;
		else
			return config.showvip;
}
#endif

#ifdef _PLAYER_NUM
int getPlayerNum( void )
{
		return config.playernum;
}
void setPlayerNum( int num )
{
		config.playernum=num;
}
#endif

#ifdef _BATTLE_GOLD
int getBattleGold( void )
{
		if(config.battlegold<0)
	    return 0;
	  else if(config.battlegold>100)
	    return 100;
	  else
	  	return config.battlegold;

}
#endif

#ifdef _ANGEL_TIME
int getAngelPlayerTime( void )
{
		return (config.angelplayertime>1)?config.angelplayertime:1;
}
int getAngelPlayerMun( void )
{
		return (config.angelplayermun>2)?config.angelplayermun:2;
}
#endif

#ifdef _RIDEMODE_20
int getRideMode( void )
{
		if(config.ridemode<0)
			config.ridemode=0;
		return config.ridemode;
}
#endif
#ifdef _FM_POINT_PK
char *getFmPointPK( void )
{
		return (config.fmpointpk>0)?"¬O":"§_";
}
#endif
#ifdef _ENEMY_ACTION
int getEnemyAction( void )
{
		if(config.enemyact>100)
			return 100;
		else if(config.enemyact<1)
			return 1;
		else
			return config.enemyact;
}
#endif

#ifdef _FUSIONBEIT_TRANS
int getFusionbeitTrans( void )
{
		if(config.fusionbeittrans>2)
			return 2;
		else if(config.fusionbeittrans<0)
			return 0;
		else
			return config.fusionbeittrans;
}
#endif
int getCpuUse( void )
{
	return config.cpuuse;
}
#ifdef _CHECK_PEPEAT
int getCheckRepeat( void )
{
		return (config.CheckRepeat>0)?1:0;
}
#endif



#ifdef _FM_JOINLIMIT
int getJoinFamilyTime( void )
{
		return config.joinfamilytime;
}
#endif
