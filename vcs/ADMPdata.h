/****************************************************************************
 * Copyright Torquil Gault 2005+
 *
#       This program is free software; you can redistribute it and/or
#       modify it under the terms of the GNU General Public License
#       as published by the Free Software Foundation; either version 2
#       of the License, or (at your option) any later version.
#
#       This program is distributed in the hope that it will be useful,
#       but WITHOUT ANY WARRANTY; without even the implied warranty of
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#       GNU General Public License for more details.
#
#       You should have received a copy of the GNU General Public License
#       along with this program; if not, write to the Free Software
#       Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#
###############################################################################
****************************************************************************/

#ifndef ADMPDATA_H
#define ADMPDATA_H

#define MAX_WEAPONS				10
#define MAX_TEMPPENALTIES		8
#define MAX_BAB					3
#define MAX_ABILITYSTATS		6
#define MAX_CLASSES				4
#define MAX_SPELLDCS				9
#define MAX_D20ROLLS				9
#define MAX_SKILLS				9
#define MAX_GROUPS				70
#define MAX_MONSTERS				256
#define MAX_PLAYERS				20
#define MAX_MODIFIERS			30
#define MAX_TRIGGERS				10
#define MAX_ATTACKS				10
#define MAX_AUTODAMAGE			10
#define MAX_WEAPONATTACKS		4
#define MAX_OBJECTS				128
#define MAX_OBJECTDESC			128
#define MAX_IDLIST				20

#define MAX_QKMONSTERS			900

#define MAX_MEMBERS				(MAX_MONSTERS+MAX_PLAYERS)

#define MAX_STDWEAPONS			66
#define MAX_SPELLSLOTS			62
#define MAX_SPELLS				736

#define MAX_HEALMONSTERS		54

#define MAX_QUICKMODIFIERS		44
#define MAX_QUICKMODTYPES		8

#define MAX_D100TABLES			70
#define MAX_D100XP				70

#define AC_NORMAL					0
#define AC_TOUCH					1
#define AC_FLATFOOTED			2
#define AC_SHIELD					1		// d100
#define AC_PARRY					2		// d100
#define AC_NOPARRY				3		// d100

#define SAVE_FORTITUDE			0
#define SAVE_REFLEX				1
#define SAVE_WISDOM				2
#define SAVE_ESSENCE				0		// d100
#define SAVE_CHANNEL				1		// d100
#define SAVE_MENTAL				2		// d100
#define SAVE_POISON				3		// d100
#define SAVE_DISEASE				4		// d100

#define PENALTY_ACTIVITY		0		// d100
#define PENALTY_1					1		// d100
#define PENALTY_2					2		// d100
#define PENALTY_3					3		// d100
#define PENALTY_4					4		// d100

#define ROUND_DEATH				0		// d100
#define ROUND_INACTIVE			1		// d100
#define ROUND_2					2		// d100
#define ROUND_SPELL_CHG			3		// d100
#define ROUND_MISSILE_CHG		4		// d100

#define HP_MAX						0
#define HP_CUR						1
#define HP_NL						2
#define HP_TMP						3
#define HP_ADJ						4
#define HP_ENH						5

#define ABILITY_STR				0
#define ABILITY_DEX				1
#define ABILITY_CON				2
#define ABILITY_INT				3
#define ABILITY_WIS				4
#define ABILITY_CHA				5

#define MAX							0
#define TMP							1

#define SKILL_SEARCH				0
#define SKILL_SOH					1
#define SKILL_SPOT				2
#define SKILL_OPENLOCKS			3
#define SKILL_MOVESILENTLY		4
#define SKILL_LISTEN				5
#define SKILL_HIDE				6
#define SKILL_CONCENTRATION	7

#define SKILL_PERC				0
#define SKILL_STALK				1
#define SKILL_READRUNE			2
#define SKILL_USEITEM			3

#define BAB_MELEE					0
#define BAB_RANGED				1
#define BAB_GRAPPLE				2

#define TYPE						0
#define VALUE						1

#define MOD_BAB					1
#define MOD_AC						2
#define MOD_SAVE					3
#define MOD_DAMAGE				4
#define MOD_INIT					5
#define MOD_HP						6
#define MOD_SKILL					7
#define MOD_SAVE_FORTITUDE		8
#define MOD_SAVE_REFLEX			9
#define MOD_SAVE_WILL			10
#define MOD_MISS_CHANCE			11
#define MOD_SPELL_RESISTANCE	12
#define MOD_MOVE					5

	// these map to adjusteffecttype[] in ADMPextra.cxx
