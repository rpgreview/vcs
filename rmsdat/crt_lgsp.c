#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[19] = {
{1,5, 'E', {0,0,0,0,0,0,0,0}, "+0 hits.", ""},
{6,10, 'E', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{16,20, 'E', {5,0,0,0,0,0,0,0}, "+5 hits.", ""},
{21,35, 'E', {7,0,0,0,0,0,0,0}, "+7 hits.", ""},
{36,45, 'E', {10,0,0,0,0,0,0,0}, "+10 hits.", ""},
{46,50, 'E', {13,0,0,0,0,0,0,0}, "+13 hits.", ""},
{51,55, 'E', {30,0,0,0,0,0,0,100}, "Blast drives in mouth. 1 month coma.", ""},
{56,60, 'E', {15,0,0,0,0,0,0,0}, "+15 hits.", ""},
{61,65, 'E', {20,0,0,0,0,0,0,0}, "+20 hits.", ""},
{66,66, 'E', {15,0,0,3,0,0,0,0}, "Strong blast staggers foe. ",""},
{67,70, 'E', {20,0,0,2,0,2,0,0}, "Leg strike. Unable to parry for 2 rnds.",""},
{71,75, 'E', {0,0,0,0,0,0,3,0}, "Blast shatters spine. Dies in 3 rnds.", ""},
{76,80, 'E', {0,0,0,0,0,0,6,0}, "Rib through heart. Dies in 6 rnds.", ""},
{81,85, 'E', {30,0,0,3,0,3,0,0}, "Massive strike. Unable to parry for 3 rnds.",""},
{86,90, 'E', {0,20,0,5,0,5,0,0}, "Side strike. Broken ribs.", ""},
{91,95, 'E', {35,35,0,0,0,0,0,0}, "Foe is knocked down. Severe thigh wound.",""},
{96,99, 'E', {50,0,0,0,0,0,0,0}, "3 month long coma. Permanent paralysis.",""},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "Strike causes bladder to explode, DEAD",""}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_LAS.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
