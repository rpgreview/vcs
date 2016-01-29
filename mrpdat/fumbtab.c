
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab fum_w[19] = {
{0,5,     {0,0,0,0,0,0,0,0}, "Lose your grip. No futher activity this round.", ""},
{6,20,    {0,0,0,0,0,0,0,0}, "Slip, if weapon is 1H/non-magical it breaks.", ""},
{21,35,   {2,0,0,0,0,0,0,0}, "Bad follow-through.", ""},
{36,50,   {0,0,0,0,0,0,0,0}, "Drop weap, 2 rnd to recover, 1 to get another", ""},
{51,65,   {0,0,0,0,0,0,0,0}, "Lose wind ... -40 for 2 rounds.", "AK AP+40:2"},
{66,79,   {0,0,0,2,0,0,0,0}, "You stumble", ""},
{80,80,   {0,0,0,0,0,0,0,0}, "B Krush. If foe uses slash weap, arm broken", ""},
{81,86,   {0,0,0,2,0,0,0,0}, "Bite and swallow tongue.", ""},
{87,89,   {0,0,0,3,0,0,0,0}, "Lose grip on weapon and reality.", ""},
{90,90,   {0,0,0,0,0,0,0,0}, "C slash crit, weapon breaks.", ""},
{91,96,   {0,0,0,0,0,0,0,0}, "Closest friend takes a B crush crit.", ""},
{97,99,   {0,0,0,3,0,0,0,0}, "Stumble on unseen deceased turtle. Confused.", ""},
{100,100, {0,60,0,0,0,0,0,0}, "Pulled groin. Foe stunned 2 rnds (adjust)", ""},
{101,106, {0,0,0,3,0,0,0,0}, "Stagger and fall. If using Pole Arm it breaks.", ""},
{107,109, {0,0,0,4,0,0,0,0}, "Weapon breaks.", ""},
{110,110, {0,0,0,5,0,0,0,0}, "Weap stuck in ground. Mounted:vault 30', C Krush", ""},
{111,116, {0,0,0,3,0,0,0,0}, "Mount rears.", ""},
{117,119, {0,0,0,0,0,0,0,0}, "-90 to Activity for next 3 rounds.", "AK AP+90:3"},
{120,228, {0,0,0,0,0,0,0,0}, "Fall off, D crush crit.", ""}};

crit_tab fum_i[19] = {
{0,5,     {0,0,0,0,0,0,0,0}, "Lose grip, no further activity this round.", ""},
{6,20,    {0,0,0,0,0,0,0,0}, "Lose this round. Fumble loading.", ""},
{21,35,   {0,0,0,0,0,0,0,0}, "Fumble ammo. Lose this round and -50 to next.", "AK AP+50:2"},
{36,50,   {0,0,0,1,0,0,0,0}, "Break ammo", ""},
{51,65,   {0,0,0,1,0,0,0,0}, "Drop ammo.", ""},
{66,79,   {0,0,0,2,0,0,0,0}, "Really mishandle weapon.", ""},
{80,80,   {5,0,0,0,0,0,0,0}, "Not using XBow: lose ear, +2 hits/round.", ""},
{81,86,   {0,0,0,0,0,0,0,0}, "String breaks. 2 rnd reweapon, 6 to restring.", ""},
{87,89,   {0,0,0,0,0,0,0,0}, "Fumble ammo ... scattered over 10' radius.", ""},
{90,90,   {0,0,0,4,0,0,0,0}, "Weapon shatters.", ""},
{91,96,   {0,0,0,0,0,0,0,0}, "Miss target, -30 for 2 rounds.", "AK AP+30:2"},
{97,99,   {0,0,0,0,0,0,0,0}, "Slip and knock weapon 5' infront of you.", ""},
{100,100, {8,2,0,0,0,0,0,0}, "Missile through hand, it's now useless.", ""},
{101,106, {0,0,0,5,0,0,0,0}, "Slip and fall.", ""},
{107,109, {5,20,0,2,0,0,0,0}, "Fletching scratches eye.", ""},
{110,110, {0,0,0,0,0,0,0,0}, "Tip catches, closest object: A punc crit.", ""},
{111,116, {0,0,0,0,0,0,0,0}, "Make attack on closest combatant.", ""},
{117,119, {4,0,2,0,0,0,0,0}, "Lose a finger.", ""},
{120,228, {10,30,2,3,0,0,0,0}, "Pin foot to ground.", ""}};

