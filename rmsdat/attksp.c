#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "ADMPmerp.h"

attk_tab2 attk[123] = {
{150,350,0, {{30,'E','P'},{28,'E','P'},{25,'E','P'},{22,'E','P'},{28,'E','P'},
	   {25,'E','P'},{20,'E','P'},{20,'E','P'},{26,'E','P'},{26,'E','P'},
	   {22,'E','P'},{20,'E','P'},{23,'E','P'},{23,'E','P'},{20,'E','P'},
	   {20,'E','P'},{14,'E','P'},{12,'E','P'},{10,'E','P'},{8,'D','P'}}},
{149,149,0, {{30,'E','P'},{28,'E','P'},{25,'E','P'},{22,'E','P'},{28,'E','P'},
	   {25,'E','P'},{20,'E','P'},{20,'E','P'},{26,'E','P'},{26,'E','P'},
	   {22,'E','P'},{20,'E','P'},{23,'E','P'},{23,'E','P'},{20,'E','P'},
	   {20,'E','P'},{14,'E','P'},{12,'E','P'},{10,'D','P'},{8,'C','P'}}},
{148,148,0, {{30,'E','P'},{28,'E','P'},{25,'E','P'},{22,'E','P'},{28,'E','P'},
	   {25,'E','P'},{20,'E','P'},{20,'E','P'},{26,'E','P'},{26,'E','P'},
	   {22,'E','P'},{20,'E','P'},{23,'E','P'},{23,'E','P'},{20,'E','P'},
	   {20,'E','P'},{14,'E','P'},{12,'D','P'},{10,'C','P'},{8,'C','P'}}},
{147,147,0, {{30,'E','P'},{28,'E','P'},{25,'E','P'},{22,'E','P'},{28,'E','P'},
	   {25,'E','P'},{20,'E','P'},{20,'E','P'},{26,'E','P'},{26,'E','P'},
	   {22,'E','P'},{20,'E','P'},{23,'E','P'},{23,'E','P'},{20,'D','P'},
	   {20,'D','P'},{14,'E','P'},{12,'D','P'},{10,'C','P'},{8,'C','P'}}},
{146,146,0, {{29,'E','P'},{27,'E','P'},{24,'E','P'},{21,'E','P'},{27,'E','P'},
	   {25,'E','P'},{20,'E','P'},{20,'E','P'},{25,'E','P'},{25,'E','P'},
	   {21,'E','P'},{20,'E','P'},{23,'E','P'},{23,'E','P'},{20,'D','P'},
	   {20,'D','P'},{14,'E','P'},{12,'D','P'},{10,'C','P'},{8,'C','P'}}},
{145,145,0, {{29,'E','P'},{27,'E','P'},{24,'E','P'},{21,'E','P'},{27,'E','P'},
	   {24,'E','P'},{20,'E','P'},{20,'E','P'},{25,'E','P'},{25,'E','P'},
	   {21,'E','P'},{19,'E','P'},{22,'E','P'},{22,'D','P'},{20,'D','P'},
	   {20,'D','P'},{14,'D','P'},{12,'C','P'},{10,'C','P'},{8,'C','P'}}},
{144,144,0, {{28,'E','P'},{27,'E','P'},{24,'E','P'},{21,'E','P'},{27,'E','P'},
	   {24,'E','P'},{19,'E','P'},{19,'E','P'},{25,'E','P'},{25,'E','P'},
	   {21,'E','P'},{19,'D','P'},{22,'E','P'},{22,'D','P'},{19,'D','P'},
	   {19,'D','P'},{14,'D','P'},{12,'C','P'},{10,'C','P'},{8,'B','P'}}},
{143,143,0, {{28,'E','P'},{27,'E','P'},{24,'E','P'},{21,'E','P'},{26,'E','P'},
	   {24,'E','P'},{19,'E','P'},{19,'E','P'},{24,'E','P'},{24,'E','P'},
	   {21,'E','P'},{19,'D','P'},{22,'E','P'},{22,'D','P'},{19,'D','P'},
	   {19,'D','P'},{13,'D','P'},{12,'C','P'},{10,'B','P'},{8,'B','P'}}},
{142,142,0, {{28,'E','P'},{26,'E','P'},{23,'E','P'},{20,'E','P'},{26,'E','P'},
	   {24,'E','P'},{19,'E','P'},{19,'E','P'},{24,'E','P'},{24,'E','P'},
	   {20,'D','P'},{19,'D','P'},{22,'D','P'},{22,'D','P'},{19,'D','P'},
	   {19,'D','P'},{13,'D','P'},{12,'C','P'},{10,'B','P'},{8,'B','P'}}},
{141,141,0, {{28,'E','P'},{26,'E','P'},{23,'E','P'},{20,'E','P'},{26,'E','P'},
	   {23,'E','P'},{19,'E','P'},{19,'D','P'},{24,'E','P'},{24,'D','P'},
	   {20,'D','P'},{19,'D','P'},{21,'D','P'},{21,'D','P'},{19,'D','P'},
	   {19,'C','P'},{13,'D','P'},{11,'C','P'},{10,'B','P'},{8,'B','P'}}},
{140,140,0, {{27,'E','P'},{26,'E','P'},{23,'E','P'},{20,'E','P'},{26,'E','P'},
	   {23,'E','P'},{19,'E','P'},{19,'D','P'},{23,'E','P'},{24,'D','P'},
	   {20,'D','P'},{18,'D','P'},{21,'D','P'},{21,'D','P'},{19,'C','P'},
	   {19,'C','P'},{13,'D','P'},{11,'C','P'},{10,'B','P'},{8,'B','P'}}},
{139,139,0, {{27,'E','P'},{26,'E','P'},{22,'E','P'},{20,'E','P'},{25,'E','P'},
	   {23,'E','P'},{19,'D','P'},{19,'D','P'},{23,'E','P'},{23,'D','P'},
	   {20,'D','P'},{18,'D','P'},{21,'D','P'},{21,'C','P'},{18,'C','P'},
	   {18,'C','P'},{13,'D','P'},{11,'C','P'},{10,'B','P'},{8,'B','P'}}},
{138,138,0, {{27,'E','P'},{25,'E','P'},{22,'E','P'},{19,'E','P'},{25,'E','P'},
	   {23,'E','P'},{18,'D','P'},{18,'D','P'},{23,'E','P'},{23,'D','P'},
	   {19,'D','P'},{18,'D','P'},{21,'D','P'},{21,'C','P'},{18,'C','P'},
	   {18,'C','P'},{13,'C','P'},{11,'B','P'},{9,'B','P'},{8,'A','P'}}},
{137,137,0, {{26,'E','P'},{25,'E','P'},{22,'E','P'},{19,'E','P'},{25,'E','P'},
	   {22,'D','P'},{18,'D','P'},{18,'D','P'},{22,'D','P'},{23,'D','P'},
	   {19,'D','P'},{18,'C','P'},{20,'D','P'},{20,'C','P'},{18,'C','P'},
	   {18,'C','P'},{13,'C','P'},{11,'B','P'},{9,'B','P'},{8,'A','P'}}},
{136,136,0, {{26,'E','P'},{25,'E','P'},{22,'E','P'},{19,'D','P'},{24,'E','P'},
	   {22,'D','P'},{18,'D','P'},{18,'D','P'},{22,'D','P'},{22,'D','P'},
	   {19,'D','P'},{18,'C','P'},{20,'D','P'},{20,'C','P'},{18,'C','P'},
	   {18,'C','P'},{12,'C','P'},{11,'B','P'},{9,'A','P'},{8,'A','P'}}},
{135,135,0, {{26,'E','P'},{25,'E','P'},{21,'E','P'},{19,'D','P'},{24,'D','P'},
	   {22,'D','P'},{18,'D','P'},{18,'D','P'},{22,'D','P'},{22,'D','P'},
	   {19,'D','P'},{17,'C','P'},{20,'D','P'},{20,'C','P'},{18,'C','P'},
	   {18,'C','P'},{12,'C','P'},{11,'B','P'},{9,'A','P'},{8,'A','P'}}},
{134,134,0, {{25,'E','P'},{24,'E','P'},{21,'E','P'},{18,'D','P'},{24,'D','P'},
	   {22,'D','P'},{18,'D','P'},{18,'D','P'},{22,'D','P'},{22,'D','P'},
	   {18,'D','P'},{17,'C','P'},{20,'D','P'},{20,'C','P'},{17,'C','P'},
	   {18,'C','P'},{12,'C','P'},{11,'B','P'},{9,'A','P'},{7,'A','P'}}},
{133,133,0, {{25,'E','P'},{24,'E','P'},{21,'D','P'},{18,'D','P'},{23,'D','P'},
	   {21,'D','P'},{17,'D','P'},{18,'D','P'},{21,'D','P'},{22,'D','P'},
	   {18,'C','P'},{17,'C','P'},{19,'D','P'},{20,'C','P'},{17,'C','P'},
	   {17,'C','P'},{12,'C','P'},{11,'B','P'},{9,'A','P'},{7,'A','P'}}},
{132,132,0, {{25,'E','P'},{24,'E','P'},{20,'D','P'},{18,'D','P'},{23,'D','P'},
	   {21,'D','P'},{17,'D','P'},{17,'C','P'},{21,'D','P'},{21,'D','P'},
	   {18,'C','P'},{17,'C','P'},{19,'D','P'},{19,'C','P'},{17,'C','P'},
	   {17,'B','P'},{12,'C','P'},{10,'B','P'},{9,'A','P'},{7,'A','P'}}},
{131,131,0, {{24,'E','P'},{24,'E','P'},{20,'D','P'},{17,'D','P'},{23,'D','P'},
	   {21,'D','P'},{17,'D','P'},{17,'C','P'},{21,'D','P'},{21,'D','P'},
	   {18,'C','P'},{17,'C','P'},{19,'C','P'},{19,'C','P'},{17,'C','P'},
	   {17,'B','P'},{12,'C','P'},{10,'B','P'},{9,'A','P'},{7,'A','S'}}},
{130,130,0, {{24,'E','P'},{23,'E','P'},{20,'D','P'},{17,'D','P'},{23,'D','P'},
	   {21,'D','P'},{17,'D','P'},{17,'C','P'},{20,'D','P'},{21,'D','P'},
	   {17,'C','P'},{16,'C','P'},{19,'C','P'},{19,'C','P'},{17,'B','P'},
	   {17,'B','P'},{12,'C','P'},{10,'B','P'},{9,'A','P'},{7,'A','P'}}},
{129,129,0, {{24,'E','P'},{23,'E','P'},{20,'D','P'},{17,'D','P'},{22,'D','P'},
	   {20,'D','P'},{17,'D','P'},{17,'C','P'},{20,'D','P'},{20,'C','P'},
	   {17,'C','P'},{16,'C','P'},{18,'C','P'},{19,'C','P'},{17,'B','P'},
	   {17,'B','P'},{11,'B','P'},{10,'A','P'},{9,'A','P'},{7,'A','K'}}},
{128,128,0, {{23,'E','P'},{23,'E','P'},{19,'D','P'},{17,'D','P'},{22,'D','P'},
	   {20,'D','P'},{17,'D','P'},{17,'C','P'},{20,'D','P'},{20,'C','P'},
	   {17,'C','P'},{16,'C','P'},{18,'C','P'},{18,'C','P'},{16,'B','P'},
	   {16,'B','P'},{11,'B','P'},{10,'A','P'},{9,'A','P'},{7,0,0}}},
{127,127,0, {{23,'D','P'},{23,'E','P'},{19,'D','P'},{16,'D','P'},{22,'D','P'},
	   {20,'D','P'},{16,'D','P'},{17,'C','P'},{19,'D','P'},{20,'C','P'},
	   {17,'C','P'},{16,'C','P'},{18,'C','P'},{18,'C','P'},{16,'B','P'},
	   {16,'B','P'},{11,'B','P'},{10,'A','P'},{8,'A','P'},{7,0,0}}},
{126,126,0, {{23,'D','P'},{22,'E','P'},{19,'D','P'},{16,'D','P'},{21,'D','P'},
	   {20,'D','P'},{16,'D','P'},{16,'C','P'},{19,'D','P'},{20,'C','P'},
	   {16,'C','P'},{15,'C','P'},{18,'C','P'},{18,'C','P'},{16,'B','P'},
	   {16,'B','P'},{11,'B','P'},{10,'A','P'},{8,'A','S'},{7,0,0}}},
{125,125,0, {{22,'D','P'},{22,'D','P'},{18,'D','P'},{16,'D','P'},{21,'D','P'},
	   {19,'D','P'},{16,'C','P'},{16,'C','P'},{19,'D','P'},{19,'C','P'},
	   {16,'C','P'},{15,'C','P'},{17,'C','P'},{18,'C','P'},{16,'B','P'},
	   {16,'B','P'},{11,'B','P'},{10,'A','P'},{8,'A','P'},{7,0,0}}},
{124,124,0, {{22,'D','P'},{22,'D','P'},{18,'D','P'},{16,'C','S'},{21,'D','P'},
	   {19,'D','P'},{16,'C','P'},{16,'C','P'},{18,'D','P'},{19,'C','P'},
	   {16,'C','P'},{15,'C','P'},{17,'C','P'},{17,'B','P'},{15,'B','P'},
	   {16,'B','P'},{11,'B','P'},{9,'A','P'},{8,'A','K'},{7,0,0}}},
{123,123,0, {{22,'D','P'},{21,'D','P'},{18,'D','P'},{15,'C','P'},{20,'D','P'},
	   {19,'C','P'},{16,'C','P'},{16,'C','P'},{18,'D','P'},{19,'C','P'},
	   {15,'C','P'},{15,'B','P'},{17,'C','P'},{17,'B','P'},{15,'B','P'},
	   {16,'B','P'},{11,'B','P'},{9,'A','P'},{8,0,0},{7,0,0}}},
{122,122,0, {{21,'D','P'},{21,'D','P'},{18,'D','S'},{15,'C','S'},{20,'D','P'},
	   {19,'C','P'},{15,'C','P'},{16,'C','P'},{18,'C','P'},{18,'C','P'},
	   {15,'C','P'},{15,'B','P'},{17,'C','P'},{17,'B','P'},{15,'B','P'},
	   {15,'A','P'},{10,'B','P'},{9,'A','P'},{8,0,0},{7,0,0}}},
{121,121,0, {{21,'D','P'},{21,'D','P'},{17,'D','P'},{15,'C','P'},{20,'D','P'},
	   {18,'C','P'},{15,'C','P'},{16,'C','P'},{18,'C','P'},{18,'C','P'},
	   {15,'C','P'},{14,'B','P'},{16,'C','P'},{17,'B','P'},{15,'B','P'},
	   {15,'A','P'},{10,'B','P'},{9,'A','P'},{8,0,0},{7,0,0}}},
{120,120,0, {{21,'D','P'},{21,'D','P'},{17,'C','S'},{15,'C','P'},{20,'D','P'},
	   {18,'C','P'},{15,'C','P'},{15,'C','P'},{17,'C','P'},{18,'C','P'},
	   {15,'C','P'},{14,'B','P'},{16,'C','P'},{17,'B','P'},{15,'B','P'},
	   {15,'A','P'},{10,'B','P'},{9,'A','P'},{8,0,0},{7,0,0}}},
{119,119,0, {{20,'D','S'},{20,'D','P'},{17,'C','P'},{14,'C','P'},{19,'C','P'},
	   {18,'C','P'},{15,'C','P'},{15,'C','P'},{17,'C','P'},{17,'C','P'},
	   {14,'C','P'},{14,'B','P'},{16,'C','P'},{16,'B','P'},{15,'B','P'},
	   {15,'A','P'},{10,'A','P'},{9,'A','P'},{8,0,0},{6,0,0}}},
{118,118,0, {{20,'D','P'},{20,'D','P'},{16,'C','S'},{14,'C','S'},{19,'C','P'},
	   {18,'C','P'},{15,'C','P'},{15,'C','P'},{17,'C','P'},{17,'C','P'},
	   {14,'B','P'},{14,'B','P'},{16,'C','P'},{16,'B','P'},{14,'A','P'},
	   {15,'A','P'},{10,'A','P'},{9,'A','P'},{8,0,0},{6,0,0}}},
{117,117,0, {{20,'D','S'},{20,'D','P'},{16,'C','P'},{14,'C','P'},{19,'C','P'},
	   {17,'C','P'},{15,'C','P'},{15,'B','P'},{16,'C','P'},{17,'C','P'},
	   {14,'B','P'},{14,'B','P'},{15,'B','P'},{16,'B','P'},{14,'A','P'},
	   {14,'A','P'},{10,'A','P'},{9,'A','P'},{8,0,0},{6,0,0}}},
{116,116,0, {{19,'D','P'},{20,'D','P'},{16,'C','S'},{14,'C','S'},{18,'C','P'},
	   {17,'C','P'},{14,'C','P'},{15,'B','P'},{16,'C','P'},{17,'C','P'},
	   {14,'B','P'},{13,'B','P'},{15,'B','P'},{16,'B','P'},{14,'A','P'},
	   {14,'A','P'},{10,'A','P'},{9,'A','S'},{7,0,0},{6,0,0}}},
{115,115,0, {{19,'D','S'},{19,'D','P'},{16,'C','P'},{13,'C','P'},{18,'C','P'},
	   {17,'C','P'},{14,'C','P'},{14,'B','P'},{16,'C','P'},{16,'C','P'},
	   {13,'B','P'},{13,'B','P'},{15,'B','P'},{15,'B','P'},{14,'A','P'},
	   {14,'A','S'},{9,'A','P'},{8,'A','P'},{7,0,0},{6,0,0}}},
{114,114,0, {{19,'D','P'},{19,'D','S'},{15,'C','S'},{13,'C','S'},{18,'C','P'},
	   {17,'C','P'},{14,'C','P'},{14,'B','S'},{15,'C','P'},{16,'C','P'},
	   {13,'B','P'},{13,'B','P'},{15,'B','P'},{15,'B','P'},{14,'A','P'},
	   {14,'A','P'},{9,'A','P'},{8,'A','K'},{7,0,0},{6,0,0}}},
{113,113,0, {{19,'D','S'},{19,'D','P'},{15,'C','P'},{13,'C','P'},{17,'C','P'},
	   {16,'C','P'},{14,'C','P'},{14,'B','P'},{15,'C','P'},{16,'C','P'},
	   {13,'B','P'},{13,'B','P'},{14,'B','P'},{15,'B','P'},{13,'A','P'},
	   {14,'A','S'},{9,'A','P'},{8,0,0},{7,0,0},{6,0,0}}},
{112,112,0, {{18,'D','P'},{19,'D','S'},{15,'C','S'},{12,'B','S'},{17,'C','P'},
	   {16,'C','P'},{14,'C','P'},{14,'B','S'},{15,'C','P'},{15,'C','P'},
	   {13,'B','P'},{13,'B','P'},{14,'B','P'},{15,'A','P'},{13,'A','P'},
	   {14,'A','P'},{9,'A','P'},{8,0,0},{7,0,0},{6,0,0}}},
{111,111,0, {{18,'C','S'},{18,'D','P'},{15,'C','P'},{12,'B','P'},{17,'C','P'},
	   {16,'C','P'},{13,'C','S'},{14,'B','P'},{14,'C','P'},{15,'B','P'},
	   {12,'B','P'},{12,'B','S'},{14,'B','P'},{14,'A','P'},{13,'A','P'},
	   {13,'A','S'},{9,'A','P'},{8,0,0},{7,0,0},{6,0,0}}},
{110,110,0, {{18,'C','P'},{18,'D','S'},{14,'B','S'},{12,'B','S'},{17,'C','P'},
	   {16,'C','P'},{13,'C','P'},{14,'B','S'},{14,'C','P'},{15,'B','P'},
	   {12,'B','P'},{12,'B','P'},{14,'B','P'},{14,'A','P'},{13,'A','S'},
	   {13,'A','P'},{9,'A','P'},{8,0,0},{7,0,0},{6,0,0}}},
{109,109,0, {{17,'C','S'},{18,'D','P'},{14,'B','P'},{12,'B','P'},{16,'C','P'},
	   {15,'B','P'},{13,'B','S'},{13,'B','P'},{14,'C','P'},{15,'B','P'},
	   {12,'B','P'},{12,'A','S'},{13,'B','P'},{14,'A','P'},{13,'A','P'},
	   {13,'A','S'},{9,'A','P'},{8,0,0},{7,0,0},{6,0,0}}},
{108,108,0, {{17,'C','P'},{18,'C','S'},{14,'B','S'},{11,'B','S'},{16,'C','P'},
	   {15,'B','S'},{13,'B','P'},{13,'B','S'},{14,'C','P'},{14,'B','P'},
	   {12,'B','S'},{12,'A','P'},{13,'B','P'},{14,'A','P'},{12,'A','S'},
	   {13,'A','P'},{8,'A','S'},{8,0,0},{7,0,0},{6,0,0}}},
{107,107,0, {{17,'C','S'},{17,'C','P'},{13,'B','P'},{11,'B','P'},{16,'B','P'},
	   {15,'B','P'},{13,'B','S'},{13,'B','P'},{13,'C','P'},{14,'B','P'},
	   {11,'B','P'},{12,'A','S'},{13,'B','P'},{14,'A','S'},{12,'A','P'},
	   {13,'A','K'},{8,'A','P'},{7,0,0},{7,0,0},{6,0,0}}},
{106,106,0, {{16,'C','P'},{17,'C','S'},{13,'B','S'},{11,'B','S'},{15,'B','P'},
	   {15,'B','P'},{13,'B','P'},{13,'B','S'},{13,'C','P'},{14,'B','P'},
	   {11,'B','S'},{11,'A','P'},{13,'B','P'},{13,'A','P'},{12,'A','S'},
	   {12,0,0},{8,'A','S'},{7,0,0},{7,0,0},{6,0,0}}},
{105,105,0, {{16,'C','S'},{17,'C','P'},{13,'B','P'},{11,'A','P'},{15,'B','S'},
	   {14,'B','P'},{12,'B','S'},{13,'B','P'},{13,'C','P'},{13,'B','P'},
	   {11,'B','P'},{11,'A','S'},{12,'B','P'},{13,'A','S'},{12,'A','P'},
	   {12,0,0},{8,'A','P'},{7,0,0},{7,0,0},{6,0,0}}},
{104,104,0, {{16,'C','P'},{17,'C','S'},{13,'B','S'},{10,'A','S'},{15,'B','P'},
	   {14,'B','S'},{12,'B','P'},{13,'B','S'},{12,'C','P'},{13,'B','P'},
	   {11,'B','S'},{11,'A','P'},{12,'B','P'},{13,'A','P'},{12,'A','S'},
	   {12,0,0},{8,'A','K'},{7,0,0},{6,0,0},{6,0,0}}},
{103,103,0, {{15,'C','S'},{16,'C','P'},{12,'B','P'},{10,'A','P'},{15,'B','S'},
	   {14,'B','P'},{12,'B','S'},{12,'A','P'},{12,'B','P'},{13,'B','S'},
	   {10,'A','P'},{11,'A','S'},{12,'A','P'},{13,'A','S'},{11,'A','P'},
	   {12,0,0},{8,0,0},{7,0,0},{6,0,0},{5,0,0}}},
{102,102,0, {{15,'B','P'},{16,'C','S'},{12,'A','S'},{10,'A','S'},{14,'B','P'},
	   {14,'B','S'},{12,'B','P'},{12,'A','S'},{12,'B','P'},{13,'B','P'},
	   {10,'A','S'},{10,'A','P'},{12,'A','P'},{12,'A','P'},{11,'A','K'},
	   {12,0,0},{8,0,0},{7,0,0},{6,0,0},{5,0,0}}},
{101,101,0, {{15,'B','S'},{16,'C','P'},{12,'A','P'},{10,'A','P'},{14,'B','S'},
	   {13,'B','P'},{12,'B','S'},{12,'A','P'},{11,'B','P'},{12,'B','S'},
	   {10,'A','P'},{10,'A','S'},{12,'A','P'},{12,'A','S'},{11,0,0},
	   {12,0,0},{7,0,0},{7,0,0},{6,0,0},{5,0,0}}},
{100,100,0, {{14,'B','P'},{16,'C','S'},{11,'A','S'},{9,'A','K'},{14,'B','P'},
	   {13,'B','S'},{11,'B','P'},{12,'A','S'},{11,'B','P'},{12,'B','P'},
	   {10,'A','S'},{10,'A','P'},{11,'A','P'},{12,'A','P'},{11,0,0},
	   {11,0,0},{7,0,0},{7,0,0},{6,0,0},{5,0,0}}},
{99,99,0, {{14,'B','S'},{15,'C','P'},{11,'A','P'},{9,'A','S'},{13,'B','P'},
	   {13,'B','P'},{11,'B','S'},{12,'A','P'},{11,'B','P'},{12,'B','S'},
	   {9,'A','P'},{10,'A','S'},{11,'A','S'},{12,'A','S'},{11,0,0},
	   {11,0,0},{7,0,0},{7,0,0},{6,0,0},{5,0,0}}},
{98,98,0, {{14,'B','P'},{15,'C','S'},{11,'A','S'},{9,0,0},{13,'B','P'},
	   {13,'B','P'},{11,'B','P'},{12,'A','S'},{10,'B','P'},{11,'B','P'},
	   {9,'A','S'},{10,'A','P'},{11,'A','P'},{11,'A','P'},{10,0,0},
	   {11,0,0},{7,0,0},{6,0,0},{6,0,0},{5,0,0}}},
{97,97,0, {{13,'B','S'},{15,'C','P'},{11,'A','P'},{9,0,0},{13,'B','S'},
	   {12,'B','P'},{11,'B','S'},{11,'A','P'},{10,'B','S'},{11,'B','S'},
	   {9,'A','P'},{9,'A','S'},{11,'A','S'},{11,'A','K'},{10,0,0},
	   {11,0,0},{7,0,0},{6,0,0},{6,0,0},{5,0,0}}},
{96,96,0, {{13,'B','P'},{14,'B','S'},{10,'A','S'},{8,0,0},{12,'B','P'},
	   {12,'B','S'},{11,'A','P'},{11,'A','S'},{10,'B','P'},{11,'A','P'},
	   {8,'A','S'},{9,'A','P'},{10,'A','P'},{11,0,0},{10,0,0},
	   {11,0,0},{7,0,0},{6,0,0},{6,0,0},{5,0,0}}},
{95,95,0, {{13,'A','S'},{14,'B','P'},{10,'A','P'},{8,0,0},{12,'B','S'},
	   {12,'B','P'},{11,'A','S'},{11,'A','P'},{10,'B','S'},{11,'A','S'},
	   {8,'A','P'},{9,'A','K'},{10,'A','S'},{11,0,0},{10,0,0},
	   {10,0,0},{7,0,0},{6,0,0},{6,0,0},{5,0,0}}},
{94,94,0, {{12,'A','P'},{14,'B','S'},{10,'A','K'},{8,0,0},{12,'B','P'},
	   {12,'A','S'},{10,'A','P'},{11,'A','S'},{9,'B','P'},{10,'A','P'},
	   {8,'A','S'},{9,0,0},{10,'A','P'},{10,0,0},{10,0,0},
	   {10,0,0},{6,0,0},{6,0,0},{6,0,0},{5,0,0}}},
{93,93,0, {{12,'A','S'},{14,'B','P'},{9,0,0},{7,0,0},{12,'B','S'},
	   {11,'A','P'},{10,'A','S'},{11,'A','P'},{9,'B','S'},{10,'A','S'},
	   {8,'A','P'},{9,0,0},{10,'A','S'},{10,0,0},{10,0,0},
	   {10,0,0},{6,0,0},{6,0,0},{5,0,0},{5,0,0}}},
{92,92,0, {{12,'A','P'},{13,'B','S'},{9,0,0},{7,0,0},{11,'B','P'},
	   {11,'A','S'},{10,'A','P'},{11,'A','S'},{9,'B','P'},{10,'A','P'},
	   {7,'A','S'},{8,0,0},{9,'A','P'},{10,0,0},{9,0,0},
	   {10,0,0},{6,0,0},{6,0,0},{5,0,0},{5,0,0}}},
{91,91,0, {{11,'A','S'},{13,'B','P'},{9,0,0},{7,0,0},{11,'A','S'},
	   {11,'A','P'},{10,'A','S'},{10,'A','S'},{8,'B','S'},{9,'A','S'},
	   {7,'A','P'},{8,0,0},{9,'A','S'},{10,0,0},{9,0,0},
	   {10,0,0},{6,0,0},{6,0,0},{5,0,0},{5,0,0}}},
{90,90,0, {{11,'A','P'},{13,'B','S'},{9,0,0},{7,0,0},{11,'A','P'},
	   {11,'A','S'},{10,'A','P'},{10,0,0},{8,'B','P'},{9,'A','P'},
	   {7,'A','K'},{8,0,0},{9,'A','P'},{10,0,0},{9,0,0},
	   {9,0,0},{6,0,0},{6,0,0},{5,0,0},{5,0,0}}},
{89,89,0, {{11,'A','K'},{13,'B','P'},{8,0,0},{6,0,0},{10,'A','S'},
	   {10,'A','P'},{9,'A','S'},{10,0,0},{8,'B','S'},{9,'A','S'},
	   {7,0,0},{8,0,0},{9,'A','S'},{9,0,0},{9,0,0},
	   {9,0,0},{6,0,0},{5,0,0},{5,0,0},{5,0,0}}},
{88,88,0, {{10,0,0},{12,'B','S'},{8,0,0},{6,0,0},{10,'A','P'},
	   {10,'A','S'},{9,'A','P'},{10,0,0},{7,'B','P'},{8,'A','P'},
	   {6,0,0},{8,0,0},{8,'A','P'},{9,0,0},{9,0,0},
	   {9,0,0},{6,0,0},{5,0,0},{5,0,0},{4,0,0}}},
{87,87,0, {{10,0,0},{12,'B','P'},{8,0,0},{6,0,0},{10,'A','S'},
	   {10,'A','P'},{9,'A','S'},{10,0,0},{7,'B','S'},{8,'A','S'},
	   {6,0,0},{7,0,0},{8,'A','K'},{9,0,0},{8,0,0},
	   {9,0,0},{5,0,0},{5,0,0},{5,0,0},{4,0,0}}},
{86,86,0, {{10,0,0},{12,'A','S'},{7,0,0},{6,0,0},{9,'A','P'},
	   {10,'A','S'},{9,'A','P'},{10,0,0},{7,'A','P'},{8,'A','P'},
	   {6,0,0},{7,0,0},{8,0,0},{9,0,0},{8,0,0},
	   {9,0,0},{5,0,0},{5,0,0},{5,0,0},{4,0,0}}},
{85,85,0, {{9,0,0},{12,'A','P'},{7,0,0},{5,0,0},{9,'A','S'},
	   {9,'A','P'},{9,0,0},{9,0,0},{6,'A','S'},{8,'A','K'},
	   {6,0,0},{7,0,0},{8,0,0},{8,0,0},{8,0,0},
	   {9,0,0},{5,0,0},{5,0,0},{5,0,0},{4,0,0}}},
{84,84,0, {{9,0,0},{11,'A','S'},{7,0,0},{5,0,0},{9,'A','P'},
	   {9,'A','S'},{9,0,0},{9,0,0},{6,'A','P'},{7,0,0},
	   {5,0,0},{7,0,0},{7,0,0},{8,0,0},{8,0,0},
	   {8,0,0},{5,0,0},{5,0,0},{5,0,0},{4,0,0}}},
{83,83,0, {{9,0,0},{11,'A','P'},{7,0,0},{5,0,0},{9,'A','S'},
	   {9,'A','P'},{8,0,0},{9,0,0},{6,'A','P'},{7,0,0},
	   {5,0,0},{7,0,0},{7,0,0},{8,0,0},{8,0,0},
	   {8,0,0},{5,0,0},{5,0,0},{5,0,0},{4,0,0}}},
{82,82,0, {{8,0,0},{11,'A','S'},{6,0,0},{5,0,0},{8,'A','P'},
	   {9,'A','S'},{8,0,0},{9,0,0},{6,'A','P'},{7,0,0},
	   {5,0,0},{6,0,0},{7,0,0},{8,0,0},{7,0,0},
	   {8,0,0},{5,0,0},{5,0,0},{4,0,0},{4,0,0}}},
{81,81,0, {{8,0,0},{11,'A','P'},{6,0,0},{4,0,0},{8,'A','S'},
	   {8,'A','P'},{8,0,0},{9,0,0},{5,'A','S'},{6,0,0},
	   {5,0,0},{6,0,0},{7,0,0},{7,0,0},{7,0,0},
	   {8,0,0},{5,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{80,80,0, {{8,0,0},{10,'A','K'},{6,0,0},{4,0,0},{8,'A','P'},
	   {8,0,0},{8,0,0},{8,0,0},{5,'A','P'},{6,0,0},
	   {4,0,0},{6,0,0},{6,0,0},{7,0,0},{7,0,0},
	   {8,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{79,79,0, {{0,0,0},{10,'A','K'},{0,0,0},{4,0,0},{7,'A','S'},
	   {8,0,0},{8,0,0},{8,0,0},{5,'A','S'},{6,0,0},
	   {4,0,0},{6,0,0},{6,0,0},{7,0,0},{7,0,0},
	   {7,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{78,78,0, {{0,0,0},{10,0,0},{0,0,0},{4,0,0},{7,'A','P'},
	   {8,0,0},{7,0,0},{8,0,0},{4,'A','P'},{6,0,0},
	   {4,0,0},{5,0,0},{6,0,0},{7,0,0},{7,0,0},
	   {7,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{77,77,0, {{0,0,0},{10,0,0},{0,0,0},{3,0,0},{7,'A','S'},
	   {7,0,0},{7,0,0},{8,0,0},{4,'A','S'},{5,0,0},
	   {4,0,0},{5,0,0},{6,0,0},{4,0,0},{6,0,0},
	   {7,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{76,76,0, {{0,0,0},{9,0,0},{0,0,0},{3,0,0},{6,'A','P'},
	   {7,0,0},{7,0,0},{8,0,0},{4,'A','P'},{5,0,0},
	   {3,0,0},{5,0,0},{5,0,0},{6,0,0},{6,0,0},
	   {7,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{75,75,0, {{0,0,0},{9,0,0},{0,0,0},{3,0,0},{6,0,0},
	   {7,0,0},{7,0,0},{8,0,0},{3,'A','K'},{5,0,0},
	   {3,0,0},{5,0,0},{5,0,0},{6,0,0},{6,0,0},
	   {7,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{74,74,0, {{0,0,0},{9,0,0},{0,0,0},{0,0,0},{6,0,0},
	   {7,0,0},{7,0,0},{7,0,0},{3,0,0},{4,0,0},
	   {3,0,0},{5,0,0},{5,0,0},{6,0,0},{6,0,0},
	   {7,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0}}},
{73,73,0, {{0,0,0},{9,0,0},{0,0,0},{0,0,0},{6,0,0},
	   {6,0,0},{7,0,0},{7,0,0},{3,0,0},{4,0,0},
	   {3,0,0},{4,0,0},{5,0,0},{6,0,0},{6,0,0},
	   {6,0,0},{3,0,0},{4,0,0},{4,0,0},{3,0,0}}},
{72,72,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{5,0,0},
	   {6,0,0},{6,0,0},{7,0,0},{2,0,0},{4,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{3,0,0},{3,0,0},{4,0,0},{3,0,0}}},
{71,71,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{5,0,0},
	   {6,0,0},{6,0,0},{7,0,0},{2,0,0},{4,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{3,0,0},{3,0,0},{4,0,0},{3,0,0}}},
{70,70,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{5,0,0},
	   {6,0,0},{6,0,0},{7,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0}}},
{69,69,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{6,0,0},{7,0,0},{0,0,0},{3,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{5,0,0},{5,0,0},
	   {6,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0}}},
{68,68,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{6,0,0},{6,0,0},{0,0,0},{3,0,0},
	   {0,0,0},{3,0,0},{3,0,0},{4,0,0},{5,0,0},
	   {5,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0}}},
{67,67,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{6,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{3,0,0},{3,0,0},{4,0,0},{5,0,0},
	   {5,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0}}},
{66,66,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {5,0,0},{5,0,0},{6,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{3,0,0},{3,0,0},{4,0,0},{4,0,0},
	   {5,0,0},{2,0,0},{3,0,0},{3,0,0},{3,0,0}}},
{65,65,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{5,0,0},{6,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{3,0,0},{3,0,0},{4,0,0},{4,0,0},
	   {5,0,0},{2,0,0},{3,0,0},{3,0,0},{3,0,0}}},
{64,64,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{5,0,0},{6,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{3,0,0},{2,0,0},{4,0,0},{4,0,0},
	   {5,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{63,63,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{5,0,0},{6,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{2,0,0},{3,0,0},{4,0,0},
	   {5,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{62,62,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{5,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{2,0,0},{3,0,0},{4,0,0},
	   {4,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{61,61,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0},
	   {4,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{60,60,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{1,0,0},{3,0,0},{3,0,0},
	   {4,0,0},{2,0,0},{2,0,0},{3,0,0},{3,0,0}}},
{59,59,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0},
	   {4,0,0},{1,0,0},{2,0,0},{2,0,0},{3,0,0}}},
{58,58,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0},
	   {4,0,0},{1,0,0},{2,0,0},{2,0,0},{3,0,0}}},
{57,57,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{1,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{56,56,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{2,0,0},{2,0,0},
	   {3,0,0},{1,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{55,55,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {3,0,0},{1,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{54,54,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {3,0,0},{1,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{53,53,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {3,0,0},{1,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{52,52,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {3,0,0},{0,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{51,51,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{50,50,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{49,49,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{48,48,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{1,0,0},{1,0,0},{2,0,0}}},
{47,47,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {2,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{46,46,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{45,45,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{44,44,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{43,43,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0}}},
{42,42,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{41,41,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{40,40,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{39,39,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{38,38,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{37,37,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{36,36,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{35,35,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{34,34,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{33,33,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{32,32,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{31,31,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{30,30,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{29,29,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{1,28,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}}};


main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_sp.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &attk[0].st, sizeof(attk));
  close(file);
}