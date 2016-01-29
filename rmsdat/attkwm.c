#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "ADMPmerp.h"

attk_tab2 attk[107] = {
{150,350,0, {{42,'E','K'},{40,'E','K'},{37,'E','K'},{34,'E','K'},{41,'E','K'},
	   {38,'E','K'},{33,'E','K'},{33,'E','K'},{36,'E','K'},{36,'E','K'},
	   {32,'E','K'},{30,'E','K'},{33,'E','K'},{33,'E','K'},{30,'E','K'},
	   {30,'E','K'},{29,'E','K'},{27,'E','K'},{25,'E','K'},{23,'E','K'}}},
{149,149,0, {{42,'E','K'},{40,'E','K'},{37,'E','K'},{34,'E','K'},{41,'E','K'},
	   {38,'E','K'},{33,'E','K'},{33,'E','K'},{36,'E','K'},{36,'E','K'},
	   {32,'E','K'},{30,'E','K'},{33,'E','K'},{33,'E','K'},{30,'E','K'},
	   {30,'E','K'},{29,'E','K'},{27,'E','K'},{25,'E','K'},{23,'E','K'}}},
{148,148,0, {{41,'E','K'},{40,'E','K'},{36,'E','K'},{33,'E','K'},{41,'E','K'},
	   {38,'E','K'},{33,'E','K'},{33,'E','K'},{36,'E','K'},{36,'E','K'},
	   {32,'E','K'},{30,'E','K'},{33,'E','K'},{33,'E','K'},{30,'E','K'},
	   {30,'E','K'},{29,'E','K'},{27,'E','K'},{25,'E','K'},{23,'E','K'}}},
{147,147,0, {{41,'E','K'},{39,'E','K'},{36,'E','K'},{33,'E','K'},{40,'E','K'},
	   {37,'E','K'},{32,'E','K'},{32,'E','K'},{35,'E','K'},{35,'E','K'},
	   {31,'E','K'},{29,'E','K'},{32,'E','K'},{32,'E','K'},{29,'E','K'},
	   {30,'E','K'},{28,'E','K'},{27,'E','K'},{25,'E','K'},{23,'E','K'}}},
{146,146,0, {{40,'E','K'},{39,'E','K'},{35,'E','K'},{32,'E','K'},{40,'E','K'},
	   {37,'E','K'},{32,'E','K'},{32,'E','K'},{35,'E','K'},{35,'E','K'},
	   {31,'E','K'},{29,'E','K'},{32,'E','K'},{32,'E','K'},{29,'E','K'},
	   {29,'E','K'},{28,'E','K'},{26,'E','K'},{25,'E','K'},{23,'E','K'}}},
{145,145,0, {{40,'E','K'},{38,'E','K'},{35,'E','K'},{32,'E','K'},{39,'E','K'},
	   {36,'E','K'},{32,'E','K'},{32,'E','K'},{34,'E','K'},{34,'E','K'},
	   {30,'E','K'},{29,'E','K'},{31,'E','K'},{32,'E','K'},{29,'E','K'},
	   {29,'E','K'},{28,'E','K'},{26,'E','K'},{24,'E','K'},{22,'E','K'}}},
{144,144,0, {{39,'E','K'},{38,'E','K'},{34,'E','K'},{31,'E','K'},{39,'E','K'},
	   {36,'E','K'},{31,'E','K'},{31,'E','K'},{34,'E','K'},{34,'E','K'},
	   {30,'E','K'},{28,'E','K'},{31,'E','K'},{31,'E','K'},{28,'E','K'},
	   {29,'E','K'},{27,'E','K'},{26,'E','K'},{24,'E','K'},{22,'E','K'}}},
{143,143,0, {{39,'E','K'},{38,'E','K'},{34,'E','K'},{31,'E','K'},{38,'E','K'},
	   {36,'E','K'},{31,'E','K'},{31,'E','K'},{33,'E','K'},{33,'E','K'},
	   {29,'E','K'},{28,'E','K'},{31,'E','K'},{31,'E','K'},{28,'E','K'},
	   {28,'E','K'},{27,'E','K'},{25,'E','K'},{24,'E','K'},{22,'E','K'}}},
{142,142,0, {{38,'E','K'},{37,'E','K'},{33,'E','K'},{30,'E','K'},{38,'E','K'},
	   {35,'E','K'},{31,'E','K'},{31,'E','K'},{33,'E','K'},{33,'E','K'},
	   {29,'E','K'},{28,'E','K'},{30,'E','K'},{30,'E','K'},{28,'E','K'},
	   {28,'E','K'},{26,'E','K'},{25,'E','K'},{24,'E','K'},{22,'E','K'}}},
{141,141,0, {{38,'E','K'},{37,'E','K'},{33,'E','K'},{30,'E','K'},{37,'E','K'},
	   {35,'E','K'},{30,'E','K'},{30,'E','K'},{33,'E','K'},{32,'E','K'},
	   {29,'E','K'},{27,'E','K'},{30,'E','K'},{30,'E','K'},{27,'E','K'},
	   {28,'E','K'},{26,'E','K'},{25,'E','K'},{23,'E','K'},{22,'E','K'}}},
{140,140,0, {{37,'E','K'},{36,'E','K'},{32,'E','K'},{29,'E','K'},{37,'E','K'},
	   {34,'E','K'},{30,'E','K'},{30,'E','K'},{32,'E','K'},{32,'E','K'},
	   {28,'E','K'},{27,'E','K'},{29,'E','K'},{30,'E','K'},{27,'E','K'},
	   {27,'E','K'},{26,'E','K'},{25,'E','K'},{23,'E','K'},{21,'E','K'}}},
{139,139,0, {{37,'E','K'},{36,'E','K'},{32,'E','K'},{29,'E','K'},{36,'E','K'},
	   {34,'E','K'},{30,'E','K'},{30,'E','K'},{32,'E','K'},{31,'E','K'},
	   {28,'E','K'},{26,'E','K'},{29,'E','K'},{29,'E','K'},{27,'E','K'},
	   {27,'E','K'},{26,'E','K'},{24,'E','K'},{23,'D','K'},{21,'D','K'}}},
{138,138,0, {{36,'E','K'},{35,'E','K'},{31,'E','K'},{28,'E','K'},{36,'E','K'},
	   {33,'E','K'},{29,'E','K'},{29,'E','K'},{31,'E','K'},{31,'E','K'},
	   {27,'E','K'},{26,'E','K'},{29,'E','K'},{29,'E','K'},{26,'E','K'},
	   {27,'E','K'},{25,'E','K'},{24,'E','K'},{23,'D','K'},{21,'D','K'}}},
{137,137,0, {{36,'E','K'},{35,'E','K'},{31,'E','K'},{28,'E','K'},{35,'E','K'},
	   {33,'E','K'},{29,'E','K'},{29,'E','K'},{31,'E','K'},{31,'E','K'},
	   {27,'E','K'},{26,'D','K'},{28,'E','K'},{28,'E','K'},{26,'E','K'},
	   {26,'E','K'},{25,'E','K'},{24,'E','K'},{22,'D','K'},{21,'D','K'}}},
{136,136,0, {{35,'E','K'},{35,'E','K'},{30,'E','K'},{27,'E','K'},{35,'E','K'},
	   {33,'E','K'},{28,'E','K'},{29,'E','K'},{30,'E','K'},{30,'E','K'},
	   {26,'E','K'},{25,'D','K'},{28,'E','K'},{28,'E','K'},{26,'E','K'},
	   {26,'E','K'},{25,'E','K'},{23,'D','K'},{22,'D','K'},{21,'D','K'}}},
{135,135,0, {{35,'E','K'},{34,'E','K'},{30,'E','K'},{27,'E','K'},{35,'E','K'},
	   {32,'E','K'},{28,'E','K'},{28,'E','K'},{30,'E','K'},{30,'E','K'},
	   {26,'E','K'},{25,'D','K'},{27,'E','K'},{28,'D','K'},{25,'D','K'},
	   {26,'D','K'},{24,'E','K'},{23,'D','K'},{22,'D','K'},{20,'D','K'}}},
{134,134,0, {{34,'E','K'},{34,'E','K'},{29,'E','K'},{26,'E','K'},{34,'E','K'},
	   {32,'E','K'},{28,'E','K'},{28,'D','K'},{29,'E','K'},{29,'D','K'},
	   {26,'D','K'},{25,'D','K'},{27,'E','K'},{27,'D','K'},{25,'D','K'},
	   {25,'D','K'},{24,'E','K'},{23,'D','K'},{22,'D','K'},{20,'D','K'}}},
{133,133,0, {{33,'E','K'},{33,'E','K'},{29,'E','K'},{26,'E','K'},{34,'E','K'},
	   {31,'E','K'},{27,'E','K'},{28,'D','K'},{29,'E','K'},{29,'D','K'},
	   {25,'D','K'},{24,'D','K'},{26,'E','K'},{27,'D','K'},{25,'D','K'},
	   {25,'D','K'},{24,'D','K'},{22,'D','K'},{21,'D','K'},{20,'D','K'}}},
{132,132,0, {{33,'E','K'},{33,'E','K'},{28,'E','K'},{25,'E','K'},{33,'E','K'},
	   {31,'E','K'},{27,'E','K'},{27,'D','K'},{29,'D','K'},{28,'D','K'},
	   {25,'D','K'},{24,'D','K'},{26,'E','K'},{26,'D','K'},{24,'D','K'},
	   {25,'D','K'},{23,'D','K'},{22,'D','K'},{21,'D','K'},{20,'D','K'}}},
{131,131,0, {{33,'E','K'},{32,'E','K'},{28,'E','K'},{25,'E','K'},{33,'E','K'},
	   {30,'E','K'},{27,'D','K'},{27,'D','K'},{28,'D','K'},{28,'D','K'},
	   {24,'D','K'},{23,'D','K'},{26,'D','K'},{26,'D','K'},{24,'D','K'},
	   {25,'D','K'},{23,'D','K'},{22,'D','K'},{21,'D','K'},{20,'D','K'}}},
{130,130,0, {{32,'E','K'},{32,'E','K'},{27,'E','K'},{24,'E','K'},{32,'E','K'},
	   {30,'D','K'},{26,'D','K'},{27,'D','K'},{28,'D','K'},{27,'D','K'},
	   {24,'D','K'},{23,'D','K'},{25,'D','K'},{26,'D','K'},{24,'D','K'},
	   {24,'D','K'},{23,'D','K'},{22,'D','K'},{21,'D','K'},{19,'C','K'}}},
{129,129,0, {{32,'E','K'},{32,'E','K'},{27,'D','K'},{24,'D','K'},{32,'D','K'},
	   {30,'D','K'},{26,'D','K'},{26,'D','K'},{27,'D','K'},{27,'D','K'},
	   {23,'D','K'},{23,'D','K'},{25,'D','K'},{25,'D','K'},{23,'D','K'},
	   {24,'D','K'},{22,'D','K'},{21,'D','K'},{20,'C','K'},{19,'C','K'}}},
{128,128,0, {{31,'E','K'},{31,'E','K'},{26,'D','K'},{23,'D','K'},{31,'D','K'},
	   {29,'D','K'},{26,'D','K'},{26,'D','K'},{27,'D','K'},{26,'D','K'},
	   {23,'D','K'},{22,'D','K'},{24,'D','K'},{25,'D','K'},{23,'D','K'},
	   {24,'D','K'},{22,'D','K'},{21,'D','K'},{20,'C','K'},{19,'C','K'}}},
{127,127,0, {{30,'E','K'},{31,'E','K'},{26,'D','K'},{23,'D','K'},{31,'D','K'},
	   {29,'D','K'},{25,'D','K'},{25,'D','K'},{26,'D','K'},{26,'D','K'},
	   {22,'D','K'},{22,'D','K'},{24,'D','K'},{25,'D','K'},{23,'D','K'},
	   {23,'D','K'},{22,'D','K'},{21,'D','K'},{20,'C','K'},{19,'C','K'}}},
{126,126,0, {{30,'E','K'},{30,'E','K'},{25,'D','K'},{22,'D','K'},{30,'D','K'},
	   {28,'D','K'},{25,'D','K'},{25,'D','K'},{26,'D','K'},{25,'D','K'},
	   {22,'D','K'},{22,'D','K'},{24,'D','K'},{24,'D','K'},{22,'D','K'},
	   {23,'D','K'},{21,'D','K'},{20,'D','K'},{20,'C','K'},{19,'C','K'}}},
{125,125,0, {{29,'E','K'},{30,'E','K'},{25,'D','K'},{22,'D','K'},{30,'D','K'},
	   {28,'D','K'},{24,'D','K'},{25,'D','K'},{25,'D','K'},{25,'D','K'},
	   {22,'D','K'},{21,'D','K'},{23,'D','K'},{24,'D','K'},{22,'D','K'},
	   {23,'D','K'},{21,'D','K'},{20,'D','K'},{19,'C','K'},{18,'C','K'}}},
{124,124,0, {{29,'E','K'},{29,'E','K'},{24,'D','K'},{21,'D','K'},{29,'D','K'},
	   {27,'D','K'},{24,'D','K'},{24,'D','K'},{25,'D','K'},{25,'D','K'},
	   {21,'D','K'},{21,'C','K'},{23,'D','K'},{23,'D','K'},{22,'D','K'},
	   {22,'D','K'},{21,'D','K'},{20,'C','K'},{19,'C','K'},{18,'C','K'}}},
{123,123,0, {{28,'E','K'},{29,'E','K'},{24,'D','K'},{21,'D','K'},{29,'D','K'},
	   {27,'D','K'},{24,'D','K'},{24,'D','K'},{25,'D','K'},{24,'D','K'},
	   {21,'D','K'},{20,'C','K'},{22,'D','K'},{23,'D','K'},{21,'D','K'},
	   {22,'D','K'},{20,'D','K'},{19,'C','K'},{19,'C','K'},{18,'C','K'}}},
{122,122,0, {{28,'E','K'},{29,'E','K'},{23,'D','K'},{20,'D','K'},{29,'D','K'},
	   {27,'D','K'},{23,'D','K'},{24,'D','K'},{24,'D','K'},{24,'D','K'},
	   {20,'D','K'},{20,'C','K'},{22,'D','K'},{23,'D','K'},{21,'D','K'},
	   {22,'D','K'},{20,'D','K'},{19,'C','K'},{19,'C','K'},{18,'C','K'}}},
{121,121,0, {{27,'D','K'},{28,'D','K'},{23,'D','K'},{20,'D','K'},{28,'D','K'},
	   {26,'D','K'},{23,'D','K'},{23,'D','K'},{24,'D','K'},{23,'D','K'},
	   {20,'D','K'},{20,'C','K'},{21,'D','K'},{22,'D','K'},{21,'D','K'},
	   {21,'C','K'},{20,'D','K'},{19,'C','K'},{18,'C','K'},{18,'C','K'}}},
{120,120,0, {{27,'D','K'},{28,'D','K'},{22,'D','K'},{19,'D','K'},{28,'D','K'},
	   {26,'D','K'},{23,'D','K'},{23,'C','K'},{23,'D','K'},{23,'D','K'},
	   {19,'D','K'},{19,'C','K'},{21,'D','K'},{22,'C','K'},{20,'C','K'},
	   {21,'C','K'},{19,'D','K'},{19,'C','K'},{18,'C','K'},{17,'C','K'}}},
{119,119,0, {{26,'D','K'},{27,'D','K'},{22,'D','K'},{19,'D','K'},{27,'D','K'},
	   {25,'D','K'},{22,'D','K'},{23,'C','K'},{23,'D','K'},{22,'D','K'},
	   {19,'C','K'},{19,'C','K'},{21,'D','K'},{21,'C','K'},{20,'C','K'},
	   {21,'C','K'},{19,'D','K'},{18,'C','K'},{18,'C','K'},{17,'B','K'}}},
{118,118,0, {{26,'D','K'},{27,'D','K'},{21,'D','K'},{18,'D','K'},{27,'D','K'},
	   {25,'D','K'},{22,'D','K'},{22,'C','K'},{22,'D','K'},{22,'D','K'},
	   {19,'C','K'},{19,'C','K'},{20,'D','K'},{21,'C','K'},{20,'C','K'},
	   {20,'C','K'},{19,'D','K'},{18,'C','K'},{18,'B','K'},{17,'B','K'}}},
{117,117,0, {{25,'D','K'},{26,'D','K'},{21,'D','K'},{18,'D','K'},{26,'D','K'},
	   {24,'D','K'},{22,'D','K'},{22,'C','K'},{22,'D','K'},{21,'C','K'},
	   {18,'C','K'},{18,'C','K'},{20,'D','K'},{21,'C','K'},{19,'C','K'},
	   {20,'C','K'},{18,'C','K'},{18,'C','K'},{17,'B','K'},{17,'B','K'}}},
{116,116,0, {{25,'D','K'},{26,'D','K'},{20,'D','K'},{17,'D','K'},{26,'D','K'},
	   {24,'D','K'},{21,'D','K'},{22,'C','K'},{21,'D','K'},{21,'C','K'},
	   {18,'C','K'},{18,'C','K'},{19,'D','K'},{20,'C','K'},{19,'C','K'},
	   {20,'C','K'},{18,'C','K'},{17,'C','K'},{17,'B','K'},{17,'B','K'}}},
{115,115,0, {{24,'D','K'},{26,'D','K'},{20,'D','K'},{17,'D','K'},{25,'D','K'},
	   {24,'D','K'},{21,'D','K'},{21,'C','K'},{21,'D','K'},{20,'C','K'},
	   {17,'C','K'},{17,'C','K'},{19,'D','K'},{20,'C','K'},{19,'C','K'},
	   {19,'C','K'},{18,'C','K'},{17,'C','K'},{17,'B','K'},{16,'A','K'}}},
{114,114,0, {{24,'D','K'},{25,'D','K'},{19,'D','K'},{16,'D','K'},{25,'D','K'},
	   {23,'D','K'},{20,'D','K'},{21,'C','K'},{21,'C','K'},{20,'C','K'},
	   {17,'C','K'},{17,'C','K'},{19,'D','K'},{19,'C','K'},{18,'C','K'},
	   {19,'C','K'},{17,'C','K'},{17,'C','K'},{17,'B','K'},{16,'A','K'}}},
{113,113,0, {{23,'D','K'},{25,'D','K'},{19,'D','K'},{16,'D','K'},{24,'D','K'},
	   {23,'D','K'},{20,'D','K'},{21,'C','K'},{20,'C','K'},{19,'C','K'},
	   {16,'C','K'},{17,'C','K'},{18,'D','K'},{19,'C','K'},{18,'C','K'},
	   {19,'C','K'},{17,'C','K'},{16,'C','K'},{16,'B','K'},{16,'A','K'}}},
{112,112,0, {{23,'D','K'},{24,'D','K'},{18,'D','K'},{15,'C','K'},{24,'D','K'},
	   {22,'D','K'},{20,'D','K'},{20,'C','K'},{20,'C','K'},{19,'C','K'},
	   {16,'C','K'},{16,'C','K'},{18,'C','K'},{19,'C','K'},{18,'C','K'},
	   {19,'C','K'},{17,'C','K'},{16,'C','K'},{16,'A','K'},{16,'A','K'}}},
{111,111,0, {{22,'D','K'},{24,'D','K'},{18,'C','K'},{15,'C','K'},{23,'D','K'},
	   {22,'C','K'},{19,'C','K'},{20,'C','K'},{19,'C','K'},{19,'C','K'},
	   {16,'C','K'},{16,'C','K'},{17,'C','K'},{18,'C','K'},{17,'C','K'},
	   {18,'C','K'},{16,'C','K'},{16,'C','K'},{16,'A','K'},{15,'A','K'}}},
{110,110,0, {{22,'D','K'},{23,'D','K'},{17,'C','K'},{14,'C','K'},{23,'C','K'},
	   {21,'C','K'},{19,'C','K'},{20,'C','K'},{18,'C','K'},{18,'C','K'},
	   {15,'C','K'},{16,'C','K'},{17,'C','K'},{18,'C','K'},{17,'C','K'},
	   {18,'C','K'},{16,'C','K'},{16,'B','K'},{16,'A','K'},{15,'A','K'}}},
{109,109,0, {{21,'D','K'},{23,'D','K'},{17,'C','K'},{14,'C','K'},{23,'C','K'},
	   {21,'C','K'},{19,'C','K'},{19,'C','K'},{18,'C','K'},{18,'C','K'},
	   {15,'C','K'},{15,'C','K'},{16,'C','K'},{17,'C','K'},{17,'C','K'},
	   {18,'C','K'},{15,'C','K'},{15,'B','K'},{15,'A','K'},{15,'A','K'}}},
{108,108,0, {{21,'D','K'},{23,'D','K'},{16,'C','K'},{13,'C','K'},{22,'C','K'},
	   {21,'C','K'},{18,'C','K'},{19,'C','K'},{18,'C','K'},{17,'C','K'},
	   {14,'C','K'},{15,'C','K'},{16,'C','K'},{17,'C','K'},{16,'C','K'},
	   {17,'B','K'},{15,'C','K'},{15,'B','K'},{15,'A','K'},{15,'A','K'}}},
{107,107,0, {{20,'D','K'},{22,'D','K'},{16,'C','K'},{13,'C','K'},{22,'C','K'},
	   {20,'C','K'},{18,'C','K'},{18,'C','K'},{18,'C','K'},{17,'C','K'},
	   {14,'C','K'},{14,'B','K'},{16,'C','K'},{17,'C','K'},{16,'C','K'},
	   {17,'B','K'},{15,'C','K'},{15,'B','K'},{15,'A','K'},{15,'A','K'}}},
{106,106,0, {{19,'D','K'},{22,'D','K'},{15,'C','K'},{12,'C','K'},{21,'C','K'},
	   {20,'C','K'},{18,'C','K'},{18,'C','K'},{17,'C','K'},{16,'C','K'},
	   {13,'C','K'},{14,'B','K'},{15,'C','K'},{16,'C','K'},{16,'B','K'},
	   {17,'B','K'},{14,'C','K'},{14,'B','K'},{15,'A','K'},{14,0,0}}},
{105,105,0, {{19,'D','K'},{21,'D','K'},{15,'C','K'},{12,'C','K'},{21,'C','K'},
	   {19,'C','K'},{17,'C','K'},{18,'C','K'},{17,'C','K'},{16,'C','K'},
	   {13,'C','K'},{14,'B','K'},{15,'C','K'},{16,'C','K'},{15,'B','K'},
	   {16,'B','K'},{14,'C','K'},{14,'B','K'},{14,'A','K'},{14,0,0}}},
{104,104,0, {{18,'D','K'},{21,'D','K'},{14,'C','K'},{11,'C','K'},{20,'C','K'},
	   {19,'C','K'},{17,'C','K'},{17,'C','K'},{16,'C','K'},{15,'C','K'},
	   {12,'C','K'},{13,'B','K'},{14,'C','K'},{16,'C','K'},{15,'B','K'},
	   {16,'B','K'},{14,'C','K'},{14,'B','K'},{14,'A','K'},{14,0,0}}},
{103,103,0, {{18,'C','K'},{20,'D','K'},{14,'C','K'},{11,'C','K'},{20,'C','K'},
	   {19,'C','K'},{16,'C','K'},{17,'C','K'},{16,'C','K'},{15,'C','K'},
	   {12,'C','K'},{13,'B','K'},{14,'C','K'},{15,'C','K'},{15,'B','K'},
	   {16,'A','K'},{13,'C','K'},{13,'B','K'},{14,'A','K'},{14,0,0}}},
{102,102,0, {{17,'C','K'},{20,'D','K'},{13,'C','K'},{10,'C','K'},{19,'C','K'},
	   {18,'C','K'},{16,'C','K'},{17,'C','K'},{15,'C','K'},{14,'C','K'},
	   {12,'B','K'},{13,'B','K'},{14,'C','K'},{15,'B','K'},{14,'B','K'},
	   {15,'A','K'},{13,'B','K'},{13,'A','K'},{14,'A','K'},{14,0,0}}},
{101,101,0, {{17,'C','K'},{20,'C','K'},{13,'C','K'},{10,'C','K'},{19,'C','K'},
	   {18,'C','K'},{16,'C','K'},{16,'B','K'},{15,'C','K'},{14,'C','K'},
	   {11,'B','K'},{12,'B','K'},{13,'C','K'},{14,'B','K'},{14,'B','K'},
	   {15,'A','K'},{13,'B','K'},{13,'A','K'},{13,0,0},{13,0,0}}},
{100,100,0, {{16,'C','K'},{19,'C','K'},{12,'C','K'},{9,'C','K'},{18,'C','K'},
	   {17,'C','K'},{15,'C','K'},{16,'B','K'},{14,'C','K'},{14,'C','K'},
	   {11,'B','K'},{12,'B','K'},{13,'C','K'},{14,'B','K'},{14,'B','K'},
	   {15,'A','K'},{12,'B','K'},{13,'A','K'},{13,0,0},{13,0,0}}},
{99,99,0, {{16,'C','K'},{19,'C','K'},{12,'B','K'},{9,'C','K'},{18,'C','K'},
	   {17,'C','K'},{15,'C','K'},{16,'B','K'},{14,'C','K'},{13,'C','K'},
	   {10,'B','K'},{11,'B','K'},{12,'C','K'},{14,'B','K'},{13,'A','K'},
	   {14,'A','K'},{12,'B','K'},{12,'A','K'},{13,0,0},{13,0,0}}},
{98,98,0, {{15,'C','K'},{18,'C','K'},{11,'B','K'},{8,'C','K'},{17,'C','K'},
	   {16,'C','K'},{15,'C','K'},{15,'B','K'},{14,'C','K'},{13,'C','K'},
	   {10,'B','K'},{11,'B','K'},{12,'C','K'},{13,'B','K'},{13,'A','K'},
	   {14,'A','K'},{12,'B','K'},{12,'A','K'},{13,0,0},{13,0,0}}},
{97,97,0, {{15,'C','K'},{18,'C','K'},{11,'B','K'},{8,'B','K'},{17,'C','K'},
	   {16,'C','K'},{14,'C','K'},{15,'B','K'},{13,'C','K'},{12,'B','K'},
	   {9,'B','K'},{11,'B','K'},{11,'C','K'},{13,'B','K'},{13,'A','K'},
	   {14,'A','K'},{11,'B','K'},{12,'A','K'},{12,0,0},{13,0,0}}},
{96,96,0, {{14,'C','K'},{17,'C','K'},{10,'B','K'},{7,'B','K'},{17,'C','K'},
	   {16,'C','K'},{14,'C','K'},{15,'B','K'},{13,'C','K'},{12,'B','K'},
	   {9,'B','K'},{10,'B','K'},{11,'C','K'},{12,'B','K'},{12,'A','K'},
	   {13,'A','K'},{11,'B','K'},{11,'A','K'},{12,0,0},{12,0,0}}},
{95,95,0, {{14,'C','K'},{17,'C','K'},{10,'B','K'},{7,'B','K'},{16,'B','K'},
	   {15,'C','K'},{14,'C','K'},{14,'B','K'},{12,'B','K'},{11,'B','K'},
	   {9,'B','K'},{10,'A','K'},{11,'C','K'},{12,'A','K'},{12,'A','K'},
	   {13,'A','K'},{11,'B','K'},{11,'A','K'},{12,0,0},{12,0,0}}},
{94,94,0, {{13,'C','K'},{17,'C','K'},{9,'B','K'},{6,'B','K'},{16,'B','K'},
	   {15,'B','K'},{13,'C','K'},{14,'B','K'},{12,'B','K'},{11,'B','K'},
	   {8,'B','K'},{10,'A','K'},{10,'B','K'},{12,'A','K'},{12,'A','K'},
	   {13,0,0},{10,'A','K'},{11,'A','K'},{12,0,0},{12,0,0}}},
{93,93,0, {{13,'C','K'},{16,'C','K'},{9,'A','K'},{6,'A','K'},{15,'B','K'},
	   {14,'B','K'},{13,'C','K'},{14,'B','K'},{11,'B','K'},{10,'B','K'},
	   {8,'B','K'},{9,'A','K'},{10,'B','K'},{11,'A','K'},{11,'A','K'},
	   {13,0,0},{10,'A','K'},{10,'A','K'},{11,0,0},{12,0,0}}},
{92,92,0, {{12,'B','K'},{16,'C','K'},{8,'A','K'},{5,'A','K'},{15,'B','K'},
	   {14,'B','K'},{12,'C','K'},{13,'B','K'},{11,'B','K'},{10,'B','K'},
	   {7,'B','K'},{9,'A','K'},{9,'B','K'},{11,'A','K'},{11,'A','K'},
	   {12,0,0},{10,'A','K'},{10,'A','K'},{11,0,0},{12,0,0}}},
{91,91,0, {{12,'B','K'},{15,'C','K'},{8,'A','K'},{5,'A','K'},{14,'B','K'},
	   {13,'B','K'},{12,'B','K'},{13,'B','K'},{10,'B','K'},{9,'B','K'},
	   {7,'A','K'},{8,'A','K'},{9,'B','K'},{10,'A','K'},{11,'A','K'},
	   {12,0,0},{9,'A','K'},{10,0,0},{11,0,0},{11,0,0}}},
{90,90,0, {{11,'B','K'},{15,'C','K'},{7,'A','K'},{4,'A','K'},{14,'B','K'},
	   {13,'B','K'},{12,'B','K'},{13,'B','K'},{10,'B','K'},{9,'B','K'},
	   {6,'A','K'},{8,'A','K'},{9,'B','K'},{10,'A','K'},{10,'A','K'},
	   {12,0,0},{9,'A','K'},{10,0,0},{11,0,0},{11,0,0}}},
{89,89,0, {{11,'B','K'},{14,'C','K'},{7,0,0},{4,0,0},{13,'B','K'},
	   {13,'B','K'},{11,'B','K'},{12,'B','K'},{10,'B','K'},{8,'B','K'},
	   {6,'A','K'},{8,'A','K'},{8,'B','K'},{10,'A','K'},{10,0,0},
	   {11,0,0},{9,'A','K'},{9,0,0},{10,0,0},{11,0,0}}},
{88,88,0, {{10,'A','K'},{14,'C','K'},{0,0,0},{0,0,0},{13,'B','K'},
	   {12,'B','K'},{11,'B','K'},{12,'B','K'},{9,'B','K'},{8,'B','K'},
	   {6,'A','K'},{7,'A','K'},{8,'B','K'},{9,'A','K'},{10,0,0},
	   {11,0,0},{8,'A','K'},{9,0,0},{10,0,0},{11,0,0}}},
{87,87,0, {{10,'A','K'},{14,'B','K'},{0,0,0},{0,0,0},{12,'B','K'},
	   {12,'B','K'},{11,'B','K'},{11,'A','K'},{9,'B','K'},{8,'B','K'},
	   {5,'A','K'},{7,'A','K'},{7,'B','K'},{9,'A','K'},{9,0,0},
	   {11,0,0},{8,'A','K'},{9,0,0},{10,0,0},{11,0,0}}},
{86,86,0, {{9,0,0},{13,'B','K'},{0,0,0},{0,0,0},{12,'B','K'},
	   {11,'B','K'},{10,'B','K'},{11,'A','K'},{8,'B','K'},{7,'A','K'},
	   {5,'A','K'},{7,'A','K'},{7,'B','K'},{9,'A','K'},{9,0,0},
	   {10,0,0},{8,'A','K'},{8,0,0},{10,0,0},{10,0,0}}},
{85,85,0, {{0,0,0},{13,'B','K'},{0,0,0},{0,0,0},{11,'B','K'},
	   {11,'B','K'},{10,'B','K'},{11,'A','K'},{8,'B','K'},{7,'A','K'},
	   {4,'A','K'},{6,'A','K'},{6,'A','K'},{8,'A','K'},{9,0,0},
	   {10,0,0},{7,'A','K'},{8,0,0},{9,0,0},{10,0,0}}},
{84,84,0, {{0,0,0},{12,'B','K'},{0,0,0},{0,0,0},{11,'B','K'},
	   {10,'B','K'},{10,'B','K'},{10,'A','K'},{7,'B','K'},{6,'A','K'},
	   {4,'A','K'},{6,0,0},{6,'A','K'},{8,0,0},{8,0,0},
	   {10,0,0},{7,'A','K'},{8,0,0},{9,0,0},{10,0,0}}},
{83,83,0, {{0,0,0},{12,'B','K'},{0,0,0},{0,0,0},{11,'A','K'},
	   {10,'B','K'},{9,'B','K'},{10,'A','K'},{7,'A','K'},{6,'A','K'},
	   {3,'A','K'},{5,0,0},{6,'A','K'},{7,0,0},{8,0,0},
	   {9,0,0},{7,'A','K'},{7,0,0},{9,0,0},{10,0,0}}},
{82,82,0, {{0,0,0},{11,'B','K'},{0,0,0},{0,0,0},{10,'A','K'},
	   {10,'B','K'},{9,'B','K'},{10,'A','K'},{6,'A','K'},{5,'A','K'},
	   {3,0,0},{5,0,0},{5,'A','K'},{7,0,0},{8,0,0},
	   {9,0,0},{6,'A','K'},{7,0,0},{9,0,0},{10,0,0}}},
{81,81,0, {{0,0,0},{11,'A','K'},{0,0,0},{0,0,0},{10,'A','K'},
	   {9,'A','K'},{8,'B','K'},{9,'A','K'},{6,'A','K'},{5,'A','K'},
	   {0,0,0},{5,0,0},{5,'A','K'},{7,0,0},{7,0,0},
	   {9,0,0},{6,0,0},{7,0,0},{8,0,0},{9,0,0}}},
{80,80,0, {{0,0,0},{11,'A','K'},{0,0,0},{0,0,0},{9,'A','K'},
	   {9,'A','K'},{8,'B','K'},{9,'A','K'},{6,'A','K'},{4,'A','K'},
	   {0,0,0},{4,0,0},{4,'A','K'},{6,0,0},{7,0,0},
	   {8,0,0},{6,0,0},{7,0,0},{8,0,0},{9,0,0}}},
{79,79,0, {{0,0,0},{10,'A','K'},{0,0,0},{0,0,0},{9,'A','K'},
	   {8,'A','K'},{8,'A','K'},{9,'A','K'},{5,'A','K'},{4,'A','K'},
	   {0,0,0},{4,0,0},{4,'A','K'},{6,0,0},{7,0,0},
	   {8,0,0},{5,0,0},{6,0,0},{8,0,0},{9,0,0}}},
{78,78,0, {{0,0,0},{10,'A','K'},{0,0,0},{0,0,0},{8,'A','K'},
	   {8,'A','K'},{7,'A','K'},{8,'A','K'},{5,'A','K'},{3,'A','K'},
	   {0,0,0},{4,0,0},{4,'A','K'},{5,0,0},{6,0,0},
	   {8,0,0},{5,0,0},{6,0,0},{8,0,0},{9,0,0}}},
{77,77,0, {{0,0,0},{9,'A','K'},{0,0,0},{0,0,0},{8,'A','K'},
	   {7,'A','K'},{7,'A','K'},{8,'A','K'},{4,'A','K'},{3,0,0},
	   {0,0,0},{3,0,0},{3,'A','K'},{5,0,0},{6,0,0},
	   {7,0,0},{5,0,0},{6,0,0},{7,0,0},{8,0,0}}},
{76,76,0, {{0,0,0},{9,0,0},{0,0,0},{0,0,0},{7,'A','K'},
	   {7,'A','K'},{7,'A','K'},{8,0,0},{4,'A','K'},{0,0,0},
	   {0,0,0},{3,0,0},{3,'A','K'},{5,0,0},{6,0,0},
	   {7,0,0},{4,0,0},{5,0,0},{7,0,0},{8,0,0}}},
{75,75,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{7,'A','K'},
	   {7,'A','K'},{6,'A','K'},{7,0,0},{3,'A','K'},{0,0,0},
	   {0,0,0},{0,0,0},{2,'A','K'},{4,0,0},{5,0,0},
	   {7,0,0},{4,0,0},{5,0,0},{7,0,0},{8,0,0}}},
{74,74,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{6,'A','K'},
	   {6,'A','K'},{6,'A','K'},{7,0,0},{3,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{2,0,0},{4,0,0},{5,0,0},
	   {7,0,0},{4,0,0},{5,0,0},{6,0,0},{8,0,0}}},
{73,73,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{6,'A','K'},
	   {6,'A','K'},{6,'A','K'},{7,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{3,0,0},{5,0,0},
	   {6,0,0},{3,0,0},{4,0,0},{6,0,0},{8,0,0}}},
{72,72,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{5,'A','K'},
	   {5,'A','K'},{5,'A','K'},{6,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{3,0,0},{4,0,0},
	   {6,0,0},{3,0,0},{4,0,0},{6,0,0},{7,0,0}}},
{71,71,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{6,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{3,0,0},{4,0,0},
	   {6,0,0},{3,0,0},{4,0,0},{6,0,0},{7,0,0}}},
{70,70,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{6,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{4,0,0},
	   {5,0,0},{2,0,0},{4,0,0},{6,0,0},{7,0,0}}},
{69,69,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{3,0,0},
	   {5,0,0},{2,0,0},{3,0,0},{5,0,0},{7,0,0}}},
{68,68,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0},
	   {5,0,0},{0,0,0},{3,0,0},{5,0,0},{7,0,0}}},
{67,67,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0},
	   {4,0,0},{0,0,0},{3,0,0},{5,0,0},{6,0,0}}},
{66,66,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0},
	   {4,0,0},{0,0,0},{2,0,0},{5,0,0},{6,0,0}}},
{65,65,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0},
	   {4,0,0},{0,0,0},{2,0,0},{4,0,0},{6,0,0}}},
{64,64,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0},
	   {3,0,0},{0,0,0},{2,0,0},{4,0,0},{6,0,0}}},
{63,63,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {3,0,0},{0,0,0},{0,0,0},{4,0,0},{6,0,0}}},
{62,62,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {3,0,0},{0,0,0},{0,0,0},{4,0,0},{5,0,0}}},
{61,61,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {2,0,0},{0,0,0},{0,0,0},{3,0,0},{5,0,0}}},
{60,60,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {2,0,0},{0,0,0},{0,0,0},{3,0,0},{5,0,0}}},
{59,59,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {2,0,0},{0,0,0},{0,0,0},{3,0,0},{5,0,0}}},
{58,58,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{3,0,0},{5,0,0}}},
{57,57,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{4,0,0}}},
{56,56,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{4,0,0}}},
{55,55,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{4,0,0}}},
{54,54,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{4,0,0}}},
{53,53,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0}}},
{52,52,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0}}},
{51,51,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0}}},
{50,50,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0}}},
{49,49,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0}}},
{48,48,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0}}},
{47,47,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0}}},
{46,46,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0}}},
{45,45,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0}}},
{1,44,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0}}}};


main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_wm.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &attk[0].st, sizeof(attk));
  close(file);
}