#define MOD_TYPE_NONE			0
#define MOD_TYPE_ENHANCEMENT	1
#define MOD_TYPE_MORALE			2
#define MOD_TYPE_LUCK			3
#define MOD_TYPE_HASTE			4
#define MOD_TYPE_ARMOR			5
#define MOD_TYPE_SHIELD			6
#define MOD_TYPE_DEFLECTION	7
#define MOD_TYPE_DODGE			8
#define MOD_TYPE_OTHER			9
#define MOD_TYPE_NATURAL		10

#define AC_SECTION_DEX			0
#define AC_SECTION_SIZE			1
#define AC_SECTION_DEFLECTION	2
#define AC_SECTION_NATURAL		3
#define AC_SECTION_ARMOR		4
#define AC_SECTION_SHIELD		5
#define AC_SECTION_DODGE		6

#define AC_SECTION_LEG			0		// d100
#define AC_SECTION_ARM			1		// d100
#define AC_SECTION_HELM			2		// d100
#define AC_SECTION_PARRY		3		// d100
#define AC_SECTION_WORN			4		// d100

	// these must match the Spell Options sequence
#define SO_SPELLRESISTANCE		1

#define ID_EDIT					0		// see MAX_IDLIST
#define ID_INIT 					1
#define ID_DEFD					2
#define ID_WEAP					3
#define ID_QMON					4
#define ID_ADJ1					5
#define ID_ADAM					6
#define ID_TEMP 					7
#define ID_WSCH 					8
#define ID_DISA 					9
#define ID_MSKILLCHK 			10
#define ID_QKHEAL					11
#define ID_GROUP					12
#define ID_QKICON					13
#define ID_WEAPONCOPY			14
#define ID_HEALMONSTER			15
#define ID_QUICKMODS				16
#define ID_MASSCOMBAT			17

#define GRIDSIZE				30
#define MAPSIZE				300

#define GRID_OBJECT			1
#define GRID_PLAYER			2
#define GRID_MONSTER			3

#define ACTION_COMBAT		0
#define ACTION_DOTS			1
#define ACTION_LINE			2
#define ACTION_SHAPES		3
#define SHAPE_FILL			0
#define SHAPE_OUTLINE		1

#define RESIST_FIRE			0
#define RESIST_ACID			1
#define RESIST_COLD			2
#define RESIST_ELEC			3
#define RESIST_SONIC			4
#define RESIST_POISON		5

#define DICE_D20				0
#define DICE_MERP				1
#define DICE_RMS				2

typedef	unsigned char uchar;
typedef	short int sint;

/*********************************************************************/
typedef struct ADMPweapon {
	char	c_available;			/* is this available to be used */
	char	c_description[30];	/* weapon description */
	int	i_attackBonus[4];		/* attack bonuses */
	int	i_noAttacks;			/* no. attacks with this weapon */
	int	i_doneAttacks;			/* no. attacks done with this weapon */
	char	c_damage[20];			/* ie. 3d4, +3 wis etc TG: should be 20 chars */
	char	c_critical[20];		/* crit range ie. 18-20,*3 TG: should be 20 chars */
	int	i_range;					/* base range of the weapon */
	int	i_reach;					/* weapon reach */
	int	i_magicalBonus;		/* used in Dam. Reduction calcs */
	int	i_size;					/* weapon size */
	int	i_type;					/* weapon type = Slash/Puncturing etc */
	char	c_attackType;			/* melee or ranged etc */
	char	c_message[40];			/* a message to display about this weapon or attack */
	char	c_table[4];				/* attack table to use */
	int	i_fumble;				/* fumble range of the weapon */
	int	i_critAdjust;			/* crit adjustment of the weapon */
} ADMPweapon;

/*********************************************************************/
typedef struct ADMPflags {
	uchar	f_isStabilised:1;
	uchar	f_disabled:1;
	uchar	f_ignoreCriticals:1;
	uchar	f_autoStablise:1;
	uchar	f_evasion:1;
	uchar	f_srdMonster:1;
	uchar	f_npc:1;
	uchar	f_invisible:1;
	uchar	f_wasViewed:1;
	uchar	f_ignoreBleed:1;
	uchar	f_ignoreStun:1;
	uchar	f_flag12:1;
	uchar	f_flag13:1;
	uchar	f_flag14:1;
	uchar	f_flag15:1;
	uchar	f_flag16:1;
} ADMPflags;

typedef struct ADMPflags2 {
	uchar	f_flag1:1;
	uchar	f_flag2:1;
	uchar	f_flag3:1;
	uchar	f_flag4:1;
	uchar	f_flag5:1;
	uchar	f_flag6:1;
	uchar	f_flag7:1;
	uchar	f_flag8:1;
} ADMPflags2;

