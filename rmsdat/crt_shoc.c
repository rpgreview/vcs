#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "None", ""},
{6,10, 'A', {0,0,0,0,0,0,0,0}, "None", ""},
{11,15, 'A', {0,0,0,0,0,0,0,0}, "None", ""},
{16,20, 'A', {0,0,0,0,0,0,0,0}, "None", ""},
{21,35, 'A', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{36,45, 'A', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{46,50, 'A', {0,0,0,2,0,0,0,0}, "Stunned for 2 rnds.", ""},
{51,55, 'A', {0,0,0,1,0,0,0,0}, "Stunned for 3 rnds. Parry at half.", "AP+50:3"},
{56,60, 'A', {0,0,0,4,0,4,0,0}, "Stunned for 4 rnds. Cant parry.", ""},
{61,65, 'A', {0,0,0,5,0,5,0,0}, "Cant parry. -5 for 20 minutes.", "AP+5:120"},
{66,66, 'A', {0,0,0,10,0,10,0,0}, "Cant parry or change facing. -25 for 24 hrs.", "AP+25:8640"},
{67,70, 'A', {0,0,0,7,0,7,0,0}, "Cant parry. -10 for 1 hr.", "AP+10:360"},
{71,75, 'A', {0,0,0,8,0,8,0,0}, "Cant parry. -15 for 1 hr.", "AP+15:360"},
{76,80, 'A', {0,0,0,9,0,9,0,0}, "Cant change facing. -20 for 3 hrs.", "AP+20:1080"},
{81,85, 'A', {0,0,0,10,0,10,0,0}, "Cant change facing. -20 for 6 hrs.", "AP+20:2160"},
{86,90, 'A', {0,0,0,11,0,11,0,0}, "Cant change facing. -25 for 6 hrs.", "AP+25:2160"},
{91,95, 'A', {0,0,0,12,0,12,0,0}, "Cant change facing. Confused. -25 for 24 hrs.", "AP+25:8640"},
{96,99, 'A', {0,0,0,13,0,13,0,0}, "Cant change facing. Confused. -30 for 24 hrs.", "AP+30:8640"},
{100,350, 'A', {0,0,0,14,0,14,0,0}, "Cant change facing. Confused. -35 for 24 hrs.", "AP+35:8640"},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "None", ""},
{6,10, 'B', {0,0,0,0,0,0,0,0}, "None", ""},
{11,15, 'B', {0,0,0,0,0,0,0,0}, "None", ""},
{16,20, 'B', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{21,35, 'B', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{36,45, 'B', {0,0,0,1,0,0,0,0}, "Stunned for 2 rnds. Parry at half.", "AP+50:2"},
{46,50, 'B', {0,0,0,3,0,0,0,0}, "Stunned for 3 rnds.", ""},
{51,55, 'B', {0,0,0,4,0,4,0,0}, "Stunned for 4 rnds. Cant parry.", ""},
{56,60, 'B', {0,0,0,5,0,5,0,0}, "Cant parry. -5 for 20 minutes.", "AP+5:120"},
{61,65, 'B', {0,0,0,6,0,6,0,0}, "-5 for 1 hr.", "AP+5:360"},
{66,66, 'B', {0,0,0,16,0,16,0,0}, "Cant parry or change facing.", ""},
{67,70, 'B', {0,0,0,9,0,9,0,0}, "Cant parry. -10 for 3 hrs.", "AP+10:1080"},
{71,75, 'B', {0,0,0,10,0,10,0,0}, "Cant change facing. -20 for 3 hrs.", "AP+20:1080"},
{76,80, 'B', {0,0,0,11,0,11,0,0}, "Cant change facing. -25 for 3 hrs.", "AP+25:1080"},
{81,85, 'B', {0,0,0,12,0,12,0,0}, "Cant change facing. Confused. -30 for 24 hrs.", "AP+30:8640"},
{86,90, 'B', {0,0,0,13,0,13,0,0}, "Cant change facing. Confused. -35 for 24 hrs.", "AP+35:8640"},
{91,95, 'B', {0,0,0,15,0,15,0,0}, "Cant change facing. Confused. -35 for 2 days", "AP+35:17280"},
{96,99, 'B', {0,0,0,16,0,16,0,0}, "Cant change facing. Confused. -40 for 2 days", "AP+40:17280"},
{100,350, 'B', {0,0,0,19,0,19,0,2}, "Still 2 rnds. -45 for 2 days", "AP+45:17280"},
{1,5, 'C', {0,0,0,0,0,0,0,0}, "None", ""},
{6,10, 'C', {0,0,0,0,0,0,0,0}, "None", ""},
{11,15, 'C', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{16,20, 'C', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{21,35, 'C', {0,0,0,2,0,0,0,0}, "Stunned for 2 rnds. Parry at half.", "AP+50:2"},
{36,45, 'C', {0,0,0,3,0,0,0,0}, "Stunned for 3 rnds.", ""},
{46,50, 'C', {0,0,0,4,0,4,0,0}, "Cant parry. -5 for 1 hr.", "AP+5:360"},
{51,55, 'C', {0,0,0,5,0,5,0,0}, "Cant parry. -10 for 1 hr.", "AP+10:360"},
{56,60, 'C', {0,0,0,6,0,6,0,0}, "-15 for 1 hr.", "AP+15:360"},
{61,65, 'C', {0,0,0,8,0,8,0,0}, "Cant parry. -20 for 1 hr.", "AP+20:360"},
{66,66, 'C', {4,0,0,0,0,0,0,100}, "Foe slams himself to the Floor. Coma!!", ""},
{67,70, 'C', {0,0,0,11,0,11,0,0}, "Cant change facing. -20 for 3 hrs.", "AP+20:1080"},
{71,75, 'C', {0,0,0,12,0,12,0,0}, "Cant change facing. Confused. -25 for 6 hrs.", "AP+25:2160"},
{76,80, 'C', {0,0,0,13,0,13,0,0}, "Cant change facing. Confused. -30 for 24 hrs.", "AP+30:8640"},
{81,85, 'C', {0,0,0,14,0,14,0,0}, "Cant change facing. Confused. -30 for 2 days", "AP+30:17280"},
{86,90, 'C', {0,0,0,15,0,15,0,0}, "Cant change facing. Confused. -35 for 2 days", "AP+35:17280"},
{91,95, 'C', {0,0,0,18,0,18,0,0}, "Cant change facing. Confused. -40 for 2 days", "AP+40:17280"},
{96,99, 'C', {1,0,0,24,0,24,0,0}, "Still 2 rnds. Confused. +1 Hit.", "|IMB:2"},
{100,350, 'C', {2,0,0,0,0,0,0,100}, "Foe is mindless drooling idiot. Coma!!", ""},
{1,5, 'D', {0,0,0,0,0,0,0,0}, "None", ""},
{6,10, 'D', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{11,15, 'D', {0,0,0,1,0,0,0,0}, "Stunned for 1 rnd.", ""},
{16,20, 'D', {0,0,0,2,0,0,0,0}, "Stunned for 2 rnds.", ""},
{21,35, 'D', {0,0,0,3,0,0,0,0}, "Parry at half.", "AP+50:1"},
{36,45, 'D', {0,0,0,4,0,4,0,0}, "Cant parry. -5 for 1 hr.", "AP+5:360"},
{46,50, 'D', {0,0,0,5,0,5,0,0}, "Cant parry. -10 for 1 hr.", "AP+10:360"},
{51,55, 'D', {0,0,0,6,0,6,0,0}, "Cant parry. -15 for 1 hr.", "AP+15:360"},
{56,60, 'D', {0,0,0,8,0,8,0,0}, "Cant parry. -20 for 1 hr.", "AP+20:360"},
{61,65, 'D', {0,0,0,10,0,10,0,0}, "Cant change facing. Confused. -25 for 24 hrs.", "AP+25:8640"},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "Foe snaps rigid & falls.","HA IA+100 EL DD+1"},
{67,70, 'D', {0,0,0,13,0,13,0,0}, "Cant change facing. Confused. -30 for 24 hrs.", "AP+30:8640"},
{71,75, 'D', {0,0,0,14,0,14,0,0}, "Cant change facing. Confused. -35 for 3 days", "AP+35:25920"},
{76,80, 'D', {0,0,0,15,0,15,0,0}, "Cant change facing. Confused. -40 for 3 days", "AP+40:25920"},
{81,85, 'D', {0,0,0,16,0,16,0,0}, "Cant change facing. Confused. -45 for 3 days", "AP+45:25920"},
{86,90, 'D', {0,0,0,17,0,17,0,0}, "Cant change facing. Confused. -50 for 3 days", "AP+50:25920"},
{91,95, 'D', {2,0,0,21,0,0,0,3}, "Still 3 rnds. -50 for 1 week.", "AP+50:60480"},
{96,99, 'D', {3,0,0,0,0,0,0,100}, "Random brain damage. +3 hits. Coma.", ""},
{100,350, 'D', {0,0,0,0,0,0,1,1}, "Foe stops & remains in last position. DEAD.", ""},
{1,5, 'E', {0,0,0,1,0,0,0,0}, "1 rnd of stun.", ""},
{6,10, 'E', {0,0,0,2,0,0,0,0}, "Stunned for 2 rnds.", ""},
{11,15, 'E', {0,0,0,3,0,0,0,0}, "Stunned for 3 rnds. Parry at half.", "AP+50:1"},
{16,20, 'E', {0,0,0,4,0,4,0,0}, "Cant parry. -5 for 1 hr.", "AP+5:360"},
{21,35, 'E', {0,0,0,5,0,0,0,0}, "-10 for 1 hr.", "AP+10:360"},
{36,45, 'E', {0,0,0,6,0,6,0,0}, "Cant parry. -15 for 1 hr.", "AP+15:360"},
{46,50, 'E', {0,0,0,7,0,7,0,0}, "Cant change facing. -20 for 1 hr.", "AP+20:360"},
{51,55, 'E', {0,0,0,9,0,9,0,0}, "Cant change facing. -25 for 24 hrs.", "AP+25:8640"},
{56,60, 'E', {0,0,0,12,0,12,0,0}, "Cant change facing. Confused. -25 for 3 days", "AP+25:25920"},
{61,65, 'E', {0,0,0,15,0,15,0,0}, "Cant change facing. Confused. -30 for 3 days", "AP+30:25920"},
{66,66, 'E', {0,0,0,0,0,0,1,1}, "Foe collapses. Death.", ""},
{67,70, 'E', {0,0,0,19,0,19,0,0}, "Cant change facing. Confused. -35 for 3 days", "AP+35:25920"},
{71,75, 'E', {0,0,0,25,0,25,0,3}, "Still for 3 rnds. Confused. -40 for 1 week.", "AP+40:60480"},
{76,80, 'E', {0,0,0,30,0,30,0,5}, "Still for 5 rnds. Confused. -50 for 1 week.", "AP+50:60480"},
{81,85, 'E', {2,0,0,0,0,0,0,360}, "Spins about, uncon. -60 for 1 week.", "AP+60:60480"},
{86,90, 'E', {5,0,0,0,0,0,0,360}, "-75 for 1 week. Unconscious.", "AP+75:60480"},
{91,95, 'E', {7,0,0,0,0,0,0,100}, "Roll 3 random phobias. Coma.", ""},
{96,99, 'E', {0,0,0,0,0,0,1,1}, "Foe crumples in an untidy heap. Death.", ""},
{100,350, 'E', {0,0,0,0,0,0,1,1}, "10' backwards. Death.", ""}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CX.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
