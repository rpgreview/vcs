
	//set whom to check
#define LANG_DEFENDER		1
#define LANG_ATTACKER		2

	//stat types
#define LANG_STRENGTH		3
#define LANG_DEXTERITY		4
#define LANG_CONSTITUTION		5
#define LANG_INTELLIGENCE		6
#define LANG_WISDOW		7
#define LANG_CHARISMA		8

	//stat type modifiers
#define LANG_STRENGTHMOD		9
#define LANG_DEXTERITYMOD		10
#define LANG_CONSTITUTIONMOD		11
#define LANG_INTELLIGENCEMOD		12
#define LANG_WISDOWMOD		13
#define LANG_CHARISMAMOD		14

	//save types
#define LANG_REFLEX		15
#define LANG_WILL		16
#define LANG_FORT		17

	//things to 'adjust'
#define LANG_BASEATTACKBONUS		18
#define LANG_ARMORCLASS		19
#define LANG_HITPOINTS		20
#define LANG_SAVE		21
#define LANG_DAMAGE		22
#define LANG_INITIATIVE		23
#define LANG_SKILL		24
#define LANG_SPELLRESIST		25
#define LANG_SAVEFORTITUDE		26
#define LANG_SAVEREFLEX		27
#define LANG_SAVEWISDOM		28

	//duration
#define LANG_ROUND		29
#define LANG_ROUNDPERLEVEL		30
#define LANG_MINPERLEVEL		31
#define LANG_HOURPERLEVEL		32
#define LANG_PLAYERLVL		33
#define LANG_PERMANENT		34

	//type of adjustment
#define LANG_ENHANCEMENT		35
#define LANG_MORALE		36
#define LANG_LUCK		37
#define LANG_HASTE		38
#define LANG_ARMOR		39
#define LANG_SHIELD		40
#define LANG_DEFLECTION		41
#define LANG_DODGE		42
#define LANG_OTHER		43
#define LANG_NATURAL		44

	//special descriptors
#define LANG_GOOD		45
#define LANG_EVIL		46
#define LANG_LAW		47
#define LANG_CHOAS		48
#define LANG_UNDEAD		49
#define LANG_MONSTER		50
#define LANG_HITDICE		51
#define LANG_SPELLLVL		52

	//check DC types
#define LANG_STRENGTHDC		53
#define LANG_DEXTERITYDC		54
#define LANG_CONSTITUTIONDC		55
#define LANG_INTELLIGENCEDC		56
#define LANG_WISDOMDC		57
#define LANG_CHARISMADC		58
#define LANG_SKILLDC		59
#define LANG_CHARLVLDC		60
#define LANG_CLASSLEVELDC		61
#define LANG_DC		62

	//spell/attack types
#define LANG_FIRE		63
#define LANG_SONIC		64
#define LANG_COLD		65
#define LANG_ACID		66
#define LANG_ELECTRICITY		67
#define LANG_PIERCING		68
#define LANG_BLUDGEONING		69
#define LANG_SLASHING		70
#define LANG_RANGED		71

	//per lvl calculations
#define LANG_PERLEVEL2		72
#define LANG_PERLEVEL3		73
#define LANG_PERLEVEL4		74

	//max level value
#define LANG_MAXLEVEL		75

	//if hit/crit'ed
#define LANG_HIT		76
#define LANG_CRITICAL		77
#define LANG_RANGEDATTK		78
#define LANG_TOUCHATTK		79

	//special actions
#define LANG_SOAK		80
#define LANG_STABILISE		81
#define LANG_DAMREDUCTION		82
#define LANG_QUEUE		83
#define LANG_MAX		84
#define LANG_REROLLDAMAGEEACHROUND		85
#define LANG_MISSCHANCE		86

	//DamReduction types
#define LANG_NONE		87
#define LANG_MAGICWEAPON		88
#define LANG_ANY		89
#define LANG_ADAMANTINE		90
#define LANG_BLUDGEONING		91
#define LANG_CHAOS		92
#define LANG_COLDIRON		93
#define LANG_EPIC		94
#define LANG_EVIL		95
#define LANG_GOOD		96
#define LANG_LAWFUL		97
#define LANG_MAGIC		98
#define LANG_SILVER		99
#define LANG_SLASHING		100
#define LANG_PIERCING		101
#define LANG_RANGED		102

	//save types
#define LANG_NODAMAGE		103
#define LANG_HALF		104
#define LANG_NOSAVE		105
#define LANG_NOSPELLRESISTANCE		106
#define LANG_RESAVE		107
#define LANG_SPELLRESISTANCE		108

	//show the message
