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
#include "ADMPmerp.h"

/******************************************************************************/
#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Select_Browser.H>
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
#include "ADMPexternals.h"

#include <dirent.h>
extern int scandir();
extern int alphasort();

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
char d100TableId[MAX_D100TABLES][4], *d100TableMem[MAX_D100TABLES];
		// these start at 1 and go up
char d100ActionModifiers[5][8] = {{0,10,-10,20,0,0,0,0}, {0,-1,20,-1,20,-10,-20,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,10,-10,20,0,0,0,0}};
char d100ActionModifiersFlags[5][8] = {{0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}};

char *d100AttkTbl=NULL, *d100CritTbl=NULL;

ADMPweapon d100WeaponUsed;

Fl_Browser* d1_DefenderList[5];
Fl_Browser* d1_CombatWeaponUsed[4];
Fl_Browser* d1_CombatWeaponDetails[4];
Fl_Input* d1_CombatParry[4][2];
Fl_Button* d1_CombatSpecAttk[4];
Fl_Input* d1_CombatAttkRoll[5];
Fl_Input* d1_CombatAdj[5];
Fl_Input* d1_CombatOB[5];
Fl_Button* d1_CombatCalc[5][3];
Fl_Input* d1_CombatCritRoll[4][2];
Fl_Choice* d1_CombatCrit[4][2];
Fl_Input* d1_CombatResults[5][8];
Fl_Button* d1_CombatAcceptThis[5];
Fl_Button* d1_CombatAcceptAll[5];
Fl_Check_Browser* d1_CombatModifiers[5];
Fl_Input* d1_CombatMods[5][4];
Fl_Input* d1_CombatAttkTable[4];
Fl_Input* d1_CombatCritTable[4][2];
Fl_Button* d1_CombatD100Roll[5];

/****************************************************************************/
extern int seed1, seed2, seed3;

extern ADMPsystem config;
extern ADMPplayer  players[MAX_MEMBERS+4], qkmonsters[MAX_QKMONSTERS+2];
extern ADMPweapon stdweapons[MAX_STDWEAPONS+2];

extern char mybuf1[2048], mybuf2[2048];

extern float ADMPversion;

extern FILE *logfile, *openf;

/******************************************************************************/
extern Fl_Menu_Item races[];
extern Fl_Menu_Item classes[];
extern Fl_Double_Window *a_WeaponWindow, *a_Exit;
extern gridMap *combatGridMap, *externalGridMap;
extern Fl_Input  *quickmodsData[MAX_QUICKMODIFIERS][MAX_QUICKMODTYPES];

/******************************************************************************/
extern int doAreYouSure(char *);
extern void doSystemAlert(char *);
extern int getHPpercentage(int );
extern int getHPs(int );
extern int getAdjustment(int, int);
extern int getRND(int);
extern void setCombatDisplay(int );
extern void reloadNames(int );
extern void writeLog(char *);

void doD100LoadAllTables(char *);
void getD100CriticalRoll(char *, int , char);
void getD100AttackRoll(char *, int , int );
char *getD100Table(char *);
int getD100DiceRoll();
void doD100IgnoreAdjustment(int );
void doD100SelectDefender(int , int );
void doD100SelectWeapon(int , int );
void doD100SetDefenderListName(int );
void doD100FumbleResult(int , int , int );

/******************************************************************************/
void d100Setup() {

a_IActions->type(2);
quickmodsData[0][0]->label("OB"); quickmodsData[0][0]->tooltip("Attack Bonus");
quickmodsData[0][2]->label("DB"); quickmodsData[0][2]->tooltip("Defensive Bonus");
quickmodsData[0][4]->label("RR"); quickmodsData[0][4]->tooltip("All Saves");
quickmodsData[22][0]->label("OB"); quickmodsData[22][0]->tooltip("Attack Bonus");
quickmodsData[22][2]->label("DB"); quickmodsData[22][2]->tooltip("Defensive Bonus");
quickmodsData[22][4]->label("RR"); quickmodsData[22][4]->tooltip("All Saves");

aEdit_ACNormal->label("DB: Norm");
aEdit_ACTouch->label("Shield");
aEdit_ACFlatFoot->label("Parry");
aEdit_ACNoParry->activate();
aEdit_ACSecDex->deactivate();
aEdit_ACSecSize->deactivate();
aEdit_ACSecDeflection->deactivate();
aEdit_ACSecNatural->deactivate();
aEdit_ACSecArmor->deactivate();
aEdit_ACSecShield->deactivate();
aEdit_ACSecDodge->deactivate();
aEdit_HitDice->deactivate();
aEdit_NegateCritical->deactivate();
aEdit_EnhHP->deactivate();
aEdit_BABMelee1->deactivate();
aEdit_BABMelee2->deactivate();
aEdit_BABMelee3->deactivate();
aEdit_BABRanged1->deactivate();
aEdit_BABRanged2->deactivate();
aEdit_BABRanged3->deactivate();
aEdit_BABGrapple1->deactivate();
aEdit_BABGrapple2->deactivate();
aEdit_BABGrapple3->deactivate();
aEdit_BaseSpells->activate();
aEdit_DirectedSpells->activate();

aEdit_SaveFort->label("RR: Ess");
aEdit_SaveReflex->label("Cha");
aEdit_SaveWill->label("Ment");
aEdit_SavePoison->activate();
aEdit_SaveDisease->activate();
aEdit_RoundsSpellChg->activate();
aEdit_RoundsMissileChg->activate();
aEdit_RoundsDeathIn->activate();
aEdit_InitBonus->label("M&M Bonus");

aEdit_ArmorWorn->activate(); aEdit_ArmorWorn->show();
aEdit_ArmorLegWorn->activate(); aEdit_ArmorLegWorn->show();
aEdit_ArmorArmWorn->activate(); aEdit_ArmorArmWorn->show();
aEdit_ArmorHelmWorn->activate(); aEdit_ArmorHelmWorn->show();
aEdit_ArmorWorn->resize(307, 272, 60, 25);
aEdit_ArmorLegWorn->resize(400, 272, 60, 25);
aEdit_ArmorArmWorn->resize(490, 272, 60, 25);
aEdit_ArmorHelmWorn->resize(590, 272, 60, 25);

aEdit_SkillSearch->label("Skills: Perc"); aEdit_SkillSearch->tooltip("Perception");
aEdit_SkillSOH->label("Stalk");	aEdit_SkillSOH->tooltip("Stalk Hide");
aEdit_SkillSpot->label("Rune");	aEdit_SkillSpot->tooltip("Read Runes");
aEdit_SkillOLocks->label("U.Item");	aEdit_SkillOLocks->tooltip("Use Items");
aEdit_SkillMoveSilently->label(""); aEdit_SkillMoveSilently->deactivate();
aEdit_SkillConcentration->label(""); aEdit_SkillConcentration->deactivate();
aEdit_SkillListen->label(""); aEdit_SkillListen->deactivate();
aEdit_SkillHide->label(""); aEdit_SkillHide->deactivate();
aEdit_SkillSpot->resize(457,309,25,25);

aEdit_d201->label("d100 Rolls");
aEdit_SpellFailure->deactivate();
aEdit_SpellResistance->deactivate();
aEdit_DamReductionHP->deactivate();
aEdit_DamReductionWeapon->deactivate();
aEdit_DamReductionType->deactivate();
aEdit_CRating->deactivate();
aEdit_SpellDC0->deactivate();
aEdit_SpellDC1->deactivate();
aEdit_SpellDC2->deactivate();
aEdit_SpellDC3->deactivate();
aEdit_SpellDC4->deactivate();
aEdit_SpellDC5->deactivate();
aEdit_SpellDC6->deactivate();
aEdit_SpellDC7->deactivate();
aEdit_SpellDC8->deactivate();

aEdit_SpellSlotMax0->deactivate();
aEdit_SpellSlotCur0->deactivate();
aEdit_SpellSlotMax1->deactivate();
aEdit_SpellSlotCur1->deactivate();
aEdit_SpellSlotMax2->deactivate();
aEdit_SpellSlotCur2->deactivate();
aEdit_SpellSlotMax3->deactivate();
aEdit_SpellSlotCur3->deactivate();
aEdit_SpellSlotMax4->deactivate();
aEdit_SpellSlotCur4->deactivate();
aEdit_SpellSlotMax5->deactivate();
aEdit_SpellSlotCur5->deactivate();
aEdit_SpellSlotMax6->deactivate();
aEdit_SpellSlotCur6->deactivate();
aEdit_SpellSlotMax7->deactivate();
aEdit_SpellSlotCur7->deactivate();
aEdit_SpellSlotMax8->deactivate();
aEdit_SpellSlotCur8->deactivate();
aEdit_SpellSlotMax9->deactivate();
aEdit_SpellSlotCur9->deactivate();

aEdit_WeaponAttkBonus1->label("OB");
aEdit_WeaponAttkBonus2->deactivate();
aEdit_WeaponAttkBonus3->deactivate();
aEdit_WeaponAttkBonus4->deactivate();
aEdit_WeaponDamage->label("Prim Crit"); aEdit_WeaponDamage->resize(503, 218, 40, 25);
aEdit_WeaponCritical->label("2nd Crit"); aEdit_WeaponCritical->resize(503, 245, 40, 25);
aEdit_WeaponFumble->activate();
aEdit_WeaponCritAdjustment->activate();
aEdit_WeaponSize->activate();
aEdit_WeaponAttackTable->activate();

//memset(&qkmonsters[0].c_name[0], '\0', sizeof(ADMPplayer)*MAX_QKMONSTERS+2);
//memset(&stdweapons[0].c_available, '\0', sizeof(ADMPweapon) * MAX_STDWEAPONS);
memset(config.system_mods[0].c_message, '\0', sizeof(ADMPmodifiers) * MAX_MODIFIERS);

d1_SpellSearchFound->type(2);

	// TODO
d1_CombatModifiers[0]->clear(); d1_CombatModifiers[1]->clear();
d1_CombatModifiers[2]->clear(); d1_CombatModifiers[3]->clear();

d1_CombatModifiers[0]->add("Test +10");
d1_CombatModifiers[0]->add("Test -10");
d1_CombatModifiers[0]->add("Test +20");

d1_CombatModifiers[1]->add("Instantaneous");
d1_CombatModifiers[1]->add("Def: Centred");
d1_CombatModifiers[1]->add("Def: -AG Bonus");
d1_CombatModifiers[1]->add("0' - 10'");
d1_CombatModifiers[1]->add("11' - 50'");
d1_CombatModifiers[1]->add("51' - 100'");
d1_CombatModifiers[1]->add("101' - 200'");

d1_CombatModifiers[4]->add("Test +10");
d1_CombatModifiers[4]->add("Test -10");
d1_CombatModifiers[4]->add("Test +20");

aEdit_ACSecDex->hide();
aEdit_ACSecSize->hide();
aEdit_ACSecDeflection->hide();
aEdit_ACSecNatural->hide();
aEdit_ACSecArmor->hide();
aEdit_ACSecShield->hide();
aEdit_ACSecDodge->hide();
aEdit_HitDice->hide();
aEdit_NegateCritical->hide();
aEdit_EnhHP->hide();
aEdit_BABMelee1->hide();
aEdit_BABMelee2->hide();
aEdit_BABMelee3->hide();
aEdit_BABRanged1->hide();
aEdit_BABRanged2->hide();
aEdit_BABRanged3->hide();
aEdit_BABGrapple1->hide();
aEdit_BABGrapple2->hide();
aEdit_BABGrapple3->hide();
aEdit_SkillMoveSilently->hide();
aEdit_SkillConcentration->hide();
aEdit_SkillListen->hide();
aEdit_SkillHide->hide();
aEdit_SpellFailure->hide();
aEdit_SpellResistance->hide();
aEdit_DamReductionHP->hide();
aEdit_DamReductionWeapon->hide();
aEdit_DamReductionType->hide();
aEdit_CRating->hide();
aEdit_SpellDC0->hide();
aEdit_SpellDC1->hide();
aEdit_SpellDC2->hide();
aEdit_SpellDC3->hide();
aEdit_SpellDC4->hide();
aEdit_SpellDC5->hide();
aEdit_SpellDC6->hide();
aEdit_SpellDC7->hide();
aEdit_SpellDC8->hide();
aEdit_SpellSlotMax0->hide();
aEdit_SpellSlotCur0->hide();
aEdit_SpellSlotMax1->hide();
aEdit_SpellSlotCur1->hide();
aEdit_SpellSlotMax2->hide();
aEdit_SpellSlotCur2->hide();
aEdit_SpellSlotMax3->hide();
aEdit_SpellSlotCur3->hide();
aEdit_SpellSlotMax4->hide();
aEdit_SpellSlotCur4->hide();
aEdit_SpellSlotMax5->hide();
aEdit_SpellSlotCur5->hide();
aEdit_SpellSlotMax6->hide();
aEdit_SpellSlotCur6->hide();
aEdit_SpellSlotMax7->hide();
aEdit_SpellSlotCur7->hide();
aEdit_SpellSlotMax8->hide();
aEdit_SpellSlotCur8->hide();
aEdit_SpellSlotMax9->hide();
aEdit_SpellSlotCur9->hide();
aEdit_WeaponAttkBonus2->hide();
aEdit_WeaponAttkBonus3->hide();
aEdit_WeaponAttkBonus4->hide();

a_SRDText->deactivate();
a_SRDIndex->deactivate();
a_SRDPreviousPage->deactivate();
aMisc_XPCalc->deactivate();
ant_Grp3->deactivate();
ant_NPC->deactivate();
a_SpellListGroup->deactivate();
a_OTDiceRoller->label("Dice Roller");

aQkAdd_InitBonus->label("M&M Bonus");
aQkAdd_WeaponFumble->activate();
aQkAdd_WeaponCritAdjustment->activate();
aQkAdd_WeaponAttackTable->activate();
aQkAdd_WeaponDamage->label("Prim Crit"); aQkAdd_WeaponDamage->resize(325, 268, 40, 25);
aQkAdd_WeaponCritical->label("2nd Crit"); aQkAdd_WeaponCritical->resize(325, 295, 40, 25);
aQkAdd_ACNormal->label("DB: Norm");
aQkAdd_ACTouch->label("Shield");
aQkAdd_ACFlatFoot->label("Parry");
aQkAdd_SaveFort->label("RR: Ess");
aQkAdd_SaveReflex->label("Cha");
aQkAdd_SaveWill->label("Ment");
aQkAdd_SpellResistance->hide();
aQkAdd_DamReductionHP->hide();
aQkAdd_DamReductionWeapon->hide();
aQkAdd_DamReductionType->hide();
aQkAdd_SaveDisease->activate();
aQkAdd_SavePoison->activate();

qkEdit_DBNormal->label("DB: Norm");
qkEdit_ACTouch->label("Shield");
qkEdit_ACFlatFoot->label("Parry");
qkEdit_SaveFort->label("RR: Ess");
qkEdit_SaveReflex->label("Cha");
qkEdit_SaveWill->label("Ment");
qkEdit_SavePoison->activate();
qkEdit_SaveDisease->activate();
qkEdit_W1AB1->label("OB");
qkEdit_W1AB2->hide();
qkEdit_W1AB3->hide();
qkEdit_W1AB4->hide();
qkEdit_W1Damage->label("Prim Crit"); qkEdit_W1Damage->resize(274, 157, 40, 25);
qkEdit_W1Critical->label("2nd Crit"); qkEdit_W1Critical->resize(369, 157, 40, 25);

qkEdit_W2AB1->label("OB");
qkEdit_W2AB2->hide();
qkEdit_W2AB3->hide();
qkEdit_W2AB4->hide();
qkEdit_W2Damage->label("Prim Crit"); qkEdit_W2Damage->resize(274, 215, 40, 25);
qkEdit_W2Critical->label("2nd Crit"); qkEdit_W2Critical->resize(369, 215, 40, 25);
}

