#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Zip.", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {1,0,0,0,0,0,0,0}, "You receive init next rnd.", ""},
{16,20, 'A', {1,0,0,0,1,0,0,0}, "Foe must parry next rnd.", ""},
{21,35, 'A', {2,0,0,0,1,0,0,0}, "Foe must parry next rnd.", "AK AP-10:1"},
{36,45, 'A', {0,0,1,0,0,0,0,0}, "Minor calf wound.",""},
{46,50, 'A', {2,0,0,0,1,0,0,0}, "Blow to back. Must parry next rnd", "AP+30:1"},
{51,55, 'A', {2,0,1,0,1,0,0,0}, "Blow to chest. Must parry next rnd","AP+25:1"},
{56,60, 'A', {3,0,2,0,1,0,0,0}, "Minor thigh wound. Must parry next rnd.",""},
{61,65, 'A', {3,10,2,0,0,0,0,0}, "Minor forearm wound.",""},
{66,66, 'A', {9,0,0,3,0,0,0,0}, "Shield shoulder shattered. Arm is useless.","AK AP-10:1"},
{67,70, 'A', {6,0,3,1,0,1,0,0}, "Slash neck.",""},
{71,75, 'A', {4,30,2,2,0,0,0,0}, "Slash tendons in lower leg.",""},
{76,80, 'A', {5,25,3,2,0,2,0,0}, "Slash upper arm. Unable to parry 2 rnds.", ""},
{81,85, 'A', {6,0,6,5,0,0,0,0}, "Slash foe in side. Major wound.","AK AP-20:1"},
{86,90, 'A', {8,10,2,2,0,2,0,0}, "Slash foe in back. Unable to parry 2 rnds.",""},
{91,95, 'A', {3,0,3,2,0,1,0,0}, "Cut off ear, hears at -50. No parry 1 rnd.", ""},
{96,99, 'A', {2,30,2,6,0,0,0,0}, "Slash nose. A permanent scar.",""},
{100,350, 'A', {0,0,0,0,0,0,1,1}, "Neck strike severs carotid artery. DEAD",""},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Weak strike. +0 hits.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'B', {3,0,0,0,0,0,0,0}, "Glancing blow to side. You have init next rnd.", ""},
{16,20, 'B', {2,0,0,0,0,0,0,0}, "Blow to side. Foe must parry next rnd", "AP+10:1"},
{21,35, 'B', {2,0,0,0,0,0,0,0}, "Foe must parry next rnd at -20.", "AP+20:1"},
{36,45, 'B', {2,0,1,0,0,0,0,0}, "Minor calf wound.",""},
{46,50, 'B', {4,0,0,0,0,0,0,0}, "Blow to back. Foe must parry next rnd", "AP+30:1"},
{51,55, 'B', {3,5,1,0,2,0,0,0}, "Minor chest wound. Must parry next 2 rnds.",""},
{56,60, 'B', {4,0,2,0,2,0,0,0}, "Minor thigh wound. Must parry next 2 rnds.", ""},
{61,65, 'B', {4,10,2,1,0,0,0,0}, "Minor forearm wound.",""},
{66,66, 'B', {8,0,0,2,0,2,0,0}, "Shatter elbow in weapon arm.",""},
{67,70, 'B', {7,5,3,2,0,0,0,0}, "Blow to neck area.",""},
{71,75, 'B', {6,40,0,2,0,1,0,0}, "Slash muscle in calf. Unable to parry 1 rnd.",""},
{76,80, 'B', {6,30,3,2,0,2,0,0}, "Slash muscle in shield arm. No parry 2 rnds.", ""},
{81,85, 'B', {7,0,6,2,0,2,0,0}, "Slash foe in side. A major wound.",""},
{86,90, 'B', {10,0,3,3,0,3,0,0}, "Strike to back knocks foe down. ",""},
{91,95, 'B', {7,20,0,2,0,1,0,0}, "Strike to hip.", "AK AP-10:1"},
{96,99, 'B', {20,0,0,0,0,0,6,6}, "Broken neck/skull. Massive brain damage.",""},
{100,350, 'B', {0,0,0,0,0,0,1,1}, "Disembowel foe, DEAD. 25% weapon stuck.",""},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {6,0,0,0,0,0,0,0}, "Blow to side yields +6 hits.",""},
{16,20, 'C', {4,0,0,0,0,0,0,0}, "Blow to side. Must parry next rnd.", "AP+20:1"},
{21,35, 'C', {3,0,0,1,0,0,0,0}, "You break rib.",""},
{36,45, 'C', {2,0,2,0,0,0,0,0}, "You slash leg.",""},
{46,50, 'C', {3,0,1,1,0,1,0,0}, "Blow to back. May not parry.",""},
{51,55, 'C', {4,10,2,0,1,0,0,0}, "Minor chest wound. Must parry next rnd.", ""},
{56,60, 'C', {5,0,2,1,0,0,0,0}, "Minor thigh wound.",""},
{61,65, 'C', {4,10,3,1,0,0,0,0}, "Medium forearm wound.",""},
{66,66, 'C', {6,90,0,0,0,3,0,3}, "You shatter knee, knocked down.",""},
{67,70, 'C', {8,0,4,2,0,2,0,0}, "Slash neck.","AK AP-10:1"},
{71,75, 'C', {7,45,0,2,0,2,0,0}, "Slash muscle and tendons in lower leg.",""},
{76,80, 'C', {9,100,4,6,0,0,0,0}, "Slash muscle/tendons in shield arm. Useless", ""},
{81,85, 'C', {8,20,4,2,0,2,0,0}, "Strike to side. ",""},
{86,90, 'C', {9,10,0,4,0,4,0,0}, "Blast to back breaks bone, knocked down.",""},
{91,95, 'C', {20,0,0,0,0,0,6,6}, "Sever leg. drops and dies in 6 rnds",""},
{96,99, 'C', {18,0,0,6,0,6,0,0}, "Sever shield arm. Unable to parry next 6 rnds.", ""},
{100,350, 'C', {5,0,0,30,0,30,0,0}, "Destroy eyes.",""},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'D', {3,0,0,0,1,0,0,0}, "Must parry for next rnd of action.", ""},
{16,20, 'D', {2,10,0,0,0,0,0,0}, "Minor side wound. Receive init next rnd.", ""},
{21,35, 'D', {3,0,0,1,0,1,0,0}, "Strike to side. Unable parry 1 rnd.", ""},
{36,45, 'D', {3,0,2,0,0,0,0,0}, "You slash upper leg",""},
{46,50, 'D', {3,0,2,0,0,0,0,1}, "Strike lower back. Unable parry",""},
{51,55, 'D', {5,15,3,0,1,0,0,0}, "Medium chest wound. Must parry next rnd.", ""},
{56,60, 'D', {6,0,2,2,0,0,0,0}, "Medium thigh wound.",""},
{61,65, 'D', {4,10,3,2,0,0,0,0}, "Medium forearm wound.",""},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "If helm out for 6 hours else DEAD.", "|IF HA IN:360 HT:15 EL DD:1"},
{67,70, 'D', {5,20,0,3,0,0,0,0}, "Slash muscle in shoulder area.", "AK AP-10:1"},
{71,75, 'D', {0,50,0,3,0,2,0,0}, "Slash muscle, sever tendons in lower leg.",""},
{76,80, 'D', {10,100,0,2,0,2,0,0}, "Slash muscle and tendons in weapon arm.",""},
{81,85, 'D', {10,10,8,2,0,2,0,0}, "Major abdomenal wound.",""},
{86,90, 'D', {6,0,0,6,0,6,12,0}, "Sever opponent's hand. Dies 12 rnds later.", ""},
{91,95, 'D', {15,0,0,9,0,9,10,0}, "Sever weapon arm. Dies 10 rnds later.", ""},
{96,99, 'D', {20,0,0,0,0,0,3,360}, "Dies in 3 rnds, massive organ damage.",""},
{100,350, 'D', {12,0,0,0,0,0,1,0}, "In heart. DEAD. 25% weapon stuck 2 rnds.", ""},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{6,10, 'E', {5,0,0,0,0,0,0,0}, "Unbalance foe. Get init next rnd.", ""},
{11,15, 'E', {4,0,0,0,1,0,0,0}, "Must parry next rnd of action.", ""},
{16,20, 'E', {0,0,0,1,0,1,0,0}, "May not parry.", "AK AP-10:1"},
{21,35, 'E', {3,10,1,0,0,0,0,0}, "Minor side wound",""},
{36,45, 'E', {0,0,0,0,0,0,0,0}, "Blow to upper leg","IF LA HT:5 EL HT:3 BL:3"}, 
{46,50, 'E', {4,0,3,0,0,0,0,1}, "Strike to lower back. Unable to parry",""},
{51,55, 'E', {6,10,4,2,0,0,0,0}, "Chest wound.",""},
{56,60, 'E', {8,0,5,2,0,0,0,0}, "Thigh wound.",""},
{61,65, 'E', {6,15,3,2,0,0,0,0}, "Forearm wound.",""},
{66,66, 'E', {12,0,0,0,0,0,12,0}, "Sever weapon arm. Dies in 12 rnds.", "AK AP-10:1"},
{67,70, 'E', {0,0,2,4,0,0,0,0}, "Slash tendons, crush bone in shield shoulder",""},
{71,75, 'E', {8,70,0,6,0,0,0,0}, "Slash lower leg, sever muscle, tendons.",""},
{76,80, 'E', {12,0,0,3,0,3,0,0}, "Slash tendons, break bone in shield arm.",""},
{81,85, 'E', {5,0,0,12,0,12,12,0}, "Sever opponent's hand. Dies in 12", ""},
{86,90, 'E', {15,0,0,0,0,0,9,360}, "Sever leg. Dies in 9 rnds.", "AK AP-10:1"},
{91,95, 'E', {20,0,0,0,0,0,0,0}, "Sever spine. Paralyzed neck down permanently.", ""},
{96,99, 'E', {0,0,0,0,0,0,1,0}, "Strike to head destroys brain. DEAD",""},
{100,350, 'E', {12,0,0,12,0,12,0,0}, "Strike to groin area, destroyed",""}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CS.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
