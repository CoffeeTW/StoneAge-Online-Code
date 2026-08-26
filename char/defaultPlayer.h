#include "version.h"

static Char    player=
{
    FALSE,      /*  use     ÇPÆìÇNÇiÆêÆê*/
    {
		0,		/*  CHAR_DATAPLACENUMBER */
        0,      /*  CHAR_BASEIMAGENUMBER */
        0,      /*  CHAR_BASEBASEIMAGENUMBER */
		0,		/*  CHAR_FACEIMAGENUMBER */
        0,      /*  CHAR_FLOOR  */
        0,      /*  CHAR_X */
        0,      /*  CHAR_Y  */
        5,      /*  CHAR_DIR 12ºßÇy0ÇRºß¯É¥óÇqÇR */
        1,      /*  CHAR_LV  */
        0,      /*  CHAR_GOLD    */
        1,      /*  CHAR_HP  */
        0,      /*  CHAR_MP  */

        0,      /*  CHAR_MAXMP   */

    	0,		/*  CHAR_VITAL	*/
        0,      /*  CHAR_STR */
        0,      /*  CHAR_TOUGH */
    	0,		/*  CHAR_DEX	*/

    	0,		/*  CHAR_CHARM	*/
    	0,		/*  CHAR_LUCK	*/
		0,		/* ©s¾Û©Ô */
		0,		/* «±¾Û©Ô */
		0,		/* ´Ý¾Û©Ô */
		0,		/* ·V¾Û©Ô */

		0,		/* CHAR_SLOT*/
		0,		/* CHAR_CRITIAL */
		0,		/* CHAR_COUNTER */
		0,		/* CHAR_RARE */
        0,      /*  CHAR_RADARSTRLENGTH */
        0,      /*  CHAR_CHATVOLUME */
        MAKE2VALUE(100,20),  /*  CHAR_MERCHANTLEVEL  */
        0,      /*  CHAR_HEALERLEVEL    */
        0,      /*  CHAR_DETERMINEITEM  */

        -1,     /*  CHAR_INDEXOFEQTITLE  */


        0,      /*  CHAR_POISON  */
        0,      /*  CHAR_PARALYSIS  */
        0,      /*  CHAR_SILENCE    */
        0,      /*  CHAR_STONE  */
        0,      /*  CHAR_DARKNESS   */
        0,      /*  CHAR_CONFUSION  */

        0,      /*  CHAR_LOGINCOUNT */
        0,      /*  CHAR_DEADCOUNT */
        0,      /*  CHAR_WALKCOUNT */
        0,      /*  CHAR_TALKCOUNT */

    	0,		/*  CHAR_DAMAGECOUNT */
    	0,		/*  CHAR_GETPETCOUNT */
    	0,		/*  CHAR_KILLPETCOUNT */
    	0,		/*  CHAR_DEADPETCOUNT */
    	0,		/*  CHAR_SENDMAILCOUNT */
		0,		/*  CHAR_MERGEITEMCOUNT */

		0,		/*  CHAR_DUELBATTLECOUNT */
		0,		/*  CHAR_DUELWINCOUNT */
		0,		/*  CHAR_DUELLOSECOUNT */
		0,		/*  CHAR_DUELSTWINCOUNT */
		0,		/*  CHAR_DUELMAXSTWINCOUNT */

        CHAR_TYPEPLAYER,    /*  CHAR_WHICHTYPE  */
        1000,   /*  CHAR_WALKINTERVAL   */
        1000,   /*  CHAR_LOOPINTERVAL   */
#ifdef _NEWOPEN_MAXEXP
		0,	// CHAR_OLDEXP,
#endif
		0,	// CHAR_EXP,
        -1,     /*  CHAR_LASTTALKELDER*/
        0,      /*  CHAR_SKILLUPPOINT    */
    	0,		/*  CHAR_LEVELUPPOINT */

        0,      /*  CHAR_IMAGETYPE    */
		CHAR_COLORWHITE,	/* CHAR_NAMECOLOR */
		CHAR_COLORWHITE,	/* CHAR_POPUPNAMECOLOR */
		0,		/*  CHAR_LASTTIMESETLUCK */
		100,	/*  CHAR_DUELPOINT */
		0,	/*  CHAR_EVENT */
		0,	/*  CHAR_EVENT2 */
		0,	/*  CHAR_EVENT3 */
#ifdef _NEWEVENT
		0,	/*  CHAR_EVENT4 */
		0,	/*  CHAR_EVENT5 */
		0,	/*  CHAR_EVENT6 */
#endif
		0,	/*  CHAR_NOWEVENT */
		0,	/*  CHAR_NOWEVENT2 */
		0,	/*  CHAR_NOWEVENT3 */
#ifdef _NEWEVENT
		0,	/*  CHAR_NOWEVENT4 */
		0,	/*  CHAR_NOWEVENT5 */
		0,	/*  CHAR_NOWEVENT6 */
#endif
		0,  /* CHAR_TRANSMIGRATION */
		0,  /* CHAR_TRANSEQUATION */

        0,      /*  CHAR_INITDATA    */

//#ifdef _PETSKILL_BECOMEPIG
//        -1,
//#endif

		0,	//CHAR_SILENT,				/* char shutup time */    
		0,	//    CHAR_FMINDEX,				// ²£¾À index
		0,	//    CHAR_FMLEADERFLAG,			
								/* ²£¾À£Küz¶PºN
    							 * FMMEMBER_NONE	:¡é£V“¡’ÍÇð•z²£¾À
    							 * FMMEMBER_APPLY	:ÇÏ¥s“¡’Í²£¾ÀÆê
    							 * FMMEMBER_LEADER	:¾Àú¹
    							 * FMMEMBER_MEMBER	:’Ãý«£Küz
    							 * FMMEMBER_ELDER	:ú¹£l    
    							 * FMMEMBER_INVITE	:¨B“·			// ¬JüÈÆéÇÊ
    							 * FMMEMBER_BAILEE	:Äî¥zú¹			// ¬JüÈÆéÇÊ
    							 * FMMEMBER_VICELEADER  :®Ã¾Àú¹		// ¬JüÈÆéÇÊ
    							*/
		0,	//    CHAR_FMSPRITE,		// ²£¾À”\¡¼¥°ÆA

		0,	//    CHAR_BANKGOLD,
		0,	//    CHAR_RIDEPET,
		0,	//    CHAR_LEARNRIDE,
#ifdef _NEW_RIDEPETS
		0,	//	CHAR_LOWRIDEPETS,
#endif
 		0,	//   CHAR_LIMITLEVEL,
#ifdef _PET_FUSION
		0,	//	CHAR_FUSIONCODE,		//úJ¶PÚñÚò
		0,	//	CHAR_FUSIONINDEX,		//ºÀÇMÐ\úJÚñ¸¡
		0,	//	CHAR_FUSIONRAISE,		//Å¢ãl£[­p
		0,	//	CHAR_FUSIONBEIT,		//Ð\Í|ê¾§¨
		0,	//	CHAR_FUSIONTIMELIMIT,	//Å¢ãlüÈ¤B
#endif
#ifdef _PERSONAL_FAME	// Arminius 8.30: ²£¾ÀüR’ËÖô¿ë
		0,	//    CHAR_FAME,
#endif

#ifdef _NEWSAVE
		0,	//    CHAR_SAVEINDEXNUMBER,	/*  SaveFile .0.char or .1.char */
#endif
 
#ifdef _ATTACK_MAGIC
		0,	//		CHAR_EARTH_EXP,						// úP²£úY”HÛUÚu°Å½uúö
		0,	//		CHAR_WATER_EXP,						// úP²£úY•VÛUÚu°Å½uúö
		0,	//		CHAR_FIRE_EXP,						// úP²£úY•WÛUÚu°Å½uúö
		0,	//		CHAR_WIND_EXP,						// úP²£úYûõÛUÚu°Å½uúö
		0,	//		CHAR_EARTH_RESIST,					// úP²£úY”HÛUÚuÈ`¢t
		0,	//		CHAR_WATER_RESIST,					// úP²£úY•VÛUÚuÈ`¢t
		0,	//		CHAR_FIRE_RESIST,					// úP²£úY•WÛUÚuÈ`¢t
		0,	//		CHAR_WIND_RESIST,					// úP²£úYûõÛUÚuÈ`¢t
		0,	//		CHAR_EARTH_ATTMAGIC_EXP,			// úP²£úY”HÛUÚu°Å½uúö©_¼QüG
		0,	//		CHAR_WATER_ATTMAGIC_EXP,			// úP²£úY•VÛUÚu°Å½uúö©_¼QüG
		0,	//		CHAR_FIRE_ATTMAGIC_EXP,				// úP²£úY•WÛUÚu°Å½uúö©_¼QüG
		0,	//		CHAR_WIND_ATTMAGIC_EXP,				// úP²£úYûõÛUÚu°Å½uúö©_¼QüG
		0,	//	 	CHAR_EARTH_DEFMAGIC_EXP,			// úP²£úY”HÛUÚuÈ`¢t©_¼QüG
		0,	//		CHAR_WATER_DEFMAGIC_EXP,			// úP²£úY•VÛUÚuÈ`¢t©_¼QüG
		0,	//		CHAR_FIRE_DEFMAGIC_EXP,				// úP²£úY•WÛUÚuÈ`¢t©_¼QüG
		0,	//		CHAR_WIND_DEFMAGIC_EXP,				// úP²£úYûõÛUÚuÈ`¢t©_¼QüG
#endif


#ifdef _GAMBLE_BANK
		0,	//		CHAR_PERSONAGOLD,	//§ÙªìüR’Ë½À¡o
#endif
#ifdef _DROPSTAKENEW
		0,	//		CHAR_GAMBLENUM,		//§ÙªìíÚÇG
#endif
#ifdef _ADD_ACTION          //npc¯¹”©
		0,	//		CHAR_ACTIONSTYLE,
#endif
#ifdef _PET_EVOLUTION
		0,	//		CHAR_EVOLUTIONBASEVTL,
		0,	//		CHAR_EVOLUTIONBASESTR,	
		0,	//		CHAR_EVOLUTIONBASETGH,	
		0,	//		CHAR_EVOLUTIONBASEDEX,	
#endif

#ifdef _FM_JOINLIMIT
		0,	//		CHAR_FMTIMELIMIT,
#endif

#ifdef _CHAR_PROFESSION			// WON ADD ’ËúJ¼®ò§
		0,	//		PROFESSION_CLASS,			// ¼®ò§”¸
		0,	//		PROFESSION_LEVEL,			// ¼®ò§³æýc
//		0,	//		PROFESSION_EXP,				// ¼®ò§©_¼QüG
		0,	//		PROFESSION_SKILL_POINT,		// Èbý~íå­p
		0,	//		ATTACHPILE,					// ´²“¡À°ÛX
		0,	//		PROFESSION_FIRE_P,			// •W°Å½uúö
		0,	//		PROFESSION_ICE_P,			// “è°Å½uúö		
		0,	//		PROFESSION_THUNDER_P,		// ¡¼°Å½uúö
		0,	//		PROFESSION_FIRE_R,			// •WÈ`¢t
		0,	//		PROFESSION_ICE_R,			// “èÈ`¢t	
		0,	//		PROFESSION_THUNDER_R,		// ¡¼È`¢t
#endif
#ifdef _ALLDOMAN // (Æé“¯¡¼) Syu ADD ¹G¡oöýNPC
		0,	//		CHAR_HEROFLOOR, 
#endif
#ifdef _PETSKILL_BECOMEPIG
		-1,	//		CHAR_BECOMEPIG,
		100250, //CHAR_BECOMEPIG_BBI
#endif
		0,	//		CHAR_LASTLEAVETIME, // Robin add µ{ûA¿f¡¼üÈ¤B

#ifdef _NEW_MANOR_LAW
		0,	//		CHAR_MOMENTUM,
#endif

#ifdef _ITEM_ADDEXP2
		0,	//		CHAR_ADDEXPPOWER,
		0,	//		CHAR_ADDEXPTIME,
#endif

#ifdef _ANGEL_SUMMON
		0,	//		CHAR_HEROCNT, // ÈL£KÍiúkÇð¥zúY£[­p
#endif

#ifdef _TEACHER_SYSTEM
	  0,	// CHAR_TEACHER_FAME,	// ¾É®v»â¾ÉÁn±æ
#endif

#ifdef _GM_ITEM
	  0, // ª±®aGM©R¥O¦¸¼Æ
#endif
#ifdef _VIP_SERVER
	  0, // ·|­ûÂI¼Æ
#endif
#ifdef _VIP_RIDE
	  0, // ·|­ûÃM¶ÂÂû
#endif
    },

    {
        {""},     /*  CHAR_NAME   */
        {""},     /*  CHAR_OWNTITLE   */
        {""},           /*  CHAR_ARGUMENT */
        {""},       /*  CHAR_OWNERCDKEY   */
        {""},       /*  CHAR_OWNERCHARANAME   */
    },
    {
        SETFLG(1,1,1,1,1,1,0,0 ),
        SETFLG(0,0,0,0,0,0,0,1 ),
    }
};

LevelUpPattern lvplayer00={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer10={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer20={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer30={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer01={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer11={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer21={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer31={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer02={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer12={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer22={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer32={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer03={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer13={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer23={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer33={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer04={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer14={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer24={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer34={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer05={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer15={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer25={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer35={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer06={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer16={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer26={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer36={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer07={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer17={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer27={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer37={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer08={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer18={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer28={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer38={ {{100,10},{200,10},{50,8}},9,11,10};

LevelUpPattern lvplayer09={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer19={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer29={ {{100,10},{200,10},{50,8}},9,11,10};
LevelUpPattern lvplayer39={ {{100,10},{200,10},{50,8}},9,11,10};


