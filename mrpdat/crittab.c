/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

crit_tab tabk[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {5,5,0,0,0,0,0,0}, "Minor rib fracture", ""},
{21, 35, {4,0,0,0,0,0,0,0}, "Blow to side, -40 Act 1 rnd", "AP+40:1"},
{36, 50, {5,0,0,1,0,0,0,0}, "Blow to forearm", ""},
{51, 65, {0,0,0,0,0,0,0,0}, "Shield broken, if none shoulder", ""},
{66, 79, {12,40,0,2,0,0,0,0}, "Leg bone broken", ""},
{80, 80, {30,0,0,24,0,0,0,100}, "Uncon,1 eye gone,no helm - 1 month coma", "IN HA IA+100"},
{81, 86, {8,0,0,2,0,0,0,0}, "Broken weapon arm, tendon dam", ""},
{87, 89, {9,60,0,3,0,0,0,0}, "Knocked down, knee shattered", ""},
{90, 90, {25,0,0,0,0,0,0,100}, "Paralyzed from shoulders down", ""},
{91, 96, {20,0,0,0,0,0,0,0}, "Uncon 4 hrs, no helm - dead", "HA IA+100 EL HT+255 DD+1"},
{97, 99, {0,0,0,0,0,0,6,100}, "Ribcage thro lungs, dies 6 rnds", ""},
{100, 100, {255,0,0,0,0,0,1,0}, "Jaw bone into brain, dead", ""},
{101, 106, {15,75,0,3,0,0,0,0}, "Knocked down, hip broken", ""},
{107, 109, {0,0,0,12,0,0,12,0}, "Crushed throat, dies in 12 rnds", ""},
{110, 110, {35,0,0,2,0,0,6,0}, "Crushed hip, dies in 6 rnds", ""},
{111, 116, {0,0,0,5,0,0,0,0}, "Shattered elbow in weapon arm", ""},
{117, 119, {255,0,0,0,0,0,3,0}, "Crushed chest, dies in 3", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Destroyed heart", ""}};

crit_tab tabs[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {0,0,1,0,0,0,0,0}, "Calf wound", ""},
{21, 35, {5,0,0,0,0,0,0,0}, "Upperleg blow, no leg armor bleed 2", "IN LA BL+2"},
{36, 50, {3,5,1,0,0,0,0,0}, "Minor chest wound", ""},
{51, 65, {4,0,2,1,0,0,0,0}, "Minor forearm wound", ""},
{66, 79, {6,10,1,2,0,0,0,0}, "Med thigh wound", ""},
{80, 80, {255,0,0,0,0,0,1,0}, "Neck strike. dies in 1 rnd", ""},
{81, 86, {10,0,1,0,0,0,0,0}, "Weapon arm: muscle/tendon dam", ""},
{87, 89, {10,0,0,30,0,0,0,0}, "Destroys 1 eye", ""},
{90, 90, {255,0,0,0,0,0,1,0}, "Disembowled. 25% weap stuck 2 rnds", ""},
{91, 96, {15,0,0,0,0,0,0,100}, "Uncon 6 hrs. No helm, dead", "HA IA+100 EL HT+255 DD+1"},
{97, 99, {0,0,20,0,0,0,0,100}, "Sever lower leg. Unconscious", ""},
{100, 100, {0,0,0,0,0,0,3,100}, "Unconscious, dies in 3 rnds", ""},
{101, 106, {10,10,8,4,0,0,0,0}, "Major stomach wound", ""},
{107, 109, {0,0,15,0,0,0,0,100}, "Sever weapon arm. Uncon & down", ""},
{110, 110, {255,0,0,0,0,0,1,0}, "Impaled heart, dead, 25% weap stuck 3 rnd", ""},
{111, 116, {0,0,12,6,0,0,0,0}, "Sever hand, knocked down", ""},
{117, 119, {20,0,0,0,0,0,0,100}, "Sever spine, paralyzed", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Destroys brain, dead", ""}};

crit_tab tabp[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {3,0,0,0,0,0,0,0}, "Glancing side blow", ""},
{21, 35, {3,0,0,0,0,0,0,0}, "Thigh blow, no leg armor bleed 3", "IN LA BL+3"},
{36, 50, {2,0,0,1,0,0,0,0}, "Minor forearm wound", ""},
{51, 65, {0,0,1,1,0,0,0,0}, "Strike to side of chest", ""},
{66, 79, {3,25,0,1,0,0,0,0}, "Strike to lower leg, tendons torn", ""},
{80, 80, {255,0,0,0,0,0,0,0}, "Neck strike, dead", ""},
{81, 86, {10,0,0,3,0,0,0,0}, "Weapon arm broken", ""},
{87, 89, {0,50,0,3,0,0,0,0}, "Lower leg muscle severed", ""},
{90, 90, {255,0,0,0,0,0,6,0}, "Lung strike, dies in 6", ""},
{91, 96, {10,0,0,0,0,0,0,0}, "Uncon 6 hrs. no helm, dead", "HA IA+100 EL HT+255 DD+1"},
{97, 99, {0,0,0,0,0,0,0,100}, "Sever spine, paralyzed", ""},
{100, 100, {255,0,0,0,0,0,1,0}, "Eye strike, dead", ""},
{101, 106, {10,20,6,4,0,0,0,0}, "Major stomach wound", ""},
{107, 109, {0,0,0,0,0,0,6,100}, "Sever backbone, dies in 6 rnds. Uncon", ""},
{110, 110, {255,0,0,0,0,0,1,0}, "Dead, reels 10', weap stuck 3 rnds", ""},
{111, 116, {0,0,12,0,0,0,0,100}, "Unconscious, leg artery severed", ""},
{117, 119, {9,0,0,0,0,0,6,100}, "Down, dies in 6 rnds", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Dead, thro both ears", ""}};

crit_tab tabu[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {2,0,0,0,0,0,0,0}, "Arm blow, -5 Act 2 rnds", "AP+5:2"},
{21, 35, {4,0,0,0,0,0,0,0}, "If no leg armor, +7 stun 1", "IN LA HT+7 ST+1"},
{36, 50, {5,0,0,0,0,0,0,0}, "Chest blow, reels 3', -10 Act 2 rnds", "AP+10:2"},
{51, 65, {5,0,0,0,0,0,0,0}, "Shld drop, if none +8 stun 2", "IN SD HT+3 ST+2"},
{66, 79, {8,0,0,0,0,0,0,0}, "Drop weapon, -10 Act 10 rnds", "AP+10:10"},
{80, 80, {0,80,0,0,0,0,0,0}, "Hip joint broken, tendon torn", ""},
{81, 86, {0,0,0,3,0,0,0,0}, "Drop all, reels 5'", ""},
{87, 89, {0,0,0,6,0,0,0,0}, "Stumble to prone position", ""},
{90, 90, {0,0,0,0,0,0,0,0}, "Reel 10',para @ waist,nerve dam", ""},
{91, 96, {0,0,0,6,0,0,0,0}, "Reel 10', no helm - uncon 24hrs", "IN HA IA+100"},
{97, 99, {0,0,0,15,0,0,0,0}, "On knees, hand weap b-wards 10'", ""},
{100, 100, {0,0,0,0,0,0,0,100}, "Reel 10',arms broken,2 mth coma", ""},
{101, 106, {12,50,0,1,0,0,0,0}, "Leg broken", ""},
{107, 109, {9,0,0,6,0,0,0,0}, "Reel 10',no helm 4 week coma", "IN HA IA+100"},
{110, 110, {0,0,0,0,0,0,12,100}, "Knocked down, dies in 12 rnds", ""},
{111, 116, {0,40,0,7,0,0,0,0}, "Knocked down, lower leg broken", ""},
{117, 119, {0,20,0,9,0,0,0,0}, "If no shld uncon and arm broken", "IN SD IA+100"},
{120, 120, {255,0,0,0,0,0,1,0}, "Reels 20', dead", ""}};

crit_tab tabg[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {2,0,0,0,0,0,0,0}, "Minor wounding", ""},
{21, 35, {3,0,0,0,0,0,0,0}, "If arm armor stun 1", "LA ST+1"},
{36, 50, {0,0,0,1,0,0,0,0}, "Leg blow, spun about", ""},
{51, 65, {0,0,0,0,0,0,0,0}, "At -50 until shld (arm) disentangled", "SD AP+50"},
{66, 79, {0,25,0,2,0,0,0,0}, "Disarmed, wrist sprained", ""},
{80, 80, {9,0,0,0,0,0,0,100}, "Uncon, legs entangled", ""},
{81, 86, {0,40,0,3,0,0,0,0}, "Disarmed, weap arm ligament/muscle torn", ""},
{87, 89, {0,0,0,1,0,0,0,0}, "Entangled, knocked down", ""},
{90, 90, {0,60,0,0,0,0,0,100}, "Uncon, sprained neck", ""},
{91, 96, {0,0,0,9,0,0,0,0}, "Head grappled, no helm coma skull broken", "IN HA IA+100"},
{97, 99, {0,75,0,0,0,0,0,0}, "Arms pinned to chest", ""},
{100, 100, {0,60,0,3,0,0,0,0}, "Dead. If neck armor -60 stun 3 neck sprain", ""},
{101, 106, {0,10,0,5,0,0,0,0}, "Ribs broken", ""},
{107, 109, {20,0,0,0,0,0,0,100}, "Uncon, weapon arm broken", ""},
{110, 110, {0,0,0,5,0,0,6,0}, "Dies in 6 rnds, if neck armor disarm stun 5", ""},
{111, 116, {0,0,0,2,0,0,0,0}, "Fall,break weap,no chest armor D Crush", ""},
{117, 119, {20,80,0,0,0,0,0,100}, "Uncon, leg/ankle broken", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Neck crushed, dead", ""}};

crit_tab tabh[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {3,0,0,0,0,0,0,0}, "Minor wounding", ""},
{21, 35, {8,0,0,1,0,0,0,0}, "Minor burns", ""},
{36, 50, {12,0,0,1,0,0,0,0}, "Blinded by hot smoke", ""},
{51, 65, {12,0,0,0,0,0,0,0}, "Clothing burning for 2 rnds +8", "HT+8:2"},
{66, 79, {10,0,0,1,0,0,0,0}, "Knocked down, leg covering gone", ""},
{80, 80, {15,0,5,0,0,0,0,100}, "Face scared,uncon, no helm 1 mnth coma", ""},
{81, 86, {0,0,2,1,0,0,0,0}, "Knocked down, backpack destroyed", ""},
{87, 89, {0,0,0,6,0,0,0,0}, "Blind 6 rnd, head covering gone", ""},
{90, 90, {255,0,0,0,0,0,1,0}, "Head gone, dead", ""},
{91, 96, {0,0,0,5,0,0,0,0}, "Shld/hand gone, no shld loses arm & uncon", "IN SD IA+100"},
{97, 99, {0,60,3,6,0,0,0,0}, "Upper leg burnt, lost use of", ""},
{100, 100, {25,0,0,0,0,0,0,100}, "Paralyzed permanently at neck", ""},
{101, 106, {0,20,2,0,0,0,0,0}, "If no leg armor, -70 massive tissue dam", "IN LA AP+50"},
{107, 109, {0,0,0,0,0,0,0,0}, "Dies in 6, if helm blind 2 wks", "IF HA IA+100 EL DD+6"},
{110, 110, {255,0,0,0,0,0,1,0}, "Cut in half, dead, all items gone", ""},
{111, 116, {12,0,0,3,0,0,0,0}, "Down,if chest armor +12 stun 3", "IN PL BL+6"},
{117, 119, {25,0,0,0,0,0,6,6}, "Dies in 6, engulfed, items gone", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Dead, smoking pile", ""}};

crit_tab tabc[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {3,0,0,0,0,0,0,0}, "No armor stun 1", "NO ST+1"},
{21, 35, {7,0,1,0,0,0,0,0}, "Frosty burn", ""},
{36, 50, {5,10,2,0,0,0,0,0}, "Mild frostbite", ""},
{51, 65, {9,0,2,0,0,0,0,0}, "Wood on back useless", ""},
{66, 79, {0,0,0,1,0,0,0,0}, "Foot covering gone, if none -30 frostbite", ""},
{80, 80, {0,0,0,0,0,0,0,100}, "1 month coma, loses nose", ""},
{81, 86, {0,0,0,3,0,0,0,0}, "Down, no leg armor:-40,frostbite,leg useless", "IN LA AP+40"},
{87, 89, {0,0,0,0,0,0,0,100}, "Uncon,loses ear. no neck armor dies in 9", "IN PL DD+9"},
{90, 90, {55,0,0,2,0,0,2,2}, "Head gone, dies in 2", ""},
{91, 96, {0,30,5,4,0,0,0,0}, "Thigh broken, frostbite", ""},
{97, 99, {0,0,0,12,0,0,12,0}, "Pelvis gone, dies in 12", ""},
{100, 100, {0,0,0,0,0,0,0,100}, "Eyes frozen, paralyzed, 3 wk coma", ""},
{101, 106, {0,0,6,5,0,0,0,0}, "Frozen hands, no use 1 hr", ""},
{107, 109, {0,0,0,0,0,0,6,0}, "Heart/lungs frozen. Dies in 6", ""},
{110, 110, {0,0,0,0,0,0,3,3}, "Dies in 3", ""},
{111, 116, {0,0,0,0,0,0,0,0}, "Dies in 10,if chest armor uncon", "IN NO | SL DD+10 EL IA+100"},
{117, 119, {255,0,0,0,0,0,1,0}, "Dead, frozen statue", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Dead, shatters", ""}};

crit_tab tabe[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {3,0,0,0,0,0,0,0}, "If metal armor stun 1", "PL | CH ST+1"},
{21, 35, {0,0,0,1,0,0,0,0}, "Explosion of light", ""},
{36, 50, {6,5,0,0,0,0,0,0}, "If metal armor stun 2", "PL | CH ST+2"},
{51, 65, {9,10,0,1,0,0,0,0}, "If metal armor stun 3", "PL | CH ST+3"},
{66, 79, {12,20,0,0,0,0,0,0}, "If metal armor/no shld uncon 1 day", "PL | CH IA+100"},
{80, 80, {0,0,0,0,0,0,0,100}, "Nervous system gone, vegetable 1 mnth", ""},
{81, 86, {0,0,2,6,0,0,0,0}, "Weap arm muscle/cartilage dam, useless", ""},
{87, 89, {0,0,0,0,0,0,12,12}, "Dies in 12 rnds", ""},
{90, 90, {0,0,0,0,0,0,0,0}, "Dead, if leather helm coma 2 wks", "HA IA+100 EL DD+1"},
{91, 96, {0,0,0,0,0,0,0,100}, "Uncon 6 hrs, if metal armor fused to chest", ""},
{97, 99, {0,0,0,0,0,0,6,6}, "Uncon, dies in 6", ""},
{100, 100, {255,0,0,0,0,0,1,0}, "Dead, light show", ""},
{101, 106, {0,0,0,8,0,0,0,0}, "Blind 2 wk,loses nose,if no helm knocked down", "IN HA ST+1"},
{107, 109, {0,0,0,0,0,0,0,0}, "Dead, if chest armor dies in 6", "PL DD+6 EL DD+1"},
{110, 110, {255,0,0,0,0,0,1,0}, "Head gone, dead", ""},
{111, 116, {0,0,6,7,0,0,12,0}, "If no stomach armor dies in 12", ""},
{117, 119, {255,0,0,0,0,0,1,0}, "Cut in half, A crit within 10'", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Dead, pile of dust", ""}};

crit_tab tabi[19] = {
{0, 5, {0,0,0,0,0,0,0,0}, "Nothing", ""},
{6, 20, {5,0,0,0,0,0,0,0}, "Nothing", ""},
{21, 35, {10,0,0,1,0,0,0,0}, "Staggered, side blow", ""},
{36, 50, {12,0,0,0,0,0,0,0}, "Reel 10', no leg armor stun 2", "IN LA ST+2"},
{51, 65, {8,0,0,1,0,0,0,0}, "Knocked down, no leg armor stun 2", "IN LA ST+2"},
{66, 79, {10,0,0,0,0,0,0,0}, "Shld gone, if none arm broken stun 3", "IN SD ST+3"},
{80, 80, {12,0,0,0,0,0,0,0}, "Dies in 3, if helm uncon 1 day", "HA IA+100 EL DD+3"},
{81, 86, {15,10,0,0,0,0,0,0}, "Leg muscle torn, no leg armor -20 stun 3", "IN LA AP+10 ST+3"},
{87, 89, {12,0,0,5,0,0,0,0}, "No speak 1 wk, no neck armor permanent", ""},
{90, 90, {20,0,0,0,0,0,0,0}, "Paralyzed from shoulders, melancholy mood", ""},
{91, 96, {15,50,0,9,0,0,0,0}, "Knee dislocated, cartilage/tendon torn", ""},
{97, 99, {18,0,0,12,0,0,6,0}, "If no stomach armor dies in 6", ""},
{100, 100, {0,0,0,0,0,0,0,0}, "Dead, if helm 3 wk coma", "HA IA+100 EL HT+255 DD+1"},
{101, 106, {15,10,0,7,0,0,0,0}, "Jaw broken, cant eat/talk", ""},
{107, 109, {0,0,0,0,0,0,6,6}, "Dies in 6", ""},
{110, 110, {255,0,0,0,0,0,1,0}, "Explodes, dead", ""},
{111, 116, {0,60,0,3,0,0,0,0}, "Knocked down, arms broken", ""},
{117, 119, {255,0,0,0,0,0,1,0}, "Head explodes, dead", ""},
{120, 120, {255,0,0,0,0,0,1,0}, "Dead, pulped", ""}};

crit_tab tabla[19] = {			/* attack crits for LARGE creatures */
{0, 5, {10,0,0,0,0,0,0,0}, "Weapon breaks in half, upset", ""},
{6, 20, {6,0,0,0,0,0,0,0}, "Minor wounding", ""},
{21, 35, {12,0,0,0,0,0,0,0}, "Minor wounding", ""},
{36, 50, {18,0,0,0,0,0,0,0}, "Minor wounding", ""},
{51, 65, {20,10,0,2,0,0,0,0}, "Staggered by strong blast", ""},
{66, 79, {18,20,5,3,0,0,0,0}, "Fine leg strike", ""},
{80, 80, {15,60,0,0,0,0,6,0}, "Sever jugular vein. Dies in 6 rnds", ""},
{81, 86, {25,10,3,2,0,0,0,0}, "Hard blow", ""},
{87, 89, {0,30,0,0,0,0,6,0}, "Sever leg artery. Dies in 6 rnds", ""},
{90, 90, {20,0,0,6,0,0,6,0}, "Sever forearm vein. Dies in 6 rnds", ""},
{91, 96, {15,20,2,3,0,0,0,0}, "Strike to leg", ""},
{97, 99, {30,0,0,0,0,0,0,100}, "Strike to head. Uncon", ""},
{100, 100, {0,0,0,0,0,0,1,0}, "Heart strike. Dead. 60% weap breaks", ""},
{101, 106, {15,0,0,3,0,0,0,0}, "Shatter weapon arm shoulder", ""},
{107, 109, {0,0,0,2,0,0,0,0}, "Vicious strike, blind", ""},
{110, 110, {0,0,0,0,0,0,1,0}, "Thro cheek, Dead. Weap stuck 2 rnds", ""},
{111, 116, {60,0,0,0,0,0,0,100}, "Jaw shatterd. 1 month coma", ""},
{117, 119, {0,0,0,0,0,0,1,0}, "Dead. Falls on you +20hits, pinned 6", "AK HT+20 IA+6"},
{120, 120, {0,0,0,0,0,0,1,0}, "Destroys brain, Dead", ""}};

crit_tab tabls[19] = {			/* spell crits for LARGE creatures */
{0, 5, {0,0,0,0,0,0,0,0}, "Awed by size", ""},
{6, 20, {5,0,0,0,0,0,0,0}, "Minor wounding", ""},
{21, 35, {8,0,0,0,0,0,0,0}, "Minor wounding", ""},
{36, 50, {10,0,0,0,0,0,0,0}, "Minor wounding", ""},
{51, 65, {12,0,0,0,0,0,0,0}, "Minor wounding", ""},
{66, 79, {15,0,0,0,0,0,0,0}, "Minor wounding", ""},
{80, 80, {15,0,0,2,0,0,0,0}, "Unbalanced by blast", ""},
{81, 86, {20,0,0,1,0,0,0,0}, "Staggered by blast", ""},
{87, 89, {15,20,0,2,0,0,0,0}, "Strike to leg", ""},
{90, 90, {30,0,0,0,0,0,0,100}, "Into mouth, 1 month coma", ""},
{91, 96, {18,10,0,1,0,0,0,0}, "Spun about, off balance", ""},
{97, 99, {25,20,0,3,0,0,0,0}, "Side strike, broken ribs", ""},
{100, 100, {0,0,0,0,0,0,4,0}, "Strike midsection, kidney destroyed. Dies 4", ""},
{101, 106, {20,0,0,2,0,0,0,0}, "Strike head, confused momentarily", ""},
{107, 109, {25,0,0,0,0,0,5,0}, "Severe thigh wound, dies in 5 rnds", ""},
{110, 110, {0,0,0,0,0,0,3,0}, "Neck/spine crushed, dies in 3 rnds", ""},
{111, 116, {15,20,0,0,0,0,0,0}, "Strike eyes, blind 2 rnds", ""},
{117, 119, {0,0,0,0,0,0,3,0}, "Strike body, dies in 3 rnds", ""},
{120, 120, {0,0,0,0,0,0,6,6}, "Crush heart, uncon. Dies in 6 rnds", ""}};

crit_tab tabsa[19] = {		/* attack crits for SUPERLARGE creatures */
{0, 5, {10,0,0,0,0,0,0,0}, "Weapon breaks in half, upset", ""},
{6, 20, {6,0,0,0,0,0,0,0}, "Minor wounding", ""},
{21, 35, {12,0,0,0,0,0,0,0}, "Minor wounding", ""},
{36, 50, {18,0,0,0,0,0,0,0}, "Minor wounding", ""},
{51, 65, {20,10,0,2,0,0,0,0}, "Staggered by strong blast", ""},
{66, 79, {18,20,5,3,0,0,0,0}, "Fine leg strike", ""},
{80, 80, {15,60,0,0,0,0,6,0}, "Sever jugular vein. Dies in 6 rnds", ""},
{81, 86, {25,10,3,2,0,0,0,0}, "Hard blow", ""},
{87, 89, {0,30,0,0,0,0,6,0}, "Sever leg artery. Dies in 6 rnds", ""},
{90, 90, {20,0,0,6,0,0,6,0}, "Sever forearm vein. Dies in 6 rnds", ""},
{91, 96, {15,20,2,3,0,0,0,0}, "Strike to leg", ""},
{97, 99, {30,0,0,0,0,0,0,100}, "Strike to head. Uncon", ""},
{100, 100, {0,0,0,0,0,0,1,0}, "Heart strike. Dead. 60% weap breaks", ""},
{101, 106, {15,0,0,3,0,0,0,0}, "Shatter weapon arm shoulder", ""},
{107, 109, {0,0,0,2,0,0,0,0}, "Vicious strike, blind", ""},
{110, 110, {0,0,0,0,0,0,1,0}, "Thro cheek, Dead. Weap stuck 2 rnds", ""},
{111, 116, {60,0,0,0,0,0,0,100}, "Jaw shatterd. 1 month coma", ""},
{117, 119, {0,0,0,0,0,0,1,0}, "Dead. Falls on you +20hits, pinned 6", "AK HT+20 IA+6"},
{120, 120, {0,0,0,0,0,0,1,0}, "Destroys brain, Dead", ""}};

crit_tab tabss[19] = {		/* spell crits for SUPERLARGE creatures */
{0, 5, {0,0,0,0,0,0,0,0}, "Awed by size", ""},
{6, 20, {5,0,0,0,0,0,0,0}, "Minor wounding", ""},
{21, 35, {8,0,0,0,0,0,0,0}, "Minor wounding", ""},
{36, 50, {10,0,0,0,0,0,0,0}, "Minor wounding", ""},
{51, 65, {12,0,0,0,0,0,0,0}, "Minor wounding", ""},
{66, 79, {15,0,0,0,0,0,0,0}, "Minor wounding", ""},
{80, 80, {15,0,0,2,0,0,0,0}, "Unbalanced by blast", ""},
{81, 86, {20,0,0,1,0,0,0,0}, "Staggered by blast", ""},
{87, 89, {15,20,0,2,0,0,0,0}, "Strike to leg", ""},
{90, 90, {30,0,0,0,0,0,0,100}, "Into mouth, 1 month coma", ""},
{91, 96, {18,10,0,1,0,0,0,0}, "Spun about, off balance", ""},
{97, 99, {25,20,0,3,0,0,0,0}, "Side strike, broken ribs", ""},
{100, 100, {0,0,0,0,0,0,4,0}, "Strike midsection, kidney destroyed. Dies 4", ""},
{101, 106, {20,0,0,2,0,0,0,0}, "Strike head, confused momentarily", ""},
{107, 109, {25,0,0,0,0,0,5,0}, "Severe thigh wound, dies in 5 rnds", ""},
{110, 110, {0,0,0,0,0,0,3,0}, "Neck/spine crushed, dies in 3 rnds", ""},
{111, 116, {15,20,0,0,0,0,0,0}, "Strike eyes, blind 2 rnds", ""},
{117, 119, {0,0,0,0,0,0,3,0}, "Strike body, dies in 3 rnds", ""},
{120, 120, {0,0,0,0,0,0,6,6}, "Crush heart, uncon. Dies in 6 rnds", ""}};

/*****************************************************************************/
main()
{
int file, i, j, sz;
char *rdata;

  if ((file = open("tab_ck.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabk[0].st, sizeof(tabk));
	close(file);
  }
  if ((file = open("tab_cs.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabs[0].st, sizeof(tabs));
	close(file);
  }
  if ((file = open("tab_cp.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabp[0].st, sizeof(tabp));
	close(file);
  }
  if ((file = open("tab_cu.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabu[0].st, sizeof(tabu));
	close(file);
  }
  if ((file = open("tab_cg.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabg[0].st, sizeof(tabg));
	close(file);
  }
  if ((file = open("tab_ch.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabh[0].st, sizeof(tabh));
	close(file);
  }
  if ((file = open("tab_cc.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabc[0].st, sizeof(tabc));
	close(file);
  }
  if ((file = open("tab_ce.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabe[0].st, sizeof(tabe));
	close(file);
  }
  if ((file = open("tab_ci.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabi[0].st, sizeof(tabi));
	close(file);
  }
  if ((file = open("tab_laa.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabla[0].st, sizeof(tabla));
	close(file);
  }
  if ((file = open("tab_las.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabls[0].st, sizeof(tabls));
	close(file);
  }
  if ((file = open("tab_sla.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabsa[0].st, sizeof(tabsa));
	close(file);
  }
  if ((file = open("tab_sls.dat", O_BINARY|O_TRUNC|O_RDWR|O_CREAT)) != -1)
  {
	write(file, &tabss[0].st, sizeof(tabss));
	close(file);
  }
}
