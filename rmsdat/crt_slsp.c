#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[19] = {
{1,5, 'E', {0,0,0,0,0,0,0,0}, "+0 hits.", ""},
{6,10, 'E', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'E', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{16,20, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{21,35, 'E', {5,0,0,0,0,0,0,0}, "+5 hits.", ""},
{36,45, 'E', {7,0,0,0,0,0,0,0}, "+7 hits.", ""},
{46,50, 'E', {10,0,0,0,0,0,0,0}, "+10 hits.", ""},
{51,55, 'E', {25,75,0,0,0,0,0,360}, "Blast knocks foe out. Shattered shoulder.",""},
{56,60, 'E', {12,0,0,0,0,0,0,0}, "+12 hits.", ""},
{61,65, 'E', {15,0,0,0,0,0,0,0}, "+15 hits.", ""},
{66,66, 'E', {20,0,0,0,0,0,0,0}, "+20 hits.", ""},
{67,70, 'E', {30,0,0,0,0,0,0,0}, "+30 hits.", ""},
{71,75, 'E', {0,0,0,0,0,0,6,6}, "Blast crushes skull. Dies in 6 rnds.", ""},
{76,80, 'E', {0,95,0,12,0,0,0,0}, "Blast destroys eyes. Permanently blind",""},
{81,85, 'E', {30,0,0,2,0,2,0,0}, "Strong blast.",""},
{86,90, 'E', {0,20,0,4,0,4,0,0}, "Side strike. Unable to parry for 4 rnds",""},
{91,95, 'E', {30,30,5,0,0,0,0,0}, "Chest blast.",""},
{96,99, 'E', {40,0,0,0,0,0,0,0}, "Paralyzed from the neck down, permanently",""},
{100,350, 'E', {0,0,0,0,0,0,1,1}, "Strike shatters chest. DEAD",""}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_SLS.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
