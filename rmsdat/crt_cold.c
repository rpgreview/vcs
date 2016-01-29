#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Cool breeze +0 hits", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {2,0,0,0,0,0,0,0}, "Lose init for 1 rnd. Cold wind.", ""},
{16,20, 'A', {3,0,0,0,0,0,0,0}, "Lose init for 1 rnd. Freezing breeze.", ""},
{21,35, 'A', {4,0,0,0,0,0,0,0}, "Mild blast. Lose init for 2 rnds.", ""},
{36,45, 'A', {5,0,0,0,1,0,0,0}, "Frosty blast. Must parry for 1 rnd.", ""},
{46,50, 'A', {6,0,0,0,2,0,0,0}, "Moderate blast. Must parry for 2 rnds.", ""},
{51,55, 'A', {7,0,0,1,0,0,0,0}, "Unbalancing blast.", ""},
{56,60, 'A', {8,0,0,2,0,0,0,0}, "Strong, but diffused, blast.", ""},
{61,65, 'A', {9,0,0,1,0,1,0,0}, "Stunned and unable to parry for 1 rnd.", ""},
{66,66, 'A', {10,0,0,3,0,3,0,0}, "Drops whatever he is holding. Chest strike.", ""},
{67,70, 'A', {10,5,0,1,0,1,0,0}, "Back blast. Frostbite.", ""},
{71,75, 'A', {11,10,0,2,0,2,0,0}, "Unbalancing blast.",""},
{76,80, 'A', {12,0,0,1,0,1,0,0}, "Chest strike. Cannot parry for 1 rnd.",""},
{81,85, 'A', {13,0,0,2,0,2,0,0}, "Back blast. Unable to parry for 2 rnds.",""},
{86,90, 'A', {0,0,0,0,0,0,0,0}, "Leg strike, knocked down.", "IF LA ST:2 EL AP:70"},
{91,95, 'A', {0,0,0,0,0,0,0,0}, "Head strike, knocked down.", "IF HA ST:3 EL ST:6 AP:50"},
{96,99, 'A', {0,0,0,0,0,0,0,100}, "Neck. Loses lips, no speak 2 weeks. Uncon."},
{100,350, 'A', {21,0,0,0,0,0,0,255}, "A month long coma,loses nose.Frostbite",""},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Cold breeze. +0 hits.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'B', {3,0,0,0,0,0,0,0}, "Foe loses init for 1 rnd. Cold chills.", ""},
{16,20, 'B', {4,0,0,0,0,0,0,0}, "Foe loses init for 2 rnds. Freezing wing.", ""},
{21,35, 'B', {5,0,0,0,0,0,0,0}, "Lose 2 rnds of init.", ""},
{36,45, 'B', {6,0,0,0,1,0,0,0}, "Freezing blast. Lose 3 rnds of init.",""},
{46,50, 'B', {7,0,0,0,2,0,0,0}, "Mild frostbite. Must parry for 2 rnds.",""},
{51,55, 'B', {8,0,3,1,0,0,0,0}, "Strong, but off-center blast.",""},
{56,60, 'B', {9,0,0,2,0,0,0,0}, "Wood exposed on back is useless and brittle.",""},
{61,65, 'B', {10,5,3,1,0,1,0,0}, "Leg strike. Frostbite.",""},
{66,66, 'B', {0,0,0,4,0,4,0,0}, "Foe is stunned", "NO BL+5"},
{67,70, 'B', {11,10,0,1,0,1,0,0}, "Back blast. Frostbite.",""},
{71,75, 'B', {12,0,3,2,0,2,0,0}, "Strike to shield side.",""},
{76,80, 'B', {13,15,3,4,0,0,0,0}, "Chest strike.",""},
{81,85, 'B', {14,0,0,3,0,3,0,0}, "Back strike.",""},
{86,90, 'B', {0,0,0,0,0,0,0,0}, "Knocked down. No leg armor loses use of foot", "LA ST+3 EL AP+75"},
{91,95, 'B', {17,75,0,3,0,3,0,0}, "Hip strike. hip is shattered.",""},
{96,99, 'B', {0,0,0,0,0,0,0,0}, "Neck & collar strike.","PL IA+100 EL DD+9 IA+9"},
{100,350, 'B', {0,0,0,0,0,0,1,1}, "Blast freeze-dries head.","AK AP-5:1"},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {4,0,0,0,0,0,0,0}, "Foe is slightly unbalanced",""},
{16,20, 'C', {5,0,0,0,0,0,0,0}, "Foe loses init for 2 rnds. Mild frosting.",""},
{21,35, 'C', {6,0,0,0,1,0,0,0}, "Moderate blast. Foe must parry for 1 rnd.",""},
{36,45, 'C', {7,0,1,0,2,0,0,0}, "Blisters. Foe must parry for 2 rnds.",""},
{46,50, 'C', {8,0,0,1,0,0,0,0}, "Blast stuns foe for 1 rnd. +8 hits.", ""},
{51,55, 'C', {0,0,0,2,0,0,0,0}, "Blast is strong but low.","IN LA BL+5"},
{56,60, 'C', {9,0,0,1,0,0,0,0}, "Back blast dries all organic material on back.",""},
{61,65, 'C', {11,0,0,4,0,0,0,0}, "Frostbite. If leather boots/greaves: gone.",""},
{66,66, 'C', {0,25,3,6,0,0,0,0}, "Foe is knocked dow",""},
{67,70, 'C', {12,15,0,1,0,1,0,0}, "Back blast.",""},
{71,75, 'C', {0,20,3,2,0,2,0,0}, "Strike to side. Shock and frostbite.",""},
{76,80, 'C', {4,0,0,0,0,0,0,0}, "Chest strike.","IF CH | PL ST+3 EL AP+25"},
{81,85, 'C', {0,40,5,6,0,0,0,0}, "Thigh strike, broken bone and frostbite.",""},
{86,90, 'C', {0,80,6,9,0,0,0,0}, "Destroys foot covering, freezes both feet",""},
{91,95, 'C', {0,0,0,0,0,0,0,0}, "Abdomen strike.","IF PL IA+100 HT+17 EL DD+9"},
{96,99, 'C', {18,0,0,0,0,0,6,0}, "Side strike shatters pelvis.Dies in 6",""},
{100,350, 'C', {0,0,0,0,0,0,0,0}, "Eyes destroyed. Coma 2 weeks, paralyzed",""},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'D', {5,0,0,0,0,0,0,0}, "Light blast.",""},
{16,20, 'D', {6,0,0,0,1,0,0,0}, "Unbalancing blast. Must parry for 1 rnd.",""},
{21,35, 'D', {7,0,1,0,0,0,0,0}, "Frosty burn. Must parry for 1 rnd at -20", "AP+20:1"},
{36,45, 'D', {8,5,0,1,0,0,0,0}, "Blast stuns foe. Facial shock.",""},
{46,50, 'D', {9,10,2,1,0,0,0,0}, "Mild frostbite.",""},
{51,55, 'D', {10,0,3,2,0,0,0,0}, "Blast to side knocks foe back 5 feet.",""},
{56,60, 'D', {0,15,3,1,0,1,0,0}, "Blast to shield arm. Frostbite.",""},
{61,65, 'D', {0,0,0,0,0,0,0,0}, "If no shield: arm useless, nerve/skin damage.", "IF SD HT+20 EL AP+30"},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "Neck blast.","PL BL4 ST6 EL AP50 BL5 ST3"},
{67,70, 'D', {13,20,0,3,0,1,0,0}, "Back blast. Frostbite.", "|FRST:-20:0"},
{71,75, 'D', {14,0,0,2,0,0,0,0}, "Blast freezes shield shoulder. Arm useless",""},
{76,80, 'D', {15,25,0,3,0,3,0,0}, "Chest strike.",""},
{81,85, 'D', {0,0,6,9,0,0,0,0}, "Blast freezes both hand. Loses use of arms.",""},
{86,90, 'D', {0,0,0,0,0,0,0,0}, "Knocked down. If no chest armor, dies in 12.", "IF PL IA+100 EL DD+12"},
{91,95, 'D', {18,0,0,0,0,0,9,9}, "Blood frozen solid. Dies in 9 rnds.",""},
{96,99, 'D', {19,0,0,0,0,0,6,6}, "Heart/lungs frozen. Dies in 6 rnds",""},
{100,350, 'D', {20,0,0,0,0,0,2,2}, "Strike freezes body fluids. Dies in 2 rnds.",""},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{6,10, 'E', {4,0,0,0,0,0,0,0}, "Foe loses init for 1 rnd. +4 hits.", "|LINT:1"},
{11,15, 'E', {0,0,0,0,0,0,0,0}, "Cold blast.", "IF NO HT+6"},
{16,20, 'E', {7,0,0,0,1,0,0,0}, "Moderate blast. Must parry for 1 rnd.", ""},
{21,35, 'E', {8,0,0,0,2,0,0,0}, "Parched, cold blast. Unbalanced","AP+15:2"},
{36,45, 'E', {0,20,0,1,0,0,0,0}, "Destroys foot covering.",""},
{46,50, 'E', {10,0,0,1,0,0,0,0}, "Spun about. Drops weapon.", ""},
{51,55, 'E', {11,0,4,1,0,1,0,0}, "Strong side strike. ",""},
{56,60, 'E', {0,20,4,1,0,1,0,0}, "Blast to weapon arm.",""},
{61,65, 'E', {13,30,0,3,0,3,0,0}, "Blast to weapon arm. Drops held. Frostbite.", ""},
{66,66, 'E', {15,100,0,0,0,0,0,0}, "Shoulder strike. Nerve/cartilage damage.","IF HA IA+100 BL+6"},
{67,70, 'E', {0,0,0,0,0,0,0,0}, "If shield, knocked down else frostbite.","IF SD BL+2 EL ST+6"},
{71,75, 'E', {15,0,0,3,0,0,0,0}, "Blast to weapon arm. Frostbite. Arm useless",""},
{76,80, 'E', {0,30,0,12,0,0,0,0}, "Knocked down,drops all held. Nerve damage.",""},
{81,85, 'E', {17,0,0,0,0,0,12,12}, "Blast freezes throat/lungs. Dies in 12 rnds.",""},
{86,90, 'E', {0,0,0,0,0,0,9,9}, "Freezes backbone. Dies in 9 rnds.",""},
{91,95, 'E', {19,0,0,0,0,0,6,6}, "Lower body fully frozen. Dies in 6 rnds.",""},
{96,99, 'E', {20,0,0,0,0,0,1,0}, "Lifeless, frozen statue - DEAD.", "AK AP-20:1"},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "Freezes solid, shatters - DEAD",""}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CC.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