typedef struct ADMPflags3 {
	uchar	f_debug:1;
	uchar	f_rollAllRolls:1;
	uchar	f_rollInitRolls:1;
	uchar	f_logfile:1;
	uchar	f_rollInitEveryRnd:1;
	uchar	f_removeMonstersInit:1;
	uchar	f_oneMissTwentyHits:1;
	uchar	f_fogOfWar:1;
	uchar	f_defaultDefender:1;
	uchar	f_askBeforeMoving:1;
	uchar	f_showDeadMonsters:1;
	uchar	f_deathAtCON:1;
	uchar	f_flag13:1;
	uchar	f_flag14:1;
	uchar	f_flag15:1;
	uchar	f_flag16:1;
} ADMPflags3;

typedef struct ADMPspell {
	uchar	i_maxLevel0:4;
	uchar	i_curLevel0:4;
	uchar	i_maxLevel1:4;
	uchar	i_curLevel1:4;
	uchar	i_maxLevel2:4;
	uchar	i_curLevel2:4;
	uchar	i_maxLevel3:4;
	uchar	i_curLevel3:4;
	uchar	i_maxLevel4:4;
	uchar	i_curLevel4:4;
	uchar	i_maxLevel5:4;
	uchar	i_curLevel5:4;
	uchar	i_maxLevel6:4;
	uchar	i_curLevel6:4;
	uchar	i_maxLevel7:4;
	uchar	i_curLevel7:4;
	uchar	i_maxLevel8:4;
	uchar	i_curLevel8:4;
	uchar	i_maxLevel9:4;
	uchar	i_curLevel9:4;
} ADMPspell;

/*********************************************************************/
typedef struct ADMPplayer {
	char	c_name[30];
	int	i_classes[MAX_CLASSES];
	int	i_levels[MAX_CLASSES];
	int	i_race;
	int	i_alignment;
	int	i_size;

	float	f_challengeRating;
	int	i_d20Rolls[MAX_D20ROLLS];
	int	i_skills[MAX_SKILLS];

	int	i_speed;
	int	i_initiative[2];
	int	i_armorClass[4];
	int	i_armorClassSplit[8];						/* DEX, Size, Deflection etc */
	int 	i_bab[MAX_BAB][4];							/* base attack bonuses */

	int	i_reach;											/* standard reach of the player */
	int	i_space;											/* standard space taken of the player */

	int	i_noAttacks;
	int	i_doneAttacks;
	short int	i_whomAttacked[MAX_ATTACKS+2][2];/* the ID of whom they attacked last time & weapon used */

	int	i_xp[2];
	uchar c_d100XP[MAX_D100XP];						// used for d100 XP calcs

	int	i_abilityStats[2][MAX_ABILITYSTATS];	/* abilitiy stats Curr & Temp */

	int	i_spellFailure;								/* spell failure percentage */
	int	i_spellDC[MAX_SPELLDCS];
	int	i_savingThrows[5];
	int	i_spellResistance;
	int	i_baseSpell;									// d100
	int	i_directedSpells;								// d100

	int	i_hp[6];											/* Max, Current, Non-lethal, Temp, Adj, from Enhancement items */
	int	i_bleeding;										/* per round amount, can be used for regeneration */
	int	i_disabledAt;									/* usually at 0 */
	int	i_unconciousAt;								/* usually at -1 */
	int	i_inactive;										/* no rounds inactive */
	int	i_stun;											/* no rounds stunned */
	int	i_penalty[5];									// various penalties
	int	i_roundsUntil[5];								// various rounds until X happens

	short int	i_damageReduction[4];				/* ie. 8/+2 */

	char	c_hitDice[20];									/* Hit Dice */
	uchar	c_environment;									/* where it lives - monsters only */

	int	i_playerID;									// internal ID
	int	i_stdMonsterID;							// which std monster it came from

	ADMPweapon	w_weapons[MAX_ATTACKS+2];
	ADMPflags	flags;
	ADMPspell	spellsAvailable;						/* spells available at each level */

	sint	i_inGroup;					// which group is it in

	sint	i_regeneration;			// how many HP to regen each round
	sint	i_resistances[8];			// various resistances - acid, fire etc, in a per round
	sint	i_resistancesUsed[8];	// various resistances used that round

	sint	i_mapX, i_mapY;					// grid map positions
	sint	i_prevMapX, i_prevMapY;			// grid map positions

	sint	i_negateCrit;						// negate critical percentage
	sint	i_useShieldOn;						// which ID the defender uses their shield AC on
	sint	i_useDodgeOn;						// which ID the defender uses their dodge AC on

	char	c_iconFile[60];			// the icon to associate with it
	char	c_items[190];			// any special items they carry

	int	i_noInGroup;			// used for mass combats

} ADMPplayer;

