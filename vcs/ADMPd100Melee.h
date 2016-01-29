extern Fl_Browser* d1_DefenderList[5];
extern Fl_Browser* d1_CombatWeaponUsed[4];
extern Fl_Browser* d1_CombatWeaponDetails[4];
extern Fl_Input* d1_CombatParry[4][2];
extern Fl_Button* d1_CombatSpecAttk[4];
extern Fl_Input* d1_CombatAttkRoll[5];
extern Fl_Input* d1_CombatAdj[5];
extern Fl_Input* d1_CombatOB[5];
extern Fl_Button* d1_CombatCalc[5][3];
extern Fl_Input* d1_CombatCritRoll[4][2];
extern Fl_Choice* d1_CombatCrit[4][2];
extern Fl_Input* d1_CombatResults[5][8];
extern Fl_Button* d1_CombatAcceptThis[5];
extern Fl_Button* d1_CombatAcceptAll[5];
extern Fl_Check_Browser* d1_CombatModifiers[5];
extern Fl_Input* d1_CombatMods[5][4];
extern Fl_Input* d1_CombatAttkTable[4];
extern Fl_Input* d1_CombatCritTable[4][2];
extern Fl_Button* d1_CombatD100Roll[5];

        { Fl_Browser* o = d1_DefenderList[scrn] = new Fl_Browser(5, 230, 180, 315);
          o->type(2);
          o->color((Fl_Color)6);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->align(FL_ALIGN_TOP_LEFT);
        }
