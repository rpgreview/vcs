#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Zip.", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {1,0,0,0,0,0,0,0}, "You receive init for next rnd. +1 hit.", ""},
{16,20, 'A', {1,0,0,0,1,0,0,0}, "Foe must parry next rnd. +1 hit.", ""},
{21,35, 'A', {2,0,0,0,1,0,0,0}, "Foe must parry next rnd.", "AK AP-10:1"},
{36,45, 'A', {0,0,1,0,0,0,0,0}, "Minor calf wound.",""},
{46,50, 'A', {2,0,0,0,0,0,0,0}, "Strike along back. Must parry next rnd", "AP+30:1"},
{51,55, 'A', {0,0,2,0,0,0,0,0}, "Strike to chest. Must parry next rnd", "AP+25:1"},
{56,60, 'A', {2,0,2,1,0,0,0,0}, "Minor thigh wound.",""},
{61,65, 'A', {2,10,2,0,0,0,0,0}, "Minor forearm wound.",""},
{66,66, 'A', {0,100,0,3,0,0,0,0}, "Strike shield shoulder, arm useless", "AK AP-10:1"},
{67,70, 'A', {5,0,0,2,0,1,0,0}, "Strike along neck. Cannot parry next rnd.", ""},
{71,75, 'A', {3,25,0,1,0,1,0,0}, "Strike lower leg. Tear tendons.",""},
{76,80, 'A', {3,25,3,2,0,0,0,0}, "Strike to upper arm.",""},
{81,85, 'A', {0,0,5,6,0,0,0,0}, "Side wound.", "AK AP-20:1"},
{86,90, 'A', {0,20,3,2,0,2,0,0}, "Strike foe in back. Unable to parry 2 rnds.", ""},
{91,95, 'A', {3,0,2,2,0,2,0,0}, "Rip off ear. Hears at -50.", ""},
{96,99, 'A', {0,0,3,3,0,3,0,0}, "Strike nose, permanent scar.",""},
{100,350, 'A', {0,0,0,0,0,0,1,0}, "Strike through neck. DEAD",""},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Glancing blow. No extra damage. +0.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'B', {3,0,0,0,0,0,0,0}, "Glancing blow to side. You have init next rnd.", ""},
{16,20, 'B', {2,0,0,0,0,0,0,0}, "Blow to side. Foe must parry next rnd.", "AP+10:1"},
{21,35, 'B', {2,0,0,0,0,0,0,0}, "Foe must parry next rnd at -20.", "AP+20:1"},
{36,45, 'B', {2,0,1,0,0,0,0,0}, "Minor calf wound.",""},
{46,50, 'B', {0,0,1,1,0,0,0,0}, "Strike along back.",""},
{51,55, 'B', {3,0,2,0,2,0,0,0}, "Minor chest wound. Must parry 2 rnds.", ""},
{56,60, 'B', {3,0,2,1,0,1,0,0}, "Minor thigh wound. Unable to parry next rnd.", ""},
{61,65, 'B', {2,10,2,1,0,0,0,0}, "Minor forearm wound.",""},
{66,66, 'B', {3,0,0,2,0,2,0,0}, "Strike shatters elbow in weapon arm.",""},
{67,70, 'B', {0,5,3,2,0,0,0,0}, "Strike to neck area.",""},
{71,75, 'B', {3,40,0,2,0,2,0,0}, "Strike to calf. Slash muscle.",""},
{76,80, 'B', {0,30,3,3,0,0,0,0}, "Strike through muscle in shield arm.",""},
{81,85, 'B', {6,25,5,3,0,3,0,0}, "Side wound. Unable to parry 3 rnds.", ""},
{86,90, 'B', {6,0,0,0,0,0,0,0}, "Strike to back of head.", "IF HA HT+6 IN:2 EL DD+1"},
{91,95, 'B', {5,25,3,1,0,0,0,0}, "Strike through hip.",""},
{96,99, 'B', {0,0,0,0,0,0,9,9}, "Strike through cheek. Dies in 9 rnds.", "AK AP-20:1"},
{100,350, 'B', {0,0,0,0,0,0,1,0}, "In eye. DEAD. +10 to allies in 30' next rnd.", ""},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {5,0,0,0,0,0,0,0}, "Blow to side. You have init next rnd.", ""},
{16,20, 'C', {3,0,0,0,2,0,0,0}, "Blow across side. Must parry next rnd", "AP+20:1"},
{21,35, 'C', {0,0,1,1,0,0,0,0}, "Side of chest.",""},
{36,45, 'C', {0,0,2,0,0,0,0,0}, "Minor calf wound.",""},
{46,50, 'C', {0,0,1,2,0,0,0,0}, "Strike across back",""},
{51,55, 'C', {3,0,2,2,0,0,0,0}, "Minor chest wound.",""},
{56,60, 'C', {5,10,2,2,0,0,0,0}, "Minor thigh wound.",""},
{61,65, 'C', {3,10,2,2,0,0,0,0}, "Forearm wound.",""},
{66,66, 'C', {0,90,0,3,0,2,0,3}, "Strike shatters knee, knocked down.",""},
{67,70, 'C', {0,0,0,4,0,2,0,0}, "Strike along neck. Unable parry 2 rnds.", "AK AP-15:1"},
{71,75, 'C', {5,50,0,2,0,2,0,0}, "Strike to lower leg, slash muscle/tendons.", ""},
{76,80, 'C', {0,25,3,6,0,0,0,0}, "Strike shield arm, tear muscle/tendons.",""},
{81,85, 'C', {6,25,5,3,0,3,0,0}, "Side wound. Unable to parry 3 rnds.", ""},
{86,90, 'C', {0,0,0,0,0,0,0,0}, "Strike to back of head.", "IF HA HT+6 IA+2 EL DD+1"},
{91,95, 'C', {0,0,0,0,0,0,9,9}, "Strike through chest, severs a vein. DEAD",""},
{96,99, 'C', {0,0,0,0,0,0,0,100}, "Severs spine. Paralyzed permanently.", ""},
{100,350, 'C', {0,0,0,0,0,0,1,0}, "Shot through both ears. DEAD.", "AK AP-20:6"},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'D', {2,0,0,0,1,0,0,0}, "+2 hits. Must parry for next rnd.", ""},
{16,20, 'D', {0,10,0,0,0,0,0,0}, "Minor side wound. Have the init next rnd.", "|:1"},
{21,35, 'D', {0,0,2,1,0,0,0,0}, "You wound foe along side of hip.",""},
{36,45, 'D', {0,0,3,0,0,0,0,0}, "Minor thigh wound. Foe takes 3 hits per rnd.", ""},
{46,50, 'D', {6,0,0,1,0,1,0,0}, "Strike to lower back. No parry next rnd.", ""},
{51,55, 'D', {5,15,3,0,1,0,0,0}, "Strike to chest. Must parry next rnd.", ""},
{56,60, 'D', {3,0,3,1,0,1,0,0}, "Strike to thigh. Unable to parry next rnd.",""},
{61,65, 'D', {3,10,3,2,0,0,0,0}, "Forearm wound",""},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "Strike to side of head.", "IF HA IA+100 EL DD+1"},
{67,70, 'D', {3,20,0,2,0,2,0,0}, "Strike foe in shoulder.",""},
{71,75, 'D', {6,50,0,2,0,2,0,0}, "Strike lower leg, slash muscle/cartilage.",""},
{76,80, 'D', {12,100,3,6,0,0,0,0}, "Strike shield arm, arm useless.",""},
{81,85, 'D', {10,20,6,3,0,3,0,0}, "Major abdomenal wound.",""},
{86,90, 'D', {9,0,0,0,0,0,6,6}, "Strike through kidneys. Dies in 6 rnds",""},
{91,95, 'D', {0,0,0,0,0,0,6,0}, "Destroy organs. Fights & dies in 6 rnds",""},
{96,99, 'D', {0,0,0,0,0,0,6,6}, "Strike lower back. Dies in 6 rnds.",""},
{100,350, 'D', {0,0,0,0,0,0,1,0}, "Strike brain. DEAD.", "AK AP-20:1"},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{6,10, 'E', {5,0,0,0,0,0,0,0}, "Unbalance foe. You gain init.", ""},
{11,15, 'E', {3,0,0,0,1,0,0,0}, "+3 hits. Must parry for next rnd.", ""},
{16,20, 'E', {0,0,0,1,0,0,0,0}, "Stun foe for 1 rnd.", "AK AP-20:1"},
{21,35, 'E', {2,10,2,0,0,0,0,0}, "Minor side wound.",""},
{36,45, 'E', {0,0,0,0,0,0,0,0}, "Thigh strike.", "IF LA HT+3 EL HT+2 BL+3"},
{46,50, 'E', {5,0,3,1,0,1,0,0}, "Strike lower back. Unable to parry next rnd.", ""},
{51,55, 'E', {5,10,4,1,0,1,0,0}, "Chest wound. Unable to parry 1 rnd.", ""},
{56,60, 'E', {6,0,5,2,0,2,0,0}, "Thigh wound. Unable to parry next rnd.", ""},
{61,65, 'E', {5,15,3,2,0,0,0,0}, "Forearm wound.",""},
{66,66, 'E', {0,0,0,0,0,0,6,6}, "Strike both lungs. Dies in 6 rnds.", "AK AP-10:1"},
{67,70, 'E', {0,100,3,6,0,0,0,0}, "Strike shoulder, sever muscle/tendons.",""},
{71,75, 'E', {0,75,0,3,0,3,0,0}, "Strike lower leg, sever muscle.",""},
{76,80, 'E', {10,100,0,3,0,3,0,0}, "Strike & break weapon arm.",""},
{81,85, 'E', {0,0,0,12,0,12,12,0}, "Strike back severs a vein. Dies in 12 rnds.",""},
{86,90, 'E', {0,0,0,0,0,0,12,12}, "Strike leg severs artery. Dies in 12 rnds.", ""},
{91,95, 'E', {0,0,0,12,0,0,12,0}, "Sever artery in arm. Dies in 12.", ""},
{96,99, 'E', {0,0,0,0,0,0,1,0}, "Into heart,reels back 10', weapon stuck",""},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "Strike through eye. DEAD.", "AK AP-25:1"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CP.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
