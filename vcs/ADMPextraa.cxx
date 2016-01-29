/**********************************************************************
 *    Copyright Torquil Gault 2005+
 * #       This program is free software; you can redistribute it and/or
 * #       modify it under the terms of the GNU General Public License
 * #       as published by the Free Software Foundation; either version 2
 * #       of the License, or (at your option) any later version.
 * #
 * #       This program is distributed in the hope that it will be useful,
 * #       but WITHOUT ANY WARRANTY; without even the implied warranty of
 * #       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * #       GNU General Public License for more details.
 * #
 * #       You should have received a copy of the GNU General Public License
 * #       along with this program; if not, write to the Free Software
 * #       Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * #
 * #
 * ###############################################################################
 **********************************************************************/

/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef VISUALC
#include <dirent.h>
#include <unistd.h>
#else
#include <windows.h>
#include <direct.h>
#include <stdlib.h>
#define strncasecmp strnicmp
#endif

#include "pDBlibrary.h"
#include "gridMap.h"

/******************************************************************************/
#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/fl_show_colormap.H>

#include "ADMPdata.h"
#include "ADMPmerp.h"
#include "ADMPexternals.h"

/****************************************************************************/
#ifdef WINDOWS
#ifdef VISUALC
#define S_IRUSR 00400
#define S_IWUSR 00200
#endif
#define S_IRGRP 00040
#define S_IROTH 00004
void fchmod(int f, int m) {
}
#endif

/****************************************************************************/
int seed1, seed2, seed3;

ADMPsystem config;
ADMPplayer  players[MAX_MEMBERS+4], qkmonsters[MAX_QKMONSTERS+2];

//ADMPplayer  sm[80];

char identifiers[] = "01234567890123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char mybuf1[2048], mybuf2[2048];

//int i,j,k;

int i_EORanswer, i_WeaponUsed, i_prevWeaponEditted, i_monsterType, i_monsterCount, i_monsterNoteID, i_srdMonsterID;
int qkMonster, qkMonsterWeapon, initiatorSelected;

float ADMPversion;

FILE *logfile=NULL, *openf=NULL;

Fl_Input *w_Initiatives[MAX_MEMBERS];
Fl_Choice *w_InitiativesSelected[MAX_MEMBERS];
Fl_Input *i_HealMonstName[MAX_HEALMONSTERS], *i_HealMonstValue[MAX_HEALMONSTERS];

Fl_Double_Window *a_EORWindow=(Fl_Double_Window *)0;
Fl_Browser *a_EORMessageList=(Fl_Browser *)0;
Fl_Button *a_EORMessageYes=(Fl_Button *)0;
Fl_Button *a_EORMessageNo=(Fl_Button *)0;
Fl_Button *AYSButton[3]={NULL,NULL,NULL};

ADMPcombatmods combatmods[] = {
{"Attacker flanking defender", {{+2,0},{+0,0}}},
{"Attacker on higher ground", {{+1,0},{+0,0}}},
{"Attacker prone", {{-4,0},{+0,0}}},
{"Attacker invisible", {{+2,0},{+2,0}}},
{"Defender kneeling", {{-2,1},{-2,1}}},
{"Defender prone", {{-4,1},{-4,1}}},
{"Defender stunned/climbing", {{-2,1},{+2,1}}},
{"Defender surprised/flat-footed", {{+0,1},{+2,1}}},
{"Defender running", {{+0,1},{-2,1}}},
{"Defender pinned", {{-4,1},{-4,1}}},
{"Cover 25%", {{+2,1},{2,1}}}, 				//|+1,2
{"Cover 50%", {{+4,1},{4,1}}}, 				//|+2,2}},
{"Cover 75%", {{+7,1},{7,1}}}, 				//|+3,2}},
{"Cover 90%", {{+10,1},{10,1}}},
{"", {{+0,0},{0,0}}}};  			//|+4,2}},

ADMPadjustments adjustments[] = {
{"None", 0, DICE_D20},
{"To Hit", MOD_BAB, DICE_D20},
{"Armor Class", MOD_AC, DICE_D20},
{"All Saves", MOD_SAVE, DICE_D20},
{"Damage", MOD_DAMAGE, DICE_D20},
{"Initiative", MOD_INIT, DICE_D20},
{"Hit Points", MOD_HP, DICE_D20},
{"Skill Checks", MOD_SKILL, DICE_D20},
{"Save Fortitude", MOD_SAVE_FORTITUDE, DICE_D20},
{"Save Reflex", MOD_SAVE_REFLEX, DICE_D20},
{"Save Will", MOD_SAVE_WILL, DICE_D20},
{"Miss Chance %", MOD_MISS_CHANCE, DICE_D20},
{"Spell Resistance", MOD_SPELL_RESISTANCE, DICE_D20},
{"None", 0, DICE_MERP},
{"OB", MOD_BAB, DICE_MERP},
{"DB", MOD_AC, DICE_MERP},
{"All RR", MOD_SAVE, DICE_MERP},
{"Damage", MOD_DAMAGE, DICE_MERP},
{"M&&M", MOD_INIT, DICE_MERP},
{"Hit Points", MOD_HP, DICE_MERP},
{"Skill Checks", MOD_SKILL, DICE_MERP},
{"None", 0, DICE_RMS},
{"OB", MOD_BAB, DICE_RMS},
{"DB", MOD_AC, DICE_RMS},
{"All RR", MOD_SAVE, DICE_RMS},
{"Damage", MOD_DAMAGE, DICE_RMS},
{"M&M", MOD_MOVE, DICE_RMS},
{"Hit Points", MOD_HP, DICE_RMS},
{"Skill Checks", MOD_SKILL, DICE_RMS},
{"", -1, -1}
};

#define MAX_ADJEFFECTTYPES 11		// this must match how many type are below
char *adjusteffecttype[] = {"None", "Enhancement", "Morale", "Luck", "Haste", "Armor", "Shield", "Deflection", "Dodge", "Other", "Natural"};

int xp_cr[21][21] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,300,600,900,1350,1800,2700,3600,5400,7200,10800,0,0,0,0,0,0,0,0,0,0},
{0,300,600,900,1350,1800,2700,3600,5400,7200,10800,0,0,0,0,0,0,0,0,0,0},
{0,300,600,900,1350,1800,2700,3600,5400,7200,10800,0,0,0,0,0,0,0,0,0,0},
{0,300,600,800,1200,1600,2400,3200,4800,6400,9600,12800,0,0,0,0,0,0,0,0,0},
{0,300,500,750,1000,1500,2250,3000,4500,6000,9000,12000,18000,0,0,0,0,0,0,0,0},
{0,300,450,600,900,1200,1800,2700,3600,5400,7200,10800,14400,21600,0,0,0,0,0,0,0},
{0,263,394,525,700,1050,1400,2100,3150,4200,6300,8400,12600,16800,25200,0,0,0,0,0,0},
{0,200,300,450,600,800,1200,1600,2400,3600,4800,7200,9600,14400,19200,28800,0,0,0,0,0},
{0,0,225,338,506,675,900,1350,1800,2700,4050,5400,8100,10800,16200,21600,32400,0,0,0,0},
{0,0,0,250,375,563,750,1000,1500,2000,3000,4500,6000,9000,12000,18000,24000,36000,0,0,0},
{0,0,0,0,275,413,619,825,1100,1650,2200,3300,4950,6600,9900,13200,19800,26400,39600,0,0},
{0,0,0,0,0,300,450,675,900,1200,1800,2400,3600,5400,7200,10800,14400,21600,28800,43200,0},
{0,0,0,0,0,0,325,488,731,975,1300,1950,2600,3900,5850,7800,11700,15600,23400,31200,46800},
{0,0,0,0,0,0,0,350,525,788,1050,1400,2100,2800,4200,6300,8400,12600,16800,25200,33600},
{0,0,0,0,0,0,0,0,375,563,844,1125,1500,2250,3000,4500,6750,9000,13500,18000,27000},
{0,0,0,0,0,0,0,0,0,400,600,900,1200,1600,2400,3200,4800,7200,9600,14400,19200},
{0,0,0,0,0,0,0,0,0,0,425,638,956,1275,1700,2550,3400,5100,7650,10200,15300},
{0,0,0,0,0,0,0,0,0,0,0,450,675,1013,1350,1800,2700,3600,5400,8100,10800},
{0,0,0,0,0,0,0,0,0,0,0,475,713,1069,1425,1900,2850,3800,5700,8550,0},
{0,0,0,0,0,0,0,0,0,0,0,500,750,1000,1500,2000,3000,4000,6000,0,0}};

ADMPweapon stdweapons[MAX_STDWEAPONS+2];

char *dam_reduct_types[] = { "None", "Magic Weapon", "Any", "Adamantine", "Bludgeoning", "Chaotic",
							"Cold Iron", "Epic", "Evil", "Good", "Lawful", "Magic", "Silver", "Slashing"};

Fl_Text_Buffer *notes_buffer, *edit_notes_buffer, *detailed_buffer[2], *treasure_buffer[2];

int adjustValues[5][3], prev_part_selected;

char systemDir[256];

char *playerFlagTypes[] = {"Stabilised", "Disabled", "Ignore Crits", "Auto Stablise", "Evasion", "NPC", "Invisible", "Viewed", "Ignore Bleeding", "Ignore Stun", NULL};

char directorySep[2] = "/";

	// if you change this, update the code in initialiseSystem
char *actionTypes[] = {"Melee/Missile", "Spell - Damage", "Spell - WILL Save",
				"Spell - REF Save", "Spell - FORT Save", "Spell - Touch Attk", "Spell - Ranged Touch",
				"Heal/Stabilise", "Turning", "Skill Check", NULL};

char prevHtmlPage[5][256];
int htmlLevel = -1;

char *environment[] = {" Any", "A chaos-aligned plane", "A chaotic-aligned plane", "A chaotic evil-aligned plane", "A chaotic good-aligned plane",
"A evil-aligned plane", "A good-aligned plane.", "A lawful-aligned plane", "A lawful evil-aligned plane", "A lawful good-aligned plane",
"An evil-aligned plane", "Any", "Any good-aligned plane", "Any land and underground", "Cold aquatic",
"Cold desert", "Cold forests", "Cold hills", "Cold marshes", "Cold mountains",
"Cold plains", "Elemental Plane of Air", "Elemental Plane of Earth", "Elemental Plane of Fire",
"Elemental Plane of Water", "Ethereal Plane", "Ever-Changing Chaos of Limbo", "Plane of Shadow", "Positive Energy Plane",
"Temperate aquatic", "Temperate deserts", "Temperate forests", "Temperate hills", "Temperate marshes",
"Temperate mountains", "Temperate plains", "Underground", "Warm aquatic", "Warm deserts",
"Warm forests", "Warm hills", "Warm marshes", "Warm mountains", "Warm plains", NULL};

char iconSelected[128];

#define MAX_ICONS		2048
Fl_Image *playerIcons[MAX_MEMBERS+2], *objectIcons[MAX_OBJECTS+2];
Fl_Image *pngIcons[MAX_ICONS], *jpgIcons[MAX_ICONS], *selectIcons[MAX_ICONS];
Fl_Button *buttonIcons[MAX_ICONS];

int i_spellEntries[130];

Fl_Menu_Button *gridPopupMenu = NULL, *initPopupMenu = NULL;

Fl_Button *colorSelector[16];

ADMPspellslots	spellslots[MAX_SPELLSLOTS+2];
ADMPspells spells[MAX_SPELLS+2];

char *popMenuItems[] = {"Do an Action",
		"_Move Players in order here",
		"Unhide this monster or player",
		"Hide this monster or player",
		"_Centre BOTH Maps here",
		"_Remove this from map",
		"_Remove && disable this from map",
		"Move all Players here",
		"_Move all Monsters here",
		"Move all NEW monsters here",
		"_Add NEW monsters here in a Group",
		"_Add,Upd,Delete an object or note",
		"Disable this monster or player",
		"Enable this monster or player",
		"_Mark as having done an action",
		"_Do Mass Combat",
		"_Charge a spell",
		"Load a missile weapon",
		"_Quick Edit",
		"Centre DM Map on this creature",
		NULL};

Fl_Output *quickmodsName[MAX_QUICKMODIFIERS];
Fl_Input  *quickmodsData[MAX_QUICKMODIFIERS][MAX_QUICKMODTYPES];

/******************************************************************************/
extern Fl_Menu_Item races[];
extern Fl_Menu_Item classes[];
extern Fl_Double_Window *a_WeaponWindow, *a_Exit;
extern gridMap *combatGridMap, *externalGridMap;
extern Fl_Browser *d1_CTDRList1, *d1_CTDRList2, *d1_CTDRList3, *d1_CTDRList4, *d1_CTDRList5, *d1_CTDRList6, *d1_CTDRList7, *d1_CTDRList8;

extern char d100TableId[MAX_D100TABLES][3], *d100TableMem[MAX_D100TABLES];

extern void doDiceSystem(int );

/******************************************************************************/
extern void doD100WindowSetup(int );
extern char *getD100Table(char *);

/******************************************************************************/
void setCombatDisplay(int );
void doSystemAlert(char *);
int doAreYouSure(char *);
void saveAllData();
int parseDice(char *dice); //, int *mult, int *die, int *plus);
int parseCritical(char *crit, int dice, int *from, int *to, int *mult);
void loadAllData();
void doInitiativeAction(int );
int getRND(int );
int getHPs(int );
int getHPpercentage(int );
void actionQkMonsters(int );
int doEndOfRoundMessages(int );
void init16();
int getAdjustment(int, int);
void doOtherAction(int );
void calcCombatMods(int );
void writeLog(char *);
void mytolower(char *);
int whichChecked(Fl_Check_Browser *);
void doAutoDamageAction(int );
int calcAutoDamage(int , int);
int calcAction(int );
int getMaxHPs(int );
void reloadNames(int );
int getWeaponAttackBonus(int , int );
void setSystemFlag(int );
void doTriggerAction(int );
void doAdjustmentAction(int );
void loadStdModifiers();
void rollRNDDice();
void qkMonsterAction(int );
int writeAllPlayerData(char *);
int writeAllMonsterData(char *);
int writeAllStdMonsterData(char *);
int writeAllSRDMonsterData(char *);
int readAllPlayerData(char *);
int readAllMonsterData(char *, ADMPplayer *);
int readAllStdMonsterData(char *);
void convertToVersion();
void loadMonsterDescription(char *);
void loadSRDspellEntries(char *);
int readAllStdWeaponData();
int writeSystemData(char *);
int readSystemData(char *);
void doNotesAction(int, int);
void doNotesAction(int);
int gridMapEventHandler();
int tileMapEventHandler();
void doMapFileAction(int);
void loadAllIconPictures(char *, int);
void selectIconUsed();
void setWindowTitles();
void doIconAction(int );
void cb_initPopupMenu(Fl_Widget* , void* );
void selectQkAddEditWeapon(int );
void qkHealAction(int );
void doHealMonsters(int );
int isDead(int );
void setOtherActionDescription(int );
void doGroupAction(int );
void setScreenSize();
int isDefenderShown(int );
void doDisableAction(int );
int doQuickMods(int , int , int );
void doQuickEdit(int );

/******************************************************************************/
int getBrowserSelected(Fl_Browser *b) {
	for (int n=b->size(); n>0; n--) {
		if (b->selected(n) == 1) { return n; }
	}
	return -1;
}

/******************************************************************************/
static void cb_colorSelector(Fl_Button *b, void *) {
int i=0, n=0;
Fl_Color c;

	n = Fl::event_button();

	for (i=0; i<16; i++) {
		if (b == colorSelector[i]) {
			if (n == 1) {		// color selected
				combatGridMap->setActiveColor(i);
				return;
			} else {				// color chooser
				c = combatGridMap->getColorMap(i);
				c = fl_show_colormap(c);
				combatGridMap->setColorMap(i,c);
				externalGridMap->setColorMap(i,c);
				b->color(c);
				combatGridMap->repaint();
				externalGridMap->repaint();
				return;
			}
		}
	}

	combatGridMap->setActiveColor(1);
}

/******************************************************************************/
void setIconImage(Fl_Image *i, char *fname, char itype) {

//printf("sII: %d %s %c\n", i, fname, itype);
	if (i != NULL) { delete i; }

	if (itype == 'P') {
		i = new Fl_PNG_Image(fname);
	} else {
		i = new Fl_JPEG_Image(fname);
	}
}

/******************************************************************************/
char *mystrcasestr(const char *s1, const char *s2) {
    char *p1, *p2;

    if (*s2 == '\0') { /* an empty s2 */
        return((char *)s1);
    }

    while (1) {
        for ( ; (*s1 != '\0') && (tolower(*s1) != tolower(*s2)); s1++);
        if (*s1 == '\0') {
            return(NULL);
        }
        /* found first character of s2, see if the rest matches */
        p1 = (char *)s1;	p2 = (char *)s2;
        for (++p1, ++p2; tolower(*p1) == tolower(*p2); ++p1, ++p2) {
            if (*p1 == '\0') { /* both strings ended together */
                return((char *)s1);
            }
        }
        if (*p2 == '\0') { /* second string ended, a match */
            break;
        }
        /* didn't find a match here, try starting at next character in s1 */
        s1++;
    }
    return((char *)s1);
}

/******************************************************************************/
void initialiseSystem(int argc, char **argv) {
int i=0, j;
struct tm *tp;
time_t t;

	init16();

#ifdef WINDOWS
	strcpy(directorySep, "\\");
#else
	strcpy(directorySep, "/");
	umask(000);
#endif

	getcwd(systemDir, 255); strcat(systemDir, directorySep);		// get the current working directory

	i = 0;
	while (systemDir[i] != '\0') {
		if (systemDir[i] == '\\') { systemDir[i] = '/'; }
		i++;
	}

	printf("System Directory = %s\n", systemDir);

	ADMPversion = 2.10;
//	a_CMessage->value("Version 1.61\nCopyright Torquil Gault 2005+\nPortions copyright Wizards of the Coast (see the Open Gaming Licence)");

	a_TMain->value(a_TCombat);
	a_OTabs->value(a_OTAutoDamage);

	setWindowTitles();

	setCombatDisplay(0);
	a_CBInitiators->textsize(12);
	a_CBActionType->textsize(13);
	a_CTAttacksLeft->textsize(24);
	d1_CombatAttacksLeft->textsize(24);
	a_IActions->textsize(13);
	a_CTACBreakdown->textsize(10);
	a_CTHelp->labelsize(20);
	a_ODRList1->textsize(14); a_ODRList2->textsize(14); a_ODRList3->textsize(14); a_ODRList4->textsize(14);
	a_ODRList5->textsize(14); a_ODRList6->textsize(14); a_ODRList7->textsize(14); a_ODRList8->textsize(14);
	a_CTWeaponDetails->textsize(10);
	aSys_flags->textsize(10);
	a_OStatusList->textsize(12);
	aGN_NameList1->textsize(14); aGN_NameList2->textsize(14); aGN_NameList3->textsize(14);
	aEdit_Notes->textsize(12);
	a_EText->textsize(16);
	aLF_Logfile->textsize(10);
	aEdit_Flags->textsize(11);
	d1_ActionType->textsize(16);
	//a_CTCombatMods->textsize(11);

		// blank everything out just incase ..
	memset(&players[0].c_name[0], '\0', sizeof(ADMPplayer)*MAX_MEMBERS);
	memset(&qkmonsters[0].c_name[0], '\0', sizeof(ADMPplayer)*MAX_QKMONSTERS+2);
	memset(&config.c_dummy, '\0', sizeof(ADMPsystem));
	memset(&stdweapons[0].c_available, '\0', sizeof(ADMPweapon) * MAX_STDWEAPONS);

	combatGridMap->getGridTile()->setObjectData(config.objects);

	doQuickMods(-2, 0, 0);		// setup the quick mods screen
	doQuickMods(-1, 0, 0);		// reset the quick mods data

	doDiceSystem(-2);		// setup d100 stuff

	loadAllData();

	doQuickMods(0, 0, 0);		// rerefresh the quick mods screen

	sprintf(mybuf2, "%d", config.i_roundCount); aSys_Rounds->value(mybuf2);
	aSys_Bleeding->value(config.i_whenBleed);
	//aSys_XPAllocation->value(config.i_xpAllocate);
	//aSys_GroupInitiatives->value(config.i_doGroupInitiatives);
	//aSys_MultipleAttacks->value(config.i_attackGroup);
	//sprintf(mybuf2, "%d", config.); aSys_AttkSep1->value(config.|);
	//sprintf(mybuf2, "%d", config.); aSys_AttkSep2->value(config.|);
	//sprintf(mybuf2, "%d", config.); aSys_AttkSep3->value(config.|);
	//sprintf(mybuf2, "%d", config.); aSys_AttkSep4->value(config.|);
	//sprintf(mybuf2, "%d", config.); aSys_AttkSep5->value(config.|);
	//sprintf(mybuf2, "%d", config.); aSys_AttkSep6->value(config.|);
	sprintf(mybuf2, "%d", config.i_roundsSave); aSys_saveRounds->value(mybuf2);
	aSys_playerFilename->value(config.c_partyFilename);
	aSys_monsterFilename->value(config.c_monstFilename);
	aSys_mapFilename->value(config.c_mapFilename);
	sprintf(mybuf2, "%.2f", config.f_version); aSys_Version->value(mybuf2);

	for (i=getRND(20); i>0; i--) { j = getRND(100); }

	for (i=0; i<MAX_MODIFIERS; i++) {
		if (config.system_mods[i].c_message[0] == '\0') { sprintf(config.system_mods[i].c_message, "-- empty slot %d", i); }
		if (config.action_mods[i].c_message[0] == '\0') { sprintf(config.action_mods[i].c_message, "-- empty slot %d", i); }
		a_OTAdjustSystemList->add(config.system_mods[i].c_message);
	}

	for (i=0; ; i++) {
		if (combatmods[i].c_message[0] == '\0') { break; }
		a_CTCombatMods->add(combatmods[i].c_message);
	}

	i=0;
	while (adjustments[i].i_diceSystem != -1) {
		if (adjustments[i].i_diceSystem == config.i_diceSystem) {
			a_OTAdjustType1->add(adjustments[i].title);
			a_OTAdjustType2->add(adjustments[i].title);
			a_OTAdjustType3->add(adjustments[i].title);
			a_OTAdjustType4->add(adjustments[i].title);
			a_OTAdjustType5->add(adjustments[i].title);
		}
		i++;
	}
	for (i=0; i<MAX_ADJEFFECTTYPES; i++) {
		a_OTAdjustEffectsType1->add(adjusteffecttype[i]);
		a_OTAdjustEffectsType2->add(adjusteffecttype[i]);
		a_OTAdjustEffectsType3->add(adjusteffecttype[i]);
		a_OTAdjustEffectsType4->add(adjusteffecttype[i]);
		a_OTAdjustEffectsType5->add(adjusteffecttype[i]);
	}
	aEdit_Flags->clear();
	for (i=0; playerFlagTypes[i] != NULL; i++) {
		aEdit_Flags->add(playerFlagTypes[i]);
	}
	for (i=0; ; i++) {
		if (environment[i] == NULL) { break; }
		a_EdtQkMonCREnvironment->add(environment[i]);
	}
	a_EdtQkMonCREnvironment->value(0);

	a_OTTriggerList->clear();
	for (i=0; i<MAX_TRIGGERS; i++) {
		a_OTTriggerList->add(config.action_msgs[i].c_message);
	}
	a_OTAdjustList->clear();
	for (i=0; i<MAX_MODIFIERS; i++) {
		a_OTAdjustList->add(config.action_mods[i].c_message);
	}

	a_CBActionType->clear();
	for (i=0; actionTypes[i] != NULL; i++) {
		a_CBActionType->add(actionTypes[i]);
	}

	if (config.flags.f_logfile != 0) {
		if (time(&t) != -1) {
			tp = localtime(&t);
			sprintf(mybuf1, "ADMP Started (%2.2d/%2.2d/%4.4d %2.2d:%2.2d) in %s\n", tp->tm_mday, tp->tm_mon+1, tp->tm_year+1900, tp->tm_hour, tp->tm_min, systemDir);
			writeLog("       ********************");
			writeLog(mybuf1);
		}
	}

	for (i=0; i<14; i++) {
		aEdit_DamReductionType->add(dam_reduct_types[i]);
		aQkAdd_DamReductionType->add(dam_reduct_types[i]);
	}

	notes_buffer = new Fl_Text_Buffer(); a_NotesArea->buffer(notes_buffer);

	edit_notes_buffer = new Fl_Text_Buffer(); aEdit_Notes->buffer(edit_notes_buffer);
	treasure_buffer[0] = new Fl_Text_Buffer(); aRT_Treasure->buffer(treasure_buffer[0]);
	treasure_buffer[1] = new Fl_Text_Buffer(); aRT_ItemList->buffer(treasure_buffer[1]);

	detailed_buffer[0] = new Fl_Text_Buffer(); a_EDInitiatorDetails2->buffer(detailed_buffer[0]);
	detailed_buffer[1] = new Fl_Text_Buffer(); a_EDDefenderDetails2->buffer(detailed_buffer[1]);

	sprintf(mybuf2, "%snotes.txt", systemDir);
	notes_buffer->loadfile(mybuf2);

	if (config.i_diceSystem == DICE_D20) {
		sprintf(mybuf2, "%ssrd/index.html", systemDir);
		if (a_SRDText->load(mybuf2) == -1) { sprintf(mybuf2, "%ssrd/readme.txt", systemDir); a_SRDText->load(mybuf2); }
	}

	sprintf(mybuf2, "%shelp.txt", systemDir);
	a_HelpList->load(mybuf2);

	doAutoDamageAction(0);

	if (strncasecmp(config.system_mods[0].c_message, "-- empty slot 0", 15) == 0) {
		if (config.i_diceSystem == DICE_D20) {
			loadStdModifiers();
		}
		doAdjustmentAction(9);		// refresh
	}

	doInitiativeAction(2); doInitiativeAction(3);

	doOtherAction(20);		// update the status tab

	setSystemFlag(0);

	prevHtmlPage[0][0] = '\0';

	doAreYouSure(NULL);

	rollRNDDice();

	if (config.i_diceSystem == DICE_D20) {
#ifdef VISUALC
		loadSRDspellEntries("srd\\spells");
#else
		loadSRDspellEntries("srd/spells");
#endif
	}

	fl_register_images();		// so that they show in the ICON selection window

	doIconAction(1);

	for (int y=0; y<2; y++) {
		for (int x=0; x<8; x++) {
			i = (y*8)+x;
//			colorSelector[i] = new Fl_Button(3+(x*25), (y*26)+396, 25, 25);
			colorSelector[i] = new Fl_Button(3+(x*25), (y*28)+436, 25, 25);
			colorSelector[i]->color(combatGridMap->getColorMap(i));
			colorSelector[i]->callback((Fl_Callback*)cb_colorSelector);
			a_CombatColorGroup->add(colorSelector[i]);
		}
	}
	colorSelector[0]->tooltip("Map main background color");
	colorSelector[1]->tooltip("Map grid line color or a Transparent background color (1)");
	colorSelector[2]->tooltip("Map Object/Notes color or a Transparent background color (2)");
	colorSelector[3]->tooltip("Map Player color or a Transparent background color (3)");
	colorSelector[4]->tooltip("Map Monster color or a Transparent background color (4)");
	colorSelector[5]->tooltip("Map background color #1 - Transparent (5)");
	colorSelector[6]->tooltip("Map background color #2 - Transparent (6)");
	colorSelector[7]->tooltip("Map background color #3 - Transparent (7)");

	colorSelector[8]->tooltip("Map line/solid color - Opaque (8)");
	colorSelector[9]->tooltip("Map line/solid color - Opaque (9)");
	colorSelector[10]->tooltip("Map line/solid color - Opaque (10)");
	colorSelector[11]->tooltip("Map line/solid color - Opaque (11)");
	colorSelector[12]->tooltip("Map line/solid color - Opaque (12)");
	colorSelector[13]->tooltip("Map line/solid color - Opaque (13)");
	colorSelector[14]->tooltip("DM line - Transparent to players, blocks LOS (14)");
	colorSelector[15]->tooltip("DM line - Transparent to players, blocks LOS (15)");

	a_CombatSpecialAction->add(" "); a_CombatSpecialAction->add("Mark all map as viewed");
	a_CombatSpecialAction->add("Clear Map");
	a_CombatSpecialAction->add("Mark current screen as viewed");
	a_CombatSpecialAction->add("Remove DEAD monsters from map");
	a_CombatSpecialAction->add("Remove && disable DEAD monsters from map");
	a_CombatSpecialAction->add("Remove ALL monsters from map");
	a_CombatSpecialAction->add("Mark ALL monsters as unviewed");
	a_CombatSpecialAction->add("Mark current screen as unviewed");
	a_CombatSpecialAction->add("Undo drawing action");
	a_CombatSpecialAction->add("Reload ALL icons");
	a_CombatSpecialAction->add("Switch to Layer0");
	a_CombatSpecialAction->add("Switch to Layer1");
	a_CombatSpecialAction->value(0);

	for (i=0; i<MAX_ICONS; i++) {
		pngIcons[i] = jpgIcons[i] = selectIcons[i] = NULL;
		buttonIcons[i] = NULL;
	}

	loadAllIconPictures("icons/player", 0);
	loadAllIconPictures("icons/monster", 1);
	loadAllIconPictures("icons/objects", 2);
	loadAllIconPictures("icons/animals", 3);
	loadAllIconPictures("icons/other", 4);

	initPopupMenu = new Fl_Menu_Button(100,100,200,200);
	initPopupMenu->type(Fl_Menu_Button::POPUP3);
	initPopupMenu->add("_Do an Action");
	initPopupMenu->add("_Hide or unhide this");
	initPopupMenu->add("Remove this from map");
	initPopupMenu->add("_Enable or disable this");
	initPopupMenu->add("Mark as having done an action");
	if (config.i_diceSystem != DICE_D20) {
		initPopupMenu->add(&popMenuItems[16][0]);
		initPopupMenu->add(&popMenuItems[17][0]);
	}
	initPopupMenu->add(&popMenuItems[18][0]);
	initPopupMenu->add(&popMenuItems[19][0]);
	initPopupMenu->callback(cb_initPopupMenu);

	qsl_castertype->add("Cleric");
	qsl_castertype->add("Wizard or Sorcerer");
	qsl_castertype->add("Druid");

	setWindowTitles();

	doHealMonsters(9);

	setOtherActionDescription(-1);

	a_OTDisableActionList->clear();
	a_OTDisableActionList->add("Disable selected");
	a_OTDisableActionList->add("Enable selected");
	a_OTDisableActionList->add("Remove from map");
	a_OTDisableActionList->add("Set as Hidden");
	a_OTDisableActionList->add("Set as Visible");
	a_OTDisableActionList->add("Delete selected");
	a_OTDisableActionList->add("Resequence IDs");

aEdit_SpecialActions->clear();
aEdit_SpecialActions->add("Delete"); aEdit_SpecialActions->add("Duplicate *1");
aEdit_SpecialActions->add("Duplicate *2"); aEdit_SpecialActions->add("Duplicate *4");
aEdit_SpecialActions->add("Add as a Standard Monster"); aEdit_SpecialActions->add("Resequence IDs");
aEdit_SpecialActions->add("Move to be a player");

#ifdef CYGWIN
	aSys_BackupFiles->deactivate();
#endif

}

/****************************************************************************/
void searchWeaponDetails(int pos, char type) {
	int a=0,i=0;

	if (stdweapons[0].c_description[0] == '\0') {
		if (config.f_version < 1.11) {
			sprintf(mybuf2, "%sweapon.dat", systemDir);
			if ((openf = fopen(mybuf2, "r")) != NULL) {
				fread(&stdweapons[0].c_available, sizeof(ADMPweapon) * MAX_STDWEAPONS, 1, openf);
				fclose(openf);
			} else {
				doSystemAlert("Unable to read the standard weapon file ... !!!");
				return;
			}
		} else {
			readAllStdWeaponData();
		}
	}
	a_WSearchList->clear();
	config.i_idList[ID_WSCH][a] = -1;
	if (type == 0) {
		for (i=0; i<MAX_STDWEAPONS; i++) {
			a_WSearchList->add(stdweapons[i].c_description);
			config.i_idList[ID_WSCH][a++] = i;
		}
	} else {
		for (i=56; i<MAX_STDWEAPONS; i++) {
			a_WSearchList->add(stdweapons[i].c_description);
			config.i_idList[ID_WSCH][a++] = i;
		}
		for (i=0; i<MAX_STDWEAPONS; i++) {
			if (stdweapons[i].c_attackType != type) {
				a_WSearchList->add(stdweapons[i].c_description);
				config.i_idList[ID_WSCH][a++] = i;
			}
		}
	}
	config.i_idList[ID_WSCH][a] = -1;
	i_WeaponUsed = pos;
	if (pos == 1) { i_prevWeaponEditted = -10; }
	if (pos == 2) { i_prevWeaponEditted = -11; }

	a_WeaponWindow->show();
}

/****************************************************************************/
void reloadNames(int type) {
	int i, j, k;
	char fmt[4];

	i=0;

	switch (type) {
		case 0:  aEdit_players->clear();
					aEdit_monsters->clear();
					aEdit_players->add("New Player");
					aEdit_monsters->add("New Monster");

					for (j=0; j<MAX_MEMBERS; j++) {
						config.i_idList[ID_EDIT][j] = -255;
					}
					config.i_idList[ID_EDIT][0] = -1;
					k=1;

					for (j=0; j<MAX_PLAYERS; j++) {
						if (players[j].c_name[0] != '\0' && players[j].i_hp[HP_MAX] > 0) {
							sprintf(mybuf1, "%s (%d%%)", players[j].c_name, getHPpercentage(j));
							aEdit_players->add(mybuf1);
							config.i_idList[ID_EDIT][k++] = j;
						}
					}

					k = MAX_PLAYERS;
					config.i_idList[ID_EDIT][k++] = -2;
					for (j=MAX_PLAYERS; j<MAX_MEMBERS; j++) {
						if (players[j].c_name[0] != '\0' && players[j].i_hp[HP_MAX] > 0) {
							if (aEdit_showEnabled->value() != 0) {
								if (players[j].flags.f_disabled == 0) {
									sprintf(mybuf1, "%s (%d%%)", players[j].c_name, getHPpercentage(j));
									aEdit_monsters->add(mybuf1);
									config.i_idList[ID_EDIT][k++] = j;
								}
							} else {
								sprintf(mybuf1, "%s (%d%%)", players[j].c_name, getHPpercentage(j));
								aEdit_monsters->add(mybuf1);
								config.i_idList[ID_EDIT][k++] = j;
							}
						}
					}
					break;

		case 1:
					a_CBInitiators->clear();
#ifdef VISUALC
					for (i=0; i<MAX_MEMBERS; i++) {
#else
					for (int i=0; i<MAX_MEMBERS; i++) {
#endif
						if (config.i_idList[ID_INIT][i] > -1) {
							mybuf2[0] = '\0'; fmt[0] = '\0';
							j = config.i_idList[ID_INIT][i];
							k = getHPs(j);
								// set the various identifiers, color etc
							if (players[j].i_doneAttacks > 0) { strcpy(fmt, "@B88@."); }
							if (players[j].i_stun > 0) { strcat(mybuf2, "S"); strcpy(fmt, "@B95@."); }
							if (k <= players[j].i_unconciousAt) { strcat(mybuf2, "U"); strcpy(fmt, "@B95@."); }
							if (players[j].i_inactive > 0) { strcat(mybuf2, "I"); strcpy(fmt, "@B95@."); }
//							if (getHPs(j) < -9) { strcat(mybuf2, "D"); }
							if (isDead(i) == 1) { strcat(mybuf2, "D"); }
							if (strlen(mybuf2) > 0) {
								sprintf(mybuf1, "%s%d%% %s (%d *%s %d:%d)", fmt, getHPpercentage(j), players[j].c_name, k, mybuf2, players[j].i_noAttacks, players[j].i_doneAttacks);
							} else {
								sprintf(mybuf1, "%s%d%% %s (%d %d:%d)", fmt, getHPpercentage(j), players[j].c_name, k, players[j].i_noAttacks, players[j].i_doneAttacks);
							}
							a_CBInitiators->add(mybuf1);
if (config.flags.f_debug != 0) { printf("rL: SL1 %d:%d (%s)\n", i, j, mybuf1); }
						}
					}
					a_CBInitiators->redraw();
					break;
		case 9:
					if (a_OTTriggerList->active() == 1) { doTriggerAction(9); }
					if (a_OTAdjustList->active() == 1) { doAdjustmentAction(9); }
					if (a_OTADList->active() == 1) { doAutoDamageAction(9); }
					break;
	}
}

/****************************************************************************/
void editPlayer(int pid) {
char mybuf[20];
int i=0, j=0, sid=0;

	if (pid < 0 || pid > (MAX_MEMBERS+2) || config.i_idList[ID_EDIT][pid] == -255) {
		return;
	}
	sid = aEdit_monsters->position();

if (config.flags.f_debug != 0) { printf("eP 1: %d:%d\n", pid, config.i_idList[ID_EDIT][pid]); }

		// check to see if it's an ADD NEW request
	if (config.i_idList[ID_EDIT][pid] == -1) {
		  for (pid=0; pid<MAX_PLAYERS; pid++) {
				 if (players[pid].c_name[0] == '\0' && players[pid].i_hp[HP_MAX] == 0)
						break;
		  }	// did we find a empty slot
		 if (players[pid].c_name[0] != '\0' && players[pid].i_hp[HP_MAX] != 0)
				 return;
if (config.flags.f_debug != 0) { printf("adding new player %d\n", pid); }
		 		// set various defaults
		 players[pid].i_inGroup = -1;
		 players[pid].i_unconciousAt = -1;
		 aEdit_players->deactivate();
		 aEdit_monsters->deactivate();
		 players[pid].i_whomAttacked[0][0] = players[pid].i_whomAttacked[1][0] = players[pid].i_whomAttacked[2][0] = -1;
	} else if (config.i_idList[ID_EDIT][pid] == -2) {
		 for (pid=MAX_PLAYERS; pid<MAX_MEMBERS; pid++) {
				 if (players[pid].c_name[0] == '\0' && players[pid].i_hp[HP_MAX] == 0)
							break;
		 }	// did we find a empty slot
		 if (players[pid].c_name[0] != '\0' && players[pid].i_hp[HP_MAX] != 0)
				 return;
if (config.flags.f_debug != 0) { printf("adding new monster %d\n", pid); }
		 aEdit_SpecialActions->activate();
		  		// set various defaults
		 players[pid].i_inGroup = -1;
		 players[pid].i_unconciousAt = -1;
		 players[pid].flags.f_disabled = 0;
		 for (j=0; j<MAX_D20ROLLS; j++) {
			if (config.i_diceSystem == DICE_D20) {
				players[pid].i_d20Rolls[j] = getRND(20);
			} else {
				players[pid].i_d20Rolls[j] = getRND(100);
			}
			players[pid].i_whomAttacked[j][0] = -1;
		 }
		 aEdit_players->deactivate();
		 aEdit_monsters->deactivate();
	} else {
		if (pid < MAX_MEMBERS) {
			reloadNames(0);
			if (pid >= MAX_PLAYERS) {
				sprintf(mybuf1, "@B88@.%s", aEdit_monsters->text(pid-MAX_PLAYERS+1));
				aEdit_monsters->text(pid-MAX_PLAYERS+1, mybuf1);
			} else {
				sprintf(mybuf1, "@B88@.%s", aEdit_players->text(pid+1));
				aEdit_players->text(pid+1, mybuf1);
			}
			pid = config.i_idList[ID_EDIT][pid];
		}
if (config.flags.f_debug != 0) { printf("eP: 2: %d\n", i); }
	}

	if (pid >= MAX_PLAYERS && pid <= MAX_MEMBERS) {
		aEdit_SpecialActions->activate();
		aEdit_monsters->position(sid);
	} else {
		aEdit_SpecialActions->deactivate();
	}
	aEdit_SpecialActions->activate();

	aEdit_IconFilename->value(players[pid].c_iconFile);
	sprintf(mybuf, "%d", players[pid].i_mapX); aEdit_MapX->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_mapY); aEdit_MapY->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_reach); aEdit_Reach->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_space); aEdit_Space->value(mybuf);
	aEdit_Name->value(players[pid].c_name);
	aEdit_Race->value(players[pid].i_race);
	aEdit_Alignment->value(players[pid].i_alignment);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	aEdit_Class1->value(players[pid].i_classes[0]);
	aEdit_Class2->value(players[pid].i_classes[1]);
	aEdit_Class3->value(players[pid].i_classes[2]);
	aEdit_Class4->value(players[pid].i_classes[3]);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	sprintf(mybuf, "%d", players[pid].i_levels[0]); aEdit_Level1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_levels[1]); aEdit_Level2->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_levels[2]); aEdit_Level3->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_levels[3]); aEdit_Level4->value(mybuf);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	sprintf(mybuf, "%d", players[pid].i_hp[HP_MAX]); aEdit_HPMax->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_hp[HP_CUR]); aEdit_HPCurrent->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_hp[HP_NL]); aEdit_NonLethal->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_hp[HP_TMP]); aEdit_TempHP->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_hp[HP_ENH]); aEdit_EnhHP->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bleeding); aEdit_Bleeding->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_regeneration); aEdit_Regeneration->value(mybuf);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	sprintf(mybuf, "%d", players[pid].i_disabledAt); aEdit_Disabled->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_unconciousAt); aEdit_Unconcious->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_savingThrows[SAVE_FORTITUDE]); aEdit_SaveFort->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_savingThrows[SAVE_REFLEX]); aEdit_SaveReflex->value(mybuf);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	sprintf(mybuf, "%d", players[pid].i_savingThrows[SAVE_WISDOM]); aEdit_SaveWill->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_armorClass[AC_NORMAL]); aEdit_ACNormal->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_armorClass[AC_TOUCH]); aEdit_ACTouch->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_armorClass[AC_FLATFOOTED]); aEdit_ACFlatFoot->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_armorClassSplit[AC_SECTION_DEX]); aEdit_ACSecDex->value(mybuf);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	if (config.i_diceSystem == DICE_D20) {
		sprintf(mybuf, "%d", players[pid].i_armorClassSplit[AC_SECTION_SIZE]); aEdit_ACSecSize->value(mybuf);
		sprintf(mybuf, "%d", players[pid].i_armorClassSplit[AC_SECTION_DEFLECTION]); aEdit_ACSecDeflection->value(mybuf);
		sprintf(mybuf, "%d", players[pid].i_armorClassSplit[AC_SECTION_NATURAL]); aEdit_ACSecNatural->value(mybuf);
		sprintf(mybuf, "%d", players[pid].i_armorClassSplit[AC_SECTION_ARMOR]); aEdit_ACSecArmor->value(mybuf);
		sprintf(mybuf, "%d", players[pid].i_armorClassSplit[AC_SECTION_SHIELD]); aEdit_ACSecShield->value(mybuf);
		sprintf(mybuf, "%d", players[pid].i_armorClassSplit[AC_SECTION_DODGE]); aEdit_ACSecDodge->value(mybuf);
	} else {
		aEdit_ArmorWorn->value(players[pid].i_armorClassSplit[AC_SECTION_WORN]);
		aEdit_ArmorLegWorn->value(players[pid].i_armorClassSplit[AC_SECTION_LEG]);
		aEdit_ArmorArmWorn->value(players[pid].i_armorClassSplit[AC_SECTION_ARM]);
		aEdit_ArmorHelmWorn->value(players[pid].i_armorClassSplit[AC_SECTION_HELM]);
	}
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_MELEE][0]); aEdit_BABMelee1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_RANGED][0]); aEdit_BABRanged1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_GRAPPLE][0]); aEdit_BABGrapple1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_MELEE][1]); aEdit_BABMelee2->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_RANGED][1]); aEdit_BABRanged2->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_GRAPPLE][1]); aEdit_BABGrapple2->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_MELEE][2]); aEdit_BABMelee3->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_RANGED][2]); aEdit_BABRanged3->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_bab[BAB_GRAPPLE][2]); aEdit_BABGrapple3->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_initiative[0]); aEdit_InitBonus->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_initiative[1]); aEdit_InitRoll->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_speed); aEdit_Speed->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_inactive); aEdit_Inactive->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_stun); aEdit_Stun->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_noAttacks); aEdit_NoAttacks->value(mybuf);

	sprintf(mybuf, "%d", players[pid].i_armorClass[AC_NOPARRY]); aEdit_ACNoParry->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_savingThrows[SAVE_POISON]); aEdit_SavePoison->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_savingThrows[SAVE_DISEASE]); aEdit_SaveDisease->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_roundsUntil[ROUND_DEATH]); aEdit_RoundsDeathIn->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_roundsUntil[ROUND_SPELL_CHG]); aEdit_RoundsSpellChg->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_roundsUntil[ROUND_MISSILE_CHG]); aEdit_RoundsMissileChg->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_baseSpell); aEdit_BaseSpells->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_directedSpells); aEdit_DirectedSpells->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_noInGroup); aEdit_NoInGroup->value(mybuf);

		// add weapon stuff
	aEdit_WeaponSelector->activate(); aEdit_WeaponSelector->clear();
	for (i=0; i<6; i++) {
		if (players[pid].w_weapons[i].c_description[0] != '\0') {
			aEdit_WeaponSelector->add(players[pid].w_weapons[i].c_description);
		} else {
			sprintf(mybuf2, "Melee Empty Slot #%d", i); aEdit_WeaponSelector->add(mybuf2);
		}
	}
	for (i=6; i<MAX_WEAPONS; i++) {
		if (players[pid].w_weapons[i].c_description[0] != '\0') {
			aEdit_WeaponSelector->add(players[pid].w_weapons[i].c_description);
		} else {
			sprintf(mybuf2, "Ranged Empty Slot #%d", i); aEdit_WeaponSelector->add(mybuf2);
		}
	}
	i_prevWeaponEditted = -1;
	aEdit_WeaponAvailable->deactivate();
	aEdit_WeaponName->deactivate();
	aEdit_WeaponSearch->deactivate();
	aEdit_WeaponAttkBonus1->deactivate();
	aEdit_WeaponAttkBonus2->deactivate();
	aEdit_WeaponAttkBonus3->deactivate();
	aEdit_WeaponAttkBonus4->deactivate();
	aEdit_WeaponDamage->deactivate();
	aEdit_WeaponCritical->deactivate();
	aEdit_WeaponMagicBonus->deactivate();
	aEdit_WeaponRange->deactivate();
	aEdit_WeaponReach->deactivate();
	aEdit_WeaponNoAttacks->deactivate();
	aEdit_WeaponSpecialMessage->deactivate();
	aEdit_WeaponType->deactivate();
	aEdit_WeaponFumble->deactivate();
	aEdit_WeaponCritAdjustment->deactivate();
	aEdit_WeaponSize->deactivate();
	aEdit_WeaponAttackTable->deactivate();

	sprintf(mybuf, "%.1f", players[pid].f_challengeRating); aEdit_CRating->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_d20Rolls[0]); aEdit_d201->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_d20Rolls[1]); aEdit_d202->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_d20Rolls[2]); aEdit_d203->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_d20Rolls[3]); aEdit_d204->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_d20Rolls[4]); aEdit_d205->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_d20Rolls[5]); aEdit_d206->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_d20Rolls[6]); aEdit_d207->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[0]); aEdit_SpellDC0->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[1]); aEdit_SpellDC1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[2]); aEdit_SpellDC2->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[3]); aEdit_SpellDC3->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[4]); aEdit_SpellDC4->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[5]); aEdit_SpellDC5->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[6]); aEdit_SpellDC6->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[7]); aEdit_SpellDC7->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_spellDC[8]); aEdit_SpellDC8->value(mybuf);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	sprintf(mybuf, "%d", players[pid].i_spellFailure); aEdit_SpellFailure->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[0][0]); aEdit_StatsSTR0->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[1][0]); aEdit_StatsSTR1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[0][1]); aEdit_StatsDEX0->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[1][1]); aEdit_StatsDEX1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[0][2]); aEdit_StatsCON0->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[1][2]); aEdit_StatsCON1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[0][3]); aEdit_StatsINT0->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[1][3]); aEdit_StatsINT1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[0][4]); aEdit_StatsWIS0->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[1][4]); aEdit_StatsWIS1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[0][5]); aEdit_StatsCHA0->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_abilityStats[1][5]); aEdit_StatsCHA1->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_SEARCH]); aEdit_SkillSearch->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_SOH]); aEdit_SkillSOH->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_SPOT]); aEdit_SkillSpot->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_OPENLOCKS]); aEdit_SkillOLocks->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_MOVESILENTLY]); aEdit_SkillMoveSilently->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_LISTEN]); aEdit_SkillListen->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_HIDE]); aEdit_SkillHide->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_skills[SKILL_CONCENTRATION]); aEdit_SkillConcentration->value(mybuf);
if (config.flags.f_debug != 0) { printf("eP: 3: %d\n", i); }
	sprintf(mybuf, "%d", players[pid].i_spellResistance); aEdit_SpellResistance->value(mybuf);
	aEdit_DamReductionType->value(players[pid].i_damageReduction[0]);
	sprintf(mybuf, "%d", players[pid].i_damageReduction[1]); aEdit_DamReductionHP->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_damageReduction[2]); aEdit_DamReductionWeapon->value(mybuf);
	aEdit_Size->value(players[pid].i_size);
	sprintf(mybuf, "%d", players[pid].i_xp[MAX]); aEdit_XPCurr->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_xp[TMP]); aEdit_XPTemp->value(mybuf);
	sprintf(mybuf, "%d", players[pid].i_inGroup); aEdit_InGroup->value(mybuf);
	aEdit_HitDice->value(players[pid].c_hitDice);

	aEdit_Items->value(players[pid].c_items);

	sprintf(mybuf, "%d", players[pid].i_negateCrit); aEdit_NegateCritical->value(mybuf);

	aEdit_Flags->check_none();
	aEdit_Flags->checked(1, players[pid].flags.f_isStabilised);
	aEdit_Flags->checked(2, players[pid].flags.f_disabled);
	aEdit_Flags->checked(3, players[pid].flags.f_ignoreCriticals);
	aEdit_Flags->checked(4, players[pid].flags.f_autoStablise);
	aEdit_Flags->checked(5, players[pid].flags.f_evasion);
	aEdit_Flags->checked(6, players[pid].flags.f_npc);
	aEdit_Flags->checked(7, players[pid].flags.f_invisible);
	aEdit_Flags->checked(8, players[pid].flags.f_wasViewed);
	aEdit_Flags->checked(9, players[pid].flags.f_ignoreBleed);
	aEdit_Flags->checked(10, players[pid].flags.f_ignoreStun);

	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel0); aEdit_SpellSlotMax0->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel1); aEdit_SpellSlotMax1->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel2); aEdit_SpellSlotMax2->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel3); aEdit_SpellSlotMax3->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel4); aEdit_SpellSlotMax4->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel5); aEdit_SpellSlotMax5->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel6); aEdit_SpellSlotMax6->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel7); aEdit_SpellSlotMax7->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel8); aEdit_SpellSlotMax8->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_maxLevel9); aEdit_SpellSlotMax9->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel0); aEdit_SpellSlotCur0->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel1); aEdit_SpellSlotCur1->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel2); aEdit_SpellSlotCur2->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel3); aEdit_SpellSlotCur3->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel4); aEdit_SpellSlotCur4->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel5); aEdit_SpellSlotCur5->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel6); aEdit_SpellSlotCur6->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel7); aEdit_SpellSlotCur7->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel8); aEdit_SpellSlotCur8->value(mybuf1);
	sprintf(mybuf1, "%d", players[pid].spellsAvailable.i_curLevel9); aEdit_SpellSlotCur9->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistances[RESIST_FIRE]); aEdit_SpellResistanceFire1->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistancesUsed[RESIST_FIRE]); aEdit_SpellResistanceFire2->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistances[RESIST_ACID]); aEdit_SpellResistanceAcid1->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistancesUsed[RESIST_ACID]); aEdit_SpellResistanceAcid2->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistances[RESIST_COLD]); aEdit_SpellResistanceCold1->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistancesUsed[RESIST_COLD]); aEdit_SpellResistanceCold2->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistances[RESIST_ELEC]); aEdit_SpellResistanceElec1->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistancesUsed[RESIST_ELEC]); aEdit_SpellResistanceElec2->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistances[RESIST_SONIC]); aEdit_SpellResistanceSonic1->value(mybuf1);
sprintf(mybuf1, "%d", players[pid].i_resistancesUsed[RESIST_SONIC]); aEdit_SpellResistanceSonic2->value(mybuf1);


	config.i_editID = pid;

	if (config.flags.f_debug != 0) printf("Editting %d\n", pid);

//	aEdit_players->deactivate();
//	aEdit_monsters->deactivate();
	aEdt_Accept->activate();
	aEdt_Cancel->activate();
	aEdt_QkMonsterAdd->deactivate();
	aEdt_Tabs->activate();
	aEdt_Tabs->value(aEdt_Main);

//	sprintf(mybuf2, "%s%s.note", systemDir, players[pid].c_name);
//	edit_notes_buffer->loadfile(mybuf2);
	doNotesAction(1, pid);
}

/******************************************************************************/
void cancelEdit() {
	aEdit_players->activate();
	aEdit_monsters->activate();
	aEdt_Accept->deactivate();
	aEdt_QkMonsterAdd->activate();
	aEdt_Cancel->deactivate();
	aEdt_Tabs->deactivate();
	aEdit_SpecialActions->deactivate();
	a_EdtQkMonList->activate();
	a_EdtQkMonstSearch->activate();
	aEdit_AddQkMonsters->activate();
	aEdit_EditQkMonsters->activate();
	aEdit_SaveQkMonsters->activate();
	a_EdtQkMonCRSearch->activate();
	aEdit_QkMonstersWildSearch->activate();
	a_EdtQkMonAddCtr->activate();
	a_EdtQkMonstIconFilename->activate();
	config.i_editID = -1;
	reloadNames(0);
}

/******************************************************************************/
void savePlayer(int pid) {
char mybuf[40], ok=0;
int i,j,k;

	if (pid < 0 || pid > (MAX_MEMBERS+1)) {
		return;
	}

	strncpy(players[pid].c_name, aEdit_Name->value(), 29);
if (config.flags.f_debug != 0) printf("savePlayer %d = %s\n", pid, players[pid].c_name);
	if (pid != MAX_MEMBERS+1) {
		if (players[pid].c_name[2] == '-') {
			players[pid].c_name[0] = identifiers[pid];
		} else {
			sprintf(mybuf, "%c - %s", identifiers[pid], players[pid].c_name);
			strncpy(players[pid].c_name, mybuf, 29);
		}
	}
	players[pid].i_race = aEdit_Race->value();
	players[pid].i_alignment = aEdit_Alignment->value();
	players[pid].i_classes[0] = aEdit_Class1->value();
	players[pid].i_classes[1] = aEdit_Class2->value();
	players[pid].i_classes[2] = aEdit_Class3->value();
	players[pid].i_classes[3] = aEdit_Class4->value();
	players[pid].i_levels[0] = atoi(aEdit_Level1->value());
	players[pid].i_levels[1] = atoi(aEdit_Level2->value());
	players[pid].i_levels[2] = atoi(aEdit_Level3->value());
	players[pid].i_levels[3] = atoi(aEdit_Level4->value());
	players[pid].i_hp[HP_MAX] = atoi(aEdit_HPMax->value());
	players[pid].i_hp[HP_CUR] = atoi(aEdit_HPCurrent->value());
	players[pid].i_hp[HP_NL] = atoi(aEdit_NonLethal->value());
	players[pid].i_hp[HP_TMP] = atoi(aEdit_TempHP->value());
	players[pid].i_hp[HP_ENH] = atoi(aEdit_EnhHP->value());
	players[pid].i_bleeding = atoi(aEdit_Bleeding->value());
	players[pid].i_disabledAt = atoi(aEdit_Disabled->value());
	players[pid].i_unconciousAt = atoi(aEdit_Unconcious->value());
	players[pid].i_regeneration = atoi(aEdit_Regeneration->value());
	players[pid].i_savingThrows[SAVE_FORTITUDE] = atoi(aEdit_SaveFort->value());
	players[pid].i_savingThrows[SAVE_REFLEX] = atoi(aEdit_SaveReflex->value());
	players[pid].i_savingThrows[SAVE_WISDOM] = atoi(aEdit_SaveWill->value());
	players[pid].i_armorClass[AC_NORMAL] = atoi(aEdit_ACNormal->value());
	players[pid].i_armorClass[AC_TOUCH] = atoi(aEdit_ACTouch->value());
	players[pid].i_armorClass[AC_FLATFOOTED] = atoi(aEdit_ACFlatFoot->value());
	if (config.i_diceSystem == DICE_D20) {
		players[pid].i_armorClassSplit[AC_SECTION_DEX] = atoi(aEdit_ACSecDex->value());
		players[pid].i_armorClassSplit[AC_SECTION_SIZE] = atoi(aEdit_ACSecSize->value());
		players[pid].i_armorClassSplit[AC_SECTION_DEFLECTION] = atoi(aEdit_ACSecDeflection->value());
		players[pid].i_armorClassSplit[AC_SECTION_NATURAL] = atoi(aEdit_ACSecNatural->value());
		players[pid].i_armorClassSplit[AC_SECTION_ARMOR] = atoi(aEdit_ACSecArmor->value());
		players[pid].i_armorClassSplit[AC_SECTION_SHIELD] = atoi(aEdit_ACSecShield->value());
		players[pid].i_armorClassSplit[AC_SECTION_DODGE] = atoi(aEdit_ACSecDodge->value());
	} else {
		players[pid].i_armorClassSplit[AC_SECTION_WORN] = aEdit_ArmorWorn->value();
		players[pid].i_armorClassSplit[AC_SECTION_LEG] = aEdit_ArmorLegWorn->value();
		players[pid].i_armorClassSplit[AC_SECTION_ARM] = aEdit_ArmorArmWorn->value();
		players[pid].i_armorClassSplit[AC_SECTION_HELM] = aEdit_ArmorHelmWorn->value();
	}
	players[pid].i_bab[BAB_MELEE][0] = atoi(aEdit_BABMelee1->value());
	players[pid].i_bab[BAB_RANGED][0] = atoi(aEdit_BABRanged1->value());
	players[pid].i_bab[BAB_GRAPPLE][0] = atoi(aEdit_BABGrapple1->value());
	players[pid].i_bab[BAB_MELEE][1] = atoi(aEdit_BABMelee2->value());
	players[pid].i_bab[BAB_RANGED][1] = atoi(aEdit_BABRanged2->value());
	players[pid].i_bab[BAB_GRAPPLE][1] = atoi(aEdit_BABGrapple2->value());
	players[pid].i_bab[BAB_MELEE][2] = atoi(aEdit_BABMelee3->value());
	players[pid].i_bab[BAB_RANGED][2] = atoi(aEdit_BABRanged3->value());
	players[pid].i_bab[BAB_GRAPPLE][2] = atoi(aEdit_BABGrapple3->value());
	players[pid].i_initiative[0] = atoi(aEdit_InitBonus->value());
	players[pid].i_initiative[1] = atoi(aEdit_InitRoll->value());
	players[pid].i_speed = atoi(aEdit_Speed->value());
	players[pid].i_inactive = atoi(aEdit_Inactive->value());
	players[pid].i_stun = atoi(aEdit_Stun->value());
	players[pid].i_noAttacks = atoi(aEdit_NoAttacks->value());
	j = players[pid].i_mapX;
	k = players[pid].i_mapY;
	players[pid].i_mapX = atoi(aEdit_MapX->value());
	players[pid].i_mapY = atoi(aEdit_MapY->value());
	players[pid].i_armorClass[AC_NOPARRY] = atoi(aEdit_ACNoParry->value());
	players[pid].i_savingThrows[SAVE_POISON] = atoi(aEdit_SavePoison->value());
	players[pid].i_savingThrows[SAVE_DISEASE] = atoi(aEdit_SaveDisease->value());

	players[pid].i_roundsUntil[ROUND_DEATH] = atoi(aEdit_RoundsDeathIn->value());
	players[pid].i_roundsUntil[ROUND_SPELL_CHG] = atoi(aEdit_RoundsSpellChg->value());
	players[pid].i_roundsUntil[ROUND_MISSILE_CHG] = atoi(aEdit_RoundsMissileChg->value());
	players[pid].i_baseSpell = atoi(aEdit_BaseSpells->value());
	players[pid].i_directedSpells = atoi(aEdit_DirectedSpells->value());
	players[pid].i_noInGroup = atoi(aEdit_NoInGroup->value());
	
	if (i_prevWeaponEditted != -1) {		// save the previous weapon details
		aEdit_WeaponAvailable->value(players[pid].w_weapons[i_prevWeaponEditted].c_available);
		strncpy(players[pid].w_weapons[i_prevWeaponEditted].c_description, aEdit_WeaponName->value(), 29);
		players[pid].w_weapons[i_prevWeaponEditted].i_attackBonus[0] = atoi(aEdit_WeaponAttkBonus1->value());
		players[pid].w_weapons[i_prevWeaponEditted].i_attackBonus[1] = atoi(aEdit_WeaponAttkBonus2->value());
		players[pid].w_weapons[i_prevWeaponEditted].i_attackBonus[2] = atoi(aEdit_WeaponAttkBonus3->value());
		players[pid].w_weapons[i_prevWeaponEditted].i_attackBonus[3] = atoi(aEdit_WeaponAttkBonus4->value());
		strncpy(players[pid].w_weapons[i_prevWeaponEditted].c_damage, aEdit_WeaponDamage->value(), 19);
		strncpy(players[pid].w_weapons[i_prevWeaponEditted].c_critical, aEdit_WeaponCritical->value(), 19);
		players[pid].w_weapons[i_prevWeaponEditted].i_magicalBonus = atoi(aEdit_WeaponMagicBonus->value());
		players[pid].w_weapons[i_prevWeaponEditted].i_range = atoi(aEdit_WeaponRange->value());
		players[pid].w_weapons[i_prevWeaponEditted].i_reach = atoi(aEdit_WeaponReach->value());
		players[pid].w_weapons[i_prevWeaponEditted].i_noAttacks = atoi(aEdit_WeaponNoAttacks->value());
		strncpy(players[pid].w_weapons[i_prevWeaponEditted].c_message, aEdit_WeaponSpecialMessage->value(), 39);
		players[pid].w_weapons[i_prevWeaponEditted].c_message[39] = '\0';
		players[pid].w_weapons[i_prevWeaponEditted].c_description[29] = '\0';
		players[pid].w_weapons[i_prevWeaponEditted].c_damage[19] = '\0';
		players[pid].w_weapons[i_prevWeaponEditted].c_critical[19] = '\0';
		players[pid].w_weapons[i_prevWeaponEditted].c_attackType = aEdit_WeaponType->value();
		players[pid].w_weapons[i_prevWeaponEditted].i_fumble = atoi(aEdit_WeaponFumble->value());
		players[pid].w_weapons[i_prevWeaponEditted].i_critAdjust = aEdit_WeaponCritAdjustment->value();
		players[pid].w_weapons[i_prevWeaponEditted].i_size = aEdit_WeaponSize->value();
		strncpy(players[pid].w_weapons[i_prevWeaponEditted].c_table, aEdit_WeaponAttackTable->value(), 3);
		players[pid].w_weapons[i_prevWeaponEditted].c_table[3] = '\0';
	}

	players[pid].f_challengeRating = (float )atof(aEdit_CRating->value());
	players[pid].i_d20Rolls[0] = atoi(aEdit_d201->value());
	players[pid].i_d20Rolls[1] = atoi(aEdit_d202->value());
	players[pid].i_d20Rolls[2] = atoi(aEdit_d203->value());
	players[pid].i_d20Rolls[3] = atoi(aEdit_d204->value());
	players[pid].i_d20Rolls[4] = atoi(aEdit_d205->value());
	players[pid].i_d20Rolls[5] = atoi(aEdit_d206->value());
	players[pid].i_d20Rolls[6] = atoi(aEdit_d207->value());
	players[pid].i_spellDC[0] = atoi(aEdit_SpellDC0->value());
	players[pid].i_spellDC[1] = atoi(aEdit_SpellDC1->value());
	players[pid].i_spellDC[2] = atoi(aEdit_SpellDC2->value());
	players[pid].i_spellDC[3] = atoi(aEdit_SpellDC3->value());
	players[pid].i_spellDC[4] = atoi(aEdit_SpellDC4->value());
	players[pid].i_spellDC[5] = atoi(aEdit_SpellDC5->value());
	players[pid].i_spellDC[6] = atoi(aEdit_SpellDC6->value());
	players[pid].i_spellDC[7] = atoi(aEdit_SpellDC7->value());
	players[pid].i_spellDC[8] = atoi(aEdit_SpellDC8->value());
	players[pid].i_spellFailure = atoi(aEdit_SpellFailure->value());
	players[pid].i_abilityStats[0][0] = atoi(aEdit_StatsSTR0->value());
	players[pid].i_abilityStats[1][0] = atoi(aEdit_StatsSTR1->value());
	players[pid].i_abilityStats[0][1] = atoi(aEdit_StatsDEX0->value());
	players[pid].i_abilityStats[1][1] = atoi(aEdit_StatsDEX1->value());
	players[pid].i_abilityStats[0][2] = atoi(aEdit_StatsCON0->value());
	players[pid].i_abilityStats[1][2] = atoi(aEdit_StatsCON1->value());
	players[pid].i_abilityStats[0][3] = atoi(aEdit_StatsINT0->value());
	players[pid].i_abilityStats[1][3] = atoi(aEdit_StatsINT1->value());
	players[pid].i_abilityStats[0][4] = atoi(aEdit_StatsWIS0->value());
	players[pid].i_abilityStats[1][4] = atoi(aEdit_StatsWIS1->value());
	players[pid].i_abilityStats[0][5] = atoi(aEdit_StatsCHA0->value());
	players[pid].i_abilityStats[1][5] = atoi(aEdit_StatsCHA1->value());
	players[pid].i_skills[SKILL_SEARCH] = atoi(aEdit_SkillSearch->value());
	players[pid].i_skills[SKILL_SOH] = atoi(aEdit_SkillSOH->value());
	players[pid].i_skills[SKILL_SPOT] = atoi(aEdit_SkillSpot->value());
	players[pid].i_skills[SKILL_OPENLOCKS] = atoi(aEdit_SkillOLocks->value());
	players[pid].i_skills[SKILL_MOVESILENTLY] = atoi(aEdit_SkillMoveSilently->value());
	players[pid].i_skills[SKILL_LISTEN] = atoi(aEdit_SkillListen->value());
	players[pid].i_skills[SKILL_HIDE] = atoi(aEdit_SkillHide->value());
	players[pid].i_skills[SKILL_CONCENTRATION] = atoi(aEdit_SkillConcentration->value());
	players[pid].i_spellResistance = atoi(aEdit_SpellResistance->value());
	players[pid].i_damageReduction[0] = aEdit_DamReductionType->value();
	players[pid].i_damageReduction[1] = atoi(aEdit_DamReductionHP->value());
	players[pid].i_damageReduction[2] = atoi(aEdit_DamReductionWeapon->value());
	players[pid].i_size = aEdit_Size->value();

	i = players[pid].i_space;
	players[pid].i_space = atoi(aEdit_Space->value());
//printf("eP: %d = %d:%d\n", pid, i, players[pid].i_space);

		// if the space changes, update the map 'shadow'
	if (i != players[pid].i_space) {
		combatGridMap->getGridTile()->setShadow(j, k, pid, 0, (i/5), 0);
		k = GRID_MONSTER;
		if (pid < MAX_PLAYERS) { k = GRID_PLAYER; }
		combatGridMap->getGridTile()->setShadow(players[pid].i_mapX, players[pid].i_mapY, pid, k, (players[pid].i_space/5), 1);
	}

	players[pid].i_xp[MAX] = atoi(aEdit_XPCurr->value());
	players[pid].i_xp[TMP] = atoi(aEdit_XPTemp->value());
	players[pid].i_inGroup = atoi(aEdit_InGroup->value());
	strncpy(players[pid].c_hitDice, aEdit_HitDice->value(), 19); players[pid].c_hitDice[19] = '\0';
	players[pid].flags.f_isStabilised = aEdit_Flags->checked(1);
	players[pid].flags.f_disabled = aEdit_Flags->checked(2);
	players[pid].flags.f_ignoreCriticals = aEdit_Flags->checked(3);
	players[pid].flags.f_autoStablise = aEdit_Flags->checked(4);
	players[pid].flags.f_evasion = aEdit_Flags->checked(5);
	players[pid].flags.f_npc = aEdit_Flags->checked(6);
	players[pid].flags.f_invisible = aEdit_Flags->checked(7);
	players[pid].flags.f_wasViewed = aEdit_Flags->checked(8);
	players[pid].flags.f_ignoreBleed = aEdit_Flags->checked(9);
	players[pid].flags.f_ignoreStun = aEdit_Flags->checked(10);

	players[pid].spellsAvailable.i_maxLevel0 = atoi(aEdit_SpellSlotMax0->value());
	players[pid].spellsAvailable.i_maxLevel1 = atoi(aEdit_SpellSlotMax1->value());
	players[pid].spellsAvailable.i_maxLevel2 = atoi(aEdit_SpellSlotMax2->value());
	players[pid].spellsAvailable.i_maxLevel3 = atoi(aEdit_SpellSlotMax3->value());
	players[pid].spellsAvailable.i_maxLevel4 = atoi(aEdit_SpellSlotMax4->value());
	players[pid].spellsAvailable.i_maxLevel5 = atoi(aEdit_SpellSlotMax5->value());
	players[pid].spellsAvailable.i_maxLevel6 = atoi(aEdit_SpellSlotMax6->value());
	players[pid].spellsAvailable.i_maxLevel7 = atoi(aEdit_SpellSlotMax7->value());
	players[pid].spellsAvailable.i_maxLevel8 = atoi(aEdit_SpellSlotMax8->value());
	players[pid].spellsAvailable.i_maxLevel9 = atoi(aEdit_SpellSlotMax9->value());
	players[pid].spellsAvailable.i_curLevel0 = atoi(aEdit_SpellSlotCur0->value());
	players[pid].spellsAvailable.i_curLevel1 = atoi(aEdit_SpellSlotCur1->value());
	players[pid].spellsAvailable.i_curLevel2 = atoi(aEdit_SpellSlotCur2->value());
	players[pid].spellsAvailable.i_curLevel3 = atoi(aEdit_SpellSlotCur3->value());
	players[pid].spellsAvailable.i_curLevel4 = atoi(aEdit_SpellSlotCur4->value());
	players[pid].spellsAvailable.i_curLevel5 = atoi(aEdit_SpellSlotCur5->value());
	players[pid].spellsAvailable.i_curLevel6 = atoi(aEdit_SpellSlotCur6->value());
	players[pid].spellsAvailable.i_curLevel7 = atoi(aEdit_SpellSlotCur7->value());
	players[pid].spellsAvailable.i_curLevel8 = atoi(aEdit_SpellSlotCur8->value());
	players[pid].spellsAvailable.i_curLevel9 = atoi(aEdit_SpellSlotCur9->value());

players[pid].i_resistances[RESIST_FIRE] = atoi(aEdit_SpellResistanceFire1->value());
players[pid].i_resistancesUsed[RESIST_FIRE] = atoi(aEdit_SpellResistanceFire2->value());
players[pid].i_resistances[RESIST_ACID] = atoi(aEdit_SpellResistanceAcid1->value());
players[pid].i_resistancesUsed[RESIST_ACID] = atoi(aEdit_SpellResistanceAcid2->value());
players[pid].i_resistances[RESIST_COLD] = atoi(aEdit_SpellResistanceCold1->value());
players[pid].i_resistancesUsed[RESIST_COLD] = atoi(aEdit_SpellResistanceCold2->value());
players[pid].i_resistances[RESIST_ELEC] = atoi(aEdit_SpellResistanceElec1->value());
players[pid].i_resistancesUsed[RESIST_ELEC] = atoi(aEdit_SpellResistanceElec2->value());
players[pid].i_resistances[RESIST_SONIC] = atoi(aEdit_SpellResistanceSonic1->value());
players[pid].i_resistancesUsed[RESIST_SONIC] = atoi(aEdit_SpellResistanceSonic2->value());

//printf("%s %d\n", mybuf2, edit_notes_buffer->length());
	if (edit_notes_buffer->length() > 0) {
//		sprintf(mybuf2, "%s%s.note", systemDir, players[pid].c_name);
//		edit_notes_buffer->savefile(mybuf2);
		doNotesAction(0, pid);
	}
		// if the icon changed, load it in
	if (strcasecmp(players[pid].c_iconFile, aEdit_IconFilename->value()) != 0) {
		if (playerIcons[pid] != NULL) { delete playerIcons[pid]; }
		if (mystrcasestr(aEdit_IconFilename->value(), "png") != NULL) {
			playerIcons[pid] = new Fl_PNG_Image(aEdit_IconFilename->value());
		} else {
			playerIcons[pid] = new Fl_JPEG_Image(aEdit_IconFilename->value());
		}
		combatGridMap->setPlayerIcon(pid, playerIcons[pid]);
//printf("loading new ICON %d = %s:%ld\n", pid, aEdit_IconFilename->value(), playerIcons[pid]);
	}
	strncpy(players[pid].c_iconFile, aEdit_IconFilename->value(), 59); players[pid].c_iconFile[59] = '\0';

	players[pid].i_reach = atoi(aEdit_Reach->value());

	strncpy(players[pid].c_items, aEdit_Items->value(), 189); players[pid].c_items[189] = '\0';

	players[pid].i_negateCrit = atoi(aEdit_NegateCritical->value());

	reloadNames(0);

	aEdit_players->activate();
	aEdit_monsters->activate();
	aEdt_Accept->deactivate();
	aEdt_Cancel->deactivate();
	aEdt_QkMonsterAdd->activate();
	aEdt_Tabs->deactivate();
	aEdit_SpecialActions->deactivate();
	a_EdtQkMonList->activate();
	a_EdtQkMonstSearch->activate();
	aEdit_AddQkMonsters->activate();
	aEdit_EditQkMonsters->activate();
	aEdit_SaveQkMonsters->activate();
	a_EdtQkMonCRSearch->activate();
	aEdit_QkMonstersWildSearch->activate();
	a_EdtQkMonAddCtr->activate();
	a_EdtQkMonstIconFilename->activate();

	// do some quick sanity checks
	if (a_EORMessageList == NULL) { doEndOfRoundMessages(0); }
	a_EORMessageList->clear();
	a_EORMessageList->add("");
	a_EORMessageList->add("@B63@.The following are possible problems with this player/monster");
	a_EORMessageList->add("");

	if (players[pid].i_hp[HP_MAX] == 0 || players[pid].i_hp[HP_CUR] == 0) { ok = 1; a_EORMessageList->add("  HP's are zero"); }
	if (players[pid].i_armorClass[AC_NORMAL] == 0) { ok = 1; a_EORMessageList->add("  A/C is zero"); }
	if (players[pid].i_noAttacks == 0) { ok = 1; a_EORMessageList->add("  #Attks is zero"); }
	if (players[pid].w_weapons[0].i_attackBonus[0] == 0 && players[pid].w_weapons[1].i_attackBonus[0] == 0 &&
players[pid].w_weapons[2].i_attackBonus[0] == 0 && players[pid].w_weapons[3].i_attackBonus[0] == 0) { ok = 1; a_EORMessageList->add("  Weapon Attack Bonuses dont seem to be set"); }

	if (config.i_diceSystem == DICE_D20) {
		if (players[pid].f_challengeRating == 0 && pid >= MAX_PLAYERS) { ok = 1; a_EORMessageList->add("  CR value is zero"); }
		if (players[pid].i_savingThrows[SAVE_FORTITUDE] == 0 && players[pid].i_savingThrows[SAVE_REFLEX] == 0 && players[pid].i_savingThrows[SAVE_WISDOM] == 0) { ok = 1; a_EORMessageList->add("  Saving Throws have issues"); }
	}

	if (ok == 1) {
		doEndOfRoundMessages(0);
	}

}

/******************************************************************************/
void setCombatDisplay(int flag) {
	int i,j,k;
	char *cp;

if (config.flags.f_debug != 0) { printf("sCD: %d\n", flag); }
	switch (flag) {
		case 0: a_CBInitiators->activate();
				  a_CBActionType->deactivate();
				  a_CTActions->deactivate();
				  a_CTMelee->deactivate();
				  a_CTSpell->deactivate();
				  a_CTOther->deactivate();
//				  a_CTCancel->deactivate();
				  a_CBActionType->clear();
				  for (i=0; actionTypes[i] != NULL; i++) {
			  			a_CBActionType->add(actionTypes[i]);
				  }
				  break;

		case 1: a_CBInitiators->activate();
				  a_CBActionType->activate();
				  a_CBActionType->clear();
				  for (i=0; actionTypes[i] != NULL; i++) {
			  			a_CBActionType->add(actionTypes[i]);
				  }
//				  a_CTActions->deactivate();
				  a_CTActions->activate();
				  a_CTMelee->deactivate();
				  a_CTSpell->deactivate();
				  a_CTOther->deactivate();
				  a_CTMonsterDetails->activate();
				  a_CTSpellDetails->activate();
				  a_CTNotes->activate();
				  a_CTActions->value(a_CTMelee);
//				  a_CTCancel->deactivate();
				  a_CTMessage->clear();
				  for (i=0; i<14; i++) { a_CTMessage->add(""); }

//				  for (i=0; i<MAX_MEMBERS; i++) { printf("sCD: 1: %d = %d\n", i, config.i_idList[ID_INIT][i]); }
//				  config.i_actionInitID = config.i_idList[ID_INIT][a_CBInitiators->value()-1];
				  config.i_actionRecvID = -1;
if (config.flags.f_debug != 0) { printf("sCD: 1: %d:%d:%d\n", flag, config.i_actionInitID, a_CBInitiators->value()-1); }
				  a_CTACBreakdown->value("");
				  a_CTInitiatorDetails->clear(); a_EDInitiatorDetails1->clear();
				  a_CTDefenderDetails->clear(); a_EDDefenderDetails1->clear();
				  sprintf(mybuf2, "Name: %s", players[config.i_actionInitID].c_name); a_CTInitiatorDetails->add(mybuf2); a_EDInitiatorDetails1->add(mybuf2);
				  sprintf(mybuf2, "Speed: %d", players[config.i_actionInitID].i_speed); a_CTInitiatorDetails->add(mybuf2); a_EDInitiatorDetails1->add(mybuf2);
				  if (players[config.i_actionInitID].spellsAvailable.i_maxLevel0 > 0) {
				  		sprintf(mybuf2, "@b@.Spells Left: %d/%d/%d/%d/%d/%d/%d/%d/%d/%d", players[config.i_actionInitID].spellsAvailable.i_curLevel0, players[config.i_actionInitID].spellsAvailable.i_curLevel1, players[config.i_actionInitID].spellsAvailable.i_curLevel2, 
						players[config.i_actionInitID].spellsAvailable.i_curLevel3, players[config.i_actionInitID].spellsAvailable.i_curLevel4, players[config.i_actionInitID].spellsAvailable.i_curLevel5, players[config.i_actionInitID].spellsAvailable.i_curLevel6, 
						players[config.i_actionInitID].spellsAvailable.i_curLevel7, players[config.i_actionInitID].spellsAvailable.i_curLevel8, players[config.i_actionInitID].spellsAvailable.i_curLevel9); 
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel0 > 0) { j = 0; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel1 > 0) { j = 1; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel2 > 0) { j = 2; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel3 > 0) { j = 3; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel4 > 0) { j = 4; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel5 > 0) { j = 5; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel6 > 0) { j = 6; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel7 > 0) { j = 7; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel8 > 0) { j = 8; }
						if (players[config.i_actionInitID].spellsAvailable.i_maxLevel9 > 0) { j = 9; }
						cp = strstr(mybuf2, "/"); j--;
						while (j >= 0) {
							cp = strstr(cp, "/");
							cp++;
							j--;
				  		}
						if (cp != NULL) { cp++; *cp = '\0'; }
						a_CTInitiatorDetails->add(mybuf2); a_EDInitiatorDetails1->add(mybuf2);
				  }
				  sprintf(mybuf2, "   %d", (players[config.i_actionInitID].i_noAttacks - players[config.i_actionInitID].i_doneAttacks)); a_CTAttacksLeft->value(mybuf2);
				  sprintf(mybuf2, "%s%s.note", systemDir, players[config.i_actionInitID].c_name); detailed_buffer[0]->loadfile(mybuf2);
				  if (players[config.i_actionInitID].i_stun > 0) {
						sprintf(mybuf2, "@B95@.!!! They are stunned for %d rounds.... !!!", players[config.i_actionInitID].i_stun);
						a_CTMessage->text(1, mybuf2);
				  }		// mark the selected one as WHITE, makes them easier to find
				  for (j=0; j<MAX_MEMBERS; j++) {
					if (config.i_idList[ID_INIT][j] == config.i_actionInitID) {
						sprintf(mybuf2, "@B255@.%s (%d=%d%% %d:%d)", players[config.i_actionInitID].c_name, getHPs(config.i_actionInitID), getHPpercentage(config.i_actionInitID), players[config.i_actionInitID].i_noAttacks, players[config.i_actionInitID].i_doneAttacks);
						a_CBInitiators->text(j, mybuf2);
					}
				  }
				  reloadNames(1);
				  config.i_actionWeaponSelected = -1;
				  a_CTMonsterDetails->deactivate();
				  if (config.i_actionInitID >= MAX_PLAYERS) {
				  		a_CTMonsterDetails->activate();
				  		a_CTActions->value(a_CTMonsterDetails);
						loadMonsterDescription(players[config.i_actionInitID].c_name);
				  }
				  doNotesAction(2, config.i_actionInitID);

				  		// display the weapon details
				  a_CTWeaponUsed->clear();
				  for (j=0; j<MAX_WEAPONS; j++) {
						if (players[config.i_actionInitID].w_weapons[j].c_available == 1 || players[config.i_actionInitID].w_weapons[j].c_description[0] != '\0') {
							sprintf(mybuf1, "%s (%d/%d)", players[config.i_actionInitID].w_weapons[j].c_description, players[config.i_actionInitID].w_weapons[j].i_noAttacks, players[config.i_actionInitID].w_weapons[j].i_doneAttacks);
							a_CTWeaponUsed->add(mybuf1);
						}
				  }
				  break;

		case 2: // a_CBInitiators->deactivate();
				  setWindowTitles();
				  a_CBActionType->deactivate();
				  a_CTActions->activate();
				  a_CTMelee->deactivate(); // a_CTallAttacksDone->deactivate();
				  a_CTSpell->deactivate(); a_CTSpellAllDone->deactivate();
				  a_CTOther->deactivate();
				  a_CTCancel->activate();
				  a_CTACBreakdown->value("");
				  a_CTMeleeACAdjustments->value("0");
				  i = a_CBActionType->value() - 1;
				  config.i_actionSelected = a_CBActionType->value() - 1;
				  sprintf(mybuf2, "@B32@.%s", actionTypes[config.i_actionSelected]);
				  a_CBActionType->text(i+1, mybuf2);
				  a_CTOtherFlags->check_none(); a_CTOtherFlags->checked(1,1); a_CTOtherFlags->checked(2,1);
				  a_CTSpellEnergyType->check_none(); a_CTSpellEnergyType->checked(1, 1);

				  		// should they bleed now
				  if (config.i_whenBleed == 0 && players[config.i_actionInitID].i_doneAttacks == 0) {
//						if ((players[config.i_actionInitID].i_hp[HP_CUR] <= players[config.i_actionInitID].i_disabledAt && players[config.i_actionInitID].flags.f_isStabilised == 0) || players[config.i_actionInitID].i_bleeding != 0) {
						if ((getHPs(config.i_actionInitID) <= players[config.i_actionInitID].i_disabledAt && players[config.i_actionInitID].flags.f_isStabilised == 0) || players[config.i_actionInitID].i_bleeding != 0) {
							if (getRND(100) < 11 && (i >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0)) {		// did they stabilise ?
								players[i].flags.f_isStabilised = 1;
								sprintf(mybuf2, "Bleed: %s (HP:0 Sb:1) Cur:%d", players[config.i_actionInitID].c_name, getHPs(config.i_actionInitID));
							} else {
								AYSButton[2]->activate();
								AYSButton[2]->label("Stabilised");
								sprintf(mybuf2, "They are bleeding @ %d/rnd or are disabled.\n Shall I remove HP's now ?", players[config.i_actionInitID].i_bleeding);
								j = doAreYouSure(mybuf2);
								a_CTOtherFlags->checked(2,0);		// uncheck the Remove from Spell Spot option
								AYSButton[2]->label("Maybe");
								AYSButton[2]->deactivate();
								if (j == 1) {
									if (players[config.i_actionInitID].i_bleeding != 0) {
										players[config.i_actionInitID].i_hp[HP_CUR] -= players[config.i_actionInitID].i_bleeding;
										sprintf(mybuf2, "Bleed: %s (HP:%d) Cur:%d", players[config.i_actionInitID].c_name, players[config.i_actionInitID].i_bleeding, getHPs(config.i_actionInitID));
										writeLog(mybuf2);
									} else {
										players[config.i_actionInitID].i_hp[HP_CUR] --;
										sprintf(mybuf2, "Bleed: %s (HP:1) Cur:%d", players[config.i_actionInitID].c_name, getHPs(config.i_actionInitID));
										writeLog(mybuf2);
									}
									players[config.i_actionInitID].i_doneAttacks = 1;
								} else if (j == -2) {
									players[config.i_actionInitID].flags.f_isStabilised = 1;
									players[config.i_actionInitID].i_doneAttacks = 1;
									sprintf(mybuf2, "Bleed: %s (HP:0 Sb:1) Cur:%d", players[config.i_actionInitID].c_name, getHPs(config.i_actionInitID));
									writeLog(mybuf2);
								}
							}
						}
				  }
				  	// are there any following adjustments that finish now
				  if (a_EORMessageList == NULL) { doEndOfRoundMessages(0); }
				  a_EORMessageList->clear();
				  a_EORMessageList->add("Modifiers that finish now:");
				  k=0;
				  for (j=0; j<MAX_MODIFIERS; j++) {
						if (config.action_mods[j].i_noRounds == 1 && config.action_mods[j].i_idFollows == config.i_actionInitID) {
				  			a_EORMessageList->add(config.action_mods[j].c_message);
				  			sprintf(mybuf1, "Adjust: %s", config.action_mods[j].c_message); writeLog(mybuf1);
							sprintf(config.action_mods[j].c_message, "-- empty slot %d", i);
							config.action_mods[j].i_noRounds = 0;
							config.action_mods[j].i_whom[0] = config.action_mods[j].i_whom[1] = config.action_mods[j].i_idFollows = -255;
							config.action_mods[j].i_data[0][0] = config.action_mods[j].i_data[0][2] = 0; config.action_mods[j].i_data[0][1] = -1;
							config.action_mods[j].i_data[1][0] = config.action_mods[j].i_data[1][2] = 0; config.action_mods[j].i_data[1][1] = -1;
							config.action_mods[j].i_data[2][0] = config.action_mods[j].i_data[2][2] = 0; config.action_mods[j].i_data[2][1] = -1;
							config.action_mods[j].i_data[3][0] = config.action_mods[j].i_data[3][2] = 0; config.action_mods[j].i_data[3][1] = -1;
							config.action_mods[j].i_data[4][0] = config.action_mods[j].i_data[4][2] = 0; config.action_mods[j].i_data[4][1] = -1;
							k=1;
						}
				  }
				  if (k == 1) {
						doEndOfRoundMessages(0);
				  }
if (config.flags.f_debug != 0) { printf("sCD: 2: %d:%d\n", flag, i); }
						// check for any auto-damage that should be applied
				  for (i=0; i<MAX_AUTODAMAGE; i++) {
						if (config.auto_damage[i].i_noRounds > 0 && config.auto_damage[i].flags.f_flag1 != 0 && config.auto_damage[i].i_initiatorID == config.i_actionInitID && config.auto_damage[i].flags.f_flag2 == 0) {
								calcAutoDamage(i, -1);
								config.auto_damage[i].flags.f_flag2 = 1;
						}
				  }
						// now do all the display configuration, clearing of fields etc
				  sprintf(mybuf2, "%d", getAdjustment(config.i_actionInitID, MOD_BAB)); a_CTMeleeBABAdjustments->value(mybuf2);
				  sprintf(mybuf2, "%d", getAdjustment(config.i_actionInitID, MOD_DAMAGE)); a_CTMeleeDmgAdjustments->value(mybuf2); a_CTSpellDmgMods->value(mybuf2);
				  if (config.i_actionSelected == 0) {
						a_CTMelee->activate(); a_CTActions->value(a_CTMelee);
						a_CTWeaponUsed->clear();
						a_CTWeaponDetails->clear();
						a_CTCombatMods->check_none();
						a_CTSpecialAttacks->check_none();
						k=0;
						for (j=0; j<MAX_WEAPONS; j++) {
							if (players[config.i_actionInitID].w_weapons[j].c_available == 1 || players[config.i_actionInitID].w_weapons[j].c_description[0] != '\0') {
								sprintf(mybuf1, "%s (%d/%d)", players[config.i_actionInitID].w_weapons[j].c_description, players[config.i_actionInitID].w_weapons[j].i_noAttacks, players[config.i_actionInitID].w_weapons[j].i_doneAttacks);
								a_CTWeaponUsed->add(mybuf1);
								config.i_idList[ID_WEAP][k++] = j;
							}
							config.i_idList[ID_WEAP][k] = -1;
						}
				   } else if (config.i_actionSelected > 6) { 		// other type action: healing/turning etc
						a_CTOtherHealHP->deactivate(); a_CTOtherHealBleeding->deactivate(); 
//						a_CTOtherStabilise->deactivate(); 
						a_CTOtherHealSkillMods->deactivate(); a_CTOtherSpellLevel->deactivate(); a_CTOtherFlags->deactivate();

						if (config.i_actionSelected != 8) {		// a turning could mark them as Inactive/Stunned
							a_CTOtherHealInactive->deactivate(); a_CTOtherHealStun->deactivate();
						}

						a_CTOther->activate(); a_CTActions->value(a_CTOther); 
						a_CTOtherActions->clear();
						a_CTOtherActions->check_none();
						a_CTOtherMessages->clear();
				  		a_CTOtherHealSkillMods->value("");
						if (config.i_actionSelected == 8) {
							a_CTOtherMessages->add("Turning Range: 60 feet, line of sight");
							a_CTOtherMessages->add("@bRoll 1d20 + Cha mod; table below shows highest HD you can turn");
							a_CTOtherMessages->add("00-00 Cleric level - 4");
							a_CTOtherMessages->add("01-03 Cleric level - 3");
							a_CTOtherMessages->add("04-06 Cleric level - 2");
							a_CTOtherMessages->add("07-09 Cleric level - 1");
							a_CTOtherMessages->add("10-12 Cleric level");
							a_CTOtherMessages->add("13-15 Cleric level + 1");
							a_CTOtherMessages->add("16-18 Cleric level + 2");
							a_CTOtherMessages->add("19-21 Cleric level + 3");
							a_CTOtherMessages->add("22+ Cleric level + 4");
							a_CTOtherMessages->add("@bRoll 2d6 + Cleric level + Cha mod, gives number of HD turned/rebuked");
							a_CTOtherMessages->add("Undead with 1/2 HD of cleric's level are destroyed/commanded");
							a_CTOtherMessages->add("Turned undead flee for 10 rounds, if they can't, they cower");
							a_CTOtherMessages->add("Rebuked undead cower in awe for 10 rounds");
							a_CTOtherMessages->add("If cleric gets closer than 10', turned undead will return to normal");
							a_CTOtherMessages->add("Commanded undead may be ordered as a standard action");
						} else if (config.i_actionSelected == 9) {
							sprintf(mybuf2, "@bd20 Rolls: %2.2d %2.2d %2.2d %2.2d %2.2d %2.2d %2.2d", players[config.i_actionInitID].i_d20Rolls[0], players[config.i_actionInitID].i_d20Rolls[1], players[config.i_actionInitID].i_d20Rolls[2], players[config.i_actionInitID].i_d20Rolls[3], players[config.i_actionInitID].i_d20Rolls[4], players[config.i_actionInitID].i_d20Rolls[5], players[config.i_actionInitID].i_d20Rolls[6]);
							a_CTOtherMessages->add(mybuf2);
							a_CTOtherMessages->add("");
							sprintf(mybuf2, "Spot: %d",players[config.i_actionInitID].i_skills[SKILL_SPOT]); a_CTOtherMessages->add(mybuf2);
							sprintf(mybuf2, "Search: %d", players[config.i_actionInitID].i_skills[SKILL_SEARCH]); a_CTOtherMessages->add(mybuf2);
							sprintf(mybuf2, "Open Locks: %d",players[config.i_actionInitID].i_skills[SKILL_OPENLOCKS]); a_CTOtherMessages->add(mybuf2);
							sprintf(mybuf2, "Move Silently: %d",players[config.i_actionInitID].i_skills[SKILL_MOVESILENTLY]); a_CTOtherMessages->add(mybuf2);
							sprintf(mybuf2, "Listen: %d",players[config.i_actionInitID].i_skills[SKILL_LISTEN]); a_CTOtherMessages->add(mybuf2);
							sprintf(mybuf2, "Hide: %d",players[config.i_actionInitID].i_skills[SKILL_HIDE]); a_CTOtherMessages->add(mybuf2);
							sprintf(mybuf2, "Concentration: %d",players[config.i_actionInitID].i_skills[SKILL_CONCENTRATION]); a_CTOtherMessages->add(mybuf2);
							sprintf(mybuf2, "Sleight of Hand: %d",players[config.i_actionInitID].i_skills[SKILL_SOH]); a_CTOtherMessages->add(mybuf2);
							a_CTOtherHealSkillMods->activate();
				  			sprintf(mybuf2, "%d", getAdjustment(config.i_actionInitID, MOD_SKILL)); a_CTOtherHealSkillMods->value(mybuf2);
						} else {
							a_CTOtherHealHP->activate(); a_CTOtherHealBleeding->activate(); a_CTOtherHealStun->activate();
//							a_CTOtherStabilise->activate(); 
							a_CTOtherHealInactive->activate(); a_CTOtherFlags->activate(); a_CTOtherSpellLevel->activate();
						}
				   } else { 		// a spell action
						a_CTSpell->activate(); a_CTActions->value(a_CTSpell); 
						a_CTSpellEffects->check_none();
						a_CTSpellModifiers->check_none();
						a_CTSpellSaved->check_none();
						a_CTSpellModifiers->check_none(); a_CTSpellModifiers->checked(1,1); // assume SAVE = 50%
						a_CTSpellModifiers->checked(4,1); a_CTSpellModifiers->checked(5,1);
						sprintf(mybuf2, "%d", players[config.i_actionInitID].i_spellDC[0]);
						a_CTSpellDC->value(mybuf2);
						a_CTSpellDC->color(FL_WHITE);
						a_CTSpellLevel->value(1.0);
						if (players[config.i_actionInitID].i_spellFailure > 0) {
							if (config.i_actionInitID < MAX_PLAYERS) {
								sprintf(mybuf2, "!!! The Initiator selected has a Spell Failure of %d%% !!!", players[config.i_actionInitID].i_spellFailure);
							} else {
								if (getRND(100) <= players[config.i_actionInitID].i_spellFailure) {
									sprintf(mybuf2, "!!! The Initiator selected has a Spell Failure of %d%% and has FAILED !!!", players[config.i_actionInitID].i_spellFailure);
								} else {
									sprintf(mybuf2, "!!! The Initiator selected has a Spell Failure of %d%% and has SUCCEEDED !!!", players[config.i_actionInitID].i_spellFailure);
								}
							}
							a_CTMessage->text(2, mybuf2);
						}
				   }		// fill in all the check lists
					j=0;
					a_CTSpellEffects->clear();
					a_CTSpellSaved->clear();
					a_CTDefender->clear();
					a_CTOtherActions->clear();
					if (config.i_actionInitID < MAX_PLAYERS) {
// put active monsters 1st
						for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0 && isDead(i) == 0
							 && getHPs(i) > -1) {
								sprintf(mybuf1, "%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTDefender->add(mybuf1);
								a_CTOtherActions->add(mybuf1);
								if (players[i].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0) {
									sprintf(mybuf1, "%s (%d=%d%% SR:%d)", players[i].c_name, getHPs(i), getHPpercentage(i), (players[i].i_spellResistance + getAdjustment(i, MOD_SPELL_RESISTANCE)));
								}
								a_CTSpellEffects->add(mybuf1);
								a_CTSpellSaved->add(mybuf1);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
// put uncon monsters next
						for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0 && isDead(i) == 0
							 && getHPs(i) < 0) {
								sprintf(mybuf1, "%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTDefender->add(mybuf1);
								a_CTOtherActions->add(mybuf1);
								if (players[i].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0) {
									sprintf(mybuf1, "%s (%d=%d%% SR:%d)", players[i].c_name, getHPs(i), getHPpercentage(i), (players[i].i_spellResistance + getAdjustment(i, MOD_SPELL_RESISTANCE)));
								}
								a_CTSpellEffects->add(mybuf1);
								a_CTSpellSaved->add(mybuf1);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
						for (i=0; i<MAX_PLAYERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0
							 && isDead(i) == 0) {
//							 && getHPs(i) > -1) {
								sprintf(mybuf1, "%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTDefender->add(mybuf1);
								a_CTOtherActions->add(mybuf1);
								if (players[i].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0) {
									sprintf(mybuf1, "%s (%d=%d%% SR:%d)", players[i].c_name, getHPs(i), getHPpercentage(i), (players[i].i_spellResistance + getAdjustment(i, MOD_SPELL_RESISTANCE)));
								}
								a_CTSpellEffects->add(mybuf1);
								a_CTSpellSaved->add(mybuf1);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
						for (i=0; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0
							 && isDead(i) == 1) {
//							 && getHPs(i) < -9) {
								sprintf(mybuf1, "@B88@.%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTDefender->add(mybuf1);
								sprintf(mybuf1, "%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTOtherActions->add(mybuf1);
								if (players[i].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0) {
									sprintf(mybuf1, "%s (%d=%d%% SR:%d)", players[i].c_name, getHPs(i), getHPpercentage(i), (players[i].i_spellResistance + getAdjustment(i, MOD_SPELL_RESISTANCE)));
								}
								a_CTSpellEffects->add(mybuf1);
								a_CTSpellSaved->add(mybuf1);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
					} else {
						for (i=0; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0
							 && isDead(i) == 0) {
//							 && getHPs(i) > -10) {
								sprintf(mybuf1, "%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTDefender->add(mybuf1);
								a_CTOtherActions->add(mybuf1);
								if (players[i].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0) {
									sprintf(mybuf1, "%s (%d=%d%% SR:%d)", players[i].c_name, getHPs(i), getHPpercentage(i), (players[i].i_spellResistance + getAdjustment(i, MOD_SPELL_RESISTANCE)));
								}
								a_CTSpellEffects->add(mybuf1);
								a_CTSpellSaved->add(mybuf1);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
						for (i=0; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0
							 && isDead(i) == 1) {
//							 && getHPs(i) < -9) {
								sprintf(mybuf1, "@B88@.%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTDefender->add(mybuf1);
								sprintf(mybuf1, "%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
								a_CTOtherActions->add(mybuf1);
								if (players[i].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0) {
									sprintf(mybuf1, "%s (%d=%d%% SR:%d)", players[i].c_name, getHPs(i), getHPpercentage(i), (players[i].i_spellResistance + getAdjustment(i, MOD_SPELL_RESISTANCE)));
								}
								a_CTSpellEffects->add(mybuf1);
								a_CTSpellSaved->add(mybuf1);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
					}
					for (; j < MAX_MEMBERS; j++) {
						config.i_idList[ID_DEFD][j] = -1;
					}
					a_CTMeleeAC->value(""); a_CTMeleeBAB->value(""); a_CTMeleeRoll->value(""); a_CTMeleeDamage->value("");
					a_CTMeleeInactive->value(""); a_CTMeleeBleeding->value(""); a_CTMeleeStun->value(""); a_CTMeleeInactive->value("");
					if (config.i_actionInitID >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0) {
						i = atoi(a_CTMeleeRoll->value());
						sprintf(mybuf1, "%d", getRND(20)); a_CTMeleeRoll->value(mybuf1);
							// just make sure the attack roll aint the same as the previous
						if (i == atoi(a_CTMeleeRoll->value())) {
							sprintf(mybuf1, "%d", getRND(20)); a_CTMeleeRoll->value(mybuf1);
						}
					}

					a_CTSpellDamage->value(""); a_CTSpellStunned->value(""); a_CTSpellBleeding->value("");
					a_CTSpellInactive->value("");

					a_CTOtherHealHP->value(""); a_CTOtherHealBleeding->value(""); a_CTOtherHealStun->value("");
//					a_CTOtherStabilise->value(1); 
					a_CTOtherSpellLevel->value(1); a_CTOtherHealInactive->value("");
					if (config.i_actionSelected == 5) {				// spell Touch attack
						a_CTSpellDC->label("Attack Roll");
						sprintf(mybuf2, "%d", (players[config.i_actionInitID].i_bab[BAB_MELEE][0] + getAdjustment(config.i_actionInitID, MOD_BAB))); a_CTSpellMods->value(mybuf2);
//						a_CTSpellLevel->deactivate();
						a_CTSpellUSA->deactivate();
						a_CTSpellSAP->deactivate();
						a_CTSpellSAM->deactivate();
						if (config.flags.f_rollAllRolls != 0 || config.i_actionInitID >= MAX_PLAYERS) {
							sprintf(mybuf2, "%d", getRND(20)); a_CTSpellDC->value(mybuf2);
						} else {
							a_CTSpellDC->value("");
						}
					} else if (config.i_actionSelected == 6) {	// spell Ranged Touch attack
						a_CTSpellDC->label("Attack Roll");
						sprintf(mybuf2, "%d", (players[config.i_actionInitID].i_bab[BAB_RANGED][0] + getAdjustment(config.i_actionInitID, MOD_BAB))); a_CTSpellMods->value(mybuf2);
//						a_CTSpellLevel->deactivate();
						a_CTSpellUSA->deactivate();
						a_CTSpellSAP->deactivate();
						a_CTSpellSAM->deactivate();
						if (config.flags.f_rollAllRolls != 0 || config.i_actionInitID >= MAX_PLAYERS) {
							sprintf(mybuf2, "%d", getRND(20)); a_CTSpellDC->value(mybuf2);
						} else {
							a_CTSpellDC->value("");
						}
				   } else if (config.i_actionSelected == 0) {
							// check to see if we should default the 1st defender
						j = players[config.i_actionInitID].i_doneAttacks;
						if (config.flags.f_defaultDefender != 0 && j > 0) {
							players[config.i_actionInitID].i_whomAttacked[j][0] = players[config.i_actionInitID].i_whomAttacked[j-1][0];
							players[config.i_actionInitID].i_whomAttacked[j][1] = players[config.i_actionInitID].i_whomAttacked[j-1][1];
//printf("defaultDefender: %d %d\n", j, players[config.i_actionInitID].i_whomAttacked[0][0]);
						}
							// preset the defender & weapon details to that of the previous attack
						i = config.i_actionRecvID = players[config.i_actionInitID].i_whomAttacked[j][0];
						j = config.i_actionWeaponSelected = players[config.i_actionInitID].i_whomAttacked[j][1];

							// auto highlight the default defender
						k=0;
						while (config.i_idList[ID_DEFD][k] != -1) {
							if (config.i_idList[ID_DEFD][k] == i) {
								a_CTDefender->select(k+1, 1);
								break;
							}
							k++;
						} 

						if (i != -1) {
							if ((k = getAdjustment(i, MOD_MISS_CHANCE)) > 0) {
								if (i >= MAX_PLAYERS) {
									if (getRND(100) <= k) {
										sprintf(mybuf2, "@B88@m@.They have a %d%% miss chance .. MISSED !!!", k);
									} else {
										sprintf(mybuf2, "@B88@m@.They have a %d%% miss chance .. HIT !!!", k);
									}
								} else {
									sprintf(mybuf2, "@B88@m@.They have a %d%% miss chance !!!", k);
								}
								a_CTMessage->text(7, mybuf2);
							} else {
								a_CTMessage->text(7, "");
							}

	// *** if you put messages here, put them down in the "4:" section aswell

							if ((k = players[config.i_actionRecvID].i_negateCrit) != 0) {
								sprintf(mybuf2, "@B88@m@.They have a %d%% to negate a Crit !!!", k);
								a_CTMessage->text(6, mybuf2);
							} else {
								a_CTMessage->text(6, "");
							}
							if (players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_SHIELD] != 0 || players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_DODGE] != 0) {
								sprintf(mybuf2, "@B63@.The defender has possible AC changes: Shield: %d & Dodge: %d", players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_SHIELD], players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_DODGE]);
								a_CTMessage->text(5, mybuf2);
							} else {
								a_CTMessage->text(5, "");
							}

							for (k=0; config.i_idList[ID_WEAP][k] != -1; k++) {
								if (config.i_idList[ID_WEAP][k] == j) {
									sprintf(mybuf2, "@B255@.%s (%d/%d)", players[config.i_actionInitID].w_weapons[j].c_description, players[config.i_actionInitID].w_weapons[j].i_noAttacks, players[config.i_actionInitID].w_weapons[j].i_doneAttacks);
									a_CTWeaponUsed->text(k+1, mybuf2);
									break;
								}
							}
							for (k=0; config.i_idList[ID_DEFD][k] != -1; k++) {
								if (config.i_idList[ID_DEFD][k] == i) {
									sprintf(mybuf2, "@B255@.%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
									a_CTDefender->text(k+1, mybuf2);
									break;
								}
							}
							setCombatDisplay(7);		// set the weapon details
							setCombatDisplay(8);		// set the defender details
							if (config.flags.f_rollAllRolls != 0 || config.i_actionInitID >= MAX_PLAYERS) {
								calcAction(0);			// calc the attack results
							}
						}
					} else {
						a_CTSpellDC->label("Spell DC");
						a_CTSpellMods->value("0");
						a_CTSpellLevel->activate();
						a_CTSpellUSA->activate();
						a_CTSpellSAP->activate();
						a_CTSpellSAM->activate();
					}
				  break;

		case 3: 	// weapon selected
				  j = a_CTWeaponUsed->value();
				  for (k=0; config.i_idList[ID_WEAP][k] != -1; k++) {
						i = config.i_idList[ID_WEAP][k];
						sprintf(mybuf2, "%s (%d/%d)", players[config.i_actionInitID].w_weapons[i].c_description, players[config.i_actionInitID].w_weapons[i].i_noAttacks, players[config.i_actionInitID].w_weapons[i].i_doneAttacks);
						a_CTWeaponUsed->text(k+1, mybuf2);
				  }
				  i = config.i_idList[ID_WEAP][j-1];
				  sprintf(mybuf2, "@B255@.%s (%d/%d)", players[config.i_actionInitID].w_weapons[i].c_description, players[config.i_actionInitID].w_weapons[i].i_noAttacks, players[config.i_actionInitID].w_weapons[i].i_doneAttacks);
				  a_CTWeaponUsed->text(j, mybuf2);
				  config.i_actionWeaponSelected = i;
				  setCombatDisplay(8);
				  break;

		case 8:
				  i = config.i_actionWeaponSelected;
if (config.flags.f_debug != 0) { printf("sCD: 3: %d:%d\n", i, a_CTWeaponUsed->value()); }
				  a_CTWeaponDetails->clear();
				  sprintf(mybuf1, "@b# Attacks: %d", players[config.i_actionInitID].w_weapons[i].i_noAttacks); a_CTWeaponDetails->add(mybuf1);
				  sprintf(mybuf1, "@b# Attks Done: %d", players[config.i_actionInitID].w_weapons[i].i_doneAttacks); a_CTWeaponDetails->add(mybuf1);
				  mybuf2[0] = '\0';
				  if (players[config.i_actionInitID].w_weapons[i].i_attackBonus[1] != 0) {
						sprintf(mybuf2, "%s/%d", mybuf2, players[config.i_actionInitID].w_weapons[i].i_attackBonus[1]);
				  }
				  if (players[config.i_actionInitID].w_weapons[i].i_attackBonus[2] != 0) {
						sprintf(mybuf2, "%s/%d", mybuf2, players[config.i_actionInitID].w_weapons[i].i_attackBonus[2]);
				  }
				  if (players[config.i_actionInitID].w_weapons[i].i_attackBonus[3] != 0) {
						sprintf(mybuf2, "%s/%d", mybuf2, players[config.i_actionInitID].w_weapons[i].i_attackBonus[3]);
				  }
				  sprintf(mybuf1, "Attk Bonuses: %d%s", players[config.i_actionInitID].w_weapons[i].i_attackBonus[0], mybuf2); a_CTWeaponDetails->add(mybuf1);
				  sprintf(mybuf1, "Damage : %s", players[config.i_actionInitID].w_weapons[i].c_damage); a_CTWeaponDetails->add(mybuf1);
				  sprintf(mybuf1, "Critical : %s", players[config.i_actionInitID].w_weapons[i].c_critical); a_CTWeaponDetails->add(mybuf1);
				  sprintf(mybuf1, "Range : %d", players[config.i_actionInitID].w_weapons[i].i_range); a_CTWeaponDetails->add(mybuf1);
				  sprintf(mybuf1, "Magic Bonus : %d", players[config.i_actionInitID].w_weapons[i].i_magicalBonus); a_CTWeaponDetails->add(mybuf1);
				  sprintf(mybuf1, "Message : %s", players[config.i_actionInitID].w_weapons[i].c_message); a_CTWeaponDetails->add(mybuf1);
				  sprintf(mybuf1, "%d", getWeaponAttackBonus(config.i_actionInitID, config.i_actionWeaponSelected)); a_CTMeleeBAB->value(mybuf1);
				  a_CTMeleeDamage->value("");
						// show any damage reduction details
				  if (config.i_actionRecvID != -1) {
					 if (players[config.i_actionRecvID].i_damageReduction[1] != 0) {
						if (players[config.i_actionRecvID].i_damageReduction[0] != 1) {
							sprintf(mybuf2, "@B88@.Damage Reduction: %d/%d %s ... Please adjust manually !!!!", players[config.i_actionRecvID].i_damageReduction[1], players[config.i_actionRecvID].i_damageReduction[2], dam_reduct_types[players[config.i_actionRecvID].i_damageReduction[0]]);
						} else {
							sprintf(mybuf2, "@B95@.Damage Reduction: %d/%d %s will be applied !!!!", players[config.i_actionRecvID].i_damageReduction[1], players[config.i_actionRecvID].i_damageReduction[2], dam_reduct_types[players[config.i_actionRecvID].i_damageReduction[0]]);
						}
						a_CTMessage->text(3, mybuf2);
					 } else {
						a_CTMessage->text(3, "");
					 }
					i = atoi(a_CTMeleeAC->value()) + atoi(a_CTMeleeACAdjustments->value()) - atoi(a_CTMeleeBAB->value()) - atoi(a_CTMeleeBABAdjustments->value());
					if (i < 1) { i = 1; }
					if (i > 20) { i = 20; }
					sprintf(mybuf2, "@b@B95@.You require atleast %d to hit them", i);
					a_CTMessage->text(1, mybuf2);
				  } else {
					a_CTMessage->text(1, "");
				  }
				  a_CTMessage->redraw();
				  break;

		case 4: 	// defender selected
				  j = a_CTDefender->value();
				  for (i=0; i<MAX_MEMBERS && config.i_idList[ID_DEFD][i] != -1; i++) {
						k = config.i_idList[ID_DEFD][i];
						sprintf(mybuf2, "%s (%d=%d%%)", players[k].c_name, getHPs(k), getHPpercentage(k));
						a_CTDefender->text(i+1, mybuf2);
				  }
				  i = config.i_idList[ID_DEFD][j-1];
				  sprintf(mybuf2, "@B255@.%s (%d=%d%%)", players[i].c_name, getHPs(i), getHPpercentage(i));
				  a_CTDefender->text(j, mybuf2);
if (config.flags.f_debug != 0) { printf("sCD: 3: %d:%d:%d\n", i, a_CTDefender->value(), j); }
				  config.i_actionRecvID = i;
				  setCombatDisplay(7);
				  if (config.i_actionWeaponSelected != -1) {
				  	setCombatDisplay(8);
				  }
				  if ((k = getAdjustment(config.i_actionRecvID, MOD_MISS_CHANCE)) > 0) {
						if (i >= MAX_PLAYERS) {
							if (getRND(100) <= k) {
								sprintf(mybuf2, "@B88@m@.They have a %d%% miss chance .. MISSED !!!", k);
							} else {
								sprintf(mybuf2, "@B88@m@.They have a %d%% miss chance .. HIT !!!", k);
							}
						} else {
							sprintf(mybuf2, "@B88@m@.They have a %d%% miss chance !!!", k);
						}
						a_CTMessage->text(7, mybuf2);
				  } else {
						a_CTMessage->text(7, "");
				  }
					if ((k = players[config.i_actionRecvID].i_negateCrit) != 0) {
						sprintf(mybuf2, "@B88@m@.They have a %d%% to negate a Crit !!!", k);
						a_CTMessage->text(6, mybuf2);
					} else {
						a_CTMessage->text(6, "");
					}
					if (players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_SHIELD] != 0 || players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_DODGE] != 0) {
						sprintf(mybuf2, "@B63@.The defender has possible AC changes: Shield: %d & Dodge: %d", players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_SHIELD], players[config.i_actionRecvID].i_armorClassSplit[AC_SECTION_DODGE]);
						a_CTMessage->text(5, mybuf2);
					} else {
						a_CTMessage->text(5, "");
					}
				  break;

		case 7:
				  i = config.i_actionRecvID;
				  a_CTDefenderDetails->clear(); a_EDDefenderDetails1->clear();
				  sprintf(mybuf2, "Name: %s", players[config.i_actionRecvID].c_name); a_CTDefenderDetails->add(mybuf2); a_EDDefenderDetails1->add(mybuf2);
				  sprintf(mybuf2, "Speed: %d", players[config.i_actionRecvID].i_speed); a_CTDefenderDetails->add(mybuf2); a_EDDefenderDetails1->add(mybuf2);
				  sprintf(mybuf1, "Touch:%d FFoot:%d (Arm:%d Shd:%d Nat:%d Dex:%d Def:%d Siz:%d Dod:%d)", players[i].i_armorClass[AC_TOUCH], players[i].i_armorClass[AC_FLATFOOTED], players[i].i_armorClassSplit[AC_SECTION_ARMOR], players[i].i_armorClassSplit[AC_SECTION_SHIELD], players[i].i_armorClassSplit[AC_SECTION_NATURAL], players[i].i_armorClassSplit[AC_SECTION_DEX], players[i].i_armorClassSplit[AC_SECTION_DEFLECTION], players[i].i_armorClassSplit[AC_SECTION_SIZE], players[i].i_armorClassSplit[AC_SECTION_DODGE]); a_CTACBreakdown->value(mybuf1); a_EDDefenderDetails1->add(mybuf1);
				  sprintf(mybuf1, "%d", players[i].i_armorClass[AC_NORMAL]); a_CTMeleeAC->value(mybuf1);
				  sprintf(mybuf2, "%d", getAdjustment(config.i_actionRecvID, MOD_AC)); a_CTMeleeACAdjustments->value(mybuf2);
				  sprintf(mybuf2, "%s%s.note", systemDir, players[config.i_actionRecvID].c_name); detailed_buffer[1]->loadfile(mybuf2);
				  	// if stunned/uncon set combat mods
					a_CTCombatMods->check_none();
					if (players[config.i_actionRecvID].i_stun > 0) { a_CTCombatMods->checked(7, 1); }
					if (getHPs(config.i_actionRecvID) <= players[config.i_actionRecvID].i_unconciousAt) { a_CTCombatMods->checked(6, 1); }
					calcCombatMods(0);
					a_CTMessage->text(3, "");		// clear damage reduction line
					if (players[config.i_actionRecvID].i_damageReduction[1] != 0) {
						if (players[config.i_actionRecvID].i_damageReduction[0] != 1) {
							sprintf(mybuf2, "@B88@.Damage Reduction: %d/%d %s ... Please adjust manually !!!!", players[config.i_actionRecvID].i_damageReduction[1], players[config.i_actionRecvID].i_damageReduction[2], dam_reduct_types[players[config.i_actionRecvID].i_damageReduction[0]]);
						} else {
							sprintf(mybuf2, "@B95@.Damage Reduction: %d/%d %s will be applied !!!!", players[config.i_actionRecvID].i_damageReduction[1], players[config.i_actionRecvID].i_damageReduction[2], dam_reduct_types[players[config.i_actionRecvID].i_damageReduction[0]]);
						}
						a_CTMessage->text(3, mybuf2);
					} else {
						a_CTMessage->text(3, "");		// clear damage reduction line
					}
					a_CTMessage->redraw();
				  break;

		case 5: 	// other selected
//				  j = a_CTOtherActions->value();
//				  i = config.i_idList[ID_DEFD][j-1];
//				  config.i_actionRecvID = i;
//if (config.flags.f_debug != 0) { printf("sCD: 3: %d:%d\n", i, a_CTOtherActions->value()); }
//				  a_CTOtherActions->check_none();
//				  a_CTOtherActions->checked(j, 1);
				  break;

		case 6:	// spell effects selected
				  if (config.i_actionSelected == 5 || config.i_actionSelected == 6) {	// spell touch attack
				  		j = a_CTSpellEffects->value();
				  		a_CTSpellEffects->check_none();
				  		a_CTSpellEffects->checked(j, 1);
				  }
				  break;

		case 9:	// Action initiator highlight
				k = a_CBInitiators->position();
				j = 0;
				if (Fl::event() == FL_RELEASE && Fl::event_button() == 3) {
					j = 1;
				}
				initiatorSelected = i = a_CBInitiators->value();
				reloadNames(1);		// redraw it
				a_CBInitiators->position(k);
				strcpy(mybuf1, a_CBInitiators->text(i));
				if (mybuf1[0] == '@') {
					sprintf(mybuf2, "@B248@.%s", &mybuf1[6]);
				} else {
					sprintf(mybuf2, "@B248@.%s", &mybuf1[0]);
				}
				a_CBInitiators->text(i, mybuf2);
				if (j == 1) {		// do we show the popup menu ?
//printf("cbI: %d:%d %d:%d %d:%d\n", Fl::event(), Fl::event_button(), a_MainWindow->x(), a_MainWindow->y(), Fl::event_x(), Fl::event_y());
					initPopupMenu->position(a_MainWindow->x() + Fl::event_x(), a_MainWindow->y() + Fl::event_y());

					j = config.i_idList[ID_INIT][i-1];

					initPopupMenu->clear();

					initPopupMenu->add(&popMenuItems[0][0]);

					if (players[j].flags.f_invisible == 0) {
						initPopupMenu->add(&popMenuItems[3][0]);
					} else {
						initPopupMenu->add(&popMenuItems[2][0]);
					}
					initPopupMenu->add(&popMenuItems[5][0]);
					if (players[j].flags.f_disabled == 0) {
						initPopupMenu->add(&popMenuItems[12][0]);
					} else {
						initPopupMenu->add(&popMenuItems[13][0]);
					}
					initPopupMenu->add(&popMenuItems[14][0]);

					if (config.i_diceSystem != DICE_D20) {
						initPopupMenu->add(&popMenuItems[16][0]);
						initPopupMenu->add(&popMenuItems[17][0]);
					}
					initPopupMenu->add(&popMenuItems[18][0]);
					initPopupMenu->add(&popMenuItems[19][0]);

					setWindowTitles();		// TODO

					initPopupMenu->popup(); 
				}
				j = config.i_idList[ID_INIT][i-1];
				combatGridMap->markPlayerLocation(players[j].i_mapX, players[j].i_mapY);
				break;

		case 10:	// set spell level/DC
				if (config.i_actionSelected < 5) { // not spell touch or ranged touch
					if ((int )a_CTSpellLevel->value() == 0) {
						sprintf(mybuf2, "%d", players[config.i_actionInitID].i_spellDC[0]-1);
					} else {
						sprintf(mybuf2, "%d", players[config.i_actionInitID].i_spellDC[(int )a_CTSpellLevel->value()-1]);
					}
					a_CTSpellDC->value(mybuf2);
					if (atoi(a_CTSpellDC->value()) == 0) {
						if (players[config.i_actionInitID].i_spellDC[0] != 0) {
							sprintf(mybuf1, "%d", (int )(players[config.i_actionInitID].i_spellDC[0] + a_CTSpellLevel->value() - 1));
						} else {
							sprintf(mybuf1, "%d", (int )(10 + a_CTSpellLevel->value()));
						}
						a_CTSpellDC->color(FL_RED);
						a_CTSpellDC->value(mybuf1);
					} else {
						a_CTSpellDC->color(FL_WHITE);
					}
				}
				break;
	}
}

/***********************************************************************/
void init16()     /* initialise the RANDOM No. generator */
{
time_t ltime;
struct tm *ntime;

	time(&ltime);
	ntime = gmtime(&ltime);

	seed1 = (ntime->tm_sec*1000)+(ntime->tm_min*100)+ntime->tm_mday;
	seed2 = (ntime->tm_min*1000)+(ntime->tm_sec*100)+ntime->tm_year;
	seed3 = (ntime->tm_sec*1000)+(ntime->tm_hour*100)+ntime->tm_mon;
}

/****************************************************************************/
double uniform16()   /* get a RANDOM No. */
{
int z=0, k=0;

    k = seed1 / 206;
    seed1 = 157 * (seed1 - k * 206) - k * 21;
    if (seed1 < 0)
        seed1 += 32363;

    k = seed2 / 217;
    seed2 = 146 * (seed2 - k * 217) - k * 45;
    if (seed2 < 0)
        seed2 += 31727;

    k = seed3 / 222;
    seed3 = 142 * (seed3 - k * 222) - k * 133;
    if (seed3 < 0)
        seed3 += 31657;

    z = seed1 - seed2;
    if (z > 706)
        z -= 32362;

    z += seed3;
    if (z < 1)
        z += 32362;

    return(z * 3.0899E-5);
}

/******************************************************************************/
int getRND(int val)
{
   if (val < 1) {
      val = getRND(20);
      fl_alert("Possible data issue ... 0 in GET-RND");
   }

   val = ((int )(uniform16() * 32767.99)) % val;

//if (config.flags.f_debug != 0) { printf("gRND: %d\n", val+1); }
   return(val+1);
} 
	
/******************************************************************************/
void endOfRound() {
int i=0,j=0,k=0;
char mybuf[70];

	if (a_EORMessageList == NULL) { doEndOfRoundMessages(0); }

	j = 0;
		// check for any players/monsters that have not done all their actions
	a_EORMessageList->clear();
	a_EORMessageList->add("@bThe following Players/Monsters have not done all their actions:");
	for (i=0; i<(MAX_MEMBERS); i++) {
		if (players[i].c_name[0] != '\0' && getHPs(i) > players[i].i_unconciousAt && players[i].i_doneAttacks < players[i].i_noAttacks && players[i].flags.f_disabled == 0) {
			a_EORMessageList->add(players[i].c_name);
			j = 1;
					// do some HP boundary checking and the like
			if (players[i].i_regeneration != 0) { players[i].i_hp[HP_CUR] += players[i].i_regeneration; }
			if (players[i].i_hp[HP_CUR] > players[i].i_hp[HP_MAX]) { players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX]; }
			if (players[i].i_hp[HP_CUR] < -250) { players[i].i_hp[HP_CUR] = -250; }
			if (players[i].i_hp[HP_CUR] > 0) { players[i].flags.f_isStabilised = 0; }
			players[i].i_resistancesUsed[RESIST_FIRE] = 0;
			players[i].i_resistancesUsed[RESIST_ACID] = 0;
			players[i].i_resistancesUsed[RESIST_ELEC] = 0;
			players[i].i_resistancesUsed[RESIST_SONIC] = 0;
		}
		if (players[i].i_roundsUntil[ROUND_DEATH] == 1) {
			sprintf(mybuf1, "@B95@. %s will die next round", players[i].c_name);
			a_EORMessageList->add(mybuf1);
		}
	}
		// check for any Messages to be shown
	a_EORMessageList->add("");
	a_EORMessageList->add("@bThe following Alerts have occurred:");
	for (i=0; i<MAX_TRIGGERS; i++) {
		if (config.action_msgs[i].i_noRounds > 0) {
			config.action_msgs[i].i_noRounds--;
			if (config.action_msgs[i].i_noRounds > 0 && config.action_msgs[i].i_display == 1) {
				a_EORMessageList->add(config.action_msgs[i].c_message);
				j = 1;
			} else if (config.action_msgs[i].i_noRounds == 0) {
				sprintf(mybuf1, "@B63@.%s", config.action_msgs[i].c_message);
				a_EORMessageList->add(mybuf1);
				if (strlen(config.action_msgs[i].c_every) > 0) {
					config.action_msgs[i].i_noRounds = parseDice(config.action_msgs[i].c_every);
				} else {
					config.action_msgs[i].i_display = 0;
					config.action_msgs[i].c_every[0] = '\0';
					sprintf(config.action_msgs[i].c_message, "-- empty slot %d", i);
				}
				j = 1;
			}
		}
	}
	doTriggerAction(9);		// refresh the list

		// check for any Modifiers that are finishing
	a_EORMessageList->add("");
	a_EORMessageList->add("@bThe following Adjustments have expired:");
	for (i=0; i<MAX_MODIFIERS; i++) {
		if (config.action_mods[i].i_noRounds > 0) {
			config.action_mods[i].i_noRounds--;
			if (config.action_mods[i].i_noRounds == 0) {
				sprintf(mybuf1, "@B63@.%s", config.action_mods[i].c_message);
				a_EORMessageList->add(mybuf1);
				sprintf(config.action_mods[i].c_message, "-- empty slot %d", i);
				config.action_mods[i].i_whom[0] = config.action_mods[i].i_whom[1] = config.action_mods[i].i_idFollows = -255;
				config.action_mods[i].i_data[0][0] = config.action_mods[i].i_data[0][2] = 0; config.action_mods[i].i_data[0][1] = -1;
				config.action_mods[i].i_data[1][0] = config.action_mods[i].i_data[1][2] = 0; config.action_mods[i].i_data[1][1] = -1;
				config.action_mods[i].i_data[2][0] = config.action_mods[i].i_data[2][2] = 0; config.action_mods[i].i_data[2][1] = -1;
				config.action_mods[i].i_data[3][0] = config.action_mods[i].i_data[3][2] = 0; config.action_mods[i].i_data[3][1] = -1;
				config.action_mods[i].i_data[4][0] = config.action_mods[i].i_data[4][2] = 0; config.action_mods[i].i_data[4][1] = -1;
				j = 1;
			}
		} else {
			sprintf(config.action_mods[i].c_message, "-- empty slot %d", i);
			config.action_mods[i].i_whom[0] = config.action_mods[i].i_whom[1] = config.action_mods[i].i_idFollows = -255;
			config.action_mods[i].i_data[0][0] = config.action_mods[i].i_data[0][2] = 0; config.action_mods[i].i_data[0][1] = -1;
			config.action_mods[i].i_data[1][0] = config.action_mods[i].i_data[1][2] = 0; config.action_mods[i].i_data[1][1] = -1;
			config.action_mods[i].i_data[2][0] = config.action_mods[i].i_data[2][2] = 0; config.action_mods[i].i_data[2][1] = -1;
			config.action_mods[i].i_data[3][0] = config.action_mods[i].i_data[3][2] = 0; config.action_mods[i].i_data[3][1] = -1;
			config.action_mods[i].i_data[4][0] = config.action_mods[i].i_data[4][2] = 0; config.action_mods[i].i_data[4][1] = -1;
		}
	}
	doAdjustmentAction(9);		// refresh the list

		// check for any Auto-Damages that are finishing
	a_EORMessageList->add("");
	a_EORMessageList->add("@bThe following Auto-Damages have expired:");
	for (i=0; i<MAX_AUTODAMAGE; i++) {
//if (config.flags.f_debug != 0) { printf("eOR: AD %d:%s:%d:%d\n", i, config.auto_damage[i].c_description, config.auto_damage[i].i_noRounds, config.auto_damage[i].flags.f_flag2); }
		if (config.auto_damage[i].i_noRounds > 0) {
			config.auto_damage[i].i_noRounds--;
			config.auto_damage[i].i_doneRounds++;
			if (config.auto_damage[i].flags.f_flag2 == 0) {		// has it been done this round
				for (k=0; k<MAX_MEMBERS; k++) {
					if (players[k].c_name[0] != '\0' && players[k].i_hp[HP_MAX] > 0) {
//if (config.flags.f_debug != 0) { printf("eOR: AD %d\n", k); }
						calcAutoDamage(i, k);							// apply it to all 
					}
				}
			}
			if (config.auto_damage[i].i_noRounds == 0) {
				a_EORMessageList->add(config.auto_damage[i].c_description);
				config.auto_damage[i].i_initiatorID = config.auto_damage[i].i_whom[0] = -1;
				config.auto_damage[i].i_noRounds = config.auto_damage[i].i_type = 0;
				config.auto_damage[i].c_damage[0] = '\0';
				sprintf(config.auto_damage[i].c_description, "-- empty slot %d", i);
				config.auto_damage[i].flags.f_flag1 = config.auto_damage[i].flags.f_flag2 = 0;
				config.auto_damage[i].flags.f_flag3 = config.auto_damage[i].flags.f_flag4 = 0;
				config.auto_damage[i].flags.f_flag5 = config.auto_damage[i].flags.f_flag6 = 0;
				config.auto_damage[i].flags.f_flag7 = config.auto_damage[i].flags.f_flag8 = 0;
				config.auto_damage[i].i_doneRounds = 0;
				j = 1;
			}
			config.auto_damage[i].flags.f_flag2 = 0;
		}
	}

	if (j != 0) {		// something to display, so display it
		i_EORanswer = -1;
		if (doEndOfRoundMessages(0) == -1) {
			return;
		}
	}

	sprintf(mybuf, "%d", ++config.i_roundCount); aSys_Rounds->value(mybuf);

		// do they BLEED now
	if (config.i_whenBleed == 1) {
		for (i=0; i<MAX_MEMBERS; i++) {
			if (players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
				if ((getHPs(i) <= players[i].i_disabledAt && players[i].flags.f_isStabilised == 0) || players[i].i_bleeding != 0) {
if (config.flags.f_debug != 0) { printf("eOR: Bl %d:%d\n", i, players[i].i_bleeding); }
						if (players[i].i_bleeding != 0) {
							players[i].i_hp[HP_CUR] -= players[i].i_bleeding;
							if (players[i].i_hp[HP_CUR] > players[i].i_hp[HP_MAX]) { players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX]; }
							sprintf(mybuf2, "Bleed: %s (HP:%d) Cur:%d", players[i].c_name, players[i].i_bleeding, players[i].i_hp[HP_CUR]);
						} else {
							if (getRND(100) < 11 && (i >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0)) {		// did they stabilise ?
								players[i].flags.f_isStabilised = 1;
								sprintf(mybuf2, "Bleed: %s (HP:0 Sb:1) Cur:%d", players[i].c_name, getHPs(i));
							} else {
								players[i].i_hp[HP_CUR]--;
								sprintf(mybuf2, "Bleed: %s (HP:1) Cur:%d", players[i].c_name, getHPs(i));
							}
						}
						writeLog(mybuf2);
//						if (getHPs(i) < -9) {		// are they DEAD
						if (isDead(i) == 1) {		// are they DEAD
							sprintf(mybuf, "%s is DEAD !!!", players[i].c_name);
							doSystemAlert(mybuf);
						} else if (getHPs(i) <= players[i].i_unconciousAt) {		// are they UNCONCIOUS
							sprintf(mybuf, "%s is UNCONCIOUS !!!", players[i].c_name);
							doSystemAlert(mybuf);
						}
				}
			}
		}
	} else {
			// check to see that you didnt miss an action
		for (i=0; i<(MAX_MEMBERS); i++) {
			if (players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
				if (((getHPs(i) <= players[i].i_disabledAt && players[i].flags.f_isStabilised == 0) || players[i].i_bleeding != 0) && players[i].i_doneAttacks == 0) {
if (config.flags.f_debug != 0) { printf("eOR: Bl %d:%d\n", i, players[i].i_bleeding); }
						if (players[i].i_bleeding != 0) {
							players[i].i_hp[HP_CUR] -= players[i].i_bleeding;
							if (players[i].i_hp[HP_CUR] > players[i].i_hp[HP_MAX]) { players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX]; }
							sprintf(mybuf2, "Bleed: %s (HP:%d) Cur:%d", players[i].c_name, players[i].i_bleeding, getHPs(i));
						} else {
							if (getRND(100) > 10) {		// did they stabilise ?
								players[i].i_hp[HP_CUR]--;
								sprintf(mybuf2, "Bleed: %s (HP:1) Cur:%d", players[i].c_name, getHPs(i));
							} else {
								players[i].flags.f_isStabilised = 1;
								sprintf(mybuf2, "Bleed: %s (HP:0 Sb:1) Cur:%d", players[i].c_name, getHPs(i));
							}
						}
						writeLog(mybuf2);
				}
			}
		}
	}

		// do misc checks
	for (i=0; i<(MAX_MEMBERS); i++) {
		if (players[i].i_inactive > 0) {
			players[i].i_inactive--;
		}
		players[i].i_doneAttacks = 0;
		for (j=0; j<MAX_ATTACKS+2; j++) {
			players[i].w_weapons[j].i_doneAttacks = 0;
		}
		if (players[i].i_stun > 0) {
			players[i].i_stun--;
		}
		players[i].i_useShieldOn = players[i].i_useDodgeOn = -1;

		if (players[i].i_roundsUntil[ROUND_DEATH] > 0) {
			players[i].i_roundsUntil[ROUND_DEATH]--;
			if (players[i].i_roundsUntil[ROUND_DEATH] == 0) {
				players[i].i_hp[HP_CUR] = -30;
				sprintf(mybuf2, "Death: %s has died due to a previous attack", players[i].c_name);
				writeLog(mybuf2);
			}
		}
	}

		// do we need to save the data
	if (config.i_roundsSave > 0) {
		if ((config.i_roundCount % config.i_roundsSave) == 0) {
			saveAllData();
		}
	}

	if (config.i_diceSystem == DICE_D20) {
		if (config.flags.f_rollInitEveryRnd != 0) {
			doInitiativeAction(1);		// reroll inits
		}

			// recalc the INIT seq
		doInitiativeAction(2);		// reload inits
		doInitiativeAction(3);		// accept inits
	}

	reloadNames(0);			// update player/monster details
	reloadNames(1);			// update player/monster details
	reloadNames(9);			// update triggers/adjustments/auto-damage
	doOtherAction(20);		// update the status tab
	qkHealAction(0);			// update the heal section

	aLF_Logfile->load("logfile.txt");

	if (config.flags.f_logfile != 0) {
		writeLog("");
		sprintf(mybuf1, "        New Round: %d", config.i_roundCount);
		writeLog(mybuf1);
	}
	setWindowTitles();
}

/******************************************************************************/
void saveAllData() {
	FILE *fp;
	int i=0;

		  if (config.f_version > 1.10) {
				writeAllPlayerData(config.c_partyFilename);
				writeAllMonsterData(config.c_monstFilename);
				config.f_version = ADMPversion;
				writeSystemData("system.sys");
		  } else {
			  sprintf(mybuf2, "%ssystem.dat", systemDir);
			  if ((fp = fopen(mybuf2, "w")) != NULL) {
					 fwrite(&config.i_roundCount, sizeof(ADMPsystem), 1, fp);
					 fchmod(i, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
					 fclose(fp);
					 if (config.flags.f_debug != 0) printf("sAD - system file save OK (%s) !!!\n", mybuf2); 
			  } else {
					 if (config.flags.f_debug != 0) printf("sAD - system file save failed (%s) !!!\n", mybuf2); 
					 sprintf(mybuf1, "System File Save Failed (%s)", mybuf2);
					 doSystemAlert(mybuf1);
			  }

			  strncpy(config.c_partyFilename, aSys_playerFilename->value(), 43);
			  config.c_partyFilename[43] = '\0';
			  if (strncasecmp(&config.c_partyFilename[0], systemDir, strlen(systemDir)-1) != 0) {
			  		sprintf(mybuf2, "%s%s", systemDir, config.c_partyFilename);
			  } else {
			  		sprintf(mybuf2, "%s", config.c_partyFilename);
			  }
			  if ((fp = fopen(mybuf2, "w")) != NULL) {
					fwrite(&players[0].c_name[0], sizeof(ADMPplayer) * MAX_PLAYERS, 1, fp);
					fchmod(i, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
					fclose(fp);
					if (config.flags.f_debug != 0) printf("sAD - party file save OK (%s) !!!\n", mybuf2);
			  } else {
					if (config.flags.f_debug != 0) printf("sAD - party file save failed (%s) !!!\n", mybuf2);
					sprintf(mybuf1, "Party File Save Failed (%s)", mybuf2);
					doSystemAlert(mybuf1);
			  }
	
			  strncpy(config.c_monstFilename, aSys_monsterFilename->value(), 43);
			  config.c_monstFilename[43] = '\0';
			  if (strncasecmp(&config.c_monstFilename[0], systemDir, strlen(systemDir)-1) != 0) {
			  		sprintf(mybuf2, "%s%s", systemDir, config.c_monstFilename);
			  } else {
			  		sprintf(mybuf2, "%s", config.c_monstFilename);
			  }
			  if ((fp = fopen(mybuf2, "w")) != NULL) {
					fwrite(&players[MAX_PLAYERS].c_name[0], sizeof(ADMPplayer) * MAX_MONSTERS, 1, fp);
					fchmod(i, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
					fclose(fp);
					if (config.flags.f_debug != 0) printf("sAD - monster file save OK (%s) !!!\n", mybuf2);
			  } else {
					if (config.flags.f_debug != 0) printf("sAD - monster file save failed !!!\n");
					sprintf(mybuf1, "Monster File Save Failed (%s)", mybuf2);
					doSystemAlert(mybuf1);
			  }
	
// if (config.flags.f_debug != 0) { printf("sAD: %s %s\n", config.c_monstFilename, config.c_partyFilename); }
  }
		  // save the notes as well
	notes_buffer->savefile("notes.txt");

	combatGridMap->saveGridMap(config.c_mapFilename);
}

/******************************************************************************/
void loadAllData() {
//int i;

	FILE *fp=NULL;

		init16();

		if (config.flags.f_debug != 0) printf("lAD: %s %s\n", config.c_partyFilename, config.c_monstFilename);

		if (ADMPversion > 1.11) {
			if (readSystemData("system.sys") == -1) {		// couldnt find it so dont try and load anything
				config.f_version = 1.6;
				return;
			}
			combatGridMap->getGridTile()->setFogOfWar(config.flags.f_fogOfWar);
		} else {
			sprintf(mybuf2, "%ssystem.dat", systemDir);
			if ((fp = fopen(mybuf2, "r")) != NULL) {
				 fread(&config.i_roundCount, sizeof(ADMPsystem), 1, fp);
				 fclose(fp);
				 if (config.flags.f_debug != 0) printf("lAD - system file load OK (%s) !!!\n", mybuf2);
			} else {
				 if (config.flags.f_debug != 0) printf("lAD - system file load failed %s %d !!!\n", mybuf2, errno);
				 sprintf(mybuf1, "System Load Failed (%s)", mybuf2);
				 doSystemAlert(mybuf1);
				 doOtherAction(6);
				 doOtherAction(7);
				 doOtherAction(10);
			}
		}

#ifdef VISUALC
		config.f_version = ADMPversion;		// force windows to be the version
#endif

		if (config.f_version > 1.10) {
				i_monsterType = 1;
		  		readAllPlayerData(config.c_partyFilename);
		  		readAllMonsterData(config.c_monstFilename, &players[MAX_PLAYERS]);
				i_monsterType = 0; qkMonster = -1;
				switch (config.i_diceSystem) {
					case 0:	// d20
								readAllStdMonsterData("srdmonster");
								break;
					case 1:	// MERP
								readAllStdMonsterData("./mrpdat/srdmonster");
								break;
					case 2:	// RMS
								readAllStdMonsterData("./rmsdat/srdmonster");
								break;
				}
				i_monsterType = -1;
				switch (config.i_diceSystem) {
					case 0:	// d20
								readAllStdMonsterData("stdmonster");
								break;
					case 1:	// MERP
								readAllStdMonsterData("./mrpdat/stdmonster");
								break;
					case 2:	// RMS
								readAllStdMonsterData("./rmsdat/stdmonster");
								break;
				}
		} else {
			  if (strncasecmp(&config.c_partyFilename[0], systemDir, strlen(systemDir)-1) != 0) {
					sprintf(mybuf2, "%s%s", systemDir, config.c_partyFilename);
			  } else {
					strcpy(mybuf2, config.c_partyFilename);
			  }
			  if ((fp = fopen(mybuf2, "r")) != NULL) {
						 fread(&players[0].c_name[0], sizeof(ADMPplayer) * MAX_PLAYERS, 1, fp);
						 fclose(fp);
						 if (config.flags.f_debug != 0) printf("lAD - party file load OK (%s) !!!\n", mybuf2);
			  } else {
						 if (config.flags.f_debug != 0) printf("lAD - party file load failed %s %d !!!\n", mybuf2, errno);
						 sprintf(mybuf1, "Party Load Failed (%s)", mybuf2);
						 doSystemAlert(mybuf1);
			  }
	
			  if (strncasecmp(&config.c_monstFilename[0], systemDir, strlen(systemDir)-1) != 0) {
			  		sprintf(mybuf2, "%s%s", systemDir, config.c_monstFilename);
			  } else {
					strcpy(mybuf2, config.c_monstFilename);
			  }
			  if ((fp = fopen(mybuf2, "r")) != NULL) {
						 fread(&players[MAX_PLAYERS].c_name[0], sizeof(ADMPplayer) * MAX_MONSTERS, 1, fp);
						 fclose(fp);
						 if (config.flags.f_debug != 0) printf("lAD - monster file load OK (%s) !!!\n", mybuf2);
			  } else {
						 if (config.flags.f_debug != 0) printf("lAD - monster file load failed %s %d !!!\n", mybuf2, errno);
						 sprintf(mybuf1, "Monster Load Failed (%s)", mybuf2);
						 doSystemAlert(mybuf1);
			  }
	
			  sprintf(mybuf2, "%sqkmonst.dat", systemDir);
			  if ((fp = fopen(mybuf2, "r")) != NULL) {
						 fread(&qkmonsters[0].c_name[0], sizeof(ADMPplayer) * MAX_QKMONSTERS, 1, fp);
						 fclose(fp);
						 if (config.flags.f_debug != 0) printf("lAD - quick monster file load OK !!!\n");
			  } else {
						 if (config.flags.f_debug != 0) printf("lAD - quick monster file load failed !!!\n");
						 sprintf(mybuf1, "Standard Monster Load Failed (%s)", mybuf2);
						 doSystemAlert(mybuf1);
			  }
		}

		if (config.f_version < 1.11) {
			convertToVersion();
		}

		if (config.flags.f_debug != 0) printf("lAD:1\n");

			// load up the system screen
//		sprintf(mybuf, "%d", config.i_roundCount); aSys_Rounds->value(mybuf);
//		aSys_Bleeding->value(config.i_whenBleed);
//		aSys_XPAllocation->value(config.i_xpAllocate);
//		aSys_GroupInitiatives->value(config.i_doGroupInitiatives);
//		aSys_MultipleAttacks->value(config.i_attackGroup);
//		aSys_Debug->value(config.flags.f_debug);
//
//		aSys_monsterFilename->value(config.c_monstFilename);
//		aSys_playerFilename->value(config.c_partyFilename);
//		sprintf(mybuf, "%d", config.i_roundsSave); aSys_saveRounds->value(mybuf);

/*
int i=0;
	memset(&sm[0].c_name[0], '\0', sizeof(ADMPplayer)*79);
#include "stdmonsters.h"
	memcpy(&players[MAX_PLAYERS].c_name[0], &sm[0].c_name[0], sizeof(ADMPplayer) * 78);
*/

	combatGridMap->setPlayerData(players);
	combatGridMap->getGridTile()->setGroupData(config.groups);
	combatGridMap->setMapEventHandler(gridMapEventHandler);
	combatGridMap->setTileEventHandler(tileMapEventHandler);
	combatGridMap->setGridType(0);
	externalGridMap->setGridType(1);
	externalGridMap->setPlayerData(players);
	externalGridMap->getGridTile()->setGridArray(combatGridMap->getGridTile()->getGridPointArray());

	combatGridMap->loadGridMap(config.c_mapFilename);

	sprintf(mybuf2, "%d", combatGridMap->getGridTile()->getGridSzWidth()); aSys_MapWidth->value(mybuf2);
	sprintf(mybuf2, "%d", combatGridMap->getGridTile()->getGridSzHeight()); aSys_MapHeight->value(mybuf2);

	doIconAction(3);

	reloadNames(0);

	doGroupAction(-1);
}

/******************************************************************************/
void copyMonsterNotes() {
char *cp;
FILE *of;

	sprintf(mybuf1, "%s.mnt", config.c_monstFilename);
	cp = strstr(pdbDataLine, "|"); cp++;
	cp = strstr(cp, "|"); cp++;
//printf("cMN: %d %s\n", i_monsterNoteID, cp);

	if ((of = fopen(mybuf1, "a+")) != NULL) {
		fprintf(of, "+%d|%d|%s\n", i_monsterNoteID, i_monsterNoteID, cp);
		fclose(of);
	}
}

/******************************************************************************/
void duplicatePlayer(int plyr, int cnt) {
	int j=0, s, e;

//printf("dP: %d %d\n", plyr, cnt);
	if (cnt == 0) { return; }
	if (plyr >= MAX_PLAYERS) { s=MAX_PLAYERS; e=MAX_MEMBERS; } else { s=0; e=MAX_PLAYERS; }

	for (int i=s;  i < e; i++) {
		if (players[i].c_name[0] == '\0' && players[i].i_hp[HP_MAX] == 0) {
if (config.flags.f_debug != 0) printf("dP: %d %d\n", plyr, i);
			memcpy(&players[i].c_name[0], &players[plyr].c_name[0], sizeof(ADMPplayer));
			if (players[i].c_name[2] == '-') {
				players[i].c_name[0] = identifiers[i];
			} else {
				sprintf(mybuf2, "%c - %s", identifiers[i], players[i].c_name);
				strncpy(players[i].c_name, mybuf2, 29);
			}
			players[i].flags.f_isStabilised = 0; // players[i].flags.f_autoStablise = 0;
			players[i].flags.f_disabled = 0; 
			players[i].i_initiative[1] = getRND(20);
			players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX];
			players[i].i_mapX = players[i].i_mapY = players[i].i_inGroup = -1;
			for (j=0; j<MAX_D20ROLLS; j++) {
				if (config.i_diceSystem == DICE_D20) {
					players[i].i_d20Rolls[j] = getRND(20);
				} else {
					players[i].i_d20Rolls[j] = getRND(100);
				}
			}
			strcpy(players[i].c_iconFile, a_EdtQkMonstIconFilename->value());
			if (players[i].c_iconFile[0] == '\0') {
				strcpy(players[i].c_iconFile, players[plyr].c_iconFile);
			}
				// copy std monster notes to the new monster
			if (plyr == (MAX_MEMBERS+1)) {
				i_monsterNoteID = i;
					// delete the old note just incase
				sprintf(mybuf1, "%s.mnt", config.c_monstFilename);
				sprintf(mybuf2, "%d", i);
				pdbDeleteRecord(mybuf1, mybuf2, NULL, NULL);
					// find it and copy it over
//printf("dP: SMnote %d = %d (%d)\n", i_srdMonsterID, i, players[plyr].flags.f_srdMonster);
				sprintf(mybuf2, "%d", i_srdMonsterID);
				if (players[i].flags.f_srdMonster != 0) {
					sprintf(mybuf2, "%d", players[i].i_stdMonsterID);
					pdbKeySearch("stdmonster.snt", copyMonsterNotes, NULL, 1, mybuf2, NULL, NULL);
				} else {
					pdbKeySearch("srdmonster.snt", copyMonsterNotes, NULL, 1, mybuf2, NULL, NULL);
				}
				//players[i].i_stdMonsterID = i_srdMonsterID; 
			}
			cnt--;
			if (cnt == 0)
			  break;
		}
	}
	if (cnt > 0) {
		sprintf(mybuf2, "Unable to add all the monsters. %d left to add\nMax Monsters = MAX_MONSTERS", cnt);
		doSystemAlert(mybuf2);
	}
}

/******************************************************************************/
void doEditSpecialActions(int action) {
	int i, j;

if (config.flags.f_debug != 0) { printf("dESA: %d %d\n", action, config.i_editID); }

	if (action > -1 && (config.i_editID < 0 || config.i_editID > MAX_MEMBERS)) {
		return;
	}

	i = config.i_editID;

	switch (action) {
		case 0: 
				  if (players[i].i_mapX > 0) {
						combatGridMap->getGridTile()->removeObject(players[i].i_mapX, players[i].i_mapY);
						players[i].i_mapX = players[i].i_mapY = -1;
				  }
				  memset(&players[i].c_name[0], '\0', sizeof(ADMPplayer));		// delete
				  players[i].flags.f_disabled = 1;
				  cancelEdit();
				  sprintf(mybuf1, "%s.mnt", config.c_monstFilename);
				  sprintf(mybuf2, "%d", i);
				  pdbDeleteRecord(mybuf1, mybuf2, NULL, NULL);
				  doInitiativeAction(2);		// reload & refresh the init lists
				  doInitiativeAction(3);
				  break;

		case 1: savePlayer(i);
				  duplicatePlayer(i, 1);
				  doIconAction(1);
				  break;

		case 2: savePlayer(i);
				  duplicatePlayer(i, 2);
				  doIconAction(1);
				  break;

		case 3: savePlayer(i);
				  duplicatePlayer(i, 4);
				  doIconAction(1);
				  break;

		case 4: // save as a standard monster
				  actionQkMonsters(-1);
				  break;

		case 5: savePlayer(i);			// resequence ids
				  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d\n", i); }
				  			for (j=MAX_PLAYERS; j<MAX_MEMBERS && j < i; j++) {
								if (players[j].c_name[0] == '\0' && players[j].i_hp[HP_MAX] == 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d %d\n", i, j); }
									memcpy(&players[j].c_name[0], &players[i].c_name[0], sizeof(ADMPplayer));
									players[j].c_name[0] = identifiers[j];
									memset(&players[i].c_name[0], '\0', sizeof(ADMPplayer));
				  					players[i].flags.f_disabled = 1;
									if (players[j].i_mapX > 0) {
										combatGridMap->getGridTile()->setGridPointId(players[j].i_mapX, players[j].i_mapY, j);
									}
									break;
								}
							}
						}
				  }
				  a_OTDisableList->clear();
				  for (i=0; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
							a_OTDisableList->add(players[i].c_name);
							config.i_idList[ID_DISA][j++] = i;
						}
				  }
				  a_OTDisableList->redraw();
				  doIconAction(1);
				  break;

		case 6:	// move to be a player
				  for (i=0; i<MAX_PLAYERS; i++) {
						if (players[i].c_name[0] == '\0' && players[i].i_hp[HP_MAX] == 0) {
				  			memcpy(&players[i].c_name[0], &players[config.i_editID].c_name[0], sizeof(ADMPplayer));		// copy it
				  			memset(&players[config.i_editID].c_name[0], '\0', sizeof(ADMPplayer));		// delete the old one
							players[i].c_name[0] = i + 48;
							break;
						}
					}
				  break;

		case -1: 	// resequence ids
				  for (i=0; i<MAX_PLAYERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d\n", i); }
				  			for (j=0; j<MAX_PLAYERS && j < i; j++) {
								if (players[j].c_name[0] == '\0' && players[j].i_hp[HP_MAX] == 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d %d\n", i, j); }
									memcpy(&players[j].c_name[0], &players[i].c_name[0], sizeof(ADMPplayer));
									players[j].c_name[0] = identifiers[j];
									memset(&players[i].c_name[0], '\0', sizeof(ADMPplayer));
				  					players[i].flags.f_disabled = 1;
									if (players[j].i_mapX > 0) {
										combatGridMap->getGridTile()->setGridPointId(players[j].i_mapX, players[j].i_mapY, j);
									}
									break;
								}
							}
						}
				  }
				  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d\n", i); }
				  			for (j=MAX_PLAYERS; j<MAX_MEMBERS && j < i; j++) {
								if (players[j].c_name[0] == '\0' && players[j].i_hp[HP_MAX] == 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d %d\n", i, j); }
									memcpy(&players[j].c_name[0], &players[i].c_name[0], sizeof(ADMPplayer));
									players[j].c_name[0] = identifiers[j];
									memset(&players[i].c_name[0], '\0', sizeof(ADMPplayer));
				  					players[i].flags.f_disabled = 1;
									if (players[j].i_mapX > 0) {
										combatGridMap->getGridTile()->setGridPointId(players[j].i_mapX, players[j].i_mapY, j);
									}
									break;
								}
							}
						}
				  }
				  a_OTDisableList->clear();
				  for (i=0; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
							a_OTDisableList->add(players[i].c_name);
							config.i_idList[ID_DISA][j++] = i;
						}
				  }
				  a_OTDisableList->redraw();
				  doIconAction(1);
				  break;

		case -2: 	// delete
				if (doAreYouSure("Are you sure ?") == 1) {
					i=a_OTDisableList->nitems();

					for (; i>0; i--) {
						if (a_OTDisableList->checked(i) == 1) {
								j = config.i_idList[ID_DISA][i-1];
				  				if (players[j].i_mapX > 0) {
									combatGridMap->getGridTile()->removeObject(players[j].i_mapX, players[j].i_mapY);
									players[j].i_mapX = players[j].i_mapY = -1;
								}
								memset(&players[j].c_name[0], '\0', sizeof(ADMPplayer));
							}
					}
					externalGridMap->repaint();

					reloadNames(0);

					a_OTDisableList->clear();

					for (i=0; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
							a_OTDisableList->add(players[i].c_name);
							config.i_idList[ID_DISA][j++] = i;
						}
					}
					a_OTDisableList->redraw();
				}
				break;
		}
		reloadNames(0);
}

/********************************************************************************/
Fl_Window *alertWindow=NULL;
Fl_Button *alertButton=NULL;
Fl_Output *alertMessage=NULL;

static void cb_acceptAlertButton(Fl_Button*, void*) {
  alertWindow->hide();
}

/********************************************************************************/
void doSystemAlert(char *msg) {
	if (alertWindow == NULL) {
		alertWindow = new Fl_Window(440, 70, "ADMP: Alert Message");
		alertWindow->labelsize(ADMP_LABEL_SIZE);
		{ alertMessage = new Fl_Output(1, 1, 434, 40);
		  alertMessage->type(4);
		  alertMessage->labelsize(ADMP_LABEL_SIZE);
		  alertMessage->textsize(ADMP_TEXT_SIZE);
		}
		{ alertButton = new Fl_Button(198, 43, 55, 25, "OK");
		  alertButton->labelsize(ADMP_LABEL_SIZE);
		  alertButton->callback((Fl_Callback*)cb_acceptAlertButton);
		}
		alertWindow->set_modal();
		alertWindow->end();
	}
	alertMessage->value(msg);
	alertWindow->show();
	alertButton->take_focus();
}

/********************************************************************************/
Fl_Window *AYSWindow=NULL;
Fl_Output *AYSMessage=NULL;

/********************************************************************************/
int doAreYouSure(char *msg) {
int AYSreturn = -1;			// Assume No

	if (AYSWindow == NULL) {
		AYSWindow = new Fl_Window(350, 70, "ADMP: Are You Sure ??");
		AYSWindow->labelsize(ADMP_LABEL_SIZE);
		{ AYSMessage = new Fl_Output(1, 1, 344, 40);
		  AYSMessage->type(4);
		  AYSMessage->labelsize(ADMP_LABEL_SIZE);
		  AYSMessage->textsize(ADMP_TEXT_SIZE+1);
		}
		{ AYSButton[0] = new Fl_Button(120, 43, 55, 25, "Yes");
		  AYSButton[0]->labelsize(ADMP_LABEL_SIZE);
		}
		{ AYSButton[1] = new Fl_Button(198, 43, 55, 25, "No");
		  AYSButton[1]->labelsize(ADMP_LABEL_SIZE);
		}
		{ AYSButton[2] = new Fl_Button(260, 43, 85, 25, "Maybe");
		  AYSButton[2]->labelsize(ADMP_LABEL_SIZE);
		}
		AYSButton[2]->deactivate();
		AYSWindow->end();
	}
	AYSWindow->set_modal();
	if (msg == NULL) {		// check to see if it's just to configure it
		return -1;
	}

	AYSMessage->value(msg);
	AYSWindow->show();
	for (;;) {
		Fl_Widget *o = Fl::readqueue();
		if (!o) {
			Fl::wait();
		} else if ( o == AYSButton[0]) { AYSreturn = 1; break;
		} else if ( o == AYSButton[1]) { AYSreturn = -1; break;
		} else if ( o == AYSButton[2]) { AYSreturn = -2; break;
		}
	}
	AYSWindow->hide();
	return AYSreturn;
}

/********************************************************************************/
int rollDice(char *dice) { //, int *mult, int *die, int *plus) {
int roll[3] = {1,0,0};		/* xDy+z */
int i=0,j=0,d=-1, result=0;
char mybuf[25]; //, *cp;

	strncpy(mybuf, dice, 24); mybuf[24] = '\0';
if (config.flags.f_debug) { printf("pD: %s\n", dice); }

/*
	if ((cp = strstr(mybuf, " + ")) != NULL) {
		*cp = '\0';
		cp++; cp++; cp++;
		result += parseDice(cp);
	} else if ((cp = strstr(mybuf, " - ")) != NULL) {
		*cp = '\0';
		cp++; cp++; cp++;
		result += parseDice(cp);
	}
*/

	while (mybuf[i] != '\0') {
		if (mybuf[i] == 'D' || mybuf[i] == 'd') {
			mybuf[i] = '\0'; roll[0] = atoi(mybuf); j = i+1;
			d=i;
		} else if (mybuf[i] == '+' || mybuf[i] == '-') {
			roll[2] = atoi(&mybuf[i]); mybuf[i] = '\0'; roll[1] = atoi(&mybuf[j]); 
		}
//if (config.flags.f_debug) { printf("pD: %d %s = %d/%d/%d\n", i, dice, roll[0], roll[1], roll[2]); }
		i++;
	}
		// check for a XdY string
	if (roll[1] == 0) {
		roll[1] = atoi(&mybuf[j]);
	}

	if (roll[0] == 0) {
		roll[0] = 1;
	}

	if (d == -1) {
		result += atoi(dice);
//if (config.flags.f_debug) { printf("pD: %s = %d/%d/%d = %d\n", dice, roll[0], roll[1], roll[2], j); }
	} else {
//if (config.flags.f_debug) { printf("pD: %s = %d/%d/%d = ", dice, roll[0], roll[1], roll[2]); }
		result += roll[2];
		while (roll[0] > 0) {
			result += getRND(roll[1]);
			roll[0] --;
		}
		if (result < 1) {
			result = 1;
		}
if (config.flags.f_debug != 0) { printf("pD: %s = %d\n", dice, result); }
	}
//printf("rD: %s = %d\n", dice, result);

	return result;
}
/********************************************************************************/
int parseDice(char *dice) { //, int *mult, int *die, int *plus) {
int i=0, j=0, t=0, sign=1;
char dicebuf[30] = {""};

//printf("pD: %s\n", dice);

	strncpy(dicebuf, dice, 30); dicebuf[29] = '\0';

	while (dicebuf[i] != '\0') {
		if (dicebuf[i] == '+' || dicebuf[i] == '-') {
			if (i == 0 && dicebuf[i] == '-') { 
				sign = -1; 
			} else {
				dicebuf[i] = '\0';
				t += rollDice(&dicebuf[j]) * sign;
				sign = 1;
				if (dice[i] == '-') { 
					if (i == 0) { sign = 1; } else { sign = -1; }
				}
			}
			j = i+1;
		}
		i++;
	}
	t += rollDice(&dicebuf[j]) * sign;

//printf("pD: Total = %d\n", t);

	return t;
}

/********************************************************************************/
int parseCritical(char *crit, int dice, int *from, int *to, int *mult) {
int roll[3] = {20,20,2};		// x-y,*z - assume 20/*2
int i=0,j=0;
char mybuf[15];

	strncpy(mybuf, crit, 14); mybuf[14] = '\0';

	while (mybuf[i] != '\0') {
		if (mybuf[i] == '-') {
			mybuf[i] = '\0'; roll[0] = atoi(&mybuf[j]); j = i+1;
		} else if (mybuf[i] == '/') {
			mybuf[i] = '\0'; roll[1] = atoi(&mybuf[j]); j = i+1;
		} else if (mybuf[i] == '*' || mybuf[i] == 'x') {
			mybuf[i] = '\0'; roll[2] = atoi(&mybuf[i+1]); j = i+1;
		}
		i++;
	}

if (config.flags.f_debug != 0) { printf("pC: %s = %d/%d/%d (%d)\n", crit, roll[0], roll[1], roll[2], dice); }
//printf("pC: %s = %d/%d/%d (%d)\n", crit, roll[0], roll[1], roll[2], dice);

	*from = roll[0];
	*to = roll[1];
	*mult = roll[2];

	if (dice >= roll[0]) {
		return roll[2];
	}

	*mult = 2;

	return 2;		// return the standard *2 critical multiplier

}

/********************************************************************************/
void loadMonsterFile() {
	int i=0,j=0;
	ADMPplayer p[MAX_MONSTERS];
	char *iname, *cp;

	if (config.f_version < 1.11) {
		if ((iname = fl_file_chooser("Monster Load", "*.dat", config.c_monstFilename, 1)) == NULL) {
			return;
		}
	} else {
		if ((iname = fl_file_chooser("Monster Load", "*.mon", config.c_monstFilename, 1)) == NULL) {
			return;
		}
	}

	if (strlen(iname) > 42) { doSystemAlert("Monster Load file name is too long ... it may not SAVE !!!!"); }

	for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
		if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
			j++;
		}
	}

if (config.flags.f_debug != 0) { printf("lMF: %s %d\n", iname, j); }
	memset(&p[0].c_name[0], '\0', sizeof(ADMPplayer)*MAX_MONSTERS);
	if (config.f_version < 1.11) {
		if ((openf = fopen(iname, "r")) != NULL) {
			fread(&p[0].c_name[0], sizeof(ADMPplayer) * MAX_MONSTERS, 1, openf);
			fclose(openf);
		} else {
			return;
		}
	} else {	
			 // remove the file extension
		if ((cp = strrchr(iname, '.')) != NULL) { *cp = '\0'; }
		readAllMonsterData(iname, &p[0]);
	}

	if (strncasecmp(iname, systemDir, strlen(systemDir)-1) != 0) {
		if ((cp = strrchr(iname, directorySep[0])) != NULL) {
			cp++;
			strncpy(config.c_monstFilename, cp, 43);
		} else {
			strncpy(config.c_monstFilename, iname, 43);
		}
	} else {
		strncpy(config.c_monstFilename, &iname[strlen(systemDir)], 43);
	}
	config.c_monstFilename[43] = '\0';
	aSys_monsterFilename->value(config.c_monstFilename);

if (config.flags.f_debug != 0) { printf("lMF: %s\n", config.c_monstFilename); }
	if (j > 0) {
		if (doAreYouSure("Shall I merge them in ?") == 1) {
			for (i=0; i<MAX_MONSTERS; i++) {
				if (p[i].c_name[0] != '\0' && p[i].i_hp[HP_MAX] > 0) {
					for (j=MAX_PLAYERS; j<MAX_MEMBERS; j++) {
						if (players[j].c_name[0] == '\0' && players[j].i_hp[HP_MAX] == 0) {
							memcpy(&players[j].c_name[0], &p[i].c_name[0], sizeof(ADMPplayer));
							if (players[j].c_name[2] == '-') {
								players[j].c_name[0] = identifiers[j];
							} else {
								sprintf(mybuf2, "%c - %s", identifiers[j], players[j].c_name);
								strncpy(players[j].c_name, mybuf2, 29); players[j].c_name[29] = '\0';
							}
							break;
						}
					}
				}
			}
		} else {
			memset(&players[MAX_PLAYERS].c_name[0], '\0', sizeof(ADMPplayer)*MAX_MONSTERS);
			memcpy(&players[MAX_PLAYERS].c_name[0], &p[0].c_name[0], sizeof(ADMPplayer) * MAX_MONSTERS);
		}
	} else {
		memset(&players[MAX_PLAYERS].c_name[0], '\0', sizeof(ADMPplayer)*MAX_MONSTERS);
		memcpy(&players[MAX_PLAYERS].c_name[0], &p[0].c_name[0], sizeof(ADMPplayer) * MAX_MONSTERS);
	}

	reloadNames(0);
	doOtherAction(20);

	doIconAction(1);
}

/********************************************************************************/
void loadPlayerFile() {
	int j=0;
	FILE *fp=NULL;
	char *iname, *cp;

	if (config.f_version < 1.11) {
		if ((iname = fl_file_chooser("Player Load", "*.dat", config.c_partyFilename, 1)) == NULL) {
			return;
		}
	} else {
		if ((iname = fl_file_chooser("Player Load", "*.pty", config.c_partyFilename, 1)) == NULL) {
			return;
		}
	}

	if (strlen(iname) > 42) { doSystemAlert("Player Load file name is too long ... it may not SAVE !!!!"); }

if (config.flags.f_debug != 0) { printf("lPF: %s %d\n", iname, j); }

		// cleanup the filename
	if (strncasecmp(iname, systemDir, strlen(systemDir)-1) != 0) {
		if ((cp = strrchr(iname, directorySep[0])) != NULL) {
			cp++;
			strncpy(config.c_partyFilename, cp, 43);
		} else {
			strncpy(config.c_partyFilename, iname, 43);
		}
	} else {
		strncpy(config.c_partyFilename, &iname[strlen(systemDir)], 43);
	}
	config.c_partyFilename[43] = '\0';

	if (config.f_version < 1.11) {
		if ((fp = fopen(iname, "r")) != NULL) {
			fread(&players[0].c_name[0], sizeof(ADMPplayer) * MAX_PLAYERS, 1, fp);
			fclose(fp);
		} else {
			sprintf(mybuf1, "Unable to load Party File (%s)", iname);
			doSystemAlert(mybuf1);
		}
	} else {	
			 // remove the file extension
		if ((cp = strrchr(config.c_partyFilename, '.')) != NULL) { *cp = '\0'; }
		readAllPlayerData(config.c_partyFilename);
	}
	aSys_playerFilename->value(config.c_partyFilename);

if (config.flags.f_debug != 0) { printf("lPF: %s\n", config.c_partyFilename); }

	doIconAction(1);

	reloadNames(0);
	doOtherAction(20);
}

/********************************************************************************/
void saveMonsterFile() {
	int i=0;
	FILE *fp=NULL;
	char *iname, *cp;

	if (config.f_version < 1.11) {
		if ((iname = fl_file_chooser("Monster Save", "*.dat", config.c_monstFilename, 1)) == NULL) {
			return;
		}
		if ((fp = fopen(iname, "w")) != NULL) {
			fwrite(&players[MAX_PLAYERS].c_name[0], sizeof(ADMPplayer) * MAX_MONSTERS, 1, fp);
			fchmod(i, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
			fclose(fp);
		} else {
			sprintf(mybuf1, "Unable to save Monster File (%s)", iname);
			doSystemAlert(mybuf1);
		}
	} else {
		if ((iname = fl_file_chooser("Monster Save", "*.mon", config.c_monstFilename, 1)) == NULL) {
			return;
		}
		writeAllMonsterData(config.c_monstFilename);
	}

	if (strncasecmp(iname, systemDir, strlen(systemDir)-1) != 0) {
		if ((cp = strrchr(iname, directorySep[0])) != NULL) {
			cp++;
			strncpy(config.c_monstFilename, cp, 43);
		} else {
			strncpy(config.c_monstFilename, iname, 43);
		}
	} else {
		strncpy(config.c_monstFilename, &iname[strlen(systemDir)], 43);
	}
	config.c_monstFilename[43] = '\0';
	aSys_monsterFilename->value(config.c_monstFilename);
}

/********************************************************************************/
void doInitiativeAction(int action) {
int i=0, x=25, y=230, j=0, a=0, b=0, k=0, rms=0, initSort[MAX_MEMBERS];

if (config.flags.f_debug != 0) { printf("dIA: %d\n", action); }

	if (config.i_diceSystem != DICE_D20) { rms = 55; }

	switch (action) {
		case 1:		// reload
		case 2:		// refresh
//			for (j=0; j < MAX_MEMBERS; j++) { config.i_idList[ID_TEMP][j] = -1; }
			j = 0;
			x=20; y=230;
			for (i=0; i < MAX_PLAYERS; i++) {
				if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0 // && getHPs(i) > -10) {
				 && isDead(i) == 0) {
					if (config.i_diceSystem != DICE_D20) {
						if (w_InitiativesSelected[j] == NULL) {
							w_InitiativesSelected[j] = new Fl_Choice(x, y, 50, 20);
							w_InitiativesSelected[j]->labelsize(ADMP_LABEL_SIZE);
							w_InitiativesSelected[j]->textsize(ADMP_TEXT_SIZE);
							w_InitiativesSelected[j]->add("None"); w_InitiativesSelected[j]->add("Spell"); w_InitiativesSelected[j]->add("Missile");
							w_InitiativesSelected[j]->add("Move"); w_InitiativesSelected[j]->add("Melee");
							w_InitiativesSelected[j]->value(0);
							a_IPlayers->add(w_InitiativesSelected[j]);
						}
					}
					if (w_Initiatives[j] == NULL) {
						w_Initiatives[j] = new Fl_Input(x+rms, y, 25, 20);
						w_Initiatives[j]->type(2);
						w_Initiatives[j]->labelsize(ADMP_LABEL_SIZE);
						w_Initiatives[j]->textsize(ADMP_TEXT_SIZE);
						w_Initiatives[j]->align(FL_ALIGN_RIGHT);
						a_IPlayers->add(w_Initiatives[j]);
					}
					y += 25;
					w_Initiatives[j]->label(players[i].c_name);
					w_Initiatives[j]->activate();
					if (config.i_diceSystem != DICE_D20) { w_InitiativesSelected[j]->value(0); }
					w_Initiatives[j]->tooltip("Add their roll to this value if you're doing New initiatives");
					if (action == 2) {
						sprintf(mybuf1, "%d", players[i].i_initiative[1]);
						w_Initiatives[j]->value(mybuf1);
					} else {
						if (config.flags.f_rollInitRolls != 0 || config.flags.f_rollAllRolls != 0) {
							players[i].i_initiative[1] = getRND(20) + getAdjustment(i, MOD_INIT) + players[i].i_initiative[0];
							sprintf(mybuf1, "%d", players[i].i_initiative[1]);
						} else {
							sprintf(mybuf1, "+%d", players[i].i_initiative[0] + getAdjustment(i, MOD_INIT));
						}
						w_Initiatives[j]->value(mybuf1);
					}
					config.i_idList[ID_TEMP][j] = i;
					j++;
				}
			}
			for (; j < MAX_PLAYERS; j++) {
				if (w_Initiatives[j] != NULL) {
					w_Initiatives[j]->label("");
					w_Initiatives[j]->tooltip("");
					w_Initiatives[j]->deactivate();
				}
				config.i_idList[ID_TEMP][j] = -1;
			}
			x=205; y=230; j = MAX_PLAYERS;
			for (i=MAX_PLAYERS; i < MAX_MEMBERS; i++) {
				if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0 //&& getHPs(i) > -10) {
				 && isDead(i) == 0) {
						// if they are unconcious and the system flag set, dont show 'em
					if (config.flags.f_removeMonstersInit != 0 && getHPs(i) <= players[i].i_unconciousAt) {
if (config.flags.f_debug != 0) { printf("dIA: 2a %d %d %d\n", i, getHPs(i), players[i].i_unconciousAt); }
						;
					} else {
if (config.flags.f_debug != 0) { printf("dIA: 2 %d\n", i); }
						if (config.i_diceSystem != DICE_D20) {
							if (w_InitiativesSelected[j] == NULL) {
								w_InitiativesSelected[j] = new Fl_Choice(x, y, 50, 20);
								w_InitiativesSelected[j]->labelsize(ADMP_LABEL_SIZE);
								w_InitiativesSelected[j]->textsize(ADMP_TEXT_SIZE);
								w_InitiativesSelected[j]->add("None"); w_InitiativesSelected[j]->add("Spell"); w_InitiativesSelected[j]->add("Missile");
								w_InitiativesSelected[j]->add("Move"); w_InitiativesSelected[j]->add("Melee");
								w_InitiativesSelected[j]->value(0);
								a_IMonsters->add(w_InitiativesSelected[j]);
							}
						}
						if (w_Initiatives[j] == NULL) {
							w_Initiatives[j] = new Fl_Input(x+rms, y, 25, 20);
							w_Initiatives[j]->type(2);
							w_Initiatives[j]->labelsize(ADMP_LABEL_SIZE);
							w_Initiatives[j]->textsize(ADMP_TEXT_SIZE);
							w_Initiatives[j]->align(FL_ALIGN_RIGHT);
							a_IMonsters->add(w_Initiatives[j]);
						}
						y += 23;
						if (y > 655) { 
							y = 230;
							if (config.i_diceSystem != DICE_D20) {
								x += 250;
							} else {
								x += 150;
							}
						}
						w_Initiatives[j]->label(players[i].c_name);
						if (action != 2) {
							players[i].i_initiative[1] = getRND(20) + players[i].i_initiative[0];
						}
						sprintf(mybuf1, "%d", players[i].i_initiative[1]);
						w_Initiatives[j]->value(mybuf1);
						w_Initiatives[j]->activate();
						if (config.i_diceSystem != DICE_D20) { w_InitiativesSelected[j]->value(0); }
						config.i_idList[ID_TEMP][j] = i;
						j++;
					}
				}
			}
			for (; j < MAX_MEMBERS; j++) {
				if (w_Initiatives[j] != NULL) {
					w_Initiatives[j]->label("");
					w_Initiatives[j]->deactivate();
				}
				config.i_idList[ID_TEMP][j] = -1;
			}
			break;

		case 3:		// accept or do
			if (config.i_diceSystem == DICE_D20) {
				a=0;
				for (i=0; i<MAX_MEMBERS; i++) {
					j = config.i_idList[ID_TEMP][i];
					if (config.i_idList[ID_TEMP][i] != -1) {
if (config.flags.f_debug != 0) { printf("dIA: 3 %d:%d:%d\n", a, i, j); }
						players[config.i_idList[ID_TEMP][i]].i_initiative[1] = atoi(w_Initiatives[i]->value());
						config.i_idList[ID_INIT][a++] = j;
					}
				}
				for (; a<MAX_MEMBERS; a++) { config.i_idList[ID_INIT][a] = -1; }
	
				for (b=0; b<MAX_MEMBERS; b++) {
					for (i=0; i<MAX_MEMBERS; i++) {
						if (config.i_idList[ID_INIT][i+1] != -1) {
							k = players[config.i_idList[ID_INIT][i+1]].i_initiative[1];
							j = players[config.i_idList[ID_INIT][i]].i_initiative[1];
							if (k > j) {
								a = config.i_idList[ID_INIT][i];
								config.i_idList[ID_INIT][i] = config.i_idList[ID_INIT][i+1];
								config.i_idList[ID_INIT][i+1] = a;
							}
						}
					}
				}
			} else {			// TODO d100 INIT calcs
				a = 0;
				for (b=1; b<6; b++) {
					for (i=0; i < MAX_MEMBERS; i++) { initSort[i] = -1; }
					for (i=0; i<MAX_MEMBERS; i++) {
						if (config.i_idList[ID_TEMP][i] != -1) {
							if (w_InitiativesSelected[i]->value() == b) {
//printf("dIA:3 1 %d = %d\n", a, config.i_idList[ID_TEMP][i]);
								switch (aSys_initSystem->value()) {
									case 0:		// standard d100
												k = MAX_MONSTERS - (atoi(w_Initiatives[i]->value()) + getAdjustment(config.i_idList[ID_TEMP][i], MOD_INIT));
												break;
									case 1:		// d12,d8,d6		TODO
												k = MAX_MONSTERS - (atoi(w_Initiatives[i]->value()) + getAdjustment(config.i_idList[ID_TEMP][i], MOD_INIT));
												break;
								}
								if (initSort[k] == -1) {
									initSort[k] = config.i_idList[ID_TEMP][i];
//printf("dIA:3 2 %d = %d:%d\n", a, k, config.i_idList[ID_TEMP][i]);
								} else {
									for ( ; k<MAX_MEMBERS; k++) {
										if (initSort[k] == -1) {
											initSort[k] = config.i_idList[ID_TEMP][i];
//printf("dIA:3 3 %d = %d\n", k, config.i_idList[ID_TEMP][i]);
											break;
										}
									}
								}
							}
						}
					}
					for (j=0; j < MAX_MEMBERS; j++) { 
						if (initSort[j] != -1) {
							config.i_idList[ID_INIT][a++] = initSort[j];
						}
					}
				}
				for (; a<MAX_MEMBERS; a++) {
					config.i_idList[ID_INIT][a] = -1;
				}
			}
			reloadNames(1);
//			for (i=0; i<MAX_MEMBERS; i++) { printf("dIA: 3: %d = %d\n", i, config.i_idList[ID_INIT][i]); }
			break;
	}

	a_IPlayers->redraw();
	a_IMonsters->redraw();
}

/********************************************************************************/
void acceptCombatAction(int action) {
	int i, j, k, l, m, n;
	int ndef=0;

if (config.flags.f_debug != 0) { printf("aCA: %d:%d:%d\n", action, config.i_actionSelected, config.i_actionRecvID); }
	switch (action) {
		case 0:	// accept this melee attack
				  if (config.i_actionRecvID == -1) {
						doSystemAlert("Please select a DEFENDER !!!!");
						return;
				  }
				  if (isDefenderShown(config.i_actionRecvID) == -1) { return; }

				  i = getHPs(config.i_actionRecvID);
				  l = atoi(a_CTMeleeDamage->value());
				  if (l != 0) { 
						l += atoi(a_CTMeleeDmgAdjustments->value()); 
						players[config.i_actionRecvID].flags.f_isStabilised = players[config.i_actionRecvID].flags.f_autoStablise;		// if they take damage, make them 'un-stabilised' if possible
				  }
						// apply any damage reduction but only magic weapon type
if (config.flags.f_debug != 0) { printf("aCA: DR: %d %d %d %d\n", players[config.i_actionRecvID].i_damageReduction[1], players[config.i_actionRecvID].i_damageReduction[0], players[config.i_actionInitID].w_weapons[config.i_actionWeaponSelected].i_magicalBonus, players[config.i_actionRecvID].i_damageReduction[2]); }
					if (players[config.i_actionRecvID].i_damageReduction[1] != 0 && players[config.i_actionRecvID].i_damageReduction[0] == 1 && players[config.i_actionInitID].w_weapons[config.i_actionWeaponSelected].i_magicalBonus < players[config.i_actionRecvID].i_damageReduction[2]) {
if (config.flags.f_debug != 0) { printf("aCA: DR\n"); }
						if (l > players[config.i_actionRecvID].i_damageReduction[1]) {
							l -= players[config.i_actionRecvID].i_damageReduction[1];
						} else {
							l = 0;
						}
					}
				  		// is it subdual damage
				  if (a_CTSpecialAttacks->checked(2) == 0) {
				  		players[config.i_actionRecvID].i_hp[HP_CUR] -= l;
				  } else {
				  		players[config.i_actionRecvID].i_hp[HP_NL] += l;
				  }
				  players[config.i_actionRecvID].i_inactive += atoi(a_CTMeleeInactive->value());
				  if (players[config.i_actionRecvID].flags.f_ignoreBleed == 0) { players[config.i_actionRecvID].i_bleeding += atoi(a_CTMeleeBleeding->value()); }
				  if (players[config.i_actionRecvID].flags.f_ignoreStun == 0) { players[config.i_actionRecvID].i_stun += atoi(a_CTMeleeStun->value()); }
				  if (getHPs(config.i_actionRecvID) <= players[config.i_actionRecvID].i_unconciousAt && i > players[config.i_actionRecvID].i_unconciousAt) {
						sprintf(mybuf2, "%s is now unconcious !!", players[config.i_actionRecvID].c_name);
//						if (getHPs(config.i_actionRecvID) < -9) {
						if (isDead(config.i_actionRecvID) == 1) {
							sprintf(mybuf2, "%s is now splattered (truely DEAD!) !!", players[config.i_actionRecvID].c_name);
						} else if (getHPs(config.i_actionRecvID) < -4) {
							sprintf(mybuf2, "%s is now whupped bad !!", players[config.i_actionRecvID].c_name);
						}
						writeLog(mybuf2);
						doSystemAlert(mybuf2);
				  } else if (getHPs(config.i_actionRecvID) <= players[config.i_actionRecvID].i_disabledAt && i > players[config.i_actionRecvID].i_disabledAt) {
						sprintf(mybuf2, "%s is now disabled !!", players[config.i_actionRecvID].c_name);
						writeLog(mybuf2);
						doSystemAlert(mybuf2);
				  }
				  		// if its not an Op. Action, decrement the #attacks
				  if (a_CTSpecialAttacks->checked(1) == 0) {
							// set the defender and weapon used
						i = players[config.i_actionInitID].i_doneAttacks;
						players[config.i_actionInitID].i_whomAttacked[i][0] = config.i_actionRecvID;
						players[config.i_actionInitID].i_whomAttacked[i][1] = config.i_actionWeaponSelected;
if (config.flags.f_debug != 0) { printf("--- aCA: 0 %d:%d:%d\n", i, config.i_actionRecvID, config.i_actionWeaponSelected); }

				  		players[config.i_actionInitID].i_doneAttacks++;
				  		players[config.i_actionInitID].w_weapons[config.i_actionWeaponSelected].i_doneAttacks++;
				  }
				  sprintf(mybuf2, "  %d", (players[config.i_actionInitID].i_noAttacks - players[config.i_actionInitID].i_doneAttacks)); a_CTAttacksLeft->value(mybuf2);
				  if (config.flags.f_logfile != 0) {
						sprintf(mybuf2, "Melee: %s -> %s (HP:%d Bd:%d St:%d In:%d) Cur:%d", players[config.i_actionInitID].c_name, players[config.i_actionRecvID].c_name, l, atoi(a_CTMeleeBleeding->value()), atoi(a_CTMeleeStun->value()), atoi(a_CTMeleeInactive->value()), getHPs(config.i_actionRecvID));
						writeLog(mybuf2);
				  }
				  sprintf(mybuf2, "@B223@.%s takes HP:%d Bd:%d St:%d In:%d", players[config.i_actionRecvID].c_name, l, atoi(a_CTMeleeBleeding->value()), atoi(a_CTMeleeStun->value()), atoi(a_CTMeleeInactive->value()));
				  i = (players[config.i_actionInitID].i_doneAttacks);
				  if (i < 0) { i = 0; }
				  if (i > 6) { i = 6; }
				  a_CTMessage->text(7+i, mybuf2);
				  setCombatDisplay(2);
				  a_CTallAttacksDone->activate();
//				  a_CTMessage->text(2, ""); 
//				  a_CTMessage->text(3, "");
//				  a_CTMessage->text(4, ""); 
//				  a_CTMessage->text(1, ""); 
// 			  a_CTMessage->text(5, ""); a_CTMessage->text(6, ""); a_CTMessage->text(7, "");
				  break;

		case 1:	// all melee attacks done
				  if (players[config.i_actionInitID].i_doneAttacks == 0) {
				  		players[config.i_actionInitID].i_doneAttacks++;
				  }
				  reloadNames(1);
				  setCombatDisplay(0);
				  a_ActionWindow->hide();
				  break;

		case 2:	// accept this spell attack
				  i = a_CTSpellEffects->nitems();
				  for (; i>=1; i--) {
						if (a_CTSpellEffects->checked(i) == 1) {
							j = config.i_idList[ID_DEFD][i-1];
if (config.flags.f_debug != 0) { printf("aCA: %d:%d:%d\n", action,i,j); }
				  			k = getHPs(j);
							l = parseDice((char *)a_CTSpellDamage->value());
							if (l != 0) { l += atoi(a_CTSpellDmgMods->value()); }

							if (a_CTSpellSaved->checked(i) == 1 || a_CTSpellModifiers->checked(3) != 0) {		// they didnt save ....
								if (a_CTSpellEnergyType->checked(1) == 0) {
									m = a_CTSpellEnergyType->value() - 2;
									n = players[j].i_resistances[m] - players[j].i_resistancesUsed[m];
//printf("ET: T:%d HP:%d %d\n", m, n, l);
									if (n > 0) {
										if (n > l) {
											players[j].i_resistancesUsed[m] += l; l = 0;
										} else {
											players[j].i_resistancesUsed[m] += n; l -= n;
										}
										if (l < 0) { l = 0; }
//printf("ET: T:%d HP:%d %d\n", m, n, l);
									}
								}
						  		players[j].i_hp[HP_CUR] -= l;
						  		players[j].i_inactive += atoi(a_CTSpellInactive->value());
						  		if (players[j].flags.f_ignoreBleed == 0) { players[j].i_bleeding += atoi(a_CTSpellBleeding->value()); }
						  		if (players[j].flags.f_ignoreStun == 0) { players[j].i_stun += atoi(a_CTSpellStunned->value()); }
								players[j].flags.f_isStabilised = players[j].flags.f_autoStablise;	// if they take damage, make them 'un-stabilised'
								sprintf(mybuf2, "Spell: %s -> %s (HP:%d Bd:%d St:%d In:%d) Cur:%d", players[config.i_actionInitID].c_name, players[j].c_name, l, atoi(a_CTSpellBleeding->value()), atoi(a_CTSpellStunned->value()), atoi(a_CTSpellInactive->value()), getHPs(j));
				  				a_CTMessage->text(4+ndef, mybuf2);
				  				if (config.flags.f_logfile != 0) {
										writeLog(mybuf2);
				  				}
								ndef++;
							} else {
								if (a_CTSpellModifiers->checked(2) == 1) {	// NO Damage
									;
								} else if (a_CTSpellModifiers->checked(1) == 1) {	// 50% Damage
									l /= 2;
									if (a_CTSpellEnergyType->checked(1) == 0) {
										m = a_CTSpellEnergyType->value() - 2;
										n = players[j].i_resistances[m] - players[j].i_resistancesUsed[m];
//printf("ET: T:%d HP:%d %d\n", m, n, l);
										if (n > 0) {
											if (n > l) {
												players[j].i_resistancesUsed[m] += l; l = 0;
											} else {
												players[j].i_resistancesUsed[m] += n; l -= n;
											}
											if (l < 0) { l = 0; }
//printf("ET: T:%d HP:%d %d\n", m, n, l);
										}
									}
							  		players[j].i_hp[HP_CUR] -= l;
							  		players[j].i_inactive += atoi(a_CTSpellInactive->value()) / 2;
									if (players[j].flags.f_ignoreBleed == 0) { players[j].i_bleeding += atoi(a_CTSpellBleeding->value()) / 2; }
							  		if (players[j].flags.f_ignoreStun == 0) { players[j].i_stun += atoi(a_CTSpellStunned->value()) / 2; }
									players[j].flags.f_isStabilised = players[j].flags.f_autoStablise;	// if they take damage, make them 'un-stabilised'
									sprintf(mybuf2, "Spell: %s -> %s (HP:%d Bd:%d St:%d In:%d) Cur:%d", players[config.i_actionInitID].c_name, players[j].c_name, l, atoi(a_CTSpellBleeding->value())/2, atoi(a_CTSpellStunned->value())/2, atoi(a_CTSpellInactive->value())/2, getHPs(j));
				  					a_CTMessage->text(4+ndef, mybuf2);
					  				if (config.flags.f_logfile != 0) {
										writeLog(mybuf2);
					  				}
									ndef++;
								}
							}
				  			if (getHPs(j) <= players[j].i_unconciousAt && k > players[j].i_unconciousAt) {
								sprintf(mybuf2, "%s is now unconcious !!", players[j].c_name);
//								if (getHPs(config.i_actionRecvID) < -9) {
								if (isDead(config.i_actionRecvID) == 1) {
									sprintf(mybuf2, "%s is now splatted (truely DEAD!) !!", players[config.i_actionRecvID].c_name);
								} else if (getHPs(config.i_actionRecvID) < -4) {
									sprintf(mybuf2, "%s is now whupped bad !!", players[config.i_actionRecvID].c_name);
								}
								writeLog(mybuf2);
								doSystemAlert(mybuf2);
						  } else if (getHPs(j) <= players[j].i_disabledAt && k > players[j].i_disabledAt) {
								sprintf(mybuf2, "%s is now disabled !!", players[j].c_name);
								writeLog(mybuf2);
								doSystemAlert(mybuf2);
						  }
						}
				  }
				  if (a_CTSpellModifiers->checked(5) == 1) {	// Remove from spell slot count
						i = (int )a_CTSpellLevel->value();
				  		if (config.flags.f_logfile != 0) {
							sprintf(mybuf2, "Spell Slot Used: %s (%d) SL: %d", players[config.i_actionInitID].c_name, config.i_actionInitID, i);
							writeLog(mybuf2);
				  		}
						if (i == 0) { players[config.i_actionInitID].spellsAvailable.i_curLevel0--; }
						if (i == 1) { players[config.i_actionInitID].spellsAvailable.i_curLevel1--; }
						if (i == 2) { players[config.i_actionInitID].spellsAvailable.i_curLevel2--; }
						if (i == 3) { players[config.i_actionInitID].spellsAvailable.i_curLevel3--; }
						if (i == 4) { players[config.i_actionInitID].spellsAvailable.i_curLevel4--; }
						if (i == 5) { players[config.i_actionInitID].spellsAvailable.i_curLevel5--; }
						if (i == 6) { players[config.i_actionInitID].spellsAvailable.i_curLevel6--; }
						if (i == 7) { players[config.i_actionInitID].spellsAvailable.i_curLevel7--; }
						if (i == 8) { players[config.i_actionInitID].spellsAvailable.i_curLevel8--; }
						if (i == 9) { players[config.i_actionInitID].spellsAvailable.i_curLevel9--; }
				  }
				  players[config.i_actionInitID].i_doneAttacks++;
				  setCombatDisplay(2);
				  a_CTSpellAllDone->activate();
				  break;

		case 3:	// all spell attacks done
				  reloadNames(1);
				  setCombatDisplay(0);
				  a_ActionWindow->hide();
				  break;

		case 4:	// other
				  players[config.i_actionInitID].i_doneAttacks++;
				  switch (config.i_actionSelected) {
						case 7:	// healing
								  if (a_CTOtherActions->nchecked() == 0) {
										doSystemAlert("Please select a person who is effected by this action !!!!");
										return;
								  }
								  config.i_actionRecvID = -1;
								  for (i=a_CTOtherActions->nitems(); i>=0; i--) {
									  if (a_CTOtherActions->checked(i) == 1) {
										  config.i_actionRecvID = config.i_idList[ID_DEFD][i-1];
										  if (a_CTOtherFlags->checked(1) != 0) {
										  	players[config.i_actionRecvID].flags.f_isStabilised = 1;
										  }
										  l = parseDice((char *)a_CTOtherHealHP->value());
										  players[config.i_actionRecvID].i_hp[HP_CUR] += l;
										  players[config.i_actionRecvID].i_inactive -= atoi(a_CTOtherHealInactive->value());
										  if (players[config.i_actionRecvID].flags.f_ignoreBleed == 0) { players[config.i_actionRecvID].i_bleeding -= atoi(a_CTOtherHealBleeding->value()); }
										  if (players[config.i_actionRecvID].flags.f_ignoreStun == 0) { players[config.i_actionRecvID].i_stun -= atoi(a_CTOtherHealStun->value()); }
										  if (getHPs(config.i_actionRecvID) > getMaxHPs(config.i_actionRecvID)) { players[config.i_actionRecvID].i_hp[HP_CUR] = getMaxHPs(config.i_actionRecvID); }
										  if (players[config.i_actionRecvID].i_inactive < 0) { players[config.i_actionRecvID].i_inactive = 0; }
										  if (players[config.i_actionRecvID].i_bleeding < 0) { players[config.i_actionRecvID].i_bleeding = 0; }
										  if (players[config.i_actionRecvID].i_stun < 0) { players[config.i_actionRecvID].i_stun = 0; }
						  				  if (config.flags.f_logfile != 0) {
												sprintf(mybuf2, "Heal: %s -> %s (HP:%d Bd:%d St:%d In:%d Sb:%d) Cur:%d", players[config.i_actionInitID].c_name, players[config.i_actionRecvID].c_name, l, atoi(a_CTOtherHealBleeding->value()), atoi(a_CTOtherHealStun->value()), atoi(a_CTOtherHealInactive->value()), a_CTOtherFlags->checked(1), getHPs(config.i_actionRecvID));
												writeLog(mybuf2);
						  				  }
					  				  }
				  				  }
								  if (a_CTOtherFlags->checked(2) != 0 && config.i_actionRecvID != -1) { 		// remove from spell slot
										i = (int )a_CTOtherSpellLevel->value();
				  				  		if (config.flags.f_logfile != 0) {
											sprintf(mybuf2, "Spell Slot Used: %s (%d) SL: %d", players[config.i_actionInitID].c_name, config.i_actionInitID, i);
											writeLog(mybuf2);
				  				  		}
										if (i == 0) { players[config.i_actionInitID].spellsAvailable.i_curLevel0--; }
										if (i == 1) { players[config.i_actionInitID].spellsAvailable.i_curLevel1--; }
										if (i == 2) { players[config.i_actionInitID].spellsAvailable.i_curLevel2--; }
										if (i == 3) { players[config.i_actionInitID].spellsAvailable.i_curLevel3--; }
										if (i == 4) { players[config.i_actionInitID].spellsAvailable.i_curLevel4--; }
										if (i == 5) { players[config.i_actionInitID].spellsAvailable.i_curLevel5--; }
										if (i == 6) { players[config.i_actionInitID].spellsAvailable.i_curLevel6--; }
										if (i == 7) { players[config.i_actionInitID].spellsAvailable.i_curLevel7--; }
										if (i == 8) { players[config.i_actionInitID].spellsAvailable.i_curLevel8--; }
										if (i == 9) { players[config.i_actionInitID].spellsAvailable.i_curLevel9--; }
								  }
								  break;

						case 8:	// turning
				  				  if (config.flags.f_logfile != 0) {
										sprintf(mybuf2, "Turning Attempt: %s", players[config.i_actionInitID].c_name);
										writeLog(mybuf2);
				  				  }
								  break;

						case 9:	// skill check -- remove the last d20 roll
				  				  if (config.flags.f_logfile != 0) {
										sprintf(mybuf2, "Skill Check: %s", players[config.i_actionInitID].c_name);
										writeLog(mybuf2);
				  				  }
								  for (i=7; i>-1; i--) {
										if (players[config.i_actionRecvID].i_d20Rolls[i] > 0) {
											players[config.i_actionRecvID].i_d20Rolls[i] = 0;
											break;
										}
								  }
								  break;
				  }
				  reloadNames(1);
				  setCombatDisplay(0);
				  a_ActionWindow->hide();
				  break;
	}
	externalGridMap->getGridTile()->redraw();
}

/********************************************************************************/
int getMaxHPs(int p) {
	return (players[p].i_hp[HP_MAX] + players[p].i_hp[HP_TMP] + getAdjustment(p, MOD_HP));
}

/********************************************************************************/
int getHPs(int p) {
	return (players[p].i_hp[HP_CUR] + players[p].i_hp[HP_TMP] - players[p].i_hp[HP_NL] + getAdjustment(p, MOD_HP));
}

/********************************************************************************/
int getHPpercentage(int p) {
int i=0; 

	if (players[p].i_hp[HP_MAX] == 0) { return 100; }

	i = getHPs(p);
if (config.flags.f_debug != 0) { printf("gHPP: %d %d:%d\n", p, i, players[p].i_hp[HP_MAX]); }
	if (i < 0) {
		if (config.flags.f_deathAtCON == 1) {
			if (players[p].i_abilityStats[1][ABILITY_CON] != 0) {
				return int((i * 100) / players[p].i_abilityStats[1][ABILITY_CON]);
			} else if (players[p].i_abilityStats[0][ABILITY_CON] != 0) {
				return int((i * 100) / players[p].i_abilityStats[0][ABILITY_CON]);
			}
		}
		return (10 * i);
	} else if (i == 0) {
		return 0;
	} else {
		return int((i * 100) / players[p].i_hp[HP_MAX]);
	}
}

/********************************************************************************/
int calcAction(int action) {
int i=0, j=0, k=0, a=0;

	switch (action) {
		case 0:	// melee
				  a = config.i_actionWeaponSelected;
				  if (a == -1) {
						doSystemAlert("Please select a Weapon to use !!!");
				  }
				  if (isDefenderShown(config.i_actionRecvID) == -1) { return 0; }

				  a_CTMeleeDamage->value(""); a_CTMeleeInactive->value(""); a_CTMeleeBleeding->value(""); a_CTMeleeStun->value("");
				  a_CTMessage->text(4, "");
				  i = (atoi(a_CTMeleeBAB->value()) + atoi(a_CTMeleeBABAdjustments->value()) - (atoi(a_CTMeleeAC->value()) + atoi(a_CTMeleeACAdjustments->value()))) + atoi(a_CTMeleeRoll->value());
				  j = atoi(a_CTMeleeRoll->value());
				  if (config.flags.f_oneMissTwentyHits != 0) {
						if (j == 1) { i = -1; }		// force a miss
						if (j == 20) { i = 1; }		// force a hit
if (config.flags.f_debug != 0) { printf("cA: 1M %d:%d\n", j, i); }
				  }
if (config.flags.f_debug != 0) { printf("cA: PC %d\n", i); }
				  if (i >= 0) {	// did they HIT them
						parseCritical(players[config.i_actionInitID].w_weapons[a].c_critical, atoi(a_CTMeleeRoll->value()), &i, &j, &k);
						if (atoi(a_CTMeleeRoll->value()) >= i && atoi(a_CTMeleeRoll->value()) <= j && players[config.i_actionRecvID].flags.f_ignoreCriticals == 0) {
							if (config.i_actionInitID >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0) {
				  				i = atoi(a_CTMeleeBAB->value()) + atoi(a_CTMeleeBABAdjustments->value()) - atoi(a_CTMeleeAC->value()) - atoi(a_CTMeleeACAdjustments->value()) + getRND(20);
if (config.flags.f_debug != 0) { printf("cA: CT %d\n", i); }
								if (i >= 0) {
									j = 0;
									for (; k > 0; k--) {
										j += parseDice(players[config.i_actionInitID].w_weapons[a].c_damage);
//printf("pC: rolled: %d\n", j);
									}
									a_CTMessage->text(4, "@B88@.!!! A CRITICAL Success ... you smacked 'em bad !!!");
								} else {
									j = parseDice(players[config.i_actionInitID].w_weapons[a].c_damage);
									a_CTMessage->text(4, "!!! Almost a CRITICAL Success ... bad luck !!!");
								}
								sprintf(mybuf1, "%d", j); a_CTMeleeDamage->value(mybuf1);
							} else {
								a_CTMessage->text(4, "@B88@.!!! A possible CRITICAL Success ... roll again !!!");
							}
						} else {
							if (config.i_actionInitID >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0) {
								sprintf(mybuf1, "%d", parseDice(players[config.i_actionInitID].w_weapons[a].c_damage)); a_CTMeleeDamage->value(mybuf1);
							}
							a_CTMessage->text(4, "@B63@.!!! Success ... you've hit them !!!");
						}
				  } else {
						a_CTMessage->text(4, "!!! You've missed them ... bad luck !!!");
				  }
				  break;

		case 1:	// spell
				  i = a_CTSpellEffects->nitems();
				  a = atoi(a_CTSpellDC->value());
				  for (; i >=1; i--) {
						if (a_CTSpellEffects->checked(i) == 1) {
							j = config.i_idList[ID_DEFD][i-1];
							if (j >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0) {
								k = getRND(20);
								switch (config.i_actionSelected) {
									case 1:	// damage spell
											  break;
									case 2:	// WILL spell
											  k += players[j].i_savingThrows[SAVE_WISDOM] + getAdjustment(j, MOD_SAVE) + getAdjustment(j, MOD_SAVE_WILL);
											  break;
									case 3:	// REF spell
											  k += players[j].i_savingThrows[SAVE_REFLEX] + getAdjustment(j, MOD_SAVE) + getAdjustment(j, MOD_SAVE_REFLEX);
											  break;
									case 4:	// FORT spell
											  k += players[j].i_savingThrows[SAVE_FORTITUDE] + getAdjustment(j, MOD_SAVE) + getAdjustment(j, MOD_SAVE_FORTITUDE);
											  break;
									case 5:	// touch attk spell
											  k = players[j].i_armorClass[AC_TOUCH] + getAdjustment(j, MOD_AC) - 1;
				  							  if (config.flags.f_oneMissTwentyHits != 0) {
													if (a == 1) { k = -100; }		// force a fail
													if (a == 20) { k = 100; }		// force a hit
				  							  }
											  break;
									case 6:	// ranged touch attk spell
											  k = players[j].i_armorClass[AC_TOUCH] + getAdjustment(j, MOD_AC) - 1;
				  							  if (config.flags.f_oneMissTwentyHits != 0) {
													if (a == 1) { k = -100; }		// force a fail
													if (a == 20) { k = 100; }		// force a hit
				  							  }
											  break;
								}
								if (a_CTSpellModifiers->checked(3) != 0) {		// No Save so force a fail
									k = -100;
								}
if (config.flags.f_debug != 0) { printf("cA: %d:%d:%d\n", i, j, k); }		// Handle Spell Resistance
								if (a_CTSpellModifiers->checked(4) == 1 && (players[j].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0)) {
									if (j >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0) {
										if ((players[j].i_spellResistance + getAdjustment(i, MOD_SPELL_RESISTANCE)) > (getRND(20) + a_CTSpellLevel->value())) {
											k = 100;
											a_CTSpellEffects->checked(i, 0);		// Uncheck it
										}
									} else {
										a_CTMessage->text(2, "@B88@.!!! Please roll Spell Resistances !!!");
									}
if (config.flags.f_debug != 0) { printf("cA: SR: %d:%d:%d\n", i, j, k); }
								}
								if (k >= (atoi(a_CTSpellDC->value()) + atoi(a_CTSpellMods->value()))) {
									a_CTSpellSaved->checked(i, 0);
										// if they have evasion & it's a REF spell they take no damage
									if (players[j].flags.f_evasion != 0 && config.i_actionSelected == 3 && a_CTSpellModifiers->checked(1) == 1) {
										a_CTSpellEffects->checked(i, 0);		// Uncheck it
									}
								} else {			// nope, didnt save
									a_CTSpellSaved->checked(i, 1);
								}
							} else {
								a_CTSpellSaved->checked(i, 1);
								if (players[j].i_spellResistance > 0 || getAdjustment(i, MOD_SPELL_RESISTANCE) > 0) {
									a_CTMessage->text(2, "@B88@.!!! Please roll Spell Resistances !!!");
								}
							}
						}
				  }
				  break;

		case 2:	// roll another d20
				  sprintf(mybuf2, "%d", getRND(20));
				  a_CTMeleeRoll->value(mybuf2);
				  break;

		case 3:	// calc damage anyway
				  j = parseDice(players[config.i_actionInitID].w_weapons[config.i_actionWeaponSelected].c_damage);
				  sprintf(mybuf1, "%d", j); a_CTMeleeDamage->value(mybuf1);
				  break;
	}
	return 0;
}

/********************************************************************************/
void actionQkMonsters(int action) {
int i=0, j=0, k=0;
char b1[30], b2[30], *cp;
FILE *nf;

	i = a_EdtQkMonList->value()-1;
	if (i < 0 && (action != 3 && action != -1)) {
		doSystemAlert("Please select a monster first !!!");
		return;
	}

if (config.flags.f_debug != 0) { printf("aQM: %d:%d:%d\n", i, config.i_idList[ID_QMON][i], config.i_editID); }
	switch (action) {
		case -1:		// standard monster save/update
				  savePlayer(config.i_editID);
				  if (i > -1) {
				  		if (doAreYouSure("This will over-write the selected Standard Monster ?") == 1) {
							j = config.i_idList[ID_QMON][i];
						  	memcpy(&qkmonsters[j].c_name[0], &players[config.i_editID].c_name[0],  sizeof(ADMPplayer));
						} else {
							return;
						}
				  } else {
					  for (j = 0; j < MAX_QKMONSTERS; j++) {
							if (strncmp(qkmonsters[j].c_name, "-- empty slot", 13) == 0 || qkmonsters[j].c_name[0] == '\0') {
if (config.flags.f_debug != 0) { printf("aQM: 0 %d:%d:%d:%d:%s\n", j, config.i_idList[ID_QMON][j], (int )a_EdtQkMonAddCtr->value(), config.i_editID, qkmonsters[j].c_name); }
					  			memcpy(&qkmonsters[j].c_name[0], &players[config.i_editID].c_name[0],  sizeof(ADMPplayer));
								qkmonsters[j].flags.f_srdMonster = 1;
								a_EdtQkMonAddCtr->value(1);
								a_EdtQkMonstIconFilename->value("");
								break;
							}
					  }
				  }
				  if (qkmonsters[j].c_name[1] == ' ' && qkmonsters[j].c_name[2] == '-') {
						memmove(&qkmonsters[j].c_name[0], &qkmonsters[j].c_name[4], 25);
				  }
				  reloadNames(0);
				  if (config.f_version > 1.10) {
						writeAllStdMonsterData("stdmonster");
				  }
				  // write out a note
					sprintf(mybuf2, "%d", qkmonsters[j].i_stdMonsterID);
					pdbDeleteRecord("stdmonster.snt", mybuf2, NULL, NULL);
					if ((nf = fopen("stdmonster.snt", "a+")) != NULL) {
						strncpy(mybuf1, edit_notes_buffer->text(),2047);
						while ((cp = strstr(mybuf1, "\n")) != NULL) {
							*cp = '|';
						}
						fprintf(nf, "+%d|%d|%s|\n", qkmonsters[j].i_stdMonsterID, qkmonsters[j].i_stdMonsterID, mybuf1);
						fclose(nf);
					}
				  break;

		case 0:	// add a std monster to the list of active monsters
				  if (config.flags.f_debug != 0) { printf("aQM: 0 %d:%d:%d\n", i, config.i_idList[ID_QMON][i], (int )a_EdtQkMonAddCtr->value()); }
				   i_srdMonsterID = config.i_idList[ID_QMON][i];
					memcpy(&players[MAX_MEMBERS+1].c_name[0], &qkmonsters[config.i_idList[ID_QMON][i]].c_name[0], sizeof(ADMPplayer));
					players[MAX_MEMBERS+1].i_mapX = players[MAX_MEMBERS+1].i_mapY = -1;
					duplicatePlayer(MAX_MEMBERS+1, (int )a_EdtQkMonAddCtr->value());
					a_EdtQkMonAddCtr->value(1);
					a_EdtQkMonstIconFilename->value("");
					reloadNames(0);
					doIconAction(1);
				  break;

		case 1:	// edit a std monster
				  a_EdtQkMonList->deactivate();
				  a_EdtQkMonstSearch->deactivate();
				  aEdit_AddQkMonsters->deactivate();
				  aEdit_EditQkMonsters->deactivate();
//				  aEdit_SaveQkMonsters->deactivate();
				  a_EdtQkMonCRSearch->deactivate();
				  aEdit_QkMonstersWildSearch->deactivate();
				  a_EdtQkMonAddCtr->deactivate();
				  a_EdtQkMonstIconFilename->deactivate();
				  aEdt_Accept->activate();
				  aEdt_Cancel->activate();
				  aEdt_QkMonsterAdd->deactivate();
				  memcpy(&players[MAX_MEMBERS+1].c_name[0], &qkmonsters[config.i_idList[ID_QMON][i]].c_name[0], sizeof(ADMPplayer));
if (config.flags.f_debug != 0) { printf("aQM: 1 %s (%d)\n", players[MAX_MEMBERS+1].c_name, config.i_idList[ID_QMON][i]); }
				  editPlayer(MAX_MEMBERS+1);
				  break;

		case 2:		// save them all but not sure if we need this bit
				  memcpy(&qkmonsters[config.i_idList[ID_QMON][i]].c_name[0], &players[MAX_MEMBERS+1].c_name[0], sizeof(ADMPplayer));
if (config.flags.f_debug != 0) { printf("aQM: 2 %s\n", players[MAX_MEMBERS+1].c_name); }
if (config.flags.f_debug != 0) { printf("aQM: 2 %s\n", qkmonsters[config.i_idList[ID_QMON][i]].c_name); }
		  		  sprintf(mybuf2, "%sqkmonst.dat", systemDir);
				  if ((openf = fopen(mybuf2, "w")) != NULL) {
						fwrite(&qkmonsters[0].c_name[0], sizeof(ADMPplayer) * MAX_QKMONSTERS, 1, openf);
						fchmod(i, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
				  		fclose(openf);
				  }
				  break;

		case 3:		// advanced search
				  j=0;
				  strncpy(b1, a_EdtQkMonstSearch->value(), 20); b1[19] = '\0';  mytolower(b1);
// if (config.flags.f_debug != 0) { printf("sQM: 3 %s : %s\n", b1, a_EdtQkMonstSearch->value()); }
				  a_EdtQkMonList->clear();
				  for (int i=0; i<MAX_QKMONSTERS; i++) {
					strncpy(b2, qkmonsters[i].c_name, 30); b2[29] = '\0'; mytolower(b2);
// if (config.flags.f_debug != 0) { printf("sQM: 3 %s : %s\n", b1, b2); }
			  		if (strstr(b2, b1) != NULL) {
						k=0;
						if (a_EdtQkMonCRSearch->value() > 0) {
							if ((int )a_EdtQkMonCRSearch->value() == (int )qkmonsters[i].f_challengeRating) {
								k = 1;
							}
						} else {
							k = 1;
						}
						if (k == 1) {
				  			sprintf(mybuf2, "%s (CR: %.1f)", qkmonsters[i].c_name, qkmonsters[i].f_challengeRating);
				  			a_EdtQkMonList->add(mybuf2);
				  			config.i_idList[ID_QMON][j++] = i;
				  			if (j > MAX_MEMBERS) {
				  				return;
				  			}
			  			}
			  		}
				  }
				  break;
	}
}

/********************************************************************************/
void searchQkMonsters(const char *name) {
	int i, j=0, k, l=0;

	a_EdtQkMonList->clear();
	qkMonsterAction(0);

if (config.flags.f_debug != 0) { printf("sQM: 0 %s:%d\n", name, a_EdtQkMonCREnvironment->value()); }
	k = strlen(name);
	for (i=0; i<MAX_QKMONSTERS; i++) {
		if (strncasecmp(qkmonsters[i].c_name, name, k) == 0) {
if (config.flags.f_debug != 0) { printf("sQM: 0 %s %.2f %d %d\n", qkmonsters[i].c_name, qkmonsters[i].f_challengeRating, qkmonsters[i].c_environment, a_EdtQkMonCREnvironment->value()); }
			j=0;
			if (a_EdtQkMonCRSearch->value() > 0) {
				if ((int )a_EdtQkMonCRSearch->value() == (int )qkmonsters[i].f_challengeRating) {
					if (a_EdtQkMonCREnvironment->value() > 0) {
						if (qkmonsters[i].c_environment == a_EdtQkMonCREnvironment->value()) {
							j = 1;
						}
					} else {
						j = 1;
					}
				}
			} else {
				if (a_EdtQkMonCREnvironment->value() > 0) {
					if (qkmonsters[i].c_environment == a_EdtQkMonCREnvironment->value()) {
						j = 1;
					}
				} else {
					j = 1;
				}
			}
			if (j == 1) {
				sprintf(mybuf2, "%s (CR: %.1f)", qkmonsters[i].c_name, qkmonsters[i].f_challengeRating);
				a_EdtQkMonList->add(mybuf2);
				config.i_idList[ID_QMON][l++] = i;
				if (l > MAX_MEMBERS) {
					return;
				}
			}
		}
	}
}

/********************************************************************************/
void doOtherAction(int action) {
int i=0, j=0, l=0, x=0, y=0;
struct tm *tp;
time_t t;
	
if (config.flags.f_debug != 0) { printf("dOA: %d\n", action); }

	switch (action) {
		case 0:	// reset players
				  for (i=0; i<MAX_PLAYERS; i++) {
						players[i].flags.f_isStabilised = players[i].i_hp[HP_TMP] = players[i].i_hp[HP_NL] = 0;
						players[i].i_initiative[1] = 0;
						players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX];
						players[i].i_bleeding = players[i].i_doneAttacks = players[i].i_stun = players[i].i_inactive = 0;
						players[i].i_roundsUntil[ROUND_DEATH] = 0;
//						if (players[i].i_mapX != -1 || players[i].i_mapY != -1) {
//							combatGridMap->setGridType(players[i].i_mapX, players[i].i_mapY, 0, 0);
//						}
//						players[i].i_mapX = players[i].i_mapY = -1;
							// players[i].flags.f_disabled = removed from the line above
						for (j=0; j<MAX_ATTACKS+2; j++) {
							players[i].w_weapons[j].i_doneAttacks = 0;
							players[i].i_whomAttacked[j][0] = players[i].i_whomAttacked[j][1] = -1;
						}
				  }
				  break;

		case 1:	// clean players
				  break;

		case 2:	// remove all players
				  if (doAreYouSure("Really remove all players ?") == 1) {
				  		memset(&players[0].c_name[0], '\0', sizeof(ADMPplayer)*MAX_PLAYERS);
				  }
				  sprintf(mybuf1, "%s.pnt", config.c_partyFilename);
				  pdbTruncate(mybuf1);
				  break;

		case 3:	// reset monsters
				  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						players[i].flags.f_isStabilised = players[i].i_hp[HP_TMP] = players[i].i_hp[HP_NL] = 0;
						players[i].i_initiative[1] = getRND(20);
						players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX];
						players[i].i_bleeding = players[i].i_doneAttacks = players[i].flags.f_disabled = players[i].i_stun = players[i].i_inactive = 0;
						players[i].i_roundsUntil[ROUND_DEATH] = 0;
//						if (players[i].i_mapX != -1 || players[i].i_mapY != -1) {
//							combatGridMap->setGridType(players[i].i_mapX, players[i].i_mapY, 0, 0);
//						}
//						players[i].i_mapX = players[i].i_mapY = -1;
						for (j=0; j<MAX_ATTACKS+2; j++) {
							players[i].w_weapons[j].i_doneAttacks = 0;
							players[i].i_whomAttacked[j][0] = players[i].i_whomAttacked[j][1] = -1;
						}
				  }
				  break;

		case 4:	// clean monsters
				  break;

		case 5:	// remove all monsters
				  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].i_mapX != -1 || players[i].i_mapY != -1) {
							combatGridMap->setGridType(players[i].i_mapX, players[i].i_mapY, 0, 0);
						}
				  }
				  memset(&players[MAX_PLAYERS].c_name[0], '\0', sizeof(ADMPplayer)*MAX_MONSTERS);
				  sprintf(mybuf1, "%s.mnt", config.c_monstFilename);
				  pdbTruncate(mybuf1);
				  externalGridMap->repaint();
				  break;

		case 6:	// clear alerts
				  for (i=0; i<MAX_TRIGGERS; i++) {
						sprintf(config.action_msgs[i].c_message, "-- empty slot %d", i);
						config.action_msgs[i].i_noRounds = config.action_msgs[i].i_display = 0;
						config.action_msgs[i].c_every[0] = '\0';
				  }
					a_OTTriggerList->clear();
					for (i=0; i<MAX_TRIGGERS; i++) {
						a_OTTriggerList->add(config.action_msgs[i].c_message);
					}
				  break;

		case 7:	// clear adjustments
				  for (i=0; i<MAX_MODIFIERS; i++) {
						sprintf(config.action_mods[i].c_message, "-- empty slot %d", i);
						config.action_mods[i].i_noRounds = 0;
						config.action_mods[i].i_whom[0] = config.action_mods[i].i_whom[1] = config.action_mods[i].i_idFollows = -255;
						config.action_mods[i].i_data[0][0] = config.action_mods[i].i_data[0][2] = 0; config.action_mods[i].i_data[0][1] = -1;
						config.action_mods[i].i_data[1][0] = config.action_mods[i].i_data[1][2] = 0; config.action_mods[i].i_data[0][1] = -1;
						config.action_mods[i].i_data[2][0] = config.action_mods[i].i_data[2][2] = 0; config.action_mods[i].i_data[0][1] = -1;
						config.action_mods[i].i_data[3][0] = config.action_mods[i].i_data[3][2] = 0; config.action_mods[i].i_data[0][1] = -1;
						config.action_mods[i].i_data[4][0] = config.action_mods[i].i_data[4][2] = 0; config.action_mods[i].i_data[4][1] = -1;
				  }
					a_OTAdjustList->clear();
					for (i=0; i<MAX_MODIFIERS; i++) {
						a_OTAdjustList->add(config.action_mods[i].c_message);
					}
					doQuickMods(-1, 0, 0);		// clear all quick mods
					doQuickMods(0, 0, 0);		// refresh quick mods screen
				  break;

		case 8:	// reset for a new combat ... reset the players and clear any triggers/adjustments etc
				  doOtherAction(0);
				  doOtherAction(3);
				  doOtherAction(6);
				  doOtherAction(7);
				  doOtherAction(10);
				  doOtherAction(11);
				  doInitiativeAction(1);
				  config.i_roundCount = 1; aSys_Rounds->value("1");
				  writeLog("**** Players reset for a new combat");
				  break;

		case 9:	// monster HP based on CR
				  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX] = parseDice(players[i].c_hitDice);
						}
				  }
				  break;

		case 10: // clear auto-damage lists
				  a_OTADList->clear();
				  for (i=0; i<MAX_AUTODAMAGE; i++) {
						config.auto_damage[i].i_initiatorID = config.auto_damage[i].i_whom[0] = -1;
						config.auto_damage[i].i_noRounds = config.auto_damage[i].i_type = 0;
						config.auto_damage[i].c_damage[0] = '\0';
						sprintf(config.auto_damage[i].c_description, "-- empty slot %d", i);
						config.auto_damage[i].flags.f_flag1 = config.auto_damage[i].flags.f_flag2 = 0;
						config.auto_damage[i].flags.f_flag3 = config.auto_damage[i].flags.f_flag4 = 0;
						config.auto_damage[i].flags.f_flag5 = config.auto_damage[i].flags.f_flag6 = 0;
						config.auto_damage[i].flags.f_flag7 = config.auto_damage[i].flags.f_flag8 = 0;
						config.auto_damage[i].i_doneRounds = 0;
				  		a_OTADList->add(config.auto_damage[i].c_description);
				  }
				  break;

		case 11: // new day stuff ... healing & spell slots
				  for (i=0; i<MAX_PLAYERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							players[i].i_hp[HP_CUR] += players[i].i_levels[0] + players[i].i_levels[1] + players[i].i_levels[2] + players[i].i_levels[3];
//							if (players[i].i_mapX != -1 || players[i].i_mapY != -1) {
//								combatGridMap->setGridType(players[i].i_mapX, players[i].i_mapY, 0, 0);
//							}
//							players[i].i_mapX = players[i].i_mapY = -1;
							if (players[i].i_hp[HP_CUR] > players[i].i_hp[HP_MAX]) {
								players[i].i_hp[HP_CUR] = players[i].i_hp[HP_MAX];
							}
							players[i].spellsAvailable.i_curLevel0 = players[i].spellsAvailable.i_maxLevel0;
							players[i].spellsAvailable.i_curLevel1 = players[i].spellsAvailable.i_maxLevel1;
							players[i].spellsAvailable.i_curLevel2 = players[i].spellsAvailable.i_maxLevel2;
							players[i].spellsAvailable.i_curLevel3 = players[i].spellsAvailable.i_maxLevel3;
							players[i].spellsAvailable.i_curLevel4 = players[i].spellsAvailable.i_maxLevel4;
							players[i].spellsAvailable.i_curLevel5 = players[i].spellsAvailable.i_maxLevel5;
							players[i].spellsAvailable.i_curLevel6 = players[i].spellsAvailable.i_maxLevel6;
							players[i].spellsAvailable.i_curLevel7 = players[i].spellsAvailable.i_maxLevel7;
							players[i].spellsAvailable.i_curLevel8 = players[i].spellsAvailable.i_maxLevel8;
							players[i].spellsAvailable.i_curLevel9 = players[i].spellsAvailable.i_maxLevel9;
							players[i].i_bleeding = players[i].i_doneAttacks = players[i].i_stun = players[i].i_inactive = 0;
							for (j=0; j<MAX_ATTACKS+2; j++) {
								players[i].w_weapons[j].i_doneAttacks = 0;
								players[i].i_whomAttacked[j][0] = -1;
							}
						}
				  }
				  doOtherAction(6);
				  doOtherAction(7);
				  doOtherAction(10);
				  doInitiativeAction(1);
				  config.i_roundCount = 1; aSys_Rounds->value("1");
				  writeLog("**** Players reset for a new day");
				  break;

		case 12:		// reset group details
				  for (i=0; i<MAX_GROUPS; i++) {
						sprintf(config.groups[i].c_description, "Group - %d", i);
				  }
				  for (i=0; i<MAX_MEMBERS; i++) {
						players[i].i_inGroup = -1;
				  }
				  doGroupAction(-1);
				  break;

		case 13:		// backup data files into archive file
				  saveAllData();
				  if (time(&t) != -1) {
						tp = localtime(&t);
				  		sprintf(mybuf2, "cd %s; zip -1q vcs-%2.2d%2.2d%2.2d-%2.2d%2.2d *.sys *.p?? *.m?? notes.txt", systemDir, tp->tm_year-100, tp->tm_mon+1, tp->tm_mday, tp->tm_hour, tp->tm_min);
//printf("Backup Cmd = %s\n", mybuf2);
						if (system(mybuf2) != 0) {
							doSystemAlert("Backup Failed ... sorry !!!");
						} else {
							doSystemAlert("Backup Complete ... excellent !!!");
						}
				  }
				  break;

		case 20:		// refresh status page
				  a_OStatusList->clear();
				  sprintf(mybuf1, "Round : %d", config.i_roundCount); a_OStatusList->add(mybuf1);
				  a_OStatusList->add("");
				  for (i=0; i<MAX_PLAYERS; i++) {
//						if (players[i].i_hp[HP_CUR] < 1) { j = players[i].i_hp[HP_CUR] * 10; }
//						else { j = (players[i].i_hp[HP_CUR] * 100) / players[i].i_hp[HP_MAX]; }
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							j = getHPpercentage(i);
							sprintf(mybuf1, "%-25.25s HP:%-3d/%-3d/%-3d %3d%% (%3d)  AC:%-2d/%-2d/%-2d  Bld:%-2d Stn:%-2d Ina:%-2d Sbl:%-2d Lvl:%d (%d) %s", players[i].c_name, getHPs(i), players[i].i_hp[HP_MAX], players[i].i_hp[HP_NL], j, abs(players[i].i_hp[HP_MAX] - getHPs(i)), players[i].i_armorClass[AC_NORMAL], players[i].i_armorClass[AC_TOUCH], players[i].i_armorClass[AC_FLATFOOTED], players[i].i_bleeding, players[i].i_stun, players[i].i_inactive, players[i].flags.f_isStabilised, (players[i].i_levels[0]+players[i].i_levels[1]+players[i].i_levels[2]+players[i].i_levels[3]), players[i].i_xp[MAX], players[i].c_items);
							if ((i % 2) == 0) {
								sprintf(mybuf2, "@B223@.%s", mybuf1);
								a_OStatusList->add(mybuf2);
							} else {
								a_OStatusList->add(mybuf1);
							}
						}
				  }
				  a_OStatusList->add("");
				  l = 0;
				  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
//printf("status: N = %d : %d : %d\n", players[i].c_name[0], players[i].i_hp[HP_MAX], players[i].flags.f_disabled);
//							if (players[i].i_hp[HP_CUR] < 1) { j = players[i].i_hp[HP_CUR] * 10; }
//							else { j = (players[i].i_hp[HP_CUR] * 100) / players[i].i_hp[HP_MAX]; }
							j = getHPpercentage(i);
							sprintf(mybuf1, "%-25.25s HP:%-3d/%-3d/%-3d %3d%%  AC:%-2d/%-2d/%-2d  Bld:%-2d Stn:%-2d Ina:%-2d Sbl:%-2d CR:%.1f %s", players[i].c_name, players[i].i_hp[HP_CUR], players[i].i_hp[HP_MAX], players[i].i_hp[HP_NL], j, players[i].i_armorClass[AC_NORMAL], players[i].i_armorClass[AC_TOUCH], players[i].i_armorClass[AC_FLATFOOTED], players[i].i_bleeding, players[i].i_stun, players[i].i_inactive, players[i].flags.f_isStabilised, players[i].f_challengeRating, players[i].c_items);
							if ((l % 2) == 0) {
								sprintf(mybuf2, "@B95@.%s", mybuf1);
								a_OStatusList->add(mybuf2);
							} else {
								a_OStatusList->add(mybuf1);
							}
							l++;
						}
				  }
				  break;

		case 30:		// add new monsters into a group
				a_addToNewGroup->hide();
				x = combatGridMap->getClickedX(), y = combatGridMap->getClickedY();

				for (j=0; j < MAX_GROUPS; j++) {
					if (strncasecmp(config.groups[j].c_description, "Group", 5) == 0) {
						strcpy(config.groups[j].c_description, a_addNewName->value());
						a_GroupList->text(j+1, config.groups[j].c_description);
//printf("add2NG: found group = %d\n", j);
						break;
					}
				}

				for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0 && players[i].i_mapX == -1) {
 						while (players[i].i_mapX == -1) {
							if (combatGridMap->getGridTile()->getGridPointType(x,y) == 0 && combatGridMap->getGridTile()->getGridPointColor(x,y) < 8) {
								combatGridMap->setGridType(x, y, GRID_MONSTER, i);
								players[i].i_inGroup = j;
								if (a_addNewDisabled->value() == 1) {
									players[i].flags.f_disabled = 1;
								}
//printf("add2NG: %d = %d/%d\n", i, j, players[i].flags.f_disabled);
							}
							x++;
							if (x % 3 == 0) { y++; x-=3; }
						}
					}
				}
				combatGridMap->repaint();		// it needs another for some reason
				break;

		case 40:		// remove from map
				i=a_OTDisableList->nitems();

				for (; i>0; i--) {
   				if (a_OTDisableList->checked(i) == 1) {
						j = config.i_idList[ID_DISA][i-1];
						combatGridMap->getGridTile()->removeObject(players[j].i_mapX, players[j].i_mapY);
						players[j].i_mapX = players[j].i_mapY = -1;
					}
				}
				break;

		case 41:		// set as hidden
				i=a_OTDisableList->nitems();

				for (; i>0; i--) {
   				if (a_OTDisableList->checked(i) == 1) {
						j = config.i_idList[ID_DISA][i-1];
						players[j].flags.f_invisible = 1;
					}
				}
				break;
	}
	reloadNames(0);
}

/********************************************************************************/
void calcCombatMods(int action) {
	int i=0,j=0,bab=0,ac=0;

if (config.flags.f_debug != 0) { printf("cCM: %d %d\n", action, a_CTCombatMods->value()); }

	switch (action) {
		case 0:	// melee
				for (i=0; ; i++) {
					if (combatmods[i].c_message[0] == '\0') { break; }
					if (a_CTCombatMods->checked(i+1) == 1) {
						switch (config.i_actionSelected) {
							case 0:	// melee
									  if (combatmods[i].i_modifications[0][1] == 0) {
									  		bab += combatmods[i].i_modifications[0][0];
									  } else if (combatmods[i].i_modifications[0][1] == 1) {
									  		ac += combatmods[i].i_modifications[0][0];
									  }
									  break;
						}
					}
				}
				sprintf(mybuf2, "%d", bab + getAdjustment(config.i_actionInitID, MOD_BAB)); a_CTMeleeBABAdjustments->value(mybuf2);
				sprintf(mybuf2, "%d", ac + getAdjustment(config.i_actionRecvID, MOD_AC)); a_CTMeleeACAdjustments->value(mybuf2);
				if (a_CTCombatMods->value() == 8) {		// Surprised/flat-footed
if (config.flags.f_debug != 0) { printf("cCM: %d %d\n", a_CTCombatMods->checked(8), a_CTCombatMods->value()); }
					if (a_CTCombatMods->checked(8) == 1) {
						sprintf(mybuf2, "%d", players[config.i_actionRecvID].i_armorClass[AC_FLATFOOTED]); a_CTMeleeAC->value(mybuf2);
					} else {
						sprintf(mybuf2, "%d", players[config.i_actionRecvID].i_armorClass[AC_NORMAL]); a_CTMeleeAC->value(mybuf2);
					}
				}
				if (a_CTCombatMods->checked(4) == 1 || a_CTCombatMods->checked(7) == 1 || a_CTCombatMods->checked(8) == 1 || a_CTCombatMods->checked(9) == 1 || a_CTCombatMods->checked(10) == 1) {
					a_CTMessage->text(2, "!!! You may need to adjust their A/C by their DEX !!!");
				}
				break;
		case 1:	// spells
				j = a_CTSpellModifiers->value();
if (config.flags.f_debug != 0) { printf("cCM: %d %d %d A\n", action, j, a_CTSpellModifiers->checked(j)); }
				if (j == 1) {		// Save = 50%
					a_CTSpellModifiers->checked(2, 0);
					a_CTSpellModifiers->checked(3, 0);
				} else if (j == 2) {	// Save = nothing
					a_CTSpellModifiers->checked(1, 0);
					a_CTSpellModifiers->checked(3, 0);
				} else if (j == 3) {	// NO Save
					a_CTSpellModifiers->checked(1, 0);
					a_CTSpellModifiers->checked(2, 0);
				}
if (config.flags.f_debug != 0) { printf("cCM: %d %d %d D\n", action, j, a_CTSpellModifiers->checked(j)); }
				if (a_CTSpellModifiers->checked(1) == 0 && a_CTSpellModifiers->checked(2) == 0 && a_CTSpellModifiers->checked(3) == 0) {
					a_CTSpellModifiers->checked(1, 1);		// you must have something checked
				}
				break;
	}
}

/********************************************************************************/
void doSpecialAttacks() {

if (config.flags.f_debug != 0) { printf("dSA: %d:%d:%d:%d:%d\n", a_CTSpecialAttacks->checked(1), a_CTSpecialAttacks->checked(2), a_CTSpecialAttacks->checked(3), a_CTSpecialAttacks->checked(4), a_CTSpecialAttacks->value()); }

	switch (a_CTSpecialAttacks->value()) {
		case 1:		// Op Act
				  break;
		case 2:		// Subdual Damage
				  break;
		case 3:		// Touch Attack
					if (a_CTSpecialAttacks->checked(4) == 1) { a_CTSpecialAttacks->checked(4, 0); } // only one of these
					sprintf(mybuf2, "%d", players[config.i_actionInitID].i_bab[BAB_MELEE][0]); a_CTMeleeBAB->value(mybuf2);
					if (a_CTSpecialAttacks->checked(3) == 1) { 	// set the A/C for a TA
						sprintf(mybuf2, "%d", players[config.i_actionRecvID].i_armorClass[AC_TOUCH]); a_CTMeleeAC->value(mybuf2);
					} else {
						sprintf(mybuf2, "%d", players[config.i_actionRecvID].i_armorClass[AC_NORMAL]); a_CTMeleeAC->value(mybuf2);
					}
				  break;
		case 4:		// Ranged touch attack
					if (a_CTSpecialAttacks->checked(3) == 1) { a_CTSpecialAttacks->checked(3, 0); } // only one of these
					sprintf(mybuf2, "%d", players[config.i_actionInitID].i_bab[BAB_RANGED][0]); a_CTMeleeBAB->value(mybuf2);
					if (a_CTSpecialAttacks->checked(4) == 1) { 	// set the A/C for a TA
						sprintf(mybuf2, "%d", players[config.i_actionRecvID].i_armorClass[AC_TOUCH]); a_CTMeleeAC->value(mybuf2);
					} else {
						sprintf(mybuf2, "%d", players[config.i_actionRecvID].i_armorClass[AC_NORMAL]); a_CTMeleeAC->value(mybuf2);
					}
				  break;
	}
	if (a_CTSpecialAttacks->checked(3) == 0 && a_CTSpecialAttacks->checked(4) == 0) { // set weapon BAB
		sprintf(mybuf2, "%d", getWeaponAttackBonus(config.i_actionInitID, config.i_actionWeaponSelected)); a_CTMeleeBAB->value(mybuf2);
	}
}

/********************************************************************************/
void doTriggerAction(int action) {
	int i = a_OTTriggerList->value() - 1;

	switch (action) {
		case 0:		// edit/add
					a_OTTriggerList->deactivate();
					a_OTTriggerRounds->activate();
					a_OTTriggerMessage->activate();
					a_OTTriggerEveryRound->activate();
					a_OTTriggerEvery->activate();
					a_OTTriggerAccept->activate();
					a_OTTriggerCancel->activate();
					a_OTTriggerMessage->value(config.action_msgs[i].c_message);
					sprintf(mybuf2, "%d", config.action_msgs[i].i_noRounds); a_OTTriggerRounds->value(mybuf2);
					a_OTTriggerEveryRound->value(config.action_msgs[i].i_display);
					a_OTTriggerEvery->value(config.action_msgs[i].c_every);
				  break;

		case 1:		// accept
					a_OTTriggerList->activate(); a_OTTriggerList->check_none();
					a_OTTriggerRounds->deactivate();
					a_OTTriggerMessage->deactivate();
					a_OTTriggerEveryRound->deactivate();
					a_OTTriggerEvery->deactivate();
					a_OTTriggerAccept->deactivate();
					a_OTTriggerCancel->deactivate();
					strncpy(config.action_msgs[i].c_message, a_OTTriggerMessage->value(), 59); config.action_msgs[i].c_message[59] = '\0';
					config.action_msgs[i].i_noRounds = atoi(a_OTTriggerRounds->value());
					config.action_msgs[i].i_display = a_OTTriggerEveryRound->value();
					strncpy(config.action_msgs[i].c_every, a_OTTriggerEvery->value(), 9); config.action_msgs[i].c_every[9] = '\0';
					a_OTTriggerList->clear();
					for (i=0; i<MAX_TRIGGERS; i++) {
						a_OTTriggerList->add(config.action_msgs[i].c_message);
					}
				  break;
		case 2:		// cancel
					a_OTTriggerList->activate();
					a_OTTriggerRounds->deactivate();
					a_OTTriggerMessage->deactivate();
					a_OTTriggerEveryRound->deactivate();
					a_OTTriggerEvery->deactivate();
					a_OTTriggerAccept->deactivate();
					a_OTTriggerCancel->deactivate();
					a_OTTriggerList->clear();
					for (i=0; i<MAX_TRIGGERS; i++) {
						a_OTTriggerList->add(config.action_msgs[i].c_message);
					}
				  break;

		case 9:		// refresh the list
					a_OTTriggerList->clear();
					for (i=0; i<MAX_TRIGGERS; i++) {
						a_OTTriggerList->add(config.action_msgs[i].c_message);
					}
				  break;
	}
}

/********************************************************************************/
void doAdjustmentAction(int action) {
	int i = a_OTAdjustList->value() - 1, j, k=0, z=0;

if (config.flags.f_debug != 0) { printf("dAA: %d:%d:%d\n", action, i, a_OTAdjustSystemList->value()); }
	switch (action) {
		case -1: 	// system adjustment selected
				  i = -1;
				  action = 0;

		case 0:		// edit/add
				   prev_part_selected = -1;
					a_OTAdjustList->deactivate();
					a_OTAdjustSystemList->deactivate(); 
					a_OTAdjustEffects->activate(); a_OTAdjustEffects->check_none();
					a_OTAdjustAccept->activate();
					a_OTAdjustCancel->activate();
					a_OTAdjustRounds->activate();
					a_OTAdjustMessage->activate();
					a_OTAdjustGroup->activate();

					a_OTAdjustValue1->value(""); a_OTAdjustValue2->value(""); a_OTAdjustValue3->value("");
					a_OTAdjustValue4->value(""); a_OTAdjustValue5->value("");
					a_OTAdjustType1->value(0); a_OTAdjustEffectsType1->value(0);
					a_OTAdjustType2->value(0); a_OTAdjustEffectsType2->value(0);
					a_OTAdjustType3->value(0); a_OTAdjustEffectsType3->value(0);
					a_OTAdjustType4->value(0); a_OTAdjustEffectsType4->value(0);
					a_OTAdjustType5->value(0); a_OTAdjustEffectsType5->value(0);

					a_OTAdjustEffects->clear();
					a_OTAdjustIDEnds->clear();
					a_OTAdjustEffects->add("All Players");
					a_OTAdjustEffects->add("All Monsters");
					k=0;
					config.i_idList[ID_ADJ1][k++] = -1;
					config.i_idList[ID_ADJ1][k++] = -2;
					for (j=0; j<MAX_MEMBERS; j++) {
						if (players[j].c_name[0] != '\0' && players[j].i_hp[HP_MAX] > 0 && players[j].flags.f_disabled == 0) {
							a_OTAdjustEffects->add(players[j].c_name);
							a_OTAdjustIDEnds->add(players[j].c_name);
if (config.flags.f_debug != 0) { printf("dAA: 0 A %d:%d\n", k, j); }
							config.i_idList[ID_ADJ1][k++] = j;
						}
					}
					config.i_idList[ID_ADJ1][k] = -255;
				  		// is it a predefined one
					if (i == -1 && a_OTAdjustSystemList->value() > 0) {
if (config.flags.f_debug != 0) { printf("dAA: 0 B\n"); }
						a_OTAdjustSystemSave->activate();
				   	i = a_OTAdjustSystemList->value() - 1;
						a_OTAdjustMessage->value(config.system_mods[i].c_message);
						sprintf(mybuf2, "%d", config.system_mods[i].i_noRounds); a_OTAdjustRounds->value(mybuf2);
						for (z=0; z<5; z++) {
							for (int x=0; x<3; x++) {
								adjustValues[z][x] = config.system_mods[i].i_data[z][x];
							}
if (config.flags.f_debug != 0) { printf("dAA: 0 C %d = %d:%d:%d\n", i, adjustValues[z][0], adjustValues[z][1], adjustValues[z][2]); }
						}
					} else {
						if (config.action_mods[i].i_whom[0] != -255) {
							for (j=0; j<MAX_MEMBERS && config.action_mods[i].i_whom[j] != -255; j++) {
								for (k=0; k<MAX_MEMBERS && config.i_idList[ID_ADJ1][k] != -255; k++) {
									if (config.action_mods[i].i_whom[j] == config.i_idList[ID_ADJ1][k]) {
if (config.flags.f_debug != 0) { printf("dAA: 2 D %d:%d:%d:%d\n", j,k,config.action_mods[i].i_whom[j],config.i_idList[ID_ADJ1][k]); }
										a_OTAdjustEffects->checked(k+1, 1);
									}
								}
							}
						}
						a_OTAdjustMessage->value(config.action_mods[i].c_message);
						sprintf(mybuf2, "%d", config.action_mods[i].i_noRounds); a_OTAdjustRounds->value(mybuf2);
						for (z=0; z<5; z++) {
							for (int x=0; x<3; x++) {
								adjustValues[z][x] = config.action_mods[i].i_data[z][x];
							}
if (config.flags.f_debug != 0) { printf("dAA: 0 c %d = %d:%d:%d\n", i, adjustValues[z][0], adjustValues[z][1], adjustValues[z][2]); }
						}
					}
					a_OTAdjustIDEnds->check_none();
					a_OTAdjustIDEnds->activate();
					if (config.action_mods[i].i_idFollows > -1) {
						for (j=0; j<MAX_MEMBERS && config.i_idList[ID_ADJ1][j] != -255; j++) {
							if (config.i_idList[ID_ADJ1][j] == config.action_mods[i].i_idFollows) {
								a_OTAdjustIDEnds->checked(j-1, 1);
if (config.flags.f_debug != 0) { printf("dAA: 0 F %d:%d:%d\n", j,config.action_mods[i].i_idFollows,config.i_idList[ID_ADJ1][j]); }
								break;
							}
						}
					}
					sprintf(mybuf1, "%d", adjustValues[0][0]); a_OTAdjustValue1->value(mybuf1);
					if (adjustValues[0][0] != 0) {
						a_OTAdjustType1->value(adjustValues[0][1]+0); a_OTAdjustEffectsType1->value(adjustValues[0][2]+0);
					}
					sprintf(mybuf1, "%d", adjustValues[1][0]); a_OTAdjustValue2->value(mybuf1);
					if (adjustValues[1][0] != 0) {
						a_OTAdjustType2->value(adjustValues[1][1]+0); a_OTAdjustEffectsType2->value(adjustValues[1][2]+0);
					}
					sprintf(mybuf1, "%d", adjustValues[2][0]); a_OTAdjustValue3->value(mybuf1);
					if (adjustValues[2][0] != 0) {
						a_OTAdjustType3->value(adjustValues[2][1]+0); a_OTAdjustEffectsType3->value(adjustValues[2][2]+0);
					}
					sprintf(mybuf1, "%d", adjustValues[3][0]); a_OTAdjustValue4->value(mybuf1);
					if (adjustValues[3][0] != 0) {
						a_OTAdjustType4->value(adjustValues[3][1]+0); a_OTAdjustEffectsType4->value(adjustValues[3][2]+0);
					}
					sprintf(mybuf1, "%d", adjustValues[4][0]); a_OTAdjustValue5->value(mybuf1);
					if (adjustValues[4][0] != 0) {
						a_OTAdjustType5->value(adjustValues[4][1]+0); a_OTAdjustEffectsType5->value(adjustValues[4][2]+0);
					}
				  break;
				  
		case 1:		// accept
						// if we're adding a predefined one, find the first empty slot
					i = whichChecked(a_OTAdjustList) - 1;
if (config.flags.f_debug != 0) { printf("dAA: 1 a %d\n", i); }

					a_OTAdjustList->activate(); a_OTAdjustList->check_none();
					a_OTAdjustSystemList->activate(); a_OTAdjustSystemList->check_none();
					a_OTAdjustEffects->deactivate();
					a_OTAdjustAccept->deactivate();
					a_OTAdjustCancel->deactivate();
					a_OTAdjustRounds->deactivate();
					a_OTAdjustMessage->deactivate();
					a_OTAdjustGroup->deactivate();
					a_OTAdjustSystemSave->deactivate();
					if (i == -1) {
						for (i=0; i<MAX_MODIFIERS; i++) {
							if (strncasecmp(config.action_mods[i].c_message, "-- empty slot", 13) == 0) { break; }
						}
					}
						// save whom it effects or follows
					config.action_mods[i].i_idFollows = -255;
					k=0; config.action_mods[i].i_whom[0] = -255;
					for (j=a_OTAdjustEffects->nitems(); j > 0; j--) {
						if (a_OTAdjustEffects->checked(j) == 1) {
if (config.flags.f_debug != 0) { printf("dAA: 1 B %d:%d:%d\n", j,k,config.i_idList[ID_ADJ1][j-1]); }
							config.action_mods[i].i_whom[k++] = config.i_idList[ID_ADJ1][j-1];
						}
						if (a_OTAdjustIDEnds->checked(j) == 1) {
if (config.flags.f_debug != 0) { printf("dAA: 1 C %d:%d\n", j,config.i_idList[ID_ADJ1][j+1]); }
							config.action_mods[i].i_idFollows = config.i_idList[ID_ADJ1][j+1];
						}
					}
					config.action_mods[i].i_whom[k] = -255;
					if (config.action_mods[i].i_whom[0] == -255) {
						doSystemAlert("You've not selected whom it will effect !!!!");
					}
					strncpy(config.action_mods[i].c_message, a_OTAdjustMessage->value(), 39); config.action_mods[i].c_message[39] = '\0';
					config.action_mods[i].i_noRounds = atoi(a_OTAdjustRounds->value());

					adjustValues[0][0] = atoi(a_OTAdjustValue1->value());
					adjustValues[0][1] = a_OTAdjustType1->value() - 0;
					adjustValues[0][2] = a_OTAdjustEffectsType1->value() - 0;
					adjustValues[1][0] = atoi(a_OTAdjustValue2->value());
					adjustValues[1][1] = a_OTAdjustType2->value();
					adjustValues[1][2] = a_OTAdjustEffectsType2->value() - 0;
					adjustValues[2][0] = atoi(a_OTAdjustValue3->value());
					adjustValues[2][1] = a_OTAdjustType3->value() - 0;
					adjustValues[2][2] = a_OTAdjustEffectsType3->value() - 0;
					adjustValues[3][0] = atoi(a_OTAdjustValue4->value());
					adjustValues[3][1] = a_OTAdjustType4->value() - 0;
					adjustValues[3][2] = a_OTAdjustEffectsType4->value() - 0;
					adjustValues[4][0] = atoi(a_OTAdjustValue5->value());
					adjustValues[4][1] = a_OTAdjustType5->value() - 0;
					adjustValues[4][2] = a_OTAdjustEffectsType5->value() - 0;

					for (z=0; z<5; z++) {
						for (int x=0; x<3; x++) {
							config.action_mods[i].i_data[z][x] = adjustValues[z][x];
						}
if (config.flags.f_debug != 0) { printf("dAA: 1 D %d = %d:%d:%d\n", i, adjustValues[z][0], adjustValues[z][1], adjustValues[z][2]); }
					}
					a_OTAdjustList->clear();
					for (i=0; i<MAX_MODIFIERS; i++) {
						a_OTAdjustList->add(config.action_mods[i].c_message);
					}
if (config.flags.f_debug != 0) { printf("dAA: 1 E %d:%d:%d:%d\n", config.action_mods[i].i_data[0][0], config.action_mods[i].i_data[1][0], config.action_mods[i].i_data[2][0], config.action_mods[i].i_data[3][0]); }
					a_OTAdjustIDEnds->check_none();
					a_OTAdjustIDEnds->deactivate();
				  break;

		case 2:		// cancel
					a_OTAdjustList->activate(); a_OTAdjustList->check_none();
					a_OTAdjustSystemList->activate(); a_OTAdjustSystemList->check_none();
					a_OTAdjustEffects->deactivate();
					a_OTAdjustAccept->deactivate();
					a_OTAdjustCancel->deactivate();
					a_OTAdjustRounds->deactivate();
					a_OTAdjustMessage->deactivate();
					a_OTAdjustGroup->deactivate();
					a_OTAdjustSystemSave->deactivate();
					a_OTAdjustIDEnds->check_none();
					a_OTAdjustIDEnds->deactivate();
				  break;

		case 3:		// adjustment part selected
				  break;

		case 7:		// save system
					adjustValues[0][0] = atoi(a_OTAdjustValue1->value());
					adjustValues[0][1] = a_OTAdjustType1->value() - 0;
					adjustValues[0][2] = a_OTAdjustEffectsType1->value() - 0;
					adjustValues[1][0] = atoi(a_OTAdjustValue2->value());
					adjustValues[1][1] = a_OTAdjustType2->value() - 0;
					adjustValues[1][2] = a_OTAdjustEffectsType2->value() - 0;
					adjustValues[2][0] = atoi(a_OTAdjustValue3->value());
					adjustValues[2][1] = a_OTAdjustType3->value() - 0;
					adjustValues[2][2] = a_OTAdjustEffectsType3->value() - 0;
					adjustValues[3][0] = atoi(a_OTAdjustValue4->value());
					adjustValues[3][1] = a_OTAdjustType4->value() - 0;
					adjustValues[3][2] = a_OTAdjustEffectsType4->value() - 0;
					adjustValues[4][0] = atoi(a_OTAdjustValue5->value());
					adjustValues[4][1] = a_OTAdjustType5->value() - 0;
					adjustValues[4][2] = a_OTAdjustEffectsType5->value() - 0;

				   i = a_OTAdjustSystemList->value() - 1;
					strncpy(config.system_mods[i].c_message, a_OTAdjustMessage->value(), 39); config.system_mods[i].c_message[39] = '\0';
					config.system_mods[i].i_noRounds = atoi(a_OTAdjustRounds->value());
					for (z=0; z<5; z++) {
						for (int x=0; x<3; x++) {
							config.system_mods[i].i_data[z][x] = adjustValues[z][x];
						}
if (config.flags.f_debug != 0) { printf("dAA: 7 D %d = %d:%d:%d\n", i, adjustValues[z][0], adjustValues[z][1], adjustValues[z][2]); }
					}
					a_OTAdjustSystemList->clear();
					for (i=0; i<MAX_MODIFIERS; i++) {
						a_OTAdjustSystemList->add(config.system_mods[i].c_message);
					}
					doAdjustmentAction(2);
				  break;

		case 8:		// selected an INIT to follow
				  i = a_OTAdjustIDEnds->nchecked();
if (config.flags.f_debug != 0) { printf("dAA: 2 %d:%d\n", i, a_OTAdjustIDEnds->value()); }
				  if (a_OTAdjustIDEnds->value() > 0 && i > 0) {
						i = a_OTAdjustIDEnds->value();
						a_OTAdjustIDEnds->check_none();
						a_OTAdjustIDEnds->checked(i, 1);
				  }
				  break;

		case 9:		// refresh the list
					a_OTAdjustList->clear();
					for (i=0; i<MAX_MODIFIERS; i++) {
						a_OTAdjustList->add(config.action_mods[i].c_message);
					}
					a_OTAdjustSystemList->clear();
					for (i=0; i<MAX_MODIFIERS; i++) {
						a_OTAdjustSystemList->add(config.system_mods[i].c_message);
					}
				  break;
	}
}

/********************************************************************************/
int getAdjustment(int plyr, int type) { 
int i=0, j=0, k, adj[MAX_ADJEFFECTTYPES+1], actype;

	for (i=0; i<MAX_ADJEFFECTTYPES+1; i++) { adj[i] = -255; }

	for (i=0; i<MAX_MODIFIERS; i++) {
		if (config.action_mods[i].i_noRounds > 0) {
if (config.flags.f_debug != 0) { printf("gA: 0 %s %d %d %d\n", config.action_mods[i].c_message, type, plyr, i); }
			for (k=0; k<MAX_MEMBERS && config.action_mods[i].i_whom[k] != -255; k++) {
if (config.flags.f_debug != 0) { printf("gA: 1 %d %d\n", config.action_mods[i].i_whom[k], k); }
			}
			for (k=0; k<MAX_MEMBERS && config.action_mods[i].i_whom[k] != -255; k++) {
				if ((plyr < MAX_PLAYERS && config.action_mods[i].i_whom[k] == -1) ||		// does it effect this player
					 (plyr >= MAX_PLAYERS && config.action_mods[i].i_whom[k] == -2) ||
					 (plyr == config.action_mods[i].i_whom[k])) {
// TODO - if it's an AC check, should it check the type and compare against the AC split
						  for (int j=0; j<5; j++) {
						  		if (adjustments[config.action_mods[i].i_data[j][1]].i_type == type) { 
									actype = 0;
									if (type == MOD_AC) {
										actype = -1;
										switch (config.action_mods[i].i_data[j][2]) {
											case MOD_TYPE_NATURAL: actype = AC_SECTION_NATURAL;
																	break;
											case MOD_TYPE_DODGE: actype = AC_SECTION_DODGE;
																	break;
											case MOD_TYPE_DEFLECTION: actype = AC_SECTION_DEFLECTION;
																	break;
											case MOD_TYPE_SHIELD: actype = AC_SECTION_SHIELD;
																	break;
											case MOD_TYPE_ARMOR: actype = AC_SECTION_ARMOR;
																	break;
										}
//printf("gM: AC: %d = %d/%d:%d\n", plyr, actype, players[plyr].i_armorClassSplit[actype], config.action_mods[i].i_data[j][0]);
										actype = config.action_mods[i].i_data[j][0] - players[plyr].i_armorClassSplit[actype];
										if (actype < 0) { actype = 0; }
										if (actype > adj[config.action_mods[i].i_data[j][2]]) {
											if (adj[config.action_mods[i].i_data[j][2]] < actype) {
												adj[config.action_mods[i].i_data[j][2]] = actype;
											}
										}
									} else if (type == MOD_HP && config.action_mods[i].i_data[j][2] == MOD_TYPE_ENHANCEMENT) {
										actype = config.action_mods[i].i_data[j][0] - players[plyr].i_hp[HP_ENH];
										if (actype < 0) { actype = 0; }
//printf("gM: HP: %d = %d/%d:%d\n", plyr, actype, players[plyr].i_hp[HP_ENH], config.action_mods[i].i_data[j][0]);
										if (actype > adj[config.action_mods[i].i_data[j][2]]) {
											if (adj[config.action_mods[i].i_data[j][2]] < actype) {
												adj[config.action_mods[i].i_data[j][2]] = actype;
											}
										}
									} else {
										if (config.action_mods[i].i_data[j][0] > adj[config.action_mods[i].i_data[j][2]]) {
											if (adj[config.action_mods[i].i_data[j][2]] < config.action_mods[i].i_data[j][0]) {
												adj[config.action_mods[i].i_data[j][2]] = config.action_mods[i].i_data[j][0];
if (config.flags.f_debug != 0) { printf("gA: 2 %s %d %d:%d:%d\n", config.action_mods[i].c_message, type, config.action_mods[i].i_data[j][0], config.action_mods[i].i_data[0][1], config.action_mods[i].i_data[j][2]); }
											}
										}
									}
								}
						  }
				}
			}
		}
	}
	j = 0;
	for (i=0; i<MAX_ADJEFFECTTYPES+1; i++) { 
		if (adj[i] != -255) {
			j += adj[i]; 
		}
	}

	j += doQuickMods(3, plyr, type);

	if (type == MOD_HP) { players[plyr].i_hp[HP_ADJ] = j; }

if (config.flags.f_debug != 0) { printf("gA: %d:%d:%d\n", plyr, type, j); }
	return(j);
}

/********************************************************************************/
int doEndOfRoundMessages(int action) {
int AYSreturn=0;

	if (a_EORWindow == NULL) {
//  		{ Fl_Double_Window* o = a_EORWindow = new Fl_Double_Window(380, 395, "ADMP - End Of Round Messages");
  		{ a_EORWindow = new Fl_Double_Window(380, 395, "ADMP - End Of Round Messages");
		    { Fl_Browser* o = a_EORMessageList = new Fl_Browser(15, 10, 350, 335);
		      o->labelsize(ADMP_LABEL_SIZE);
		      o->textsize(ADMP_TEXT_SIZE);
		    }
		    { Fl_Button* o = a_EORMessageYes = new Fl_Button(60, 355, 105, 25, "Yes - Continue");
		      o->labelsize(ADMP_LABEL_SIZE);
		    }
		    { Fl_Button* o = a_EORMessageNo = new Fl_Button(190, 355, 105, 25, "No - Do Actions");
		      o->labelsize(ADMP_LABEL_SIZE);
		    }
		    a_EORWindow->set_modal();
		    a_EORWindow->end();
		    a_EORWindow->resizable(a_EORWindow);
 		 }
		 if (action == 0) { a_EORWindow->hide(); return 0; }
	}
	a_EORWindow->show();
	for (;;) {
		Fl_Widget *o = Fl::readqueue();
		if (!o) {
			Fl::wait();
		} else if ( o == a_EORMessageYes) {
			AYSreturn = 1;
			break;
		} else if ( o == a_EORMessageNo) {
			AYSreturn = -1;
			break;
		}
	}
	a_EORWindow->hide();
	return AYSreturn;
}

/********************************************************************************/
void doCalcXP() {
	int i, j, xp=0, np=0;

	a_OXPCalcList->clear();
	i = atoi(a_OXPPartyLevel->value());
	for (j=0; j<MAX_PLAYERS; j++) {
		if (players[j].c_name[0] != '\0' && players[j].i_hp[HP_MAX] > 0 && players[j].flags.f_disabled == 0) {
			np++;
		}
	}
	if (np == 0) { np = 1; }
	for (j=MAX_PLAYERS; j<MAX_MEMBERS; j++) {
		if (players[j].c_name[0] != '\0' && players[j].i_hp[HP_MAX] > 0 && players[j].flags.f_npc == 0) {
			if (a_OXPCalcIncAll->value() == 1 || players[j].flags.f_disabled == 0) {
				sprintf(mybuf2, "%s (CR: %.1f) = %d", players[j].c_name, players[j].f_challengeRating, xp_cr[i][(int )players[j].f_challengeRating]);
				a_OXPCalcList->add(mybuf2);
				xp += xp_cr[i][(int )players[j].f_challengeRating];
			}
		}
	}
	a_OXPCalcList->add("");
	sprintf(mybuf2, "   XP Total: %d (Per Player: %d)", xp, (xp / np)); a_OXPCalcList->add(mybuf2);

	sprintf(mybuf2, "%d", (xp / np)); a_OXPValue->value(mybuf2);
}

/********************************************************************************/
void doAddPlayerXP() {

	sprintf(mybuf2, "XP: adding %d to all players", atoi(a_OXPValue->value()));
	writeLog(mybuf2);
	for (int i=0; i<MAX_PLAYERS; i++) {
		if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
			players[i].i_xp[MAX] += atoi(a_OXPValue->value());
		}
	}
	a_OXPValue->value("0");
}

/********************************************************************************/
void writeLog(char *text) {
	char fn[512];
	
	if (config.flags.f_logfile == 0) { return; }

	if (logfile == NULL) {
		sprintf(fn, "%slogfile.txt", systemDir);
		if ((logfile = fopen(fn, "a")) == NULL) {
			doSystemAlert("Unable to open the logfile.txt .... !!!");
			return;
		}
	}
	if (fprintf(logfile, "%s\n", text) < 0) {
		doSystemAlert("Unable to log the logfile.txt .... !!!");
	}
	fflush(logfile);
}

/********************************************************************************/
void mytolower(char *string) {
	int i=0;

	while (string[i] != '\0') {
		string[i] = tolower(string[i]);
		i++;
	}
}

/********************************************************************************/
void doWeaponSearchAction(int action) {
	int i = a_WSearchList->value() - 1;

	i = config.i_idList[ID_WSCH][i];

if (config.flags.f_debug != 0) { printf("dWSA: %d:%d:%d\n", action, i, i_WeaponUsed); }
	switch (action) {
		case 0:
				  a_WSearchDetails->clear();
				  a_WSearchDetails->add(stdweapons[i].c_description);
				  break;
		case 1: 
				  if (config.i_editID != MAX_MEMBERS+3) {
				  	if (i_prevWeaponEditted > -1) {
					  aEdit_WeaponAvailable->value(1);
					  aEdit_WeaponName->value(stdweapons[i].c_description);
					  aEdit_WeaponAttkBonus1->value("0");
					  aEdit_WeaponAttkBonus2->value("0");
					  aEdit_WeaponAttkBonus3->value("0");
					  aEdit_WeaponAttkBonus4->value("0");
					  aEdit_WeaponDamage->value(stdweapons[i].c_damage);
					  aEdit_WeaponCritical->value(stdweapons[i].c_critical);
					  aEdit_WeaponMagicBonus->value("0");
					  sprintf(mybuf2, "%d", stdweapons[i].i_range); aEdit_WeaponRange->value(mybuf2);
					  sprintf(mybuf2, "%d", stdweapons[i].i_reach); aEdit_WeaponReach->value(mybuf2);
					  aEdit_WeaponNoAttacks->value("1");
					  aEdit_WeaponSpecialMessage->value("");
					  aEdit_WeaponType->value(stdweapons[i].c_attackType);
					  sprintf(mybuf2, "%d", stdweapons[i].i_fumble); aEdit_WeaponFumble->value(mybuf2);
					  aEdit_WeaponCritAdjustment->value(stdweapons[i].i_critAdjust);
					  aEdit_WeaponSize->value(stdweapons[i].i_size);
					  aEdit_WeaponAttackTable->value(stdweapons[i].c_table);
					}
				  } else {
					  aQkAdd_WeaponName->value(stdweapons[i].c_description);
					  aQkAdd_WeaponAttkBonus1->value("0");
					  aQkAdd_WeaponAttkBonus2->value("0");
					  aQkAdd_WeaponAttkBonus3->value("0");
					  aQkAdd_WeaponAttkBonus4->value("0");
					  aQkAdd_WeaponDamage->value(stdweapons[i].c_damage);
					  aQkAdd_WeaponCritical->value(stdweapons[i].c_critical);
					  aQkAdd_WeaponMagicBonus->value("0");
					  sprintf(mybuf2, "%d", stdweapons[i].i_range); aQkAdd_WeaponRange->value(mybuf2);
					  sprintf(mybuf2, "%d", stdweapons[i].i_reach); aQkAdd_WeaponReach->value(mybuf2);
					  aQkAdd_WeaponNoAttacks->value("1");
					  aQkAdd_WeaponSpecialMessage->value("");
					  sprintf(mybuf2, "%d", stdweapons[i].i_fumble); aQkAdd_WeaponFumble->value(mybuf2);
					  aQkAdd_WeaponCritAdjustment->value(stdweapons[i].i_critAdjust);
					  aQkAdd_WeaponSize->value(stdweapons[i].i_size);
					  aQkAdd_WeaponAttackTable->value(stdweapons[i].c_table);
				  }
				  a_WeaponWindow->hide();
				  break;
		case 2:
				  a_WeaponWindow->hide();
				  break;
	}
}

/********************************************************************************/
int whichChecked(Fl_Check_Browser *b) {
	for (int i=b->nitems(); i>0; i--) {
		if (b->checked(i) == 1) {
if (config.flags.f_debug != 0) { printf("wC: %d\n", i); }
			return i;
		}
	}
	return 0;
}

/********************************************************************************/
void doAutoDamageAction(int act) {
	int i,j,k,l;

if (config.flags.f_debug != 0) { printf("dADA: %d\n", act); }
	switch (act) {
		case 0:
				  a_OTADList->clear();
				  for (i=0; i<MAX_AUTODAMAGE; i++) {
				  		a_OTADList->add(config.auto_damage[i].c_description);
				  }
					a_OTADList->activate();
					a_OTADAccept->deactivate();
					a_OTADCancel->deactivate();
					a_OTADInitiateList->deactivate();
					a_OTADReceiveList->deactivate();
					a_OTADDescription->deactivate();
					a_OTADDamage->deactivate();
					a_OTADRounds->deactivate();
					a_OTADRoundsDone->deactivate();
					a_OTADType->deactivate();
					a_OTADFlags->deactivate();
				  break;
		case 1:
				  i = a_OTADList->value() - 1;
				  if (i < 0)  {
						return;
				  }
if (config.flags.f_debug != 0) { printf("dADA: 1 %d:%d\n", i, config.auto_damage[i].i_initiatorID); }
				  k=0;
				  a_OTADInitiateList->clear();
					a_OTADReceiveList->clear();
				  for (j=0; j<MAX_MEMBERS; j++) {
						if (players[j].c_name[0] != '\0' && players[j].i_hp[HP_MAX] > 0 && players[j].flags.f_disabled == 0) {
							l = 0;
							if (i < MAX_PLAYERS) { l = 1; } else
							if ((getHPs(i) < 0 && config.flags.f_showDeadMonsters != 0) || getHPs(i) > -1) { l = 1; }
							if (l == 1) {
					  			config.i_idList[ID_ADAM][k++] = j;
								if (config.auto_damage[i].i_initiatorID == j) {
									a_OTADInitiateList->add(players[j].c_name, 1);
								} else {
									a_OTADInitiateList->add(players[j].c_name);
								}
								a_OTADReceiveList->add(players[j].c_name);
							}
						}
				  }
				  	config.i_idList[ID_ADAM][k] = -1;
					for (k=0; config.auto_damage[i].i_whom[k] != -1 && k < MAX_MEMBERS; k++) {
						for (j=0; j < MAX_MEMBERS && config.i_idList[ID_ADAM][j] != -1; j++) {
							if (config.auto_damage[i].i_whom[k] == config.i_idList[ID_ADAM][j]) {
								a_OTADReceiveList->checked(j+1, 1);
							}
						}
					}
					a_OTADList->deactivate();
					a_OTADAccept->activate();
					a_OTADCancel->activate();
					a_OTADInitiateList->activate();
					a_OTADReceiveList->activate();
					a_OTADDescription->activate();
					a_OTADDamage->activate();
					a_OTADRounds->activate();
					a_OTADRoundsDone->activate();
					a_OTADType->deactivate();
					a_OTADFlags->activate();
					a_OTADFlags->check_none();

				  a_OTADDescription->value(config.auto_damage[i].c_description);
				  a_OTADDamage->value(config.auto_damage[i].c_damage);
				  sprintf(mybuf2, "%d", config.auto_damage[i].i_noRounds); a_OTADRounds->value(mybuf2);
				  sprintf(mybuf2, "%d", config.auto_damage[i].i_doneRounds); a_OTADRoundsDone->value(mybuf2);
				  a_OTADType->value(config.auto_damage[i].i_type);
				  a_OTADFlags->checked(1, config.auto_damage[i].flags.f_flag1);
				  a_OTADFlags->checked(2, config.auto_damage[i].flags.f_flag2);
				  a_OTADFlags->checked(3, config.auto_damage[i].flags.f_flag3);
				  		// adding a new one, so mark it as being done else it'll double add
				  if (config.auto_damage[i].i_noRounds == 0 && strncasecmp(config.auto_damage[i].c_description, "-- empty", 8) == 0) {
				  		a_OTADFlags->checked(2, 1);
				  }
				  break;

		case 2:	// accept
				  i = a_OTADList->value() - 1;
				  strncpy(config.auto_damage[i].c_description, a_OTADDescription->value(), 32); config.auto_damage[i].c_description[31] = '\0';
				  strncpy(config.auto_damage[i].c_damage, a_OTADDamage->value(), 32); config.auto_damage[i].c_damage[31] = '\0';
				  for (j=a_OTADInitiateList->nitems(); j>0; j--) {
						if (a_OTADInitiateList->checked(j) == 1) {
				  			config.auto_damage[i].i_initiatorID = config.i_idList[ID_ADAM][j-1];
						}
				  }
				  config.auto_damage[i].i_noRounds = atoi(a_OTADRounds->value());
				  config.auto_damage[i].i_doneRounds = atoi(a_OTADRoundsDone->value());
				  config.auto_damage[i].i_type = a_OTADType->value();
				  config.auto_damage[i].flags.f_flag1 = a_OTADFlags->checked(1);
				  config.auto_damage[i].flags.f_flag2 = a_OTADFlags->checked(2);
				  config.auto_damage[i].flags.f_flag3 = a_OTADFlags->checked(3);
				  k=0;
				  for (j=a_OTADReceiveList->nitems(); j>0; j--) {
						if (a_OTADReceiveList->checked(j) == 1) {
				  			config.auto_damage[i].i_whom[k++] = config.i_idList[ID_ADAM][j-1];
						}
				  }
				  config.auto_damage[i].i_whom[k] = -1;
//printf("aADA: 3: %d:%d\n", config.auto_damage[i].i_initiatorID, a_OTADInitiateList->value());
				  doAutoDamageAction(0);
				  break;

		case 3:	// cancel
				  doAutoDamageAction(0);
				  break;

		case 4:	// flags/options selected
				  mybuf2[0] = '\0';
				  if (a_OTADFlags->checked(1) == 1) { strcat(mybuf2, "Dont forget to add ONE to the number of Rounds"); }
				  if (mybuf2[0] != '\0') {
						doSystemAlert(mybuf2);
				  }
				  break;

		case 9:	// refresh the list
				  a_OTADList->clear();
				  for (i=0; i<MAX_AUTODAMAGE; i++) {
				  		a_OTADList->add(config.auto_damage[i].c_description);
				  }
				  break;
	}
}

/********************************************************************************/
int calcAutoDamage(int adID, int recvID) {
int i=0, j=0, k=0, l=0;
char *dam=NULL;

		// find all the Auto-damages not done & do all the damage
//	for (i=0; i<MAX_AUTODAMAGE; i++) {
		i = adID;	// only this autoDamage config
if (config.flags.f_debug != 0) { printf("cAD: 0 %d:%d:%d:%d\n", i, recvID, config.auto_damage[i].i_noRounds, config.auto_damage[i].flags.f_flag2); }
		if (config.auto_damage[i].i_noRounds > 0 && config.auto_damage[i].flags.f_flag2 == 0) {
//			config.auto_damage[i].flags.f_flag2 = 1;		// mark as being done
			strcpy(mybuf2, config.auto_damage[i].c_damage);
			dam = strtok(mybuf2, " ");
			if (dam == NULL) {	// only ONE damage 'value' specified
				dam = &mybuf2[0];
			} else {
				k = 1;
				while (k < config.auto_damage[i].i_doneRounds && dam != NULL) {
					dam = strtok(NULL, " ");
					k++;
				}
			}
			if (dam == NULL) {	// only ONE damage 'value' specified
				dam = &mybuf2[0];
			}
if (config.flags.f_debug != 0) { printf("cAD: 0 %s\n", dam); }
			k = parseDice(dam);
			for (j=0; j<MAX_MEMBERS && config.auto_damage[i].i_whom[j] != -1; j++) {
				if (config.auto_damage[i].i_whom[j] == recvID || recvID == -1) {
					if (config.auto_damage[i].flags.f_flag3 != 0) {		// reroll flag set ?
						k = parseDice(dam);
					}
					l = config.auto_damage[i].i_whom[j];
					players[l].i_hp[HP_CUR] -= k;
					if (players[l].i_hp[HP_CUR] > players[l].i_hp[HP_MAX]) {
						players[l].i_hp[HP_CUR] = players[l].i_hp[HP_MAX];
					}
					sprintf(mybuf2, "AutoDamage: %s -> %s (HP:%d) Cur:%d", players[config.auto_damage[i].i_initiatorID].c_name, players[l].c_name, k, players[l].i_hp[HP_CUR]);
					writeLog(mybuf2);
if (config.flags.f_debug != 0) { printf("cAD: 1 %d:%d:%d\n", i, j, config.auto_damage[i].i_whom[j]); }
				}
			}
		}
//	}
	return 0;
}

/********************************************************************************/
void selectEditWeapon(int w) {
	int i = config.i_editID;
	char buf[10];

	if (i_prevWeaponEditted != -1) {		// save the previous weapon details
		aEdit_WeaponAvailable->value(players[i].w_weapons[i_prevWeaponEditted].c_available);
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_description, aEdit_WeaponName->value(), 29);
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[0] = atoi(aEdit_WeaponAttkBonus1->value());
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[1] = atoi(aEdit_WeaponAttkBonus2->value());
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[2] = atoi(aEdit_WeaponAttkBonus3->value());
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[3] = atoi(aEdit_WeaponAttkBonus4->value());
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_damage, aEdit_WeaponDamage->value(), 19);
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_critical, aEdit_WeaponCritical->value(), 19);
		players[i].w_weapons[i_prevWeaponEditted].i_magicalBonus = atoi(aEdit_WeaponMagicBonus->value());
		players[i].w_weapons[i_prevWeaponEditted].i_range = atoi(aEdit_WeaponRange->value());
		players[i].w_weapons[i_prevWeaponEditted].i_reach = atoi(aEdit_WeaponReach->value());
		players[i].w_weapons[i_prevWeaponEditted].i_noAttacks = atoi(aEdit_WeaponNoAttacks->value());
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_message, aEdit_WeaponSpecialMessage->value(), 39);
		players[i].w_weapons[i_prevWeaponEditted].c_message[39] = '\0';
		players[i].w_weapons[i_prevWeaponEditted].c_description[29] = '\0';
		players[i].w_weapons[i_prevWeaponEditted].c_damage[19] = '\0';
		players[i].w_weapons[i_prevWeaponEditted].c_critical[19] = '\0';
		if (players[i].w_weapons[i_prevWeaponEditted].c_description[0] != '\0') {
			aEdit_WeaponSelector->text(i_prevWeaponEditted+1, players[i].w_weapons[i_prevWeaponEditted].c_description);
		}
		players[i].w_weapons[i_prevWeaponEditted].c_attackType = aEdit_WeaponType->value();
		players[i].w_weapons[i_prevWeaponEditted].i_fumble = atoi(aEdit_WeaponFumble->value());
		players[i].w_weapons[i_prevWeaponEditted].i_critAdjust = aEdit_WeaponCritAdjustment->value();
		players[i].w_weapons[i_prevWeaponEditted].i_size = aEdit_WeaponSize->value();
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_table, aEdit_WeaponAttackTable->value(), 3);
		players[i].w_weapons[i_prevWeaponEditted].c_table[3] = '\0';
	}
	aEdit_WeaponAvailable->activate(); aEdit_WeaponAvailable->value(players[i].w_weapons[w].c_available);
	aEdit_WeaponName->activate(); aEdit_WeaponName->value(players[i].w_weapons[w].c_description);
	aEdit_WeaponSearch->activate();
	aEdit_WeaponAttkBonus1->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[0]); aEdit_WeaponAttkBonus1->value(buf);
	if (config.i_diceSystem == DICE_D20) {
		aEdit_WeaponAttkBonus2->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[1]); aEdit_WeaponAttkBonus2->value(buf);
		aEdit_WeaponAttkBonus3->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[2]); aEdit_WeaponAttkBonus3->value(buf);
		aEdit_WeaponAttkBonus4->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[3]); aEdit_WeaponAttkBonus4->value(buf);
		aEdit_WeaponFumble->deactivate();
		aEdit_WeaponCritAdjustment->deactivate();
		aEdit_WeaponSize->deactivate();
		aEdit_WeaponAttackTable->deactivate();
	} else {
		aEdit_WeaponFumble->activate();
		aEdit_WeaponCritAdjustment->activate();
		aEdit_WeaponSize->activate();
		aEdit_WeaponAttackTable->activate();
	}
	aEdit_WeaponDamage->activate(); aEdit_WeaponDamage->value(players[i].w_weapons[w].c_damage);
	aEdit_WeaponCritical->activate(); aEdit_WeaponCritical->value(players[i].w_weapons[w].c_critical);
	aEdit_WeaponMagicBonus->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_magicalBonus); aEdit_WeaponMagicBonus->value(buf);
	aEdit_WeaponRange->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_range); aEdit_WeaponRange->value(buf);
	aEdit_WeaponReach->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_reach); aEdit_WeaponReach->value(buf);
	aEdit_WeaponNoAttacks->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_noAttacks); aEdit_WeaponNoAttacks->value(buf);
	aEdit_WeaponSpecialMessage->activate(); aEdit_WeaponSpecialMessage->value(players[i].w_weapons[w].c_message);
	aEdit_WeaponType->activate(); aEdit_WeaponType->value(players[i].w_weapons[w].c_attackType);
	sprintf(buf, "%d", players[i].w_weapons[w].i_fumble); aEdit_WeaponFumble->value(buf);
	aEdit_WeaponCritAdjustment->value(players[i].w_weapons[w].i_critAdjust);
	aEdit_WeaponSize->value(players[i].w_weapons[w].i_size);
	aEdit_WeaponAttackTable->value(players[i].w_weapons[w].c_table);
	i_prevWeaponEditted = w;
}
	
/********************************************************************************/
int getWeaponAttackBonus(int p, int w) {
int i=0, j=0;

	i = players[p].w_weapons[w].i_doneAttacks; if (i > MAX_WEAPONATTACKS) { i = 0; } // MAX_WEAPONATTACKS-1; }
	j = players[p].w_weapons[w].i_attackBonus[i];
if (config.flags.f_debug != 0) { printf("gWAB: 0: %d %d %d %d\n", p, w, i, j); }
	if (j > 0 || i == 0) { return(j); }
//	for (i=(MAX_WEAPONATTACKS-1); i >= 0; i--) {
//		j = players[p].w_weapons[w].i_attackBonus[i];
//		if (j > 0) { return(j); }
//	}
//		we assume that since there's not a AB for that attack that it's the first bonus
	return (players[p].w_weapons[w].i_attackBonus[0]);
}

/********************************************************************************/
void setOtherActionDescription(int d) {
	switch (d) {
		case -1:
				  a_OOActionList->add("Reset Players"); a_OOActionList->add("Clean Players"); a_OOActionList->add("Remove ALL Players");
				  a_OOActionList->add("Reset Monsters"); a_OOActionList->add("Clean Monsters"); a_OOActionList->add("Remove ALL Monsters");
				  a_OOActionList->add("Clear Triggers"); a_OOActionList->add("Clear Adjustments"); a_OOActionList->add("Reset ALL for new combat");
				  a_OOActionList->add("Set Monster HP based on HD"); a_OOActionList->add("Clear Auto-Damage"); 
				  a_OOActionList->add("New day healing & spell slots"); a_OOActionList->add("Clear All Group Details");
				  break;

		case 0: a_OOtherActionDescription->value("This will reset them back to full health");
				  break;
		case 1: a_OOtherActionDescription->value("This currently does nothing");
				  break;
		case 2: a_OOtherActionDescription->value("This will remove all the players currently defined");
				  break;
		case 3: a_OOtherActionDescription->value("This will reset them back to full health");
				  break;
		case 4: a_OOtherActionDescription->value("This currently does nothing");
				  break;
		case 5: a_OOtherActionDescription->value("This will remove all the monsters currently defined");
				  break;
		case 6: a_OOtherActionDescription->value("This will remove all the Triggers currently defined");
				  break;
		case 7: a_OOtherActionDescription->value("This will remove all the Adjustments currently defined");
				  break;
		case 8: a_OOtherActionDescription->value("This will reset the players/monsters to full health and\nclear any triggers/adjustments/auto-damages\ncurrently defined");
				  break;
		case 9: a_OOtherActionDescription->value("This will calculate the monster's Hit Points based\non their Hit Dice");
				  break;
		case 10: a_OOtherActionDescription->value("This will remove all the Auto-Damages currently defined");
				  break;
		case 11: a_OOtherActionDescription->value("This will heal all enabled players by LEVEL HPs and reset their\nspell slot counts");
				  break;
		case 12: a_OOtherActionDescription->value("This will reset the Group Descriptions and remove all from the groups");
				  break;
		case 13: a_OOtherActionDescription->value("");
				  break;
	}
	//a_OOtherActionDescription->value(a_OOActionList->text(d+1));
}

/********************************************************************************/
void setSystemFlag(int type) {

	switch (type) {
		case 0: aSys_flags->clear();
				  aSys_flags->add("Debug", config.flags.f_debug);
				  aSys_flags->add("Roll All Rolls", config.flags.f_rollAllRolls);
				  aSys_flags->add("Roll All INIT Rolls", config.flags.f_rollInitRolls);
				  aSys_flags->add("Write Log File", config.flags.f_logfile);
				  aSys_flags->add("Roll INIT's Every Round", config.flags.f_rollInitEveryRnd);
				  aSys_flags->add("Remove Uncon Monsters from Init Seq", config.flags.f_removeMonstersInit);
				  aSys_flags->add("One always Misses, 20 Always Hits", config.flags.f_oneMissTwentyHits);
				  aSys_flags->add("Fog of War", config.flags.f_fogOfWar);
				  aSys_flags->add("Default to previous defender for attacks", config.flags.f_defaultDefender);
				  aSys_flags->add("Ask before moving players", config.flags.f_askBeforeMoving);
				  aSys_flags->add("Show Dead Monsters in Display Lists", config.flags.f_showDeadMonsters);
				  aSys_flags->add("Death occurs at negative CON", config.flags.f_deathAtCON);
				  break;

		case 1:
				  config.flags.f_debug = aSys_flags->checked(1);
				  config.flags.f_rollAllRolls = aSys_flags->checked(2);
				  config.flags.f_rollInitRolls = aSys_flags->checked(3);
				  config.flags.f_logfile = aSys_flags->checked(4);
				  config.flags.f_rollInitEveryRnd = aSys_flags->checked(5);
				  config.flags.f_removeMonstersInit = aSys_flags->checked(6);
				  config.flags.f_oneMissTwentyHits = aSys_flags->checked(7);
				  config.flags.f_fogOfWar = aSys_flags->checked(8);
				  config.flags.f_defaultDefender = aSys_flags->checked(9);
				  config.flags.f_askBeforeMoving = aSys_flags->checked(10);
				  config.flags.f_showDeadMonsters = aSys_flags->checked(11);
				  config.flags.f_deathAtCON = aSys_flags->checked(12);
				  combatGridMap->getGridTile()->setFogOfWar(config.flags.f_fogOfWar);
				  if (config.flags.f_rollInitEveryRnd != 0) {
						config.flags.f_rollInitRolls = 1;
						aSys_flags->checked(3, 1);
				  }
				  break;
	}
// printf("sSF: %d\n", config.flags.f_debug);
}

// List of possible vowels; duplicates increase the likelihood of selection:
char *vowels[] = {
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"a", "e", "i", "o", "u",
"ae", "ai", "ao", "au", "aa",
"ea", "eo", "eu", "ee",
"ia", "io", "iu", "ii",
"oa", "oe", "oi", "ou", "oo",
"eau", "'", "y"};

typedef struct consons {
	char *conson;
	int flag;
} consons;

consons consonants[] = {
{"b", 3},  {"c", 3},  {"d", 3},  {"f", 3},  {"g", 3},  {"h", 3}, 
{"j", 3},  {"k", 3},  {"l", 3},  {"m", 3},  {"n", 3},  {"p", 3}, 
{"qu", 2},  {"r", 3}, {"s", 3},  {"t", 3},  {"v", 3},  {"w", 3},
{"x", 3},  {"y", 3},  {"z", 3}, 
// Blends, sorted by second character:
{"sc", 3},		// 22
{"ch", 3},  {"gh", 3},  {"ph", 3}, {"sh", 3},  {"th", 3}, {"wh", 2},
{"ck", 1},  {"nk", 1},  {"rk", 1}, {"sk", 3},  {"wk", 0},
{"cl", 2},  {"fl", 2},  {"gl", 2}, {"kl", 2},  {"ll", 2}, {"pl", 2}, {"sl", 2},
{"br", 2},  {"cr", 2},  {"dr", 2},  {"fr", 2},  {"gr", 2},  {"kr", 2}, 
{"pr", 2},  {"sr", 2},  {"tr", 2}, {"ss", 1}, {"st", 3},  {"str", 2},	// 53
// Repeat some entries to make them more common.
{"b", 3},  {"c", 3},  {"d", 3},  {"f", 3},  {"g", 3},  {"h", 3}, 
{"j", 3},  {"k", 3},  {"l", 3},  {"m", 3},  {"n", 3},  {"p", 3}, 
{"r", 3}, {"s", 3},  {"t", 3},  {"v", 3},  {"w", 3}, 
{"b", 3},  {"c", 3},  {"d", 3},  {"f", 3},  {"g", 3},  {"h", 3}, 
{"j", 3},  {"k", 3},  {"l", 3},  {"m", 3},  {"n", 3},  {"p", 3}, 
{"r", 3}, {"s", 3},  {"t", 3},  {"v", 3},  {"w", 3},
{"br", 2},  {"dr", 2},  {"fr", 2},  {"gr", 2},  {"kr", 2}
};

// Return a random value between minvalue and maxvalue, inclusive, with equal probability.
//************************************************************************************
int rolldie(int minvalue, int maxvalue) {
int result=0;

	while (1) {
//		 result = random() % maxvalue;
		 result = getRND(maxvalue-minvalue) + minvalue - 1;
		 if ((result >= minvalue) && (result <= maxvalue)) { 
			return result;
		 }
	}
}

char genname[90];         // this accumulates the generated name.

// Create a random name.  It must have at least between minsyl and maxsyl number of syllables (inclusive).
//************************************************************************************
char * RandomName(int minsyl, int maxsyl) {
char data[90];
int leng = rolldie(minsyl, maxsyl); // Compute number of syllables in the name
int isvowel = rolldie(0, 2); // randomly start with vowel or consonant
int i=0, j=0;

genname[0] = '\0';
for (i = 1; i <= leng; i++) { // syllable #. Start is 1 (not 0)
	if (isvowel) {
		strcpy(data, vowels[rolldie(0, 80)]);
			// Don't allow ' at beginning or end of name; change it to "e".
		if ( (data[0] == '\'') && ((i == 1) || (i == leng))) { data[0] = 'e';};
			strcat(genname, data);
		} else {
			do {
				j = rolldie(0, 91);
				strcpy(data, consonants[j].conson);
				j = consonants[j].flag;
					// Check if this consonant can occur in this syllable.
				if ( i == 1) { // first syllable.
					if (data[0] != '\0' && j == 2) { break;}
				} else if (i == leng) { // last syllable.
					if (data[0] != '\0' && j == 1) { break;}
				} else { break;}; // Middle syllable, any consonant allowed.
			} while (1);
			strncat(genname, &data[0], 1);
		}
		isvowel = 1 - isvowel; // Alternate between vowels and consonants.
	}
// Initial caps:
	genname[0] = toupper(genname[0]);
	return genname;
}

/********************************************************************************/
void generateRndNames() {
//	time_t ltime;
//	struct tm *ntime;
//	int seed1;
	char n1[50], n2[50], n3[50];

//	time(&ltime);
//	ntime = gmtime(&ltime);
//	seed1 = (ntime->tm_sec*400)+(ntime->tm_min*70)+ntime->tm_hour;
//	srandom(seed1);

	aGN_NameList1->clear(); aGN_NameList2->clear(); aGN_NameList3->clear();
	aGN_NameList1->add(""); aGN_NameList2->add(""); aGN_NameList3->add("");

	for (int i=0; i<6; i++) {
		strcpy(n1, RandomName(3,4));
		strcpy(n2, RandomName(3,5));
		strcpy(n3, RandomName(3,7));
		aGN_NameList1->add(n1);
		aGN_NameList2->add(n2);
		aGN_NameList3->add(n3);
		if ((i%5) == 0 && i != 0) { aGN_NameList1->add(""); aGN_NameList2->add(""); aGN_NameList3->add(""); }
	}
}

/********************************************************************************/
void npc_action(int action) {
FILE *ifile;
char buf[2048], *cp, *cp1;
int sz=0, i=0, j=0, ns=-1;
ADMPplayer p;

	switch (action) {
		case 0:		// generate NPC
				  a_NPCSave->activate();
				  a_NPCText->clear();
				  if (a_NPCRace->value() == 0) {
						a_NPCRace->value(getRND(6) + 1);
				  }
				  if (a_NPCClass->value() == 0) {
						a_NPCClass->value(getRND(11) + 1);
				  }
#ifndef VISUALC
				  sprintf(mybuf1, "./npc -o acibklfpS -l %d -r %s -c %s > npc.txt 2>&1", (int )a_NPCLevel->value(), races[a_NPCRace->value()].text, classes[a_NPCClass->value()].text);
#else
				  sprintf(mybuf1, "npc -o acibklfpS -l %d -r %s -c %s > npc.txt 2>&1", (int )a_NPCLevel->value(), races[a_NPCRace->value()].text, classes[a_NPCClass->value()].text);
#endif
				  system(mybuf1);
				  a_NPCText->clear();
				  if ((ifile = fopen("npc.txt", "r")) != NULL) {
						while (fgets(buf, 2047, ifile) != NULL) {
							if (strlen(buf) > 10) {
								if (strncmp(buf, ", ", 2) == 0 || strncmp(buf, "Skills", 6) == 0 || strncmp(buf, "Wizard", 6) == 0 ||
									strncmp(buf, "Sorcerer", 8) == 0 || strncmp(buf, "Bard", 4) == 0) {
									cp = strtok(buf, ";");
				  					a_NPCText->add(cp);
									while ((cp = strtok(NULL, ";")) != NULL) {
										if ((cp1 = strstr(cp, "--")) != NULL) {
											cp1 -= 5;
											*cp1 = '\0'; cp1++;
				  							a_NPCText->add(cp);
				  							a_NPCText->add(cp1);
										} else {
				  							a_NPCText->add(cp);
										}
									}
								} else {
				  					a_NPCText->add(buf);
								}
							}
						}
				  }
				  a_NPCText->add("");
				  break;
//	copy the details into a new monster slot
		case 1:
				  memset(p.c_name, '\0', sizeof(ADMPplayer));
				  p.i_mapX = p.i_mapY = -1;
				  sz = a_NPCText->size();
				  strcpy(buf, a_NPCText->text(1));
				  p.f_challengeRating = 1.0;
				  if ((cp = strstr(buf, " CR ")) != NULL) { *cp = '\0'; cp+=4; p.f_challengeRating = atof(cp); }
				  sprintf(p.c_name, "Z - %s", &buf[2]);
				  for (i=2; i<=sz; i++) {
				  		strcpy(buf, a_NPCText->text(i));
						if (strstr(buf, "HD") != NULL) { strcpy(p.c_hitDice, &buf[4]); }
						else if (strstr(buf, "hp") != NULL) { p.i_hp[HP_MAX] = p.i_hp[HP_CUR] = atoi(&buf[4]); }
						else if (strstr(buf, "Init") != NULL) { p.i_initiative[0] = atoi(&buf[7]); }
						else if (strstr(buf, "AC") != NULL) { p.i_armorClass[AC_NORMAL] = atoi(&buf[4]); }
						else if (strstr(buf, "Spd") != NULL) { p.i_speed = atoi(&buf[5]); }
						else if (strstr(buf, "Languages") != NULL) { ns = i; }
						else if (strstr(buf, "SV") != NULL) { 
							cp = strtok(&buf[6], " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_savingThrows[SAVE_FORTITUDE] = atoi(cp); }
							cp = strtok(NULL, " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_savingThrows[SAVE_REFLEX] = atoi(cp); }
							cp = strtok(NULL, " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_savingThrows[SAVE_WISDOM] = atoi(cp); }
						} else if (strstr(buf, "Skills") != NULL) {
							do {
								j = 0;
								if ((cp = strstr(buf, "+")) != NULL) { if ((cp1 = strstr(cp, " ")) != NULL) { *cp1 = '\0'; j = atoi(cp); }}
								else if ((cp = strstr(buf, "-")) != NULL) { if ((cp1 = strstr(cp, " ")) != NULL) { *cp1 = '\0'; j = atoi(cp); }}
								if (strstr(buf, "Hide") != NULL) { p.i_skills[SKILL_HIDE] = j;
								} else if (strstr(buf, "Listen") != NULL) { p.i_skills[SKILL_LISTEN] = j;
								} else if (strstr(buf, "Spot") != NULL) { p.i_skills[SKILL_SPOT] = j;
								} else if (strstr(buf, "Move") != NULL) { p.i_skills[SKILL_MOVESILENTLY] = j;
								} else if (strstr(buf, "Search") != NULL) { p.i_skills[SKILL_SEARCH] = j;
								} else if (strstr(buf, "Open") != NULL) { p.i_skills[SKILL_OPENLOCKS] = j;
								} else if (strstr(buf, "Concent") != NULL) { p.i_skills[SKILL_CONCENTRATION] = j;
								} else if (strstr(buf, "Sleight") != NULL) { p.i_skills[SKILL_SOH] = j;
								}
								i++; strcpy(buf, a_NPCText->text(i));
							} while (buf[0] == ' ' && i<= sz);
						} else if (strstr(buf, "Str") != NULL) {
							cp = strtok(&buf[3], " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_abilityStats[0][ABILITY_STR] = p.i_abilityStats[1][ABILITY_STR] = atoi(cp); }
							cp = strtok(NULL, " "); cp = strtok(NULL, " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_abilityStats[0][ABILITY_DEX] = p.i_abilityStats[1][ABILITY_DEX] = atoi(cp); }
							cp = strtok(NULL, " "); cp = strtok(NULL, " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_abilityStats[0][ABILITY_CON] = p.i_abilityStats[1][ABILITY_CON] = atoi(cp); }
							cp = strtok(NULL, " "); cp = strtok(NULL, " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_abilityStats[0][ABILITY_INT] = p.i_abilityStats[1][ABILITY_INT] = atoi(cp); }
							cp = strtok(NULL, " "); cp = strtok(NULL, " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_abilityStats[0][ABILITY_WIS] = p.i_abilityStats[1][ABILITY_WIS] = atoi(cp); }
							cp = strtok(NULL, " "); cp = strtok(NULL, " ");
							cp = strtok(NULL, " ");
							if (cp != NULL) { p.i_abilityStats[0][ABILITY_CHA] = p.i_abilityStats[1][ABILITY_CHA] = atoi(cp); }
						} else if (strstr(buf, "Spells") != NULL) {
							do {
								i++; strcpy(buf, a_NPCText->text(i));
							} while (buf[0] == ' ' && i<= sz);
						} else if (strstr(buf, "Attack") != NULL) {
							p.i_noAttacks = 1;
							p.w_weapons[0].i_noAttacks = 1;
							p.w_weapons[6].i_noAttacks = 1;
							if ((cp = strstr(buf, "melee")) != NULL) {
								*cp = '\0'; cp++;
								if ((cp1 = strstr(cp, "(")) != NULL) { *cp1 = '\0'; }
								j = 0;
								strcpy(p.w_weapons[6].c_description, "Unknown Ranged");
								strcpy(p.w_weapons[6].c_damage, "1d6");
								strcpy(p.w_weapons[6].c_critical, "*3");
								p.w_weapons[6].i_range = 60;
								if ((cp = strstr(cp, "+")) != NULL) { if ((cp1 = strstr(cp, " ")) != NULL) { *cp1 = '\0'; } }
								else if ((cp = strstr(cp, "-")) != NULL) { if ((cp1 = strstr(cp, " ")) != NULL) { *cp1 = '\0'; } }

								if ((cp1 = strstr(cp, "/")) != NULL) {
									while ((cp1 = strstr(cp, "/")) != NULL && j < 4) {
										*cp1 = '\0';
										p.w_weapons[6].i_attackBonus[j++] = atoi(cp);
										cp = cp1; cp++;
									}
									p.w_weapons[6].i_attackBonus[j++] = atoi(cp);
									p.w_weapons[6].i_noAttacks = j;
									p.w_weapons[0].i_noAttacks = j;
									p.i_noAttacks = j;
								} else {
									p.w_weapons[6].i_attackBonus[0] = atoi(cp);
								}
							}

							if ((cp1 = strstr(buf, "(")) != NULL) { *cp1 = '\0'; }
							strcpy(p.w_weapons[0].c_description, "Unknown Melee");
							strcpy(p.w_weapons[0].c_damage, "1d8");
							strcpy(p.w_weapons[0].c_critical, "19-20/*2");
							j = 0;
							if ((cp = strstr(cp, "+")) != NULL) { if ((cp1 = strstr(cp, " ")) != NULL) { *cp1 = '\0'; } }
							else if ((cp = strstr(cp, "-")) != NULL) { if ((cp1 = strstr(cp, " ")) != NULL) { *cp1 = '\0'; } }

							if ((cp1 = strstr(cp, "/")) != NULL) {
								while ((cp1 = strstr(cp, "/")) != NULL && j < 4) {
									*cp1 = '\0';
									p.w_weapons[0].i_attackBonus[j++] = atoi(cp);
									cp = cp1; cp++;
								}
								p.w_weapons[0].i_attackBonus[j++] = atoi(cp);
							} else {
								p.w_weapons[0].i_attackBonus[0] = atoi(cp);
							}
						}
				  }
				  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] == '\0' && players[i].i_hp[HP_MAX] == 0) {
							memcpy(players[i].c_name, p.c_name, sizeof(ADMPplayer));
							players[i].c_name[0] = identifiers[i];
								// save the note into the file instead
							edit_notes_buffer->text("");
							if (ns != -1) {
								int ssz = 1;
								for (j=ns; j<=sz; j++) {
				  					sprintf(mybuf2, "%s\n", a_NPCText->text(j));
				  					edit_notes_buffer->insert(ssz, mybuf2);
									ssz += strlen(mybuf2);
								}
							}
							doNotesAction(0, i);
							break;
						}
				  }
				  reloadNames(0);
				  doSystemAlert("Dont forget to change the weapon details in the Edit tab !!!");
				  break;
	}
}

/********************************************************************************/
void dump_player_data(int pid) {
	printf("strcpy(p[i].c_name, \"%s\");\n", &players[pid].c_name[4]);
	printf("p[i].i_race = %d;\n", players[pid].i_race);
	printf("p[i].i_alignment = %d;\n", players[pid].i_alignment);
	printf("p[i].i_classes[0] = %d;\n", players[pid].i_classes[0]);
	printf("p[i].i_classes[1] = %d;\n", players[pid].i_classes[1]);
	printf("p[i].i_classes[2] = %d;\n", players[pid].i_classes[2]);
	printf("p[i].i_classes[3] = %d;\n", players[pid].i_classes[3]);
	printf("p[i].i_levels[0] = %d;\n", players[pid].i_levels[0]);
	printf("p[i].i_levels[1] = %d;\n", players[pid].i_levels[1]);
	printf("p[i].i_levels[2] = %d;\n", players[pid].i_levels[2]);
	printf("p[i].i_levels[3] = %d;\n", players[pid].i_levels[3]);
	printf("p[i].i_hp[HP_MAX] = %d;\n", players[pid].i_hp[HP_MAX]);
	printf("p[i].i_hp[HP_CUR] = %d;\n", players[pid].i_hp[HP_CUR]);
	printf("p[i].i_hp[HP_NL] = %d;\n", players[pid].i_hp[HP_NL]);
	printf("p[i].i_hp[HP_TMP] = %d;\n", players[pid].i_hp[HP_TMP]);
	printf("p[i].i_hp[HP_ENH] = %d;\n", players[pid].i_hp[HP_ENH]);
	printf("p[i].i_bleeding = %d;\n", players[pid].i_bleeding);
	printf("p[i].i_disabledAt = %d;\n", players[pid].i_disabledAt);
	printf("p[i].i_unconciousAt = %d;\n", players[pid].i_unconciousAt);
	printf("p[i].i_savingThrows[SAVE_FORTITUDE] = %d;\n", players[pid].i_savingThrows[SAVE_FORTITUDE]);
	printf("p[i].i_savingThrows[SAVE_REFLEX] = %d;\n", players[pid].i_savingThrows[SAVE_REFLEX]);
	printf("p[i].i_savingThrows[SAVE_WISDOM] = %d;\n", players[pid].i_savingThrows[SAVE_WISDOM]);
	printf("p[i].i_armorClass[AC_NORMAL] = %d;\n", players[pid].i_armorClass[AC_NORMAL]);
	printf("p[i].i_armorClass[AC_TOUCH] = %d;\n", players[pid].i_armorClass[AC_TOUCH]);
	printf("p[i].i_armorClass[AC_FLATFOOTED] = %d;\n", players[pid].i_armorClass[AC_FLATFOOTED]);
	printf("p[i].i_armorClassSplit[AC_SECTION_DEX] = %d;\n", players[pid].i_armorClassSplit[AC_SECTION_DEX]);
	printf("p[i].i_armorClassSplit[AC_SECTION_SIZE] = %d;\n", players[pid].i_armorClassSplit[AC_SECTION_SIZE]);
	printf("p[i].i_armorClassSplit[AC_SECTION_DEFLECTION] = %d;\n", players[pid].i_armorClassSplit[AC_SECTION_DEFLECTION]);
	printf("p[i].i_armorClassSplit[AC_SECTION_NATURAL] = %d;\n", players[pid].i_armorClassSplit[AC_SECTION_NATURAL]);
	printf("p[i].i_armorClassSplit[AC_SECTION_ARMOR] = %d;\n", players[pid].i_armorClassSplit[AC_SECTION_ARMOR]);
	printf("p[i].i_armorClassSplit[AC_SECTION_SHIELD] = %d;\n", players[pid].i_armorClassSplit[AC_SECTION_SHIELD]);
	printf("p[i].i_armorClassSplit[AC_SECTION_DODGE] = %d;\n", players[pid].i_armorClassSplit[AC_SECTION_DODGE]);
	printf("p[i].i_bab[BAB_MELEE][0] = %d;\n", players[pid].i_bab[BAB_MELEE][0]);
	printf("p[i].i_bab[BAB_RANGED][0] = %d;\n", players[pid].i_bab[BAB_RANGED][0]);
	printf("p[i].i_bab[BAB_GRAPPLE][0] = %d;\n", players[pid].i_bab[BAB_GRAPPLE][0]);
	printf("p[i].i_bab[BAB_MELEE][1] = %d;\n", players[pid].i_bab[BAB_MELEE][1]);
	printf("p[i].i_bab[BAB_RANGED][1] = %d;\n", players[pid].i_bab[BAB_RANGED][1]);
	printf("p[i].i_bab[BAB_GRAPPLE][1] = %d;\n", players[pid].i_bab[BAB_GRAPPLE][1]);
	printf("p[i].i_bab[BAB_MELEE][2] = %d;\n", players[pid].i_bab[BAB_MELEE][2]);
	printf("p[i].i_bab[BAB_RANGED][2] = %d;\n", players[pid].i_bab[BAB_RANGED][2]);
	printf("p[i].i_bab[BAB_GRAPPLE][2] = %d;\n", players[pid].i_bab[BAB_GRAPPLE][2]);
	printf("p[i].i_initiative[0] = %d;\n", players[pid].i_initiative[0]);
	printf("p[i].i_initiative[1] = %d;\n", players[pid].i_initiative[1]);
	printf("p[i].i_speed = %d;\n", players[pid].i_speed);
	printf("p[i].i_inactive = %d;\n", players[pid].i_inactive);
	printf("p[i].i_stun = %d;\n", players[pid].i_stun);
	printf("p[i].i_noAttacks = %d;\n", players[pid].i_noAttacks);

	printf("p[i].i_regeneration = %d;\n", players[pid].i_regeneration);
	for (int i=0; i<8; i++) {
		printf("p[i].i_resistances[%d] = %d;\n", i, players[pid].i_regeneration);
		printf("p[i].i_resistancesUsed[%d] = %d;\n", i, players[pid].i_regeneration);
	}

	printf("strcpy(p[i].c_iconFile, \"%s\");\n", players[pid].c_iconFile);
	printf("strcpy(p[i].c_items, \"%s\");\n", players[pid].c_items);

	printf("p[i].i_negateCrit = %d;\n", players[pid].i_negateCrit);
	
	for (int j=0; j<MAX_WEAPONS; j++) {
		if (players[pid].w_weapons[j].c_description[0] != '\0') {
			printf("p[i].w_weapons[%d].c_available = %d;\n", j, players[pid].w_weapons[j].c_available);
			printf("strcpy(p[i].w_weapons[%d].c_description, \"%s\");\n", j, players[pid].w_weapons[j].c_description);
			printf("p[i].w_weapons[%d].i_attackBonus[0] = %d;\n", j, players[pid].w_weapons[j].i_attackBonus[0]);
			printf("p[i].w_weapons[%d].i_attackBonus[1] = %d;\n", j, players[pid].w_weapons[j].i_attackBonus[1]);
			printf("p[i].w_weapons[%d].i_attackBonus[2] = %d;\n", j, players[pid].w_weapons[j].i_attackBonus[2]);
			printf("p[i].w_weapons[%d].i_attackBonus[3] = %d;\n", j, players[pid].w_weapons[j].i_attackBonus[3]);
			printf("strcpy(p[i].w_weapons[%d].c_damage, \"%s\");\n", j, players[pid].w_weapons[j].c_damage);
			printf("strcpy(p[i].w_weapons[%d].c_critical, \"%s\");\n", j, players[pid].w_weapons[j].c_critical);
			printf("p[i].w_weapons[%d].i_magicalBonus = %d;\n", j, players[pid].w_weapons[j].i_magicalBonus);
			printf("p[i].w_weapons[%d].i_range = %d;\n", j, players[pid].w_weapons[j].i_range);
			printf("p[i].w_weapons[%d].i_reach = %d;\n", j, players[pid].w_weapons[j].i_reach);
			printf("p[i].w_weapons[%d].i_noAttacks = %d;\n", j, players[pid].w_weapons[j].i_noAttacks);
			printf("strcpy(p[i].w_weapons[%d].c_message, \"%s\");\n", j, players[pid].w_weapons[j].c_message);
			printf("p[i].w_weapons[%d].c_attackType = %d;\n", j, players[pid].w_weapons[j].c_attackType);
		}
	}
	
	printf("p[i].f_challengeRating = %.2f;\n", players[pid].f_challengeRating);
	printf("p[i].i_d20Rolls[0] = %d;\n", players[pid].i_d20Rolls[0]);
	printf("p[i].i_d20Rolls[1] = %d;\n", players[pid].i_d20Rolls[1]);
	printf("p[i].i_d20Rolls[2] = %d;\n", players[pid].i_d20Rolls[2]);
	printf("p[i].i_d20Rolls[3] = %d;\n", players[pid].i_d20Rolls[3]);
	printf("p[i].i_d20Rolls[4] = %d;\n", players[pid].i_d20Rolls[4]);
	printf("p[i].i_d20Rolls[5] = %d;\n", players[pid].i_d20Rolls[5]);
	printf("p[i].i_d20Rolls[6] = %d;\n", players[pid].i_d20Rolls[6]);
	printf("p[i].i_spellDC[0] = %d;\n", players[pid].i_spellDC[0]);
	printf("p[i].i_spellDC[1] = %d;\n", players[pid].i_spellDC[1]);
	printf("p[i].i_spellDC[2] = %d;\n", players[pid].i_spellDC[2]);
	printf("p[i].i_spellDC[3] = %d;\n", players[pid].i_spellDC[3]);
	printf("p[i].i_spellDC[4] = %d;\n", players[pid].i_spellDC[4]);
	printf("p[i].i_spellDC[5] = %d;\n", players[pid].i_spellDC[5]);
	printf("p[i].i_spellDC[6] = %d;\n", players[pid].i_spellDC[6]);
	printf("p[i].i_spellDC[7] = %d;\n", players[pid].i_spellDC[7]);
	printf("p[i].i_spellDC[8] = %d;\n", players[pid].i_spellDC[8]);
	printf("p[i].i_spellFailure = %d;\n", players[pid].i_spellFailure);
	printf("p[i].i_abilityStats[0][0] = %d;\n", players[pid].i_abilityStats[0][0]);
	printf("p[i].i_abilityStats[1][0] = %d;\n", players[pid].i_abilityStats[1][0]);
	printf("p[i].i_abilityStats[0][1] = %d;\n", players[pid].i_abilityStats[0][1]);
	printf("p[i].i_abilityStats[1][1] = %d;\n", players[pid].i_abilityStats[1][1]);
	printf("p[i].i_abilityStats[0][2] = %d;\n", players[pid].i_abilityStats[0][2]);
	printf("p[i].i_abilityStats[1][2] = %d;\n", players[pid].i_abilityStats[1][2]);
	printf("p[i].i_abilityStats[0][3] = %d;\n", players[pid].i_abilityStats[0][3]);
	printf("p[i].i_abilityStats[1][3] = %d;\n", players[pid].i_abilityStats[1][3]);
	printf("p[i].i_abilityStats[0][4] = %d;\n", players[pid].i_abilityStats[0][4]);
	printf("p[i].i_abilityStats[1][4] = %d;\n", players[pid].i_abilityStats[1][4]);
	printf("p[i].i_abilityStats[0][5] = %d;\n", players[pid].i_abilityStats[0][5]);
	printf("p[i].i_abilityStats[1][5] = %d;\n", players[pid].i_abilityStats[1][5]);
	printf("p[i].i_skills[SKILL_SEARCH] = %d;\n", players[pid].i_skills[SKILL_SEARCH]);
	printf("p[i].i_skills[SKILL_SOH] = %d;\n", players[pid].i_skills[SKILL_SOH]);
	printf("p[i].i_skills[SKILL_SPOT] = %d;\n", players[pid].i_skills[SKILL_SPOT]);
	printf("p[i].i_skills[SKILL_OPENLOCKS] = %d;\n", players[pid].i_skills[SKILL_OPENLOCKS]);
	printf("p[i].i_skills[SKILL_MOVESILENTLY] = %d;\n", players[pid].i_skills[SKILL_MOVESILENTLY]);
	printf("p[i].i_skills[SKILL_LISTEN] = %d;\n", players[pid].i_skills[SKILL_LISTEN]);
	printf("p[i].i_skills[SKILL_HIDE] = %d;\n", players[pid].i_skills[SKILL_HIDE]);
	printf("p[i].i_skills[SKILL_CONCENTRATION] = %d;\n", players[pid].i_skills[SKILL_CONCENTRATION]);
	printf("p[i].i_spellResistance = %d;\n", players[pid].i_spellResistance);
	printf("p[i].i_damageReduction[0] = %d;\n", players[pid].i_damageReduction[0]);
	printf("p[i].i_damageReduction[1] = %d;\n", players[pid].i_damageReduction[1]);
	printf("p[i].i_damageReduction[2] = %d;\n", players[pid].i_damageReduction[2]);
	printf("p[i].i_size = %d;\n", players[pid].i_size);
	printf("p[i].i_xp[MAX] = %d;\n", players[pid].i_xp[MAX]);
	printf("p[i].i_xp[TMP] = %d;\n", players[pid].i_xp[TMP]);
	printf("p[i].i_inGroup = %d;\n", players[pid].i_inGroup);
	printf("strcpy(p[i].c_hitDice, \"%s\");\n", players[pid].c_hitDice);

	printf("p[i].flags.f_isStabilised = %d;\n", players[pid].flags.f_isStabilised);
	printf("p[i].flags.f_disabled = %d;\n", players[pid].flags.f_disabled);
	printf("p[i].flags.f_ignoreCriticals = %d;\n", players[pid].flags.f_ignoreCriticals);
	printf("p[i].flags.f_autoStablise = %d;\n", players[pid].flags.f_autoStablise);
	printf("p[i].flags.f_evasion = %d;\n", players[pid].flags.f_evasion);

	printf("p[i].spellsAvailable.i_maxLevel0 = %d;\n", players[pid].spellsAvailable.i_maxLevel0);
	printf("p[i].spellsAvailable.i_maxLevel1 = %d;\n", players[pid].spellsAvailable.i_maxLevel1);
	printf("p[i].spellsAvailable.i_maxLevel2 = %d;\n", players[pid].spellsAvailable.i_maxLevel2);
	printf("p[i].spellsAvailable.i_maxLevel3 = %d;\n", players[pid].spellsAvailable.i_maxLevel3);
	printf("p[i].spellsAvailable.i_maxLevel4 = %d;\n", players[pid].spellsAvailable.i_maxLevel4);
	printf("p[i].spellsAvailable.i_maxLevel5 = %d;\n", players[pid].spellsAvailable.i_maxLevel5);
	printf("p[i].spellsAvailable.i_maxLevel6 = %d;\n", players[pid].spellsAvailable.i_maxLevel6);
	printf("p[i].spellsAvailable.i_maxLevel7 = %d;\n", players[pid].spellsAvailable.i_maxLevel7);
	printf("p[i].spellsAvailable.i_maxLevel8 = %d;\n", players[pid].spellsAvailable.i_maxLevel8);
	printf("p[i].spellsAvailable.i_maxLevel9 = %d;\n", players[pid].spellsAvailable.i_maxLevel9);
	printf("p[i].spellsAvailable.i_curLevel0 = %d;\n", players[pid].spellsAvailable.i_maxLevel0);
	printf("p[i].spellsAvailable.i_curLevel1 = %d;\n", players[pid].spellsAvailable.i_maxLevel1);
	printf("p[i].spellsAvailable.i_curLevel2 = %d;\n", players[pid].spellsAvailable.i_maxLevel2);
	printf("p[i].spellsAvailable.i_curLevel3 = %d;\n", players[pid].spellsAvailable.i_maxLevel3);
	printf("p[i].spellsAvailable.i_curLevel4 = %d;\n", players[pid].spellsAvailable.i_maxLevel4);
	printf("p[i].spellsAvailable.i_curLevel5 = %d;\n", players[pid].spellsAvailable.i_maxLevel5);
	printf("p[i].spellsAvailable.i_curLevel6 = %d;\n", players[pid].spellsAvailable.i_maxLevel6);
	printf("p[i].spellsAvailable.i_curLevel7 = %d;\n", players[pid].spellsAvailable.i_maxLevel7);
	printf("p[i].spellsAvailable.i_curLevel8 = %d;\n", players[pid].spellsAvailable.i_maxLevel8);
	printf("p[i].spellsAvailable.i_curLevel9 = %d;\n", players[pid].spellsAvailable.i_maxLevel9);

	printf("i++;\n\n");
}

/********************************************************************************/
void dump_player_details() {
	int i;
	for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) { 
		if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) { dump_player_data(i); }
	}
}

/********************************************************************************/
void calcELLevel() {
	int i=0,j=0;

	aELC_Results->clear();
	i = (int )aELC_ELLevel->value();
//	sprintf(mybuf2, "Less than %d = why bother !", i); aELC_Results->add(mybuf2);
	if (i < 4) {
		sprintf(mybuf2, "1 * CR %d,%d", i,i+1); aELC_Results->add(mybuf2);
	} else {
		sprintf(mybuf2, "1 * CR %d,%d,%d", i-1,i,i+1); aELC_Results->add(mybuf2);
	}
	for (j=2; j<6; j++) {
		if ((i-j) == 1) { sprintf(mybuf2, "%d * CR 1,2", j); aELC_Results->add(mybuf2); } else
		if ((i-j) == 0) { sprintf(mybuf2, "%d * CR 1", j); aELC_Results->add(mybuf2); } else
		if ((i-j) > 1) { sprintf(mybuf2, "%d * CR %d", j, (i-j)); aELC_Results->add(mybuf2); } 
	}
	aELC_Results->add("");
	if (i > 3) { sprintf(mybuf2, "1 * CR %d + 1 * CR %d", i-1, i-3); aELC_Results->add(mybuf2); } else
	if (i == 3) { sprintf(mybuf2, "1 * CR 2 + 1 * CR 1"); aELC_Results->add(mybuf2); } else
	if (i == 2) { sprintf(mybuf2, "1 * CR 1 + 1 * CR 0.5"); aELC_Results->add(mybuf2); } else
	if (i < 2) { sprintf(mybuf2, "1 * CR 0.5 + 1 * CR 0.3"); aELC_Results->add(mybuf2); } 
}

/********************************************************************************/
const char *htmlLoadLink(Fl_Widget *w, const char *c) {	
//	printf("hLL: 0 : %s\n", c);
	if (a_SRDText->filename() != NULL) {
		htmlLevel++;
		if (htmlLevel >= 4) { htmlLevel = 3; }
		strcpy(&prevHtmlPage[0][0], a_SRDText->filename());
if (config.flags.f_debug != 0) { printf("hLL: 0 : %d %s\n", htmlLevel, &prevHtmlPage[0][0]); }
		if (htmlLevel == 0) { prevHtmlPage[1][0] = '\0'; prevHtmlPage[2][0] = '\0'; }
	}
	return(c);
}

/********************************************************************************/
void doMassSkillCheck(int option) {
	int i=0,j=0,k=0,l=0,m=0;
	int v1=0,v2=0;

if (config.flags.f_debug != 0) { printf("dMSC: %d\n", option); }

	switch (option) {
		case 0: aMSC_DoingList->clear();
				  j=0;
				  for (i=0; i < MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							if (i >= MAX_PLAYERS) {
								if ((getHPs(i) < 0 && config.flags.f_showDeadMonsters != 0) || getHPs(i) > -1) {
									config.i_idList[ID_MSKILLCHK][j++] = i;
									aMSC_DoingList->add(players[i].c_name);
								}
							} else {
								config.i_idList[ID_MSKILLCHK][j++] = i;
								aMSC_DoingList->add(players[i].c_name);
							}
						}
				  }
				  config.i_idList[ID_MSKILLCHK][j] = -1;
				  aMSC_DCValue->value("0");
				  aMSC_DoingList->redraw();
				  break;

		case 1:
				  break;

		case 2:
				  k = atoi(aMSC_DCValue->value());
				  if (k > 0) {
if (config.flags.f_debug != 0) { printf("dMSC: %d %d %d\n", option, aMSC_flags->value(), aMSC_SkillList->value()); }
						aMSC_ResultList->clear();
						for (i=0; i < aMSC_DoingList->nitems(); i++) {
							if (aMSC_DoingList->checked(i) != 0) {				// is it marked
								j = config.i_idList[ID_MSKILLCHK][i-1];		// get the player ID
								if (aMSC_flags->value() == 1) {					// roll a d20
									v1 = getRND(20);
								} else if (aMSC_flags->value() == 2) {			// use a prerolled d20
									for (m=6; m >= 0; m--) {
										if (players[j].i_d20Rolls[m] > 0) {
											v1 = players[j].i_d20Rolls[m];
											players[j].i_d20Rolls[m] = 0;
											break;
										}
									}
									if (m < 0) {										// were there any left to use
										if (config.i_diceSystem == DICE_D20) {
											v1 = getRND(20);
										} else {
											v1 = getRND(100);
										}
									}
								} 
								v2 = getAdjustment(j, MOD_SKILL) + players[j].i_skills[aMSC_SkillList->value()];
if (config.flags.f_debug != 0) { printf("dMSC: %d %s (%d:%d:%d)\n", option, players[j].c_name, l, k, players[j].i_skills[aMSC_SkillList->value()]); }

								if ((v1+v2) >= k) {		// did they fail or succeed
									if (m < 0) {
										sprintf(mybuf2, "@B63@.>> %s by %d (Rolled %d+%d)", players[j].c_name, (v1+v2-k), v1,v2);
									} else {
										sprintf(mybuf2, "@B63@.%s by %d (Rolled %d+%d)", players[j].c_name, (v1+v2-k), v1,v2);
									}
								} else {
									if (m < 0) {
										sprintf(mybuf2, "@B88@.>> %s by %d (Rolled %d+%d)", players[j].c_name, (v1+v2-k)*-1, v1,v2);
									} else {
										sprintf(mybuf2, "@B88@.%s by %d (Rolled %d+%d)", players[j].c_name, (v1+v2-k)*-1, v1,v2);
									}
								}
								aMSC_ResultList->add(mybuf2);
							}
						}
				  }
				  break;
	}
	a_TMassSkillCheck->redraw();
	return;
}

/********************************************************************************/
void dumpAdjustments() {
	int i,j,k;
	int a=0;

	for (i=0; i<MAX_MODIFIERS; i++) {
		if (config.system_mods[i].c_message[0] != '-') {
			printf("strcpy(config.system_mods[%d].c_message, \"%s\");\n", a, config.system_mods[i].c_message);
			printf("config.system_mods[%d].i_noRounds = %d;\n", a, config.system_mods[i].i_noRounds);
			for (j=0; j<5; j++) {
				for (k=0; k<3; k++) {
					printf("config.system_mods[%d].i_data[%d][%d] = %d;\n", a, j,k, config.system_mods[i].i_data[j][k]);
				}
			}
			a++;
		}
	}

	for (i=0; i<MAX_MODIFIERS; i++) {
		if (config.action_mods[i].c_message[0] != '-') {
			printf("strcpy(config.system_mods[%d].c_message, \"%s\");\n", a, config.action_mods[i].c_message);
			printf("config.system_mods[%d].i_noRounds = %d;\n", a, config.action_mods[i].i_noRounds);
			for (j=0; j<5; j++) {
				for (k=0; k<3; k++) {
					printf("config.system_mods[%d].i_data[%d][%d] = %d;\n", a, j,k, config.action_mods[i].i_data[j][k]);
				}
			}
			a++;
		}
	}
}

/********************************************************************************/
void loadStdModifiers() {
int i=0;

	memset(config.system_mods[0].c_message, '\0', sizeof(ADMPmodifiers) * MAX_MODIFIERS);

	for (i=0; i<MAX_MODIFIERS; i++) {
		sprintf(config.system_mods[i].c_message, "-- empty slot %d", i);
	}

#include "stdmodifiers.h"

	doAdjustmentAction(9);		// refresh
}

/********************************************************************************/
void rollRNDDice() {
	int dt[8] = {4,6,8,10,12,20,30,100}, sm[8] = {0,0,0,0,0,0,0,0},
		     rd[8] = {0,0,0,0,0,0,0,0};
	char buf[256], bc[8];

	a_ODRList1->clear(); a_ODRList2->clear(); a_ODRList3->clear(); a_ODRList4->clear();
	a_ODRList5->clear(); a_ODRList6->clear(); a_ODRList7->clear(); a_ODRList8->clear();
	a_ODRList1->add("@b  d4"); a_ODRList2->add("@b  d6"); a_ODRList3->add("@b  d8"); a_ODRList4->add("@b   d10");
	a_ODRList5->add("@b   d12"); a_ODRList6->add("@b   d20"); a_ODRList7->add("@b   d30"); a_ODRList8->add("@b   d100");

	a_CTDRList1->clear(); a_CTDRList2->clear(); a_CTDRList3->clear(); a_CTDRList4->clear();
	a_CTDRList5->clear(); a_CTDRList6->clear(); a_CTDRList7->clear(); a_CTDRList8->clear();
	a_CTDRList1->add("@b  d4"); a_CTDRList2->add("@b  d6"); a_CTDRList3->add("@b  d8"); a_CTDRList4->add("@b   d10");
	a_CTDRList5->add("@b   d12"); a_CTDRList6->add("@b   d20"); a_CTDRList7->add("@b   d30"); a_CTDRList8->add("@b   d100");

	d1_CTDRList1->clear(); d1_CTDRList2->clear(); d1_CTDRList3->clear(); d1_CTDRList4->clear();
	d1_CTDRList5->clear(); d1_CTDRList6->clear(); d1_CTDRList7->clear(); d1_CTDRList8->clear();
	d1_CTDRList1->add("@b  d4"); d1_CTDRList2->add("@b  d6"); d1_CTDRList3->add("@b  d8"); d1_CTDRList4->add("@b   d10");
	d1_CTDRList5->add("@b   d12"); d1_CTDRList6->add("@b   d20"); d1_CTDRList7->add("@b   d30"); d1_CTDRList8->add("@b   d100");

	for (int k=(int )a_ODRCount->value(); k > 0; k--) {
		bc[0] = '\0';
		if ((k-1) % 5 == 0) { strcpy(bc, "@B95@."); }
		rd[0] = getRND(dt[0]); sm[0] += rd[0];
		rd[1] = getRND(dt[1]); sm[1] += rd[1];
		rd[2] = getRND(dt[2]); sm[2] += rd[2];
		rd[3] = getRND(dt[3]); sm[3] += rd[3];
		rd[4] = getRND(dt[4]); sm[4] += rd[4];
		rd[5] = getRND(dt[5]); sm[5] += rd[5];
		rd[6] = getRND(dt[6]); sm[6] += rd[6];
		rd[7] = getRND(dt[7]); sm[7] += rd[7];
		sprintf(buf, "%s%d (%d)", bc, rd[0], sm[0]); a_ODRList1->add(buf); a_CTDRList1->add(buf); d1_CTDRList1->add(buf);
		sprintf(buf, "%s%d (%d)", bc, rd[1], sm[1]); a_ODRList2->add(buf); a_CTDRList2->add(buf); d1_CTDRList2->add(buf);
		sprintf(buf, "%s%d (%d)", bc, rd[2], sm[2]); a_ODRList3->add(buf); a_CTDRList3->add(buf); d1_CTDRList3->add(buf);
		sprintf(buf, "%s%2d (%d)", bc, rd[3], sm[3]); a_ODRList4->add(buf); a_CTDRList4->add(buf); d1_CTDRList4->add(buf);
		sprintf(buf, "%s%2d (%d)", bc, rd[4], sm[4]); a_ODRList5->add(buf); a_CTDRList5->add(buf); d1_CTDRList5->add(buf);
		sprintf(buf, "%s%2d (%d)", bc, rd[5], sm[5]); a_ODRList6->add(buf); a_CTDRList6->add(buf); d1_CTDRList6->add(buf);
		sprintf(buf, "%s%2d (%d)", bc, rd[6], sm[6]); a_ODRList7->add(buf); a_CTDRList7->add(buf); d1_CTDRList7->add(buf);
		sprintf(buf, "%s%3d (%d)", bc, rd[7], sm[7]); a_ODRList8->add(buf); a_CTDRList8->add(buf); d1_CTDRList8->add(buf);
	}
}

/********************************************************************************/
void doCleanUp() {
int i;

	combatGridMap->getGridTile()->cleanUp();

	for (i=0; i<MAX_ICONS; i++) { 
		if (buttonIcons[i] != NULL) { delete buttonIcons[i]; }
		if (selectIcons[i] != NULL) { delete selectIcons[i]; }
		if (pngIcons[i] != NULL) { delete pngIcons[i]; } 
		if (jpgIcons[i] != NULL) { delete jpgIcons[i]; }
	}
	for (i=0; i<MAX_MEMBERS; i++) { 
		if (w_Initiatives[i] != NULL) { delete w_Initiatives[i]; }
	}
	for (i=0; i<MAX_D100TABLES; i++) { 
		if (d100TableMem[i] != NULL) { free(d100TableMem[i]); }
	}
}

/********************************************************************************/
void doSystemExit() {
	a_Exit->show();
	for (;;) {
		Fl_Widget *o = Fl::readqueue();
		if (!o) {
			Fl::wait();
		} else if ( o == a_EBExit) { doCleanUp(); exit(0);
		} else if ( o == a_EBCancel) { break;
		} else if ( o == a_EBSaveExit) { saveAllData(); doCleanUp(); exit(0);
		}
	}
	a_Exit->hide();
}

/********************************************************************************/
void qkMonsterAction(int action) {		// set the color of the selected monster
static int selected=-1;
int i=0;

	i = config.i_idList[ID_QMON][selected];

if (config.flags.f_debug != 0) { printf("qkMA: %d %d %d\n", action, i, selected); }

	switch (action) {
		case 0: selected = -1;
				  break;

		case 1: if (selected != -1) {
				  		sprintf(mybuf2, "%s (CR: %.1f)", &qkmonsters[i].c_name[0], qkmonsters[i].f_challengeRating);
				  		a_EdtQkMonList->text(selected+1, mybuf2);
				  }
				  selected = a_EdtQkMonList->value()-1;
				  i = config.i_idList[ID_QMON][selected];	
				  if (selected < 0 || selected > MAX_MEMBERS) { selected = -1; return; }
				  sprintf(mybuf2, "@B95@.%s (CR: %.1f)", &qkmonsters[i].c_name[0], qkmonsters[i].f_challengeRating);
				  a_EdtQkMonList->text(selected+1, mybuf2);
				  break;
	}
}

/********************************************************************************/
int pi_id=0, wi_id=0;

int writePlayerWeaponData() {
FILE *wfile;
ADMPweapon *wp;

	wfile = pdbFilePointer;
	if ((wp = (ADMPweapon *)pdbDataPointer) == NULL) { return -1; }

//	pdbPutInt(wfile, players[pid].i_id);
	pdbPutInt(wfile, pi_id);
	pdbPutInt(wfile, wi_id);
	pdbPutInt(wfile, wp->c_available);
	pdbPutString(wfile, &wp->c_description[0]);
	pdbPutInt(wfile, wp->i_attackBonus[0]);
	pdbPutInt(wfile, wp->i_attackBonus[1]);
	pdbPutInt(wfile, wp->i_attackBonus[2]);
	pdbPutInt(wfile, wp->i_attackBonus[3]);
	pdbPutString(wfile, wp->c_damage);
	pdbPutString(wfile, wp->c_critical);
	pdbPutInt(wfile, wp->i_magicalBonus);
	pdbPutInt(wfile, wp->i_range);
	pdbPutInt(wfile, wp->i_reach);
	pdbPutInt(wfile, wp->i_noAttacks);
	pdbPutString(wfile, wp->c_message);
	pdbPutInt(wfile, wp->c_attackType);
	pdbPutString(wfile, wp->c_table);
	pdbPutInt(wfile, wp->i_doneAttacks);
	pdbPutInt(wfile, wp->i_size);
	pdbPutInt(wfile, wp->i_type);
	pdbPutInt(wfile, wp->i_fumble);
	pdbPutInt(wfile, wp->i_critAdjust);

	return 0;
}

/********************************************************************************/
int writePlayerData() {
FILE *ofile;
ADMPplayer *pd;
int i;

	ofile = pdbFilePointer;
	if ((pd = (ADMPplayer *)pdbDataPointer) == NULL) { return -1; }

	pdbPutInt(ofile, pi_id);

	pdbPutString(ofile, pd->c_name);
	pdbPutInt(ofile, pd->i_race);
	pdbPutInt(ofile, pd->i_alignment);
	pdbPutInt(ofile, pd->i_classes[0]);
	pdbPutInt(ofile, pd->i_classes[1]);
	pdbPutInt(ofile, pd->i_classes[2]);
	pdbPutInt(ofile, pd->i_classes[3]);
	pdbPutInt(ofile, pd->i_levels[0]);
	pdbPutInt(ofile, pd->i_levels[1]);
	pdbPutInt(ofile, pd->i_levels[2]);
	pdbPutInt(ofile, pd->i_levels[3]);
	pdbPutInt(ofile, pd->i_hp[HP_MAX]);
	pdbPutInt(ofile, pd->i_hp[HP_CUR]);
	pdbPutInt(ofile, pd->i_hp[HP_NL]);
	pdbPutInt(ofile, pd->i_hp[HP_TMP]);
	pdbPutInt(ofile, pd->i_bleeding);
	pdbPutInt(ofile, pd->i_disabledAt);
	pdbPutInt(ofile, pd->i_unconciousAt);
	pdbPutInt(ofile, pd->i_savingThrows[SAVE_FORTITUDE]);
	pdbPutInt(ofile, pd->i_savingThrows[SAVE_REFLEX]);
	pdbPutInt(ofile, pd->i_savingThrows[SAVE_WISDOM]);
	pdbPutInt(ofile, pd->i_armorClass[AC_NORMAL]);
	pdbPutInt(ofile, pd->i_armorClass[AC_TOUCH]);
	pdbPutInt(ofile, pd->i_armorClass[AC_FLATFOOTED]);
	pdbPutInt(ofile, pd->i_armorClassSplit[AC_SECTION_DEX]);
	pdbPutInt(ofile, pd->i_armorClassSplit[AC_SECTION_SIZE]);
	pdbPutInt(ofile, pd->i_armorClassSplit[AC_SECTION_DEFLECTION]);
	pdbPutInt(ofile, pd->i_armorClassSplit[AC_SECTION_NATURAL]);
	pdbPutInt(ofile, pd->i_armorClassSplit[AC_SECTION_ARMOR]);
	pdbPutInt(ofile, pd->i_armorClassSplit[AC_SECTION_SHIELD]);
	pdbPutInt(ofile, pd->i_bab[BAB_MELEE][0]);
	pdbPutInt(ofile, pd->i_bab[BAB_RANGED][0]);
	pdbPutInt(ofile, pd->i_bab[BAB_GRAPPLE][0]);
	pdbPutInt(ofile, pd->i_bab[BAB_MELEE][1]);
	pdbPutInt(ofile, pd->i_bab[BAB_RANGED][1]);
	pdbPutInt(ofile, pd->i_bab[BAB_GRAPPLE][1]);
	pdbPutInt(ofile, pd->i_bab[BAB_MELEE][2]);
	pdbPutInt(ofile, pd->i_bab[BAB_RANGED][2]);
	pdbPutInt(ofile, pd->i_bab[BAB_GRAPPLE][2]);
	pdbPutInt(ofile, pd->i_initiative[0]);
	pdbPutInt(ofile, pd->i_initiative[1]);
	pdbPutInt(ofile, pd->i_speed);
	pdbPutInt(ofile, pd->i_inactive);
	pdbPutInt(ofile, pd->i_stun);
	pdbPutInt(ofile, pd->i_noAttacks);

	pdbPutFloat(ofile, pd->f_challengeRating);
	pdbPutInt(ofile, pd->i_d20Rolls[0]);
	pdbPutInt(ofile, pd->i_d20Rolls[1]);
	pdbPutInt(ofile, pd->i_d20Rolls[2]);
	pdbPutInt(ofile, pd->i_d20Rolls[3]);
	pdbPutInt(ofile, pd->i_d20Rolls[4]);
	pdbPutInt(ofile, pd->i_d20Rolls[5]);
	pdbPutInt(ofile, pd->i_d20Rolls[6]);
	pdbPutInt(ofile, pd->i_spellDC[0]);
	pdbPutInt(ofile, pd->i_spellDC[1]);
	pdbPutInt(ofile, pd->i_spellDC[2]);
	pdbPutInt(ofile, pd->i_spellDC[3]);
	pdbPutInt(ofile, pd->i_spellDC[4]);
	pdbPutInt(ofile, pd->i_spellDC[5]);
	pdbPutInt(ofile, pd->i_spellDC[6]);
	pdbPutInt(ofile, pd->i_spellFailure);
	pdbPutInt(ofile, pd->i_abilityStats[0][0]);
	pdbPutInt(ofile, pd->i_abilityStats[1][0]);
	pdbPutInt(ofile, pd->i_abilityStats[0][1]);
	pdbPutInt(ofile, pd->i_abilityStats[1][1]);
	pdbPutInt(ofile, pd->i_abilityStats[0][2]);
	pdbPutInt(ofile, pd->i_abilityStats[1][2]);
	pdbPutInt(ofile, pd->i_abilityStats[0][3]);
	pdbPutInt(ofile, pd->i_abilityStats[1][3]);
	pdbPutInt(ofile, pd->i_abilityStats[0][4]);
	pdbPutInt(ofile, pd->i_abilityStats[1][4]);
	pdbPutInt(ofile, pd->i_abilityStats[0][5]);
	pdbPutInt(ofile, pd->i_abilityStats[1][5]);
	pdbPutInt(ofile, pd->i_skills[SKILL_SEARCH]);
	pdbPutInt(ofile, pd->i_skills[SKILL_SOH]);
	pdbPutInt(ofile, pd->i_skills[SKILL_SPOT]);
	pdbPutInt(ofile, pd->i_skills[SKILL_OPENLOCKS]);
	pdbPutInt(ofile, pd->i_skills[SKILL_MOVESILENTLY]);
	pdbPutInt(ofile, pd->i_skills[SKILL_LISTEN]);
	pdbPutInt(ofile, pd->i_skills[SKILL_HIDE]);
	pdbPutInt(ofile, pd->i_skills[SKILL_CONCENTRATION]);
	pdbPutInt(ofile, pd->i_spellResistance);
	pdbPutInt(ofile, pd->i_damageReduction[0]);
	pdbPutInt(ofile, pd->i_damageReduction[1]);
	pdbPutInt(ofile, pd->i_damageReduction[2]);
	pdbPutInt(ofile, pd->i_size);
	pdbPutInt(ofile, pd->i_xp[MAX]);
	pdbPutInt(ofile, pd->i_xp[TMP]);
	pdbPutInt(ofile, pd->i_inGroup);
	pdbPutString(ofile, pd->c_hitDice);
	pdbPutInt(ofile, pd->flags.f_isStabilised);
	pdbPutInt(ofile, pd->flags.f_disabled);
	pdbPutInt(ofile, pd->flags.f_ignoreCriticals);
	pdbPutInt(ofile, pd->flags.f_autoStablise);
	pdbPutInt(ofile, pd->flags.f_evasion);

	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel0);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel1);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel2);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel3);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel4);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel5);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel6);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel7);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel8);
	pdbPutInt(ofile, pd->spellsAvailable.i_maxLevel9);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel0);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel1);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel2);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel3);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel4);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel5);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel6);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel7);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel8);
	pdbPutInt(ofile, pd->spellsAvailable.i_curLevel9);

	pdbPutInt(ofile, pd->i_playerID);
	pdbPutInt(ofile, pd->i_stdMonsterID);
	pdbPutInt(ofile, pd->flags.f_npc);
	pdbPutInt(ofile, pd->i_regeneration);
	pdbPutString(ofile, pd->c_iconFile);
	pdbPutInt(ofile, pd->i_inGroup);
	pdbPutInt(ofile, pd->i_mapX);
	pdbPutInt(ofile, pd->i_mapY);
	pdbPutInt(ofile, pd->i_reach);
	pdbPutInt(ofile, pd->i_space);
	pdbPutInt(ofile, pd->flags.f_invisible);

	pdbPutInt(ofile, pd->i_resistances[RESIST_FIRE]);
	pdbPutInt(ofile, pd->i_resistancesUsed[RESIST_FIRE]);
	pdbPutInt(ofile, pd->i_resistances[RESIST_ACID]);
	pdbPutInt(ofile, pd->i_resistancesUsed[RESIST_ACID]);
	pdbPutInt(ofile, pd->i_resistances[RESIST_COLD]);
	pdbPutInt(ofile, pd->i_resistancesUsed[RESIST_COLD]);
	pdbPutInt(ofile, pd->i_resistances[RESIST_ELEC]);
	pdbPutInt(ofile, pd->i_resistancesUsed[RESIST_ELEC]);
	pdbPutInt(ofile, pd->i_resistances[RESIST_SONIC]);
	pdbPutInt(ofile, pd->i_resistancesUsed[RESIST_SONIC]);

	pdbPutString(ofile, pd->c_items);
	pdbPutInt(ofile, pd->i_negateCrit);
	pdbPutInt(ofile, pd->i_armorClassSplit[AC_SECTION_DODGE]);
	pdbPutInt(ofile, pd->i_useShieldOn);
	pdbPutInt(ofile, pd->i_useDodgeOn);
	pdbPutInt(ofile, pd->flags.f_wasViewed);
	pdbPutInt(ofile, pd->i_spellDC[7]);
	pdbPutInt(ofile, pd->i_spellDC[8]);
	pdbPutInt(ofile, pd->i_hp[HP_ENH]);
	pdbPutInt(ofile, pd->i_doneAttacks);

	pdbPutInt(ofile, pd->i_savingThrows[SAVE_MENTAL]);
	pdbPutInt(ofile, pd->i_savingThrows[SAVE_DISEASE]);

	pdbPutInt(ofile, pd->i_penalty[0]);
	pdbPutInt(ofile, pd->i_penalty[1]);
	pdbPutInt(ofile, pd->i_penalty[2]);
	pdbPutInt(ofile, pd->i_penalty[3]);
	pdbPutInt(ofile, pd->i_penalty[4]);

	pdbPutInt(ofile, pd->i_roundsUntil[0]);
	pdbPutInt(ofile, pd->i_roundsUntil[1]);
	pdbPutInt(ofile, pd->i_roundsUntil[2]);
	pdbPutInt(ofile, pd->i_roundsUntil[3]);
	pdbPutInt(ofile, pd->i_roundsUntil[4]);

	pdbPutInt(ofile, pd->i_armorClass[AC_NOPARRY]);

	for (i=0; i<MAX_D100XP; i++) { pdbPutInt(ofile, pd->c_d100XP[i]); }

	pdbPutInt(ofile, pd->i_armorClass[AC_NOPARRY]);
	pdbPutInt(ofile, pd->i_savingThrows[SAVE_POISON]);
	pdbPutInt(ofile, pd->i_savingThrows[SAVE_DISEASE]);
	pdbPutInt(ofile, pd->i_roundsUntil[ROUND_DEATH]);
	pdbPutInt(ofile, pd->i_roundsUntil[ROUND_SPELL_CHG]);
	pdbPutInt(ofile, pd->i_roundsUntil[ROUND_MISSILE_CHG]);
	pdbPutInt(ofile, pd->i_baseSpell);
	pdbPutInt(ofile, pd->i_directedSpells);

	pdbPutInt(ofile, pd->flags.f_ignoreBleed);
	pdbPutInt(ofile, pd->flags.f_ignoreStun);
	pdbPutInt(ofile, pd->i_noInGroup);

	return 0;
}

/********************************************************************************/
int writeAllPlayerData(char *fx) {
int i=0, w=0;
char of[256], wf[256];

	sprintf(of, "%s.pty", fx);
	sprintf(wf, "%s.pwp", fx);

	i = pdbClearFile(of); if (i != 0) { printf("Unlinking %s = %d:%d\n", of, i, errno); }
	i = pdbClearFile(wf); if (i != 0) { printf("Unlinking %s = %d:%d\n", wf, i, errno); }

	for (i=0; i<MAX_PLAYERS; i++) {
		if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
			pi_id = i;
			pdbAddRecord(of, writePlayerData, (void *)&players[i]); if (errno != 0) { printf("wPD: %d = %d\n", i, errno); }
			for (w=0; w<MAX_WEAPONS; w++) {
				if (players[i].w_weapons[w].c_description[0] != '\0' && players[i].w_weapons[w].c_damage[0] != '\0') {
					wi_id = w;
					pdbAddRecord(wf, writePlayerWeaponData, (void *)&players[i].w_weapons[w]); if (errno != 0) { printf("wAPD: %d = %d\n", i, errno); }
				}
			}
		}
	}

	return 0;
}

/********************************************************************************/
int writeAllMonsterData(char *fx) {
int i=0, w=0;
char of[256], wf[256];

	sprintf(of, "%s.mon", fx);
	sprintf(wf, "%s.mwp", fx);

	pdbClearFile(of);
	pdbClearFile(wf);

	for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
		if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
			pi_id = i;
			pdbAddRecord(of, writePlayerData, (void *)&players[i]);
			for (w=0; w<MAX_WEAPONS; w++) {
				if (players[i].w_weapons[w].c_description[0] != '\0' && players[i].w_weapons[w].c_damage[0] != '\0') {
					wi_id = w;
					pdbAddRecord(wf, writePlayerWeaponData, (void *)&players[i].w_weapons[w]);
				}
			}
		}
	}

	return 0;
}

/********************************************************************************/
void convertToVersion() {
int v = (int )config.f_version * 100;
//char *cp;

	if (v < 111) { v = 0; }

	switch (v) {
		case 112:
				  break;

		case 111:
				  break;

		case 0:		// move the datafiles to backup names
//				  	sprintf(mybuf1, "%s_", config.c_partyFilename); rename(config.c_partyFilename, mybuf1);
//				  	sprintf(mybuf1, "%s_", config.c_monstFilename); rename(config.c_monstFilename, mybuf1);
//					rename("qkmonst.dat", "qkmonst.dat_");

//				   if ((cp = strstr(config.c_partyFilename, ".")) != NULL) { *cp = '\0'; }
//				   if ((cp = strstr(config.c_monstFilename, ".")) != NULL) { *cp = '\0'; }
//					writeAllPlayerData(config.c_partyFilename);
//					writeAllMonsterData(config.c_monstFilename);
//					writeAllSRDMonsterData("srdmonster");

//					config.f_version = ADMPversion;
//					writeSystemData("system.sys");

					writeLog("");
					writeLog("*********** doing a version convert to 1.11");
					writeLog("");

				  	break;
	}
}

/********************************************************************************/
void readPlayerWeaponData() {
int i_dummy=0, i_wpos=0;
ADMPweapon *wp;
char *cp;

	wp = (ADMPweapon *)pdbDataPointer;
	pdbTokenize(pdbDataLine);

	i_dummy = pdbGetInt();
	i_wpos = pdbGetInt();
	wp->c_available = pdbGetInt();
	if ((cp = pdbGetString()) != NULL) { strcpy(&wp->c_description[0], cp); }
	wp->i_attackBonus[0] = pdbGetInt();
	wp->i_attackBonus[1] = pdbGetInt();
	wp->i_attackBonus[2] = pdbGetInt();
	wp->i_attackBonus[3] = pdbGetInt();
	if ((cp = pdbGetString()) != NULL) { strcpy(wp->c_damage, cp); }
	if ((cp = pdbGetString()) != NULL) { strcpy(wp->c_critical, cp); }
	wp->i_magicalBonus = pdbGetInt();
	wp->i_range = pdbGetInt();
	wp->i_reach = pdbGetInt();
	wp->i_noAttacks = pdbGetInt();
	if ((cp = pdbGetString()) != NULL) { strcpy(wp->c_message, cp); }
	wp->c_attackType = pdbGetInt();

	if ((cp = pdbGetString()) != NULL) { strcpy(wp->c_table, cp); }
	wp->i_doneAttacks = pdbGetInt();
	wp->i_size = pdbGetInt();
	wp->i_type = pdbGetInt();
	wp->i_fumble = pdbGetInt();
	wp->i_critAdjust = pdbGetInt();

// printf("%d %s\n", qkMonster, wp->c_description);
}

/********************************************************************************/
void readPlayerData() {
ADMPplayer *pd;
int i=0;
char *cp;

	pd = (ADMPplayer *)pdbDataPointer;

	pdbTokenize(pdbDataLine);


	i = pdbGetInt();
	if ((cp = pdbGetString()) != NULL) { strcpy(pd->c_name, cp); }
//printf("rPD: %s\n", pd->c_name);
	pd->i_race = pdbGetInt();
	pd->i_alignment = pdbGetInt();
	pd->i_classes[0] = pdbGetInt();
	pd->i_classes[1] = pdbGetInt();
	pd->i_classes[2] = pdbGetInt();
	pd->i_classes[3] = pdbGetInt();
	pd->i_levels[0] = pdbGetInt();
	pd->i_levels[1] = pdbGetInt();
	pd->i_levels[2] = pdbGetInt();
	pd->i_levels[3] = pdbGetInt();
	pd->i_hp[HP_MAX] = pdbGetInt();
	pd->i_hp[HP_CUR] = pdbGetInt();
	pd->i_hp[HP_NL] = pdbGetInt();
	pd->i_hp[HP_TMP] = pdbGetInt();
	pd->i_bleeding = pdbGetInt();
	pd->i_disabledAt = pdbGetInt();
	pd->i_unconciousAt = pdbGetInt();
	pd->i_savingThrows[SAVE_FORTITUDE] = pdbGetInt();
	pd->i_savingThrows[SAVE_REFLEX] = pdbGetInt();
	pd->i_savingThrows[SAVE_WISDOM] = pdbGetInt();
	pd->i_armorClass[AC_NORMAL] = pdbGetInt();
	pd->i_armorClass[AC_TOUCH] = pdbGetInt();
	pd->i_armorClass[AC_FLATFOOTED] = pdbGetInt();
	pd->i_armorClassSplit[AC_SECTION_DEX] = pdbGetInt();
	pd->i_armorClassSplit[AC_SECTION_SIZE] = pdbGetInt();
	pd->i_armorClassSplit[AC_SECTION_DEFLECTION] = pdbGetInt();
	pd->i_armorClassSplit[AC_SECTION_NATURAL] = pdbGetInt();
	pd->i_armorClassSplit[AC_SECTION_ARMOR] = pdbGetInt();
	pd->i_armorClassSplit[AC_SECTION_SHIELD] = pdbGetInt();
	pd->i_bab[BAB_MELEE][0] = pdbGetInt();
	pd->i_bab[BAB_RANGED][0] = pdbGetInt();
	pd->i_bab[BAB_GRAPPLE][0] = pdbGetInt();
	pd->i_bab[BAB_MELEE][1] = pdbGetInt();
	pd->i_bab[BAB_RANGED][1] = pdbGetInt();
	pd->i_bab[BAB_GRAPPLE][1] = pdbGetInt();
	pd->i_bab[BAB_MELEE][2] = pdbGetInt();
	pd->i_bab[BAB_RANGED][2] = pdbGetInt();
	pd->i_bab[BAB_GRAPPLE][2] = pdbGetInt();
	pd->i_initiative[0] = pdbGetInt();
	pd->i_initiative[1] = pdbGetInt();
	pd->i_speed = pdbGetInt();
	pd->i_inactive = pdbGetInt();
	pd->i_stun = pdbGetInt();
	pd->i_noAttacks = pdbGetInt();
	pd->f_challengeRating = pdbGetFloat();
	pd->i_d20Rolls[0] = pdbGetInt();
	pd->i_d20Rolls[1] = pdbGetInt();
	pd->i_d20Rolls[2] = pdbGetInt();
	pd->i_d20Rolls[3] = pdbGetInt();
	pd->i_d20Rolls[4] = pdbGetInt();
	pd->i_d20Rolls[5] = pdbGetInt();
	pd->i_d20Rolls[6] = pdbGetInt();
	pd->i_spellDC[0] = pdbGetInt();
	pd->i_spellDC[1] = pdbGetInt();
	pd->i_spellDC[2] = pdbGetInt();
	pd->i_spellDC[3] = pdbGetInt();
	pd->i_spellDC[4] = pdbGetInt();
	pd->i_spellDC[5] = pdbGetInt();
	pd->i_spellDC[6] = pdbGetInt();
	pd->i_spellFailure = pdbGetInt();
	pd->i_abilityStats[0][0] = pdbGetInt();
	pd->i_abilityStats[1][0] = pdbGetInt();
	pd->i_abilityStats[0][1] = pdbGetInt();
	pd->i_abilityStats[1][1] = pdbGetInt();
	pd->i_abilityStats[0][2] = pdbGetInt();
	pd->i_abilityStats[1][2] = pdbGetInt();
	pd->i_abilityStats[0][3] = pdbGetInt();
	pd->i_abilityStats[1][3] = pdbGetInt();
	pd->i_abilityStats[0][4] = pdbGetInt();
	pd->i_abilityStats[1][4] = pdbGetInt();
	pd->i_abilityStats[0][5] = pdbGetInt();
	pd->i_abilityStats[1][5] = pdbGetInt();
	pd->i_skills[SKILL_SEARCH] = pdbGetInt();
	pd->i_skills[SKILL_SOH] = pdbGetInt();
	pd->i_skills[SKILL_SPOT] = pdbGetInt();
	pd->i_skills[SKILL_OPENLOCKS] = pdbGetInt();
	pd->i_skills[SKILL_MOVESILENTLY] = pdbGetInt();
	pd->i_skills[SKILL_LISTEN] = pdbGetInt();
	pd->i_skills[SKILL_HIDE] = pdbGetInt();
	pd->i_skills[SKILL_CONCENTRATION] = pdbGetInt();
	pd->i_spellResistance = pdbGetInt();
	pd->i_damageReduction[0] = pdbGetInt();
	pd->i_damageReduction[1] = pdbGetInt();
	pd->i_damageReduction[2] = pdbGetInt();
	pd->i_size = pdbGetInt();
	pd->i_xp[MAX] = pdbGetInt();
	pd->i_xp[TMP] = pdbGetInt();
	pd->i_inGroup = pdbGetInt();
	if ((cp = pdbGetString()) != NULL) { strcpy(pd->c_hitDice, cp); }
	pd->flags.f_isStabilised = pdbGetInt();
	pd->flags.f_disabled = pdbGetInt();
	pd->flags.f_ignoreCriticals = pdbGetInt();
	pd->flags.f_autoStablise = pdbGetInt();
	pd->flags.f_evasion = pdbGetInt();
	
	pd->spellsAvailable.i_maxLevel0 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel1 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel2 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel3 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel4 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel5 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel6 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel7 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel8 = pdbGetInt();
	pd->spellsAvailable.i_maxLevel9 = pdbGetInt();
	pd->spellsAvailable.i_curLevel0 = pdbGetInt();
	pd->spellsAvailable.i_curLevel1 = pdbGetInt();
	pd->spellsAvailable.i_curLevel2 = pdbGetInt();
	pd->spellsAvailable.i_curLevel3 = pdbGetInt();
	pd->spellsAvailable.i_curLevel4 = pdbGetInt();
	pd->spellsAvailable.i_curLevel5 = pdbGetInt();
	pd->spellsAvailable.i_curLevel6 = pdbGetInt();
	pd->spellsAvailable.i_curLevel7 = pdbGetInt();
	pd->spellsAvailable.i_curLevel8 = pdbGetInt();
	pd->spellsAvailable.i_curLevel9 = pdbGetInt();

	pd->i_playerID = pdbGetInt();
	pd->i_stdMonsterID = pdbGetInt();
	if (i_monsterType < 1) {
		pd->i_stdMonsterID = qkMonster;
	}
	pd->flags.f_npc = pdbGetInt();
	pd->i_regeneration = pdbGetInt();

	cp = pdbGetString();
	if (cp != NULL) {
		strcpy(pd->c_iconFile, cp);
		pd->i_inGroup = pdbGetInt();
		pd->i_mapX = pdbGetInt();
		pd->i_mapY = pdbGetInt();
		pd->i_reach = pdbGetInt();
		pd->i_space = pdbGetInt();
	} else {
		pd->i_inGroup = pd->i_mapX = pd->i_mapY = -1;
		pd->i_reach = 5;
		pd->i_space = 5;
	}
	pd->flags.f_invisible = pdbGetInt();

	pd->i_resistances[RESIST_FIRE] = pdbGetInt();
	pd->i_resistancesUsed[RESIST_FIRE] = pdbGetInt();
	pd->i_resistances[RESIST_ACID] = pdbGetInt();
	pd->i_resistancesUsed[RESIST_ACID] = pdbGetInt();
	pd->i_resistances[RESIST_COLD] = pdbGetInt();
	pd->i_resistancesUsed[RESIST_COLD] = pdbGetInt();
	pd->i_resistances[RESIST_ELEC] = pdbGetInt();
	pd->i_resistancesUsed[RESIST_ELEC] = pdbGetInt();
	pd->i_resistances[RESIST_SONIC] = pdbGetInt();
	pd->i_resistancesUsed[RESIST_SONIC] = pdbGetInt();

	if ((cp = pdbGetString()) != NULL) { strncpy(pd->c_items, cp, 189); pd->c_items[189] = '\0'; }

//	if (pd->i_regeneration > 0) { printf("%s = %d\n", pd->c_name, pd->i_regeneration); }

	pd->i_negateCrit = pdbGetInt();
	pd->i_armorClassSplit[AC_SECTION_DODGE] = pdbGetInt();
	pd->i_useShieldOn = pdbGetInt();
	pd->i_useDodgeOn = pdbGetInt();

	pd->flags.f_wasViewed = pdbGetInt();

	pd->i_spellDC[7] = pdbGetInt();
	pd->i_spellDC[8] = pdbGetInt();
	pd->i_hp[HP_ENH] = pdbGetInt();
	pd->i_doneAttacks = pdbGetInt();

	pd->i_savingThrows[SAVE_MENTAL] = pdbGetInt();
	pd->i_savingThrows[SAVE_DISEASE] = pdbGetInt();
	pd->i_penalty[0] = pdbGetInt();
	pd->i_penalty[1] = pdbGetInt();
	pd->i_penalty[2] = pdbGetInt();
	pd->i_penalty[3] = pdbGetInt();
	pd->i_penalty[4] = pdbGetInt();

	pd->i_roundsUntil[0] = pdbGetInt();
	pd->i_roundsUntil[1] = pdbGetInt();
	pd->i_roundsUntil[2] = pdbGetInt();
	pd->i_roundsUntil[3] = pdbGetInt();
	pd->i_roundsUntil[4] = pdbGetInt();

	pd->i_armorClass[AC_NOPARRY] = pdbGetInt();

	for (i=0; i<MAX_D100XP; i++) { pd->c_d100XP[i] = pdbGetInt(); }
	pd->i_armorClass[AC_NOPARRY] = pdbGetInt();
	pd->i_savingThrows[SAVE_POISON] = pdbGetInt();
	pd->i_savingThrows[SAVE_DISEASE] = pdbGetInt();
	pd->i_roundsUntil[ROUND_DEATH] = pdbGetInt();
	pd->i_roundsUntil[ROUND_SPELL_CHG] = pdbGetInt();
	pd->i_roundsUntil[ROUND_MISSILE_CHG] = pdbGetInt();
	pd->i_baseSpell = pdbGetInt();
	pd->i_directedSpells = pdbGetInt();

	pd->flags.f_ignoreBleed = pdbGetInt();
	pd->flags.f_ignoreStun = pdbGetInt();

	pd->i_noInGroup = pdbGetInt();
}

/********************************************************************************/
int readAllPlayerData(char *fx) {
int i=0, w=0;
char of[256], wf[256];
char key1[10], key2[10];

	sprintf(of, "%s.pty", fx);
	sprintf(wf, "%s.pwp", fx);

	for (i=0; i<MAX_PLAYERS; i++) {
		sprintf(key1, "%d", i);
		pdbKeySearch(of, readPlayerData, (void *)&players[i], 1, key1, NULL, NULL);
		for (w=0; w<MAX_WEAPONS; w++) {
			sprintf(key2, "%d", w);
			pdbKeySearch(wf, readPlayerWeaponData, (void *)&players[i].w_weapons[w], 1, key1, key2, NULL);
		}
	}

	return 0;
}

/********************************************************************************/
int readAllMonsterData(char *fx, ADMPplayer *p) {
int i=0, w=0;
char of[256], wf[256];
char key1[10], key2[10];

	sprintf(of, "%s.mon", fx);
	sprintf(wf, "%s.mwp", fx);

	for (i=0; i<MAX_MONSTERS; i++) {
		sprintf(key1, "%d", i+MAX_PLAYERS);
		pdbKeySearch(of, readPlayerData, (void *)&p[i], 1, key1, NULL, NULL);
		for (w=0; w<MAX_WEAPONS; w++) {
			sprintf(key2, "%d", w);
			pdbKeySearch(wf, readPlayerWeaponData, (void *)&p[i].w_weapons[w], 1, key1, key2, NULL);
		}
	}

	return 0;
}

/********************************************************************************/
int readQKMonsterData() {
	qkMonster++;
	pdbDataPointer = (void *)&qkmonsters[qkMonster];
	readPlayerData();
	qkmonsters[qkMonster].flags.f_srdMonster = i_monsterType;
	qkmonsters[qkMonster].i_stdMonsterID = (qkMonster - i_monsterCount) + i_monsterType;
//printf("loaded: %s (%d/%d)\n", qkmonsters[qkMonster].c_name, qkMonster, qkmonsters[qkMonster].i_stdMonsterID);

	return 0;
}

/********************************************************************************/
void readQKMonstWeaponData() {
	pdbDataPointer = (void *)&qkmonsters[qkMonster].w_weapons[qkMonsterWeapon];
	readPlayerWeaponData();
	qkMonsterWeapon++;
}

/********************************************************************************/
int readAllStdMonsterData(char *fx) {
char of[256], wf[256];
char key1[10];

	sprintf(of, "%s.std", fx);
	sprintf(wf, "%s.swp", fx);

	pdbLoadAll(of, readQKMonsterData);
	if (i_monsterType == 0) { i_monsterCount = qkMonster; }
//printf("i_monsterCount = %d\n", i_monsterCount);

	for (int i=0; i<MAX_QKMONSTERS; i++) {
		if (qkmonsters[i].c_name[0] != '\0') {
			if (i_monsterType == 0) { qkMonster = i; } else { qkMonster = i_monsterCount + i; }
			sprintf(key1, "%d", i);
			qkMonsterWeapon = 0;
			pdbKeySearch(wf, readQKMonstWeaponData, (void *)&qkmonsters[qkMonster].w_weapons[0], MAX_WEAPONS, key1, NULL, NULL);
		}
	}

	return 0;
}

/********************************************************************************/
int writeAllSRDMonsterData(char *fx) {
int i=0, w=0, r=0;
char of[256], wf[256];

	sprintf(of, "%s.std", fx);
	sprintf(wf, "%s.swp", fx);

	pdbClearFile(of);
	pdbClearFile(wf);

	for (i=0; i<MAX_QKMONSTERS; i++) {
		if (qkmonsters[i].c_name[0] != '\0' && qkmonsters[i].i_hp[HP_MAX] > 0 && qkmonsters[i].flags.f_srdMonster == 0) {
			pi_id = i;
			r = pdbAddRecord(of, writePlayerData, (void *)&qkmonsters[i]);
			for (w=0; w<MAX_WEAPONS; w++) {
				if (qkmonsters[i].w_weapons[w].c_description[0] != '\0' && qkmonsters[i].w_weapons[w].c_damage[0] != '\0') {
					wi_id = w;
					r = pdbAddRecord(wf, writePlayerWeaponData, (void *)&qkmonsters[i].w_weapons[w]);
				}
			}
		}
	}

	return 0;
}

/********************************************************************************/
int writeAllStdMonsterData(char *fx) {
int i=0, w=0, r=0, j=0;
char of[256], wf[256];

	sprintf(of, "%s.std", fx);
	sprintf(wf, "%s.swp", fx);

	pdbClearFile(of);
	pdbClearFile(wf);

	j=0;

	for (i=0; i<MAX_QKMONSTERS; i++) {
		if (qkmonsters[i].c_name[0] != '\0' && qkmonsters[i].i_hp[HP_MAX] > 0 && qkmonsters[i].flags.f_srdMonster != 0) {
			qkmonsters[i].i_stdMonsterID = pi_id = j++;
			r = pdbAddRecord(of, writePlayerData, (void *)&qkmonsters[i]);
			for (w=0; w<MAX_WEAPONS; w++) {
				if (qkmonsters[i].w_weapons[w].c_description[0] != '\0' && qkmonsters[i].w_weapons[w].c_damage[0] != '\0') {
					wi_id = w;
					r = pdbAddRecord(wf, writePlayerWeaponData, (void *)&qkmonsters[i].w_weapons[w]);
				}
			}
		}
	}


	return 0;
}

/********************************************************************************/
void loadMonsterDescription(char *name) {
char fname[256], tname[64], *words[3] = {NULL, NULL, NULL};
int i=4;
FILE *ifile;

	while (name[i] != '\0') {
		tname[i-4] = toupper(name[i]);
		if (tname[i-4] == ' ') { tname[i-4] = '_'; }
		i++;
	}

	tname[i-4] = '\0';
	sprintf(fname, "srd/monsters/%s.html", tname);

	if ((ifile = fopen(fname, "r")) != NULL) {
		fclose(ifile);
		a_CTMonsterHTMLDetails->load(fname);
		return;
	} else {
		if ((words[1] = strstr(tname, "_")) != NULL) {
			*words[1] = '\0'; words[1]++;
			if ((words[2] = strstr(words[1], "_")) != NULL) {
				*words[2] = '\0'; words[2]++;
			}
			sprintf(fname, "srd/monsters/%s.html", tname);
			if ((ifile = fopen(fname, "r")) != NULL) {
				fclose(ifile);
				a_CTMonsterHTMLDetails->load(fname);
				return;
			} else {
				sprintf(fname, "srd/monsters/%s_%s.html", tname, words[1]);
				if ((ifile = fopen(fname, "r")) != NULL) {
					fclose(ifile);
					a_CTMonsterHTMLDetails->load(fname);
					return;
				} else {
					sprintf(fname, "srd/monsters/%s.html", words[1]);
					if ((ifile = fopen(fname, "r")) != NULL) {
						fclose(ifile);
						a_CTMonsterHTMLDetails->load(fname);
						return;
					}
				}
			}
		}
	}
	a_CTMonsterHTMLDetails->load("");
}

/********************************************************************************/
int myalphasort(const void *a, const void *b) {
#ifndef VISUALC
	return (strcasecmp((*(const struct dirent **) a)->d_name, (*(const struct dirent **) b)->d_name));
#else
	return (strcmpi((*(const struct dirent **) a)->d_name, (*(const struct dirent **) b)->d_name));
#endif
}

/********************************************************************************/
void loadSRDspellEntries(char *dir) {
int num_entries=0, i=0, j=0;
char *cp, *cp1;
struct dirent **list;

	for (i=0; i<128; i++) { i_spellEntries[i] = -1; }
	a_CTSpellDetailsList->clear();
	a_SLSpellSearchList->clear();

	num_entries = fl_filename_list(dir, &list, fl_casealphasort);
	if (num_entries < 3) { return; }
	list++; list++;
	for (i=2; i<num_entries; i++) {
		cp = (*list)->d_name;
			// remove the .html extension
		if ((cp1 = strstr(cp, ".")) != NULL) { *cp1 = '\0'; }
		j = tolower(cp[0]) - 'a';
		if (i_spellEntries[j] == -1) { i_spellEntries[j] = i; } //printf("lSSE: %d (%c) = %d\n", j, cp[0], i); }
		a_CTSpellDetailsList->add(cp);
		a_SLSpellSearchList->add(cp);
		list++;
	}
}

/********************************************************************************/
void showSRDspellEntries(int scrn) {
int i=0, j, k;

	if (scrn == 0) {
		strcpy(mybuf2, a_CTSpellDetailsSearch->value());
	} else {
		strcpy(mybuf2, a_SLSpellSearch->value());
	}
	i = tolower(mybuf2[0]) - 'a';
	k = strlen(mybuf2);

	if (i < 0 || i > 100) { return; }
	if (i_spellEntries[i] < 0) { return; }

	if (strlen(mybuf2) > 1) {
		if (scrn == 0) { a_CTSpellDetailsList->topline(i_spellEntries[i]); } else { a_SLSpellSearchList->topline(i_spellEntries[i]); }
		i = i_spellEntries[i];
		for (j=0; j < 100; j++) {
			if (scrn == 0) {
				if ((i+j) > a_CTSpellDetailsList->size()) { return; }
				if (strncasecmp(a_CTSpellDetailsList->text(i+j), mybuf2, k) == 0) {
					a_CTSpellDetailsList->topline(i+j);
					return;
				}
			} else {
				if ((i+j) > a_SLSpellSearchList->size()) { return; }
				if (strncasecmp(a_SLSpellSearchList->text(i+j), mybuf2, k) == 0) {
					a_SLSpellSearchList->topline(i+j);
					return;
				}
			}
		}
	} else {
		if (scrn == 0) { a_CTSpellDetailsList->topline(i_spellEntries[i]); } else { a_SLSpellSearchList->topline(i_spellEntries[i]); }
	}
}

/********************************************************************************/
void selectSRDspellEntries(int scrn) {
	if (scrn == 0) {
		sprintf(mybuf2, "srd/spells/%s.html", a_CTSpellDetailsList->text(a_CTSpellDetailsList->value()));
		a_CTSpellHTMLDetails->load(mybuf2);
	} else {
		sprintf(mybuf2, "srd/spells/%s.html", a_SLSpellSearchList->text(a_SLSpellSearchList->value()));
		a_SLSpellSearchDetails->load(mybuf2);
	}
}

/********************************************************************************/
int readAllStdWeaponData() {
char key1[10];
weapon_tab *wtbl;
int i=0;

	switch (config.i_diceSystem) {
		case 0:		// d20
				for (i=0; i<MAX_STDWEAPONS; i++) {
					sprintf(key1, "%d", i);
					pdbKeySearch("stdweapon.wpd", readPlayerWeaponData, (void *)&stdweapons[i], 1, key1, NULL, NULL);
				}
				break;

		case 1:		// MERP
		case 2:		// RMS
				if ((wtbl = (weapon_tab *)getD100Table("WE")) != NULL) {
					for (i=0; i<MAX_D100WEAPONS; i++) {
						if (wtbl->wp_ob != 5) {				// not spells
							strcpy(stdweapons[i].c_description, wtbl->wp_dsc);
							stdweapons[i].i_fumble = wtbl->wp_fm;
							stdweapons[i].i_critAdjust = wtbl->wp_ca;
							stdweapons[i].i_range = wtbl->wp_br;
							strcpy(stdweapons[i].c_damage, wtbl->wp_pc);
							strcpy(stdweapons[i].c_critical, wtbl->wp_sc);
							strcpy(stdweapons[i].c_message, wtbl->wp_sm);
							strcpy(stdweapons[i].c_table, wtbl->wp_tbl);
						}
						wtbl++;
					}
				}
				break;
	}

	return 0;
}

/********************************************************************************/
void qkMonsterAdd(int action) {
ADMPplayer plyrs;
int pid=0, ok=0, i=0, j=0;

	switch (action) {
			// show it
		case 0:  
					aQkAdd_Name->value("");
					aQkAdd_Count->value(1);
					aQkAdd_HPMax->value("");
					aQkAdd_ACNormal->value("");
					aQkAdd_ACTouch->value("");
					aQkAdd_ACFlatFoot->value("");
					aQkAdd_InitBonus->value("");
					aQkAdd_Speed->value("");
					aQkAdd_SaveFort->value("");
					aQkAdd_SaveReflex->value("");
					aQkAdd_SaveWill->value("");
					aQkAdd_NoAttacks->value("1");
					aQkAdd_CRating->value("");
					aQkAdd_SpellResistance->value("");
					aQkAdd_DamReductionHP->value("");
					aQkAdd_DamReductionWeapon->value("");
					aQkAdd_DamReductionType->value(0);
					aQkAdd_Regeneration->value("");
					aQkAdd_Icon->value("");
					aQkAdd_ResistFire->value("");
					aQkAdd_ResistAcid->value("");
					aQkAdd_ResistCold->value("");
					aQkAdd_ResistElec->value("");
					aQkAdd_ResistSonic->value("");
					aQkAdd_NoInGroup->value("");

					aQkAdd_WeaponSelector->clear();

					for (i=1; i<7; i++) {
						sprintf(mybuf1, "Empty Weapon Slot #%d", i);
						aQkAdd_WeaponSelector->add(mybuf1);
					}
               aQkAdd_WeaponName->value("");
//               aQkAdd_WeaponSearch->value("");
               aQkAdd_WeaponAttkBonus1->value("");
               aQkAdd_WeaponAttkBonus2->value("");
               aQkAdd_WeaponAttkBonus3->value("");
               aQkAdd_WeaponAttkBonus4->value("");
               aQkAdd_WeaponDamage->value("");
               aQkAdd_WeaponCritical->value("");
               aQkAdd_WeaponMagicBonus->value("");
               aQkAdd_WeaponRange->value("");
               aQkAdd_WeaponReach->value("");
               aQkAdd_WeaponNoAttacks->value("");
               aQkAdd_WeaponSpecialMessage->value("");

					memset(&players[MAX_MEMBERS+3].w_weapons[0].c_available, '\0', sizeof(ADMPweapon) * MAX_ATTACKS);
					config.i_editID = MAX_MEMBERS+3;
					i_prevWeaponEditted = -1;
				  	a_QkMonsterAdd->show();
					break;

		case 1:  // accept
					selectQkAddEditWeapon(aQkAdd_WeaponSelector->value()-1);		// save current weapon details
					a_QkMonsterAdd->hide();
					memset(plyrs.c_name, '\0', sizeof(ADMPplayer));
					sprintf(mybuf1, "Z - %s", aQkAdd_Name->value());
					mybuf1[29] = '\0'; strcpy(plyrs.c_name, mybuf1);
					plyrs.i_hp[HP_CUR] = plyrs.i_hp[HP_MAX] = atoi(aQkAdd_HPMax->value());
					if (plyrs.c_name[4] == '\0' && plyrs.i_hp[HP_MAX] == 0) { return; }
					plyrs.i_savingThrows[SAVE_FORTITUDE] = atoi(aQkAdd_SaveFort->value());
					plyrs.i_savingThrows[SAVE_REFLEX] = atoi(aQkAdd_SaveReflex->value());
					plyrs.i_savingThrows[SAVE_WISDOM] = atoi(aQkAdd_SaveWill->value());
					plyrs.i_armorClass[AC_NORMAL] = atoi(aQkAdd_ACNormal->value());
					plyrs.i_armorClass[AC_TOUCH] = atoi(aQkAdd_ACTouch->value());
					plyrs.i_armorClass[AC_FLATFOOTED] = atoi(aQkAdd_ACFlatFoot->value());
					plyrs.i_initiative[0] = atoi(aQkAdd_InitBonus->value());
					plyrs.i_speed = atoi(aQkAdd_Speed->value());
					plyrs.i_noAttacks = atoi(aQkAdd_NoAttacks->value());
				
					plyrs.f_challengeRating = (float )atof(aQkAdd_CRating->value());
					plyrs.i_spellResistance = atoi(aQkAdd_SpellResistance->value());
					plyrs.i_damageReduction[0] = aQkAdd_DamReductionType->value();
					plyrs.i_damageReduction[1] = atoi(aQkAdd_DamReductionHP->value());
					plyrs.i_damageReduction[2] = atoi(aQkAdd_DamReductionWeapon->value());

					plyrs.i_resistances[RESIST_FIRE] = atoi(aQkAdd_ResistFire->value());
					plyrs.i_resistances[RESIST_ACID] = atoi(aQkAdd_ResistAcid->value());
					plyrs.i_resistances[RESIST_COLD] = atoi(aQkAdd_ResistCold->value());
					plyrs.i_resistances[RESIST_ELEC] = atoi(aQkAdd_ResistElec->value());
					plyrs.i_resistances[RESIST_SONIC] = atoi(aQkAdd_ResistSonic->value());

					plyrs.i_noInGroup = atoi(aQkAdd_NoInGroup->value());

					strcpy(plyrs.c_iconFile, aQkAdd_Icon->value());

					memcpy(&plyrs.w_weapons[0].c_available, &players[MAX_MEMBERS+3].w_weapons[0].c_available, sizeof(ADMPweapon) * MAX_ATTACKS);

					plyrs.i_unconciousAt = -1;
					plyrs.flags.f_disabled = 0;
					for (j=0; j<MAX_D20ROLLS; j++) {
						if (config.i_diceSystem == DICE_D20) {
							plyrs.i_d20Rolls[j] = getRND(20);
						} else {
							plyrs.i_d20Rolls[j] = getRND(100);
						}
						plyrs.i_whomAttacked[j][0] = -1;
		 			}
		 			plyrs.i_whomAttacked[0][0] = plyrs.i_whomAttacked[1][0] = plyrs.i_whomAttacked[2][0] = -1;
					plyrs.i_mapX = plyrs.i_mapY = plyrs.i_inGroup = -1;
					plyrs.i_regeneration = atoi(aQkAdd_Regeneration->value());
				
					reloadNames(0);
				
					if (config.flags.f_debug != 0) printf("Saving %d\n", pid);
				
					// do some quick sanity checks
					if (a_EORMessageList == NULL) { doEndOfRoundMessages(0); }
					a_EORMessageList->clear();
					a_EORMessageList->add("");
					a_EORMessageList->add("@B63@.The following are possible problems with this monster");
					a_EORMessageList->add("");
					if (plyrs.i_hp[HP_MAX] == 0 || plyrs.i_hp[HP_CUR] == 0) { ok = 1; a_EORMessageList->add("  HP's are zero"); }
					if (plyrs.i_armorClass[AC_NORMAL] == 0) { ok = 1; a_EORMessageList->add("  A/C is zero"); }
					if (plyrs.i_savingThrows[SAVE_FORTITUDE] == 0 && plyrs.i_savingThrows[SAVE_REFLEX] == 0 && plyrs.i_savingThrows[SAVE_WISDOM] == 0) { ok = 1; a_EORMessageList->add("  Saving Throws have issues"); }
					if (plyrs.i_noAttacks == 0) { ok = 1; a_EORMessageList->add("  #Attks is zero"); }
					if (plyrs.w_weapons[0].i_attackBonus[0] == 0 && plyrs.w_weapons[1].i_attackBonus[0] == 0) { ok = 1; a_EORMessageList->add("  Weapon BAB's dont seem to be set"); }
					if (plyrs.f_challengeRating == 0 && pid >= MAX_PLAYERS) { ok = 1; a_EORMessageList->add("  CR value is zero"); }
				
					if (ok == 1) {
						doEndOfRoundMessages(0);
					}
					j = (int )aQkAdd_Count->value();
					for (; j>0; j--) {
						for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] == '\0' && players[i].i_hp[HP_MAX] == 0) {
								memcpy(&players[i].c_name[0], &plyrs.c_name[0], sizeof(ADMPplayer));
								players[i].c_name[0] = identifiers[i];
								if (strlen(plyrs.c_iconFile) > 0) {
									if (playerIcons[i] != NULL) { delete playerIcons[i]; }
									if (mystrcasestr(plyrs.c_iconFile, "png") != NULL) {
										playerIcons[i] = new Fl_PNG_Image(plyrs.c_iconFile);
									} else {
										playerIcons[i] = new Fl_JPEG_Image(plyrs.c_iconFile);
									}
									combatGridMap->setPlayerIcon(i, playerIcons[i]);
								}
								break;
							}
						}
					}
					reloadNames(0);
					break;

			// cancel
		case 2:  a_QkMonsterAdd->hide();
					break;
	}
}

/********************************************************************************/
int writeSystemData(char *fn) {
FILE *ofile;
int i=0,j=0;

	if ((ofile = fopen(fn, "w+")) == NULL) {
		return -1;
	}

	if (ADMPversion > 1.40) {
		fprintf(ofile, "A %f %d %d %d %d %d %d %d %d\n", config.f_version, config.i_roundCount, config.i_whenBleed, config.i_editID, config.i_actionInitID, config.i_actionRecvID, config.i_actionSelected, config.i_actionWeaponSelected, config.i_roundsSave);
		fprintf(ofile, "B %s\n", config.c_partyFilename);
		fprintf(ofile, "C %s\n", config.c_monstFilename);
		fprintf(ofile, "D %s\n", config.c_mapFilename);
		fprintf(ofile, "R %d %d\n", (int )aSys_ScreenWidth->value(), (int )aSys_ScreenHeight->value());
		fprintf(ofile, "G %d %d\n", config.i_diceSystem, config.i_initSystem);
		fprintf(ofile, "E"); 
		i=MAX_MEMBERS; fprintf(ofile, " %d", i); i=MAX_IDLIST; fprintf(ofile, " %d", i);
		i=MAX_MODIFIERS; fprintf(ofile, " %d", i); i=MAX_TRIGGERS; fprintf(ofile, " %d", i);
		i=MAX_AUTODAMAGE; fprintf(ofile, " %d\n", i); 
		fprintf(ofile, "F %d %d %d %d %d %d %d %d %d %d %d %d\n", config.flags.f_debug, config.flags.f_rollAllRolls, config.flags.f_rollInitRolls, config.flags.f_logfile, config.flags.f_rollInitEveryRnd, config.flags.f_removeMonstersInit, config.flags.f_oneMissTwentyHits, config.flags.f_fogOfWar, config.flags.f_defaultDefender, config.flags.f_askBeforeMoving, config.flags.f_showDeadMonsters, config.flags.f_deathAtCON);

		for (i=0; i<MAX_IDLIST; i++) {
			fprintf(ofile, "I");
			for (j=0; j<MAX_MEMBERS+2; j++) {
				fprintf(ofile, " %d", config.i_idList[i][j]);
			}
			fprintf(ofile, "\n");
		}

		for (i=0; i<MAX_MODIFIERS; i++) {
			fprintf(ofile, "S %s|%d|%d", config.system_mods[i].c_message, config.system_mods[i].i_idFollows, config.system_mods[i].i_noRounds);
			for (j=0; j<MAX_MEMBERS; j++) { fprintf(ofile, "|%d", config.system_mods[i].i_whom[j]); }
			for (j=0; j<5; j++) { 
				fprintf(ofile, "|%d|%d|%d", config.system_mods[i].i_data[j][0], config.system_mods[i].i_data[j][1], config.system_mods[i].i_data[j][2]);
			}
			fprintf(ofile, "|\n");
		}

		for (i=0; i<MAX_MODIFIERS; i++) {
			fprintf(ofile, "M %s|%d|%d", config.action_mods[i].c_message, config.action_mods[i].i_idFollows, config.action_mods[i].i_noRounds);
			for (j=0; j<MAX_MEMBERS; j++) { fprintf(ofile, "|%d", config.action_mods[i].i_whom[j]); }
			for (j=0; j<5; j++) { 
				fprintf(ofile, "|%d|%d|%d", config.action_mods[i].i_data[j][0], config.action_mods[i].i_data[j][1], config.action_mods[i].i_data[j][2]);
			}
			fprintf(ofile, "|\n");
		}

		for (i=0; i<MAX_TRIGGERS; i++) {
			fprintf(ofile, "T %s|%d|%d|%s|\n", config.action_msgs[i].c_message, config.action_msgs[i].i_noRounds, config.action_msgs[i].i_display, config.action_msgs[i].c_every);
		}
		for (i=0; i<MAX_AUTODAMAGE; i++) {
			fprintf(ofile, "U %s|%d|%s|%d|%d|%d", config.auto_damage[i].c_description, config.auto_damage[i].i_initiatorID, config.auto_damage[i].c_damage, config.auto_damage[i].i_noRounds, config.auto_damage[i].i_doneRounds, config.auto_damage[i].i_type);
			for (j=0; j<MAX_MEMBERS; j++) { fprintf(ofile, "|%d", config.auto_damage[i].i_whom[j]); }
			fprintf(ofile, "|%d|%d|%d|%d|%d|%d|%d|%d|0|0|\n", config.auto_damage[i].flags.f_flag1, config.auto_damage[i].flags.f_flag2, config.auto_damage[i].flags.f_flag3, config.auto_damage[i].flags.f_flag4, config.auto_damage[i].flags.f_flag5, config.auto_damage[i].flags.f_flag6, config.auto_damage[i].flags.f_flag7, config.auto_damage[i].flags.f_flag8);
		}
		for (i=0; i<MAX_MEMBERS; i++) {
			if (config.quickmods[i].i_id != -1) {
				fprintf(ofile, "Q %d|%d|%d|%d|%d|%d|%d|%d|%d|\n", config.quickmods[i].i_id, config.quickmods[i].i_effects[0][1], config.quickmods[i].i_effects[1][1], config.quickmods[i].i_effects[2][1], config.quickmods[i].i_effects[3][1], config.quickmods[i].i_effects[4][1], config.quickmods[i].i_effects[5][1], config.quickmods[i].i_effects[6][1], config.quickmods[i].i_effects[7][1]);
			}
		}
	} else {
		pdbFilePointer = ofile; 
	
		fprintf(ofile, "0|");
	
		pdbPutFloat(ofile, config.f_version);
		pdbPutInt(ofile, config.i_roundCount);
		pdbPutInt(ofile, config.i_whenBleed);
		pdbPutInt(ofile, config.i_editID);
		pdbPutInt(ofile, config.i_actionInitID);
		pdbPutInt(ofile, config.i_actionRecvID);
		pdbPutInt(ofile, config.i_actionSelected);
		pdbPutInt(ofile, config.i_actionWeaponSelected);
		pdbPutInt(ofile, config.i_roundsSave);
		pdbPutString(ofile, config.c_partyFilename);
		pdbPutString(ofile, config.c_monstFilename);
		pdbPutInt(ofile, config.flags.f_debug);
		pdbPutInt(ofile, config.flags.f_rollAllRolls);
		pdbPutInt(ofile, config.flags.f_rollInitRolls);
		pdbPutInt(ofile, config.flags.f_logfile);
		pdbPutInt(ofile, config.flags.f_rollInitEveryRnd);
		pdbPutInt(ofile, config.flags.f_removeMonstersInit);
		pdbPutInt(ofile, config.flags.f_oneMissTwentyHits);
		pdbPutString(ofile, config.c_mapFilename);
		pdbPutInt(ofile, config.flags.f_fogOfWar);
		i = MAX_MEMBERS; pdbPutInt(ofile, i);
		i = MAX_IDLIST; pdbPutInt(ofile, i);
		pdbPutInt(ofile, config.flags.f_defaultDefender);
		pdbPutInt(ofile, config.flags.f_askBeforeMoving);
		pdbPutInt(ofile, config.flags.f_showDeadMonsters);
	
		pdbPutNewLine(ofile); fprintf(ofile, "0|");
	
		for (i=0; i<MAX_IDLIST; i++) {
			for (j=0; j<MAX_MEMBERS+2; j++) {
				pdbPutInt(ofile, config.i_idList[i][j]);
			}
		}
	
		pdbPutNewLine(ofile); fprintf(ofile, "0|");
		for (i=0; i<MAX_MODIFIERS; i++) {
			pdbPutString(ofile, config.system_mods[i].c_message);
			pdbPutInt(ofile, config.system_mods[i].i_idFollows);
			pdbPutInt(ofile, config.system_mods[i].i_noRounds);
			for (j=0; j<MAX_MEMBERS; j++) { pdbPutInt(ofile, config.system_mods[i].i_whom[j]); }
			for (j=0; j<5; j++) { 
				pdbPutInt(ofile, config.system_mods[i].i_data[j][0]); 
				pdbPutInt(ofile, config.system_mods[i].i_data[j][1]); 
				pdbPutInt(ofile, config.system_mods[i].i_data[j][2]); 
			}
		}
	
		pdbPutNewLine(ofile); fprintf(ofile, "0|");
		for (i=0; i<MAX_MODIFIERS; i++) {
			pdbPutString(ofile, config.action_mods[i].c_message);
			pdbPutInt(ofile, config.action_mods[i].i_idFollows);
			pdbPutInt(ofile, config.action_mods[i].i_noRounds);
			for (j=0; j<MAX_MEMBERS; j++) { pdbPutInt(ofile, config.action_mods[i].i_whom[j]); }
			for (j=0; j<5; j++) { 
				pdbPutInt(ofile, config.action_mods[i].i_data[j][0]); 
				pdbPutInt(ofile, config.action_mods[i].i_data[j][1]); 
				pdbPutInt(ofile, config.action_mods[i].i_data[j][2]); 
			}
		}
	
		pdbPutNewLine(ofile); fprintf(ofile, "0|");
		for (i=0; i<MAX_TRIGGERS; i++) {
			pdbPutString(ofile, config.action_msgs[i].c_message);
			pdbPutInt(ofile, config.action_msgs[i].i_noRounds);
			pdbPutInt(ofile, config.action_msgs[i].i_display);
			pdbPutString(ofile, config.action_msgs[i].c_every);
		}
	
		pdbPutNewLine(ofile); fprintf(ofile, "0|");
		for (i=0; i<MAX_AUTODAMAGE; i++) {
			pdbPutString(ofile, config.auto_damage[i].c_description);
			pdbPutInt(ofile, config.auto_damage[i].i_initiatorID);
			for (j=0; j<MAX_MEMBERS; j++) { pdbPutInt(ofile, config.auto_damage[i].i_whom[j]); }
			pdbPutString(ofile, config.auto_damage[i].c_damage);
			pdbPutInt(ofile, config.auto_damage[i].i_noRounds);
			pdbPutInt(ofile, config.auto_damage[i].i_doneRounds);
			pdbPutInt(ofile, config.auto_damage[i].i_type);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag1);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag2);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag3);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag4);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag5);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag6);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag7);
			pdbPutInt(ofile, config.auto_damage[i].flags.f_flag8);
		}
	
		pdbPutNewLine(ofile); fprintf(ofile, "0|");
		if (ADMPversion < 1.30) {
			for (i=0; i<MAX_GROUPS; i++) {
				pdbPutString(ofile, config.groups[i].c_description);
				pdbPutInt(ofile, config.groups[i].i_active);
			}
		}
	}

	fclose(ofile);

	return 0;
}

/********************************************************************************/
int readSystemData(char *fn) {
FILE *ofile;
int i=0,j=0, max_members=0, max_idlists=0, max_triggers=0, max_modifiers=0, max_autodamage=0;
int i_idlists=0, i_triggers=0, i_modifiers=0, i_autodamage=0, flags[15], i_smodifiers=0, i_quickmods=0;
char *cp;
char buf[2048];

	if ((ofile = fopen(fn, "r")) == NULL) { return -1; }

	if (getc(ofile) != 'A') {
		fclose(ofile);
		if ((ofile = fopen(fn, "r")) == NULL) { return -1; }
		pdbFilePointer = ofile;
		fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);
		pdbTokenize(pdbDataLine);
	
		config.f_version = pdbGetFloat();
		config.i_roundCount = pdbGetInt();
		config.i_whenBleed = pdbGetInt();
		config.i_editID = pdbGetInt();
		config.i_actionInitID = pdbGetInt();
		config.i_actionRecvID = pdbGetInt();
		config.i_actionSelected = pdbGetInt();
		config.i_actionWeaponSelected = pdbGetInt();
		config.i_roundsSave = pdbGetInt(); if (config.i_roundsSave == 0) { config.i_roundsSave = 1; }
		if ((cp = pdbGetString()) != NULL) { strcpy(config.c_partyFilename, cp); }
		if ((cp = pdbGetString()) != NULL) { strcpy(config.c_monstFilename, cp); }
		config.flags.f_debug = pdbGetInt();
		config.flags.f_rollAllRolls = pdbGetInt();
		config.flags.f_rollInitRolls = pdbGetInt();
		config.flags.f_logfile = pdbGetInt();
		config.flags.f_rollInitEveryRnd = pdbGetInt();
		config.flags.f_removeMonstersInit = pdbGetInt();
		config.flags.f_oneMissTwentyHits = pdbGetInt();
		if ((cp = pdbGetString()) != NULL) { strcpy(config.c_mapFilename, cp); }
		if (config.c_mapFilename[0] == '\0') { strcpy(config.c_mapFilename, "mymap.map"); }
		config.flags.f_fogOfWar = pdbGetInt();
	
		max_members = pdbGetInt();
		max_idlists = pdbGetInt();
	
		config.flags.f_defaultDefender = pdbGetInt();
		config.flags.f_askBeforeMoving = pdbGetInt();
		config.flags.f_showDeadMonsters = pdbGetInt();
	
		if (max_idlists == 0) { 
			if (max_members > 0) { max_idlists = 15; }
			else { max_idlists = MAX_IDLIST; }
		}
		if (max_members == 0) { max_members = MAX_MEMBERS; }
		
		fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);
		pdbTokenize(pdbDataLine);
		for (i=0; i<max_idlists; i++) {
			for (j=0; j<max_members+2; j++) {
				config.i_idList[i][j] = pdbGetInt();
			}
		}
		
		fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);
		pdbTokenize(pdbDataLine);
		for (i=0; i<MAX_MODIFIERS; i++) {
			if ((cp = pdbGetString()) != NULL) { strcpy(config.system_mods[i].c_message, cp); }
			config.system_mods[i].i_idFollows = pdbGetInt();
			config.system_mods[i].i_noRounds = pdbGetInt();
			for (j=0; j<max_members; j++) { config.system_mods[i].i_whom[j] = pdbGetInt(); }
			for (j=0; j<5; j++) { 
				config.system_mods[i].i_data[j][0] = pdbGetInt();
				config.system_mods[i].i_data[j][1] = pdbGetInt();
				config.system_mods[i].i_data[j][2] = pdbGetInt();
			}
		}
		
		fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);
		pdbTokenize(pdbDataLine);
		for (i=0; i<MAX_MODIFIERS; i++) {
			if ((cp = pdbGetString()) != NULL) { strcpy(config.action_mods[i].c_message, cp); }
			config.action_mods[i].i_idFollows = pdbGetInt();
			config.action_mods[i].i_noRounds = pdbGetInt();
			for (j=0; j<max_members; j++) { config.action_mods[i].i_whom[j] = pdbGetInt(); }
			for (j=0; j<5; j++) { 
				config.action_mods[i].i_data[j][0] = pdbGetInt();
				config.action_mods[i].i_data[j][1] = pdbGetInt();
				config.action_mods[i].i_data[j][2] = pdbGetInt();
			}
		}
		
		fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);
		pdbTokenize(pdbDataLine);
		for (i=0; i<MAX_TRIGGERS; i++) {
			if ((cp = pdbGetString()) != NULL) { strcpy(config.action_msgs[i].c_message, cp); }
			config.action_msgs[i].i_noRounds = pdbGetInt();
			config.action_msgs[i].i_display = pdbGetInt();
			if (config.f_version > 1.12) {
				if ((cp = pdbGetString()) != NULL) { strncpy(config.action_msgs[i].c_every, cp, 9); config.action_msgs[i].c_every[9] = '\0'; }
			}
		}
		
		fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);
		pdbTokenize(pdbDataLine);
		for (i=0; i<MAX_AUTODAMAGE; i++) {
			if ((cp = pdbGetString()) != NULL) { strcpy(config.auto_damage[i].c_description, cp); }
			config.auto_damage[i].i_initiatorID = pdbGetInt();
			for (j=0; j<max_members; j++) { config.auto_damage[i].i_whom[j] = pdbGetInt(); }
			if ((cp = pdbGetString()) != NULL) { strcpy(config.auto_damage[i].c_damage, cp); }
			config.auto_damage[i].i_noRounds = pdbGetInt();
			config.auto_damage[i].i_doneRounds = pdbGetInt();
			config.auto_damage[i].i_type = pdbGetInt();
			config.auto_damage[i].flags.f_flag1 = pdbGetInt();
			config.auto_damage[i].flags.f_flag2 = pdbGetInt();
			config.auto_damage[i].flags.f_flag3 = pdbGetInt();
			config.auto_damage[i].flags.f_flag4 = pdbGetInt();
			config.auto_damage[i].flags.f_flag5 = pdbGetInt();
			config.auto_damage[i].flags.f_flag6 = pdbGetInt();
			config.auto_damage[i].flags.f_flag7 = pdbGetInt();
			config.auto_damage[i].flags.f_flag8 = pdbGetInt();
		}
	
		if (ADMPversion < 1.30) {
			fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);
			pdbTokenize(pdbDataLine);
			for (i=0; i<MAX_GROUPS; i++) {
				cp = pdbGetString();
				if (cp != NULL) {
					strncpy(config.groups[i].c_description, cp, 29); config.groups[i].c_description[29] = '\0';
					config.groups[i].i_active = pdbGetInt();
				}
				if (config.groups[i].c_description[0] == '\0') {
					sprintf(config.groups[i].c_description, "Group - %d", i);
				}
			}
		}
	} else {
		fclose(ofile);
		if ((ofile = fopen(fn, "r")) == NULL) { return -1; }

		while (fgets(buf, 2048, ofile) != NULL) {
			i = strlen(buf);
			if (buf[i-1] == '\n') { buf[i-1] = '\0'; }
			if (buf[i] == '\n') { buf[i] = '\0'; }
			if (buf[i+1] == '\n') { buf[i+1] = '\0'; }
//printf("rSD: %s\n", buf);
			switch (buf[0]) {
				case 'A':		// version etc data
							sscanf(&buf[2], "%f %d %d %d %d %d %d %d %d", &config.f_version, &config.i_roundCount, &config.i_whenBleed, &config.i_editID, &config.i_actionInitID, &config.i_actionRecvID, &config.i_actionSelected, &config.i_actionWeaponSelected, &config.i_roundsSave);
							break;
				case 'B':		// player filename
							strcpy(config.c_partyFilename, &buf[2]);
							break;
				case 'C':		// monster filename
							strcpy(config.c_monstFilename, &buf[2]);
							break;
				case 'D':		// map filename
							strcpy(config.c_mapFilename, &buf[2]);
							break;
				case 'E':		// max type variables
							sscanf(&buf[2], "%d %d %d %d %d", &max_members, &max_idlists, &max_modifiers, &max_triggers, &max_autodamage);
							break;
				case 'F':		// system flag settings
							sscanf(&buf[2], "%d %d %d %d %d %d %d %d %d %d %d %d", &flags[0],&flags[1],&flags[2],&flags[3],&flags[4],&flags[5],&flags[6],&flags[7],&flags[8],&flags[9],&flags[10],&flags[11]);
							config.flags.f_debug = flags[0];
							config.flags.f_rollAllRolls = flags[1];
							config.flags.f_rollInitRolls = flags[2];
							config.flags.f_logfile = flags[3];
							config.flags.f_rollInitEveryRnd = flags[4];
							config.flags.f_removeMonstersInit = flags[5];
							config.flags.f_oneMissTwentyHits = flags[6];
							config.flags.f_fogOfWar = flags[7];
							config.flags.f_defaultDefender = flags[8];
							config.flags.f_askBeforeMoving = flags[9];
							config.flags.f_showDeadMonsters = flags[10];
							config.flags.f_deathAtCON = flags[11];
							break;

				case 'G':		// dice system
							sscanf(&buf[2], "%d %d", &i, &j);
							config.i_diceSystem = -1; doDiceSystem(i);		// setup the screen etc
							config.i_diceSystem = i;
							config.i_initSystem = j;
							aSys_diceSystem->value(i);
							aSys_initSystem->value(j);
							break;

				case 'I':		// id lists
							i = i_idlists;
							cp = strtok(&buf[2], " ");
//							for (j=0; j<MAX_MEMBERS+2; j++) {
							for (j=0; j<max_members+2; j++) {
								if (cp != NULL) config.i_idList[i][j] = atoi(cp);
								cp = strtok(NULL, " ");
							}
							i_idlists++;
							break;
				case 'S':		// system modifiers
							i = i_smodifiers;
							cp = strtok(&buf[2], "|"); if (cp != NULL) strcpy(config.system_mods[i].c_message, cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.system_mods[i].i_idFollows = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.system_mods[i].i_noRounds = atoi(cp);
//							for (j=0; j<MAX_MEMBERS; j++) { 
							for (j=0; j<max_members; j++) { 
								cp = strtok(NULL, "|"); if (cp != NULL) config.system_mods[i].i_whom[j] = atoi(cp); 
							}
							for (j=0; j<5; j++) { 
								cp = strtok(NULL, "|"); if (cp != NULL) config.system_mods[i].i_data[j][0] = atoi(cp);
								cp = strtok(NULL, "|"); if (cp != NULL) config.system_mods[i].i_data[j][1] = atoi(cp);
								cp = strtok(NULL, "|"); if (cp != NULL) config.system_mods[i].i_data[j][2] = atoi(cp);
							}
							i_smodifiers++;
							break;
				case 'M':		// modifiers
							i = i_modifiers;
							cp = strtok(&buf[2], "|"); if (cp != NULL) strcpy(config.action_mods[i].c_message, cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.action_mods[i].i_idFollows = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.action_mods[i].i_noRounds = atoi(cp);
//							for (j=0; j<MAX_MEMBERS; j++) { 
							for (j=0; j<max_members; j++) { 
								cp = strtok(NULL, "|"); if (cp != NULL) config.action_mods[i].i_whom[j] = atoi(cp); 
							}
							for (j=0; j<5; j++) { 
								cp = strtok(NULL, "|"); if (cp != NULL) config.action_mods[i].i_data[j][0] = atoi(cp);
								cp = strtok(NULL, "|"); if (cp != NULL) config.action_mods[i].i_data[j][1] = atoi(cp);
								cp = strtok(NULL, "|"); if (cp != NULL) config.action_mods[i].i_data[j][2] = atoi(cp);
							}
							i_modifiers++;
							break;
				case 'R':		// DM screen resolution
							sscanf(&buf[2], "%d %d", &i, &j);
							aSys_ScreenWidth->value(i);
							aSys_ScreenHeight->value(j);
							setScreenSize();
							break;
				case 'T':		// triggers
							i = i_triggers;
							cp = strtok(&buf[2], "|"); if (cp != NULL) strcpy(config.action_msgs[i].c_message, cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.action_msgs[i].i_noRounds = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.action_msgs[i].i_display = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) strcpy(config.action_msgs[i].c_every, cp);
							i_triggers++;
							break;
				case 'U':		// autodamage
							i = i_autodamage;
							cp = strtok(&buf[2], "|"); if (cp != NULL) strcpy(config.auto_damage[i].c_description, cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].i_initiatorID = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) strcpy(config.auto_damage[i].c_damage, cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].i_noRounds = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].i_doneRounds = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].i_type = atoi(cp);
//							for (j=0; j<MAX_MEMBERS; j++) { 
							for (j=0; j<max_members; j++) { 
								cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].i_whom[j] = atoi(cp);
							}
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag1 = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag2 = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag3 = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag4 = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag5 = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag6 = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag7 = atoi(cp);
							cp = strtok(NULL, "|"); if (cp != NULL) config.auto_damage[i].flags.f_flag8 = atoi(cp);
							i_autodamage++;
							break;
				case 'Q':		// quick mods
							cp = strtok(&buf[2], "|"); if (cp != NULL) config.quickmods[i_quickmods].i_id = atoi(cp);
							for (j=0; j<MAX_QUICKMODTYPES; j++) {
								cp = strtok(NULL, "|"); if (cp != NULL) config.quickmods[i_quickmods].i_effects[j][1] = atoi(cp);
							}
							i_quickmods++;
							break;
			}
		}
	}
	fclose(ofile);

	return 0;
}

/********************************************************************************/
void loadCombatNotes() {
char *cp;

	cp = pdbTokenize(pdbDataLine);	// get rid of the line no and key
	cp = pdbGetString();

	while ((cp = pdbGetString()) != NULL) {
		a_CTNotesDetails->add(cp);
	}
}

/********************************************************************************/
void loadEditNotes() {
char *cp;

	cp = pdbTokenize(pdbDataLine);	// get rid of the line no and key
	cp = pdbGetString();

	while ((cp = pdbGetString()) != NULL) {
		edit_notes_buffer->append(cp);
		edit_notes_buffer->append("\n");
	}
}

/********************************************************************************/
void doNotesAction(int action, int id) {
FILE *nf;
char *cp;

	if (id >= MAX_PLAYERS) {
		sprintf(mybuf1, "%s.mnt", config.c_monstFilename);
	} else {
		sprintf(mybuf1, "%s.pnt", config.c_partyFilename);
	}

if (config.flags.f_debug != 0) printf("dNA: %d %d %d\n", action, id, edit_notes_buffer->length());

	switch(action) {
		case 0:		// SAVE
					sprintf(mybuf2, "%d", id);
					pdbDeleteAllRecord(mybuf1, mybuf2, NULL, NULL);
					if ((nf = fopen(mybuf1, "a+")) != NULL) {
						strncpy(mybuf1, edit_notes_buffer->text(),2047);
						while ((cp = strstr(mybuf1, "\n")) != NULL) {
							*cp = '|';
						}
						fprintf(nf, "+%d|%d|%s|\n", id, id, mybuf1);
						fclose(nf);
					}
				  break;

		case 1:		// LOAD
				  edit_notes_buffer->select(0, edit_notes_buffer->length());
				  edit_notes_buffer->remove_selection();
				  sprintf(mybuf2, "%d", id);
				  pdbKeySearch(mybuf1, loadEditNotes, NULL, 1, mybuf2, NULL, NULL);
				  break;

		case 2:		// DISPLAY ON COMBAT SCREEN
					a_CTNotesDetails->clear();
				  sprintf(mybuf2, "%d", id);
				  pdbKeySearch(mybuf1, loadCombatNotes, NULL, 1, mybuf2, NULL, NULL);
				  break;
	}
}

/********************************************************************************/
void qkHealAction(int action) {
	int j=0, k, l;

	switch (action) {
		case 0:		// refresh
/*
				  a_qkheal_ln00->deactivate(); a_qkheal_ln01->deactivate(); a_qkheal_ln01->value("");
				  a_qkheal_ln10->deactivate(); a_qkheal_ln11->deactivate(); a_qkheal_ln11->value("");
				  a_qkheal_ln20->deactivate(); a_qkheal_ln21->deactivate(); a_qkheal_ln21->value("");
				  a_qkheal_ln30->deactivate(); a_qkheal_ln31->deactivate(); a_qkheal_ln31->value("");
				  a_qkheal_ln40->deactivate(); a_qkheal_ln41->deactivate(); a_qkheal_ln41->value("");
				  a_qkheal_ln50->deactivate(); a_qkheal_ln51->deactivate(); a_qkheal_ln51->value("");
				  a_qkheal_ln60->deactivate(); a_qkheal_ln61->deactivate(); a_qkheal_ln61->value("");
				  a_qkheal_ln70->deactivate(); a_qkheal_ln71->deactivate(); a_qkheal_ln71->value("");
				  a_qkheal_ln80->deactivate(); a_qkheal_ln81->deactivate(); a_qkheal_ln81->value("");
				  a_qkheal_ln90->deactivate(); a_qkheal_ln91->deactivate(); a_qkheal_ln91->value("");
*/
				  a_qkheal_ln00->activate(); a_qkheal_ln01->deactivate(); a_qkheal_ln01->value("");
				  a_qkheal_ln10->activate(); a_qkheal_ln11->deactivate(); a_qkheal_ln11->value("");
				  a_qkheal_ln20->activate(); a_qkheal_ln21->deactivate(); a_qkheal_ln21->value("");
				  a_qkheal_ln30->activate(); a_qkheal_ln31->deactivate(); a_qkheal_ln31->value("");
				  a_qkheal_ln40->activate(); a_qkheal_ln41->deactivate(); a_qkheal_ln41->value("");
				  a_qkheal_ln50->activate(); a_qkheal_ln51->deactivate(); a_qkheal_ln51->value("");
				  a_qkheal_ln60->activate(); a_qkheal_ln61->deactivate(); a_qkheal_ln61->value("");
				  a_qkheal_ln70->activate(); a_qkheal_ln71->deactivate(); a_qkheal_ln71->value("");
				  a_qkheal_ln80->activate(); a_qkheal_ln81->deactivate(); a_qkheal_ln81->value("");
				  a_qkheal_ln90->activate(); a_qkheal_ln91->deactivate(); a_qkheal_ln91->value("");

				  for (int i=0; i<MAX_PLAYERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							sprintf(mybuf1, "%s (%d/%d) = %d", players[i].c_name, players[i].i_hp[HP_CUR], players[i].i_hp[HP_MAX], (players[i].i_hp[HP_MAX] - players[i].i_hp[HP_CUR]));
							switch (j) {
								case 0: a_qkheal_ln00->value(mybuf1); a_qkheal_ln01->activate(); break;
								case 1: a_qkheal_ln10->value(mybuf1); a_qkheal_ln11->activate(); break;
								case 2: a_qkheal_ln20->value(mybuf1); a_qkheal_ln21->activate(); break;
								case 3: a_qkheal_ln30->value(mybuf1); a_qkheal_ln31->activate(); break;
								case 4: a_qkheal_ln40->value(mybuf1); a_qkheal_ln41->activate(); break;
								case 5: a_qkheal_ln50->value(mybuf1); a_qkheal_ln51->activate(); break;
								case 6: a_qkheal_ln60->value(mybuf1); a_qkheal_ln61->activate(); break;
								case 7: a_qkheal_ln70->value(mybuf1); a_qkheal_ln71->activate(); break;
								case 8: a_qkheal_ln80->value(mybuf1); a_qkheal_ln81->activate(); break;
								case 9: a_qkheal_ln90->value(mybuf1); a_qkheal_ln91->activate(); break;
							}
							config.i_idList[ID_QKHEAL][j] = i;
							j++;
							config.i_idList[ID_QKHEAL][j] = -1;
						}
				  }
				  a_qkheal_all->value("");
				  break;

		case 1:		// accept
				  if ((k = atoi(a_qkheal_all->value())) != 0) {
				  	 j = 0;
				  	 while (config.i_idList[ID_QKHEAL][j] != -1) {
						if ((l = config.i_idList[ID_QKHEAL][j]) != -1) {
							players[l].i_hp[HP_CUR] += k;
						}
						j++;
					 }
				  } else {
					 if ((k=atoi(a_qkheal_ln01->value())) != 0) { j = config.i_idList[ID_QKHEAL][0]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln11->value())) != 0) { j = config.i_idList[ID_QKHEAL][1]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln21->value())) != 0) { j = config.i_idList[ID_QKHEAL][2]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln31->value())) != 0) { j = config.i_idList[ID_QKHEAL][3]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln41->value())) != 0) { j = config.i_idList[ID_QKHEAL][4]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln51->value())) != 0) { j = config.i_idList[ID_QKHEAL][5]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln61->value())) != 0) { j = config.i_idList[ID_QKHEAL][6]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln71->value())) != 0) { j = config.i_idList[ID_QKHEAL][7]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln81->value())) != 0) { j = config.i_idList[ID_QKHEAL][8]; players[j].i_hp[HP_CUR] += k; }
					 if ((k=atoi(a_qkheal_ln91->value())) != 0) { j = config.i_idList[ID_QKHEAL][9]; players[j].i_hp[HP_CUR] += k; }
				  }
				  j = 0;
				  while (config.i_idList[ID_QKHEAL][j] != -1) {
						k = config.i_idList[ID_QKHEAL][j];
						if (players[k].i_hp[HP_CUR] > players[k].i_hp[HP_MAX]) { players[k].i_hp[HP_CUR] = players[k].i_hp[HP_MAX]; }
						j++;
				  }
				  a_qkheal_ln01->value(""); a_qkheal_ln11->value(""); a_qkheal_ln21->value("");
				  a_qkheal_ln31->value(""); a_qkheal_ln41->value(""); a_qkheal_ln51->value("");
				  a_qkheal_ln61->value(""); a_qkheal_ln71->value(""); a_qkheal_ln81->value("");
				  a_qkheal_ln91->value("");
				  qkHealAction(0);		// refresh
				  break;
	}
}

/********************************************************************************/
void cb_initPopupMenu(Fl_Widget* w, void*) {
int i=0,x=0,y=0,msel=0;

	i = config.i_idList[ID_INIT][initiatorSelected - 1];
	x = players[i].i_mapX;
	y = players[i].i_mapY;

	if (i<0 || i>MAX_MEMBERS) { return; }

//printf("iPM: %d = %d %d:%d %d\n", initPopupMenu->value(), i, x, y, initiatorSelected);
	while (popMenuItems[msel] != NULL) {
		if (popMenuItems[msel][0] == '_') {
			if (strcasecmp(initPopupMenu->text(), &popMenuItems[msel][1]) == 0) { break; }
		} else {
			if (strcasecmp(initPopupMenu->text(), &popMenuItems[msel][0]) == 0) { break; }
		}
		msel++;
	}
	if (popMenuItems[msel] == NULL) { return; }
//printf("iPM: %d = %d\n", initPopupMenu->value(), msel);

	switch (msel) {
		case 0:		// do action
					config.i_actionInitID = i;
					if (config.i_diceSystem == DICE_D20) {
						setCombatDisplay(1);
						a_ActionWindow->show();
					} else {
						doD100WindowSetup(0);
						a_d100CombatWindow->show();
					}
					break;

		case 3:		// hide/unhide
		case 2:		// hide/unhide
//					if (x < 0 || y < 0) { break; }
//					if (combatGridMap->getGridTile()->getGridPointHidden(x,y) == 1) { j = 0; players[i].flags.f_invisible = 0; }
//					else { j = 1; players[i].flags.f_invisible = 1; }
//					combatGridMap->getGridTile()->setGridPointHidden(x,y,j);
					if (players[i].flags.f_invisible == 0) { players[i].flags.f_invisible = 1; } else { players[i].flags.f_invisible = 0; }
					break;

		case 5:		// remove from map
					if (x < 0 || y < 0) { break; }
					combatGridMap->getGridTile()->removeObject(x, y);
					break;

		case 13:		// enable or disable them
		case 12:		// enable or disable them
					if (players[i].flags.f_disabled == 0) { players[i].flags.f_disabled = 1; } else { players[i].flags.f_disabled = 0; }
					break;

		case 14:		// mark as done an action
					players[i].i_doneAttacks++;
					reloadNames(1);
					break;

		case 16:		// d100 - spell charging
					players[i].i_roundsUntil[ROUND_SPELL_CHG]++;
					players[i].i_doneAttacks++;
					break;

		case 17:		// d100 - missile load
					players[i].i_roundsUntil[ROUND_MISSILE_CHG]++;
					players[i].i_doneAttacks++;
					break;

		case 18:		// quick edit
					config.i_quickEditID = i;
					doQuickEdit(0);
					break;

		case 19:		// centre on this creature
					combatGridMap->getGridTile()->centreMap(x,y);
					combatGridMap->repaint();
					break;
	}
}

/********************************************************************************/
void cb_gridPopupMenu(Fl_Widget* w, void*) {
	int i=0, j=0, x=0, y=0, dx=0, dy=0, msel=0;
//printf("in cb_gridPopupMenu: %d:%d:%d\n", gridPopupMenu->value(), combatGridMap->getClickedGridType(), combatGridMap->getClickedGridID());

	x = combatGridMap->getClickedX();
	y = combatGridMap->getClickedY();

	while (popMenuItems[msel] != NULL) {
		if (popMenuItems[msel][0] == '_') {
			if (strcasecmp(gridPopupMenu->text(), &popMenuItems[msel][1]) == 0) { break; }
		} else {
			if (strcasecmp(gridPopupMenu->text(), &popMenuItems[msel][0]) == 0) { break; }
		}
		msel++;
	}
//printf("cbgPM: %d:%s = %d\n", gridPopupMenu->value(), gridPopupMenu->text(), msel);
	if (popMenuItems[msel] == NULL) { return; }

	switch (msel) {
		case 0:		// do action
					if ((config.i_actionInitID = combatGridMap->getClickedGridID()) == -1) { return; }
					dy = combatGridMap->getClickedGridType();
					if (dy != GRID_PLAYER && dy != GRID_MONSTER) { return; }
						// do a d20 or d100 combat
					if (config.i_diceSystem == DICE_D20) {
						setCombatDisplay(1);
						a_ActionWindow->show();
					} else {
						doD100WindowSetup(0);
						a_d100CombatWindow->show();
					}
					//combatGridMap->getGridTile()->repaint();
					break;

		case 1:		// move players in marching order to here	
					if (config.flags.f_askBeforeMoving != 0) {
						if (doAreYouSure("Really move all the players here ?") != 1) { break; }
					}
					externalGridMap->getGridTile()->centreMap(x,y);
					externalGridMap->repaint();
					for (i=0; i<MAX_PLAYERS; i++) {
						if (players[i].i_mapX != -1 && players[i].i_mapY != -1) {
							dx = x - players[i].i_mapX;
							dy = y - players[i].i_mapY;
							break;
						}
					}
					for (i=0; i<MAX_PLAYERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0 && players[i].i_mapX != -1) {
							x = players[i].i_mapX + dx;
							y = players[i].i_mapY + dy;
							j = combatGridMap->getGridTile()->getGridPointPrevColor(players[i].i_mapX, players[i].i_mapY);
							combatGridMap->setGridType(players[i].i_mapX, players[i].i_mapY, 0, 0);
							combatGridMap->getGridTile()->setGridPointColor(players[i].i_mapX, players[i].i_mapY, j);
							while (1) {
								if (combatGridMap->getGridTile()->getGridPointType(x,y) == 0 &&
										combatGridMap->getGridTile()->getGridPointColor(x,y) < 8) {
									combatGridMap->setGridType(x, y, GRID_PLAYER, i);
									break;
								}
								x++;
								if (x % 3 == 0) { y++; x-=3; }
							}
						}
					}
					break;

		case 7:		// move players here
					if (config.flags.f_askBeforeMoving != 0) {
						if (doAreYouSure("Really move all the players here ?") != 1) { break; }
					}
					externalGridMap->getGridTile()->centreMap(x,y);
					externalGridMap->repaint();
					for (i=0; i<MAX_PLAYERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							if (players[i].i_mapX != -1 && players[i].i_mapY != -1) {
								j = combatGridMap->getGridTile()->getGridPointPrevColor(players[i].i_mapX, players[i].i_mapY);
								combatGridMap->setGridType(players[i].i_mapX, players[i].i_mapY, 0, 0);
								combatGridMap->getGridTile()->setGridPointColor(players[i].i_mapX, players[i].i_mapY, j);
								players[i].i_mapX = players[i].i_mapY = -1;
							}
 							while (players[i].i_mapX == -1) {
								if (combatGridMap->getGridTile()->getGridPointType(x,y) == 0 &&
										combatGridMap->getGridTile()->getGridPointColor(x,y) < 8) {
									combatGridMap->setGridType(x, y, GRID_PLAYER, i);
								}
								x++;
								if (x % 3 == 0) { y++; x-=3; }
							}
						}
					}
					break;

		case 8:		// move monsters here
					if (config.flags.f_askBeforeMoving != 0) {
						if (doAreYouSure("Really move all the monsters here ?") != 1) { break; }
					}
					for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							if (players[i].i_mapX != -1 || players[i].i_mapY != -1) {
								j = combatGridMap->getGridTile()->getGridPointPrevColor(players[i].i_mapX, players[i].i_mapY);
								combatGridMap->getGridTile()->setShadow(players[i].i_mapX, players[i].i_mapY, i, GRID_MONSTER, (players[i].i_space/5),0);
								combatGridMap->setGridType(players[i].i_mapX, players[i].i_mapY, 0, 0);
								combatGridMap->getGridTile()->setGridPointColor(players[i].i_mapX, players[i].i_mapY, j);
								players[i].i_mapX = players[i].i_mapY = -1;
							}
 							while (players[i].i_mapX == -1) {
								if (combatGridMap->getGridTile()->getGridPointType(x,y) == 0 &&
										combatGridMap->getGridTile()->getGridPointColor(x,y) < 8) {
									combatGridMap->setGridType(x, y, GRID_MONSTER, i);
//printf("aNM: %d %d %d\n", i, x, y);
								}
								x++;
								if (x % 3 == 0) { y++; x-=3; }
							}
						}
					}
					break;

		case 2:		// hide/unhide
		case 3:		// hide/unhide
					if ((i = combatGridMap->getClickedGridID()) == -1) { return; }
					j = combatGridMap->getClickedGridType();
					if (j != GRID_MONSTER && j != GRID_PLAYER) { return; }
					if (combatGridMap->getGridTile()->getGridPointHidden(x,y) == 1) { j = 0; players[i].flags.f_invisible = 0; }
					else { j = 1; players[i].flags.f_invisible = 1; players[i].flags.f_wasViewed = 0; }
					combatGridMap->getGridTile()->setGridPointHidden(x,y,j);
					combatGridMap->getGridTile()->setLOSAll();
					externalGridMap->getGridTile()->redraw();
					break;

		case 5:		// remove from map
		case 6:		// remove from map and disable
					j = combatGridMap->getClickedGridType(); i = combatGridMap->getClickedGridID();
					if (j == GRID_MONSTER && msel == 6) {
						players[i].flags.f_disabled = 1;
					}
					combatGridMap->getGridTile()->removeObject(x, y);
					break;

		case 9:		// add new monsters
					for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0 && players[i].i_mapX == -1) {
 							while (players[i].i_mapX == -1) {
								if (combatGridMap->getGridTile()->getGridPointType(x,y) == 0 &&
										combatGridMap->getGridTile()->getGridPointColor(x,y) < 8) {
									combatGridMap->setGridType(x, y, GRID_MONSTER, i);
//printf("aNM: %d %d %d\n", i, x, y);
								}
								x++;
								if (x % 3 == 0) { y++; x-=3; }
							}
						}
					}
					break;

		case 4:		// centre both maps here
					combatGridMap->getGridTile()->centreMap(x,y);
					combatGridMap->repaint();
					externalGridMap->getGridTile()->centreMap(x,y);
					externalGridMap->repaint();
					break;

		case 10:		// add new monsters in a group
					a_addNewName->value("Room - ");
					a_addNewDisabled->value(1);
					a_addToNewGroup->show();
					break;

		case 11:		// add/upd/del a map note/object
					a_NotesDescription->value("");
					a_NotesDelete->deactivate();
					if (combatGridMap->getClickedGridType() == GRID_OBJECT) {
						i = combatGridMap->getClickedGridID();
						a_NotesDescription->value(config.objects[i].c_description);
						a_ObjectIcon->value(config.objects[i].c_iconFile);
						sprintf(mybuf2, "%d", config.objects[i].i_width); a_ObjectWidth->value(mybuf2);
						sprintf(mybuf2, "%d", config.objects[i].i_height); a_ObjectHeight->value(mybuf2);
						a_NotesDelete->activate();
					} else {
						a_NotesDescription->value("");
						a_ObjectIcon->value("");
						a_ObjectWidth->value("5");
						a_ObjectHeight->value("5");
					}
					a_notesWindow->show();
					break;

		case 12:		// enable/disable
		case 13:		// enable/disable
					j = combatGridMap->getClickedGridType(); i = combatGridMap->getClickedGridID();
					if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) { 
						if (players[i].flags.f_disabled == 0) { players[i].flags.f_disabled = 1; } else { players[i].flags.f_disabled = 0; }
					}
					break;

		case 14:		// mark as having done an action
					j = combatGridMap->getClickedGridType(); i = combatGridMap->getClickedGridID();
					if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) { 
						players[i].i_doneAttacks++;
						reloadNames(1);
					}
					break;

		case 15:		// do mass combat
					a_MCAttkGroups->value("1");
					a_MCAttkInGroups->value("0");
					a_MCAttkBAB->value("0");
					a_MCAttkDamage->value("");
					a_MCDefdInGroups->value("0");
					a_MCDefdAC->value("0");
					a_MCResults->clear();
					a_MCShowTotals->value(1);
					a_MCDied->value("0");
					a_MCMaxHP->value("0");
					a_MCCurrentHP->value("0");
					a_MCAttackers->clear();
					a_MCDefenders->clear();
					j = 0;
					for (i=0; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].i_inactive == 0) {
							if (players[i].i_noInGroup != 0) {
								sprintf(mybuf2, "%s # %d", players[i].c_name, players[i].i_noInGroup);
							} else {
								sprintf(mybuf2, "%s", players[i].c_name);
							}
							a_MCAttackers->add(mybuf2);
							a_MCDefenders->add(mybuf2);
							config.i_idList[ID_MASSCOMBAT][j++] = i;
						}
					}
					config.i_idList[ID_MASSCOMBAT][j] = -1; config.i_idList[ID_MASSCOMBAT][j+1] = -1;
					a_MCDefenders->deactivate();
					a_MassCombatWindow->show();
					break;

		case 16:		// d100 - spell charging
					j = combatGridMap->getClickedGridType(); i = combatGridMap->getClickedGridID();
					if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) { 
						players[i].i_roundsUntil[ROUND_SPELL_CHG]++;
						players[i].i_doneAttacks++;
					}
					break;

		case 17:		// d100 - missile load
					j = combatGridMap->getClickedGridType(); i = combatGridMap->getClickedGridID();
					if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) { 
						players[i].i_roundsUntil[ROUND_MISSILE_CHG]++;
						players[i].i_doneAttacks++;
					}
					break;

		case 18:		// quick edit
					j = combatGridMap->getClickedGridType(); i = combatGridMap->getClickedGridID();
					if (i == -1 || (j != GRID_MONSTER && j != GRID_PLAYER)) { 
						return;
					}
					config.i_quickEditID = i;
					doQuickEdit(0);
					break;
	}
	combatGridMap->getGridTile()->repaint();
	externalGridMap->getGridTile()->redraw();
}

/********************************************************************************/
int tileMapEventHandler() {
//printf("in tileMapEventHandler\n");
	return 0;
}

/********************************************************************************/
int gridMapEventHandler() {
int x=0, y=0, i=0, j=0;

	x = combatGridMap->getClickedX();
	y = combatGridMap->getClickedY();

//printf("in gridMapEventHandler\n");
	if (gridPopupMenu == NULL) {
		gridPopupMenu = new Fl_Menu_Button(100,100,200,200);
		gridPopupMenu->type(Fl_Menu_Button::POPUP3);
		gridPopupMenu->callback(cb_gridPopupMenu);
	}

	gridPopupMenu->clear();

	j = combatGridMap->getClickedGridType(); i = combatGridMap->getClickedGridID();

	if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) { 
		gridPopupMenu->add(&popMenuItems[0][0]);
		gridPopupMenu->add(&popMenuItems[14][0]);
	}
	gridPopupMenu->add(&popMenuItems[1][0]);
	if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) { 
		if (players[i].flags.f_invisible == 1) { 
			gridPopupMenu->add(&popMenuItems[2][0]);
		} else {
			gridPopupMenu->add(&popMenuItems[3][0]);
		}
	}
	gridPopupMenu->add(&popMenuItems[4][0]);
	if (j == GRID_MONSTER) {
		gridPopupMenu->add(&popMenuItems[5][1]);
		gridPopupMenu->add(&popMenuItems[6][0]);
	} else {
		gridPopupMenu->add(&popMenuItems[5][0]);
	}
	gridPopupMenu->add(&popMenuItems[7][0]);
	gridPopupMenu->add(&popMenuItems[8][0]);
	gridPopupMenu->add(&popMenuItems[9][0]);
	gridPopupMenu->add(&popMenuItems[10][0]);
	gridPopupMenu->add(&popMenuItems[11][0]);
	if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) { 
		if (players[i].flags.f_disabled == 0) { 
			gridPopupMenu->add(&popMenuItems[12][0]);
		} else {
			gridPopupMenu->add(&popMenuItems[13][0]);
		}
	}
	gridPopupMenu->add(&popMenuItems[15][0]);

	if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER) && config.i_diceSystem != DICE_D20) { 
		gridPopupMenu->add(&popMenuItems[16][0]);
		gridPopupMenu->add(&popMenuItems[17][0]);
	}
	if (i != -1 && (j == GRID_MONSTER || j == GRID_PLAYER)) {
		gridPopupMenu->add(&popMenuItems[18][0]);
	}

	setWindowTitles();		// TODO

	gridPopupMenu->popup();
	return 0;
}

/********************************************************************************/
void doMapFileAction(int action) {
	int i;
	char *iname;

	switch (action) {	
		case 0:		// load
				doNotesAction(2);
				if ((iname = fl_file_chooser("Map File Load", "*.map", config.c_mapFilename, 1)) != NULL) {
					strcpy(config.c_mapFilename, iname);
					aSys_mapFilename->value(iname);
					combatGridMap->loadGridMap(config.c_mapFilename);
					sprintf(mybuf2, "%d", combatGridMap->getGridTile()->getGridSzWidth()); aSys_MapWidth->value(mybuf2);
					sprintf(mybuf2, "%d", combatGridMap->getGridTile()->getGridSzHeight()); aSys_MapHeight->value(mybuf2);
					doIconAction(3);
					doGroupAction(-1);		// refresh group names
				}
				break;

		case 1:		// save
				if ((iname = fl_file_chooser("Map File Save", "*.map", config.c_mapFilename, 1)) != NULL) {
					strncpy(config.c_mapFilename, iname, 43);
					config.c_mapFilename[43] = '\0'; iname[43] = '\0';
					aSys_mapFilename->value(iname);
					combatGridMap->saveGridMap(config.c_mapFilename);
				}
				break;

		case 2:		// clear or new
				combatGridMap->clearGridMap();
				for (i=0; i<MAX_MEMBERS; i++) {
					players[i].i_mapX = players[i].i_mapY = -1;
				}
				combatGridMap->resizeGridMap(atoi(aSys_MapWidth->value()), atoi(aSys_MapHeight->value()));
				externalGridMap->resizeGridMap(atoi(aSys_MapWidth->value()), atoi(aSys_MapHeight->value()));
				combatGridMap->redraw();
				externalGridMap->redraw();
				doNotesAction(2);
				break;

		case 3:		// resize
				combatGridMap->resizeGridMap(atoi(aSys_MapWidth->value()), atoi(aSys_MapHeight->value()));
				externalGridMap->resizeGridMap(atoi(aSys_MapWidth->value()), atoi(aSys_MapHeight->value()));
				break;

		case 4:		// remap color ID's
				if (doAreYouSure("Do you really want to ?") == 1) {
					combatGridMap->getGridTile()->remapColors((int )aSys_MapColorFrom->value(),(int )aSys_MapColorTo->value());
				}
				break;
	}
}

/********************************************************************************/
void doGroupAction(int action) {
	int i, j, k=0;

	j = a_GroupList->value() - 1;

	switch (action) {
		case -1: a_GroupList->clear();
					for (i=0; i<MAX_GROUPS; i++) {
						if (config.groups[i].c_description[0] == '\0') {
							sprintf(mybuf2, "Group %d", i);
							a_GroupList->add(mybuf2);
						} else {
							a_GroupList->add(config.groups[i].c_description);
						}
					}
					break;

		case 0:	// grp selected
				a_GroupGroup->activate();
				a_GroupMembers->clear();
				for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
						if (players[i].i_inGroup == j) {
							a_GroupMembers->add(players[i].c_name, 1);
						} else {
							a_GroupMembers->add(players[i].c_name, 0);
						}
						config.i_idList[ID_GROUP][k++] = i;
					}
				}
				a_GroupDescription->value(config.groups[j].c_description);
				a_GroupActive->value(config.groups[j].i_active);
				break;

		case 1:	// cancel
				a_GroupGroup->deactivate();
				break;

		case 2:	// accept
				for (i=a_GroupMembers->nitems(); i>0; i--) {
					k = config.i_idList[ID_GROUP][i-1];
					if (a_GroupMembers->checked(i) != 0) {
						players[k].i_inGroup = j;
					} else {
						if (players[k].i_inGroup == j) { players[k].i_inGroup = -1; }
					}
				}
				a_GroupGroup->deactivate();

				strncpy(config.groups[j].c_description, a_GroupDescription->value(), 29); config.groups[j].c_description[29] = '\0';
				config.groups[j].i_active = a_GroupActive->value();
				a_GroupList->clear();
				for (i=0; i<MAX_GROUPS; i++) {
					if (config.groups[i].c_description[0] == '\0') {
						sprintf(mybuf2, "Group %d", i);
						a_GroupList->add(mybuf2);
					} else {
						a_GroupList->add(config.groups[i].c_description);
					}
				}
				break;

		case 3:	// enable all in group
				for (i=a_GroupMembers->nitems(); i>0; i--) {
					k = config.i_idList[ID_GROUP][i-1];
					if (a_GroupMembers->checked(i) != 0) {
						players[k].i_inGroup = j;
					} else {
						if (players[k].i_inGroup == j) { players[k].i_inGroup = -1; }
					}
				}
				for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
						if (players[i].i_inGroup == j) {
							players[i].flags.f_disabled = 0;
						}
					}
				}
				break;

		case 4:	// disable all except this group
				for (i=a_GroupMembers->nitems(); i>0; i--) {
					k = config.i_idList[ID_GROUP][i-1];
					if (a_GroupMembers->checked(i) != 0) {
						players[k].i_inGroup = j;
					} else {
						if (players[k].i_inGroup == j) { players[k].i_inGroup = -1; }
					}
				}
				for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
						if (players[i].i_inGroup == j) {
							players[i].flags.f_disabled = 0;
						} else {
							players[i].flags.f_disabled = 1;
						}
					}
				}
				break;

		case 5:	// clear all details
//				a_GroupGroup->deactivate();
//				a_GroupList->clear();
//				for (i=0; i<MAX_GROUPS; i++) {
//					sprintf(config.groups[i].c_description, "Group %d", i);
//					config.groups[i].i_members[0] = -1;
//					a_GroupList->add(config.groups[i].c_description);
//				}
				a_GroupMembers->clear();
				for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
					players[i].i_inGroup = -1;
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
						a_GroupMembers->add(players[i].c_name, 0);
						config.i_idList[ID_GROUP][k++] = i;
					}
				}
				break;

		case 6:	// delete all selected
				for (i=a_GroupMembers->nitems(); i>0; i--) {
					k = config.i_idList[ID_GROUP][i-1];
					if (a_GroupMembers->checked(i) != 0) {
				  		if (players[k].i_mapX > 0) {
							combatGridMap->getGridTile()->removeObject(players[k].i_mapX, players[k].i_mapY);
							players[k].i_mapX = players[k].i_mapY = -1;
				  		}
				  		memset(&players[k].c_name[0], '\0', sizeof(ADMPplayer));		// delete
					}
				}
				break;

		case 7:	// remove from map
				for (i=a_GroupMembers->nitems(); i>0; i--) {
					k = config.i_idList[ID_GROUP][i-1];
					if (a_GroupMembers->checked(i) != 0) {
						combatGridMap->getGridTile()->removeObject(players[k].i_mapX, players[k].i_mapY);
						players[k].i_mapX = players[k].i_mapY = -1;
					}
				}
				break;

		case 8:	// disable all selected
				for (i=a_GroupMembers->nitems(); i>0; i--) {
					k = config.i_idList[ID_GROUP][i-1];
					if (a_GroupMembers->checked(i) != 0) {
						players[k].flags.f_disabled = 1;
					}
				}
				break;
	}
}

/********************************************************************************/
void setScreenSize() {
int w=0,h=0;

	w = (int )aSys_ScreenWidth->value();
	h = (int )aSys_ScreenHeight->value();
//printf("setScreenSize: %d:%d\n", w, h);	

	a_MainWindow->size(w,h);

//	a_TMain->size(w-4,h);		// stops it from messing up the edit tab for some reason

	a_TCombat->size(w-5,h-25);
	combatGridMap->size(w-215,h-69);
}

/********************************************************************************/
void doSpecialMapAction(int action) {
int i=0;

//printf("doSpecialMapAction: %d\n", action);
	switch (action) {
		case 1:		// mark all as viewed
				if (doAreYouSure("Do you really want to mark ALL as viewed ?") == 1) {
					combatGridMap->getGridTile()->setAllViewed();
					externalGridMap->getGridTile()->redraw();
				}
				break;

		case 2:		// clear map
				if (doAreYouSure("Do you really want to clear the map ?") == 1) {
					combatGridMap->getGridTile()->clearGridMap();
					externalGridMap->getGridTile()->redraw();
					doNotesAction(2);
				}
				break;

		case 3:		// mark the current screen as viewed
				if (doAreYouSure("Do you really want to mark the current screen as viewed ?") == 1) {
					combatGridMap->getGridTile()->setCurrentAsViewed(1);
					externalGridMap->getGridTile()->redraw();
				}
				break;

		case 4:		// remove dead monsters
				if (doAreYouSure("Do you really want to remove all DEAD monsters\nfrom the map ?") == 1) {
					for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) { // && players[i].flags.f_disabled == 0) {
							if (players[i].i_hp[HP_CUR] < 0 && players[i].i_mapX != -1) {
								combatGridMap->getGridTile()->removeObject(players[i].i_mapX, players[i].i_mapY);
							}
						}
					}
				}
				break;

		case 5:		// remove dead monsters and disable them
				if (doAreYouSure("Do you really want to remove all DEAD monsters\n(& disable them) from the map ?") == 1) {
					for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) { // && players[i].flags.f_disabled == 0) {
							if (players[i].i_hp[HP_CUR] < 0 && players[i].i_mapX != -1) {
								combatGridMap->getGridTile()->removeObject(players[i].i_mapX, players[i].i_mapY);
								players[i].flags.f_disabled = 1;
							}
						}
					}
				}
				break;

		case 6:		// remove ALL monsters
				if (doAreYouSure("Do you really want to remove ALL the monsters\nfrom the map ?") == 1) {
					for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) { // && players[i].flags.f_disabled == 0) {
							if (players[i].i_mapX != -1) {
								combatGridMap->getGridTile()->removeObject(players[i].i_mapX, players[i].i_mapY);
							}
						}
					}
				}
				break;

		case 7:		// mark all monsters as unviewed
				for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
						if (players[i].i_mapX != -1) {
							combatGridMap->getGridTile()->setGridPointViewed(players[i].i_mapX, players[i].i_mapY, 0);
							players[i].flags.f_wasViewed = 0;
						}
					}
				}
				break;

		case 8:		// mark the current screen as unviewed
				combatGridMap->getGridTile()->setCurrentAsViewed(0);
				externalGridMap->getGridTile()->redraw();
				break;

		case 9:		// undo previous drawing action
				combatGridMap->getGridTile()->undoMapDrawing(1);
				externalGridMap->getGridTile()->centreMap(-1,-1);		// re-centre the players map
				break;

		case 10:		// reload ALL icons
				doIconAction(1);
				break;

		case 11:		// switch to layer0
				break;

		case 12:		// switch to layer1
				break;

		case 100:
//				if ((iname = fl_file_chooser("Icon File Load", "*.png", players[config.i_editID].c_iconFile, 1)) != NULL) {
				t_IconSelector->value(t_PlayerIcons);
				selectIconUsed();
				if (iconSelected[0] != '\0') {
					aEdit_IconFilename->value(iconSelected); // iname);
				}
				break;
		case 101:
//				if ((iname = fl_file_chooser("Icon File Load", "*.png", iname, 1)) != NULL) {
				t_IconSelector->value(t_MonsterIcons);
				selectIconUsed();
				if (iconSelected[0] != '\0') {
					a_EdtQkMonstIconFilename->value(iconSelected); // iname);
				}
				break;
		case 102:
//				if ((iname = fl_file_chooser("Icon File Load", "*.png", iname, 1)) != NULL) {
				t_IconSelector->value(t_ObjectIcons);
				selectIconUsed();
				if (iconSelected[0] != '\0') {
					a_ObjectIcon->value(iconSelected);
				}
				break;
		case 103:
				t_IconSelector->value(t_MonsterIcons);
				selectIconUsed();
				if (iconSelected[0] != '\0') {
					aQkAdd_Icon->value(iconSelected);
				}
				break;
		case 104:
				t_IconSelector->value(t_PlayerIcons);
				selectIconUsed();
				if (iconSelected[0] != '\0') {
					qkEdit_Icon->value(iconSelected); // iname);
				}
				combatGridMap->repaint();
				externalGridMap->repaint();
				break;
	}
}

/********************************************************************************/
void doNotesAction(int action) {
	int x=0, y=0, i=0;

	a_notesWindow->hide();

	switch (action) {
		case 0:		// add/update
				i = combatGridMap->getClickedGridID();
//printf("dNA: %d\n", i);
				if (i == -1) {
					for (i=0; i<MAX_OBJECTS; i++) {
						if (config.objects[i].c_description[0] == '\0' && config.objects[i].c_iconFile[0] == '\0') {
							break;
						}
					}
				}
				if (i != -1) {
					config.objects[i].i_id = i;
					strncpy(config.objects[i].c_description, a_NotesDescription->value(), MAX_OBJECTDESC-1);
					config.objects[i].c_description[MAX_OBJECTDESC] = '\0';
					strncpy(config.objects[i].c_iconFile, a_ObjectIcon->value(), 59);
					config.objects[i].c_iconFile[59] = '\0';
					config.objects[i].i_width = atoi(a_ObjectWidth->value());
					config.objects[i].i_height = atoi(a_ObjectHeight->value());
					if (config.objects[i].i_height < 5) { config.objects[i].i_height = 5; }
					if (config.objects[i].i_width < 5) { config.objects[i].i_width = 5; }
					x = combatGridMap->getClickedX();
					y = combatGridMap->getClickedY();
					if (mystrcasestr(config.objects[i].c_iconFile, "png") != NULL) {
						objectIcons[i] = new Fl_PNG_Image(config.objects[i].c_iconFile);
					} else {
						objectIcons[i] = new Fl_JPEG_Image(config.objects[i].c_iconFile);
					}
					combatGridMap->getGridTile()->setObjectIcon(i, objectIcons[i]);
					combatGridMap->setGridType(x, y, GRID_OBJECT, i);
//printf("doNotesAction: %d:%s %d:%d at %d/%d\n", i, config.objects[i].c_description, config.objects[i].i_width, config.objects[i].i_height, x, y);
				}
				break;

		case 1:		// delete note
				x = combatGridMap->getClickedGridID();
				if (x < 0 || x > MAX_OBJECTS) { break; }
				config.objects[x].i_id = 0; config.objects[x].c_description[0] = config.objects[x].c_iconFile[0] = '\0';
				x = combatGridMap->getClickedX();
				y = combatGridMap->getClickedY();
				combatGridMap->setGridType(x, y, 0, 0);
				break;

		case 2:		// clear all notes
				for (int i=0; i<MAX_OBJECTS; i++) {
					config.objects[i].c_description[0] = config.objects[i].c_iconFile[0] = '\0';
					config.objects[i].i_id = config.objects[i].i_height = config.objects[i].i_width = 0;
					objectIcons[i] = NULL;
					combatGridMap->getGridTile()->setObjectIcon(i, objectIcons[i]);
				}
				break;
	}
	combatGridMap->getGridTile()->repaint();
}

/********************************************************************************/
void doMapMode(int mode) {

	if (combatGridMap->getGridTile() == NULL) { return; }

	if (mode >= 0) {
		combatGridMap->setMode(mode);
		a_CombatShapes->deactivate();
		a_CombatShapesFill->deactivate();
		a_CombatLayer->deactivate();
		a_CombatShapeWidth->deactivate(); a_CombatShapeHeight->deactivate();
	}

	switch (mode) {
		case ACTION_COMBAT:
			break;

		case ACTION_DOTS:
			break;

		case ACTION_LINE:
			break;

		case ACTION_SHAPES:
			a_CombatShapes->activate(); a_CombatShapes->value(0);
//			a_CombatShapesFill->activate(); a_CombatShapesFill->value(0);
			combatGridMap->getGridTile()->setCurrentShape(0);
			combatGridMap->getGridTile()->setShapeFill(0);
			a_CombatShapeWidth->activate(); a_CombatShapeHeight->activate();
			a_CombatShapesFill->activate();
			break;

		case ACTION_10CORRIDOR:
			break;

		case ACTION_20CORRIDOR :
			break;

		case ACTION_COPYOBJECT:
			break;

		case -1:	// shape selected
			combatGridMap->getGridTile()->setCurrentShape(a_CombatShapes->value());
			a_CombatShapeWidth->activate(); a_CombatShapeHeight->activate();
			break;

		case -2:	// shape outline/fill
			combatGridMap->getGridTile()->setShapeFill(a_CombatShapesFill->value());
			break;

		case -3:	// shape size
			combatGridMap->getGridTile()->setShapeSize((int )a_CombatShapeWidth->value(), (int )a_CombatShapeHeight->value());
			break;

		case -10:		// external screen zoom out
			externalGridMap->setGridSize(-1);
			externalGridMap->getGridTile()->centreMap(-1, -1);		// keep it centred on the same point
			a_TMain->redraw();
			break;

		case -11:		// external screen zoom in
			externalGridMap->setGridSize(+1);
			a_TMain->redraw();
			externalGridMap->getGridTile()->centreMap(-1, -1);		// keep it centred on the same point
			break;

		case -12:		// dm screen zoom out
			combatGridMap->clearlayerLocation();
			combatGridMap->getGridTile()->setMapCentre();
			combatGridMap->setGridSize(-1);
			combatGridMap->getGridTile()->centreMap(-1, -1); // recalc scroll bars
			break;

		case -13:		// dm screen zoom in
			combatGridMap->clearlayerLocation();
			combatGridMap->getGridTile()->setMapCentre();
			combatGridMap->setGridSize(+1);
			combatGridMap->getGridTile()->centreMap(-1, -1); // recalc scroll bars
			break;
	}
}

/********************************************************************************/
void doQkIcon(int type) {
int i=0,j=0, r=0, s=0;

	mybuf1[0] = '\0';

	switch(type) {
		case 0:	// refresh
					a_qkIconList->clear();
					for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
							if ((getHPs(i) < 0 && config.flags.f_showDeadMonsters != 0) || getHPs(i) > -1) {
								a_qkIconList->add(players[i].c_name);
								config.i_idList[ID_QKICON][j++] = i;
							}
						}
					}
					config.i_idList[ID_QKICON][j] = -1;
					a_qkIconIcon->value(""); a_qkIconSpace->value("0"); a_qkIconReach->value("0");
					a_TQkIcon->redraw();
					a_qkIconList->redraw();
					break;

		case 1:	// load icon list
//					if ((iname = fl_file_chooser("Icon File Select", "*.png", mybuf1, 1)) != NULL) {
					selectIconUsed();
					if (iconSelected[0] != '\0') {
						a_qkIconIcon->value(iconSelected); // iname);
					}
					break;

		case 2:	// accept
					s = atoi(a_qkIconSpace->value());
					r = atoi(a_qkIconReach->value());
					for (i=a_qkIconList->nitems(); i>0; i--) {
						if (a_qkIconList->checked(i) == 1) {
							j = config.i_idList[ID_QKICON][i-1];
							strncpy(players[j].c_iconFile, a_qkIconIcon->value(), 59); players[j].c_iconFile[59] = '\0';
							if (s > 0) { players[j].i_space = s; }
							if (r > 0) { players[j].i_reach = r; }
						}
					}
					doIconAction(1);
					doQkIcon(0);
					break;
	}
}

/********************************************************************************/
void doRndsDecrement(int val) {
int i=0;

	for (i=0; i<MAX_TRIGGERS; i++) {
		if (config.action_msgs[i].i_noRounds > 0) {
			config.action_msgs[i].i_noRounds -= val;
			if (config.action_msgs[i].i_noRounds < 0) { 
				config.action_msgs[i].i_noRounds = 0;
				config.action_msgs[i].i_display = 0;
				config.action_msgs[i].c_every[0] = '\0';
				sprintf(config.action_msgs[i].c_message, "-- empty slot %d", i);
			}
		}
	}

	for (i=0; i<MAX_MODIFIERS; i++) {
		if (config.action_mods[i].i_noRounds > 0) {
			config.action_mods[i].i_noRounds -= val;
			if (config.action_mods[i].i_noRounds < 0) {
				config.action_mods[i].i_noRounds = 0;
				sprintf(config.action_mods[i].c_message, "-- empty slot %d", i);
				config.action_mods[i].i_whom[0] = config.action_mods[i].i_whom[1] = config.action_mods[i].i_idFollows = -255;
				config.action_mods[i].i_data[0][0] = config.action_mods[i].i_data[0][2] = 0; config.action_mods[i].i_data[0][1] = -1;
				config.action_mods[i].i_data[1][0] = config.action_mods[i].i_data[1][2] = 0; config.action_mods[i].i_data[1][1] = -1;
				config.action_mods[i].i_data[2][0] = config.action_mods[i].i_data[2][2] = 0; config.action_mods[i].i_data[2][1] = -1;
				config.action_mods[i].i_data[3][0] = config.action_mods[i].i_data[3][2] = 0; config.action_mods[i].i_data[3][1] = -1;
				config.action_mods[i].i_data[4][0] = config.action_mods[i].i_data[4][2] = 0; config.action_mods[i].i_data[4][1] = -1;
			}
		}
	}
	doAdjustmentAction(9);		// refresh the list
	doTriggerAction(9);		// refresh the list
}

/********************************************************************************/
static void cb_acceptPlayerIcon(Fl_Button *b, void *) {
	a_IconWindow->hide();
	sprintf(iconSelected, "icons/player/%s\n", (char *)b->tooltip());
//printf("caPI: %s\n", iconSelected);
}

static void cb_acceptMonsterIcon(Fl_Button *b, void *) {
	a_IconWindow->hide();
	sprintf(iconSelected, "icons/monster/%s\n", (char *)b->tooltip());
//printf("caMI: %s\n", iconSelected);
}

static void cb_acceptObjectIcon(Fl_Button *b, void *) {
	a_IconWindow->hide();
	sprintf(iconSelected, "icons/objects/%s\n", (char *)b->tooltip());
//printf("caMI: %s\n", iconSelected);
}

static void cb_acceptAnimalIcon(Fl_Button *b, void *) {
	a_IconWindow->hide();
	sprintf(iconSelected, "icons/animals/%s\n", (char *)b->tooltip());
//printf("caMI: %s\n", iconSelected);
}

static void cb_acceptOtherIcon(Fl_Button *b, void *) {
	a_IconWindow->hide();
	sprintf(iconSelected, "icons/other/%s\n", (char *)b->tooltip());
//printf("caMI: %s\n", iconSelected);
}

/********************************************************************************/
void loadAllIconPictures(char *dir, int type) {
int num_entries=0, i=0, x=0, y=0, xp, ic=0, ji=0, pi=0, bi=0;
char *cp, in[70];
struct dirent **list;

//	num_entries = fl_filename_list(dir, &list, fl_casealphasort);
	num_entries = scandir(dir, &list, NULL, alphasort);
//printf("aAIP: dir = %s:%d\n", dir, num_entries);
	if (num_entries < 3) { return; }
//	list++; list++;
	for (i=2; i<num_entries; i++) {
		cp = (*list)->d_name;
//		cp = list[i]->d_name;
//printf("aAIP: file = %s : %d\n", cp, i);
// jpeg images not working : for i in `ls *.j*`; do f=`echo "$i" | cut -f1 -d"."`; convert $i $f.png; done
//		if (mystrcasestr(cp, "png") != NULL || mystrcasestr(cp, "jpg") != NULL) {
		if (mystrcasestr(cp, "png") != NULL) {
			xp = 10 + (x * 68);
			sprintf(in, "%s/%s", dir, cp);
			buttonIcons[bi] = new Fl_Button(xp, (y * 68), 66, 66); buttonIcons[bi]->tooltip(cp);
			if (mystrcasestr(cp, "png") != NULL) {
				pngIcons[pi] = new Fl_PNG_Image(in);
//printf("aAIP: png = %s\n", cp);
				if (pngIcons[pi]->w() > 64 || pngIcons[pi]->h() > 64) {
					selectIcons[ic] = pngIcons[pi]->copy(62,62); buttonIcons[bi]->image(selectIcons[ic]); ic++;
				} else { buttonIcons[bi]->image(pngIcons[pi]); }
				pi++;
			} else {
				jpgIcons[ji] = new Fl_JPEG_Image(in);
//printf("aAIP: jpg = %s (%d:%d)\n", in, jpgIcons[ji]->w(), jpgIcons[ji]->h());
				if (jpgIcons[ji]->w() > 64 || jpgIcons[ji]->h() > 64) {
					selectIcons[ic] = jpgIcons[ji]->copy(62,62); buttonIcons[bi]->image(selectIcons[ic]); ic++;
				} else { buttonIcons[bi]->image(jpgIcons[ji]); }
				ji++;
			}

			switch (type) {
				case 0: s_PlayerIcons->add(buttonIcons[bi]);
							buttonIcons[bi]->callback((Fl_Callback*)cb_acceptPlayerIcon);
						break;
				case 1: s_MonsterIcons->add(buttonIcons[bi]);
							buttonIcons[bi]->callback((Fl_Callback*)cb_acceptMonsterIcon);
						break;
				case 2: s_ObjectIcons->add(buttonIcons[bi]);
							buttonIcons[bi]->callback((Fl_Callback*)cb_acceptObjectIcon);
						break;
				case 3: s_AnimalIcons->add(buttonIcons[bi]);
							buttonIcons[bi]->callback((Fl_Callback*)cb_acceptAnimalIcon);
						break;
				case 4: s_OtherIcons->add(buttonIcons[bi]);
							buttonIcons[bi]->callback((Fl_Callback*)cb_acceptOtherIcon);
						break;
			}
			x++; if (x > 13) { x = 0; y++; }
			bi++;
		}
//printf("lAIP: %s\n", cp);
		list++;
	}
//	if (pimage != NULL) { delete pimage; }
//	if (jimage != NULL) { delete jimage; }
//	if (resizedImage != NULL) { delete resizedImage; }
	selectIcons[ic] = NULL; selectIcons[ic+1] = NULL;
	pngIcons[pi] = NULL; pngIcons[pi+1] = NULL;
	jpgIcons[ji] = NULL; jpgIcons[ji+1] = NULL;
	buttonIcons[bi] = NULL; buttonIcons[bi+1] = NULL;
}

/********************************************************************************/
void selectIconUsed() {
	iconSelected[0] = '\0';
	a_IconWindow->show();
	while (a_IconWindow->shown()) Fl::wait();
	for (int i=0; i<59; i++) { if (iconSelected[i] < 31) { iconSelected[i] = '\0'; break; } }
}

/********************************************************************************/
void setWindowTitles() {
struct tm *tp;
time_t t;
char mybuf1[512];

	if (time(&t) != -1) {
		tp = localtime(&t);
		sprintf(mybuf1, "VCS Main Window, v%.2f by Torquil Gault, Copyright 2005+       Round: %d @ %2.2d:%2.2d", ADMPversion, config.i_roundCount, tp->tm_hour, tp->tm_min);
		a_MainWindow->label(mybuf1);
		sprintf(mybuf1, "VCS Player Window, v%.2f by Torquil Gault, Copyright 2005+       Round: %d @ %2.2d:%2.2d", ADMPversion, config.i_roundCount, tp->tm_hour, tp->tm_min);
		a_WExternalGridMap->label(mybuf1);
	}
}

/********************************************************************************/
void selectQkAddEditWeapon(int w) {
	int i = MAX_MEMBERS+3;
	char buf[10];

	if (i_prevWeaponEditted != -1) {		// save the previous weapon details
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_description, aQkAdd_WeaponName->value(), 29);
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[0] = atoi(aQkAdd_WeaponAttkBonus1->value());
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[1] = atoi(aQkAdd_WeaponAttkBonus2->value());
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[2] = atoi(aQkAdd_WeaponAttkBonus3->value());
		players[i].w_weapons[i_prevWeaponEditted].i_attackBonus[3] = atoi(aQkAdd_WeaponAttkBonus4->value());
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_damage, aQkAdd_WeaponDamage->value(), 19);
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_critical, aQkAdd_WeaponCritical->value(), 19);
		players[i].w_weapons[i_prevWeaponEditted].i_magicalBonus = atoi(aQkAdd_WeaponMagicBonus->value());
		players[i].w_weapons[i_prevWeaponEditted].i_range = atoi(aQkAdd_WeaponRange->value());
		players[i].w_weapons[i_prevWeaponEditted].i_reach = atoi(aQkAdd_WeaponReach->value());
		players[i].w_weapons[i_prevWeaponEditted].i_noAttacks = atoi(aQkAdd_WeaponNoAttacks->value());
		strncpy(players[i].w_weapons[i_prevWeaponEditted].c_message, aQkAdd_WeaponSpecialMessage->value(), 39);
		players[i].w_weapons[i_prevWeaponEditted].c_message[39] = '\0';
		players[i].w_weapons[i_prevWeaponEditted].c_description[29] = '\0';
		players[i].w_weapons[i_prevWeaponEditted].c_damage[19] = '\0';
		players[i].w_weapons[i_prevWeaponEditted].c_critical[19] = '\0';
		if (players[i].w_weapons[i_prevWeaponEditted].c_description[0] != '\0') {
			aQkAdd_WeaponSelector->text(i_prevWeaponEditted+1, players[i].w_weapons[i_prevWeaponEditted].c_description);
		}
//		players[i].w_weapons[i_prevWeaponEditted].c_attackType = aQkAdd_WeaponType->value();
	}
//	aQkAdd_WeaponAvailable->activate(); aQkAdd_WeaponAvailable->value(players[i].w_weapons[w].c_available);
	aQkAdd_WeaponName->activate(); aQkAdd_WeaponName->value(players[i].w_weapons[w].c_description);
	aQkAdd_WeaponSearch->activate();
	aQkAdd_WeaponAttkBonus1->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[0]); aQkAdd_WeaponAttkBonus1->value(buf);
	aQkAdd_WeaponAttkBonus2->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[1]); aQkAdd_WeaponAttkBonus2->value(buf);
	aQkAdd_WeaponAttkBonus3->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[2]); aQkAdd_WeaponAttkBonus3->value(buf);
	aQkAdd_WeaponAttkBonus4->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_attackBonus[3]); aQkAdd_WeaponAttkBonus4->value(buf);
	aQkAdd_WeaponDamage->activate(); aQkAdd_WeaponDamage->value(players[i].w_weapons[w].c_damage);
	aQkAdd_WeaponCritical->activate(); aQkAdd_WeaponCritical->value(players[i].w_weapons[w].c_critical);
	aQkAdd_WeaponMagicBonus->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_magicalBonus); aQkAdd_WeaponMagicBonus->value(buf);
	aQkAdd_WeaponRange->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_range); aQkAdd_WeaponRange->value(buf);
	aQkAdd_WeaponReach->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_reach); aQkAdd_WeaponReach->value(buf);
	aQkAdd_WeaponNoAttacks->activate(); sprintf(buf, "%d", players[i].w_weapons[w].i_noAttacks); aQkAdd_WeaponNoAttacks->value(buf);
	aQkAdd_WeaponSpecialMessage->activate(); aQkAdd_WeaponSpecialMessage->value(players[i].w_weapons[w].c_message);
//	aQkAdd_WeaponType->activate(); aQkAdd_WeaponType->value(players[i].w_weapons[w].c_attackType);
	i_prevWeaponEditted = w;
}
	
/********************************************************************************/
void doIconAction(int action) {
	switch (action) {
		case 1:
				for (int i=0; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) { // && players[i].flags.f_disabled == 0) {
						if (players[i].c_iconFile[0] != '\0') {
							if (mystrcasestr(players[i].c_iconFile, "png") != NULL) {
								if (playerIcons[i] != NULL) { delete playerIcons[i]; }
								playerIcons[i] = new Fl_PNG_Image(players[i].c_iconFile);
							} else {
								if (playerIcons[i] != NULL) { delete playerIcons[i]; }
								playerIcons[i] = new Fl_JPEG_Image(players[i].c_iconFile);
							}
							combatGridMap->setPlayerIcon(i, playerIcons[i]);
//printf("dIA: %d = %s %d/%d :%ld\n", i, players[i].c_iconFile, playerIcons[i]->w(), playerIcons[i]->h(), playerIcons[i]);
						}
					} else {
						if (playerIcons[i] != NULL) { delete playerIcons[i]; }
						playerIcons[i] = NULL;
						combatGridMap->setPlayerIcon(i, NULL);
					}
				}
				combatGridMap->getGridTile()->repaint();
				externalGridMap->getGridTile()->repaint();
				break;

		case 2:
				for (int i=0; i<MAX_MEMBERS; i++) {
					if (playerIcons[i] != NULL) { delete playerIcons[i]; }
					playerIcons[i] = NULL;
				}
				break;

		case 3:
				for (int i=0; i<MAX_OBJECTS; i++) {
					if (config.objects[i].c_iconFile[0] != '\0') {
//printf("dIA: 3: %d %s|\n", i, config.objects[i].c_iconFile);
//#ifdef CYGWIN
//						if (strstr(config.objects[i].c_iconFile, "png") != NULL || strstr(config.objects[i].c_iconFile, "PNG") != NULL) {
//#else
						if (mystrcasestr(config.objects[i].c_iconFile, "png") != NULL) {
//#endif
							objectIcons[i] = new Fl_PNG_Image(config.objects[i].c_iconFile);
//							setIconImage(objectIcons[i], config.objects[i].c_iconFile, 'P');
						} else {
							objectIcons[i] = new Fl_JPEG_Image(config.objects[i].c_iconFile);
//							setIconImage(objectIcons[i], config.objects[i].c_iconFile, 'J');
						}
						combatGridMap->getGridTile()->setObjectIcon(i, objectIcons[i]);
					}
				}
				break;
	}
}

/********************************************************************************/
void doCopyWeaponDetails(int action) {
int i=0, j=0, k=0, x=-1, y=-1;
char name[50], icon[70];

//printf("dCWD: %d\n", action);
	switch (action) {
		case 0:			// refresh
				config.i_idList[ID_WEAPONCOPY][0] = config.i_idList[ID_WEAPONCOPY][1] = config.i_idList[ID_WEAPONCOPY][2] = -1;
				mWC_FromList->clear();
				mWC_FromList->activate();
				mWC_ToList->clear();
				j=0;
				for (i=0; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
						if (i >= MAX_PLAYERS) {
							if ((getHPs(i) < 0 && config.flags.f_showDeadMonsters != 0) || getHPs(i) > -1) {
								mWC_FromList->add(players[i].c_name);
								mWC_ToList->add(players[i].c_name);
								config.i_idList[ID_WEAPONCOPY][j++] = i;
							}
						} else {
							mWC_FromList->add(players[i].c_name);
							mWC_ToList->add(players[i].c_name);
							config.i_idList[ID_WEAPONCOPY][j++] = i;
						}
					}
				}
				config.i_idList[ID_WEAPONCOPY][j] = -1;
				mWC_FromList->redraw();
				mWC_ToList->redraw();
				break;

		case 1:			// copy weapon details
				i=mWC_FromList->nitems(); j = -1;
				for (; i>0; i--) { if (mWC_FromList->checked(i) == 1) { j = config.i_idList[ID_WEAPONCOPY][i-1]; break; } }
				if (j != -1) {
					i=mWC_ToList->nitems();
					for (; i>0; i--) { 
						if (mWC_ToList->checked(i) == 1) {
							k = config.i_idList[ID_WEAPONCOPY][i-1];
							memcpy(&players[k].w_weapons[0].c_available, &players[j].w_weapons[0].c_available, sizeof(ADMPweapon) * MAX_ATTACKS);
						}
					}
				}
				doCopyWeaponDetails(0);
				break;

		case 2:			// copy ALL details
				i=mWC_FromList->nitems(); j = -1;
				for (; i>0; i--) { if (mWC_FromList->checked(i) == 1) { j = config.i_idList[ID_WEAPONCOPY][i-1]; break; } }
				if (j != -1) {
					i=mWC_ToList->nitems();
					for (; i>0; i--) { 
						if (mWC_ToList->checked(i) == 1) {
							k = config.i_idList[ID_WEAPONCOPY][i-1];
							x = players[k].i_mapX; y = players[k].i_mapY;
							strcpy(name, players[k].c_name);
							strcpy(icon, players[k].c_iconFile);
							memcpy(&players[k].c_name[0], &players[j].c_name[0], sizeof(ADMPplayer));
							players[k].i_mapX = x; players[k].i_mapY = y;
							strcpy(players[k].c_name, name);
							strcpy(players[k].c_iconFile, icon);
						}
					}
				}
				doCopyWeaponDetails(0);
				break;
	}
}

/********************************************************************************/
int readSpellData() {

//printf("readSpellData - %s", pdbDataLine);
	pdbTokenize(pdbDataLine);

//	i_dummy = pdbGetInt();
	spells[qkMonster].i_type = pdbGetInt();
	spells[qkMonster].i_level = pdbGetInt();
	strncpy(&spells[qkMonster].c_spell[0], pdbGetString(), 109); spells[qkMonster].c_spell[109] = '\0';
	spells[qkMonster].i_attack = pdbGetInt();
	spells[qkMonster].i_defend = pdbGetInt();
	if (spells[qkMonster].i_attack == 0 && spells[qkMonster].i_defend == 0) {
		spells[qkMonster].i_attack = getRND(100); 
		spells[qkMonster].i_defend = 100 - spells[qkMonster].i_attack;
		if (spells[qkMonster].i_defend < 0) { spells[qkMonster].i_defend = 0; }
	}
//printf("%d/%d (%d/%d) = %s\n", spells[qkMonster].i_type, spells[qkMonster].i_level, spells[qkMonster].i_attack, spells[qkMonster].i_defend, spells[qkMonster].c_spell);
	qkMonster++;

	return 0;
}

/********************************************************************************/
void loadAllSpells(char *fname) {
	qkMonster = 0;
	pdbLoadAll(fname, readSpellData);
}

/********************************************************************************/
int readSpellSlotData() {
char *c_dummy;

//printf("readSpellSlotData - %s", pdbDataLine);
	pdbTokenize(pdbDataLine);

//	i_dummy = pdbGetInt();
	spellslots[qkMonster].i_level = pdbGetInt();
	spellslots[qkMonster].i_type = pdbGetInt();
	c_dummy = pdbGetString();		// attack bonus
	c_dummy = pdbGetString();		// saves
	c_dummy = pdbGetString();		// saves
	c_dummy = pdbGetString();		// saves
	c_dummy = pdbGetString();		// 0th level spells
	strcpy(&spellslots[qkMonster].c_spellslots[0][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[1][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[2][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[3][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[4][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[5][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[6][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[7][0], pdbGetString());
	strcpy(&spellslots[qkMonster].c_spellslots[8][0], pdbGetString());
//printf("readSpellSlotData - %d/%d = %s\n", spellslots[qkMonster].i_type, spellslots[qkMonster].i_level, &spellslots[qkMonster].c_spellslots[0][0]);
	qkMonster++;

	return 0;
}

/********************************************************************************/
void loadAllSpellSlots(char *fname) {
	qkMonster = 0;
	pdbLoadAll(fname, readSpellSlotData);
}

/********************************************************************************/
void generateSpellList(int type, int level, int nospells) {
int rnd, nspells, sslot, i, ar, dr, ra, rd;

//printf("generateSpellList: %d %d %d\n", type, level, nospells);
	if (nospells < 1) { return; }

	ar = atoi(qsl_AttackRating->value());
	dr = atoi(qsl_DefenceRating->value());

		// find the no spells in that level and where they start from
	nspells = 0; sslot = MAX_SPELLS;
	for (i=0; i<MAX_SPELLS; i++) { 
		if (spells[i].i_type == type && spells[i].i_level == level) {
			nspells++; if (sslot > i) { sslot = i; } 
		}
		spells[i].i_used = (nospells / 4) + 1;
	}

	sprintf(mybuf1, "     Level %d\n", level); qsl_spellLists->insert(mybuf1);

	i = 0;
	while (nospells > 0) {
		rnd = getRND(nspells) + sslot;
		ra = getRND(ar); rd = getRND(dr);
		if (spells[rnd].i_attack == 0) { ra = -10; }
		if (spells[rnd].i_defend == 0) { rd = -10; }
//printf("%d = %d/%d = %d/%d = %d/%d\n", rnd, spells[rnd].i_attack, spells[rnd].i_defend, ra, rd, ar, dr);
		if ((ra <= spells[rnd].i_attack || rd <= spells[rnd].i_defend) && spells[rnd].i_used > 0) {
			qsl_spellLists->insert(&spells[rnd].c_spell[0]);
			spells[rnd].i_used--;
//printf("generateSpellList = %d %s\n", rnd, &spells[rnd].c_spell[0]);
			nospells--;
			qsl_spellLists->insert("\n");
		}
		i++; if (i > 30) { break; }	// after 30 times break out
	}
	qsl_spellLists->insert("\n");
}

/********************************************************************************/
void doSpellLists(int action) {
int i,j,k;

	switch (action) {
		case 0:
				qsl_spellLists->replace(0, qsl_spellLists->size(), " ", 1);
				qsl_spellLists->value("");
				qsl_spellsLevel1->value("0");
				qsl_spellsLevel2->value("0");
				qsl_spellsLevel3->value("0");
				qsl_spellsLevel4->value("0");
				qsl_spellsLevel5->value("0");
				qsl_spellsLevel6->value("0");
				qsl_spellsLevel7->value("0");
				qsl_spellsLevel8->value("0");
				qsl_spellsLevel9->value("0");
				if (strlen(&spellslots[0].c_spellslots[0][0]) == 0 || strlen(&spells[0].c_spell[0]) == 0) {
					loadAllSpells("stdspells.spd");
					loadAllSpellSlots("stdspslots.std");
				}
				i = (int )qsl_castertype->value();
				j = (int )qsl_casterlevel->value();
				for (k=0; k<MAX_SPELLSLOTS; k++) {
					if (spellslots[k].i_type == i && spellslots[k].i_level == j) {
						qsl_spellsLevel1->value(&spellslots[k].c_spellslots[0][0]);
						qsl_spellsLevel2->value(&spellslots[k].c_spellslots[1][0]);
						qsl_spellsLevel3->value(&spellslots[k].c_spellslots[2][0]);
						qsl_spellsLevel4->value(&spellslots[k].c_spellslots[3][0]);
						qsl_spellsLevel5->value(&spellslots[k].c_spellslots[4][0]);
						qsl_spellsLevel6->value(&spellslots[k].c_spellslots[5][0]);
						qsl_spellsLevel7->value(&spellslots[k].c_spellslots[6][0]);
						qsl_spellsLevel8->value(&spellslots[k].c_spellslots[7][0]);
						qsl_spellsLevel9->value(&spellslots[k].c_spellslots[8][0]);
					}
				}
				break;

		case 1:		// generate a random spell list
				qsl_spellLists->replace(0, qsl_spellLists->size(), " ", 1);
				qsl_spellLists->value("");
				i = (int )qsl_castertype->value();
				generateSpellList(i, 1, atoi(qsl_spellsLevel1->value()));
				generateSpellList(i, 2, atoi(qsl_spellsLevel2->value()));
				generateSpellList(i, 3, atoi(qsl_spellsLevel3->value()));
				generateSpellList(i, 4, atoi(qsl_spellsLevel4->value()));
				generateSpellList(i, 5, atoi(qsl_spellsLevel5->value()));
				generateSpellList(i, 6, atoi(qsl_spellsLevel6->value()));
				generateSpellList(i, 7, atoi(qsl_spellsLevel7->value()));
				generateSpellList(i, 8, atoi(qsl_spellsLevel8->value()));
				generateSpellList(i, 9, atoi(qsl_spellsLevel9->value()));
				qsl_spellLists->redraw();
				break;
	}
}

/********************************************************************************/
void doSpellEnergyType(int action) {
int i=0;

//printf("doSpellEnergyType: %d/%d\n", action, a_CTSpellEnergyType->value());

	switch (action) {
		case 0:		// selection a_CTSpellEnergyType
				i = a_CTSpellEnergyType->value();
				a_CTSpellEnergyType->check_none();
				a_CTSpellEnergyType->checked(i, 1);
				break;
	}
}

/********************************************************************************/
extern treasureTblData rndTreasureTblData[];
extern void parseTreasureData(int , int , Fl_Text_Display *);
extern int findTreasureLine(int , int );

void doMagicItemGeneration() {
int i=aRT_ItemCount->value(), t=aRT_ItemType->value()-1, r, l, p;
int tbl[3][8] = {{376, 379, 379, 375, 374, 377, 378, 380},		// match aRT_ItemType
					  {383, 388, 387, 382, 381, 384, 386, 389},
					  {392, 397, 396, 391, 390, 393, 395, 398}};
				//None,Potion,Wand,Staff,Weapon,Armour,Rings,Scroll,Wonderous

int plus[3][10] = {{0,0,1,1,1,1,1,1,2,2}, {1,1,1,2,2,2,2,2,3,3}, {1,2,2,2,3,3,3,3,4,4}};

int awtbl[3][2] = {{92, 157}, {93, 157}, {94, 157}};
int eptbl[3][2] = {{98, 161}, {97, 160}, {96, 159}};

char *cp;

	treasure_buffer[1]->select(0, treasure_buffer[1]->length());
	treasure_buffer[1]->remove_selection();

	p = getRND(3) - 1; 		// pick a rnd power level
	if (i == 0 || t < 0) { return; }

//printf("dMIG: %d %d %d = %d\n", i, t, r, tbl[p][t]);

	for (; i>0; i--) {
		if (t == 4 || t == 3) {		// handle weapons & armor differently as it does weird stuff currently ....
			l = findTreasureLine(awtbl[p][t-3], getRND(100));
			strcpy(mybuf1, rndTreasureTblData[l].data); 
			if ((cp = strstr(mybuf1, "|")) != NULL) { *cp = '\0'; }
			r = getRND(10) - 1;
			if (getRND(100) > 95) {
				l = findTreasureLine(eptbl[p][t-3], getRND(100));
				strcat(mybuf1, " :: ");
				strcat(mybuf1, rndTreasureTblData[l].data); 
			}
			sprintf(mybuf2, "+%d %s", plus[p][r], mybuf1);
			treasure_buffer[1]->append(mybuf2);
			treasure_buffer[1]->append("\n");
		} else {
			parseTreasureData(tbl[p][t], 0, aRT_ItemList);
		}
		p = getRND(3) - 1; 		// pick a rnd power level
	}

}

/********************************************************************************/
void doHealMonsters(int action) {
int x, y, i, j, x1, y1, x2, y2;
char hp[100];

	switch(action) {
		case 0:		// refresh list
					for (i=0; i<MAX_HEALMONSTERS; i++) {
                  i_HealMonstName[i]->value("");
                  i_HealMonstName[i]->deactivate();
                  i_HealMonstValue[i]->value("");
                  i_HealMonstValue[i]->deactivate();
					}

					x = 0;
					for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
							sprintf(hp, "%s (%d/%d)", players[i].c_name, getHPs(i), players[i].i_hp[HP_MAX]); 
							i_HealMonstName[x]->value(hp);
							i_HealMonstValue[x]->value("");

                  	i_HealMonstName[x]->deactivate();
                  	i_HealMonstValue[x]->activate();
							config.i_idList[ID_HEALMONSTER][x] = i;
							x++;
							if (x >= MAX_HEALMONSTERS) { break; }
						}
					}
					config.i_idList[ID_HEALMONSTER][x] = config.i_idList[ID_HEALMONSTER][x+1] = -1;
					iHM_allMonsters->value("");

					break;

		case 1:		// accept
					j = atoi(iHM_allMonsters->value());
					for (i=0; i<MAX_HEALMONSTERS; i++) {
						if ((x = config.i_idList[ID_HEALMONSTER][i]) != -1) {
							if (j != 0) {
								players[x].i_hp[HP_CUR] += j;
							} else {
								players[x].i_hp[HP_CUR] += atoi(i_HealMonstValue[i]->value());
							}
							if (players[x].i_hp[HP_CUR] > players[x].i_hp[HP_MAX]) { players[x].i_hp[HP_CUR] = players[x].i_hp[HP_MAX]; }
						} else {
							break;
						}
						i_HealMonstName[i]->value("");
						i_HealMonstValue[i]->value("");
					}
					iHM_allMonsters->value("");
					config.i_idList[ID_HEALMONSTER][0] = config.i_idList[ID_HEALMONSTER][1] = -1;
					doHealMonsters(0);

					break;

		case 9:		// setup screen
					x1 = gHM_Monsters->x(); x2 = gHM_Monsters->w();
					y1 = gHM_Monsters->y(); y2 = gHM_Monsters->h();
					x = x1+10; y = y1+10;

					for (i=0; i<MAX_HEALMONSTERS; i++) {
						i_HealMonstName[i] = new Fl_Input(x, y, 250, 25);
                  i_HealMonstName[i]->type(0);
                  i_HealMonstName[i]->labelsize(ADMP_LABEL_SIZE);
                  i_HealMonstName[i]->textsize(ADMP_TEXT_SIZE);
                  i_HealMonstName[i]->deactivate();
						gHM_Monsters->add(i_HealMonstName[i]);

						i_HealMonstValue[i] = new Fl_Input(x+255, y, 30, 25);
                  i_HealMonstValue[i]->type(2);
                  i_HealMonstValue[i]->labelsize(ADMP_LABEL_SIZE);
                  i_HealMonstValue[i]->textsize(ADMP_TEXT_SIZE);
                  i_HealMonstValue[i]->deactivate();
						gHM_Monsters->add(i_HealMonstValue[i]);

						y += 30;
						if (y > (y1+y2-30)) { y = y1+10; x += (x2 / 3); }
					}
					break;
	}
}

/********************************************************************************/
int isDead(int p) {
int h=-10;

	if (config.flags.f_deathAtCON == 1) {
		if (players[p].i_abilityStats[1][ABILITY_CON] != 0) {
			h = players[p].i_abilityStats[1][ABILITY_CON] * -1;
		} else if (players[p].i_abilityStats[0][ABILITY_CON] != 0) {
			h = players[p].i_abilityStats[0][ABILITY_CON] * -1;
		}
	}
//printf("iD: %d = %d\n", p, h);
	if (getHPs(p) <= h) { return 1; }		// they are DEAD

	return 0;
}

/********************************************************************************/
int isDefenderShown(int d) {
int j=0;

	while (config.i_idList[ID_DEFD][j] != -1) {
		if (config.i_idList[ID_DEFD][j] == d) { return j; }
		j++;
	}
	doSystemAlert("Please select a Defender before continuing !!!");
	return -1;
}

/********************************************************************************/
void doDisableAction(int action) {
int i=0, j=0;

//printf("dDAA: %d = %d:%d\n", action, a_OTDisableActionList->value(), a_OTDisableList->nitems());

	switch (action) {
		case 0:		// action list selection. only allow 1
			i = a_OTDisableActionList->value();
			a_OTDisableActionList->check_none();
			a_OTDisableActionList->set_checked(i);
			break;

		case -1:		// refresh list
			a_OTDisableList->clear();

			for (i=0; i<MAX_MEMBERS; i++) {
				if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
					a_OTDisableList->add(players[i].c_name);
					config.i_idList[ID_DISA][j++] = i;
				}
			}
	
			a_OTDisableList->redraw();
			break;

		default:		// do the action selected
			i=a_OTDisableList->nitems();

			switch (a_OTDisableActionList->value()) {
				case 1:		// Disable selected
						for (; i>0; i--) {
							if (a_OTDisableList->checked(i) == 1) {
								j = config.i_idList[ID_DISA][i-1];
								players[j].flags.f_disabled = 1;
							}
						}
						break;
		
				case 2:		// Enable selected
						for (; i>0; i--) {
							if (a_OTDisableList->checked(i) == 1) {
								j = config.i_idList[ID_DISA][i-1];
								players[j].flags.f_disabled = 0;
							}
						}
						break;
		
				case 3:	// remove from map
						for (; i>0; i--) {
		   				if (a_OTDisableList->checked(i) == 1) {
								j = config.i_idList[ID_DISA][i-1];
								combatGridMap->getGridTile()->removeObject(players[j].i_mapX, players[j].i_mapY);
								players[j].i_mapX = players[j].i_mapY = -1;
							}
						}
						break;
		
				case 4:	// set as hidden
						for (; i>0; i--) {
							if (a_OTDisableList->checked(i) == 1) {
								j = config.i_idList[ID_DISA][i-1];
								players[j].flags.f_invisible = 1;
							}
						}
						break;
		
				case 5:	// set as visible
						for (; i>0; i--) {
							if (a_OTDisableList->checked(i) == 1) {
								j = config.i_idList[ID_DISA][i-1];
								players[j].flags.f_invisible = 0;
							}
						}
						break;
		
				case 6:	// delete selected
//						doEditSpecialActions(-2);
					if (doAreYouSure("Are you sure ?") == 1) {
						i=a_OTDisableList->nitems();
	
						for (; i>0; i--) {
							if (a_OTDisableList->checked(i) == 1) {
									j = config.i_idList[ID_DISA][i-1];
					  				if (players[j].i_mapX > 0) {
										combatGridMap->getGridTile()->removeObject(players[j].i_mapX, players[j].i_mapY);
										players[j].i_mapX = players[j].i_mapY = -1;
									}
									memset(&players[j].c_name[0], '\0', sizeof(ADMPplayer));
								}
						}
						externalGridMap->repaint();
	
						reloadNames(0);
	
						doDisableAction(-1);		// refresh the list
					}
						break;
		
				case 7:	// resequence ID's
//						doEditSpecialActions(-1);
					  for (i=0; i<MAX_PLAYERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d\n", i); }
					  			for (j=0; j<MAX_PLAYERS && j < i; j++) {
									if (players[j].c_name[0] == '\0' && players[j].i_hp[HP_MAX] == 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d %d\n", i, j); }
										memcpy(&players[j].c_name[0], &players[i].c_name[0], sizeof(ADMPplayer));
										players[j].c_name[0] = identifiers[j];
										memset(&players[i].c_name[0], '\0', sizeof(ADMPplayer));
					  					players[i].flags.f_disabled = 1;
										if (players[j].i_mapX > 0) {
											combatGridMap->getGridTile()->setGridPointId(players[j].i_mapX, players[j].i_mapY, j);
										}
										break;
									}
								}
							}
					  }
					  for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d\n", i); }
					  			for (j=MAX_PLAYERS; j<MAX_MEMBERS && j < i; j++) {
									if (players[j].c_name[0] == '\0' && players[j].i_hp[HP_MAX] == 0) {
if (config.flags.f_debug != 0) { printf("dESA: 5 %d %d\n", i, j); }
										memcpy(&players[j].c_name[0], &players[i].c_name[0], sizeof(ADMPplayer));
										players[j].c_name[0] = identifiers[j];
										memset(&players[i].c_name[0], '\0', sizeof(ADMPplayer));
					  					players[i].flags.f_disabled = 1;
										if (players[j].i_mapX > 0) {
											combatGridMap->getGridTile()->setGridPointId(players[j].i_mapX, players[j].i_mapY, j);
										}
										break;
									}
								}
							}
					  }
					  doIconAction(1);
					  doDisableAction(-1);		// refresh the list
					  break;
			}
			break;
	}
}

/********************************************************************************/
int doQuickMods(int action, int pid, int type) {
int i=0, x=10, y=110, j=0;

//printf("dQM: %d %d %d\n", action, pid, type);

	switch (action) {
		case -2:		// setup the screen input fields etc
				for (i=0; i<MAX_QUICKMODIFIERS; i++) {
					quickmodsName[i] = new Fl_Output(x, y, 215, 25);
					quickmodsData[i][0] = new Fl_Input(x+220, y, 28, 25);
					quickmodsData[i][1] = new Fl_Input(x+250, y, 28, 25);
					quickmodsData[i][2] = new Fl_Input(x+280, y, 28, 25);
					quickmodsData[i][3] = new Fl_Input(x+310, y, 28, 25);
					quickmodsData[i][4] = new Fl_Input(x+340, y, 28, 25);
					quickmodsData[i][5] = new Fl_Input(x+370, y, 28, 25);
					quickmodsData[i][6] = new Fl_Input(x+400, y, 28, 25);
					quickmodsData[i][7] = new Fl_Input(x+430, y, 28, 25);
/*
					quickmodsData[i][0] = new Fl_Input(x+220, y, 40, 25);
					quickmodsData[i][1] = new Fl_Input(x+265, y, 40, 25);
					quickmodsData[i][2] = new Fl_Input(x+310, y, 40, 25);
					quickmodsData[i][3] = new Fl_Input(x+355, y, 40, 25);
					quickmodsData[i][4] = new Fl_Input(x+400, y, 40, 25);
					quickmodsData[i][5] = new Fl_Input(x+445, y, 40, 25);
*/
					for (j=0; j<MAX_QUICKMODTYPES; j++) {
						quickmodsData[i][j]->type(2);
						quickmodsData[i][j]->labelsize(ADMP_LABEL_SIZE);
						quickmodsData[i][j]->textsize(ADMP_TEXT_SIZE);
						quickmodsData[i][j]->align(FL_ALIGN_TOP_LEFT);
						quickmodsData[i][j]->deactivate();
						t_SpellAdjustmentsQuick->add(quickmodsData[i][j]);
					}
					quickmodsName[i]->labelsize(ADMP_LABEL_SIZE);
					quickmodsName[i]->textsize(ADMP_TEXT_SIZE);
					quickmodsName[i]->align(FL_ALIGN_TOP_LEFT);
					quickmodsName[i]->deactivate();
					t_SpellAdjustmentsQuick->add(quickmodsName[i]);
					y += 26;
					if (i == 21) { 
						x=515; y=110; 
					}
				}
				quickmodsName[0]->label("Name");
				quickmodsData[0][0]->label("BAB"); quickmodsData[0][0]->tooltip("Base Attack");
				quickmodsData[0][1]->label("Dam"); quickmodsData[0][1]->tooltip("Melee Damage");
				quickmodsData[0][2]->label("A/C"); quickmodsData[0][2]->tooltip("Armor Class");
				quickmodsData[0][3]->label("HP"); quickmodsData[0][3]->tooltip("Hit Points");
				quickmodsData[0][4]->label("Sav"); quickmodsData[0][4]->tooltip("All Saves");
				quickmodsData[0][5]->label("Init"); quickmodsData[0][5]->tooltip("Initiative");
				quickmodsData[0][6]->label("SR"); quickmodsData[0][6]->tooltip("Spell Resistance");
				quickmodsData[0][7]->label("Miss%"); quickmodsData[0][7]->tooltip("Miss Chance");
				quickmodsName[22]->label("Name");
				quickmodsData[22][0]->label("BAB"); quickmodsData[22][0]->tooltip("Base Attack");
				quickmodsData[22][1]->label("Dam"); quickmodsData[22][1]->tooltip("Melee Damage");
				quickmodsData[22][2]->label("A/C"); quickmodsData[22][2]->tooltip("Armor Class");
				quickmodsData[22][3]->label("HP"); quickmodsData[22][3]->tooltip("Hit Points");
				quickmodsData[22][4]->label("Sav"); quickmodsData[22][4]->tooltip("All Saves");
				quickmodsData[22][5]->label("Init"); quickmodsData[22][5]->tooltip("Initiative");
				quickmodsData[22][6]->label("SR"); quickmodsData[22][6]->tooltip("Spell Resistance");
				quickmodsData[22][7]->label("Miss%"); quickmodsData[22][7]->tooltip("Miss Chance");
				break;

		case -1:		// reset the data
				memset(&config.quickmods[0].i_id, '\0', sizeof(ADMPquickmods) * (MAX_MEMBERS + 1));
				for (i=0; i<MAX_MEMBERS+1; i++) {
					config.quickmods[i].i_id = -1;
					config.quickmods[i].i_effects[0][0] = -1;
					config.quickmods[i].i_effects[1][0] = -1;
					config.quickmods[i].i_effects[2][0] = -1;
					config.quickmods[i].i_effects[3][0] = -1;
					config.quickmods[i].i_effects[4][0] = -1;
					config.quickmods[i].i_effects[5][0] = -1;
					config.quickmods[i].i_effects[6][0] = -1;
					config.quickmods[i].i_effects[7][0] = -1;
					config.i_idList[ID_QUICKMODS][i] = -1;
				}
				break;

		case 0:		// refresh
				y=x=j=0;
				for (i=0; i<MAX_MEMBERS; i++) {
					if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0
						&& isDead(i) == 0) {
							if (j < MAX_QUICKMODIFIERS) {
//printf("dQM: found id %d:%d\n", i, j);
								for (x=0; x<MAX_MEMBERS; x++) {
									if (config.quickmods[x].i_id == i) {
										quickmodsName[j]->value(players[i].c_name);
										for (y=0; y<MAX_QUICKMODTYPES; y++) {
											sprintf(mybuf2, "%d", config.quickmods[x].i_effects[y][1]); quickmodsData[j][y]->value(mybuf2);
											quickmodsData[j][y]->activate();
										}
										quickmodsName[j]->activate();
										config.i_idList[ID_QUICKMODS][j] = i;
										break;
									}
								}
								// if it didnt find anything, set it to zero's
							if (x >= MAX_MEMBERS) {
//printf("dQM: didnt find id %d:%d\n", i, j);
								quickmodsName[j]->value(players[i].c_name);
								quickmodsName[j]->activate();
								quickmodsData[j][0]->activate(); quickmodsData[j][0]->value("0");
								quickmodsData[j][1]->activate(); quickmodsData[j][1]->value("0");
								quickmodsData[j][2]->activate(); quickmodsData[j][2]->value("0");
								quickmodsData[j][3]->activate(); quickmodsData[j][3]->value("0");
								quickmodsData[j][4]->activate(); quickmodsData[j][4]->value("0");
								quickmodsData[j][5]->activate(); quickmodsData[j][5]->value("0");
								quickmodsData[j][6]->activate(); quickmodsData[j][6]->value("0");
								quickmodsData[j][7]->activate(); quickmodsData[j][7]->value("0");
								config.i_idList[ID_QUICKMODS][j] = i;
							}
							j++;
						}
					}
				}
				for (; j<MAX_QUICKMODIFIERS; j++) {
//printf("dQM: clearing id %d\n", j);
					quickmodsName[j]->deactivate();
					quickmodsData[j][0]->deactivate();
					quickmodsData[j][1]->deactivate();
					quickmodsData[j][2]->deactivate();
					quickmodsData[j][3]->deactivate();
					quickmodsData[j][4]->deactivate();
					quickmodsData[j][5]->deactivate();
					quickmodsData[j][6]->deactivate();
					quickmodsData[j][7]->deactivate();
					config.i_idList[ID_QUICKMODS][j] = -1;
				}
				break;

		case 1:		// accept
				i = 0;
				for (j=0; j<MAX_QUICKMODIFIERS; j++) {
					if (config.i_idList[ID_QUICKMODS][j] != -1) {
						config.quickmods[i].i_id = config.i_idList[ID_QUICKMODS][j];
						for (y=0; y<MAX_QUICKMODTYPES; y++) {
							config.quickmods[i].i_effects[y][1] = atoi(quickmodsData[j][y]->value());
						}
						i++;
					}
				}
				for (; i<MAX_MEMBERS; i++) {
					config.quickmods[i].i_id = -1;
				}
				doQuickMods(0, 0, 0);		// rerefresh the quick mods screen
				break;

		case 2:		// clear
				for (i=0; i<MAX_QUICKMODIFIERS; i++) {
					quickmodsName[i]->value("");
					for (j=0; j<MAX_QUICKMODTYPES; j++) {
						quickmodsData[i][j]->value("");
					}
				}
				i = doQuickMods(-1,0,0);
				break;

		case 3:		// get the adjust for a player & type
				j = 0;
				for (x=0; x<MAX_MEMBERS; x++) {
					if (config.quickmods[x].i_id == pid) {
						switch (type) {
							case MOD_BAB: j += config.quickmods[x].i_effects[0][1];
										break;
							case MOD_AC: j += config.quickmods[x].i_effects[2][1];
										break;
							case MOD_SAVE: j += config.quickmods[x].i_effects[4][1];
										break;
							case MOD_DAMAGE: j += config.quickmods[x].i_effects[1][1];
										break;
							case MOD_INIT: j += config.quickmods[x].i_effects[5][1];
										break;
							case MOD_HP: j += config.quickmods[x].i_effects[3][1];
										break;
							case MOD_MISS_CHANCE: j += config.quickmods[x].i_effects[7][1];
										break;
							case MOD_SPELL_RESISTANCE: j += config.quickmods[x].i_effects[6][1];
										break;
						}
					}
				}
				return j;
				break;
	}

	return 0;
}

/********************************************************************************/
void do_masscombat(int action) {
int i=0,j=0,k=0,t=0,defd[MAX_MEMBERS];

	for (i=0;i<MAX_MEMBERS;i++) { defd[i] = 0; }

	switch (action) {
		case 1:
				a_MCResults->clear();
				for (i=1; i<=atoi(a_MCAttkGroups->value()); i++) {
					k=0;
					if (a_MCShowTotals->value() == 0) {
						sprintf(mybuf2, "Totals for Group: %d", i);
						a_MCResults->add("");
						a_MCResults->add(mybuf2);
					}
					for (j=1; j<=atoi(a_MCAttkInGroups->value()); j++) {
						k = j;
						if (j>MAX_MEMBERS) { k = j % MAX_MEMBERS; }
						if ((getRND(20) + atoi(a_MCAttkBAB->value())) >= atoi(a_MCDefdAC->value())) {
							t = parseDice((char *)a_MCAttkDamage->value());
							defd[k] += t;
							if (a_MCShowTotals->value() == 0) {
								sprintf(mybuf2, "Attacker %-3d gives %-3d damage", k, t);
								a_MCResults->add(mybuf2);
							}
						}
					}
				}
				if (a_MCShowTotals->value() == 0) {
					a_MCResults->add("");
					a_MCResults->add("Totals:");
				}
				j = 0;
				for (i=0;i<MAX_MEMBERS;i++) {
					if (defd[i] != 0) {
						sprintf(mybuf2, "Attacker %-3d gives %-3d damage", i, defd[i]);
						a_MCResults->add(mybuf2);
						j += defd[i];
					}
				}
				sprintf(mybuf2, "Grand Total: %-3d damage", j);
				a_MCResults->add("");
				a_MCResults->add(mybuf2);
				break;

		case 2:		// attacker selected
				i = a_MCAttackers->value(); i = config.i_idList[ID_MASSCOMBAT][i-1];
				sprintf(mybuf2, "%d", players[i].w_weapons[0].i_attackBonus[0] + getAdjustment(i, MOD_BAB)); a_MCAttkBAB->value(mybuf2);
				a_MCAttkDamage->value(players[i].w_weapons[0].c_damage);
				if (players[i].i_noInGroup > 0) {
					sprintf(mybuf2, "%d", players[i].i_noInGroup); a_MCAttkInGroups->value(mybuf2); 
				} else { a_MCAttkInGroups->value("1"); }
//printf("dMC: Attacker = %s\n", players[i].c_name);
				a_MCDefenders->activate();
				break;

		case 3:		// defender selected
				i = a_MCDefenders->value(); i = config.i_idList[ID_MASSCOMBAT][i-1];
				sprintf(mybuf2, "%d", players[i].i_armorClass[AC_NORMAL] + getAdjustment(i, MOD_AC)); a_MCDefdAC->value(mybuf2);
				if (players[i].i_noInGroup > 0) {
					sprintf(mybuf2, "%d", players[i].i_noInGroup); a_MCDefdInGroups->value(mybuf2); 
				} else { a_MCDefdInGroups->value("1"); }
				sprintf(mybuf2, "%d", players[i].i_hp[HP_MAX]); a_MCMaxHP->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_hp[HP_CUR] + getAdjustment(i, MOD_HP)); a_MCCurrentHP->value(mybuf2);
				a_MCDied->value("0");
//printf("dMC: Defender = %s\n", players[i].c_name);
				break;

		case 4:		// accept this attack
				if ((i = a_MCDefenders->value()) != -1) {
					i = config.i_idList[ID_MASSCOMBAT][i-1];
					players[i].i_noInGroup -= atoi(a_MCDied->value());
					players[i].i_hp[HP_CUR] = atoi(a_MCCurrentHP->value());
				}
					a_MCAttkGroups->value("1");
					a_MCAttkInGroups->value("0");
					a_MCAttkBAB->value("0");
					a_MCAttkDamage->value("");
					a_MCDefdInGroups->value("0");
					a_MCDefdAC->value("0");
					a_MCResults->clear();
					a_MCShowTotals->value(1);
					a_MCDied->value("0");
					a_MCMaxHP->value("0");
					a_MCCurrentHP->value("0");
					a_MCAttackers->clear();
					a_MCDefenders->clear();
					j = 0;
					for (i=0; i<MAX_MEMBERS; i++) {
						if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].i_inactive == 0) {
							if (players[i].i_noInGroup != 0) {
								sprintf(mybuf2, "%s # %d", players[i].c_name, players[i].i_noInGroup);
							} else {
								sprintf(mybuf2, "%s", players[i].c_name);
							}
							a_MCAttackers->add(mybuf2);
							a_MCDefenders->add(mybuf2);
							config.i_idList[ID_MASSCOMBAT][j++] = i;
						}
					}
					config.i_idList[ID_MASSCOMBAT][j] = -1; config.i_idList[ID_MASSCOMBAT][j+1] = -1;
					a_MCDefenders->deactivate();
				break;

		case 5:		// all done
				a_MassCombatWindow->hide();
				combatGridMap->repaint();
				externalGridMap->repaint();
				break;
	}
}

/********************************************************************************/
void doQuickEdit(int action) {
int i=0, j=0, l=0;

	switch (action) {
		case 0:	// show
				if (config.i_quickEditID == -1) { return; }

				qkEdit_Name->value("");
				qkEdit_HPCurrent->value("");
				qkEdit_HPMax->value("");
				qkEdit_DBNormal->value("");
				qkEdit_NoInGroup->value("");
				qkEdit_W1Id->value("-1");
				qkEdit_W1Name->value("");
				qkEdit_W1AB1->value("");
				qkEdit_W1AB2->value("");
				qkEdit_W1AB3->value("");
				qkEdit_W1AB4->value("");
				qkEdit_W1Damage->value("");
				qkEdit_W1Critical->value("");
				qkEdit_W2Id->value("-1");
				qkEdit_W2Name->value("");
				qkEdit_W2AB1->value("");
				qkEdit_W2AB2->value("");
				qkEdit_W2AB3->value("");
				qkEdit_W2AB4->value("");
				qkEdit_W2Damage->value("");
				qkEdit_W2Critical->value("");
				qkEdit_Icon->value("");
				qkEdit_Space->value("");
				qkEdit_ACTouch->value("");
				qkEdit_ACFlatFoot->value("");

				i = config.i_quickEditID;

				qkEdit_Name->value(players[i].c_name);
				sprintf(mybuf2, "%d", players[i].i_hp[HP_CUR]); qkEdit_HPCurrent->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_hp[HP_MAX]); qkEdit_HPMax->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_armorClass[AC_NORMAL]); qkEdit_DBNormal->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_noInGroup); qkEdit_NoInGroup->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_savingThrows[SAVE_FORTITUDE]); qkEdit_SaveFort->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_savingThrows[SAVE_REFLEX]); qkEdit_SaveReflex->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_savingThrows[SAVE_WISDOM]); qkEdit_SaveWill->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_savingThrows[SAVE_POISON]); qkEdit_SavePoison->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_savingThrows[SAVE_DISEASE]); qkEdit_SaveDisease->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_space); qkEdit_Space->value(mybuf2);
				qkEdit_Icon->value(players[i].c_iconFile);
				sprintf(mybuf2, "%d", players[i].i_armorClass[AC_TOUCH]); qkEdit_ACTouch->value(mybuf2);
				sprintf(mybuf2, "%d", players[i].i_armorClass[AC_FLATFOOTED]); qkEdit_ACFlatFoot->value(mybuf2);

				for (j=0; j<MAX_WEAPONS; j++) {
					if (players[i].w_weapons[j].c_description[0] != '\0') {
						if (l == 0) {
							sprintf(mybuf2, "%d", j); qkEdit_W1Id->value(mybuf2);
							qkEdit_W1Name->value(players[i].w_weapons[j].c_description);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[0]); qkEdit_W1AB1->value(mybuf2);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[1]); qkEdit_W1AB2->value(mybuf2);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[2]); qkEdit_W1AB3->value(mybuf2);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[3]); qkEdit_W1AB4->value(mybuf2);
							qkEdit_W1Damage->value(players[i].w_weapons[j].c_damage);
							qkEdit_W1Critical->value(players[i].w_weapons[j].c_critical);
							l++;
						} else if (l == 1) {
							sprintf(mybuf2, "%d", j); qkEdit_W2Id->value(mybuf2);
							qkEdit_W2Name->value(players[i].w_weapons[j].c_description);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[0]); qkEdit_W2AB1->value(mybuf2);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[1]); qkEdit_W2AB2->value(mybuf2);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[2]); qkEdit_W2AB3->value(mybuf2);
							sprintf(mybuf2, "%d", players[i].w_weapons[j].i_attackBonus[3]); qkEdit_W2AB4->value(mybuf2);
							qkEdit_W2Damage->value(players[i].w_weapons[j].c_damage);
							qkEdit_W2Critical->value(players[i].w_weapons[j].c_critical);
							l++;
						} else { break; }			// only show 1 line
					}
				}

				qkEdit_Window->show();
				break;

		case 1:	// accept
				i = config.i_quickEditID;
				if (config.i_quickEditID == -1) { return; }
				players[i].i_hp[HP_CUR] = atoi(qkEdit_HPCurrent->value());
				players[i].i_hp[HP_MAX] = atoi(qkEdit_HPMax->value());
				players[i].i_armorClass[AC_NORMAL] = atoi(qkEdit_DBNormal->value());
				players[i].i_noInGroup = atoi(qkEdit_NoInGroup->value());
				players[i].i_savingThrows[SAVE_FORTITUDE] = atoi(qkEdit_SaveFort->value());
				players[i].i_savingThrows[SAVE_REFLEX] = atoi(qkEdit_SaveReflex->value());
				players[i].i_savingThrows[SAVE_WISDOM] = atoi(qkEdit_SaveWill->value());
				players[i].i_savingThrows[SAVE_POISON] = atoi(qkEdit_SavePoison->value());
				players[i].i_savingThrows[SAVE_DISEASE] = atoi(qkEdit_SaveDisease->value());
				players[i].i_space = atoi(qkEdit_Space->value());
				strncpy(players[i].c_iconFile, qkEdit_Icon->value(), 59); players[i].c_iconFile[59] = '\0';
				players[i].i_armorClass[AC_TOUCH] = atoi(qkEdit_ACTouch->value());
				players[i].i_armorClass[AC_FLATFOOTED] = atoi(qkEdit_ACFlatFoot->value());

				j = atoi(qkEdit_W1Id->value());
				if (j == -1 && strlen(qkEdit_W1Name->value()) > 0) { j = 0; }
				if (j > -1) {
					strncpy(players[i].w_weapons[j].c_description, qkEdit_W1Name->value(), 30); players[i].w_weapons[j].c_description[29] = '\0';
					players[i].w_weapons[j].i_attackBonus[0] = atoi(qkEdit_W1AB1->value());
					players[i].w_weapons[j].i_attackBonus[1] = atoi(qkEdit_W1AB2->value());
					players[i].w_weapons[j].i_attackBonus[2] = atoi(qkEdit_W1AB3->value());
					players[i].w_weapons[j].i_attackBonus[3] = atoi(qkEdit_W1AB4->value());
					strncpy(players[i].w_weapons[j].c_damage, qkEdit_W1Damage->value(), 20); players[i].w_weapons[j].c_damage[19] = '\0';
					strncpy(players[i].w_weapons[j].c_critical, qkEdit_W1Critical->value(), 20); players[i].w_weapons[j].c_critical[19] = '\0';
				}

				j = atoi(qkEdit_W2Id->value());
				if (j == -1 && strlen(qkEdit_W2Name->value()) > 0) { j = 1; }
				if (j > -1) {
					strncpy(players[i].w_weapons[j].c_description, qkEdit_W2Name->value(), 30); players[i].w_weapons[j].c_description[29] = '\0';
					players[i].w_weapons[j].i_attackBonus[0] = atoi(qkEdit_W2AB1->value());
					players[i].w_weapons[j].i_attackBonus[1] = atoi(qkEdit_W2AB2->value());
					players[i].w_weapons[j].i_attackBonus[2] = atoi(qkEdit_W2AB3->value());
					players[i].w_weapons[j].i_attackBonus[3] = atoi(qkEdit_W2AB4->value());
					strncpy(players[i].w_weapons[j].c_damage, qkEdit_W2Damage->value(), 20); players[i].w_weapons[j].c_damage[19] = '\0';
					strncpy(players[i].w_weapons[j].c_critical, qkEdit_W2Critical->value(), 20); players[i].w_weapons[j].c_critical[19] = '\0';
				}
				config.i_quickEditID = -1;
				qkEdit_Window->hide();
				if (mystrcasestr(players[i].c_iconFile, "png") != NULL) {
					if (playerIcons[i] != NULL) { delete playerIcons[i]; }
					playerIcons[i] = new Fl_PNG_Image(players[i].c_iconFile);
				} else {
					if (playerIcons[i] != NULL) { delete playerIcons[i]; }
					playerIcons[i] = new Fl_JPEG_Image(players[i].c_iconFile);
				}
				combatGridMap->setPlayerIcon(i, playerIcons[i]);
				combatGridMap->repaint();
				externalGridMap->repaint();
				break;

		case 2:	// cancel
				config.i_quickEditID = -1;
				qkEdit_Window->hide();
				break;
	}
}

/********************************************************************************/