if (scrn < 4) {
	if (scrn != 3) {
        { Fl_Browser* o = d1_CombatWeaponUsed[scrn] = new Fl_Browser(195, 240, 155, 95, "Weapon Used");
          o->type(2);
          o->color((Fl_Color)2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->align(FL_ALIGN_TOP_LEFT);
        }
        { Fl_Browser* o = d1_CombatWeaponDetails[scrn] = new Fl_Browser(195, 405, 215, 134, "Weapon Details");
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->align(FL_ALIGN_TOP_LEFT);
        }
        { Fl_Input* o = d1_CombatAttkTable[scrn] = new Fl_Input(495, 230, 30, 25, "Attk Table");
//          o->type(2);
          o->color((Fl_Color)2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
			 o->tooltip("The attack table to be used. You can edit/change this to do a special attack");
        }
        { Fl_Input* o = d1_CombatParry[scrn][0] = new Fl_Input(495, 290, 35, 25, "Parry: Attker");
          o->type(2);
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatParry[scrn][1] = new Fl_Input(565, 290, 35, 25, "Defd");
          o->type(2);
          o->color((Fl_Color)6);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Button* o = d1_CombatSpecAttk[scrn] = new Fl_Button(690, 285, 45, 25, "Sp.Attk");
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
        }
	}
}
        { Fl_Input* o = d1_CombatAttkRoll[scrn] = new Fl_Input(495, 325, 35, 25, "Attk Roll:");
          o->type(2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatAdj[scrn] = new Fl_Input(560, 325, 35, 25, "Adj:");
          o->type(2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatOB[scrn] = new Fl_Input(625, 325, 35, 25, "OB:");
          o->type(2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Button* o = d1_CombatCalc[scrn][0] = new Fl_Button(690, 325, 45, 25, "Calc");
          o->labelsize(ADMP_LABEL_SIZE);
        }
        { Fl_Button* o = d1_CombatD100Roll[scrn] = new Fl_Button(760, 285, 50, 25, "d100");
          o->color((Fl_Color)1);
          o->labelsize(ADMP_LABEL_SIZE);
        }

if (scrn == 4) {
	d1_CombatAttkRoll[scrn]->label("Move Roll");
	d1_CombatOB[scrn]->resize(640, 325, 35, 25); d1_CombatOB[scrn]->label("M&M");
}

if (scrn < 3) {
        { Fl_Input* o = d1_CombatCritRoll[scrn][0] = new Fl_Input(495, 355, 35, 25, "1st Crit Roll:");
          o->type(2);
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->deactivate();
        }
        { Fl_Choice* o = d1_CombatCrit[scrn][0] = new Fl_Choice(560, 355, 45, 25, "Crit:");
          o->down_box(FL_BORDER_BOX);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->add("-"); o->add("A"); o->add("B"); o->add("C"); o->add("D"); o->add("E"); o->add("T");
          o->deactivate();
        }
        { Fl_Button* o = d1_CombatCalc[scrn][1] = new Fl_Button(625, 355, 45, 25, "Calc");
          o->labelsize(ADMP_LABEL_SIZE);
          o->deactivate();
        }
        { Fl_Input* o = d1_CombatCritTable[scrn][0] = new Fl_Input(700, 355, 30, 25, "Tbl:");
//          o->type(2);
          o->color((Fl_Color)2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
			 o->tooltip("The critical table to be used. You can edit/change this to do a special attack");
          o->deactivate();
        }
        { Fl_Input* o = d1_CombatCritRoll[scrn][1] = new Fl_Input(495, 385, 35, 25, "2nd Crit Roll:");
          o->type(2);
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->deactivate();
        }
        { Fl_Choice* o = d1_CombatCrit[scrn][1] = new Fl_Choice(560, 385, 45, 25, "Crit:");
          o->down_box(FL_BORDER_BOX);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->add("-"); o->add("A"); o->add("B"); o->add("C"); o->add("D"); o->add("E"); o->add("T");
          o->deactivate();
        }
        { Fl_Button* o = d1_CombatCalc[scrn][2] = new Fl_Button(625, 385, 45, 25, "Calc");
          o->labelsize(ADMP_LABEL_SIZE);
          o->deactivate();
        }
        { Fl_Input* o = d1_CombatCritTable[scrn][1] = new Fl_Input(700, 385, 30, 25, "Tbl:");
//          o->type(2);
          o->color((Fl_Color)2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
			 o->tooltip("The critical table to be used. You can edit/change this to do a special attack");
          o->deactivate();
        }
}
        { Fl_Input* o = d1_CombatResults[scrn][0] = new Fl_Input(495, 420, 35, 25, "Results: HP");
          o->type(2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatResults[scrn][1] = new Fl_Input(585, 420, 35, 25, "APen:");
          o->type(2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatResults[scrn][2] = new Fl_Input(495, 450, 35, 25, "Bleed:");
          o->type(2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatResults[scrn][3] = new Fl_Input(585, 450, 35, 25, "Stun:");
          o->type(2); o->labelsize(ADMP_LABEL_SIZE); o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatResults[scrn][4] = new Fl_Input(495, 480, 35, 25, "Parry:");
          o->type(2); o->labelsize(ADMP_LABEL_SIZE); o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatResults[scrn][5] = new Fl_Input(585, 480, 35, 25, "NoParry:");
          o->type(2); o->labelsize(ADMP_LABEL_SIZE); o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatResults[scrn][6] = new Fl_Input(495, 510, 35, 25, "Death:");
          o->type(2); o->labelsize(ADMP_LABEL_SIZE); o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatResults[scrn][7] = new Fl_Input(585, 510, 35, 25, "Inact:");
          o->type(2); o->labelsize(ADMP_LABEL_SIZE); o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Button* o = d1_CombatAcceptThis[scrn] = new Fl_Button(645, 237, 115, 25, "Accept this Attack");
          o->labelsize(ADMP_LABEL_SIZE);
        }
        { Fl_Button* o = d1_CombatAcceptAll[scrn] = new Fl_Button(788, 237, 115, 25, "All Attacks done");
          o->labelsize(ADMP_LABEL_SIZE);
        }
        { Fl_Check_Browser* o = d1_CombatModifiers[scrn] = new Fl_Check_Browser(760, 365, 150, 175, "Modifiers");
          o->type(3);
          o->color((Fl_Color)2);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
          o->align(FL_ALIGN_TOP_LEFT);
          o->when(FL_WHEN_RELEASE_ALWAYS);
        }
        { Fl_Input* o = d1_CombatMods[scrn][0] = new Fl_Input(715, 428, 35, 25, "Mods: OB");
          o->type(2);
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatMods[scrn][1] = new Fl_Input(715, 454, 35, 25, "DB");
          o->type(2);
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatMods[scrn][2] = new Fl_Input(715, 480, 35, 25, "Damage");
          o->type(2);
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
        { Fl_Input* o = d1_CombatMods[scrn][3] = new Fl_Input(715, 506, 35, 25, "APen");
          o->type(2);
          o->color((Fl_Color)3);
          o->labelsize(ADMP_LABEL_SIZE);
          o->textsize(ADMP_TEXT_SIZE);
        }
if (scrn == 1) { 		// spells
	d1_CombatWeaponUsed[scrn]->label("Spell Used"); 
	d1_CombatWeaponUsed[scrn]->resize(195, 240, 155, 145);
	d1_CombatParry[scrn][0]->deactivate();
	d1_CombatParry[scrn][1]->deactivate();
} else if (scrn == 4) {		// move
	d1_CombatAcceptThis[scrn]->label("Accept this Move");
	d1_CombatAcceptAll[scrn]->label("All Moves Done");
	d1_CombatMods[scrn][0]->label("Mods: Move");
} else if (scrn == 3) {		// heal
 d1_CombatResults[scrn][0]->resize(495, 360, 35, 25);
 d1_CombatResults[scrn][1]->resize(585, 360, 35, 25);
 d1_CombatResults[scrn][2]->resize(495, 390, 35, 25);
 d1_CombatResults[scrn][3]->resize(585, 390, 35, 25);
 d1_CombatResults[scrn][4]->resize(495, 420, 35, 25);
 d1_CombatResults[scrn][5]->resize(585, 420, 35, 25);
 d1_CombatResults[scrn][6]->resize(495, 450, 35, 25);
 d1_CombatResults[scrn][7]->resize(585, 450, 35, 25);
 d1_CombatAcceptThis[scrn]->label("Accept this Heal");
 d1_CombatAcceptAll[scrn]->label("All Healing Done");
}
