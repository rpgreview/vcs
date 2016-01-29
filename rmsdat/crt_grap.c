#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab2 crit[95] = {
{1,5, 'A', {0,0,0,0,0,0,0,0}, "Weak grip. No bonus.", ""},
{6,10, 'A', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{11,15, 'A', {0,0,0,0,0,0,0,0}, "Glancing attack. You've the init next rnd.",""},
{16,20, 'A', {3,0,0,0,0,0,0,0}, "is free, but you've the init next rnd. ",""},
{21,35, 'A', {5,0,0,0,0,0,0,0}, "Grazing strike. You've the init next rnd.",""},
{36,45, 'A', {0,0,0,0,1,0,0,0}, "Blow to lower back. Must parry next rnd.", ""},
{46,50, 'A', {3,0,0,0,1,0,0,0}, "Passing hip strike. Must parry next rnd.", "AP-20:1"},
{51,55, 'A', {0,0,0,0,1,0,0,0}, "Slightly unbalanced. You've init for 2 rnds.", ""},
{56,60, 'A', {0,0,0,0,0,0,0,0}, "Glancing back blow. You've init 2 rnds.", "AP-25:1"},
{61,65, 'A', {3,0,0,1,0,0,0,0}, "Blow to shoulder.", ""},
{66,66, 'A', {2,0,0,2,0,0,0,0}, "Grasp weapon arm disarms foe.",""},
{67,70, 'A', {0,0,0,0,0,0,0,0}, "Passing chest strike.", "AP-20:2"},
{71,75, 'A', {5,0,0,0,0,0,0,0}, "An uneasy hold on midsection.", "AP+50:2"},
{76,80, 'A', {0,0,0,0,0,0,0,0}, "Unfirm hold on midsection. You've the init.", "AP+50:3"},
{81,85, 'A', {3,0,0,2,0,0,0,0}, "Grasp leg. Breaks free. You've init 6 rnds.", ""},
{86,90, 'A', {0,0,0,0,0,0,0,0}, "If shield: must parry next rnd else arm held", "SD AP+50"},
{91,95, 'A', {3,0,0,2,0,2,0,0}, "Entangle leg. Knocked down.",""},
{96,99, 'A', {7,0,0,0,0,0,0,0}, "Tie up completely. Immobilized for 12 rnds.", "IA+12 AP+60:15"},
{100,350, 'A', {9,0,0,0,0,0,0,360}, "Both legs entangled. Uncon.", "AK AP-20:1"},
{1,5, 'B', {0,0,0,0,0,0,0,0}, "Indecision. An opportunity lost.", ""},
{6,10, 'B', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{11,15, 'B', {2,0,0,0,0,0,0,0}, "Passing strike. You've the init next rnd.",""},
{16,20, 'B', {2,0,0,0,1,0,0,0}, "Fends off attack. Must parry 1 rnd.", ""},
{21,35, 'B', {0,0,0,0,0,0,0,0}, "Attack has punch, but nothing more.", "AP-20:1"},
{36,45, 'B', {4,0,0,0,1,0,0,0}, "Unbalance foe. You've init for 2 rnds.", ""},
{46,50, 'B', {5,0,0,1,0,0,0,0}, "Blow to chest stuns for 1 rnd. +5 hits.", ""},
{51,55, 'B', {7,0,0,1,0,0,0,0}, "Blow to back stuns for 1 rnd. +7 hits.", ""},
{56,60, 'B', {0,0,0,1,2,0,0,0}, "Unbalancing strike. Spins free ",""},
{61,65, 'B', {0,0,0,2,0,0,0,0}, "Slipping grasp around waist is weak.",""},
{66,66, 'B', {0,25,0,2,0,0,0,0}, "Grasp weapon arm disarms, sprains wrist.",""},
{67,70, 'B', {4,0,0,1,0,1,0,0}, "Entangle leg.",""},
{71,75, 'B', {4,0,0,0,0,0,0,0}, "Attack yields a weak hold on lower chest.", "AP+50:3"},
{76,80, 'B', {0,0,0,0,0,0,0,0}, "Entangle shield arm. At -30 until dropped.", "SD AP+30 EL AP+40"},
{81,85, 'B', {0,0,0,0,0,0,0,0}, "Infirm grasp on midsection. You've the init.", "AP+50:6"},
{86,90, 'B', {0,10,0,2,0,2,0,0}, "Entangle leg. Knocked down. Pulled muscle",""},
{91,95, 'B', {0,25,0,2,0,2,0,0}, "Both of legs are tied up. Downed, disarmed",""},
{96,99, 'B', {0,40,0,6,0,0,0,0}, "Completely entangled/immobilized. Broken leg",""},
{100,350, 'B', {0,90,0,0,0,0,0,360}, "Knocked out. Spained neck",""},
{1,5, 'C', {1,0,0,0,0,0,0,0}, "+1 hit.", ""},
{6,10, 'C', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{11,15, 'C', {4,0,0,0,0,0,0,0}, "Grazing side strike. You've the init next rnd.",""},
{16,20, 'C', {4,0,0,0,1,0,0,0}, "Recovers but is forced to parry next rnd.",""},
{21,35, 'C', {2,0,0,1,0,0,0,0}, "Glancing attack.",""},
{36,45, 'C', {0,0,0,1,2,0,0,0}, "Flailing attack.",""},
{46,50, 'C', {0,0,0,0,0,0,0,0}, "Weak grasp around waist.", "AP+25:3"},
{51,55, 'C', {0,0,0,1,0,1,0,0}, "Slipping grasp around leg.",""},
{56,60, 'C', {3,0,0,1,0,1,0,0}, "Breaks free of hold around thigh",""},
{61,65, 'C', {3,0,0,0,0,0,0,0}, "Grasp around chest.", "AP+50:3"},
{66,66, 'C', {5,0,0,0,0,0,0,0}, "Grasp both legs. Knocked down/prone 1 rnd.",""},
{67,70, 'C', {0,0,0,0,0,0,0,0}, "Entangle shield arm. At -50 until dropped.", "AP+50"},
{71,75, 'C', {0,0,0,2,0,0,0,0}, "Attack results in loose grasp on midsection.", "AP+50:3"},
{76,80, 'C', {0,0,0,2,0,2,0,0}, "Entangle weapon arm.", "AP+50:3"},
{81,85, 'C', {0,5,0,3,0,3,0,0}, "Grasp chest breaks rib ",""},
{86,90, 'C', {8,30,0,6,0,0,0,0}, "Entangle foot. Falls. Breaks shoulder.",""},
{91,95, 'C', {0,95,0,44,0,44,0,0}, "Pin both of arms to chest.",""},
{96,99, 'C', {20,0,0,0,0,0,0,360}, "Falls.Disarmed.Breaks weap arm. Uncon",""},
{100,350, 'C', {0,75,0,0,0,0,0,0}, "Grapple neck.","PL AP+75 ST+3 EL DD+1"},
{1,5, 'D', {2,0,0,0,0,0,0,0}, "+2 hits.", ""},
{6,10, 'D', {4,0,0,0,0,0,0,0}, "+4 hits.", ""},
{11,15, 'D', {6,0,0,0,0,0,0,0}, "Glancing blow. You've the init next rnd.",""},
{16,20, 'D', {5,0,0,0,0,0,0,0}, "Unbalances foe. You've init for 2 rnds.",""},
{21,35, 'D', {3,0,0,1,0,0,0,0}, "Hard but misplaced strike. Eludes grip",""},
{36,45, 'D', {0,0,0,0,0,0,0,0}, "Strike to shield arm.","SD HT+3 EL ST+3 AP+25"},
{46,50, 'D', {0,0,0,0,0,0,0,0}, "Weak hold on chest. You've init 4 rnds.", "AP+30:3"},
{51,55, 'D', {0,0,0,0,0,0,0,0}, "Slipping grip around waist.", "AP+50:3"},
{56,60, 'D', {6,0,0,3,0,0,0,0}, "Hold around leg. Grip is slipping.", ""},
{61,65, 'D', {0,0,0,1,0,1,0,0}, "Grasp around chest.", "AP+20:3"},
{66,66, 'D', {6,0,0,0,0,0,0,0}, "Grasp leg.Knocked down. Prone/immobile 2 rnds.", "AP+100:2"},
{67,70, 'D', {7,0,0,1,0,1,0,0}, "Entangle leg.",""},
{71,75, 'D', {0,0,0,1,0,1,0,0}, "Loose hold around midsection.", "AP+70:3"},
{76,80, 'D', {3,0,0,0,0,0,0,0}, "Entangle weapon arm. Arm immobilized.", "AP+25"},
{81,85, 'D', {0,0,0,2,0,2,0,0}, "Knocked down.Stunned.Disarmed.Breaks shield arm.", ""},
{86,90, 'D', {6,0,0,9,0,0,0,0}, "Tie up both of arms. Immobile. Cannot fight.", "AP+50"},
{91,95, 'D', {10,0,0,30,0,30,0,0}, "Entangle and immobilize legs. Falls.", "AP+50"},
{96,99, 'D', {0,0,0,0,0,3,0,0}, "Grapple neck. Disarmed","PL ST+3 EL DD+6 IA+6"},
{100,350, 'D', {0,0,0,0,0,0,0,0}, "Grapple head. If no helm: coma.", "HA ST+9 EL IA+100"},
{1,5, 'E', {3,0,0,0,0,0,0,0}, "+3 hits.", ""},
{6,10, 'E', {5,0,0,0,0,0,0,0}, "Glancing attack. You've the init next rnd.", ""},
{11,15, 'E', {6,0,0,0,1,0,0,0}, "Lame attack, but must parry next rnd.", ""},
{16,20, 'E', {3,0,0,1,0,0,0,0}, "Strong, passing blow.",""},
{21,35, 'E', {0,0,0,1,0,0,0,0}, "Disjointed attack. You've init 2 rnds.", ""},
{36,45, 'E', {0,0,0,1,0,1,0,0}, "Attack to upper leg. Spun about",""},
{46,50, 'E', {0,0,0,1,0,1,0,0}, "Hold around leg. Slips away",""},
{51,55, 'E', {5,0,0,1,0,1,0,0}, "Breaks free of hold around shield arm.",""},
{56,60, 'E', {0,0,0,1,0,1,0,0}, "Grasp around leg.", "AP+25:3"},
{61,65, 'E', {7,0,0,0,0,0,0,0}, "Attack to shield arm.", "SD HT+6 EL ST+3 NP+3"},
{66,66, 'E', {0,20,0,0,0,0,0,3}, "Knocked down. Torn neck muscles. Prone 3 rnds.", ""},
{67,70, 'E', {0,0,0,2,0,2,0,0}, "Entangle weapon arm.", "AP+75:3"},
{71,75, 'E', {9,0,0,2,0,2,0,0}, "Entangle leg. Knocked down.",""},
{76,80, 'E', {0,40,0,0,0,0,0,0}, "Disarmed. Torn ligaments/pulled arm muscle",""},
{81,85, 'E', {0,75,0,0,0,0,0,0}, "Entangle both arms. Pin them to chest.",""},
{86,90, 'E', {0,0,0,2,0,0,0,0}, "Falls, breaks weap.No chest armor: D krush crit.", ""},
{91,95, 'E', {20,95,0,0,0,0,0,360}, "Knocked out. 2 broken arms/broken ankle.",""},
{96,99, 'E', {0,0,0,0,0,0,9,0}, "Strangling hold. Dies in 9 rnds",""},
{100,350, 'E', {0,0,0,0,0,0,1,1}, "Crush windpipe. DEAD.", "AK AP-25:1"}
};

main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_CG.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &crit[0].st, sizeof(crit));
  close(file);
}
