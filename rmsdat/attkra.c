#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "ADMPmerp.h"

attk_tab2 attk[130] = {
{150,350,0, {{22,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{20,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'E','P'},
	   {10,'E','P'},{8,'E','P'},{12,'E','P'},{12,'E','P'},{9,'E','P'},
	   {9,'E','P'},{9,'E','P'},{7,'E','P'},{5,'D','P'},{3,'C','P'}}},
{149,149,0, {{22,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{20,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'E','P'},
	   {10,'E','P'},{8,'E','P'},{12,'E','P'},{12,'E','P'},{9,'E','P'},
	   {9,'E','P'},{9,'E','P'},{7,'E','P'},{5,'C','P'},{3,'C','P'}}},
{148,148,0, {{22,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{20,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'E','P'},
	   {10,'E','P'},{8,'E','P'},{12,'E','P'},{12,'E','P'},{9,'E','P'},
	   {9,'E','P'},{9,'E','P'},{7,'D','P'},{5,'C','P'},{3,'C','P'}}},
{147,147,0, {{22,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{20,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'E','P'},
	   {10,'E','P'},{8,'E','P'},{12,'E','P'},{12,'E','P'},{9,'E','P'},
	   {9,'E','P'},{9,'E','P'},{7,'D','P'},{5,'C','P'},{3,'C','P'}}},
{146,146,0, {{22,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{20,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'E','P'},
	   {10,'E','P'},{8,'E','P'},{12,'E','P'},{12,'D','P'},{9,'D','P'},
	   {9,'D','P'},{9,'D','P'},{7,'D','P'},{5,'C','P'},{3,'C','P'}}},
{145,145,0, {{22,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{20,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'E','P'},
	   {10,'E','P'},{8,'D','P'},{12,'E','P'},{12,'D','P'},{9,'D','P'},
	   {9,'D','P'},{9,'D','P'},{7,'C','P'},{5,'C','P'},{3,'B','P'}}},
{144,144,0, {{22,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{19,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'E','P'},
	   {10,'E','P'},{8,'D','P'},{12,'E','P'},{12,'D','P'},{9,'D','P'},
	   {9,'D','P'},{9,'D','P'},{7,'C','P'},{5,'C','P'},{3,'B','P'}}},
{143,143,0, {{21,'E','P'},{20,'E','P'},{17,'E','P'},{14,'E','P'},{19,'E','P'},
	   {17,'E','P'},{12,'E','P'},{12,'E','P'},{14,'E','P'},{14,'D','P'},
	   {10,'D','P'},{8,'D','P'},{12,'E','P'},{12,'D','P'},{9,'D','P'},
	   {9,'D','P'},{9,'D','P'},{7,'C','P'},{5,'B','P'},{3,'B','P'}}},
{142,142,0, {{21,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{19,'E','P'},
	   {16,'E','P'},{12,'E','P'},{12,'E','P'},{13,'E','P'},{13,'D','P'},
	   {10,'D','P'},{8,'D','P'},{12,'D','P'},{12,'D','P'},{9,'D','P'},
	   {9,'D','P'},{9,'D','P'},{7,'C','P'},{5,'B','P'},{3,'B','P'}}},
{141,141,0, {{21,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{19,'E','P'},
	   {16,'E','P'},{12,'E','P'},{12,'E','P'},{13,'E','P'},{13,'D','P'},
	   {10,'D','P'},{8,'D','P'},{11,'D','P'},{11,'D','P'},{9,'D','P'},
	   {9,'D','P'},{9,'D','P'},{7,'C','P'},{5,'B','P'},{3,'B','P'}}},
{140,140,0, {{21,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{19,'E','P'},
	   {16,'E','P'},{12,'E','P'},{12,'E','P'},{13,'E','P'},{13,'D','P'},
	   {10,'D','P'},{8,'D','P'},{11,'D','P'},{11,'D','P'},{9,'D','P'},
	   {9,'D','P'},{9,'C','P'},{7,'C','P'},{5,'B','P'},{3,'B','P'}}},
{139,139,0, {{21,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{19,'E','P'},
	   {16,'E','P'},{12,'E','P'},{12,'E','P'},{13,'D','P'},{13,'D','P'},
	   {9,'D','P'},{8,'C','P'},{11,'D','P'},{11,'D','P'},{9,'D','P'},
	   {9,'C','P'},{9,'C','P'},{7,'C','P'},{5,'B','P'},{3,'A','P'}}},
{138,138,0, {{21,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{18,'E','P'},
	   {16,'E','P'},{12,'E','P'},{12,'D','P'},{13,'D','P'},{13,'D','P'},
	   {9,'D','P'},{8,'C','P'},{11,'D','P'},{11,'C','P'},{9,'C','P'},
	   {9,'C','P'},{8,'C','P'},{7,'C','P'},{5,'B','P'},{3,'A','P'}}},
{137,137,0, {{20,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{18,'E','P'},
	   {16,'E','P'},{11,'E','P'},{11,'D','P'},{13,'D','P'},{13,'D','P'},
	   {9,'D','P'},{8,'C','P'},{11,'D','P'},{11,'C','P'},{8,'C','P'},
	   {8,'C','P'},{8,'C','P'},{7,'B','P'},{5,'B','P'},{3,'A','P'}}},
{136,136,0, {{20,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{18,'E','P'},
	   {16,'E','P'},{11,'E','P'},{11,'D','P'},{13,'D','P'},{13,'D','P'},
	   {9,'D','P'},{8,'C','P'},{11,'D','P'},{11,'C','P'},{8,'C','P'},
	   {8,'C','P'},{8,'C','P'},{7,'B','P'},{5,'A','P'},{3,'A','P'}}},
{135,135,0, {{20,'E','P'},{19,'E','P'},{16,'E','P'},{13,'E','P'},{18,'E','P'},
	   {16,'E','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{13,'D','P'},
	   {9,'C','P'},{8,'C','P'},{11,'D','P'},{11,'C','P'},{8,'C','P'},
	   {8,'C','P'},{8,'C','P'},{7,'B','P'},{5,'A','P'},{3,'A','P'}}},
{134,134,0, {{20,'E','P'},{18,'E','P'},{15,'E','P'},{12,'E','P'},{18,'E','P'},
	   {15,'E','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{12,'D','P'},
	   {9,'C','P'},{7,'C','P'},{11,'D','P'},{11,'C','P'},{8,'C','P'},
	   {8,'C','P'},{8,'C','P'},{6,'B','P'},{5,'A','P'},{3,'A','S'}}},
{133,133,0, {{20,'E','P'},{18,'E','P'},{15,'E','P'},{12,'E','P'},{18,'E','P'},
	   {15,'D','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{12,'C','P'},
	   {9,'C','P'},{7,'C','P'},{10,'D','P'},{11,'C','P'},{8,'C','P'},
	   {8,'C','P'},{8,'C','P'},{6,'B','P'},{5,'A','P'},{3,'A','P'}}},
{132,132,0, {{20,'E','P'},{18,'E','P'},{15,'E','P'},{12,'E','P'},{17,'E','P'},
	   {15,'D','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{12,'C','P'},
	   {9,'C','P'},{7,'C','P'},{10,'D','P'},{10,'C','P'},{8,'C','P'},
	   {8,'C','P'},{8,'C','P'},{6,'B','P'},{5,'A','P'},{3,'A','S'}}},
{131,131,0, {{19,'E','P'},{18,'E','P'},{15,'E','P'},{12,'E','P'},{17,'E','P'},
	   {15,'D','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{12,'C','P'},
	   {9,'C','P'},{7,'C','P'},{10,'D','P'},{10,'C','P'},{8,'C','P'},
	   {8,'B','P'},{8,'B','P'},{6,'B','P'},{5,'A','P'},{3,'A','P'}}},
{130,130,0, {{20,'E','P'},{18,'E','P'},{15,'E','P'},{12,'E','P'},{17,'D','P'},
	   {15,'D','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{12,'C','P'},
	   {9,'C','P'},{7,'C','P'},{10,'C','P'},{10,'C','P'},{8,'C','P'},
	   {8,'B','P'},{8,'B','P'},{6,'B','P'},{5,'A','P'},{3,'A','K'}}},
{129,129,0, {{19,'E','P'},{18,'E','P'},{15,'E','P'},{12,'D','P'},{17,'D','P'},
	   {15,'D','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{12,'C','P'},
	   {9,'C','P'},{7,'C','P'},{10,'C','P'},{10,'C','P'},{8,'B','P'},
	   {8,'B','P'},{8,'B','P'},{6,'B','P'},{5,'A','S'},{3,0,0}}},
{128,128,0, {{19,'E','P'},{18,'E','P'},{15,'E','P'},{12,'D','P'},{17,'D','P'},
	   {15,'D','P'},{11,'D','P'},{11,'D','P'},{12,'D','P'},{12,'C','P'},
	   {8,'C','P'},{7,'C','P'},{10,'C','P'},{10,'C','P'},{8,'B','P'},
	   {8,'B','P'},{8,'B','P'},{6,'A','P'},{5,'A','P'},{3,0,0}}},
{127,127,0, {{19,'E','P'},{18,'E','P'},{14,'E','P'},{12,'D','P'},{17,'D','P'},
	   {14,'D','P'},{11,'D','P'},{11,'D','P'},{11,'D','P'},{12,'C','P'},
	   {8,'C','P'},{7,'C','P'},{10,'C','P'},{10,'C','P'},{8,'B','P'},
	   {8,'B','P'},{8,'B','P'},{6,'A','P'},{5,'A','S'},{3,0,0}}},
{126,126,0, {{19,'E','P'},{17,'E','P'},{14,'D','P'},{11,'D','P'},{16,'D','P'},
	   {14,'D','P'},{11,'D','P'},{11,'C','P'},{11,'C','P'},{11,'C','P'},
	   {8,'C','P'},{7,'B','P'},{10,'C','P'},{10,'C','P'},{8,'B','P'},
	   {8,'B','P'},{7,'B','P'},{6,'A','P'},{5,'A','P'},{3,0,0}}},
{125,125,0, {{18,'E','P'},{17,'E','P'},{14,'D','P'},{11,'D','P'},{16,'D','P'},
	   {14,'D','P'},{10,'D','P'},{11,'C','P'},{11,'C','P'},{11,'C','P'},
	   {8,'C','P'},{7,'B','P'},{10,'C','P'},{10,'B','P'},{7,'B','P'},
	   {8,'B','P'},{7,'B','P'},{6,'A','P'},{4,'A','K'},{3,0,0}}},
{124,124,0, {{18,'E','P'},{17,'E','P'},{14,'D','P'},{11,'D','P'},{16,'D','P'},
	   {14,'D','P'},{10,'D','P'},{10,'C','P'},{11,'C','P'},{11,'C','P'},
	   {8,'C','P'},{7,'B','P'},{9,'C','P'},{10,'B','P'},{7,'B','P'},
	   {7,'B','P'},{7,'B','P'},{6,'A','P'},{4,0,0},{3,0,0}}},
{123,123,0, {{18,'E','P'},{17,'E','P'},{14,'D','P'},{11,'D','P'},{16,'D','P'},
	   {14,'D','P'},{10,'D','P'},{10,'C','P'},{11,'C','P'},{11,'C','P'},
	   {8,'C','P'},{7,'C','P'},{9,'C','P'},{9,'B','P'},{8,'B','P'},
	   {7,'B','P'},{7,'B','P'},{6,'A','P'},{4,0,0},{3,0,0}}},
{122,122,0, {{18,'E','P'},{17,'E','P'},{14,'D','P'},{11,'D','P'},{16,'D','P'},
	   {14,'D','P'},{10,'D','P'},{10,'C','P'},{11,'C','P'},{11,'C','P'},
	   {8,'C','P'},{7,'B','P'},{9,'C','P'},{9,'B','P'},{7,'B','P'},
	   {8,'A','P'},{7,'B','P'},{6,'A','P'},{4,0,0},{3,0,0}}},
{121,121,0, {{18,'E','P'},{17,'E','P'},{14,'D','P'},{11,'D','P'},{16,'D','P'},
	   {14,'D','P'},{10,'D','P'},{10,'C','P'},{11,'C','P'},{11,'C','P'},
	   {8,'B','P'},{7,'B','P'},{9,'C','P'},{9,'B','P'},{7,'B','P'},
	   {7,'A','P'},{7,'A','P'},{6,'A','S'},{4,0,0},{3,0,0}}},
{120,120,0, {{18,'E','P'},{17,'E','P'},{14,'D','P'},{11,'D','P'},{15,'D','P'},
	   {14,'D','P'},{10,'D','P'},{10,'C','P'},{10,'C','P'},{11,'C','P'},
	   {8,'B','P'},{7,'B','P'},{9,'C','P'},{9,'B','P'},{7,'B','P'},
	   {7,'A','P'},{7,'A','P'},{6,'A','P'},{4,0,0},{3,0,0}}},
{119,119,0, {{17,'E','P'},{17,'E','P'},{13,'D','P'},{11,'D','P'},{15,'D','P'},
	   {13,'D','P'},{10,'D','P'},{10,'C','P'},{10,'C','P'},{11,'C','P'},
	   {8,'B','P'},{6,'B','P'},{9,'C','P'},{9,'B','P'},{7,'B','P'},
	   {7,'A','P'},{7,'A','P'},{6,'A','S'},{4,0,0},{3,0,0}}},
{118,118,0, {{17,'E','P'},{16,'E','P'},{13,'D','P'},{10,'D','P'},{15,'D','P'},
	   {13,'D','P'},{10,'D','P'},{10,'C','P'},{10,'C','P'},{10,'C','P'},
	   {7,'B','P'},{6,'B','P'},{9,'C','P'},{9,'B','P'},{7,'A','P'},
	   {7,'A','S'},{7,'A','P'},{5,'A','P'},{4,0,0},{3,0,0}}},
{117,117,0, {{17,'E','P'},{16,'E','P'},{13,'D','P'},{10,'D','P'},{15,'D','P'},
	   {13,'D','P'},{10,'D','P'},{10,'C','P'},{10,'C','P'},{10,'B','P'},
	   {7,'B','P'},{6,'B','P'},{9,'B','P'},{9,'B','P'},{7,'A','P'},
	   {7,'A','P'},{7,'A','P'},{5,'A','S'},{4,0,0},{3,0,0}}},
{116,116,0, {{17,'D','P'},{16,'D','P'},{13,'D','P'},{10,'D','P'},{15,'D','P'},
	   {13,'D','P'},{10,'C','P'},{10,'C','P'},{10,'C','P'},{10,'B','P'},
	   {7,'B','P'},{6,'B','P'},{8,'B','P'},{9,'B','P'},{7,'A','P'},
	   {7,'A','S'},{7,'A','P'},{5,'A','P'},{4,0,0},{3,0,0}}},
{115,115,0, {{17,'D','P'},{16,'D','P'},{13,'D','P'},{10,'D','P'},{15,'D','P'},
	   {13,'C','P'},{10,'C','P'},{10,'C','P'},{10,'C','P'},{10,'B','P'},
	   {7,'B','P'},{6,'B','P'},{8,'B','P'},{9,'B','P'},{7,'A','P'},
	   {7,'A','P'},{7,'A','P'},{5,'A','K'},{4,0,0},{3,0,0}}},
{114,114,0, {{17,'D','P'},{16,'D','P'},{13,'D','P'},{10,'D','P'},{14,'D','P'},
	   {13,'C','P'},{10,'C','P'},{10,'C','P'},{10,'C','P'},{10,'B','P'},
	   {7,'B','P'},{6,'B','P'},{8,'B','P'},{8,'A','P'},{7,'A','P'},
	   {7,'A','S'},{6,'A','P'},{5,0,0},{4,0,0},{3,0,0}}},
{113,113,0, {{16,'D','P'},{16,'D','P'},{13,'D','P'},{10,'D','P'},{14,'D','P'},
	   {13,'C','P'},{9,'C','P'},{10,'C','P'},{9,'C','P'},{10,'B','P'},
	   {7,'B','P'},{6,'B','S'},{8,'B','P'},{8,'A','P'},{6,'A','S'},
	   {7,'A','P'},{6,'A','S'},{5,0,0},{4,0,0},{3,0,0}}},
{112,112,0, {{16,'D','P'},{16,'D','P'},{12,'D','P'},{10,'D','P'},{14,'D','P'},
	   {12,'C','P'},{9,'C','P'},{10,'C','P'},{9,'C','P'},{10,'B','P'},
	   {7,'B','P'},{6,'A','P'},{8,'B','P'},{8,'A','P'},{6,'A','P'},
	   {7,'A','S'},{6,'A','P'},{5,0,0},{4,0,0},{3,0,0}}},
{111,111,0, {{16,'D','P'},{15,'D','P'},{12,'D','P'},{10,'D','S'},{14,'D','P'},
	   {12,'C','P'},{9,'C','P'},{9,'C','P'},{9,'C','P'},{7,'B','P'},
	   {7,'B','P'},{7,'A','S'},{8,'B','P'},{8,'A','P'},{6,'A','S'},
	   {6,'A','P'},{6,'A','S'},{5,0,0},{4,0,0},{3,0,0}}},
{110,110,0, {{16,'D','P'},{15,'D','P'},{12,'D','P'},{9,'C','P'},{14,'D','P'},
	   {12,'C','P'},{9,'C','P'},{9,'C','P'},{9,'C','P'},{9,'B','P'},
	   {7,'B','S'},{6,'A','P'},{8,'B','P'},{8,'A','S'},{6,'A','P'},
	   {6,'A','K'},{6,'A','P'},{5,0,0},{4,0,0},{3,0,0}}},
{109,109,0, {{16,'D','P'},{15,'D','P'},{12,'D','P'},{9,'C','S'},{14,'C','P'},
	   {12,'C','P'},{9,'C','P'},{9,'B','P'},{9,'B','P'},{9,'B','P'},
	   {7,'B','P'},{6,'A','S'},{8,'B','P'},{8,'A','P'},{6,'A','S'},
	   {6,0,0},{6,'A','S'},{5,0,0},{4,0,0},{3,0,0}}},
{108,108,0, {{16,'D','P'},{15,'D','P'},{12,'D','S'},{9,'C','P'},{13,'C','P'},
	   {12,'C','P'},{9,'C','P'},{9,'B','S'},{9,'B','P'},{9,'B','P'},
	   {7,'B','S'},{6,'A','P'},{8,'B','P'},{8,'A','S'},{6,'A','P'},
	   {6,0,0},{6,'A','P'},{5,0,0},{4,0,0},{3,0,0}}},
{107,107,0, {{15,'D','P'},{15,'D','P'},{12,'D','P'},{9,'C','S'},{13,'C','P'},
	   {12,'C','P'},{9,'C','P'},{9,'B','P'},{9,'B','P'},{9,'B','S'},
	   {6,'B','P'},{6,'A','S'},{7,'B','P'},{8,'A','P'},{6,'A','S'},
	   {6,0,0},{6,'A','S'},{5,0,0},{4,0,0},{3,0,0}}},
{106,106,0, {{15,'D','P'},{15,'D','P'},{12,'C','S'},{9,'C','P'},{13,'C','P'},
	   {12,'C','P'},{9,'C','P'},{9,'B','S'},{9,'B','P'},{9,'B','P'},
	   {6,'A','S'},{6,'A','P'},{7,'B','P'},{8,'A','S'},{6,'A','P'},
	   {6,0,0},{6,'A','P'},{5,0,0},{4,0,0},{2,0,0}}},
{105,105,0, {{15,'D','S'},{15,'D','P'},{12,'C','P'},{9,'C','S'},{13,'C','P'},
	   {12,'C','P'},{9,'C','S'},{9,'B','P'},{8,'B','P'},{9,'B','S'},
	   {6,'A','P'},{6,'A','S'},{7,'B','P'},{7,'A','P'},{6,'A','K'},
	   {6,0,0},{6,'A','K'},{5,0,0},{4,0,0},{2,0,0}}},
{104,104,0, {{15,'D','P'},{15,'D','P'},{11,'C','S'},{9,'C','P'},{13,'C','P'},
	   {11,'C','P'},{9,'C','P'},{9,'B','S'},{8,'B','P'},{9,'B','P'},
	   {6,'A','S'},{5,'A','P'},{7,'A','P'},{7,'A','S'},{6,0,0},
	   {6,0,0},{6,0,0},{5,0,0},{4,0,0},{2,0,0}}},
{103,103,0, {{15,'D','S'},{14,'D','P'},{11,'C','P'},{9,'C','S'},{13,'C','P'},
	   {11,'C','P'},{9,'C','S'},{9,'B','P'},{8,'B','P'},{8,'A','S'},
	   {6,'A','P'},{5,'A','S'},{7,'A','P'},{7,'A','P'},{6,0,0},
	   {6,0,0},{6,0,0},{5,0,0},{4,0,0},{2,0,0}}},
{102,102,0, {{15,'D','P'},{14,'D','P'},{11,'C','S'},{8,'C','P'},{12,'C','P'},
	   {11,'C','S'},{9,'C','P'},{9,'B','S'},{8,'B','P'},{8,'A','P'},
	   {6,'A','S'},{5,'A','P'},{7,'A','S'},{7,'A','S'},{6,0,0},
	   {6,0,0},{5,0,0},{4,0,0},{4,0,0},{2,0,0}}},
{101,101,0, {{14,'D','S'},{14,'D','P'},{11,'C','P'},{8,'C','S'},{12,'C','P'},
	   {11,'C','P'},{9,'C','S'},{9,'B','P'},{8,'B','P'},{8,'A','S'},
	   {6,'A','P'},{5,'A','S'},{7,'A','P'},{7,'A','P'},{6,0,0},
	   {6,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{100,100,0, {{14,'D','P'},{14,'D','P'},{11,'C','S'},{8,'C','P'},{12,'C','P'},
	   {11,'B','S'},{8,'C','P'},{9,'B','S'},{8,'B','P'},{8,'A','P'},
	   {6,'A','S'},{5,'A','P'},{7,'A','S'},{7,'A','K'},{5,0,0},
	   {6,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{99,99,0, {{14,'D','S'},{14,'D','S'},{11,'C','P'},{8,'C','S'},{12,'C','S'},
	   {11,'B','P'},{8,'C','S'},{9,'B','P'},{8,'B','S'},{8,'A','S'},
	   {6,'A','P'},{5,'A','K'},{6,'A','P'},{7,0,0},{5,0,0},
	   {6,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{98,98,0, {{14,'D','P'},{14,'D','P'},{11,'C','S'},{8,'C','P'},{12,'C','P'},
	   {11,'B','S'},{8,'C','P'},{8,'B','S'},{7,'B','P'},{8,'A','P'},
	   {6,'A','S'},{5,0,0},{6,'A','S'},{7,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{97,97,0, {{14,'D','S'},{14,'D','S'},{11,'C','P'},{8,'C','S'},{12,'B','S'},
	   {10,'B','P'},{8,'B','S'},{8,'B','P'},{7,'B','S'},{8,'A','S'},
	   {6,'A','P'},{5,0,0},{6,'A','P'},{6,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{96,96,0, {{14,'D','P'},{14,'D','P'},{10,'C','S'},{8,'B','P'},{11,'B','P'},
	   {10,'B','S'},{8,'B','P'},{8,'B','S'},{7,'B','P'},{8,'A','P'},
	   {5,'A','S'},{5,0,0},{6,'A','S'},{6,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{95,95,0, {{13,'D','S'},{13,'D','S'},{10,'B','P'},{8,'B','S'},{11,'B','S'},
	   {10,'B','P'},{8,'B','S'},{8,'B','P'},{7,'B','S'},{7,'A','S'},
	   {5,'A','P'},{5,0,0},{6,'A','P'},{6,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{94,94,0, {{13,'D','P'},{13,'D','P'},{10,'B','S'},{7,'B','P'},{11,'B','P'},
	   {10,'B','S'},{8,'B','P'},{8,'B','S'},{7,'B','P'},{7,'A','P'},
	   {5,'A','K'},{5,0,0},{6,'A','S'},{6,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{93,93,0, {{13,'C','S'},{13,'C','S'},{10,'B','P'},{7,'B','S'},{11,'B','S'},
	   {10,'B','P'},{8,'B','S'},{8,'A','P'},{7,'A','S'},{7,'A','S'},
	   {5,0,0},{5,0,0},{6,'A','P'},{6,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{92,92,0, {{13,'C','P'},{13,'C','P'},{10,'B','S'},{7,'B','P'},{11,'B','P'},
	   {10,'B','S'},{8,'B','P'},{8,'A','S'},{7,'A','P'},{7,'A','P'},
	   {5,0,0},{5,0,0},{6,'A','S'},{6,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{91,91,0, {{13,'C','S'},{13,'C','S'},{10,'B','P'},{7,'B','S'},{11,'B','S'},
	   {10,'B','P'},{8,'B','S'},{8,'A','P'},{7,'A','S'},{7,'A','S'},
	   {5,0,0},{5,0,0},{5,'A','P'},{6,0,0},{5,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{90,90,0, {{13,'C','P'},{13,'C','P'},{10,'B','S'},{7,'B','P'},{10,'B','P'},
	   {10,'B','S'},{8,'B','P'},{8,'A','S'},{6,'A','P'},{7,'A','P'},
	   {5,0,0},{5,0,0},{5,'A','K'},{6,0,0},{5,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{89,89,0, {{12,'C','S'},{13,'C','S'},{9,'B','P'},{7,'A','S'},{10,'B','S'},
	   {9,'B','P'},{8,'B','S'},{8,'A','P'},{6,'A','S'},{7,'A','K'},
	   {5,0,0},{4,0,0},{5,0,0},{6,0,0},{5,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{88,88,0, {{12,'C','P'},{13,'C','P'},{9,'B','S'},{7,'A','P'},{10,'B','P'},
	   {9,'B','S'},{7,'B','P'},{8,'A','S'},{6,'A','P'},{7,0,0},
	   {5,0,0},{4,0,0},{5,0,0},{5,0,0},{4,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{87,87,0, {{12,'C','S'},{12,'C','S'},{9,'B','P'},{7,'A','S'},{10,'B','S'},
	   {9,'B','P'},{7,'B','S'},{8,'A','P'},{6,'A','S'},{6,0,0},
	   {5,0,0},{4,0,0},{5,0,0},{5,0,0},{4,0,0},
	   {5,0,0},{4,0,0},{4,0,0},{3,0,0},{2,0,0}}},
{86,86,0, {{12,'C','P'},{12,'C','P'},{9,'A','S'},{6,'A','P'},{10,'B','P'},
	   {9,'B','S'},{7,'B','P'},{8,'A','S'},{6,'A','P'},{6,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{5,0,0},{4,0,0},
	   {5,0,0},{4,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{85,85,0, {{12,'C','S'},{12,'C','S'},{9,'A','P'},{6,'A','K'},{10,'B','S'},
	   {9,'B','P'},{7,'B','S'},{7,'A','P'},{6,'A','S'},{6,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{5,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{84,84,0, {{12,'B','P'},{12,'C','P'},{9,'A','S'},{6,0,0},{9,'B','P'},
	   {9,'B','S'},{7,'B','P'},{7,'A','S'},{6,'A','P'},{6,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{5,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{83,83,0, {{11,'B','S'},{12,'C','S'},{9,'A','P'},{6,0,0},{9,'B','S'},
	   {9,'A','P'},{7,'B','S'},{7,'A','P'},{5,'A','S'},{6,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{5,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{82,82,0, {{11,'B','P'},{12,'C','P'},{9,'A','S'},{6,0,0},{9,'B','P'},
	   {9,'A','S'},{7,'A','P'},{7,'A','S'},{5,'A','P'},{6,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{5,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{81,81,0, {{11,'B','S'},{12,'C','S'},{8,'A','P'},{6,0,0},{9,'B','S'},
	   {8,'A','P'},{7,'A','S'},{7,'A','P'},{5,'A','S'},{6,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{5,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{80,80,0, {{11,'B','P'},{11,'B','P'},{8,'A','K'},{6,0,0},{9,'A','P'},
	   {8,'A','S'},{7,'A','P'},{7,0,0},{5,'A','P'},{5,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{5,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{79,79,0, {{11,'B','S'},{11,'B','S'},{8,0,0},{6,0,0},{9,'A','S'},
	   {8,'A','P'},{7,'A','S'},{7,0,0},{5,'A','K'},{5,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{78,78,0, {{11,'A','P'},{11,'B','P'},{8,0,0},{5,0,0},{8,'A','P'},
	   {8,'A','S'},{7,'A','P'},{7,0,0},{5,0,0},{5,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{3,0,0},{2,0,0}}},
{77,77,0, {{10,'A','S'},{11,'B','S'},{8,0,0},{5,0,0},{8,'A','S'},
	   {8,'A','P'},{7,'A','S'},{7,0,0},{5,0,0},{5,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{4,0,0},{4,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{76,76,0, {{10,'A','P'},{11,'B','P'},{8,0,0},{5,0,0},{8,'A','P'},
	   {8,'A','S'},{6,'A','P'},{7,0,0},{4,0,0},{5,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{4,0,0},{3,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{75,75,0, {{10,'A','K'},{11,'B','S'},{8,0,0},{5,0,0},{8,'A','S'},
	   {8,'A','P'},{6,0,0},{7,0,0},{4,0,0},{5,0,0},
	   {3,0,0},{4,0,0},{4,0,0},{4,0,0},{3,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{74,74,0, {{10,0,0},{11,'B','P'},{7,0,0},{5,0,0},{8,'A','P'},
	   {7,'A','S'},{6,0,0},{7,0,0},{4,0,0},{5,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{4,0,0},{3,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{73,73,0, {{10,0,0},{11,'B','S'},{7,0,0},{5,0,0},{8,'A','S'},
	   {7,'A','P'},{6,0,0},{7,0,0},{4,0,0},{5,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{4,0,0},{3,0,0},
	   {4,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{72,72,0, {{10,0,0},{10,'B','P'},{7,0,0},{5,0,0},{7,'A','P'},
	   {7,'A','S'},{6,0,0},{6,0,0},{4,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{4,0,0},{3,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{71,71,0, {{9,0,0},{10,'A','S'},{7,0,0},{5,0,0},{7,'A','S'},
	   {7,'A','P'},{6,0,0},{6,0,0},{4,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{4,0,0},{3,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{70,70,0, {{9,0,0},{10,'A','P'},{7,0,0},{4,0,0},{7,'A','P'},
	   {7,0,0},{6,0,0},{6,0,0},{4,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0},
	   {3,0,0},{3,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{69,69,0, {{9,0,0},{10,'A','S'},{7,0,0},{4,0,0},{7,'A','S'},
	   {7,0,0},{6,0,0},{6,0,0},{4,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0},
	   {3,0,0},{3,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{68,68,0, {{9,0,0},{10,'A','P'},{7,0,0},{4,0,0},{7,'A','P'},
	   {7,0,0},{6,0,0},{6,0,0},{3,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0},
	   {3,0,0},{3,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{67,67,0, {{9,0,0},{10,'A','S'},{7,0,0},{4,0,0},{7,'A','S'},
	   {7,0,0},{6,0,0},{6,0,0},{3,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{66,66,0, {{9,0,0},{10,'A','P'},{6,0,0},{4,0,0},{6,'A','P'},
	   {6,0,0},{6,0,0},{6,0,0},{3,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{65,65,0, {{8,0,0},{10,'A','K'},{6,0,0},{4,0,0},{6,0,0},
	   {6,0,0},{6,0,0},{6,0,0},{3,0,0},{4,0,0},
	   {3,0,0},{3,0,0},{2,0,0},{3,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{64,64,0, {{8,0,0},{9,0,0},{6,0,0},{4,0,0},{6,0,0},
	   {6,0,0},{6,0,0},{6,0,0},{3,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{2,0,0},{3,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{63,63,0, {{8,0,0},{9,0,0},{6,0,0},{4,0,0},{6,0,0},
	   {6,0,0},{5,0,0},{6,0,0},{3,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{2,0,0},{3,0,0},{2,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0}}},
{62,62,0, {{8,0,0},{9,0,0},{6,0,0},{3,0,0},{6,0,0},
	   {6,0,0},{5,0,0},{6,0,0},{3,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{2,0,0},{3,0,0},{2,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{61,61,0, {{8,0,0},{9,0,0},{6,0,0},{3,0,0},{6,0,0},
	   {6,0,0},{5,0,0},{6,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{60,60,0, {{8,0,0},{9,0,0},{6,0,0},{3,0,0},{5,0,0},
	   {6,0,0},{5,0,0},{6,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{3,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{59,59,0, {{0,0,0},{9,0,0},{0,0,0},{3,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{58,58,0, {{0,0,0},{9,0,0},{0,0,0},{3,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{57,57,0, {{0,0,0},{9,0,0},{0,0,0},{3,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{2,0,0},{3,0,0},
	   {2,0,0},{2,0,0},{1,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{56,56,0, {{0,0,0},{8,0,0},{0,0,0},{3,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{1,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{55,55,0, {{0,0,0},{8,0,0},{0,0,0},{3,0,0},{5,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{1,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0}}},
{54,54,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{2,0,0},{1,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{2,0,0},{1,0,0}}},
{53,53,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{2,0,0},{1,0,0},{2,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{52,52,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {5,0,0},{5,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{51,51,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{2,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{50,50,0, {{0,0,0},{8,0,0},{0,0,0},{0,0,0},{4,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{0,0,0},{2,0,0},
	   {0,0,0},{2,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{49,49,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{48,48,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{47,47,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{4,0,0},{5,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{46,46,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{45,45,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {4,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{2,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{44,44,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{43,43,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{42,42,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{41,41,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{40,40,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{4,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{39,39,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{38,38,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{37,37,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{36,36,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{35,35,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{4,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{34,34,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{33,33,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{32,32,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{31,31,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{30,30,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
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
{1,21,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}}};


main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_ra.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &attk[0].st, sizeof(attk));
  close(file);
}
