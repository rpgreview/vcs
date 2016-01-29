/******************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include "ADMPmerp.h"

/******************************************************************************/
weapon_tab weap[MAX_D100WEAPONS] = {
{"BroadSword", "1E", '\0', 0, 0, "", 4, 3, 0, 160, 75, "S", "", ""},
{"Dagger", "1E", '\0', 0, 0, "", 1, 1, 15, 195, 18, "Pc", "", "CH | PL AK OB-15"},
{"Short Sword", "1E", '\0', 0, 0, "", 3, 2, 3, 185, 75, "S", "", "CH | PL AK OB-10 EL OB+10"},
{"HandAxe", "1E", '\0', 0, 0, "", 5, 4, 15, 160, 70, "S", "", "CH | PL AK OB+5"},
{"Scimitar", "1E", '\0', 0, 0, "", 4, 4, 0, 150, 60, "S", "", "CH | PL AK OB-5 EL OB+5"},
{"Whip", "1E", '\0', 0, 0, "", 3, 6, 0, 75, 10, "Gc", "sa", "AK OB-10"},

{"War Hammer", "1C", '\0', 0, 0, "", 5, 4, 10, 155, 60, "K", "", "AK OB+5"},
{"Club", "1C", '\0', 0, 0, "", 5, 4, 2, 140, 10, "Kd", "", "AK OB-10"},
{"Mace", "1C", '\0', 0, 0, "", 5, 2, 5, 250, 65, "K", "", ""},
{"Morning Star", "1C", '\0', 0, 0, "", 5, 8, 0, 145, 60, "K", "pa", "AK OB+10"},
{"Net", "1C", '\0', 0, 0, "", 3, 6, 10, 75, 15, "K", "", ""},

{"1-Javelin", "1E", '\0', 0, 0, "", 4, 4, 0, 105, 17, "P", "", "AK OB-10"},
{"1-Spear", "1E", '\0', 0, 0, "", 5, 4, 0, 130, 15, "P", "sa", "AK OB-5"},
{"2-Javelin", "2H", '\0', 0, 0, "", 4, 4, 0, 105, 17, "P", "", "AK OB+10"},
{"2-Spear", "2H", '\0', 0, 0, "", 5, 4, 0, 130, 15, "P", "sa", "AK OB+10"},

{"Lance", "2H", '\0', 0, 0, "", 10, 8, 0, 130, 30, "P", "u", "AK OB+15"}, 
{"Halbard", "2H", '\0', 0, 0, "", 7, 8, 0, 150, 25, "S", "p", "AK OB-5"},

{"Battle Axe", "2H", '\0', 0, 0, "", 7, 5, 0, 155, 70, "S", "k", "CH | PL AK OB+5 EL OB-5"},
{"Flail", "2H", '\0', 0, 0, "", 6, 8, 0, 150, 60, "K", "p", "AK OB+10"},
{"Qtr Staff", "2H", '\0', 0, 0, "", 4, 3, 0, 140, 20, "K", "", "AK OB-10"},
{"2H Sword", "2H", '\0', 0, 0, "", 8, 5, 0, 200, 75, "S", "k", ""},
{"Halbard", "2H", '\0', 0, 0, "", 7, 8, 0, 150, 25, "S", "p", "AK OB-5"},

{"Long Bow", "MS", '\0', 3, 0, "", 3, 5, 100, 0, 0, "P", "", ""},
{"Short Bow", "MS", '\0', 3, 0, "", 2, 4, 60, 0, 0, "P", "", ""},
{"Composite Bow", "MS", '\0', 3, 0, "", 3, 4, 75, 0, 0, "P", "", ""},
{"Crossbow", "MS", '\0', 3, 0, "", 8, 5, 90, 0, 0, "P", "", ""},
{"Sling", "MS", '\0', 3, 0, "", 1, 6, 50, 0, 0, "P", "", ""},
{"Bola", "MS", '\0', 3, 0, "", 3, 7, 40, 75, 12, "G", "ka", "AK OB-5"},

{"Pincher", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "S", "k", ""},
{"Bite", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "P", "sc", ""},
{"Claw", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "S", "pb", ""},
{"Stinger", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "P", "kc", ""},
{"Grapple", "GR", '\0', 4, 0, "", 5, 2, 0, 0, 0, "G", "uc", ""},
{"Bash", "GR", '\0', 4, 0, "", 5, 2, 0, 0, 0, "U", "kc", ""},
{"Tiny Animal", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "St", "", ""},
{"Trample", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "K", "k", ""},
{"Crush", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "K", "k", ""},
{"Kick", "TC", '\0', 4, 0, "", 5, 2, 0, 0, 0, "Ua", "", ""},
{"Tackle", "GR", '\0', 4, 0, "", 5, 2, 0, 0, 0, "Ga", "", ""},
{"Poison", "", '\0', 4, 0, "", 0, 0, 0, 0, 0, "", "", ""},
{"Fear", "", '\0', 4, 0, "", 0, 0, 0, 0, 0, "", "", ""},
{"Disease", "", '\0', 4, 0, "", 0, 0, 0, 0, 0, "", "", ""},
{"Con Drain", "", '\0', 4, 0, "", 0, 0, 0, 0, 0, "", "", ""},

{"Base Spell", "SB", '\0', 5, 0, "", 0, 0, 0, 0, 0, "", "", ""},
{"Shock Bolt", "SS", '\0', 5, 0, "", 0, 0, 0, 0, 0, "E", "", "CH | PL AK OB+5"},
{"Water Bolt", "SW", '\0', 5, 0, "", 0, 0, 0, 0, 0, "I", "", "PL | RL AK OB-10"},
{"Ice Bolt",  "SI", '\0', 5, 0, "", 0, 0, 0, 0, 0, "I", "c", "PL | RL AK OB-5"},
{"Fire Bolt", "SO", '\0', 5, 0, "", 0, 0, 0, 0, 0, "H", "", ""},
{"Lightning Bolt", "SO", '\0', 5, 0, "", 0, 0, 0, 0, 0, "E", "i", "CH | PL AK OB+10"},
{"Cold Ball", "SA", '\0', 5, 0, "", 0, 0, 0, 0, 0, "C", "", ""},
{"Fire Ball", "SA", '\0', 5, 0, "", 0, 0, 0, 0, 0, "H", "", ""},
{"Special", "", '\0', 5, 0, "", 0, 0, 0, 0, 0, "", "", ""},

{"", "", '\0', 0, 0, "", 0, 0, 0, 0, 0, "", "", ""}};

main()
{
int fn, i,j,sz;
char *rdata;

	if ((fn=open("tab_we.dat", O_CREAT|O_TRUNC|O_BINARY|O_RDWR,666)) == -1)
	{
		printf("Can't open TAB_WE.DAT ....\n\n");	
		exit(0);
	}
	write(fn, &weap[0].wp_dsc[0], sizeof(weap));
	close(fn);
}
