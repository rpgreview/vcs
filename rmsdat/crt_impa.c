#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Nary a whisper. +0 hits.", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {2,0,0,0,0,0,0,0}, "Foe loses init for 1 rnd.", ""},
{16,20, 'A', {3,0,0,0,0,0,0,0}, "Spun about. Loses init 1 rnd.",""},
{21,35, 'A', {5,0,0,0,0,0,0,0}, "Foe is unbalanced. Loses 2 rnds of init.",""},
{36,45, 'A', {8,0,0,0,0,0,0,0}, "Foe is unbalanced. Loses 2 rnds of init.",""},
{46,50, 'A', {10,0,0,0,0,0,0,0}, "Blow unbalances foe. Loses 3 rnds of init.",""},
{51,55, 'A', {10,0,0,1,0,0,0,0}, "Foe is unbalanced. ",""},
{56,60, 'A', {10,0,0,1,0,0,0,0}, "Foe is unbalanced. ",""},
{61,65, 'A', {12,0,0,1,0,0,0,0}, "Foe is unbalanced. ",""},
{66,66, 'A', {20,0,0,0,1,0,0,0}, "Blast break's shield shoulder. Arm useless.",""},
{67,70, 'A', {7,0,0,1,0,1,0,0}, "Blow to back. Unable to parry for 1 rnd.",""},
{71,75, 'A', {10,0,0,2,0,0,0,0}, "Blow unbalances foe. ",""},
{76,80, 'A', {15,0,0,1,0,1,0,0}, "Blow stuns foe for 2 rnds.",""},
{81,85, 'A', {10,25,0,0,0,0,0,0}, "Blow to back, broken ribs/torn cartilage",""},
{86,90, 'A', {10,0,0,3,0,0,0,0}, "Blow knocks foe down for 3 rnds",""},
{91,95, 'A', {20,50,0,3,0,3,0,0}, "Blow breaks hip.",""},
{96,99, 'A', {20,0,0,0,0,0,0,100}, "Head blast. Helm: uncon 1 day else 1 month",""},
{100,350, 'A', {25,0,0,0,0,0,0,0}, "Head strike. Uncon","HA IA+100 EL DD+3"},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Great luck escapes you. +0.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits", ""},
{11,15, 'B', {4,0,0,0,0,0,0,0}, "Foe is spun about. ",""},
{16,20, 'B', {2,0,0,0,1,0,0,0}, "Blast unbalances foe.",""},
{21,35, 'B', {5,0,0,0,1,0,0,0}, "Blow unbalances foe.",""},
{36,45, 'B', {9,0,0,0,1,0,0,0}, "Blow unbalances foe.",""},
{46,50, 'B', {10,0,0,1,0,0,0,0}, "Blow unbalances foe.",""},
{51,55, 'B', {12,0,0,1,0,0,0,0}, "Blow unbalances foe.",""},
{56,60, 'B', {10,0,0,2,0,0,0,0}, "Foe is spun about.",""},
{61,65, 'B', {10,0,0,1,0,1,0,0}, "Foe is staggered.",""},
{66,66, 'B', {15,0,0,0,0,0,0,0}, "Blow shatters weapon shoulder, arm useless.",""},
{67,70, 'B', {12,0,0,1,0,1,0,0}, "Blow to back.",""},
{71,75, 'B', {20,0,0,1,0,1,0,0}, "Blow stuns foe for 2 rnds.",""},
{76,80, 'B', {10,0,0,0,0,0,0,2}, "Foe is knocked down.", "AK AP-5:1"},
{81,85, 'B', {10,25,0,2,0,0,0,0}, "Back blow tears cartilage, breaks ribs.",""},
{86,90, 'B', {20,50,0,3,0,0,0,0}, "Strike to calf. Broken bone, torn tendons.",""},
{91,95, 'B', {0,0,0,0,0,0,0,0}, "Blow to upper head area. Coma 2 weeks", "HA IA+100 EL DD+1"},
{96,99, 'B', {25,0,0,12,0,0,12,0}, "Blast severs windpipe. Dies in 12 rnds.", ""},
{100,350, 'B', {30,0,0,0,0,0,0,0}, "Blow to back of neck paralyzes foe",""},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {3,0,0,0,1,0,0,0}, "Foe is unbalanced.",""},
{16,20, 'C', {4,0,0,0,1,0,0,0}, "Foe is unbalanced.",""},
{21,35, 'C', {8,0,0,0,1,0,0,0}, "Foe is unbalanced.",""},
{36,45, 'C', {10,0,0,1,0,0,0,0}, "Foe is unbalanced",""},
{46,50, 'C', {12,0,0,0,2,0,0,0}, "Foe is unbalanced",""},
{51,55, 'C', {15,0,0,0,2,0,0,0}, "Foe is knocked back 5 feet",""},
{56,60, 'C', {12,0,0,2,0,0,0,0}, "Foe is spun about",""},
{61,65, 'C', {10,0,0,1,0,1,0,0}, "Foe unable to parry next rnd.", "AK AP-5:1"},
{66,66, 'C', {0,90,0,3,0,0,0,0}, "Breaks both arms. Knocked down",""},
{67,70, 'C', {0,0,0,1,0,1,0,0}, "Blow to back.",""},
{71,75, 'C', {10,0,0,0,0,0,0,2}, "Foe is knocked down.", "AK AP-5:1"},
{76,80, 'C', {15,25,0,1,0,0,0,0}, "Blow breaks collar bone.",""},
{81,85, 'C', {15,40,0,3,0,0,0,0}, "Foe has broken thigh.",""},
{86,90, 'C', {20,60,0,2,0,2,0,0}, "Blow breaks hip.",""},
{91,95, 'C', {20,75,0,9,0,9,0,0}, "Blow shatters knee. Foe is hobbled",""},
{96,99, 'C', {50,0,0,0,0,0,1,1}, "Blast to chest. DEAD",""},
{100,350, 'C', {0,0,0,0,0,0,1,0}, "Blast to head crushes skull. DEAD.", "AK AP-10:1"},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits", ""},
{11,15, 'D', {4,0,0,0,1,0,0,0}, "Foe is unbalanced.",""},
{16,20, 'D', {6,0,0,0,1,0,0,0}, "Foe is unbalanced.",""},
{21,35, 'D', {10,0,0,0,1,0,0,0}, "Foe is unbalanced.",""},
{36,45, 'D', {12,0,0,0,2,0,0,0}, "Foe is unbalanced",""},
{46,50, 'D', {20,0,0,2,0,0,0,0}, "Foe is spun about.",""},
{51,55, 'D', {0,0,0,0,2,0,0,0}, "Foe is knocked back 5 feet.", "AK AP-5:1"},
{56,60, 'D', {10,0,0,1,0,1,0,0}, "Foe is staggered.",""},
{61,65, 'D', {10,0,0,1,0,1,0,0}, "Foe is staggered.",""},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "Blow to head. Uncon 3 hrs", "HA IA+100 EL DD+1"},
{67,70, 'D', {15,0,0,0,0,0,0,2}, "Foe is knocked down.", "|KD:2AK AP-5:1"},
{71,75, 'D', {10,0,0,1,0,0,0,0}, "Foe now has a broken shield arm.",""},
{76,80, 'D', {10,0,0,1,0,0,0,0}, "Blow breaks weapon arm. Arm useless.",""},
{81,85, 'D', {20,0,0,0,0,0,0,3}, "Blow breaks both arms, knocked down.",""},
{86,90, 'D', {20,0,0,0,0,0,0,0}, "Strike to abdomen.","PL ST+12 EL DD+6"},
{91,95, 'D', {50,0,0,0,0,0,3,3}, "Blow shatters jaw/brain. dies in 3 rnds",""},
{96,99, 'D', {25,0,0,0,0,0,1,0}, "Blow to side. DEAD",""},
{100,350, 'D', {0,0,0,0,0,0,1,0}, "Lungs and heart explode. DEAD.", "AK AP-25:1"},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{6,10, 'E', {3,0,0,1,0,0,0,0}, "Blast stuns foe for 1 rnd. +3 hits.", ""},
{11,15, 'E', {4,0,0,1,0,0,0,0}, "Blast stuns foe for 1 rnd. +4 hits.", ""},
{16,20, 'E', {9,0,0,1,0,0,0,0}, "Blast stuns foe for 1 rnd. +9 hits.", ""},
{21,35, 'E', {12,0,0,1,0,0,0,0}, "Foe reels from blast.",""},
{36,45, 'E', {20,0,0,2,0,0,0,0}, "Foe is spun about, reels backwards 10 feet.",""},
{46,50, 'E', {20,0,0,1,0,1,0,0}, "Foe is staggered.",""},
{51,55, 'E', {20,0,0,1,0,1,0,0}, "Foe is staggered.",""},
{56,60, 'E', {20,0,0,0,0,0,0,2}, "Foe is knocked down.",""},
{61,65, 'E', {20,0,0,0,0,0,0,3}, "Foe is knocked down.",""},
{66,66, 'E', {0,0,0,0,0,0,1,0}, "Blast shatters skull. DEAD",""},
{67,70, 'E', {0,0,0,1,0,0,0,0}, "Blast to shield arm. Arm/shield broken",""},
{71,75, 'E', {20,25,0,6,0,0,0,0}, "Blast to chest breaks ribs",""},
{76,80, 'E', {25,100,0,0,0,0,0,0}, "Breaks collar bone, both shoulders.",""},
{81,85, 'E', {30,0,0,0,0,0,6,6}, "Blast to side crushes organs. Dies in 6 rnds",""},
{86,90, 'E', {50,0,0,0,0,0,3,3}, "Blast crushes bone. Dies in 3 rnds.",""},
{91,95, 'E', {30,0,0,0,0,0,6,6}, "Blast drives bone through lungs. Dies in 6",""},
{96,99, 'E', {0,0,0,0,0,0,1,0}, "Blast crushes skull. DEAD.", "AK AP-20:1"},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "Blast annihilates entire skeleton. DEAD",""}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CI.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
