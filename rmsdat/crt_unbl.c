#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Nary a thing extra.", ""},
{6,10, 'A', {0,0,0,0,0,0,0,0}, "Sorry pal, maybe next time.", ""},
{11,15, 'A', {3,0,0,0,0,0,0,0}, "Glancing strike.", ""},
{16,20, 'A', {3,0,0,0,1,0,0,0}, "Foe must parry next rnd.", ""},
{21,35, 'A', {4,0,0,0,1,0,0,0}, "Weak. Foe must parry next rnd.", ""},
{36,45, 'A', {4,0,0,0,0,0,0,0}, "You gain init for next rnd.", ""},
{46,50, 'A', {5,0,0,0,0,0,0,0}, "Back strike. Must parry next rnd.", "AP+10:1"},
{51,55, 'A', {5,0,0,0,0,0,0,0}, "Chest strike knocks foe back.", "AP+20:1"},
{56,60, 'A', {0,0,0,0,0,0,0,0}, "Glancing leg strike.", "IF LA HT+5 EL HT+7 ST+2"},
{61,65, 'A', {6,0,0,1,0,0,0,0}, "Arm strike.",""},
{66,66, 'A', {7,0,0,2,0,2,0,0}, "Shoulder strike sends foe spinning.",""},
{67,70, 'A', {6,0,0,0,0,0,0,0}, "Chest strike unbalances foe.", "AP+50:2"},
{71,75, 'A', {7,0,0,2,0,0,0,0}, "Blow to lower leg.",""},
{76,80, 'A', {0,0,0,0,0,0,0,0}, "Blow to shield arm. Drops shield", "IF SD HT+8 EL HT+12 ST+2"},
{81,85, 'A', {12,0,0,1,0,1,0,0}, "Side strike. Unable to parry next rnd.", "AK AP-10:1"},
{86,90, 'A', {13,0,0,3,0,0,0,0}, "Blow to back, stumbles 5' sideways.", "AK AP-20:1"},
{91,95, 'A', {0,0,0,0,0,0,0,0}, "Head strike breaks nose.", "IF HA ST+3 EL IA+100"},
{96,99, 'A', {10,0,0,3,0,3,0,0}, "Strike sends foe sprawling on his face.",""},
{100,350, 'A', {0,90,0,999,0,999,0,0}, "Hit hip,knocked down,tendon/joint.",""},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Fairly weak. +0 zip.", ""},
{6,10, 'B', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'B', {4,0,0,0,0,0,0,0}, "Lame side strike. +4 hits.", ""},
{16,20, 'B', {4,0,0,0,0,0,0,0}, "Glancing side blow. Must parry next rnd.", ""},
{21,35, 'B', {5,0,0,0,0,0,0,0}, "Foe is unbalanced.", "AP+20:1"},
{36,45, 'B', {5,0,0,0,0,0,0,0}, "Leg strike unsteadies foe. Get init next rnd", "AP+5:2"},
{46,50, 'B', {5,0,0,0,0,0,0,0}, "Back hit forces foe to parry next rnd.", "AP+20:1"},
{51,55, 'B', {5,0,0,1,0,0,0,0}, "Blow stuns foe for next rnd.", ""},
{56,60, 'B', {6,0,0,0,0,0,0,0}, "Thigh strike bruises foe.", "AP+30:1"},
{61,65, 'B', {6,0,0,0,0,0,0,0}, "Forearm strike disarms foe.", ""},
{66,66, 'B', {8,0,0,2,0,2,0,0}, "Elbow strike numbs forearm. Drops weapon",""},
{67,70, 'B', {7,0,0,1,0,1,0,0}, "Blow to chest. Confused",""},
{71,75, 'B', {9,10,0,0,0,0,0,0}, "Blow bruises calf",""},
{76,80, 'B', {10,10,0,2,0,0,0,0}, "Strike to shield arm. knocked 5'.",""},
{81,85, 'B', {15,0,0,3,0,0,0,0}, "Blow to side. knocked sideways 3'",""},
{86,90, 'B', {12,0,0,2,0,2,0,0}, "Strike to back knocks foe sideways 10'",""},
{91,95, 'B', {9,50,0,6,0,0,0,0}, "Blow to side of head crushes ear area.",""},
{96,99, 'B', {0,0,0,6,0,6,0,0}, "Side strike causes foe to prone position.",""},
{100,350, 'B', {0,0,0,0,0,0,0,0}, "Sends foe flying 10' onto face. Paralyzed",""},
{1,5, 'C', {0,0,0,0,0,0,0,0}, "Nope.", ""},
{6,10, 'C', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'C', {5,0,0,0,0,0,0,0}, "Weak blow. +5 hits.", ""},
{16,20, 'C', {5,0,0,0,1,0,0,0}, "Side strike. Foe must parry next rnd.", ""},
{21,35, 'C', {6,0,0,1,0,0,0,0}, "Chest strike. Foe is stunned next rnd.", ""},
{36,45, 'C', {5,0,0,0,0,0,0,0}, "Blow to leg.", "AP+40:1"},
{46,50, 'C', {5,0,0,1,0,1,0,0}, "Lower back strike. Foe reels",""},
{51,55, 'C', {6,0,0,1,0,1,0,0}, "Blast staggers foe.",""},
{56,60, 'C', {0,0,0,2,0,0,0,0}, "Skipping calf strike.", "IF LA HT+5 EL HT+9 ST+2 AP+10"},
{61,65, 'C', {6,0,0,2,0,0,0,0}, "Shoulder strike disarms foe",""},
{66,66, 'C', {9,80,0,3,0,3,0,0}, "Knee strike,knocked down. Broken knee",""},
{67,70, 'C', {8,20,0,2,0,0,0,0}, "Strike to chest. Broken ribs.",""},
{71,75, 'C', {10,20,0,1,0,1,0,0}, "Bruise leg. Unable to parry next rnd.",""},
{76,80, 'C', {11,25,0,3,0,0,0,0}, "Strike to weapon arm,broken,knocked back 5'",""},
{81,85, 'C', {0,0,0,6,0,0,0,0}, "Knocks foe 5 feet sideways. Drops shield",""},
{86,90, 'C', {14,0,0,6,0,0,0,0}, "Knocked down. Disarmed.", "AK AP-20:1"},
{91,95, 'C', {8,0,0,0,0,0,0,0}, "Spun 10' sideways. Foe fumbles next 3 rnds.", ""},
{96,99, 'C', {0,0,0,8640,0,0,0,0}, "On knees. If 1-hand weapon, backwards 10'",""},
{100,350, 'C', {0,0,0,0,0,0,0,0}, "Knocked 10'. Break arms. 2 month coma.", ""},
{1,5, 'D', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'D', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'D', {6,0,0,0,0,0,0,0}, "Back strike. +6 hits.", ""},
{16,20, 'D', {7,0,0,0,0,0,0,0}, "Blow to side. Foe is at -10 next rnd.", "AP+10:1"},
{21,35, 'D', {8,0,0,1,0,0,0,0}, "Blow is weak",""},
{36,45, 'D', {7,25,0,0,0,0,0,0}, "Calf strike. Hurt muscle. Get init next rnd.", ""},
{46,50, 'D', {8,0,0,1,0,1,0,0}, "Blow to back spins foe.",""},
{51,55, 'D', {10,0,0,1,0,1,0,0}, "Chest strike takes wind out of foe.",""},
{56,60, 'D', {12,0,0,2,0,0,0,0}, "Thigh strike. You have init next 3 rnds.", ""},
{61,65, 'D', {7,0,0,2,0,0,0,0}, "Arm strike disarms foe.", "AK AP-20:1"},
{66,66, 'D', {0,0,0,0,0,0,0,0}, "Hard hit strike.", "IF HA ST+6 EL IA+100"},
{67,70, 'D', {10,25,0,1,0,1,0,0}, "Shoulder strike spins foe, broken collar bone",""},
{71,75, 'D', {12,75,0,1,0,1,0,0}, "Blow break leg. Foe moves at -75.",""},
{76,80, 'D', {10,0,0,3,0,0,0,0}, "Hit weapon arm. Knocked 10'. Drops weapon.",""},
{81,85, 'D', {11,50,0,0,0,0,0,0}, "Shield strike knocks 5', breaks ankle,falls",""},
{86,90, 'D', {12,0,0,4,0,4,0,0}, "Back strike knocks foe down, disarmed",""},
{91,95, 'D', {0,0,0,0,0,0,0,0}, "Strike to arm. If shield, lost", "IF SD HT:10 EL ST+9"},
{96,99, 'D', {0,0,0,0,0,0,0,0}, "Reel 10' backwards. No helm coma 4 weeks", "IF HA HT+9 ST+6 EL IA+100"},
{100,350, 'D', {0,0,0,0,0,0,12,12}, "Knocked down. Coma, dies in 12 rnds.", "AK AP-20:1"},
{1,5, 'E', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'E', {5,0,0,0,0,0,0,0}, "+5 hits.", ""},
{11,15, 'E', {7,0,0,0,0,0,0,0}, "Blow to back.", ""},
{16,20, 'E', {8,0,0,0,0,0,0,0}, "Side blow.", "AP+20:1"},
{21,35, 'E', {9,0,0,1,0,0,0,0}, "Blow cracks rib.", "AP+10:1"},
{36,45, 'E', {0,0,0,0,0,0,0,0}, "Hard glancing blow to leg.", "IF LA HT+10 EL HT+12 ST+2"},
{46,50, 'E', {12,0,0,1,0,1,0,0}, "Strong back blow staggers foe.",""},
{51,55, 'E', {12,0,0,1,0,1,0,0}, "Foe is knocked down.",""},
{56,60, 'E', {14,0,0,3,0,0,0,0}, "Glancing strike to leg.",""},
{61,65, 'E', {13,0,0,2,0,2,0,0}, "Blow to shoulder spins foe.",""},
{66,66, 'E', {30,0,0,0,0,0,0,0}, "Foe is knocked down and is unconscious.",""},
{67,70, 'E', {0,10,0,2,0,2,0,0}, "Knocked down. Minor shoulder fracture.", ""},
{71,75, 'E', {15,0,0,3,0,3,0,0}, "Hard blow to thigh knock foe down.",""},
{76,80, 'E', {15,0,0,4,0,4,0,0}, "Hit shield arm. Back 3',falls down. Disarmed", ""},
{81,85, 'E', {0,50,0,6,0,6,0,0}, "Trips sideways, breaks leg, rolls 5'.",""},
{86,90, 'E', {20,0,0,12,0,12,0,0}, "Cruel head strike. 10' backwards",""},
{91,95, 'E', {0,0,0,0,0,0,0,0}, "Blow to shield shoulder.", "IF SD ST+6 EL IA+100"},
{96,99, 'E', {0,0,0,0,0,0,3,3}, "Pinpoint strike breaks neck. Dies in 3",""},
{100,350, 'E', {0,0,0,0,0,0,1,0}, "Frightening temple strike. DEAD.", "AK AP-20:3"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CU.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
