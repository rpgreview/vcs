#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[19] = {
{1,5, 'E', {15,0,0,0,0,0,0,0}, "Fumble your weapon & must parry next rnd.", ""},
{6,10, 'E', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'E', {8,0,0,0,0,0,0,0}, "+8 hits.", ""},
{16,20, 'E', {10,0,0,0,0,0,0,0}, "+10 hits.", ""},
{21,35, 'E', {15,0,0,0,0,0,0,0}, "+15 hits.", ""},
{36,45, 'E', {18,0,0,0,0,0,0,0}, "+18 hits.", ""},
{46,50, 'E', {25,0,0,0,0,0,0,0}, "+25 hits.", ""},
{51,55, 'E', {30,0,0,0,0,0,3,3}, "Abdomenal strike. Dies in 3 rnds.",""},
{56,60, 'E', {30,0,0,0,0,0,0,0}, "+30 hits.", ""},
{61,65, 'E', {13,0,0,1,0,1,0,0}, "Light wound.",""},
{66,66, 'E', {22,0,0,2,0,1,0,0}, "Hard blow, Unable to parry next round.", "AK AP-10:1"},
{67,70, 'E', {5,25,3,0,0,0,0,0}, "Strike foe in face.", "AK AP-20:1"},
{71,75, 'E', {25,0,0,0,0,0,3,0}, "Strike in both lungs. Dies in 3 rnds.",""},
{76,80, 'E', {35,0,0,1,0,1,0,0}, "Hard, flat strike. Your weapon breaks",""},
{81,85, 'E', {20,0,0,0,0,0,0,1080}, "Strike to side of head knocks foe out.", "AK AP-10:1"},
{86,90, 'E', {0,0,0,0,0,0,1,0}, "Strike drives jaw into brain. DEAD",""},
{91,95, 'E', {10,0,0,0,0,0,1,0}, "Strike in ear kills foe. +20 to allies 1 rnd.", ""},
{96,99, 'E', {15,0,0,0,0,0,0,0}, "Sever spine. Paralyzed. Weapon breaks.", ""},
{100,350, 'E', {20,0,0,0,0,0,1,0}, "Strike in eye. DEAD.", "AK AP-25:1"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_LAA.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
