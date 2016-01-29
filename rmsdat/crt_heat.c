#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Hot air. +0 hits.", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {2,0,0,0,0,0,0,0}, "Foe loses init for 1 rnd. Hard, hot breeze.",""},
{16,20, 'A', {3,0,0,0,0,0,0,0}, "Foe loses init for 1 rnd.",""},
{21,35, 'A', {4,0,0,0,0,0,0,0}, "Blast unbalances foe. Loses init for 2 rnds.",""},
{36,45, 'A', {6,0,0,0,1,0,0,0}, "Foe must parry for 1 rnd. +6 hits.", ""},
{46,50, 'A', {7,0,1,0,1,0,0,0}, "Light burns. Must parry for 1 rnd.",""},
{51,55, 'A', {8,0,1,0,2,0,0,0}, "Blast unbalances foe. Must parry for 2 rnds",""},
{56,60, 'A', {9,0,2,1,0,0,0,0}, "Foe loses init for 2 rnds",""},
{61,65, 'A', {0,0,0,2,0,0,0,0}, "Foe is stunned for 2 rnds.","LA HT+7 BL+1 EL HT+10 BL+3"},
{66,66, 'A', {9,15,0,2,0,2,0,0}, "Blast causes foe to drop what he is holding.",""},
{67,70, 'A', {8,5,0,2,0,0,0,0}, "Back blast.",""},
{71,75, 'A', {12,0,0,1,0,1,0,0}, "Hot smoke blinds foe.",""},
{76,80, 'A', {10,0,2,1,0,1,0,0}, "Blast stuns foe for 2 rnds.",""},
{81,85, 'A', {8,0,2,2,0,0,0,0}, "Back blast.","AP+20:2"},
{86,90, 'A', {10,0,0,0,0,0,0,1}, "Knocked down. Destroys organic foot covering.",""},
{91,95, 'A', {12,30,0,2,0,2,0,0}, "Fire burns foe in hip area.",""},
{96,99, 'A', {0,0,8,0,0,0,0,100}, "Blast to neck area. Down for the count",""},
{100,350, 'A', {15,0,0,0,0,0,0,0}, "Helm: uncon else coma & 50% PR loss","HA IA+100 BL+7 EL IA+100 HT+15"},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Hot draft. +0 hits.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'B', {2,0,0,0,0,0,0,0}, "Foe loses 1 rnd of init. Strong heat.",""},
{16,20, 'B', {0,0,0,0,0,0,0,0}, "Blast unbalances foe. Loses init for 2 rnds.", ""},
{21,35, 'B', {6,0,0,0,0,0,0,0}, "Loses init for 2 rnds. Bothersome smoke.",""},
{36,45, 'B', {7,0,1,0,1,0,0,0}, "Light burns. Foe must parry for 1 rnd.",""},
{46,50, 'B', {8,0,1,0,2,0,0,0}, "Minor burns. Foe must parry for 2 rnds.",""},
{51,55, 'B', {8,0,2,1,0,0,0,0}, "Wide shot, strong fire.",""},
{56,60, 'B', {0,0,0,2,0,0,0,0}, "Foe is stunned for 2 rnds.", "PL | CH & LA HT+8 EL HT+9 BL+3"},
{61,65, 'B', {9,5,2,1,0,1,0,0}, "Foe unable to parry for 1 rnd.",""},
{66,66, 'B', {10,0,4,2,0,0,0,0}, "If organic armor, it is now useless.",""},
{67,70, 'B', {7,10,2,1,0,1,0,0}, "Back blast. Unable to parry for 1 rnd.",""},
{71,75, 'B', {9,15,0,1,0,1,0,0}, "Chest blast. Unable to parry for 1 rnd.", "AK AP-10:1"},
{76,80, 'B', {0,0,2,2,0,0,0,0}, "All weapon arm cloth gone. Drops all",""},
{81,85, 'B', {0,0,2,1,0,0,0,1}, "Knocked down, All organic on back destroyed.",""},
{86,90, 'B', {10,0,6,3,0,0,0,0}, "Leg covering burns @ 6 until extinguished",""},
{91,95, 'B', {0,0,0,0,0,0,0,0}, "Head strike. Blinded. No helm:50% hair loss", "HA AP+95:6 EL BL+8"},
{96,99, 'B', {20,0,0,0,0,0,9,9}, "Neck strike destroys throat. Dies in 9 rnds.", "AK AP-10:1"},
{100,350, 'B', {25,0,0,0,0,0,0,0}, "Neck blast, paralyzed permanently.", ""},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {3,0,0,0,0,0,0,0}, "Loses 1 rnd of init recovering their balance.",""},
{16,20, 'C', {5,0,0,0,0,0,0,0}, "Foe loses init for 2 rnds. +5 hits.", ""},
{21,35, 'C', {7,0,1,0,1,0,0,0}, "Light burns. Must parry for 1 rnd.",""},
{36,45, 'C', {8,0,1,0,2,0,0,0}, "Minor burns force foe to parry for 2 rnds.",""},
{46,50, 'C', {9,0,2,1,0,0,0,0}, "Minor burns.", ""},
{51,55, 'C', {9,0,0,2,0,0,0,0}, "Blast stuns foe for 2 rnds.","LA BL+1 EL BL+3"},
{56,60, 'C', {10,0,2,2,0,0,0,0}, "All cloth covering on back is destroyed.",""},
{61,65, 'C', {10,10,3,1,0,1,0,0}, "Upper leg burns.",""},
{66,66, 'C', {12,0,0,0,0,0,0,0}, "Knocked down. If no arm armor, arm useless.", "AA BL+2 EL BL+4"},
{67,70, 'C', {0,15,2,1,0,1,0,0}, "Back blast.",""},
{71,75, 'C', {0,0,0,3,0,0,0,0}, "Chest blast. If organic chest armor: gone.", "NO AP+25 BL+6"},
{76,80, 'C', {0,0,0,0,0,0,0,0}, "Drops shield. If none: loses use of arm.", "SD AP+50 BL+6"},
{81,85, 'C', {0,0,0,0,0,0,0,0}, "If no leg armor: massive damage & is useless.", "LA BL+2 AP+20 EL AP+80"},
{86,90, 'C', {15,85,3,6,0,6,0,0}, "Lower leg burns. Foe loses foot.",""},
{91,95, 'C', {18,90,4,6,0,6,0,0}, "Loses use of leg from tissue loss from burns",""},
{96,99, 'C', {0,0,0,0,0,0,0,0}, "If chest armor: dies in 9 else DEAD","PL DD+9 EL DD+1 IA+1"},
{100,350, 'C', {0,0,0,0,0,0,1,0}, "Head is a charred stump. DEAD.", "AK AP-10:1"},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'D', {4,0,0,0,0,0,0,0}, "Loses init for 1 rnd. Not quite singeing.",""},
{16,20, 'D', {6,0,0,0,1,0,0,0}, "Unbalanced and must parry for 1 rnd.",""},
{21,35, 'D', {8,0,1,0,2,0,0,0}, "Minor burns. Must parry for 2 rnds.",""},
{36,45, 'D', {9,0,2,1,0,0,0,0}, "Blast stuns foe for 1 rnd.",""},
{46,50, 'D', {10,0,3,1,0,0,0,0}, "If foe is using a non-metal bow: destroyed.", ""},
{51,55, 'D', {0,0,0,2,0,0,0,0}, "Blast stuns foe 2 rnds.","HA HT+8 BL+2 EL HT+11 BL+4"},
{56,60, 'D', {12,0,9,1,0,1,0,0}, "Clothing burns 9/rnd (2 rnds to extinguish)",""},
{61,65, 'D', {0,0,0,1,0,0,0,0}, "Good Strike","LA HT+10 BL+4 EL HT+13 BL+6"},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "Neck blast.","PL BL3 AP10 EL IN100 BL10"},
{67,70, 'D', {15,0,3,0,0,0,0,1}, "Back blast. Knocked down. Organic on back gone",""},
{71,75, 'D', {0,0,0,0,0,0,0,0}, "Shield dropped. If none: arm useless", "IN SD ST+6 AP+50"},
{76,80, 'D', {0,0,5,3,0,3,0,0}, "Severe hand burns.",""},
{81,85, 'D', {15,0,0,9,0,0,0,0}, "Blast burns arms/upper chest. Arms useless",""},
{86,90, 'D', {0,0,0,0,0,0,0,0}, "If abdomenal armor: uncon else dies in 12.", "PL IA+100 BL+2 EL DD+12 IA+12"},
{91,95, 'D', {20,0,0,0,0,0,0,6}, "If helm: eyes gone & 2 day coma else dies 6","HA IA+100 EL DD+6 IA+6"},
{96,99, 'D', {20,100,0,0,0,0,6,0}, "Engulfed in flames. Dies in 6 rnds",""},
{100,350, 'D', {0,0,0,0,0,0,1,0}, "Heat vaporizes midsection. All destroyed.", "AK AP-15:1"},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{6,10, 'E', {4,0,0,0,0,0,0,0}, "Loses init for 1 rnd. +4 hits.", ""},
{11,15, 'E', {5,0,0,0,0,0,0,0}, "Feels heat, loses 1 rnd init.","NO HT+5"},
{16,20, 'E', {7,0,0,0,1,0,0,0}, "Hot, unbalancing blast. Must parry for 1 rnd.",""},
{21,35, 'E', {9,0,2,0,2,0,0,0}, "Minor burns. Must parry for 2 rnds.",""},
{36,45, 'E', {10,0,3,1,0,0,0,0}, "If wearing a cloak it is destroyed.",""},
{46,50, 'E', {12,0,3,2,0,0,0,0}, "If using a wooden weapon, it is destroyed.",""},
{51,55, 'E', {13,0,3,1,0,1,0,0}, "Reels back 3 feet. ",""},
{56,60, 'E', {15,10,3,1,0,1,0,0}, "Cannot parry for 1 rnd.",""},
{61,65, 'E', {15,10,4,2,0,2,0,0}, "Searing blast burns legs.",""},
{66,66, 'E', {0,0,0,0,0,0,0,0}, "If helm: uncon else DEAD", "HA IA+100 EL IA+1 DD+1"},
{67,70, 'E', {0,0,0,0,0,0,0,0}, "If no arm armor: loses use of arm.", "AA AP+15 BL+4 EL BL+5"},
{71,75, 'E', {0,0,0,3,0,0,0,0}, "Chest armor gone. If none knocked down.","PL HT+12 ST+3 EL BL+6 AP+60"},
{76,80, 'E', {20,0,0,6,0,0,0,0}, "If shield: it & hand gone else loses arm & uncon.", "SD ST+6 EL IA+100"},
{81,85, 'E', {20,0,0,0,0,0,12,0}, "Inhales flame. Dies in 12 painful rnds.",""},
{86,90, 'E', {20,100,0,0,0,0,9,0}, "Lower body engulfed in flames. Dies in 9",""},
{91,95, 'E', {25,0,0,0,0,0,6,6}, "All organic on body gone. Dies in 6 of nerve",""},
{96,99, 'E', {0,0,0,0,0,0,1,0}, "Instantly dehydrated into dust.", "AK AP-10:1"},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "All that remains is charred bits.", "AK AP-20:1"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CH.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