/******************************************************************************/
void doDiceSystem(int type) {

//printf("dDS: %d\n", type);

	if (config.i_diceSystem == type) return;

	if (type == -2) {
		for (int i=0; i<MAX_D100TABLES; i++) {
			d100TableMem[i] = NULL;
			d100TableId[i][0] = '\0';
		}
		return;
	}

	if (config.i_diceSystem != -1 && type == 1) {
		if (doAreYouSure("Do you really want to do this ?\nIf so, then 'Save All' and restart the program") == -1) { return; }
	}

	config.i_diceSystem = type;

	switch (type) {
		case 0:		// d20
					aSys_initSystem->deactivate();
					aSys_initSystem->value(0);
					break;

		case 1:		// d100 MERP
					doD100LoadAllTables("./mrpdat/");
					aSys_initSystem->activate();
					d100Setup();
					break;

		case 2:		// d100 RMS
					doD100LoadAllTables("./rmsdat/");
					aSys_initSystem->activate();
					d100Setup();
					break;

		case 20:
		case 21:
		case 22:		// Init system picked
					config.i_initSystem = aSys_initSystem->value();
					break;
	}
}

/******************************************************************************/
void doD100WindowSetup(int action) {
int i=0, j=0;
weapon_tab *wtbl;

//printf("dDWS: %d\n", action);

	switch (action) {
		case 0:		// initial setup, before window is displayed
					d1_ActionType->clear();
					d1_ActionType->add("Melee Attack"); d1_ActionType->add("Spell Attack");
					d1_ActionType->add("Missile Attack"); d1_ActionType->add("Heal"); d1_ActionType->add("M & M");
					d1_ActionType->activate();

					d1_CombatModifiers[0]->check_none(); d1_CombatModifiers[1]->check_none();
					d1_CombatModifiers[2]->check_none(); d1_CombatModifiers[3]->check_none();

					sprintf(mybuf2, "%d", (players[config.i_actionInitID].i_noAttacks - players[config.i_actionInitID].i_doneAttacks)); d1_CombatAttacksLeft->value(mybuf2);

					d1_ActionTab->deactivate();
					d1_ActionMeleeTab->deactivate();
					d1_ActionSpellTab->deactivate();
					d1_ActionMissileTab->deactivate();
					d1_ActionMoveTab->deactivate();
					d1_ActionHealTab->deactivate();
					d1_ActionMessages->clear();
					d1_ActionMessages->add(""); d1_ActionMessages->add(""); d1_ActionMessages->add(""); d1_ActionMessages->add("");
					d1_ActionMessages->add(""); d1_ActionMessages->add(""); d1_ActionMessages->add(""); d1_ActionMessages->add("");
					d1_ActionMessages->add(""); d1_ActionMessages->add(""); d1_ActionMessages->add("");
					if (config.i_diceSystem == DICE_MERP) {	// MERP
						d1_CombatDefenderArmor->clear();
						d1_CombatDefenderArmor->add("None"); d1_CombatDefenderArmor->add("Soft Leather"); d1_CombatDefenderArmor->add("Rigid Leather");
						d1_CombatDefenderArmor->add("Chain"); d1_CombatDefenderArmor->add("Plate");
					} else if (config.i_diceSystem == DICE_RMS) {	// RMS
						d1_CombatDefenderArmor->clear();					// TODO
						d1_CombatDefenderArmor->add("AR0"); d1_CombatDefenderArmor->add("AR1");
						d1_CombatDefenderArmor->add("AR2"); d1_CombatDefenderArmor->add("AR3");
						d1_CombatDefenderArmor->add("AR4"); d1_CombatDefenderArmor->add("AR5");
					}
					d1_CombatWeaponUsed[1]->clear();
					if ((wtbl = (weapon_tab *)getD100Table("WE")) != NULL) {
						for (i=0; i<MAX_D100WEAPONS; i++) {
//printf("WP = %s\n", wtbl->wp_dsc);
							if (wtbl->wp_ob == 5) {			// search for spells
								d1_CombatWeaponUsed[1]->add(wtbl->wp_dsc);
							}
							wtbl++;
						}
					} else {
//printf("Unable to find std weapons/spells ... using defaults\n");
						d1_CombatWeaponUsed[1]->add("Base Spell");
						d1_CombatWeaponUsed[1]->add("Shock Bolt");
						d1_CombatWeaponUsed[1]->add("Water Bolt");
						d1_CombatWeaponUsed[1]->add("Ice Bolt");
						d1_CombatWeaponUsed[1]->add("Fire Bolt");
						d1_CombatWeaponUsed[1]->add("Lightning Bolt");
						d1_CombatWeaponUsed[1]->add("Cold Ball");
						d1_CombatWeaponUsed[1]->add("Fire Ball");
						d1_CombatWeaponUsed[1]->add("Special");
					}
					break;

		case 1: // reset all the screen fields
					for (i=0; i<3; i++) {
						d1_CombatModifiers[i]->check_none();
						d1_CombatResults[i][0]->value(""); d1_CombatResults[i][1]->value(""); d1_CombatResults[i][2]->value(""); d1_CombatResults[i][3]->value("");
						d1_CombatResults[i][4]->value(""); d1_CombatResults[i][5]->value(""); d1_CombatResults[i][6]->value(""); d1_CombatResults[i][7]->value("");
						d1_CombatCritRoll[i][0]->value(""); d1_CombatCritRoll[i][1]->value("");
						d1_CombatOB[i]->value("");
						d1_CombatAdj[i]->value("");
						d1_CombatAttkRoll[i]->value("");
						d1_CombatParry[i][0]->value(""); d1_CombatParry[i][1]->value("");
						d1_CombatWeaponDetails[i]->clear();
						d1_CombatAttkTable[i]->value("");
						d1_CombatCritTable[i][0]->value(""); d1_CombatCritTable[i][1]->value("");
					}
					i = 3;	// Heal screen
					d1_CombatModifiers[i]->check_none();
					d1_CombatOB[i]->value("");
					d1_CombatAdj[i]->value("");
					d1_CombatAttkRoll[i]->value("");

					i = getAdjustment(config.i_actionInitID, MOD_BAB); sprintf(mybuf2, "%d", i);
					d1_CombatMods[0][0]->value(mybuf2); d1_CombatMods[1][0]->value(mybuf2); d1_CombatMods[2][0]->value(mybuf2); d1_CombatMods[3][0]->value(mybuf2);
					i = getAdjustment(config.i_actionInitID, MOD_DAMAGE); sprintf(mybuf2, "%d", i);
					d1_CombatMods[0][2]->value(mybuf2); d1_CombatMods[1][2]->value(mybuf2); d1_CombatMods[2][2]->value(mybuf2); d1_CombatMods[3][2]->value(mybuf2);
					sprintf(mybuf2, "%d", players[config.i_actionInitID].i_penalty[PENALTY_ACTIVITY]);
					d1_CombatMods[0][3]->value(mybuf2); d1_CombatMods[1][3]->value(mybuf2); d1_CombatMods[2][3]->value(mybuf2);

					sprintf(mybuf2, "%d", players[config.i_actionInitID].i_initiative[0] + getAdjustment(config.i_actionInitID, MOD_MOVE)); 
					d1_CombatOB[4]->value(mybuf2);

					break;

		case 2:	// show the defender details
					d1_DefenderList[0]->clear(); d1_DefenderList[1]->clear(); d1_DefenderList[2]->clear(); d1_DefenderList[3]->clear();
					d1_DefenderList[4]->clear();
					if (config.i_actionInitID < MAX_PLAYERS) {
						for (i=MAX_PLAYERS; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
								doD100SetDefenderListName(i);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
						for (i=0; i<MAX_PLAYERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
								doD100SetDefenderListName(i);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
					} else {
						for (i=0; i<MAX_MEMBERS; i++) {
							if (players[i].c_name[0] != '\0' && players[i].i_hp[HP_MAX] > 0 && players[i].flags.f_disabled == 0) {
								doD100SetDefenderListName(i);
								config.i_idList[ID_DEFD][j++] = i;
							}
						}
					}
					j = players[config.i_actionInitID].i_doneAttacks-1;					// default the previous defender
					if (j >= 0) {
						j = players[config.i_actionInitID].i_whomAttacked[j][0];
						for (i=0; i<MAX_MEMBERS; i++) {
							if (config.i_idList[ID_DEFD][i] == j) {
printf("Default Defd = %d\n", j);
								d1_DefenderList[0]->select(i+1, 1); d1_DefenderList[2]->select(i+1, 1);
								config.i_actionRecvID = j = players[config.i_actionInitID].i_whomAttacked[0][0];
								doD100SelectDefender(action-1, i+1);
								break;
							}
						}
					}
					return;
					break;
	}
	d1_CombatAcceptAll[0]->deactivate(); d1_CombatAcceptAll[1]->deactivate();
	d1_CombatAcceptAll[2]->deactivate(); d1_CombatAcceptAll[3]->deactivate();
	d1_CombatAcceptAll[4]->deactivate();

	for (i=0; i<5; i++) { for (j=0; j<8; j++) { d100ActionModifiersFlags[i][j] = 0; } }
}

/******************************************************************************/
void loadd100file(char *fname, char *fid) {
int i, j;
struct stat fs;

	for (i=0; i<MAX_D100TABLES; i++) {
		if (d100TableMem[i] == NULL) {
//printf("ld1f: %d %s %s\n", i, fname, fid);
			if ((j = open(fname, O_RDONLY)) != -1) {
				if (fstat(j, &fs) == 0) {
					if ((d100TableMem[i] = (char *)malloc(fs.st_size)) != NULL) {
//printf("ld1f: %d %s = %d\n", i, fname, fs.st_size);
						read(j, d100TableMem[i], fs.st_size);
						strcpy(&d100TableId[i][0], fid);
					}
				}
			}
			return;
		}
	}
}
/******************************************************************************/
void doD100LoadAllTables(char *path) {
int num_entries=0, i=0, j=0, k=0;
struct dirent **list;
struct stat fs;
char *cp, *cp1, tid[4], fname[200];

	for (i=0; i<MAX_D100TABLES; i++) {
		if (d100TableMem[i] != NULL) {
			free(d100TableMem[i]);
			d100TableId[i][0] = d100TableId[i][1] = d100TableId[i][2] = d100TableId[i][3] = '\0';
		} 
	}
/*
	if (config.i_diceSystem == DICE_MERP) { // MERP
		loadd100file("mrpdat/tab_1c.dat", "1c");
		loadd100file("mrpdat/tab_1e.dat", "1e");
		loadd100file("mrpdat/tab_2h.dat", "2h");
		loadd100file("mrpdat/tab_cc.dat", "cc");
		loadd100file("mrpdat/tab_ce.dat", "ce");
		loadd100file("mrpdat/tab_cg.dat", "cg");
		loadd100file("mrpdat/tab_ch.dat", "ch");
		loadd100file("mrpdat/tab_ci.dat", "ci");
		loadd100file("mrpdat/tab_ck.dat", "ck");
		loadd100file("mrpdat/tab_cp.dat", "cp");
		loadd100file("mrpdat/tab_cs.dat", "cs");
		loadd100file("mrpdat/tab_cu.dat", "cu");
		loadd100file("mrpdat/tab_fi.dat", "fi");
		loadd100file("mrpdat/tab_fm.dat", "fm");
		loadd100file("mrpdat/tab_fs.dat", "fs");
		loadd100file("mrpdat/tab_fw.dat", "fw");
		loadd100file("mrpdat/tab_gr.dat", "gr");
		loadd100file("mrpdat/tab_laa.dat", "la");
		loadd100file("mrpdat/tab_las.dat", "ls");
		loadd100file("mrpdat/tab_mm.dat", "mm");
		loadd100file("mrpdat/tab_ms.dat", "ms");
		loadd100file("mrpdat/tab_sa.dat", "sa");
		loadd100file("mrpdat/tab_sb.dat", "sb");
		loadd100file("mrpdat/tab_si.dat", "si");
		loadd100file("mrpdat/tab_sla.dat", "sa");
		loadd100file("mrpdat/tab_sls.dat", "ss");
		loadd100file("mrpdat/tab_so.dat", "so");
		loadd100file("mrpdat/tab_ss.dat", "ss");
		loadd100file("mrpdat/tab_sw.dat", "sw");
		loadd100file("mrpdat/tab_tc.dat", "tc");
		loadd100file("mrpdat/tab_we.dat", "we");
		loadd100file("mrpdat/tab_xh.dat", "xh");
		loadd100file("mrpdat/tab_xs.dat", "xs");
		return;
	} else if (config.i_diceSystem == DICE_RMS) { // RMS
		loadd100file("rmsdat/tab_af.dat", "af");
		loadd100file("rmsdat/tab_ba.dat", "ba");
		loadd100file("rmsdat/tab_bo.dat", "bo");
		loadd100file("rmsdat/tab_bs.dat", "bs");
		loadd100file("rmsdat/tab_cb.dat", "cb");
		loadd100file("rmsdat/tab_CC.dat", "CC");
		loadd100file("rmsdat/tab_CE.dat", "CE");
		loadd100file("rmsdat/tab_CG.dat", "CG");
		loadd100file("rmsdat/tab_CH.dat", "CH");
		loadd100file("rmsdat/tab_CI.dat", "CI");
		loadd100file("rmsdat/tab_CK.dat", "CK");
		loadd100file("rmsdat/tab_cl.dat", "cl");
		loadd100file("rmsdat/tab_CP.dat", "CP");
		loadd100file("rmsdat/tab_CS.dat", "CS");
		loadd100file("rmsdat/tab_CT.dat", "CT");
		loadd100file("rmsdat/tab_CU.dat", "CU");
		loadd100file("rmsdat/tab_CX.dat", "CX");
		loadd100file("rmsdat/tab_da.dat", "da");
		loadd100file("rmsdat/tab_dt.dat", "dt");
		loadd100file("rmsdat/tab_fa.dat", "fa");
		loadd100file("rmsdat/tab_fl.dat", "fl");
		loadd100file("rmsdat/tab_ha.dat", "ha");
		loadd100file("rmsdat/tab_ja.dat", "ja");
		loadd100file("rmsdat/tab_LAA.dat", "LAA");
		loadd100file("rmsdat/tab_LAS.dat", "LAS");
		loadd100file("rmsdat/tab_lb.dat", "lb");
		loadd100file("rmsdat/tab_ma.dat", "ma");
		loadd100file("rmsdat/tab_mg.dat", "mg");
		loadd100file("rmsdat/tab_ml.dat", "ml");
		loadd100file("rmsdat/tab_mm.dat", "mm");
		loadd100file("rmsdat/tab_ms.dat", "ms");
		loadd100file("rmsdat/tab_pl.dat", "pl");
		loadd100file("rmsdat/tab_qs.dat", "qs");
		loadd100file("rmsdat/tab_ra.dat", "ra");
		loadd100file("rmsdat/tab_sb.dat", "sb");
		loadd100file("rmsdat/tab_sca.dat", "sca");
		loadd100file("rmsdat/tab_sc.dat", "sc");
		loadd100file("rmsdat/tab_sfa.dat", "sfa");
		loadd100file("rmsdat/tab_sfo.dat", "sfo");
		loadd100file("rmsdat/tab_sio.dat", "sio");
		loadd100file("rmsdat/tab_sla.dat", "sla");
		loadd100file("rmsdat/tab_SLA.dat", "SLA");
		loadd100file("rmsdat/tab_sl.dat", "sl");
		loadd100file("rmsdat/tab_slo.dat", "slo");
		loadd100file("rmsdat/tab_SLS.dat", "SLS");
		loadd100file("rmsdat/tab_sp.dat", "sp");
		loadd100file("rmsdat/tab_ss.dat", "ss");
		loadd100file("rmsdat/tab_sso.dat", "sso");
		loadd100file("rmsdat/tab_swo.dat", "swo");
		loadd100file("rmsdat/tab_th.dat", "th");
		loadd100file("rmsdat/tab_we.dat", "we");
		loadd100file("rmsdat/tab_wh.dat", "wh");
		loadd100file("rmsdat/tab_wm.dat", "wm");
		loadd100file("rmsdat/tab_wp.dat", "wp");
		loadd100file("rmsdat/tab_xe.dat", "xe");
		loadd100file("rmsdat/tab_xh.dat", "xh");
		return;
	}
*/

//	num_entries = fl_filename_list(path, &list, fl_casealphasort);
	num_entries = scandir(path, &list, NULL, alphasort);
	if (num_entries < 3) { return; }
//printf("ddLAT: 2: %s : %d\n", path, num_entries);

	for (i=2; i<num_entries; i++) {
		cp = list[i]->d_name;
//printf("ddLAT: %d %s %s\n", i, path, list[i]->d_name);
		if (strncasecmp(cp, "tab_", 3) == 0) {
			tid[0] = toupper(cp[4]);
			tid[1] = toupper(cp[5]);
			tid[2] = tid[3] = '\0';
			if (cp[6] != '.') { tid[2] = toupper(cp[6]); }
			sprintf(fname, "%s%s", path, cp);
			if ((j = open(fname, O_RDONLY)) != -1) {
				if (fstat(j, &fs) == 0) {
					if ((d100TableMem[k] = (char *)malloc(fs.st_size)) != NULL) {
						read(j, d100TableMem[k], fs.st_size);
						strcpy(&d100TableId[k][0], tid);
//printf("ddLAT: %s : %s (%d:%d)\n", cp, &d100TableId[k][0], (k+1), fs.st_size);
						k++;
					}
				}
				close(j);
			}
		}
	}

	return;
}

/******************************************************************************/
char *getD100Table(char *tbl) {
int i;

	for (i=0; i<MAX_D100TABLES; i++) {
		if (strcasecmp(&d100TableId[i][0], tbl) == 0) {
//printf("gDT: %s -> %s\n", tbl, &d100TableId[i][0]);
			return d100TableMem[i];
		}
	}
	sprintf(mybuf1, "Unable to load data file %s", tbl);
	doSystemAlert(mybuf1);
	return NULL;
}

/******************************************************************************/
void doD100SetDefenderListName(int pid) {
char fmt[10];
int k;

	fmt[0] = mybuf2[0] = '\0';
	k = getHPs(pid);

//	if (players[pid].i_doneAttacks > 0) { strcpy(fmt, "@B88@."); }
	if (players[pid].i_stun > 0) { strcat(mybuf2, "S"); strcpy(fmt, "@B95@."); }
	if (k <= players[pid].i_unconciousAt) { strcat(mybuf2, "U"); strcpy(fmt, "@B95@."); }
	if (players[pid].i_inactive > 0) { strcat(mybuf2, "I"); strcpy(fmt, "@B95@."); }

	sprintf(mybuf1, "%s%d%% %s (%d *%s %d:%d)", fmt, getHPpercentage(pid), players[pid].c_name, k, mybuf2, players[pid].i_noAttacks, players[pid].i_doneAttacks);
	d1_DefenderList[0]->add(mybuf1); d1_DefenderList[1]->add(mybuf1);
	d1_DefenderList[2]->add(mybuf1); d1_DefenderList[3]->add(mybuf1);
	d1_DefenderList[4]->add(mybuf1);
}

/******************************************************************************/
void doD100SelectAction(int action) {
int i=0, j=0;

printf("dDAM: %d\n", action);

	d1_ActionTab->activate();
	d1_ActionType->deactivate();
	d1_DefenderList[0]->clear(); d1_DefenderList[1]->clear();
	d1_DefenderList[2]->clear(); d1_DefenderList[3]->clear();
	d1_DefenderList[4]->clear();

	doD100WindowSetup(1);

	switch (action) {
		case 1:	d1_ActionMeleeTab->activate(); d1_ActionTab->value(d1_ActionMeleeTab);
					break;
		case 2: d1_ActionSpellTab->activate(); d1_ActionTab->value(d1_ActionSpellTab);
					break;
		case 3: d1_ActionMissileTab->activate(); d1_ActionTab->value(d1_ActionMissileTab);
					break;
		case 4: d1_ActionHealTab->activate(); d1_ActionTab->value(d1_ActionHealTab);
					break;
		case 5: d1_ActionMoveTab->activate(); d1_ActionTab->value(d1_ActionMoveTab);
					d1_CombatMMDifficulty->value(0);
					break;
	}
	
	if (config.i_actionInitID >= MAX_PLAYERS || config.flags.f_rollAllRolls != 0) {
		sprintf(mybuf2, "%d", getD100DiceRoll()); 
		d1_CombatAttkRoll[0]->value(mybuf2); d1_CombatAttkRoll[1]->value(mybuf2);
		d1_CombatAttkRoll[2]->value(mybuf2); d1_CombatAttkRoll[3]->value(mybuf2);
		sprintf(mybuf2, "%d", getRND(100)); 
		d1_CombatCritRoll[0][0]->value(mybuf2); d1_CombatCritRoll[1][0]->value(mybuf2);
		d1_CombatCritRoll[2][0]->value(mybuf2); 
		sprintf(mybuf2, "%d", getRND(100)); 
		d1_CombatCritRoll[0][1]->value(mybuf2); d1_CombatCritRoll[1][1]->value(mybuf2);
		d1_CombatCritRoll[2][1]->value(mybuf2); 
	}

		doD100WindowSetup(2);			// show the defender details
	
		j = players[config.i_actionInitID].i_doneAttacks;					// default the last defender attacked
		j = players[config.i_actionInitID].i_whomAttacked[0][0];
		for (i=0; i<MAX_MEMBERS; i++) {
			if (config.i_idList[ID_DEFD][i] == j) {
				d1_DefenderList[0]->select(i+1, 1); d1_DefenderList[2]->select(i+1, 1);
				config.i_actionRecvID = j = players[config.i_actionInitID].i_whomAttacked[0][0];
				doD100SelectDefender(action-1, i+1);
				break;
			}
		}
	
		d1_CombatWeaponUsed[0]->clear(); d1_CombatWeaponUsed[2]->clear();
		j=0;
	
		for (i=0; i<MAX_WEAPONS; i++) {
			if (players[config.i_actionInitID].w_weapons[i].c_description[0] != '\0') {
				d1_CombatWeaponUsed[0]->add(players[config.i_actionInitID].w_weapons[i].c_description);
				d1_CombatWeaponUsed[2]->add(players[config.i_actionInitID].w_weapons[i].c_description);
				config.i_idList[ID_WEAP][j++] = i;
			}
		}
		for (i=0; i<MAX_WEAPONS; i++) {
			if (players[config.i_actionInitID].i_whomAttacked[0][1] == config.i_idList[ID_WEAP][i]) {
				d1_CombatWeaponUsed[0]->select(i+1, 1); d1_CombatWeaponUsed[2]->select(i+1, 1);
				doD100SelectWeapon(action-1, i+1);
				break;
			}
		}
}

/******************************************************************************/
void doD100SelectDefender(int screen, int defd) {
int i, recv, weap;

printf("dDSD: %d:%d\n", screen, defd);

	config.i_actionRecvID = defd = config.i_idList[ID_DEFD][defd-1];

	i = getAdjustment(defd, MOD_AC); sprintf(mybuf2, "%d", i); 
	d1_CombatMods[0][1]->value(mybuf2); d1_CombatMods[1][1]->value(mybuf2); d1_CombatMods[2][1]->value(mybuf2);
	sprintf(mybuf2, "Action Initiator: %s", players[config.i_actionInitID].c_name); d1_ActionMessages->text(1, mybuf2);

	switch (screen) {
		case 0:		// melee screen
				sprintf(mybuf2, "%d", players[defd].i_armorClass[AC_NORMAL]); d1_CombatDefenderArmor->value(players[defd].i_armorClassSplit[AC_SECTION_WORN]);
				if (players[defd].i_armorClassSplit[AC_SECTION_WORN] < 0) d1_CombatDefenderArmor->value(1);
				if (config.i_diceSystem == DICE_MERP) {
					if (players[defd].i_armorClassSplit[AC_SECTION_WORN] > 5) d1_CombatDefenderArmor->value(5);
				} else {
					if (players[defd].i_armorClassSplit[AC_SECTION_WORN] > 20) d1_CombatDefenderArmor->value(20);
				}

				sprintf(mybuf2, "%d", players[defd].i_armorClass[AC_SECTION_PARRY]);
				sprintf(mybuf2, "%d", getAdjustment(defd, MOD_AC)); d1_CombatMods[screen][1]->value(mybuf2);
				sprintf(mybuf2, "Defender Selected: %s", players[defd].c_name); d1_ActionMessages->text(2, mybuf2);
				break;
		case 1:		// spell screen
				sprintf(mybuf2, "Defender Selected: %s", players[defd].c_name); d1_ActionMessages->text(2, mybuf2);
				break;
		case 2:		// missile screen
				sprintf(mybuf2, "Defender Selected: %s", players[defd].c_name); d1_ActionMessages->text(2, mybuf2);
				break;
		case 3:		// heal screen
				break;
		case 4:		// move screen
				break;
	}
}

/******************************************************************************/
void doD100SelectWeapon(int screen, int weapon) {
int i;
weapon_tab *wtbl;

//printf("dDSW: %d:%d\n", screen, weapon);

	d1_CombatWeaponDetails[0]->clear(); d1_CombatWeaponDetails[1]->clear(); d1_CombatWeaponDetails[2]->clear();
	config.i_actionWeaponSelected = weapon = config.i_idList[ID_WEAP][weapon-1];
	memset(&d100WeaponUsed.c_available, '\0', sizeof(ADMPweapon));

	switch (screen) {
		case 0:		// melee screen
		case 2:		// missile screen
				players[config.i_actionInitID].i_whomAttacked[0][1] = config.i_actionWeaponSelected;
				sprintf(mybuf1, "  Name: %s", players[config.i_actionInitID].w_weapons[weapon].c_description); d1_CombatWeaponDetails[screen]->add(mybuf1);
				sprintf(mybuf1, " Table: %s", players[config.i_actionInitID].w_weapons[weapon].c_table); d1_CombatWeaponDetails[screen]->add(mybuf1);
				sprintf(mybuf1, "Fumble: %d", players[config.i_actionInitID].w_weapons[weapon].i_fumble); d1_CombatWeaponDetails[screen]->add(mybuf1);
				sprintf(mybuf1, "P Crit: %s", players[config.i_actionInitID].w_weapons[weapon].c_damage); d1_CombatWeaponDetails[screen]->add(mybuf1);
				sprintf(mybuf1, "2 Crit: %s", players[config.i_actionInitID].w_weapons[weapon].c_critical); d1_CombatWeaponDetails[screen]->add(mybuf1);
				sprintf(mybuf1, "Sp Msg: %s", players[config.i_actionInitID].w_weapons[weapon].c_message); d1_CombatWeaponDetails[screen]->add(mybuf1);

				sprintf(mybuf1, "%d", players[config.i_actionInitID].w_weapons[weapon].i_attackBonus[0]); d1_CombatOB[screen]->value(mybuf1); 

				memcpy(&d100WeaponUsed.c_available, &players[config.i_actionInitID].w_weapons[weapon].c_available, sizeof(ADMPweapon));
				d1_CombatAttkTable[screen]->value(d100WeaponUsed.c_table);
				d1_CombatCritTable[screen][0]->value(d100WeaponUsed.c_damage);
				d1_CombatCritTable[screen][1]->value(d100WeaponUsed.c_critical);
				break;

		case 1:		// spell screen
				if ((weapon = d1_CombatWeaponUsed[1]->value()) == 0) return;
				if ((wtbl = (weapon_tab *)getD100Table("WE")) != NULL) {
					for (i=0; i<MAX_D100WEAPONS; i++) {
						if (wtbl->wp_ob == 5 && strcasecmp(wtbl->wp_dsc, d1_CombatWeaponUsed[1]->text(weapon)) == 0) {			// search the spells
							sprintf(mybuf1, "  Name: %s", wtbl->wp_dsc); d1_CombatWeaponDetails[1]->add(mybuf1);
							sprintf(mybuf1, " Table: %s", wtbl->wp_tbl); d1_CombatWeaponDetails[1]->add(mybuf1);
							sprintf(mybuf1, "Fumble: %d", wtbl->wp_fm); d1_CombatWeaponDetails[1]->add(mybuf1);
							sprintf(mybuf1, "P Crit: %s", wtbl->wp_pc); d1_CombatWeaponDetails[1]->add(mybuf1);
							sprintf(mybuf1, "2 Crit: %s", wtbl->wp_sc); d1_CombatWeaponDetails[1]->add(mybuf1);
							sprintf(mybuf1, "Sp Msg: %s", wtbl->wp_sm); d1_CombatWeaponDetails[1]->add(mybuf1);

							strcpy(d100WeaponUsed.c_description, wtbl->wp_dsc);
							d100WeaponUsed.i_fumble = wtbl->wp_fm;
							d100WeaponUsed.i_critAdjust = wtbl->wp_ca;
							strcpy(d100WeaponUsed.c_damage, wtbl->wp_pc);
							strcpy(d100WeaponUsed.c_critical, wtbl->wp_sc);
							strcpy(d100WeaponUsed.c_message, wtbl->wp_sm);
							strcpy(d100WeaponUsed.c_table, wtbl->wp_tbl);

							d1_CombatAttkTable[screen]->value(d100WeaponUsed.c_table);
							d1_CombatCritTable[screen][0]->value(d100WeaponUsed.c_damage);
							d1_CombatCritTable[screen][1]->value(d100WeaponUsed.c_critical);

							break;
						}
						wtbl++;
					}
				}
				if (weapon == 1) {
					sprintf(mybuf1, "%d", players[config.i_actionInitID].i_baseSpell); 
				} else {
					sprintf(mybuf1, "%d", players[config.i_actionInitID].i_baseSpell + players[config.i_actionInitID].i_directedSpells);
				}
				d1_CombatOB[screen]->value(mybuf1); 
				break;

		case 3:		// heal screen
				break;
	}

}

/******************************************************************************/
void doD100ActionOption(int screen, int option) {
int i=0;

printf("dDAO: %d:%d\n", screen, option);

	doD100IgnoreAdjustment(config.i_actionRecvID);

	switch (option) {
		case 0:	//	accept this attack
					i = players[config.i_actionInitID].i_doneAttacks;
					players[config.i_actionInitID].i_whomAttacked[i][0] = config.i_actionRecvID;

					switch (screen) {
					 case 3:		// healing
						players[config.i_actionRecvID].i_hp[HP_CUR] += atoi(d1_CombatResults[screen][0]->value()) + atoi(d1_CombatMods[screen][2]->value());	//HP
						players[config.i_actionRecvID].i_penalty[PENALTY_ACTIVITY] -= atoi(d1_CombatResults[screen][1]->value());	//APen
						players[config.i_actionRecvID].i_bleeding -= atoi(d1_CombatResults[screen][2]->value());	//Bleed
						players[config.i_actionRecvID].i_stun -= atoi(d1_CombatResults[screen][3]->value());	//Stun
						players[config.i_actionRecvID].i_armorClass[AC_SECTION_PARRY] -= atoi(d1_CombatResults[screen][4]->value());	//Rnds Parry
						players[config.i_actionRecvID].i_armorClass[AC_NOPARRY] -= atoi(d1_CombatResults[screen][5]->value());	//Rnds NoParry
						players[config.i_actionRecvID].i_roundsUntil[ROUND_DEATH] -= atoi(d1_CombatResults[screen][6]->value());	//Death
						players[config.i_actionRecvID].i_inactive -= atoi(d1_CombatResults[screen][7]->value());	//Inact

						if (players[config.i_actionRecvID].i_hp[HP_CUR] > players[config.i_actionRecvID].i_hp[HP_MAX]) { players[config.i_actionRecvID].i_hp[HP_CUR] = players[config.i_actionRecvID].i_hp[HP_MAX]; }
						if (players[config.i_actionRecvID].i_penalty[PENALTY_ACTIVITY] < 0) { players[config.i_actionRecvID].i_penalty[PENALTY_ACTIVITY] = 0; }
						if (players[config.i_actionRecvID].i_bleeding < 0) { players[config.i_actionRecvID].i_bleeding = 0; }
						if (players[config.i_actionRecvID].i_stun < 0) { players[config.i_actionRecvID].i_stun = 0; }
						if (players[config.i_actionRecvID].i_armorClass[AC_SECTION_PARRY] < 0) { players[config.i_actionRecvID].i_armorClass[AC_SECTION_PARRY] = 0; }
						if (players[config.i_actionRecvID].i_armorClass[AC_NOPARRY] < 0) { players[config.i_actionRecvID].i_armorClass[AC_NOPARRY] = 0; }
						if (players[config.i_actionRecvID].i_roundsUntil[ROUND_DEATH] < 0) { players[config.i_actionRecvID].i_roundsUntil[ROUND_DEATH] = 0; }
						if (players[config.i_actionRecvID].i_inactive < 0) { players[config.i_actionRecvID].i_inactive = 0; }
						break;

					 case 4:		// move
						break;

					 default:	// melee, missiles & spells
						players[config.i_actionRecvID].i_hp[HP_CUR] -= atoi(d1_CombatResults[screen][0]->value()) + atoi(d1_CombatMods[screen][2]->value());	//HP
						players[config.i_actionRecvID].i_penalty[PENALTY_ACTIVITY] += atoi(d1_CombatResults[screen][1]->value());	//APen
						players[config.i_actionRecvID].i_bleeding += atoi(d1_CombatResults[screen][2]->value());	//Bleed
						players[config.i_actionRecvID].i_stun += atoi(d1_CombatResults[screen][3]->value());	//Stun
						players[config.i_actionRecvID].i_armorClass[AC_SECTION_PARRY] += atoi(d1_CombatResults[screen][4]->value());	//Rnds Parry
						players[config.i_actionRecvID].i_armorClass[AC_NOPARRY] += atoi(d1_CombatResults[screen][5]->value());	//Rnds NoParry
						players[config.i_actionRecvID].i_roundsUntil[ROUND_DEATH] += atoi(d1_CombatResults[screen][6]->value());	//Death
						players[config.i_actionRecvID].i_inactive += atoi(d1_CombatResults[screen][7]->value());	//Inact
						break;
					}

					players[config.i_actionInitID].i_doneAttacks++;
					sprintf(mybuf2, "%d", (players[config.i_actionInitID].i_noAttacks - players[config.i_actionInitID].i_doneAttacks));
					d1_CombatAttacksLeft->value(mybuf2);

					d1_CombatAcceptAll[screen]->activate();

					sprintf(mybuf2, "%s %s -> %s (HP:%d APen:%d Bleed:%d Stun:%d RParry:%d RNoParry:%d Death:%d Inact:%d)", players[config.i_actionInitID].c_name, d100WeaponUsed.c_description, players[config.i_actionRecvID].c_name,
					atoi(d1_CombatResults[screen][0]->value()), atoi(d1_CombatResults[screen][1]->value()), atoi(d1_CombatResults[screen][2]->value()),
					atoi(d1_CombatResults[screen][3]->value()), atoi(d1_CombatResults[screen][4]->value()), atoi(d1_CombatResults[screen][5]->value()),
					atoi(d1_CombatResults[screen][6]->value()), atoi(d1_CombatResults[screen][7]->value()));
					writeLog(mybuf2);
					if (players[config.i_actionInitID].i_doneAttacks < 7) {
						sprintf(mybuf2, "%s (HP:%d APen:%d Bleed:%d Stun:%d RParry:%d RNoParry:%d Death:%d Inact:%d)", players[config.i_actionRecvID].c_name,
						atoi(d1_CombatResults[screen][0]->value()), atoi(d1_CombatResults[screen][1]->value()), atoi(d1_CombatResults[screen][2]->value()),
						atoi(d1_CombatResults[screen][3]->value()), atoi(d1_CombatResults[screen][4]->value()), atoi(d1_CombatResults[screen][5]->value()),
						atoi(d1_CombatResults[screen][6]->value()), atoi(d1_CombatResults[screen][7]->value()));
						d1_ActionMessages->text(5+players[config.i_actionInitID].i_doneAttacks, mybuf2);
					}
					doD100WindowSetup(2);
					break;

		case 1:	//	all attacks done
					if (players[config.i_actionInitID].i_noAttacks == players[config.i_actionInitID].i_doneAttacks) {
						players[config.i_actionInitID].i_doneAttacks++;
					}
					a_d100CombatWindow->hide();
					reloadNames(1);
					setCombatDisplay(0);
					break;

		case 3:	// d100 roll
					sprintf(mybuf2, "%d", getD100DiceRoll()); d1_CombatAttkRoll[screen]->value(mybuf2);
					if (screen < 3) {
						sprintf(mybuf2, "%d", getRND(100)); d1_CombatCritRoll[screen][0]->value(mybuf2);
						sprintf(mybuf2, "%d", getRND(100)); d1_CombatCritRoll[screen][1]->value(mybuf2);
					}
					break;

		case 5:	// defd armor
					break;
	}

	d1_CombatResults[screen][0]->value("");
	d1_CombatResults[screen][1]->value("");
	d1_CombatResults[screen][2]->value("");
	d1_CombatResults[screen][3]->value("");
	d1_CombatResults[screen][4]->value("");
	d1_CombatResults[screen][5]->value("");
	d1_CombatResults[screen][6]->value("");
	d1_CombatResults[screen][7]->value("");

}

/******************************************************************************/
void doD100CalcAttack(int screen) {
int roll=0, i=0, a=0;
attk_tab *tbl1;
attk_tab2 *tbl2;
move_tab *mtbl;
char atbl[4];

printf("dDCA: %d\n", screen);
	for (i=0; i<2; i++) {
		d1_CombatResults[i][0]->value(""); d1_CombatResults[i][1]->value(""); d1_CombatResults[i][2]->value(""); d1_CombatResults[i][3]->value("");
		d1_CombatResults[i][4]->value(""); d1_CombatResults[i][5]->value(""); d1_CombatResults[i][6]->value(""); d1_CombatResults[i][7]->value("");
		d1_CombatCrit[i][0]->value(0); d1_CombatCrit[i][1]->value(0);
	}
	d1_CombatResults[3][0]->value(""); d1_CombatResults[3][1]->value(""); d1_CombatResults[3][2]->value(""); d1_CombatResults[3][3]->value("");
	d1_CombatResults[3][4]->value(""); d1_CombatResults[3][5]->value(""); d1_CombatResults[3][6]->value(""); d1_CombatResults[3][7]->value("");
	d1_CombatResults[4][0]->value(""); d1_CombatResults[4][1]->value(""); d1_CombatResults[4][2]->value(""); d1_CombatResults[4][3]->value("");
	d1_CombatResults[4][4]->value(""); d1_CombatResults[4][5]->value(""); d1_CombatResults[4][6]->value(""); d1_CombatResults[4][7]->value("");

	if ((i = atoi(d1_CombatAttkRoll[screen]->value())) < 0) {				// FUMBLE		TODO
		doD100FumbleResult(config.i_actionInitID, screen, i);
		return;
	}

	switch (screen) {
		case 0:		// melee screen
		case 1:		// spell screen
		case 2:		// missile screen
				strcpy(atbl, d1_CombatAttkTable[screen]->value());		// use the attk table as marked on the screen
				if (strlen(atbl) < 2) {
					doSystemAlert("Please enter an Attack Table to use !!!!");
					return;
				}
				roll = atoi(d1_CombatAttkRoll[screen]->value());
				if (roll <= d100WeaponUsed.i_fumble) {						// TODO
					doSystemAlert("Fumble !!!!");
				}
				if (config.i_diceSystem == DICE_MERP) {
					getD100AttackRoll(atbl, roll, 1);
					if (d100AttkTbl != NULL) {
						tbl1 = (attk_tab *)d100AttkTbl;
					} else {
						roll = atoi(d1_CombatAttkRoll[screen]->value()) + atoi(d1_CombatOB[screen]->value()) + atoi(d1_CombatParry[screen][0]->value()) + atoi(d1_CombatMods[screen][0]->value()) + atoi(d1_CombatAdj[screen]->value()) - (atoi(d1_CombatParry[screen][0]->value()) + atoi(d1_CombatMods[screen][1]->value()) + atoi(d1_CombatMods[screen][3]->value()));
						getD100AttackRoll(atbl, roll, 0);
						if (d100AttkTbl != NULL) { tbl1 = (attk_tab *)d100AttkTbl; } else { return; }
					}
					a = d1_CombatDefenderArmor->value(); if (a < 0) { a = 0; } if (a > 4) { a = 4; }
					sprintf(mybuf2, "%d", tbl1->res[a][0]); d1_CombatResults[screen][0]->value(mybuf2);
//printf("dDCA: %d:%d = %d\n", tbl1->res[a][0], tbl1->res[a][1], a);
					d1_CombatCritRoll[screen][0]->deactivate(); d1_CombatCrit[screen][0]->deactivate(); d1_CombatCalc[screen][1]->deactivate();
					d1_CombatCritRoll[screen][1]->deactivate(); d1_CombatCrit[screen][1]->deactivate(); d1_CombatCalc[screen][2]->deactivate();
//					d1_CombatCritTable[screen][0]->deactivate(); d1_CombatCritTable[screen][1]->deactivate();
					if (tbl1->res[a][1] != 0) {	// a crit
						d1_CombatCritRoll[screen][0]->activate();
						d1_CombatCrit[screen][0]->activate();
						d1_CombatCalc[screen][1]->activate();
						d1_CombatCrit[screen][0]->value(tbl1->res[a][1] - 64);
						d1_CombatCritRoll[screen][1]->deactivate();
						d1_CombatCrit[screen][1]->deactivate();
						d1_CombatCalc[screen][2]->deactivate();
//						d1_CombatCritTable[screen][0]->activate(); d1_CombatCritTable[screen][1]->deactivate();
					}
				} else {
					roll = atoi(d1_CombatAttkRoll[screen]->value()) + atoi(d1_CombatOB[screen]->value()) + atoi(d1_CombatParry[screen][0]->value()) + atoi(d1_CombatMods[screen][0]->value()) + atoi(d1_CombatAdj[screen]->value()) - (atoi(d1_CombatParry[screen][0]->value()) + atoi(d1_CombatMods[screen][1]->value()) + atoi(d1_CombatMods[screen][3]->value()));
					getD100AttackRoll(atbl, roll, 0);
					if (d100AttkTbl != NULL) {
						tbl2 = (attk_tab2 *)d100AttkTbl;
						a = d1_CombatDefenderArmor->value(); if (a < 0) { a = 0; } if (a > 19) { a = 19; }
						sprintf(mybuf2, "%d", tbl2->res[a][0]); d1_CombatResults[screen][0]->value(mybuf2);
//printf("dDCA: %d:%d = %d\n", tbl2->res[a][0], tbl2->res[a][1], a);
						d1_CombatCritRoll[screen][0]->deactivate(); d1_CombatCrit[screen][0]->deactivate(); d1_CombatCalc[screen][1]->deactivate();
						d1_CombatCritRoll[screen][1]->deactivate(); d1_CombatCrit[screen][1]->deactivate(); d1_CombatCalc[screen][2]->deactivate();
//						d1_CombatCritTable[screen][0]->deactivate(); d1_CombatCritTable[screen][1]->deactivate();
						if (tbl2->res[a][1] != 0) {	// a crit
							d1_CombatCritRoll[screen][0]->activate();
							d1_CombatCrit[screen][0]->activate();
							d1_CombatCalc[screen][1]->activate();
							d1_CombatCrit[screen][0]->value(tbl2->res[a][1] - 64);
							d1_CombatCritRoll[screen][1]->deactivate();
							d1_CombatCrit[screen][1]->deactivate();
							d1_CombatCalc[screen][2]->deactivate();
//							d1_CombatCritTable[screen][0]->activate(); d1_CombatCritTable[screen][1]->deactivate();
						}
					}
				}
				break;

		case 3:		// heal screen
				break;

		case 4:		// m&m screen				TODO
				roll = atoi(d1_CombatAttkRoll[screen]->value()) + atoi(d1_CombatOB[screen]->value()) + getAdjustment(config.i_actionInitID, MOD_MOVE) + atoi(d1_CombatMods[screen][0]->value()) - atoi(d1_CombatMods[screen][3]->value());
				if (roll > 350) { roll = 350; }
				a = (d1_CombatMMDifficulty->value() * 2) + 1;
				if (a < 0) { break; }
printf("Move: %d:%d\n", roll, a);
				if ((mtbl = (move_tab *)getD100Table("MM")) != NULL) {
					for (i=0; i<23; i++) {
						if (mtbl->st <= roll && mtbl->ed >= roll) {
							if (mtbl->res[a] > 0) {
								sprintf(mybuf2, "Completed %d%% of their action", mtbl->res[a]);
							} else {
								sprintf(mybuf2, "@B55@.Fumble !!!");
							}
							d1_ActionMessages->text(5, mybuf2);
						}
						mtbl++;
					}
				}
				d1_CombatAcceptAll[screen]->activate();
				break;
	}
}

/******************************************************************************/
void doD100CalcCritical(int screen, int line) {
char crt[4];
crit_tab *ctbl1;
crit_tab2 *ctbl2;
int i=0, roll=0;
int crtadj[] = {0, -20, -10, 0, 10, 20, 30, -50};

//printf("dDCC: %d:%d = %d\n", screen, line, d1_CombatCrit[screen][line]->value());

	switch (screen) {
		case 0:		// melee screen
		case 1:		// spell screen
		case 2:		// missile screen
				crt[0] = 'C'; crt[2]=crt[3]='\0';
//				if (line == 0) { crt[1] = d100WeaponUsed.c_damage[0]; } else { crt[1] = d100WeaponUsed.c_critical[0]; }
				strncpy(&crt[1], d1_CombatCritTable[screen][line]->value(), 2);			// get the crit as marked on the screen
				crt[3]=crt[2]; crt[2]='\0'; 

				i = d1_CombatCrit[screen][line]->value();
				if (config.i_diceSystem == DICE_MERP) {
					roll = atoi(d1_CombatCritRoll[screen][line]->value()) + crtadj[i];		// adjust the roll by the crit value
				} else {
					roll = atoi(d1_CombatCritRoll[screen][line]->value());
				}
				getD100CriticalRoll(crt, roll, i+64);
				if (d100CritTbl != NULL) {
					if (config.i_diceSystem == DICE_MERP) {
						ctbl1 = (crit_tab *)d100CritTbl;
						if (line == 0) { sprintf(mybuf2, "@B63@.1st Crit: %s", ctbl1->msg); } else { sprintf(mybuf2, "@B63@.2nd Crit: %s", ctbl1->msg); }
						d1_ActionMessages->text(4+line, mybuf2);
						for (i=0; i<8; i++) {
							sprintf(mybuf2, "%d", ctbl1->res[i] + atoi(d1_CombatResults[screen][i]->value())); 
							d1_CombatResults[screen][i]->value(mybuf2);
						}
					} else {
						ctbl2 = (crit_tab2 *)d100CritTbl;
						if (line == 0) { sprintf(mybuf2, "@B63@.1st Crit: %s", ctbl2->msg); } else { sprintf(mybuf2, "@B63@.2nd Crit: %s", ctbl2->msg); }
						d1_ActionMessages->text(4+line, mybuf2);
						for (i=0; i<8; i++) {
							sprintf(mybuf2, "%d", ctbl2->res[i] + atoi(d1_CombatResults[screen][i]->value())); 
							d1_CombatResults[screen][i]->value(mybuf2);
						}
					}
				}
				if (line == 0 && isdigit(crt[3]) != 0) {		// max crit value ?
//printf("Max crit = %c\n", d100WeaponUsed.c_damage[1]);
					i = d100WeaponUsed.c_damage[1] - 'a' + 1;
					if (d1_CombatCrit[screen][0]->value() > i) {
						d1_CombatCrit[screen][0]->value(i);
					}
				}
				if (line == 0 && d1_CombatCrit[screen][line]->value() > 2) {		// check for secondary crit
					if (strlen(d1_CombatCritTable[screen][1]->value()) > 0) {
//printf("Max crit = %c\n", d100WeaponUsed.c_critical[1]);
						strncpy(&crt[0], d1_CombatCritTable[screen][line]->value(), 2);	// get the crit as marked on the screen
						d1_CombatCritRoll[screen][1]->activate();
						d1_CombatCrit[screen][1]->activate();
						d1_CombatCrit[screen][1]->value(d1_CombatCrit[screen][0]->value() - 2);
						d1_CombatCalc[screen][2]->activate();
//						d1_CombatCritTable[screen][1]->activate();
						if (isdigit(crt[1]) != 0) {				// max crit value ?
							i = crt[1] - 'a' + 1;
							if (d1_CombatCrit[screen][1]->value() > i) {
								d1_CombatCrit[screen][1]->value(i);
							}
						}
					}
				}
				break;

		case 3:		// heal screen
				break;
	}
}

/******************************************************************************/
void doD100ActionModifiers(int screen, int modifier) {
int i=0;

printf("dDAM: %d:%d\n", screen, modifier);

	switch (screen) {
		case 0:		// melee screen
		case 4:		// heal screen
				if (d100ActionModifiersFlags[screen][modifier] == 1) {	// turning it off
					i = atoi(d1_CombatMods[screen][0]->value()) - d100ActionModifiers[screen][modifier];
				} else {
					i = atoi(d1_CombatMods[screen][0]->value()) + d100ActionModifiers[screen][modifier];
				}
				sprintf(mybuf2, "%d", i); d1_CombatMods[screen][0]->value(mybuf2);
				if (d100ActionModifiersFlags[screen][modifier] == 0) {
					d100ActionModifiersFlags[screen][modifier] = 1;
				} else {
					d100ActionModifiersFlags[screen][modifier] = 0;
				}
				break;

		case 1:		// spell screen
				switch (modifier) {
					case 1:		// instantaneous
								if (d100ActionModifiersFlags[screen][modifier] == 1) {	// turning it off
									players[config.i_actionInitID].i_roundsUntil[ROUND_SPELL_CHG] -= 2;
								} else {
									players[config.i_actionInitID].i_roundsUntil[ROUND_SPELL_CHG] += 2;
								}
								break;
					case 3:		// defd -AG
								break;
					default:
								if (d100ActionModifiersFlags[screen][modifier] == 1) {	// turning it off
									i = atoi(d1_CombatMods[screen][0]->value()) - d100ActionModifiers[screen][modifier];
								} else {
									i = atoi(d1_CombatMods[screen][0]->value()) + d100ActionModifiers[screen][modifier];
								}
								sprintf(mybuf2, "%d", i); d1_CombatMods[screen][0]->value(mybuf2);
								break;
				}
				if (d100ActionModifiersFlags[screen][modifier] == 0) {
					d100ActionModifiersFlags[screen][modifier] = 1;
				} else {
					d100ActionModifiersFlags[screen][modifier] = 0;
				}
				break;

		case 2:		// missile screen
				break;

		case 3:		// heal screen
				break;
	}
}

/******************************************************************************/
void doD100SpellSearch(const char *spell) {
spell_tab *st;
int i=0, j=0;

//printf("dDSS: %s\n", spell);

	i = strlen(spell);
	if ((st = (spell_tab *)getD100Table("XS")) != NULL) {
		d1_SpellSearchFound->clear(); d1_SpellSearchDetails->clear();
		while (st->realm_id != -1) {
			if (strncasecmp(st->spell_name, spell, i) == 0) {
				d1_SpellSearchFound->add(st->spell_name);
			}
			st++;
		}
	}
}

/******************************************************************************/
void doD100SpellSearchAction(int action, int spell) {
spell_tab *st;
int i=0, j=0;

	i = strlen(d1_SpellSearchFound->text(spell));

//printf("dDSSA: %d:%d:%s\n", action, spell, d1_SpellSearchFound->text(spell));

	switch(action) {
		case 0:	// spell selected, display details
				if ((st = (spell_tab *)getD100Table("XS")) != NULL) {
					d1_SpellSearchDetails->clear();
					while (st->realm_id != -1) {
						if (strncasecmp(st->spell_name, d1_SpellSearchFound->text(spell), i) == 0) {
							sprintf(mybuf2, " Name: %s", st->spell_name); d1_SpellSearchDetails->add(mybuf2);
							sprintf(mybuf2, "   AoE: %s", st->spell_aoe); d1_SpellSearchDetails->add(mybuf2);
							sprintf(mybuf2, "    Dur: %s", st->spell_duration); d1_SpellSearchDetails->add(mybuf2);
							sprintf(mybuf2, "Range: %s", st->spell_range); d1_SpellSearchDetails->add(mybuf2);
							sprintf(mybuf2, "  Desc: %s", st->spell_desc); d1_SpellSearchDetails->add(mybuf2);
							sprintf(mybuf2, " Level: %d", st->spell_lvl); d1_SpellSearchDetails->add(mybuf2);
							if (st->realm_id == 0) {
								d1_SpellSearchDetails->add(" Realm: Essence");
							} else {
								d1_SpellSearchDetails->add(" Realm: Channel");
							}
							break;

						}
						st++;
					}
				}
				break;
	}
}

/******************************************************************************/
void doD100IgnoreAdjustment(int cd) {

if (config.flags.f_debug == 1) printf("dIA: %d (%d/%d)\n", cd);

	if (players[cd].flags.f_ignoreBleed != 0) {		// No Bleeding
		d1_CombatResults[0][2]->value("0"); d1_CombatResults[1][2]->value("0");
		d1_CombatResults[2][2]->value("0"); d1_CombatResults[3][2]->value("0");
	}
	if (players[cd].flags.f_ignoreStun != 0) {		// No Stun
		d1_CombatResults[0][3]->value("0"); d1_CombatResults[1][3]->value("0");
		d1_CombatResults[2][3]->value("0"); d1_CombatResults[3][3]->value("0");
	}
}

/******************************************************************************/
void doD100CriticalAdjustment(int tile, int line, int cd) {
int i, j;

/*
	i = players[cd].CritAdj;
	j = actionsMeleeCrit1Result[line]->value();
if (config.flags.f_debug == 1) printf("dCA: %d (%d:%d/%d)\n", cd, line, i, j);
	switch (i) {
		case 1:		// -1
		case 2:		// -2
			if (line == 0) {
				if (j >= i) {
					actionsMeleeCrit1Result[line]->value(j-i);
				}
				if (j == 6) {	// T crit
					actionsMeleeCrit1Result[line]->value(0);
				}
			}
			break;
		case 3:		// Large
			j = actionsMeleeCrit1Result[tile]->value();
			if (j < 2 || j > 6) {		// Ignore A, T crits
			}
			break;
		case 4:		// SuperLarge
			j = actionsMeleeCrit1Result[tile]->value();
			if (j < 4 || j > 6) {		// Ignore A-C, T crits
			}
			break;
	}
*/
}

/******************************************************************************/
void doD100FumbleResult(int ca, int screen, int val) {
crit_tab *ctbl1;
crit_tab2 *ctbl2;
char ft[3] = {"FW"};

printf("dDFR: %d = %d:%d\n", ca, screen, val);

	switch (screen) {
		case 0:			// melee
				ft[1] = 'W';
				break;
		case 1:			// spell
				ft[1] = 'S';
				break;
		case 2:			// missile
				ft[1] = 'I';
				break;
		case 3:			// move
				ft[1] = 'M';
				break;
	}
if (config.flags.f_debug == 1) printf("dFR: %d (%d/%d) %s\n", ca, screen, val, ft);
	getD100CriticalRoll(ft, val, ' ');
	if (d100CritTbl != NULL) {
		if (config.i_diceSystem == DICE_MERP) {
			ctbl1 = (crit_tab *) d100CritTbl;
if (config.flags.f_debug == 1) printf("FC: %d (%d/%d: %s)\n", val, ctbl1->st, ctbl1->ed, ctbl1->msg);
			d1_ActionMessages->text(3, ctbl1->msg);
			sprintf(mybuf2, "%d", ctbl1->res[0]); d1_CombatResults[0][0]->value(mybuf2); // Hits
			sprintf(mybuf2, "%d", ctbl1->res[1]); d1_CombatResults[0][1]->value(mybuf2); // Act. Pen
			sprintf(mybuf2, "%d", ctbl1->res[2]); d1_CombatResults[0][2]->value(mybuf2); // Bleed
			sprintf(mybuf2, "%d", ctbl1->res[3]); d1_CombatResults[0][3]->value(mybuf2); // Stun
			sprintf(mybuf2, "%d", ctbl1->res[4]); d1_CombatResults[0][4]->value(mybuf2); // Parry
			sprintf(mybuf2, "%d", ctbl1->res[5]); d1_CombatResults[0][5]->value(mybuf2); // No Parry
			sprintf(mybuf2, "%d", ctbl1->res[6]); d1_CombatResults[0][6]->value(mybuf2); // Death
			sprintf(mybuf2, "%d", ctbl1->res[7]); d1_CombatResults[0][7]->value(mybuf2); // Inactive
		} else {
			ctbl2 = (crit_tab2 *) d100CritTbl;
if (config.flags.f_debug == 1) printf("FC: %d (%d/%d: %s)\n", val, ctbl2->st, ctbl2->ed, ctbl2->msg);
			d1_ActionMessages->text(3, ctbl2->msg);
			sprintf(mybuf2, "%d", ctbl2->res[0]); d1_CombatResults[0][0]->value(mybuf2); // Hits
			sprintf(mybuf2, "%d", ctbl2->res[1]); d1_CombatResults[0][1]->value(mybuf2); // Act. Pen
			sprintf(mybuf2, "%d", ctbl2->res[2]); d1_CombatResults[0][2]->value(mybuf2); // Bleed
			sprintf(mybuf2, "%d", ctbl2->res[3]); d1_CombatResults[0][3]->value(mybuf2); // Stun
			sprintf(mybuf2, "%d", ctbl2->res[4]); d1_CombatResults[0][4]->value(mybuf2); // Parry
			sprintf(mybuf2, "%d", ctbl2->res[5]); d1_CombatResults[0][5]->value(mybuf2); // No Parry
			sprintf(mybuf2, "%d", ctbl2->res[6]); d1_CombatResults[0][6]->value(mybuf2); // Death
			sprintf(mybuf2, "%d", ctbl2->res[7]); d1_CombatResults[0][7]->value(mybuf2); // Inactive
		}
		doD100IgnoreAdjustment(ca);
		return;
	}
}

/******************************************************************************/
void getD100AttackRoll(char *tbl, int roll, int um) {
attk_tab *tbl1;
attk_tab2 *tbl2;

if (config.flags.f_debug == 1) printf("gAR: %s = %d/%d/%d\n", tbl, roll, um, config.i_diceSystem);
//printf("gAR: %s = %d/%d/%d\n", tbl, roll, um, config.i_diceSystem);

//	if (roll > 150 && MEKSconfig.use_150 == 1) {
//		sprintf(mybuf2, "+150 Roll. Add +%d to 1st Crit Roll (%d)", (((roll-150)/25)+1)*5, roll);
//		doSystemAlert(mybuf2);
//	}

	roll = (roll < 1)?1:roll;
	roll = (roll > 150)?150:roll;
	d100AttkTbl = getD100Table(tbl);

	if (d100AttkTbl != NULL) {
		if (config.i_diceSystem == DICE_MERP) {
			tbl1 = (attk_tab *)d100AttkTbl;
			for (int i=0; i<28; i++) {
				if (tbl1->st <= roll && tbl1->ed >= roll) {
					if (tbl1->um_flag == um) { 
if (config.flags.f_debug == 1) printf("gAR: %d:%d:%d:%d:%d\n", tbl1->res[0][0],tbl1->res[1][0],tbl1->res[2][0],tbl1->res[3][0],tbl1->res[4][0]);
						d100AttkTbl = (char *)tbl1;
						return;
					}
				}
				if (tbl1->ed >= 250) {
					d100AttkTbl = NULL;
					return;
				}
				tbl1++;
			}
		} else {
			tbl2 = (attk_tab2 *)d100AttkTbl;
			for (int i=0; i<136; i++) {
				if (tbl2->st <= roll && tbl2->ed >= roll) {
if (config.flags.f_debug == 1) printf("gAR: %d:%d:%d:%d:%d\n", tbl2->res[0][0],tbl2->res[1][0],tbl2->res[2][0],tbl2->res[3][0],tbl2->res[4][0]);
					d100AttkTbl = (char *)tbl2;
					return;
				}
				if (tbl2->st == 1) { break; }		// reached the end
				tbl2++;
			}
		}
	}

	d100AttkTbl = NULL;
	return;
}

/******************************************************************************/
void getD100CriticalRoll(char *tbl, int roll, char crit) {
crit_tab *tbl1;
crit_tab2 *tbl2;
char *tbl_crit;
int i, j;

if (config.flags.f_debug == 1) printf("gDCR: %s = %d:%c\n", tbl, roll, crit);
printf("gDCR: %s = %d:%c\n", tbl, roll, crit);

	roll = (roll < 1)?1:roll;
	roll = (roll > 120)?120:roll;
	tbl_crit = getD100Table(tbl);
	d100CritTbl = NULL;

	if (tbl_crit != NULL) {
		if (config.i_diceSystem == DICE_MERP) {
			tbl1 = (crit_tab *)tbl_crit;
			for (i=0; i<19; i++) {
				if (tbl1->st <= roll && tbl1->ed >= roll) {
if (config.flags.f_debug == 1) printf("gDCR: %d:%d:%d:%d:%d\n", tbl1->res[0],tbl1->res[1],tbl1->res[2],tbl1->res[3],tbl1->res[4]);
					d100CritTbl = (char *)tbl1;
					return;
				}
				tbl1++;
			}
		} else if (config.i_diceSystem == DICE_RMS) {
			tbl2 = (crit_tab2 *)tbl_crit;
			for (i=0; i<95; i++) {
				if (tbl2->st <= roll && tbl2->ed >= roll && tbl2->crit == crit) {
if (config.flags.f_debug == 1) printf("gDCR: %d:%d:%d:%d:%d\n", tbl2->res[0],tbl2->res[1],tbl2->res[2],tbl2->res[3],tbl2->res[4]);
					d100CritTbl = (char *)tbl2;
					return;
				}
				if (tbl2->ed == 350 && tbl2->crit == 'E') { break; }		// reached the end
				tbl2++;
			}
		}
	}

	d100CritTbl = NULL;

	return;
}

/******************************************************************************/
int getD100RRValue(int atk_lvl, int def, int def_lvl, unsigned char type) {
int rr=0;

	if (def_lvl > 15)
	  rr = 15 - def_lvl;
	else if (def_lvl > 10)
	  rr = 15 - ((def_lvl - 10) * 2);
	else if (def_lvl > 5)
	  rr = 30 - ((def_lvl - 5) * 3);
	else if (def_lvl > 1)
	  rr = 50 - ((def_lvl - 1) * 5);
	else
	  rr = 50;
	
	if (atk_lvl > 15)
	  rr += 50 + (atk_lvl-15);
	else if (atk_lvl > 10)
	  rr += 35 + ((atk_lvl - 10) * 2);
	else if (atk_lvl > 5)
	  rr += 20 + ((atk_lvl - 5) * 3);
	else if (atk_lvl > 1)
	  rr += (atk_lvl - 1) * 5;

	if (atk_lvl == def_lvl)
	  rr = 50;

	switch (type)
	{
		case 1:
	   case 'E': rr -= players[def].i_savingThrows[SAVE_ESSENCE];
		     break;
		case 0:
	   case 'F':		/* Fear is a channeling RR */
	   case 'C': rr -= players[def].i_savingThrows[SAVE_CHANNEL];
		     break;
		case 2:
	   case 'M': rr -= players[def].i_savingThrows[SAVE_MENTAL];
		     break;
	   case 'P': rr -= players[def].i_savingThrows[SAVE_POISON];
		     break;
	   case 'D': rr -= players[def].i_savingThrows[SAVE_DISEASE];
		     break;
	}
	rr -= getAdjustment(def, MOD_SAVE);

if (config.flags.f_debug == 1) printf("gRRV: %d:%d:%c = %d\n", atk_lvl, def_lvl, type, rr);

	return(rr);
}

/******************************************************************************/
int getD100StatBonus(int val) {
	if (val > 101) return +35;
	else if (val > 100) return +30;
	else if (val > 99) return +25;
	else if (val > 97) return +20;
	else if (val > 94) return +15;
	else if (val > 89) return +10;
	else if (val > 74) return +5;
	else if (val > 24) return +0;
	else if (val > 9) return -5;
	else if (val > 4) return -10;
	else if (val > 2) return -15;
	else if (val == 2) return -20;

	return -25;
}

/******************************************************************************/
int getD100DiceRoll() {
int val=0, i;

   val = i = getRND(100);
   while (i > 95) {
      i = getRND(100);
      val += i;
   }
   return val;
}

/******************************************************************************/
int doIconKeyPressed(int action) {
int event = Fl::event();

printf("Event: A=%d E=%d B=%d S=%d X=%d Y=%d T=%d\n", action, event, Fl::event_button(), Fl::event_state(), Fl::event_x(), Fl::event_y());

	return 0;
}

/******************************************************************************/

