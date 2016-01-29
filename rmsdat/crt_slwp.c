#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[19] = {
{1,5, 'E', {10,0,0,0,0,0,0,0}, "Drop your weapon, takes 2 rnds to get it back.",""},
{6,10, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'E', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{16,20, 'E', {5,0,0,0,0,0,0,0}, "+5 hits.", ""},
{21,35, 'E', {6,0,0,0,0,0,0,0}, "+6 hits.", ""},
{36,45, 'E', {7,0,0,0,0,0,0,0}, "+7 hits.", ""},
{46,50, 'E', {8,0,0,0,0,0,0,0}, "+8 hits.", ""},
{51,55, 'E', {12,10,3,0,0,0,0,0}, "Blow gives light wound. Your weapon breaks.", ""},
{56,60, 'E', {9,0,0,0,0,0,0,0}, "+9 hits.", ""},
{61,65, 'E', {10,0,0,0,0,0,0,0}, "+10 hits.", ""},
{66,66, 'E', {15,0,0,0,0,0,0,0}, "+15 hits.", ""},
{67,70, 'E', {20,0,0,0,0,0,0,0}, "+20 hits.", ""},
{71,75, 'E', {0,0,0,0,0,0,1,1}, "Massive blow to neck. Dies in 1 rnd.", "AK AP-25:1"},
{76,80, 'E', {25,0,0,0,0,0,2,0}, "Strike foe in leg and sever vein.",""},
{81,85, 'E', {13,0,2,0,1,0,0,0}, "Light wound. Must parry next rnd.", "AK AP-20:1"},
{86,90, 'E', {25,20,0,1,0,1,0,0}, "Foe is unable to parry. Is quite upset.", ""},
{91,95, 'E', {20,0,0,2,0,2,0,0}, "Knock foe down. Unable to parry.", "AK AP-25:1"},
{96,99, 'E', {25,40,0,3,0,3,0,0}, "Heavy wound.",""},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "Strike eye. DEAD. 20% weapon stuck for 3 rnds.", "AK AP-20:1"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_SLA.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
