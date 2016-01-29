// static void cb_d1_CombatDefenderArmor(Fl_Choice*, void*) { doD100ActionOption(0,5); }
//static void cb_d1_CombatSpecAttk1(Fl_Button*, void*) { doD100ActionOption(1,2); }

static void cb_d1_DefenderList0(Fl_Browser* o, void*) { doD100SelectDefender(0, o->value()); }
static void cb_d1_CombatWeaponUsed0(Fl_Browser* o, void*) { doD100SelectWeapon(0, o->value()); }
static void cb_d1_CombatSpecAttk0(Fl_Button*, void*) { doD100ActionOption(0,2); }
static void cb_d1_CombatCalc01(Fl_Button*, void*) { doD100CalcAttack(0); }
static void cb_d1_CombatCalc02(Fl_Button*, void*) { doD100CalcCritical(0,0); }
static void cb_d1_CombatCalc03(Fl_Button*, void*) { doD100CalcCritical(0,1); }
static void cb_d1_CombatAcceptThis0(Fl_Button*, void*) { doD100ActionOption(0,0); }
static void cb_d1_CombatAcceptAll0(Fl_Button*, void*) { doD100ActionOption(0,1); }
static void cb_d10_CombatModifiers0(Fl_Check_Browser* o, void*) { doD100ActionModifiers(0, o->value()); }

static void cb_d1_DefenderList1(Fl_Browser* o, void*) { doD100SelectDefender(1, o->value()); }
static void cb_d1_CombatWeaponUsed1(Fl_Browser* o, void*) { doD100SelectWeapon(1, o->value()); }
static void cb_d1_CombatCalc11(Fl_Button*, void*) { doD100CalcAttack(1); }
static void cb_d1_CombatCalc12(Fl_Button*, void*) { doD100CalcCritical(1,0); }
static void cb_d1_CombatCalc13(Fl_Button*, void*) { doD100CalcCritical(1,1); }
static void cb_d1_CombatAcceptThis1(Fl_Button*, void*) { doD100ActionOption(1,0); }
static void cb_d1_CombatAcceptAll1(Fl_Button*, void*) { doD100ActionOption(1,1); }
static void cb_d10_CombatModifiers1(Fl_Check_Browser* o, void*) { doD100ActionModifiers(1, o->value()); }

static void cb_d1_DefenderList2(Fl_Browser* o, void*) { doD100SelectDefender(2, o->value()); }
static void cb_d1_CombatWeaponUsed2(Fl_Browser* o, void*) { doD100SelectWeapon(2, o->value()); }
static void cb_d1_CombatSpecAttk2(Fl_Button*, void*) { doD100ActionOption(2,2); }
static void cb_d1_CombatCalc21(Fl_Button*, void*) { doD100CalcAttack(2); }
static void cb_d1_CombatCalc22(Fl_Button*, void*) { doD100CalcCritical(2,0); }
static void cb_d1_CombatCalc23(Fl_Button*, void*) { doD100CalcCritical(2,1); }
static void cb_d1_CombatAcceptThis2(Fl_Button*, void*) { doD100ActionOption(2,0); }
static void cb_d1_CombatAcceptAll2(Fl_Button*, void*) { doD100ActionOption(2,1); }
static void cb_d10_CombatModifiers2(Fl_Check_Browser* o, void*) { doD100ActionModifiers(2, o->value()); }

static void cb_d1_DefenderList3(Fl_Browser* o, void*) { doD100SelectDefender(3, o->value()); }

static void cb_d1_CombatCalc41(Fl_Button*, void*) { doD100CalcAttack(4); }
static void cb_d1_CombatAcceptThis4(Fl_Button*, void*) { doD100ActionOption(4,0); }
static void cb_d1_CombatAcceptAll4(Fl_Button*, void*) { doD100ActionOption(4,1); }
static void cb_d10_CombatModifiers4(Fl_Check_Browser* o, void*) { doD100ActionModifiers(4, o->value()); }

static void cb_d1_CombatD100Roll1(Fl_Button*, void*) { doD100ActionOption(0,3); }
static void cb_d1_CombatD100Roll2(Fl_Button*, void*) { doD100ActionOption(1,3); }
static void cb_d1_CombatD100Roll3(Fl_Button*, void*) { doD100ActionOption(2,3); }
static void cb_d1_CombatD100Roll4(Fl_Button*, void*) { doD100ActionOption(3,3); }
static void cb_d1_CombatD100Roll5(Fl_Button*, void*) { doD100ActionOption(4,3); }

static void cb_d1_CombatAcceptThis3(Fl_Button*, void*) { doD100ActionOption(3,0); }
static void cb_d1_CombatAcceptAll3(Fl_Button*, void*) { doD100ActionOption(3,1); }
