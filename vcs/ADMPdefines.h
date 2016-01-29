/**********************************************************************
 * 	Copyright Torquil Gault 2005+
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef VISUALC
#include <strings.h>
#endif

#include <FL/Fl_Menu_Item.H>

/**********************************************************************/
Fl_Menu_Item races[] = {
		  {"",0,0,(void*)0},
		  {"Human",0,0,(void*)0},
		  {"Elf",0,0,(void*)0},
		  {"HalfElf",0,0,(void*)0},
		  {"Gnome",0,0,(void*)0},
		  {"Halfling",0,0,(void*)0},
		  {"Dwarf",0,0,(void*)0},
		  {"Other",0,0,(void*)0},
		  {0}
};

Fl_Menu_Item classes[] = {
		  {"",0,0,(void*)0},
		  {"Barbarian",0,0,(void*)0},
		  {"Cleric",0,0,(void*)0},
		  {"Bard",0,0,(void*)0},
		  {"Druid",0,0,(void*)0},
		  {"Fighter",0,0,(void*)0},
		  {"Monk",0,0,(void*)0},
		  {"Paladin",0,0,(void*)0},
		  {"Ranger",0,0,(void*)0},
		  {"Rogue",0,0,(void*)0},
		  {"Sorcerer",0,0,(void*)0},
		  {"Wizard",0,0,(void*)0},
		  {0}
};

Fl_Menu_Item alignment[] = {
{"",0,0,(void*)0},
{"LG",0,0,(void*)0},
{"LN",0,0,(void*)0},
{"LE",0,0,(void*)0},
{"NG",0,0,(void*)0},
{"N",0,0,(void*)0},
{"NE",0,0,(void*)0},
{"CG",0,0,(void*)0},
{"CN",0,0,(void*)0},
{"CE",0,0,(void*)0},
{0}
};

/**********************************************************************/
extern ADMPsystem config;

/**********************************************************************/
void editPlayer(int i) ;
void searchWeaponDetails(int pos, char type);
void calcCombatLine(Fl_Widget *w);
void savePlayer(int i);
void initialiseSystem(int, char **);
void cancelEdit();
void doEditSpecialActions(int action);

void saveAllData();
void loadAllData();
void loadMonsterFile();
void loadPlayerFile();
void loadMapFile();
void saveMonsterFile();
void saveMapFile();
void saveAllAsIni();
void loadAllAsIni();
void setCombatDisplay(int );
void doInitiativeAction(int );
void setWeaponDisplay(int );
void acceptCombatAction(int );
int calcAction(int );
void actionQkMonsters(int );
void searchQkMonsters(const char *);
void doOtherAction(int );
void endOfRound();
void calcCombatMods(int );
void doSpecialAttacks();
void doTriggerAction(int );
void doAdjustmentAction(int );
void doCalcXP();
void doWeaponSearchAction(int );
int  getRND(int );
void doAutoDamageAction(int );
void selectEditWeapon(int );
void selectQkAddEditWeapon(int );
void setOtherActionDescription(int );
void setSystemFlag(int );
void generateRndNames();
void generateRndTreasure();
void npc_action(int );
void dump_player_details();
void calcELLevel();
const char *htmlLoadLink(Fl_Widget *, const char *);
void doMassSkillCheck(int );
void dumpAdjustments();
void rollRNDDice();
void doAddPlayerXP();
void doSystemExit();
void qkMonsterAction(int );
void showSRDspellEntries(int );
void selectSRDspellEntries(int );
void qkMonsterAdd(int );
void qkHealAction(int );
void doMapFileAction(int);
void doGroupAction(int);
void setScreenSize();
void doSpecialMapAction(int);
void doNotesAction(int);
void doMapMode(int);
void doQkIcon(int);
void doRndsDecrement(int);
void loadStdModifiers();
void doCopyWeaponDetails(int );
void doSpellLists(int );
void doSpellEnergyType(int );
void reloadNames(int );
void doMagicItemGeneration();
void doHealMonsters(int );
void setWindowTitles();
void doDisableAction(int );
int doQuickMods(int, int, int);
void do_masscombat(int );
void doDiceSystem(int );
void doD100SelectAction(int );
void doD100SelectDefender(int, int);
void doD100SelectWeapon(int, int);
void doD100ActionOption(int, int);
void doD100CalcAttack(int );
void doD100CalcCritical(int, int);
void doD100ActionModifiers(int, int);
void doD100SpellSearch(const char *);
void doD100SpellSearchAction(int, int);
void doQuickEdit(int );

int doIconKeyPressed(int );
