#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "A lot of static. +0 hits.", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {2,0,0,0,0,0,0,0}, "loses init for 1 rnd. +2 hits.", ""},
{16,20, 'A', {3,0,0,0,0,0,0,0}, "Spun about and loses 1 rnd of init.", ""},
{21,35, 'A', {4,0,0,0,0,0,0,0}, "Blast unbalances foe. Loses 2 rnds of init.",""},
{36,45, 'A', {5,0,0,0,1,0,0,0}, "Light distracts foe, must parry for 1 rnd.", ""},
{46,50, 'A', {2,0,1,0,1,0,0,0}, "Minor burns. Must parry for 1 rnd",""},
{51,55, 'A', {6,0,0,1,0,0,0,0}, "Sizzling but weak blast",""},
{56,60, 'A', {7,0,0,0,3,0,0,0}, "Unbalanced and must parry next 3 rnds.",""},
{61,65, 'A', {0,0,0,0,0,0,0,0}, "Chest strike.", "CH | PL ST2. NO ST3"},
{66,66, 'A', {0,0,0,3,0,0,0,0}, "Light/smoke stun all in 5' 1 rnd. Knocked down",""},
{67,70, 'A', {7,0,0,1,0,1,0,0}, "Back strike.", ""},
{71,75, 'A', {8,0,0,3,0,0,0,0}, "Blast stuns for 3 rnds.", "AP+5:6"},
{76,80, 'A', {9,0,0,1,0,1,0,0}, "Strike to upper chest",""},
{81,85, 'A', {12,0,0,2,0,2,0,0}, "Back blast. Unable to parry for 2 rnds.",""},
{86,90, 'A', {0,0,0,0,0,0,0,0}, "Knocked down. If metal leg armor: loses leg.", "LA AP50 EL ST2 NP2 HT15"},
{91,95, 'A', {0,0,0,0,0,0,0,0}, "Hip strike.", "PL ST6 HT10 EL ST3 AP50"},
{96,99, 'A', {10,0,0,0,0,0,0,0}, "Neck & shoulder strike.", "PL ST6 NP6 EL IN100 HT10"},
{100,350, 'A', {20,0,0,0,0,0,6,6}, "Head strike. Uncon. Dies in 6",""},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Hair stands up. +0 hits.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'B', {2,0,0,0,0,0,0,0}, "loses init for 1 rnd. Metal worn buzzes.",""},
{16,20, 'B', {4,0,0,0,0,0,0,0}, "Explosion of light. Loses 1 rnd of init.",""},
{21,35, 'B', {5,0,0,0,0,0,0,0}, "Crackling blast. Lose 2 rnds of init.",""},
{36,45, 'B', {2,0,1,0,1,0,0,0}, "Minor burns. Must parry for 1 rnd",""},
{46,50, 'B', {6,0,0,0,2,0,0,0}, "Blast forces to parry for 2 rnds.",""},
{51,55, 'B', {7,0,2,1,0,0,0,0}, "Spun about. A minor burn on leg",""},
{56,60, 'B', {8,0,0,2,0,0,0,0}, "Stunned for 2 rnds.","CH | PL NP+1"},
{61,65, 'B', {9,0,0,1,0,1,0,0}, "Upper leg strike. Unable to parry 1 rnd.", ""},
{66,66, 'B', {15,20,3,3,0,3,0,0}, "Chest strike. No parry for 3 rnds",""},
{67,70, 'B', {10,0,0,1,0,1,0,0}, "Back strike.",""},
{71,75, 'B', {0,0,0,0,0,0,0,0}, "If no shield: arm is useless.", "SD ST+4 EL ST+2 NP+2"},
{76,80, 'B', {11,0,2,0,0,0,0,0}, "Chest strike. Knocked down",""},
{81,85, 'B', {13,10,0,3,0,3,0,0}, "Back blast. Muscle torn",""},
{86,90, 'B', {0,0,0,0,0,0,0,0}, "If no leg armor: leg broken, damaged nerves.", "LA ST+6 NP+6 EL ST+6 AP+50"},
{91,95, 'B', {0,95,0,9,0,0,0,0}, "Loses nose. Blind 2 weeks. No helm: knocked down.", ""},
{96,99, 'B', {15,0,0,0,0,0,9,9}, "Massive brain damage. Dies in 9 rnds.",""},
{100,350, 'B', {0,0,0,0,0,0,1,0}, "Blast neck, severs head. DEAD.", "AK AP-10:1"},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {3,0,0,0,0,0,0,0}, "Hears crackling sound. Loses 1 rnd init.",""},
{16,20, 'C', {3,0,0,0,0,0,0,0}, "Eruption of smoke. Lose 2 rnds of init.",""},
{21,35, 'C', {6,0,0,0,1,0,0,0}, "Strong but glancing blast",""},
{36,45, 'C', {7,0,0,0,2,0,0,0}, "Feels the heat and must parry for 2 rnds.",""},
{46,50, 'C', {7,0,0,0,0,0,0,0}, "Minor damage", "CH | PL ST2 EL ST1 HT7"},
{51,55, 'C', {0,0,0,0,0,0,0,0}, "Strike to leg.","LA ST1 EL ST1 NO1 BL3"},
{56,60, 'C', {9,0,0,1,0,1,0,0}, "Blast stuns for 2 rnds.",""},
{61,65, 'C', {10,0,0,2,0,2,0,0}, "Stunned and unable to parry for 2 rnds.",""},
{66,66, 'C', {0,0,0,0,0,0,0,0}, "If metal armor on arms/chest: can't use arms.", "CH | PL IN+100 HT+9"},
{67,70, 'C', {11,10,0,2,0,2,0,0}, "Back strike. ",""},
{71,75, 'C', {0,0,0,0,0,0,0,0}, "If no shield: knocked down, arm useless.", "SD ST6 HT12 EL HT13"},
{76,80, 'C', {0,0,0,0,0,0,0,0}, "If no chest armor: uncon 3 days.", "PL IN100 EL ST6 BL2 AP5"},
{81,85, 'C', {0,40,2,4,0,0,0,0}, "Thigh strike. Bones breaks/torn cartilage.",""},
{86,90, 'C', {0,60,0,2,0,2,0,0}, "Blast shatters knee. Destroys nerves.",""},
{91,95, 'C', {0,0,0,0,0,0,0,0}, "Strike lower abdomen.","PL AP75 BL5 EL IN9 DD9"}, 
{96,99, 'C', {0,0,0,0,0,0,0,0}, "Chest strike destroys heart/lungs.", "PL DD6 EL IN1 DD1"},
{100,350, 'C', {0,0,0,0,0,0,1,0}, "Head gone. Add 10 to friendly rolls 3 rnds.", ""},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'D', {4,0,0,0,0,0,0,0}, "Loses init for 1 rnd.",""},
{16,20, 'D', {4,0,0,0,1,0,0,0}, "Unbalanced, but the strike is weak.",""},
{21,35, 'D', {5,0,1,0,2,0,0,0}, "Light burns. Must parry for 2 rnds",""},
{36,45, 'D', {7,0,0,1,0,0,0,0}, "Blast stuns for 1 rnd.", "AP+10:2"},
{46,50, 'D', {7,0,0,2,0,0,0,0}, "Explosion of light and fire.", "AP+10:2"},
{51,55, 'D', {10,0,0,1,0,1,0,0}, "Blast stuns for 2 rnds ",""},
{56,60, 'D', {15,0,0,0,0,0,0,0}, "If metal armor: uncon 1 day.",""},
{61,65, 'D', {0,0,0,0,0,0,0,0}, "A good strike", "CH | PL BL2 ST2 EL ST6 BL3"},
{66,66, 'D', {20,0,4,0,0,0,0,360}, "Knocked out. Can't speak 2 months",""},
{67,70, 'D', {12,20,0,0,0,0,0,1}, "Back strike. Knocked down ",""},
{71,75, 'D', {13,0,0,3,0,0,0,0}, "Strike weap arm. Arm useless",""},
{76,80, 'D', {0,0,0,0,0,0,0,0}, "Chest strike.","CH | PL IN100 HT25 EL HT15 ST6 NP6"},
{81,85, 'D', {15,0,3,30,0,0,0,0}, "Lower back strike. Nerve damage",""},
{86,90, 'D', {0,0,0,0,0,0,0,0}, "Abdomen strike.","CH | PL ST9 BL6 EL IN12 DD12"},
{91,95, 'D', {30,0,0,0,0,0,0,0}, "Devastated nervous system. Coma. Vegetable.",""},
{96,99, 'D', {20,0,0,0,0,0,3,0}, "Reels 10'. Massive nerve damage. Dies in 3",""},
{100,350, 'D', {0,0,0,0,0,0,1,0}, "Instant death gives all a fine light show.", "AK AP-15:1"},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{6,10, 'E', {4,0,0,0,0,0,0,0}, "Loses init for 1 rnd.",""},
{11,15, 'E', {5,0,0,0,0,0,0,0}, "If metal armor, loses 2 rnds of init.","IF CH | PL ST1 HT5"},
{16,20, 'E', {6,0,0,1,0,0,0,0}, "Glancing strike stuns for 1 rnd.", ""},
{21,35, 'E', {10,0,0,2,0,0,0,0}, "Gets a minor scorching",""},
{36,45, 'E', {12,0,0,2,0,0,0,0}, "Smoke and light stun for 2 rnds.", "AP+10:2"},
{46,50, 'E', {13,0,0,0,0,0,0,0}, "A good hit", "CH | PL ST2 NP2 EL ST2 HT13"},
{51,55, 'E', {13,0,0,4,0,0,0,0}, "Hot smoke. Loses init for 6 rnds.", ""},
{56,60, 'E', {0,0,2,2,0,0,0,0}, "Drops all in weapon hand.",""},
{61,65, 'E', {14,0,0,1,0,1,0,0}, "Leg strike. Knocked down",""},
{66,66, 'E', {0,0,0,0,0,0,0,0}, "If helm: coma 2 months else dies instantly.", "HA IN100 EL DD1 IN1. AK AP-10:1"},
{67,70, 'E', {15,25,0,4,0,4,0,0}, "Back strike. Minor shock.",""},
{71,75, 'E', {0,0,3,6,0,0,0,0}, "Weapon arm broken. Muscle/cartilage damage.",""},
{76,80, 'E', {18,0,3,0,0,0,0,360}, "Knocked out. Blood loss,nerve damage cost",""},
{81,85, 'E', {0,0,0,12,0,0,12,12}, "Strike rearranges nervous system. Dies in 12",""},
{86,90, 'E', {0,0,0,0,0,0,12,12}, "Crushes pelvis/shatters backbone. Dies in 12",""},
{91,95, 'E', {25,0,0,0,0,0,9,9}, "Strike melts lower skeleton. Dies in 9 rnds.",""},
{96,99, 'E', {0,0,0,0,0,0,1,0}, "Strike destroys both lungs. Cut in half.",""},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "Returns to the dust.", "AK AP-20:1"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CE.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