#define LANG_MESSAGE		109

	//show the message and ask Y/N
#define LANG_MESSAGEBOOLEAN		110

	//show the message and ask for a value
#define LANG_MESSAGEINTEGER		111

	//statement conditions etc
#define LANG_IF		112
#define LANG_THEN		113
#define LANG_ELSE		114
#define LANG_AND		115
#define LANG_OR		116
#define LANG_DOT		117

//**********************************************

struct d20lang_def { char tkn_id; char *tkn_lstr, *tkn_sstr; }
d20lang_def language[] = {
	{LANG_DEFENDER, "DEFENDER", "DEFR"},
	{LANG_ATTACKER, "ATTACKER", "ATKR"},
	{LANG_STRENGTH, "STRENGTH", "STR"},
	{LANG_DEXTERITY, "DEXTERITY", "DEX"},
	{LANG_CONSTITUTION, "CONSTITUTION", "CON"},
	{LANG_INTELLIGENCE, "INTELLIGENCE", "INT"},
	{LANG_WISDOW, "WISDOW", "WIS"},
	{LANG_CHARISMA, "CHARISMA", "CHA"},
	{LANG_STRENGTHMOD, "STRENGTHMOD", "STRM"},
	{LANG_DEXTERITYMOD, "DEXTERITYMOD", "DEXM"},
	{LANG_CONSTITUTIONMOD, "CONSTITUTIONMOD", "CONM"},
	{LANG_INTELLIGENCEMOD, "INTELLIGENCEMOD", "INTM"},
	{LANG_WISDOWMOD, "WISDOWMOD", "WISM"},
	{LANG_CHARISMAMOD, "CHARISMAMOD", "CHAM"},
	{LANG_REFLEX, "REFLEX", "REF"},
	{LANG_WILL, "WILL", "WILL"},
	{LANG_FORT, "FORT", "FORT"},
	{LANG_BASEATTACKBONUS, "BASEATTACKBONUS", "BAB"},
	{LANG_ARMORCLASS, "ARMORCLASS", "AC"},
	{LANG_HITPOINTS, "HITPOINTS", "HP"},
	{LANG_SAVE, "SAVE", "SAVE"},
	{LANG_DAMAGE, "DAMAGE", "DAM"},
	{LANG_INITIATIVE, "INITIATIVE", "INIT"},
	{LANG_SKILL, "SKILL", "SKIL"},
	{LANG_SPELLRESIST, "SPELLRESIST", "SPRS"},
	{LANG_SAVEFORTITUDE, "SAVEFORTITUDE", "SFOR"},
	{LANG_SAVEREFLEX, "SAVEREFLEX", "SREF"},
	{LANG_SAVEWISDOM, "SAVEWISDOM", "SWIS"},
	{LANG_ROUND, "ROUND", "RND"},
	{LANG_ROUNDPERLEVEL, "ROUNDPERLEVEL", "RDPL"},
	{LANG_MINPERLEVEL, "MINPERLEVEL", "MNPL"},
	{LANG_HOURPERLEVEL, "HOURPERLEVEL", "HRPL"},
	{LANG_PLAYERLVL, "PLAYERLVL", "PLVL"},
	{LANG_PERMANENT, "PERMANENT", "PERM"},
	{LANG_ENHANCEMENT, "ENHANCEMENT", "ENHT"},
	{LANG_MORALE, "MORALE", "MORE"},
	{LANG_LUCK, "LUCK", "LUCK"},
	{LANG_HASTE, "HASTE", "HAST"},
	{LANG_ARMOR, "ARMOR", "ARMR"},
	{LANG_SHIELD, "SHIELD", "SHLD"},
	{LANG_DEFLECTION, "DEFLECTION", "DEFL"},
	{LANG_DODGE, "DODGE", "DDGE"},
	{LANG_OTHER, "OTHER", "OTHR"},
	{LANG_NATURAL, "NATURAL", "NATL"},
	{LANG_GOOD, "GOOD", "GOOD"},
	{LANG_EVIL, "EVIL", "EVIL"},
	{LANG_LAW, "LAW", "LAW"},
	{LANG_CHOAS, "CHOAS", "CHOS"},
	{LANG_UNDEAD, "UNDEAD", "UNDD"},
	{LANG_MONSTER, "MONSTER", "MONS"},
	{LANG_HITDICE, "HITDICE", "HD"},
	{LANG_SPELLLVL, "SPELLLVL", "SLVL"},
	{LANG_STRENGTHDC, "STRENGTHDC", "STDC"},
	{LANG_DEXTERITYDC, "DEXTERITYDC", "DXDC"},
	{LANG_CONSTITUTIONDC, "CONSTITUTIONDC", "CODC"},
	{LANG_INTELLIGENCEDC, "INTELLIGENCEDC", "INDC"},
	{LANG_WISDOMDC, "WISDOMDC", "WIDC"},
	{LANG_CHARISMADC, "CHARISMADC", "CHDC"},
	{LANG_SKILLDC, "SKILLDC", "SKDC"},
	{LANG_CHARLVLDC, "CHARLVLDC", "CLDC"},
	{LANG_CLASSLEVELDC, "CLASSLEVELDC", "LLDC"},
	{LANG_DC, "DC", "DC"},
	{LANG_FIRE, "FIRE", "FIRE"},
	{LANG_SONIC, "SONIC", "SONC"},
	{LANG_COLD, "COLD", "COLD"},
	{LANG_ACID, "ACID", "ACID"},
	{LANG_ELECTRICITY, "ELECTRICITY", "ELEC"},
	{LANG_PIERCING, "PIERCING", "PIER"},
	{LANG_BLUDGEONING, "BLUDGEONING", "BLUD"},
	{LANG_SLASHING, "SLASHING", "SLAS"},
	{LANG_RANGED, "RANGED", "RANG"},
	{LANG_PERLEVEL2, "PERLEVEL2", "PLV2"},
	{LANG_PERLEVEL3, "PERLEVEL3", "PLV3"},
	{LANG_PERLEVEL4, "PERLEVEL4", "PLV4"},
	{LANG_MAXLEVEL, "MAXLEVEL", "MXLV"},
	{LANG_HIT, "HIT", "HIT"},
	{LANG_CRITICAL, "CRITICAL", "CRIT"},
	{LANG_RANGEDATTK, "RANGEDATTK", "RATK"},
	{LANG_TOUCHATTK, "TOUCHATTK", "TATK"},
	{LANG_SOAK, "SOAK", "SOAK"},
	{LANG_STABILISE, "STABILISE", "STAB"},
	{LANG_DAMREDUCTION, "DAMREDUCTION", "DRED"},
	{LANG_QUEUE, "QUEUE", "QUE"},
	{LANG_MAX, "MAX", "MAX"},
	{LANG_REROLLDAMAGEEACHROUND, "REROLLDAMAGEEACHROUND", "RDER"},
	{LANG_MISSCHANCE, "MISSCHANCE", "MSCH"},
	{LANG_NONE, "NONE", "NONE"},
	{LANG_MAGICWEAPON, "MAGICWEAPON", "MAGW"},
	{LANG_ANY, "ANY", "ANY"},
	{LANG_ADAMANTINE, "ADAMANTINE", "ADAM"},
	{LANG_BLUDGEONING, "BLUDGEONING", "BLUD"},
	{LANG_CHAOS, "CHAOS", "CHOS"},
	{LANG_COLDIRON, "COLDIRON", "CIRN"},
	{LANG_EPIC, "EPIC", "EPIC"},
	{LANG_EVIL, "EVIL", "EVIL"},
	{LANG_GOOD, "GOOD", "GOOD"},
	{LANG_LAWFUL, "LAWFUL", "LAW"},
	{LANG_MAGIC, "MAGIC", "MAGC"},
	{LANG_SILVER, "SILVER", "SILV"},
	{LANG_SLASHING, "SLASHING", "SLAS"},
	{LANG_PIERCING, "PIERCING", "PIER"},
	{LANG_RANGED, "RANGED", "RANG"},
	{LANG_NODAMAGE, "NODAMAGE", "NDAM"},
	{LANG_HALF, "HALF", "HALF"},
	{LANG_NOSAVE, "NOSAVE", "NSAV"},
	{LANG_NOSPELLRESISTANCE, "NOSPELLRESISTANCE", "NOSR"},
	{LANG_RESAVE, "RESAVE", "RSAV"},
	{LANG_SPELLRESISTANCE, "SPELLRESISTANCE", "SR"},
	{LANG_MESSAGE, "MESSAGE", "MESG"},
	{LANG_MESSAGEBOOLEAN, "MESSAGEBOOLEAN", "MESB"},
	{LANG_MESSAGEINTEGER, "MESSAGEINTEGER", "MESI"},
	{LANG_IF, "IF", "IF"},
	{LANG_THEN, "THEN", "THEN"},
	{LANG_ELSE, "ELSE", "ELSE"},
	{LANG_AND, "AND", "AND"},
	{LANG_OR, "OR", "OR"},
	{LANG_DOT, ".", "."}
};