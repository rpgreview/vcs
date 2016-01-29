#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "ADMPmerp.h"

attk_tab2 attk[132] = {
{150,350,0, {{23,'E','K'},{21,'E','K'},{18,'E','K'},{15,'E','K'},{23,'E','K'},
	   {20,'E','K'},{15,'E','K'},{15,'E','K'},{20,'E','K'},{20,'E','K'},
	   {16,'E','K'},{14,'E','K'},{22,'E','K'},{22,'E','K'},{19,'E','K'},
	   {19,'E','K'},{18,'E','K'},{16,'E','K'},{14,'E','K'},{12,'E','K'}}},
{149,149,0, {{23,'E','K'},{21,'E','K'},{18,'E','K'},{15,'E','K'},{23,'E','K'},
	   {20,'E','K'},{15,'E','K'},{15,'E','K'},{20,'E','K'},{20,'E','K'},
	   {16,'E','K'},{14,'E','K'},{22,'E','K'},{22,'E','K'},{19,'E','K'},
	   {19,'E','K'},{18,'E','K'},{16,'E','K'},{14,'E','K'},{12,'E','K'}}},
{148,148,0, {{23,'E','K'},{21,'E','K'},{18,'E','K'},{15,'E','K'},{23,'E','K'},
	   {20,'E','K'},{15,'E','K'},{15,'E','K'},{20,'E','K'},{20,'E','K'},
	   {16,'E','K'},{14,'E','K'},{22,'E','K'},{22,'E','K'},{19,'E','K'},
	   {19,'E','K'},{18,'E','K'},{16,'E','K'},{14,'E','K'},{12,'E','K'}}},
{147,147,0, {{23,'E','K'},{21,'E','K'},{18,'E','K'},{15,'E','K'},{23,'E','K'},
	   {20,'E','K'},{15,'E','K'},{15,'E','K'},{20,'E','K'},{20,'E','K'},
	   {16,'E','K'},{14,'E','K'},{22,'E','K'},{22,'E','K'},{19,'E','K'},
	   {19,'E','K'},{18,'E','K'},{16,'E','K'},{14,'E','K'},{12,'E','K'}}},
{146,146,0, {{22,'E','K'},{21,'E','K'},{18,'E','K'},{15,'E','K'},{23,'E','K'},
	   {20,'E','K'},{15,'E','K'},{15,'E','K'},{20,'E','K'},{20,'E','K'},
	   {16,'E','K'},{14,'E','K'},{22,'E','K'},{22,'E','K'},{19,'E','K'},
	   {19,'E','K'},{18,'E','K'},{16,'E','K'},{14,'E','K'},{12,'E','K'}}},
{145,145,0, {{22,'E','K'},{21,'E','K'},{17,'E','K'},{15,'E','K'},{22,'E','K'},
	   {20,'E','K'},{15,'E','K'},{15,'E','K'},{19,'E','K'},{19,'E','K'},
	   {16,'E','K'},{14,'E','K'},{21,'E','K'},{21,'E','K'},{19,'E','K'},
	   {19,'E','K'},{18,'E','K'},{16,'E','K'},{14,'D','K'},{12,'D','K'}}},
{144,144,0, {{22,'E','K'},{20,'E','K'},{17,'E','K'},{14,'E','K'},{22,'E','K'},
	   {19,'E','K'},{15,'E','K'},{15,'E','K'},{19,'E','K'},{19,'E','K'},
	   {15,'E','K'},{14,'E','K'},{21,'E','K'},{21,'E','K'},{18,'E','K'},
	   {19,'E','K'},{17,'E','K'},{16,'E','K'},{14,'D','K'},{12,'D','K'}}},
{143,143,0, {{22,'E','K'},{20,'E','K'},{17,'E','K'},{14,'E','K'},{22,'E','K'},
	   {19,'E','K'},{15,'E','K'},{15,'E','K'},{19,'E','K'},{19,'E','K'},
	   {15,'E','K'},{13,'D','K'},{21,'E','K'},{21,'E','K'},{18,'E','K'},
	   {18,'E','K'},{17,'E','K'},{15,'D','K'},{14,'D','K'},{12,'D','K'}}},
{142,142,0, {{21,'E','K'},{20,'E','K'},{17,'E','K'},{14,'E','K'},{22,'E','K'},
	   {19,'E','K'},{14,'E','K'},{14,'D','K'},{19,'E','K'},{19,'E','K'},
	   {15,'E','K'},{13,'D','K'},{21,'E','K'},{21,'E','K'},{18,'E','K'},
	   {18,'E','K'},{17,'E','K'},{15,'D','K'},{14,'D','K'},{12,'D','K'}}},
{141,141,0, {{21,'E','K'},{20,'E','K'},{17,'E','K'},{14,'E','K'},{21,'E','K'},
	   {19,'E','K'},{14,'E','K'},{14,'D','K'},{18,'E','K'},{19,'D','K'},
	   {15,'D','K'},{13,'D','K'},{21,'E','K'},{21,'D','K'},{18,'D','K'},
	   {18,'D','K'},{17,'E','K'},{15,'D','K'},{13,'D','K'},{12,'D','K'}}},
{140,140,0, {{21,'E','K'},{20,'E','K'},{16,'E','K'},{14,'E','K'},{21,'E','K'},
	   {19,'E','K'},{14,'D','K'},{14,'D','K'},{18,'E','K'},{18,'D','K'},
	   {15,'D','K'},{13,'D','K'},{20,'E','K'},{20,'D','K'},{18,'D','K'},
	   {18,'D','K'},{17,'E','K'},{15,'D','K'},{13,'C','K'},{12,'C','K'}}},
{139,139,0, {{21,'E','K'},{19,'E','K'},{16,'E','K'},{13,'D','K'},{21,'E','K'},
	   {18,'E','K'},{14,'D','K'},{14,'D','K'},{18,'E','K'},{18,'D','K'},
	   {14,'D','K'},{13,'D','K'},{20,'E','K'},{20,'D','K'},{18,'D','K'},
	   {18,'D','K'},{17,'D','K'},{15,'D','K'},{13,'C','K'},{11,'C','K'}}},
{138,138,0, {{20,'E','K'},{19,'E','K'},{16,'E','K'},{13,'D','K'},{21,'E','K'},
	   {18,'D','K'},{14,'D','K'},{14,'D','K'},{18,'E','K'},{18,'D','K'},
	   {14,'D','K'},{13,'D','K'},{20,'E','K'},{20,'D','K'},{17,'D','K'},
	   {18,'D','K'},{16,'D','K'},{15,'D','K'},{13,'C','K'},{11,'C','K'}}},
{137,137,0, {{20,'E','K'},{19,'E','K'},{16,'E','K'},{13,'D','K'},{20,'E','K'},
	   {18,'D','K'},{14,'D','K'},{14,'D','K'},{17,'E','K'},{18,'D','K'},
	   {14,'D','K'},{13,'D','K'},{20,'D','K'},{20,'D','K'},{17,'D','K'},
	   {17,'D','K'},{16,'D','K'},{15,'D','K'},{13,'C','K'},{11,'C','K'}}},
{136,136,0, {{20,'E','K'},{19,'E','K'},{16,'D','K'},{13,'D','K'},{20,'D','K'},
	   {18,'D','K'},{14,'D','K'},{14,'D','K'},{17,'D','K'},{17,'D','K'},
	   {14,'D','K'},{12,'D','K'},{19,'D','K'},{20,'D','K'},{17,'D','K'},
	   {17,'D','K'},{16,'D','K'},{14,'D','K'},{13,'C','K'},{11,'C','K'}}},
{135,135,0, {{20,'E','K'},{19,'E','K'},{15,'D','K'},{13,'D','K'},{20,'D','K'},
	   {18,'D','K'},{14,'D','K'},{14,'D','K'},{17,'D','K'},{17,'D','K'},
	   {14,'D','K'},{13,'C','K'},{19,'D','K'},{19,'D','K'},{17,'D','K'},
	   {17,'D','K'},{16,'D','K'},{14,'C','K'},{13,'C','K'},{11,'C','K'}}},
{134,134,0, {{19,'E','K'},{18,'E','K'},{15,'D','K'},{12,'D','K'},{20,'D','K'},
	   {17,'D','K'},{13,'D','K'},{13,'C','K'},{17,'D','K'},{17,'D','K'},
	   {14,'D','K'},{12,'C','K'},{19,'D','K'},{19,'D','K'},{17,'D','K'},
	   {17,'D','K'},{16,'D','K'},{14,'C','K'},{13,'C','K'},{11,'B','K'}}},
{133,133,0, {{19,'E','K'},{18,'E','K'},{15,'D','K'},{12,'D','K'},{19,'D','K'},
	   {17,'D','K'},{13,'D','K'},{13,'C','K'},{17,'D','K'},{17,'D','K'},
	   {13,'D','K'},{12,'C','K'},{19,'D','K'},{19,'D','K'},{17,'D','K'},
	   {17,'D','K'},{16,'D','K'},{14,'C','K'},{13,'B','K'},{11,'B','K'}}},
{132,132,0, {{19,'E','K'},{18,'E','K'},{15,'D','K'},{12,'D','K'},{19,'D','K'},
	   {17,'D','K'},{13,'D','K'},{13,'C','K'},{16,'D','K'},{17,'D','K'},
	   {13,'D','K'},{12,'C','K'},{19,'D','K'},{19,'D','K'},{16,'D','K'},
	   {17,'D','K'},{15,'D','K'},{14,'C','K'},{12,'B','K'},{11,'B','K'}}},
{131,131,0, {{19,'E','K'},{18,'E','K'},{13,'D','K'},{12,'D','K'},{19,'D','K'},
	   {17,'D','K'},{13,'D','K'},{13,'C','K'},{16,'D','K'},{16,'D','K'},
	   {13,'D','K'},{12,'D','K'},{18,'D','K'},{19,'D','K'},{16,'D','K'},
	   {16,'C','K'},{15,'D','K'},{14,'C','K'},{12,'B','K'},{11,'B','K'}}},
{130,130,0, {{18,'D','K'},{18,'E','K'},{14,'D','K'},{12,'D','K'},{19,'D','K'},
	   {17,'D','K'},{13,'D','K'},{13,'C','K'},{16,'D','K'},{16,'D','K'},
	   {13,'C','K'},{12,'C','K'},{18,'D','K'},{18,'C','K'},{16,'C','K'},
	   {16,'C','K'},{15,'D','K'},{14,'C','K'},{12,'B','K'},{11,'B','K'}}},
{129,129,0, {{18,'D','K'},{17,'E','K'},{14,'D','K'},{11,'C','K'},{18,'D','K'},
	   {16,'D','K'},{13,'D','K'},{13,'C','K'},{16,'D','K'},{16,'D','K'},
	   {13,'C','K'},{11,'C','K'},{18,'D','K'},{18,'C','K'},{16,'C','K'},
	   {16,'C','K'},{15,'D','K'},{13,'C','K'},{12,'B','K'},{11,'A','K'}}},
{128,128,0, {{18,'D','K'},{17,'D','K'},{14,'D','K'},{11,'C','K'},{18,'D','K'},
	   {16,'D','K'},{13,'D','K'},{13,'C','K'},{15,'D','K'},{16,'C','K'},
	   {12,'C','K'},{11,'C','K'},{18,'D','K'},{18,'C','K'},{16,'C','K'},
	   {16,'C','K'},{15,'D','K'},{13,'C','K'},{12,'B','K'},{10,'A','K'}}},
{127,127,0, {{18,'D','K'},{17,'D','K'},{14,'D','K'},{11,'C','K'},{18,'D','K'},
	   {16,'D','K'},{12,'C','K'},{13,'C','K'},{12,'D','K'},{15,'C','K'},
	   {12,'C','K'},{11,'C','K'},{17,'D','K'},{18,'C','K'},{16,'C','K'},
	   {16,'C','K'},{15,'C','K'},{13,'C','K'},{12,'B','K'},{10,'A','K'}}},
{126,126,0, {{17,'D','K'},{17,'D','K'},{14,'D','K'},{11,'C','K'},{18,'D','K'},
	   {16,'D','K'},{12,'C','K'},{12,'C','K'},{15,'D','K'},{15,'C','K'},
	   {12,'C','K'},{11,'C','K'},{17,'D','K'},{18,'C','K'},{15,'C','K'},
	   {16,'C','K'},{14,'C','K'},{13,'B','K'},{12,'A','K'},{10,'A','K'}}},
{125,125,0, {{17,'D','K'},{17,'D','K'},{13,'C','K'},{11,'C','K'},{17,'D','K'},
	   {16,'C','K'},{12,'C','K'},{12,'C','K'},{15,'D','K'},{15,'C','K'},
	   {12,'C','K'},{11,'C','K'},{17,'D','K'},{17,'C','K'},{15,'C','K'},
	   {15,'C','K'},{14,'C','K'},{13,'B','K'},{12,'A','K'},{10,'A','K'}}},
{124,124,0, {{17,'D','K'},{17,'D','K'},{13,'C','K'},{11,'C','K'},{17,'D','K'},
	   {15,'C','K'},{12,'C','K'},{12,'C','K'},{14,'D','K'},{15,'C','K'},
	   {12,'C','K'},{11,'C','K'},{17,'D','K'},{17,'C','K'},{15,'C','K'},
	   {15,'C','K'},{14,'C','K'},{13,'B','K'},{11,'A','K'},{10,'A','K'}}},
{123,123,0, {{17,'D','K'},{16,'D','K'},{13,'C','K'},{10,'C','K'},{17,'D','K'},
	   {15,'C','K'},{12,'C','K'},{12,'C','K'},{14,'D','K'},{15,'C','K'},
	   {11,'C','K'},{11,'C','K'},{17,'D','K'},{17,'C','K'},{15,'C','K'},
	   {15,'C','K'},{14,'C','K'},{13,'B','K'},{11,'A','K'},{10,'A','K'}}},
{122,122,0, {{16,'D','K'},{16,'D','K'},{13,'C','K'},{10,'C','K'},{17,'D','K'},
	   {15,'C','K'},{12,'C','K'},{12,'C','K'},{14,'D','K'},{14,'C','K'},
	   {11,'C','K'},{10,'C','K'},{16,'C','K'},{17,'C','K'},{15,'C','K'},
	   {15,'B','K'},{14,'C','K'},{12,'B','K'},{11,'A','K'},{10,'A','K'}}},
{121,121,0, {{16,'D','K'},{16,'D','K'},{13,'C','K'},{10,'C','K'},{16,'C','K'},
	   {15,'C','K'},{12,'C','K'},{12,'C','K'},{14,'D','K'},{14,'C','K'},
	   {11,'C','K'},{10,'B','K'},{16,'C','K'},{16,'C','K'},{15,'C','K'},
	   {15,'B','K'},{14,'C','K'},{12,'B','K'},{11,'A','K'},{10,'A','K'}}},
{120,120,0, {{16,'D','K'},{16,'D','K'},{12,'C','K'},{10,'C','K'},{16,'C','K'},
	   {15,'C','K'},{12,'C','K'},{12,'C','K'},{13,'C','K'},{14,'C','K'},
	   {11,'C','K'},{10,'B','K'},{16,'C','K'},{16,'C','K'},{14,'B','K'},
	   {15,'B','K'},{13,'C','K'},{12,'B','K'},{11,'A','K'},{10,'A','K'}}},
{119,119,0, {{16,'D','K'},{16,'D','K'},{12,'C','K'},{10,'C','K'},{16,'C','K'},
	   {14,'C','K'},{11,'C','K'},{12,'B','K'},{13,'C','K'},{14,'C','K'},
	   {11,'C','K'},{10,'B','K'},{16,'C','K'},{16,'C','K'},{14,'B','K'},
	   {14,'B','K'},{13,'C','K'},{12,'B','K'},{11,'A','K'},{10,0,0}}},
{118,118,0, {{15,'D','K'},{15,'D','K'},{12,'C','K'},{9,'C','K'},{16,'C','K'},
	   {14,'C','K'},{11,'C','K'},{11,'B','K'},{13,'C','K'},{13,'C','K'},
	   {11,'C','K'},{10,'B','K'},{16,'C','K'},{16,'C','K'},{14,'B','K'},
	   {14,'B','K'},{13,'C','K'},{12,'B','K'},{11,'A','K'},{10,0,0}}},
{117,117,0, {{15,'C','K'},{15,'D','K'},{12,'C','K'},{9,'B','K'},{15,'C','K'},
	   {14,'C','K'},{11,'C','K'},{11,'B','K'},{13,'C','K'},{13,'C','K'},
	   {10,'C','K'},{10,'B','K'},{15,'C','K'},{13,'C','K'},{14,'B','K'},
	   {14,'B','K'},{13,'C','K'},{12,'A','K'},{11,'A','K'},{9,0,0}}},
{116,116,0, {{15,'C','K'},{15,'D','K'},{11,'C','K'},{9,'B','K'},{15,'C','K'},
	   {14,'C','K'},{11,'C','K'},{11,'B','K'},{13,'C','K'},{13,'C','K'},
	   {10,'B','K'},{10,'B','K'},{15,'C','K'},{15,'C','K'},{14,'B','K'},
	   {14,'B','K'},{13,'B','K'},{12,'A','K'},{11,'A','K'},{9,0,0}}},
{115,115,0, {{15,'C','K'},{15,'D','K'},{11,'C','K'},{9,'B','K'},{15,'C','K'},
	   {14,'C','K'},{11,'C','K'},{11,'B','K'},{12,'C','K'},{13,'C','K'},
	   {10,'B','K'},{9,'B','K'},{15,'C','K'},{15,'B','K'},{14,'B','K'},
	   {14,'A','K'},{13,'B','K'},{11,'A','K'},{10,'A','K'},{9,0,0}}},
{114,114,0, {{14,'C','K'},{15,'D','K'},{11,'B','K'},{9,'B','K'},{15,'C','K'},
	   {13,'C','K'},{11,'C','K'},{11,'B','K'},{12,'C','K'},{13,'C','K'},
	   {10,'B','K'},{9,'B','K'},{15,'C','K'},{15,'B','K'},{13,'B','K'},
	   {14,'A','K'},{12,'B','K'},{11,'A','K'},{10,0,0},{9,0,0}}},
{113,113,0, {{14,'C','K'},{14,'C','K'},{11,'B','K'},{8,'B','K'},{14,'C','K'},
	   {13,'C','K'},{11,'C','K'},{11,'B','K'},{12,'C','K'},{12,'C','K'},
	   {10,'B','K'},{9,'B','K'},{16,'C','K'},{15,'B','K'},{13,'B','K'},
	   {13,'A','K'},{12,'B','K'},{11,'A','K'},{10,0,0},{9,0,0}}},
{112,112,0, {{14,'C','K'},{14,'C','K'},{11,'B','K'},{8,'B','K'},{14,'C','K'},
	   {13,'C','K'},{10,'C','K'},{11,'B','K'},{12,'C','K'},{12,'C','K'},
	   {9,'B','K'},{9,'B','K'},{14,'C','K'},{15,'B','K'},{13,'B','K'},
	   {13,'A','K'},{12,'B','K'},{11,'A','K'},{10,0,0},{9,0,0}}},
{111,111,0, {{14,'C','K'},{14,'C','K'},{10,'B','K'},{8,'B','K'},{14,'C','K'},
	   {13,'C','K'},{10,'B','K'},{11,'B','K'},{11,'C','K'},{12,'B','K'},
	   {9,'B','K'},{9,'B','K'},{14,'C','K'},{14,'B','K'},{13,'A','K'},
	   {13,'A','K'},{12,'B','K'},{11,'A','K'},{10,0,0},{9,0,0}}},
{110,110,0, {{13,'C','K'},{14,'C','K'},{10,'B','K'},{8,'B','K'},{14,'C','K'},
	   {13,'B','K'},{10,'B','K'},{10,'B','K'},{11,'C','K'},{12,'B','K'},
	   {9,'B','K'},{9,'B','K'},{14,'C','K'},{14,'B','K'},{13,'A','K'},
	   {13,'A','K'},{12,'B','K'},{11,'A','K'},{10,0,0},{9,0,0}}},
{109,109,0, {{13,'C','K'},{14,'C','K'},{10,'B','K'},{8,'A','K'},{13,'B','K'},
	   {12,'B','K'},{10,'B','K'},{10,'B','K'},{11,'C','K'},{11,'B','K'},
	   {9,'B','K'},{9,'B','K'},{14,'C','K'},{14,'B','K'},{12,'A','K'},
	   {13,'A','K'},{12,'B','K'},{11,'A','K'},{10,0,0},{9,0,0}}},
{108,108,0, {{13,'C','K'},{13,'C','K'},{10,'B','K'},{7,'A','K'},{13,'B','K'},
	   {12,'B','K'},{10,'B','K'},{10,'B','K'},{11,'C','K'},{11,'B','K'},
	   {9,'B','K'},{8,'B','K'},{13,'B','K'},{14,'B','K'},{12,'A','K'},
	   {13,'A','K'},{11,'B','K'},{10,'A','K'},{10,0,0},{9,0,0}}},
{107,107,0, {{13,'B','K'},{13,'C','K'},{10,'B','K'},{7,'A','K'},{13,'B','K'},
	   {12,'B','K'},{10,'B','K'},{10,'B','K'},{10,'C','K'},{11,'B','K'},
	   {9,'B','K'},{8,'A','K'},{13,'B','K'},{14,'B','K'},{12,'A','K'},
	   {12,'A','K'},{11,'A','K'},{10,'A','K'},{10,0,0},{9,0,0}}},
{106,106,0, {{12,'B','K'},{13,'C','K'},{9,'B','K'},{7,'A','K'},{13,'B','K'},
	   {12,'B','K'},{10,'B','K'},{10,'B','K'},{10,'C','K'},{11,'B','K'},
	   {8,'B','K'},{8,'A','K'},{13,'B','K'},{13,'A','K'},{12,'A','K'},
	   {12,'A','K'},{11,'A','K'},{10,'A','K'},{9,0,0},{8,0,0}}},
{105,105,0, {{12,'B','K'},{13,'C','K'},{9,'A','K'},{7,'A','K'},{12,'B','K'},
	   {12,'B','K'},{10,'B','K'},{10,'B','K'},{10,'C','K'},{11,'B','K'},
	   {8,'B','K'},{8,'A','K'},{13,'B','K'},{13,'A','K'},{12,'A','K'},
	   {12,'A','K'},{11,'A','K'},{10,'A','K'},{9,0,0},{8,0,0}}},
{104,104,0, {{12,'B','K'},{13,'C','K'},{9,'A','K'},{7,'A','K'},{12,'B','K'},
	   {11,'B','K'},{9,'B','K'},{10,'A','K'},{10,'C','K'},{10,'B','K'},
	   {8,'B','K'},{8,'A','K'},{12,'B','K'},{13,'A','K'},{12,'A','K'},
	   {12,0,0},{11,'A','K'},{10,0,0},{9,0,0},{8,0,0}}},
{103,103,0, {{12,'B','K'},{12,'C','K'},{9,'A','K'},{7,'A','K'},{12,'B','K'},
	   {11,'B','K'},{9,'B','K'},{10,'A','K'},{9,'C','K'},{10,'B','K'},
	   {8,'B','K'},{8,'A','K'},{12,'B','K'},{13,'A','K'},{11,'A','K'},
	   {12,0,0},{11,'A','K'},{10,0,0},{9,0,0},{8,0,0}}},
{102,102,0, {{11,'B','K'},{12,'C','K'},{9,'A','K'},{6,'A','K'},{12,'B','K'},
	   {11,'B','K'},{9,'B','K'},{9,'A','K'},{9,'B','K'},{10,'B','K'},
	   {8,'A','K'},{8,'A','K'},{12,'B','K'},{13,'A','K'},{11,'A','K'},
	   {12,0,0},{10,'A','K'},{10,0,0},{9,0,0},{8,0,0}}},
{101,101,0, {{11,'B','K'},{12,'C','K'},{8,'A','K'},{6,'A','K'},{11,'B','K'},
	   {11,'B','K'},{9,'B','K'},{9,'A','K'},{9,'B','K'},{10,'B','K'},
	   {7,'A','K'},{7,'A','K'},{12,'B','K'},{12,'A','K'},{11,'A','K'},
	   {11,0,0},{10,'A','K'},{9,0,0},{9,0,0},{8,0,0}}},
{100,100,0, {{11,'B','K'},{12,'B','K'},{8,'A','K'},{6,'A','K'},{11,'B','K'},
	   {11,'B','K'},{9,'B','K'},{9,'A','K'},{9,'B','K'},{9,'B','K'},
	   {7,'A','K'},{7,'A','K'},{12,'B','K'},{12,'A','K'},{11,'A','K'},
	   {11,0,0},{10,'A','K'},{9,0,0},{9,0,0},{8,0,0}}},
{99,99,0, {{11,'A','K'},{12,'B','K'},{8,'A','K'},{6,0,0},{11,'B','K'},
	   {10,'B','K'},{9,'B','K'},{9,'A','K'},{9,'B','K'},{9,'B','K'},
	   {7,'A','K'},{7,'A','K'},{11,'B','K'},{12,'A','K'},{11,0,0},
	   {11,0,0},{10,'A','K'},{9,0,0},{9,0,0},{8,0,0}}},
{98,98,0, {{10,'A','K'},{12,'B','K'},{8,'A','K'},{6,0,0},{11,'B','K'},
	   {10,'B','K'},{9,'B','K'},{9,'A','K'},{8,'B','K'},{9,'B','K'},
	   {7,'A','K'},{7,'A','K'},{11,'B','K'},{12,'A','K'},{11,0,0},
	   {11,0,0},{10,'A','K'},{9,0,0},{8,0,0},{8,0,0}}},
{97,97,0, {{10,'A','K'},{11,'B','K'},{8,'A','K'},{5,0,0},{10,'B','K'},
	   {10,'B','K'},{9,'A','K'},{9,'A','K'},{8,'B','K'},{9,'A','K'},
	   {7,'A','K'},{7,'A','K'},{11,'A','K'},{11,'A','K'},{10,0,0},
	   {11,0,0},{9,'A','K'},{9,0,0},{8,0,0},{8,0,0}}},
{96,96,0, {{10,'A','K'},{11,'B','K'},{7,'A','K'},{5,0,0},{10,'B','K'},
	   {10,'B','K'},{8,'A','K'},{9,'A','K'},{8,'B','K'},{9,'A','K'},
	   {6,'A','K'},{7,'A','K'},{11,'A','K'},{11,'A','K'},{10,0,0},
	   {11,0,0},{9,'A','K'},{9,0,0},{8,0,0},{8,0,0}}},
{95,95,0, {{10,'A','K'},{11,'B','K'},{7,'A','K'},{5,0,0},{10,'B','K'},
	   {10,'B','K'},{8,'A','K'},{9,'A','K'},{8,'B','K'},{8,'A','K'},
	   {6,'A','K'},{7,'A','K'},{11,'A','K'},{11,'A','K'},{10,0,0},
	   {10,0,0},{9,'A','K'},{9,0,0},{8,0,0},{7,0,0}}},
{94,94,0, {{9,'A','K'},{11,'B','K'},{7,0,0},{5,0,0},{10,'B','K'},
	   {9,'A','K'},{8,'A','K'},{8,'A','K'},{7,'B','K'},{8,'A','K'},
	   {6,'A','K'},{6,0,0},{10,'A','K'},{11,0,0},{10,0,0},
	   {10,0,0},{9,0,0},{8,0,0},{8,0,0},{7,0,0}}},
{93,93,0, {{9,'A','K'},{11,'B','K'},{7,0,0},{5,0,0},{9,'B','K'},
	   {9,'A','K'},{8,'A','K'},{8,'A','K'},{7,'B','K'},{8,'A','K'},
	   {6,'A','K'},{6,0,0},{10,'A','K'},{11,0,0},{10,0,0},
	   {10,0,0},{9,0,0},{8,0,0},{8,0,0},{7,0,0}}},
{92,92,0, {{9,'A','K'},{10,'B','K'},{7,0,0},{4,0,0},{9,'A','K'},
	   {9,'A','K'},{8,'A','K'},{8,'A','K'},{7,'B','K'},{8,'A','K'},
	   {6,'A','K'},{6,0,0},{10,'A','K'},{10,0,0},{10,0,0},
	   {10,0,0},{9,0,0},{8,0,0},{8,0,0},{7,0,0}}},
{91,91,0, {{9,'A','K'},{10,'B','K'},{6,0,0},{4,0,0},{9,'A','K'},
	   {9,'A','K'},{8,'A','K'},{8,'A','K'},{7,'B','K'},{7,'A','K'},
	   {6,'A','K'},{6,0,0},{10,'A','K'},{10,0,0},{9,0,0},
	   {10,0,0},{8,0,0},{8,0,0},{8,0,0},{7,0,0}}},
{90,90,0, {{8,'A','K'},{10,'B','K'},{6,0,0},{4,0,0},{9,'A','K'},
	   {9,'A','K'},{8,'A','K'},{8,'A','K'},{6,'B','K'},{7,'A','K'},
	   {5,'A','K'},{6,0,0},{9,'A','K'},{10,0,0},{9,0,0},
	   {10,0,0},{8,0,0},{8,0,0},{8,0,0},{7,0,0}}},
{89,89,0, {{8,0,0},{10,'A','K'},{6,0,0},{4,0,0},{8,'A','K'},
	   {8,'A','K'},{7,'A','K'},{8,0,0},{6,'B','K'},{7,'A','K'},
	   {5,0,0},{6,0,0},{9,'A','K'},{10,0,0},{9,0,0},
	   {10,0,0},{8,0,0},{8,0,0},{7,0,0},{7,0,0}}},
{88,88,0, {{8,0,0},{10,'A','K'},{6,0,0},{4,0,0},{8,'A','K'},
	   {8,'A','K'},{7,'A','K'},{8,0,0},{6,'B','K'},{7,'A','K'},
	   {5,0,0},{6,0,0},{9,'A','K'},{10,0,0},{9,0,0},
	   {9,0,0},{8,0,0},{8,0,0},{7,0,0},{7,0,0}}},
{87,87,0, {{0,0,0},{9,'A','K'},{0,0,0},{3,0,0},{8,'A','K'},
	   {8,'A','K'},{7,'A','K'},{8,0,0},{6,'B','K'},{7,'A','K'},
	   {5,0,0},{5,0,0},{9,'A','K'},{9,0,0},{9,0,0},
	   {9,0,0},{8,0,0},{7,0,0},{7,0,0},{7,0,0}}},
{86,86,0, {{0,0,0},{9,'A','K'},{0,0,0},{3,0,0},{8,'A','K'},
	   {8,'A','K'},{7,'A','K'},{7,0,0},{5,'A','K'},{6,'A','K'},
	   {5,0,0},{5,0,0},{9,'A','K'},{9,0,0},{9,0,0},
	   {9,0,0},{8,0,0},{7,0,0},{7,0,0},{7,0,0}}},
{85,85,0, {{0,0,0},{9,'A','K'},{0,0,0},{3,0,0},{7,'A','K'},
	   {8,'A','K'},{7,'A','K'},{7,0,0},{5,'A','K'},{6,'A','K'},
	   {4,0,0},{5,0,0},{8,'A','K'},{9,0,0},{8,0,0},
	   {9,0,0},{7,0,0},{7,0,0},{7,0,0},{7,0,0}}},
{84,84,0, {{0,0,0},{9,'A','K'},{0,0,0},{3,0,0},{7,'A','K'},
	   {7,'A','K'},{7,0,0},{7,0,0},{5,'A','K'},{6,0,0},
	   {4,0,0},{5,0,0},{8,0,0},{9,0,0},{8,0,0},
	   {9,0,0},{7,0,0},{7,0,0},{7,0,0},{6,0,0}}},
{83,83,0, {{0,0,0},{9,'A','K'},{0,0,0},{3,0,0},{7,'A','K'},
	   {7,'A','K'},{7,0,0},{7,0,0},{5,'A','K'},{6,0,0},
	   {4,0,0},{5,0,0},{8,0,0},{9,0,0},{8,0,0},
	   {9,0,0},{7,0,0},{7,0,0},{7,0,0},{6,0,0}}},
{82,82,0, {{0,0,0},{8,'A','K'},{0,0,0},{0,0,0},{7,'A','K'},
	   {7,'A','K'},{7,0,0},{7,0,0},{5,'A','K'},{5,0,0},
	   {4,0,0},{5,0,0},{8,0,0},{8,0,0},{8,0,0},
	   {8,0,0},{7,0,0},{7,0,0},{7,0,0},{6,0,0}}},
{81,81,0, {{0,0,0},{8,'A','K'},{0,0,0},{0,0,0},{6,'A','K'},
	   {7,'A','K'},{6,0,0},{7,0,0},{4,'A','K'},{5,0,0},
	   {4,0,0},{5,0,0},{7,0,0},{8,0,0},{8,0,0},
	   {8,0,0},{7,0,0},{7,0,0},{7,0,0},{6,0,0}}},
{80,80,0, {{0,0,0},{8,'A','K'},{0,0,0},{0,0,0},{6,'A','K'},
	   {7,'A','K'},{6,0,0},{7,0,0},{4,'A','K'},{5,0,0},
	   {4,0,0},{4,0,0},{7,0,0},{8,0,0},{8,0,0},
	   {8,0,0},{7,0,0},{6,0,0},{6,0,0},{6,0,0}}},
{79,79,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{6,'A','K'},
	   {6,0,0},{6,0,0},{7,0,0},{4,'A','K'},{5,0,0},
	   {3,0,0},{4,0,0},{7,0,0},{8,0,0},{7,0,0},
	   {8,0,0},{6,0,0},{6,0,0},{6,0,0},{6,0,0}}},
{78,78,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{6,'A','K'},
	   {6,0,0},{6,0,0},{6,0,0},{4,'A','K'},{5,0,0},
	   {3,0,0},{4,0,0},{7,0,0},{8,0,0},{7,0,0},
	   {8,0,0},{6,0,0},{6,0,0},{6,0,0},{6,0,0}}},
{77,77,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{5,'A','K'},
	   {6,0,0},{6,0,0},{6,0,0},{3,'A','K'},{4,0,0},
	   {3,0,0},{4,0,0},{7,0,0},{7,0,0},{7,0,0},
	   {8,0,0},{6,0,0},{6,0,0},{6,0,0},{6,0,0}}},
{76,76,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{5,'A','K'},
	   {6,0,0},{6,0,0},{6,0,0},{3,'A','K'},{4,0,0},
	   {3,0,0},{4,0,0},{6,0,0},{7,0,0},{7,0,0},
	   {7,0,0},{6,0,0},{6,0,0},{6,0,0},{6,0,0}}},
{75,75,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{5,'A','K'},
	   {6,0,0},{6,0,0},{6,0,0},{3,'A','K'},{4,0,0},
	   {3,0,0},{4,0,0},{6,0,0},{7,0,0},{7,0,0},
	   {7,0,0},{6,0,0},{6,0,0},{6,0,0},{6,0,0}}},
{74,74,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{6,0,0},{3,0,0},{4,0,0},
	   {2,0,0},{4,0,0},{6,0,0},{7,0,0},{6,0,0},
	   {7,0,0},{6,0,0},{6,0,0},{6,0,0},{6,0,0}}},
{73,73,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{6,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{6,0,0},{7,0,0},{6,0,0},
	   {7,0,0},{5,0,0},{5,0,0},{6,0,0},{5,0,0}}},
{72,72,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{6,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{6,0,0},{6,0,0},{6,0,0},
	   {7,0,0},{5,0,0},{5,0,0},{5,0,0},{5,0,0}}},
{71,71,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{6,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{5,0,0},{6,0,0},{6,0,0},
	   {7,0,0},{5,0,0},{5,0,0},{5,0,0},{5,0,0}}},
{70,70,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{5,0,0},{6,0,0},{6,0,0},
	   {6,0,0},{5,0,0},{5,0,0},{5,0,0},{5,0,0}}},
{69,69,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{5,0,0},{5,0,0},{0,0,0},{3,0,0},
	   {0,0,0},{3,0,0},{5,0,0},{6,0,0},{6,0,0},
	   {6,0,0},{5,0,0},{5,0,0},{5,0,0},{5,0,0}}},
{68,68,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{5,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{3,0,0},{5,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{5,0,0},{5,0,0},{5,0,0},{5,0,0}}},
{67,67,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{5,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{3,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{4,0,0},{5,0,0},{5,0,0},{5,0,0}}},
{66,66,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{2,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{4,0,0},{4,0,0},{5,0,0},{5,0,0}}},
{65,65,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{2,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{4,0,0},{4,0,0},{5,0,0},{5,0,0}}},
{64,64,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{5,0,0},{5,0,0}}},
{63,63,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{4,0,0},{4,0,0},{5,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{4,0,0},{5,0,0}}},
{62,62,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{3,0,0},{4,0,0},{4,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{61,61,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{3,0,0},{4,0,0},{4,0,0},
	   {5,0,0},{3,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{60,60,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{3,0,0},{4,0,0},{4,0,0},
	   {5,0,0},{3,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{59,59,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{3,0,0},{4,0,0},{4,0,0},
	   {5,0,0},{3,0,0},{3,0,0},{4,0,0},{4,0,0}}},
{58,58,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{2,0,0},{3,0,0},{4,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{4,0,0},{4,0,0}}},
{57,57,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{2,0,0},{3,0,0},{4,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{4,0,0},{4,0,0}}},
{56,56,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{2,0,0},{3,0,0},{3,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{4,0,0},{4,0,0}}},
{55,55,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{2,0,0},{3,0,0},{3,0,0},
	   {4,0,0},{2,0,0},{3,0,0},{4,0,0},{4,0,0}}},
{54,54,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{2,0,0},{3,0,0},{3,0,0},
	   {4,0,0},{2,0,0},{3,0,0},{3,0,0},{4,0,0}}},
{53,53,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0},
	   {4,0,0},{2,0,0},{3,0,0},{3,0,0},{4,0,0}}},
{52,52,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{3,0,0},{4,0,0}}},
{51,51,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{50,50,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{2,0,0},{2,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{49,49,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{2,0,0},
	   {3,0,0},{1,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{48,48,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {3,0,0},{1,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{47,47,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {3,0,0},{1,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{46,46,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{2,0,0},{2,0,0},{3,0,0}}},
{45,45,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{2,0,0},{3,0,0}}},
{44,44,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0}}},
{43,43,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0}}},
{42,42,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0}}},
{41,41,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0}}},
{40,40,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{39,39,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{2,0,0},{2,0,0}}},
{38,38,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{2,0,0},{2,0,0}}},
{37,37,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{36,36,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{35,35,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{34,34,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{33,33,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{32,32,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{31,31,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{30,30,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{29,29,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{28,28,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{27,27,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{26,26,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{25,25,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{24,24,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{23,23,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{22,22,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{21,21,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{20,20,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{1,20,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}}};


main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_ma.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &attk[0].st, sizeof(attk));
  close(file);
}