crit_tab fum_s[19] = {
{0,5,     {0,0,0,0,0,0,0,0}, "Spell lost but not PPs.", ""},
{6,20,    {0,0,0,0,0,0,0,0}, "No spell cast/prepared next rnd.", ""},
{21,35,   {0,0,0,0,0,0,0,0}, "Indecision, spell delayed 1 round.", ""},
{36,50,   {0,0,0,0,0,0,0,0}, "Spell lost but not PPs. -30 for 3 rnds.", "AK AP+30:3"},
{51,65,   {0,0,0,1,0,0,0,0}, "Spell and PPs lost.", ""},
{66,79,   {0,0,0,2,0,0,0,0}, "Spell and PPs lost.", ""},
{80,80,   {15,0,0,60,0,0,0,100}, "Spell internalised. Down, uncon 1 hr.", ""},
{81,86,   {0,0,0,3,0,0,0,0}, "Spell lost but not PPs.", ""},
{87,89,   {20,0,0,0,0,0,0,0}, "Blind and deaf for 10 mins.", ""},
{90,90,   {20,0,0,60,0,0,0,100}, "Mild stroke, uncon 12 hrs.", ""},
{91,96,   {5,0,0,3,0,0,0,0}, "Misfire.", ""},
{97,99,   {0,0,0,0,0,0,0,0}, "Reverse target & caster in effects.", ""},
{100,100, {0,0,0,0,0,0,0,0}, "Lose spell casting for 2 weeks.", ""},
{101,106, {10,0,0,6,0,0,0,0}, "Misfire.", ""},
{107,109, {25,0,0,60,0,0,0,100}, "No casting for 3 weeks, uncon 3 hrs.", ""},
{110,110, {0,0,0,0,0,0,0,100}, "Severe stroke, paralysed from waist down.", ""},
{111,116, {0,0,0,3,0,0,0,0}, "Strays 20' right of target.", ""},
{117,119, {0,0,0,3,0,0,0,0}, "Strays 20' left of target.", ""},
{120,228, {0,0,0,0,0,0,0,0}, "Cast in opposite dir, no cast 3 months.", ""}};

crit_tab fum_m[19] = {
{0,5,     {0,0,0,0,0,0,0,0}, "Hesitate and fail to act.", ""},
{6,20,    {0,0,0,0,0,0,0,0}, "Second thoughts, wait 1 round.", ""},
{21,35,   {0,0,0,0,0,0,0,0}, "Slip, 30% of falling, -20 to M&M for 2 rnds.", "AK AP+20:2"},
{36,50,   {0,0,0,0,0,0,0,0}, "Stumble, 45% of falling, -30 M&M for 2 rnds.", "AK AP+30:2"},
{51,65,   {3,10,0,0,0,0,0,0}, "Stub toe, 60% of falling.", ""},
{66,79,   {0,0,0,2,0,0,0,0}, "Slip, 75% of falling.", ""},
{80,80,   {5,10,0,0,0,0,0,0}, "Twist ankle.", ""},
{81,86,   {3,0,0,0,0,0,0,0}, "Fall down, -20 for 3 rnds.", "AK AP+20:3"},
{87,89,   {7,20,0,1,0,0,0,0}, "Sprain ankle, tear tendons.", ""},
{90,90,   {8,30,0,3,0,0,0,0}, "Fall breaks leg.", ""},
{91,96,   {12,20,0,2,0,0,0,0}, "Fall breaks wrist.", ""},
{97,99,   {14,30,0,4,0,0,0,0}, "Fall breaks arm.", ""},
{100,100, {30,0,0,6,0,0,0,0}, "Fall breaks both arms.", ""},
{101,106, {15,50,0,3,0,0,0}, "Fall breaks leg.", ""},
{107,109, {10,80,0,4,0,0,0,0}, "Fall shatters knee.", ""},
{110,110, {0,0,0,0,0,0,0,100}, "Fall results in year long coma.", ""},
{111,116, {30,0,0,0,0,0,0,100}, "Fall, paralysed from waist down.", ""},
{117,119, {20,0,0,0,0,0,0,100}, "Fall, paralysed from neck down.", ""},
{120,228, {255,0,0,0,0,0,1,0}, "Fall, crush skull ... DEAD.", ""}};

/****************************************************************************/
main()
{
int file, i, j, sz;
char *rdata;

   if ((file = open("tab_fw.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
   {
       printf("\nUnable to OPEN tab_fw.dat\n");
       exit(0);
   }
   write(file, &fum_w[0].st, sizeof(fum_w));
   close(file);
   if ((file = open("tab_fi.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
   {
       printf("\nUnable to OPEN tab_fi.dat\n");
       exit(0);
   }
   write(file, &fum_i[0].st, sizeof(fum_i));
   close(file);
   if ((file = open("tab_fs.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
   {
       printf("\nUnable to OPEN tab_fs.dat\n");
       exit(0);
   }
   write(file, &fum_s[0].st, sizeof(fum_s));
   close(file);
   if ((file = open("tab_fm.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
   {
       printf("\nUnable to OPEN tab_fm.dat\n");
       exit(0);
   }
   write(file, &fum_m[0].st, sizeof(fum_m));
   close(file);
}