/*********************************************************************/
typedef struct ADMPmodifiers {
	char	c_message[40];					// the message to display
	sint	i_idFollows;					// which ID does it follow to finish on
	sint	i_noRounds;						/* how many rounds until it lasts */
	sint	i_whom[MAX_MEMBERS];			/* whom it effects */
	sint	i_data[5][3];					/* the value, type, effects-type */
} ADMPmodifiers;

/*********************************************************************/
typedef struct ADMPtriggers {
	char	c_message[60];		/* whats the message */
	sint	i_noRounds;			/* how many rounds until it happens */
	sint	i_display;			/* should it be displayed every round */
	char	c_every[10];		/* every X or d? rnds this message to be displayed */
} ADMPtriggers;

/*********************************************************************/
typedef struct ADMPgroup {
	char	c_description[30];
	char	i_active;
	sint	i_members[MAX_MEMBERS+2];
} ADMPgroup;

/*********************************************************************/
typedef struct ADMPdamage {
	char	c_description[32];	// what's it called
	sint	i_initiatorID;			// who did the auto-damage
	sint	i_whom[MAX_MEMBERS+2];		// who 'gets' it
	char	c_damage[32];			// what damage to do .. either a dice roll or a series of numbers
	sint	i_noRounds;				// how may rounds to last
	sint	i_doneRounds;			// how may rounds done
	sint	i_type;					// what type of damage to do
	ADMPflags2	flags;			// any flags - like was it done this round, follow initiator's init etc
} ADMPdamage;

/*********************************************************************/
typedef struct ADMPobject {
	uchar	i_id;
	char  c_description[MAX_OBJECTDESC];
	char	c_iconFile[60];			// the icon to associate with it
	sint  i_width, i_height;
} ADMPobject;

/*********************************************************************/
typedef struct ADMPquickmods {
	sint	i_id;
	sint	i_effects[MAX_QUICKMODTYPES][2];			// BAB, AC, Dam, HP, Init, All Saves [effects-type, value], Miss%, SR
} ADMPquickmods;

/*********************************************************************/
typedef struct ADMPsystem {
	char			c_dummy;
	sint			i_roundCount;
	sint			i_whenBleed;							/* when to bleed, at INIT or end of rnd */
	sint			i_xpAllocate;							/* how to do XP calculations */

	sint			i_editID;
	sint			i_quickEditID;
	sint			i_actionInitID;
	sint			i_actionRecvID;
	sint			i_actionSelected;
	sint			i_actionWeaponSelected;

	sint			i_roundsSave;							/* every X rounds save the player/monster data */

	sint			i_diceSystem;							/* d20 or d100 */
	sint			i_initSystem;							/* d20 or d100 */

	char			c_partyFilename[44];
	char			c_monstFilename[44];
	char			c_mapFilename[44];

	sint			i_idList[MAX_IDLIST][MAX_MEMBERS+2];

	ADMPflags3	flags;										// 16 of these

	sint			i_doGroupInitiatives;				/* do groups as ONE initiative roll */
	sint			i_attackGroup;							/* do all attacks at once or separate them */
	sint			i_attackSeparation[MAX_ATTACKS]; /* base INIT modifiers for each attack */

	ADMPmodifiers	system_mods[MAX_MODIFIERS];		// char, 4 * int
	ADMPmodifiers	action_mods[MAX_MODIFIERS];		// char, 4 * int
	ADMPtriggers	action_msgs[MAX_TRIGGERS];			// char, 2 * int
	ADMPgroup		groups[MAX_GROUPS];					// char, int, int[MM+2]
	ADMPdamage		auto_damage[MAX_AUTODAMAGE];		// char, int, int[MM+2], char, 3 * int, 8 * int
	ADMPobject		objects[MAX_OBJECTS];
	ADMPquickmods	quickmods[MAX_MEMBERS+1];		// quick modifiers - BAB, AC, Dam, HP, Init, All Saves

	float			f_version;

} ADMPsystem;

/*********************************************************************/
typedef struct ADMPcombatmods {
	char *c_message;
	sint   i_modifications[2][2];
} ADMPcombatmods;

/*********************************************************************/
typedef struct ADMPadjustments {
	char	*title;
	sint	i_type;
	sint	i_diceSystem;
} ADMPadjustments;

/*********************************************************************/
typedef struct ADMPspellslots {
	sint	i_type;
	sint	i_level;
	char	c_spellslots[9][5];
} ADMPspellslots;

/*********************************************************************/
typedef struct ADMPspells {
	sint	i_type;
	sint	i_level;
	char	c_spell[110];
	sint	i_attack;
	sint	i_defend;
	sint	i_used;
} ADMPspells;

/*********************************************************************/
typedef struct treasureTblData {
   unsigned char table_id, start_roll, end_roll;
   char *data;
} treasureTblData;

#endif
