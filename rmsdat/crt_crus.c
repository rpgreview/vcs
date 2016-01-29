#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Zip.", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {3,0,0,0,0,0,0,0}, "Glancing blow. You have the init next rnd.", ""},
{16,20, 'A', {2,0,0,0,1,0,0,0}, "Must parry next rnd of action.", ""},
{21,35, 'A', {3,0,0,0,1,0,0,0}, "Must parry next rnd.","AK AP-5:1"},
{36,45, 'A', {6,0,0,0,0,0,0,0}, "Bruise calf. You gain the init.","AP+5:1"},
{46,50, 'A', {4,0,0,0,0,0,0,0}, "Blow to back. Must parry next rnd","AP+25:1"},
{51,55, 'A', {5,0,0,0,0,0,0,0}, "Blow to chest. A bruised rib.", "AP+25:1"},
{56,60, 'A', {5,0,0,0,0,0,0,0}, "Strike thigh. Parry next rnd.", "AP+25:1"},
{61,65, 'A', {5,0,0,0,0,0,0,0}, "Blow to forearm.", "AK AP-20:1"},
{66,66, 'A', {8,0,0,2,0,2,0,0}, "Shatter shoulder in shield arm.",""},
{67,70, 'A', {8,0,0,2,0,1,0,0}, "Strike upper chest area. Unable to parry",""},
{71,75, 'A', {5,20,0,1,0,1,0,0}, "Blow to lower leg. Bad bruise.",""},
{76,80, 'A', {0,0,0,0,0,0,0,0}, "Shield arm broken. If no shield it's broken",""},
{81,85, 'A', {10,20,0,2,0,2,0,0}, "Blow to side.",""},
{86,90, 'A', {12,25,0,3,0,3,0,0}, "Strike in back. Muscle/cartilage.",""},
{91,95, 'A', {15,30,0,3,0,3,0,0}, "Break nose. Fights at -30 for 2 days.",""},
{96,99, 'A', {0,0,0,6,0,0,0,0}, "Blow to head. If no helm dead.","IF HA IN:6 ST:6 HT:20 EL DD:1"},
{100,350, 'A', {50,0,0,0,0,0,1,0}, "Blow to jaw. DEAD.","AK AP-20:1"},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Weak grip. No extra damage.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'B', {3,0,0,0,0,0,0,0}, "Glanncing blow. You have the init next rnd.", ""},
{16,20, 'B', {3,0,0,0,0,0,0,0}, "Blow to side. Must parry next rnd.", "AP+10:1"},
{21,35, 'B', {4,0,0,0,0,0,0,0}, "Foe must parry next rnd at -20.", "AP+20:1"},
{36,45, 'B', {6,0,0,0,0,0,0,0}, "Bruise calf. You gain the init.", "AP+20:2|1"},
{46,50, 'B', {6,0,0,0,0,0,0,0}, "Blow to back. Must parry next rnd.", "AP+25:1"},
{51,55, 'B', {6,0,0,0,2,0,0,0}, "Blow to chest. Must parry for next 2 rnds.", ""},
{56,60, 'B', {6,5,0,0,1,0,0,0}, "Strike thigh, bruised. Must parry 1 rnd.",""},
{61,65, 'B', {9,10,0,1,0,0,0,0}, "Blow to forearm.",""},
{66,66, 'B', {0,0,0,3,0,3,0,0}, "Shatter elbow in weapon arm, drops weapon",""},
{67,70, 'B', {10,10,0,2,0,2,0,0}, "Strike upper chest area.",""},
{71,75, 'B', {10,35,0,2,0,1,0,0}, "Blow bruises calf.",""},
{76,80, 'B', {6,0,0,1,0,0,0,0}, "Blow to shield arm, shatters wrist.",""},
{81,85, 'B', {12,25,0,2,0,2,0,0}, "Blow to side. Broken ribs.",""},
{86,90, 'B', {0,30,0,4,0,4,0,0}, "Strike to back,knocked down. Smashes tendons.",""},
{91,95, 'B', {0,0,0,0,0,0,0,0}, "Upper head hit. If no helm, a coma 3 weeks.", "IF HA HT:20 ST:12 EL IN:360"},
{96,99, 'B', {0,0,0,0,0,0,1,0}, "Blast chest. DEAD.", "AK AP-20:1"},
{100,350, 'B', {25,0,0,0,0,0,0,0}, "Blow to neck paralyzes from shoulders down.",""},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {0,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {7,0,0,0,0,0,0,0}, "Blow to side. You receive init next rnd.", ""},
{16,20, 'C', {6,0,0,0,0,0,0,0}, "Blow to side. Must parry next rnd.", "AP+20:1"},
{21,35, 'C', {5,0,0,1,0,0,0,0}, "You break rib.",""},
{36,45, 'C', {9,0,0,0,0,0,0,0}, "Bruise calf. You gain the init.", "AP+25:2"},
{46,50, 'C', {5,0,0,1,0,1,0,0}, "Blow to back. You have the init for 2 rnds.", ""},
{51,55, 'C', {5,10,0,1,0,0,0,0}, "Hard blow to chest.",""},
{56,60, 'C', {6,5,0,0,1,0,0,0}, "Strike thigh. Must parry next rnd.", "AK AP-10:1"},
{61,65, 'C', {8,0,0,1,0,0,0,0}, "Disarm foe with a blow to forearm.",""},
{66,66, 'C', {9,90,0,3,0,3,0,0}, "Shatter knee, knocked down",""},
{67,70, 'C', {10,10,0,1,0,2,0,0}, "Strike upper chest area.",""},
{71,75, 'C', {10,40,0,2,0,2,0,0}, "Blow bruises knee.",""},
{76,80, 'C', {9,50,0,1,0,1,0,0}, "Blow to weapon arm. Bad bruise.",""},
{81,85, 'C', {12,40,0,3,0,3,0,0}, "Strike to side. Breaks 3 ribs.",""},
{86,90, 'C', {20,50,0,6,0,0,0,0}, "Blow to back smashes muscle, breaks bone.",""},
{91,95, 'C', {9,0,0,0,0,0,12,12}, "Shattered thigh. Dies in 12",""},
{96,99, 'C', {0,0,0,0,0,0,6,6}, "Blow to abdomen destroys organs. Dies in 6",""},
{100,350, 'C', {30,0,0,24,0,24,0,0}, "Strike to forehead. Eyes destroyed",""},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'D', {5,0,0,0,0,0,0,0}, "+5 hits. Must parry next rnd at -10.", "AP+10:1"},
{16,20, 'D', {5,5,0,0,0,0,0,0}, "Minor rib fracture. You have init next rnd.", ""},
{21,35, 'D', {5,0,0,1,0,1,0,0}, "Strike to side. Unable to parry next rnd.", ""},
{36,45, 'D', {10,10,0,0,0,0,0,0}, "Major calf bruise. You have init next rnd.", ""},
{46,50, 'D', {10,0,0,1,0,1,0,0}, "Hard blow to back. Unable to parry next rnd.", ""},
{51,55, 'D', {10,15,0,0,0,0,0,0}, "Blow to chest, broken ribs",""},
{56,60, 'D', {6,10,0,1,0,0,0,0}, "Blow to thigh. Is upset.", ""},
{61,65, 'D', {10,10,0,1,0,1,0,0}, "Blow to forearm.",""},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "Blow to head. Uncon 4 hrs. No helm:DEAD","IF HA IN:360 HT:20 EL DD:1"},
{67,70, 'D', {0,20,0,2,0,2,0,0}, "Blow to shoulder. Minor fracture.",""},
{71,75, 'D', {12,50,0,2,0,2,0,0}, "Blow breaks leg bone. Major cartilage damage.",""},
{76,80, 'D', {8,0,0,1,0,1,0,0}, "Blow breaks weapon arm. Tendon damage.",""},
{81,85, 'D', {15,0,0,3,0,3,0,0}, "Strike to side, knocked down.", "AK AP-10:1"},
{86,90, 'D', {25,0,0,0,0,0,2,0}, "Blow to neck breaks backbone. Dies 2 rnds.", ""},
{91,95, 'D', {0,0,0,0,0,0,9,9}, "Blow shatters shield arm. Dies in 9 rnds.",""},
{96,99, 'D', {0,0,0,0,0,0,3,3}, "Blow to side crushes chest. Dies in 3", "AK AP-25:1"},
{100,350, 'D', {25,0,0,0,0,0,1,0}, "Blast to chest, destroy heart.",""},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits", ""},
{6,10, 'E', {6,0,0,0,0,0,0,0}, "Glancing blow. Slightly unbalanced.",""},
{11,15, 'E', {6,0,0,1,0,0,0,0}, "+6 hits.", "AK AP-5:1"},
{16,20, 'E', {0,0,0,1,0,1,0,0}, "Strong blow. Unable to parry next rnd.","AK AP-10:1"},
{21,35, 'E', {6,10,0,0,0,0,0,0}, "Strike cracks ribs. You have init next rnd.", ""},
{36,45, 'E', {12,10,0,0,0,0,0,0}, "Strike to upper leg. Minor fracture.",""},
{46,50, 'E', {15,0,0,1,0,1,0,0}, "Strike to lower back. No parry next rnd.", ""},
{51,55, 'E', {15,15,0,2,0,0,0,0}, "Blow to chest.",""},
{56,60, 'E', {10,10,0,1,0,1,0,0}, "Blow to thigh.",""},
{61,65, 'E', {10,15,0,1,0,1,0,0}, "Blow to forearm. Drops weapon.",""},
{66,66, 'E', {15,0,0,0,0,0,1,0}, "Blow to back of neck. DEAD", "AK AP-10:1"},
{67,70, 'E', {0,0,0,0,0,0,0,0}, "Shield broken. If none shoulder shattered",""},
{71,75, 'E', {15,75,0,3,0,0,0,0}, "Blow breaks hip. Knocked down.",""},
{76,80, 'E', {9,0,0,2,0,2,0,0}, "Blow to elbow. Joint is shattered.",""},
{81,85, 'E', {30,0,0,0,0,0,3,0}, "Catch armpit. Crush ribs.Dies in 3 rnds.",""},
{86,90, 'E', {0,0,0,0,0,0,12,12}, "Neck strike shatters bone. Dies in 12",""},
{91,95, 'E', {25,0,0,0,0,0,6,6}, "Blast to back. Dies in 6",""},
{96,99, 'E', {30,0,0,0,0,0,1,0}, "Crush skull.","AK AP-20:1"},
{100,350, 'E', {35,0,0,2,0,0,7,0}, "Crush hip. Dies in 6.", "AP+30:6"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CK.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
