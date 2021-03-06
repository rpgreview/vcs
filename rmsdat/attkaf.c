#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "ADMPmerp.h"

attk_tab2 attk[101] = {
{150,350,0, {{10,'E','K'},{8,'E','K'},{7,'E','K'},{4,'E','K'},{9,'E','K'},
	   {7,'E','K'},{4,'E','K'},{4,'E','K'},{5,'E','K'},{5,'E','K'},
	   {2,'E','K'},{2,'E','K'},{5,'E','K'},{6,'D','K'},{2,'C','K'},
	   {2,'C','K'},{5,'E','K'},{5,'C','K'},{2,'A','K'},{2,'A','K'}}},
{149,149,0, {{10,'E','K'},{8,'E','K'},{7,'E','K'},{4,'E','K'},{9,'E','K'},
	   {7,'E','K'},{4,'E','K'},{4,'E','K'},{5,'E','K'},{5,'E','K'},
	   {2,'E','K'},{2,'D','K'},{5,'E','K'},{5,'C','K'},{2,'C','K'},
	   {2,'B','K'},{5,'D','K'},{5,'B','K'},{2,0,0},{2,0,0}}},
{148,148,0, {{10,'E','K'},{8,'E','K'},{7,'E','K'},{4,'E','K'},{9,'E','K'},
	   {7,'E','K'},{4,'E','K'},{4,'E','K'},{5,'E','K'},{5,'D','K'},
	   {2,'D','K'},{2,'C','K'},{5,'D','K'},{5,'C','K'},{2,'B','K'},
	   {2,'A','K'},{5,'C','K'},{5,'A','K'},{2,0,0},{2,0,0}}},
{147,147,0, {{10,'E','K'},{8,'E','K'},{7,'E','K'},{4,'E','K'},{9,'E','K'},
	   {7,'E','K'},{4,'E','K'},{4,'D','K'},{5,'E','K'},{5,'D','K'},
	   {2,'D','K'},{2,'C','K'},{5,'D','K'},{5,'C','K'},{2,'B','K'},
	   {2,'A','K'},{5,'C','K'},{5,'A','K'},{2,0,0},{2,0,0}}},
{146,146,0, {{10,'E','K'},{8,'E','K'},{7,'E','K'},{4,'D','K'},{9,'E','K'},
	   {7,'D','K'},{4,'D','K'},{4,'D','K'},{5,'D','K'},{5,'D','K'},
	   {2,'C','K'},{2,'C','K'},{5,'C','K'},{4,'C','K'},{2,'B','K'},
	   {2,'A','K'},{4,'C','K'},{5,'A','K'},{2,0,0},{2,0,0}}},
{145,145,0, {{10,'E','K'},{8,'E','K'},{7,'E','K'},{4,'D','K'},{9,'E','K'},
	   {7,'D','K'},{4,'D','K'},{4,'D','K'},{5,'D','K'},{5,'C','K'},
	   {2,'C','K'},{2,'C','K'},{5,'C','K'},{5,'B','K'},{2,'A','K'},
	   {2,'A','K'},{5,'B','K'},{5,'A','K'},{2,0,0},{2,0,0}}},
{144,144,0, {{10,'E','K'},{8,'E','K'},{7,'D','K'},{4,'D','K'},{9,'D','K'},
	   {7,'D','K'},{4,'D','K'},{4,'C','K'},{5,'D','K'},{5,'C','K'},
	   {2,'C','K'},{2,'C','K'},{5,'C','K'},{5,'B','K'},{2,'A','K'},
	   {2,0,0},{5,'B','K'},{5,0,0},{2,0,0},{2,0,0}}},
{143,143,0, {{10,'E','K'},{8,'E','K'},{7,'D','K'},{4,'D','K'},{9,'D','K'},
	   {7,'D','K'},{4,'D','K'},{4,'C','K'},{5,'D','K'},{5,'C','K'},
	   {2,'C','K'},{2,'B','K'},{5,'C','K'},{5,'B','K'},{2,'A','K'},
	   {2,0,0},{5,'B','K'},{5,0,0},{2,0,0},{2,0,0}}},
{142,142,0, {{9,'E','K'},{8,'E','K'},{7,'D','K'},{4,'C','K'},{9,'D','K'},
	   {7,'D','K'},{4,'D','K'},{4,'C','K'},{5,'D','K'},{5,'C','K'},
	   {2,'C','K'},{2,'B','K'},{5,'C','K'},{5,'B','K'},{2,'A','K'},
	   {2,0,0},{5,'B','K'},{5,0,0},{2,0,0},{2,0,0}}},
{141,141,0, {{9,'D','K'},{8,'E','K'},{7,'D','K'},{4,'C','K'},{8,'D','K'},
	   {7,'C','K'},{4,'C','K'},{4,'C','K'},{5,'C','K'},{5,'C','K'},
	   {2,'C','K'},{2,'B','K'},{5,'C','K'},{5,'A','K'},{2,'A','K'},
	   {2,0,0},{5,'A','K'},{5,0,0},{2,0,0},{2,0,0}}},
{140,140,0, {{9,'D','K'},{8,'E','K'},{7,'D','K'},{4,'C','K'},{8,'D','K'},
	   {7,'C','K'},{4,'C','K'},{4,'C','K'},{5,'C','K'},{5,'C','K'},
	   {2,'B','K'},{2,'B','K'},{5,'B','K'},{5,'A','K'},{2,'A','K'},
	   {2,0,0},{5,'A','K'},{5,0,0},{2,0,0},{2,0,0}}},
{139,139,0, {{9,'D','K'},{7,'D','K'},{6,'C','K'},{4,'C','K'},{8,'D','K'},
	   {7,'C','K'},{4,'C','K'},{4,'C','K'},{5,'C','K'},{5,'C','K'},
	   {2,'B','K'},{2,'B','K'},{5,'B','K'},{5,'A','K'},{2,0,0},
	   {2,0,0},{5,'A','K'},{5,0,0},{2,0,0},{2,0,0}}},
{138,138,0, {{9,'D','K'},{7,'D','K'},{6,'C','K'},{4,'C','K'},{8,'C','K'},
	   {6,'C','K'},{4,'C','K'},{4,'C','K'},{5,'C','K'},{5,'C','K'},
	   {2,'B','K'},{2,'A','K'},{5,'B','K'},{5,'A','K'},{2,0,0},
	   {2,0,0},{5,'A','K'},{5,0,0},{2,0,0},{2,0,0}}},
{137,137,0, {{9,'D','K'},{7,'D','K'},{6,'C','K'},{4,'C','K'},{8,'C','K'},
	   {6,'C','K'},{4,'C','K'},{4,'C','K'},{5,'C','K'},{5,'B','K'},
	   {2,'B','K'},{2,'A','K'},{5,'B','K'},{5,'A','K'},{2,0,0},
	   {2,0,0},{5,'A','K'},{5,0,0},{2,0,0},{2,0,0}}},
{136,136,0, {{9,'D','K'},{7,'D','K'},{6,'C','K'},{4,'C','K'},{8,'C','K'},
	   {6,'C','K'},{4,'C','K'},{4,'B','K'},{5,'C','K'},{5,'B','K'},
	   {2,'B','K'},{2,'A','K'},{5,'B','K'},{5,'A','K'},{2,0,0},
	   {2,0,0},{5,'A','K'},{5,0,0},{2,0,0},{2,0,0}}},
{135,135,0, {{8,'C','K'},{7,'D','K'},{6,'C','K'},{4,'B','K'},{8,'C','K'},
	   {6,'C','K'},{4,'C','K'},{4,'B','K'},{4,'C','K'},{5,'B','K'},
	   {2,'B','K'},{2,'A','K'},{5,'B','K'},{5,'A','K'},{2,0,0},
	   {2,0,0},{5,'A','K'},{5,0,0},{2,0,0},{2,0,0}}},
{134,134,0, {{8,'C','K'},{7,'D','K'},{6,'C','K'},{4,'B','K'},{8,'C','K'},
	   {6,'C','K'},{4,'C','K'},{4,'B','K'},{4,'C','K'},{4,'B','K'},
	   {2,'B','K'},{2,'A','K'},{4,'A','K'},{5,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{5,0,0},{2,0,0},{2,0,0}}},
{133,133,0, {{8,'C','K'},{7,'D','K'},{6,'C','K'},{4,'B','K'},{7,'C','K'},
	   {6,'C','K'},{4,'C','K'},{4,'B','K'},{4,'C','K'},{4,'B','K'},
	   {2,'A','K'},{2,'A','K'},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{132,132,0, {{8,'C','K'},{7,'C','K'},{6,'B','K'},{4,'B','K'},{7,'C','K'},
	   {6,'B','K'},{4,'B','K'},{4,'B','K'},{4,'C','K'},{4,'B','K'},
	   {2,'A','K'},{2,'A','K'},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{131,131,0, {{8,'C','K'},{7,'C','K'},{6,'B','K'},{3,'B','K'},{7,'C','K'},
	   {6,'B','K'},{4,'B','K'},{4,'B','K'},{4,'B','K'},{4,'B','K'},
	   {2,'A','K'},{2,'A','K'},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{130,130,0, {{8,'C','K'},{7,'C','K'},{6,'B','K'},{3,'B','K'},{7,'C','K'},
	   {6,'B','K'},{4,'B','K'},{4,'B','K'},{4,'B','K'},{4,'B','K'},
	   {2,'A','K'},{2,'A','K'},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{129,129,0, {{8,'C','K'},{6,'C','K'},{5,'B','K'},{3,'A','K'},{7,'B','K'},
	   {6,'B','K'},{4,'B','K'},{4,'B','K'},{4,'B','K'},{4,'A','K'},
	   {2,'A','K'},{2,0,0},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{128,128,0, {{7,'C','K'},{6,'C','K'},{5,'B','K'},{3,'A','K'},{7,'B','K'},
	   {6,'B','K'},{3,'B','K'},{4,'A','K'},{4,'B','K'},{4,'A','K'},
	   {2,'A','K'},{2,0,0},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{127,127,0, {{7,'B','K'},{6,'C','K'},{5,'B','K'},{3,'A','K'},{7,'B','K'},
	   {6,'B','K'},{3,'B','K'},{3,'A','K'},{4,'B','K'},{4,'A','K'},
	   {2,'A','K'},{2,0,0},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{126,126,0, {{7,'B','K'},{6,'C','K'},{5,'B','K'},{3,'A','K'},{7,'B','K'},
	   {5,'B','K'},{3,'B','K'},{3,'A','K'},{4,'B','K'},{4,'A','K'},
	   {2,'A','K'},{2,0,0},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{125,125,0, {{7,'B','K'},{6,'C','K'},{5,'A','K'},{3,'A','K'},{7,'B','K'},
	   {5,'B','K'},{3,'B','K'},{3,'A','K'},{4,'B','K'},{4,'A','K'},
	   {2,'A','K'},{2,0,0},{4,'A','K'},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{124,124,0, {{7,'B','K'},{6,'C','K'},{5,'A','K'},{3,'A','K'},{6,'B','K'},
	   {5,'B','K'},{3,'A','K'},{3,'A','K'},{4,'B','K'},{4,'A','K'},
	   {2,0,0},{2,0,0},{4,0,0},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{123,123,0, {{7,'B','K'},{6,'C','K'},{5,'A','K'},{3,'A','K'},{6,'B','K'},
	   {5,'B','K'},{3,'A','K'},{3,'A','K'},{4,'B','K'},{4,'A','K'},
	   {2,0,0},{2,0,0},{4,0,0},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{122,122,0, {{7,'B','K'},{6,'B','K'},{5,'A','K'},{3,'A','K'},{6,'B','K'},
	   {5,'A','K'},{3,'A','K'},{3,'A','K'},{4,'B','K'},{4,'A','K'},
	   {2,0,0},{2,0,0},{4,0,0},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{121,121,0, {{6,'B','K'},{6,'B','K'},{5,'A','K'},{3,'A','K'},{6,'B','K'},
	   {5,'A','K'},{3,'A','K'},{3,'A','K'},{3,'A','K'},{4,'A','K'},
	   {2,0,0},{2,0,0},{4,0,0},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{120,120,0, {{6,'B','K'},{6,'B','K'},{4,'A','K'},{3,'A','K'},{6,'B','K'},
	   {5,'A','K'},{3,'A','K'},{3,'A','K'},{3,'A','K'},{4,'A','K'},
	   {2,0,0},{2,0,0},{4,0,0},{4,0,0},{2,0,0},
	   {2,0,0},{4,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{119,119,0, {{6,'A','K'},{5,'B','K'},{4,'A','K'},{3,0,0},{6,'B','K'},
	   {5,'A','K'},{3,'A','K'},{3,0,0},{3,'A','K'},{3,0,0},
	   {2,0,0},{2,0,0},{3,0,0},{4,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{118,118,0, {{6,'A','K'},{5,'B','K'},{4,'A','K'},{3,0,0},{6,'A','K'},
	   {5,'A','K'},{3,'A','K'},{3,0,0},{3,'A','K'},{3,0,0},
	   {2,0,0},{2,0,0},{3,0,0},{4,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{4,0,0},{2,0,0},{2,0,0}}},
{117,117,0, {{6,'A','K'},{5,'B','K'},{4,'A','K'},{3,0,0},{6,'A','K'},
	   {5,'A','K'},{3,'A','K'},{3,0,0},{3,'A','K'},{3,0,0},
	   {2,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{116,116,0, {{6,'A','K'},{5,'B','K'},{4,'A','K'},{3,0,0},{5,'A','K'},
	   {5,'A','K'},{3,'A','K'},{3,0,0},{3,'A','K'},{3,0,0},
	   {2,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{115,115,0, {{6,'A','K'},{5,'B','K'},{4,'A','K'},{3,0,0},{5,'A','K'},
	   {4,'A','K'},{3,'A','K'},{3,0,0},{3,'A','K'},{3,0,0},
	   {2,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{114,114,0, {{5,'A','K'},{5,'B','K'},{4,0,0},{3,0,0},{5,'A','K'},
	   {4,'A','K'},{3,0,0},{3,0,0},{3,'A','K'},{3,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{113,113,0, {{5,'A','K'},{5,'B','K'},{4,0,0},{3,0,0},{5,'A','K'},
	   {4,'A','K'},{3,0,0},{3,0,0},{3,'A','K'},{3,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{112,112,0, {{5,'A','K'},{5,'A','K'},{4,0,0},{2,0,0},{5,'A','K'},
	   {4,'A','K'},{3,0,0},{3,0,0},{3,'A','K'},{3,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{111,111,0, {{5,'A','K'},{5,'A','K'},{4,0,0},{2,0,0},{5,'A','K'},
	   {4,'A','K'},{3,0,0},{3,0,0},{3,'A','K'},{3,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{110,110,0, {{5,'A','K'},{5,'A','K'},{4,0,0},{2,0,0},{5,'A','K'},
	   {4,'A','K'},{3,0,0},{3,0,0},{3,'A','K'},{3,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{109,109,0, {{5,0,0},{4,'A','K'},{3,0,0},{2,0,0},{5,'A','K'},
	   {4,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0},
	   {1,0,0},{1,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{108,108,0, {{5,0,0},{4,'A','K'},{3,0,0},{2,0,0},{5,'A','K'},
	   {4,0,0},{3,0,0},{3,0,0},{3,0,0},{3,0,0},
	   {1,0,0},{1,0,0},{3,0,0},{3,0,0},{2,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{107,107,0, {{4,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,'A','K'},
	   {4,0,0},{2,0,0},{3,0,0},{2,0,0},{3,0,0},
	   {1,0,0},{1,0,0},{3,0,0},{3,0,0},{1,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{106,106,0, {{4,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,'A','K'},
	   {4,0,0},{2,0,0},{3,0,0},{2,0,0},{3,0,0},
	   {1,0,0},{1,0,0},{3,0,0},{3,0,0},{1,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{105,105,0, {{4,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,'A','K'},
	   {4,0,0},{2,0,0},{3,0,0},{2,0,0},{3,0,0},
	   {1,0,0},{1,0,0},{3,0,0},{3,0,0},{1,0,0},
	   {2,0,0},{3,0,0},{3,0,0},{2,0,0},{2,0,0}}},
{104,104,0, {{4,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,0,0},
	   {4,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{3,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{1,0,0},{2,0,0}}},
{103,103,0, {{4,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{3,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{1,0,0},{2,0,0}}},
{102,102,0, {{4,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{3,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{1,0,0},{2,0,0}}},
{101,101,0, {{4,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{2,0,0}}},
{100,100,0, {{3,0,0},{4,'A','K'},{3,0,0},{2,0,0},{4,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{2,0,0}}},
{99,99,0, {{3,0,0},{3,0,0},{2,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{98,98,0, {{3,0,0},{3,0,0},{2,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{97,97,0, {{3,0,0},{3,0,0},{2,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{96,96,0, {{3,0,0},{3,0,0},{2,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{95,95,0, {{3,0,0},{3,0,0},{2,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{94,94,0, {{3,0,0},{3,0,0},{2,0,0},{2,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{2,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{93,93,0, {{2,0,0},{3,0,0},{2,0,0},{1,0,0},{3,0,0},
	   {3,0,0},{2,0,0},{2,0,0},{1,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{92,92,0, {{2,0,0},{3,0,0},{2,0,0},{1,0,0},{3,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{1,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{91,91,0, {{2,0,0},{3,0,0},{2,0,0},{1,0,0},{3,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{1,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{90,90,0, {{2,0,0},{3,0,0},{2,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{1,0,0},{2,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{89,89,0, {{2,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{88,88,0, {{2,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{87,87,0, {{2,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{86,86,0, {{1,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{2,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0}}},
{85,85,0, {{1,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{84,84,0, {{1,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{83,83,0, {{1,0,0},{2,0,0},{1,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{82,82,0, {{1,0,0},{2,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {2,0,0},{1,0,0},{2,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{81,81,0, {{1,0,0},{2,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {2,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{80,80,0, {{1,0,0},{2,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{79,79,0, {{0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{1,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{78,78,0, {{0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{1,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{77,77,0, {{0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{1,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{76,76,0, {{0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{1,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{75,75,0, {{0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{1,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{74,74,0, {{0,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{73,73,0, {{0,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{72,72,0, {{0,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{71,71,0, {{0,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{70,70,0, {{0,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{0,0,0},{1,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{1,0,0},{1,0,0}}},
{69,69,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{68,68,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{67,67,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{66,66,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{65,65,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{64,64,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{63,63,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{62,62,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{61,61,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{60,60,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{59,59,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{58,58,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{57,57,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{56,56,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{55,55,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{54,54,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{53,53,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{52,52,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{51,51,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{1,50,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}}};


main()
{
int file;
int i,j,sz;
char *rdata;

  if ((file = open("tab_af.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &attk[0].st, sizeof(attk));
  close(file);
}
