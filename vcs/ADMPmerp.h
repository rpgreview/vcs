/*****************************************************************************/

typedef struct attk_tab {	/* MERP table */
    unsigned char	st;		/* start value */
    unsigned char	ed;		/* end value */
    char um_flag;	/* unmodified roll flag */
    char res[5][3];	/* array of results Hits/Crit/Crit_Type */
} attk_tab;

	/* res[8] is HITS,APEN,BLEED,STUN,PARRY,No PARRY,DEATH,INACT */
typedef struct crit_tab {	/* MERP table */
    unsigned char	st;	   	/* start value */
    unsigned char	ed;  	   	/* end value */
    int res[8];   	/* array of results HITS/BLEED/STUN/ACT etc */
    char msg[54];   	/* description */
    char spec_mods[30];	/* Special armor mods, temp penalties */
} crit_tab;

typedef struct move_tab {
    	int st;			/* start value */
    	int ed;			/* end value */
    unsigned char res[9];	/* array of results */
} move_tab;

typedef struct spell_tab {
	signed char realm_id;
	signed char spell_lvl;
	char spell_name[25];
	char spell_aoe[13];
	char spell_duration[13];
	char spell_range[9];
	char spell_desc[34];
} spell_tab;

typedef struct herb_tab {
	char herb_type;
	char herb_name[20];
	char herb_found[20];
	char herb_usage[20];
	char herb_cost[10];
	char herb_effects[90];
} herb_tab;

typedef struct weapon_tab {
	char    wp_dsc[25];     /* Description */
	char    wp_tbl[4];      /* attack table to use */
	char    wp_sel;         /* Weapon selected */
	int     wp_ob;          /* Current OB */
	int     wp_ca;  /* Weapon Critical Adjustment */
	char    wp_sz[2];       /* Size of weapon's attack */
	int     wp_ma;  /* it's weight */
	int     wp_fm;          /* Fumble Value */
	int     wp_br;  /* Base Range */
	int     wp_bf;          /* Breakage Factor */
	int     wp_str;         /* Strength */
	char    wp_pc[3];       /* Primary Crit Value */
	char    wp_sc[3];       /* Secondary Crit Value */
	char    wp_sm[30];      /* Special armor mods */
} weapon_tab;

typedef struct equip_tab {
	char	type;
	char	name[30];
	char	cost[30];
	char	weight[30];
	char	desc[30];
} equip_tab;

#define     CRITG_A		1
#define     CRITG_B		2
#define     CRITG_C		3
#define     CRITG_D		4
#define     CRITG_E		5
#define     KILL_XP		6

#define		MAX_D100WEAPONS	53

	/* this points into the list of actions available */
#define Act_Melee 0
#define Act_MissileAttack 1
#define Act_MissileLoad 2
#define Act_SpellCast 3
#define Act_SpellCharge 4
#define Act_MissileThrow 5
#define Act_Move 6
#define Act_OppAction 7
#define Act_Inactive 8
#define Act_Bandage 9

#ifndef O_BINARY
#define O_BINARY O_RDWR
#endif

typedef struct attk_tab2 {
	int   st;
	int   ed;
	char um_flag;
	char res[20][3];		/* array of results Hits/Crit/Crit_Type */
} attk_tab2;

typedef struct crit_tab2 {
	int   st;
	int   ed;
	char crit;
	int res[8];				/* res[8] is HITS,APEN,BLEED,STUN,PARRY,No PARRY,DEATH,INACT */
	char msg[80];
	char mods[80];
} crit_tab2;
