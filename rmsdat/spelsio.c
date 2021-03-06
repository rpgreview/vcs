#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "ADMPmerp.h"

attk_tab2 attk[32] = {
{146,150,0, {{36,'E','I'},{34,'E','I'},{32,'E','I'},{30,'E','I'},{34,'E','I'},
	   {31,'E','I'},{28,'E','I'},{26,'E','I'},{22,'E','I'},{22,'E','I'},
	   {16,'E','I'},{12,'E','I'},{22,'E','I'},{22,'E','I'},{16,'E','I'},
	   {16,'E','I'},{18,'E','I'},{18,'E','I'},{14,'E','I'},{10,'E','I'}}},
{141,145,0, {{34,'E','I'},{32,'E','I'},{30,'E',0},{28,'E',0},{32,'E','I'},
	   {30,'E','I'},{26,'E','I'},{24,'E','I'},{21,'E','I'},{20,'E','I'},
	   {16,'E','I'},{12,'E','I'},{21,'E','I'},{20,'E','I'},{16,'E','I'},
	   {15,'E','I'},{18,'E','I'},{17,'E','I'},{14,'E','I'},{10,'D','I'}}},
{136,140,0, {{32,'E',0},{30,'E',0},{28,'E',0},{26,'E',0},{30,'E','I'},
	   {28,'E','I'},{24,'E','I'},{22,'E','I'},{20,'E','I'},{19,'E','I'},
	   {15,'E','I'},{11,'E','I'},{20,'E','I'},{18,'E','I'},{15,'D','I'},
	   {14,'D','I'},{17,'E','I'},{16,'E','I'},{13,'D','I'},{10,'D','I'}}},
{131,135,0, {{30,'E',0},{28,'E',0},{26,'E',0},{24,'E',0},{28,'E','I'},
	   {26,'E','I'},{22,'E','I'},{20,'E','I'},{19,'E','I'},{18,'E','I'},
	   {15,'E','I'},{11,'E','I'},{19,'E','I'},{17,'E','I'},{14,'D','I'},
	   {13,'D','I'},{17,'E','I'},{15,'D','I'},{13,'D','I'},{9,'C','I'}}},
{126,130,0, {{28,'E',0},{26,'E',0},{24,'E',0},{22,'E',0},{26,'E','I'},
	   {24,'E','I'},{20,'E','I'},{18,'E','I'},{18,'E','I'},{17,'E','I'},
	   {14,'E','I'},{10,'D','I'},{18,'E','I'},{16,'D','I'},{14,'D','I'},
	   {12,'D','I'},{16,'D','I'},{14,'D','I'},{12,'C','I'},{9,'C','I'}}},
{121,125,0, {{26,'E',0},{24,'E',0},{22,'E',0},{20,'E',0},{24,'E','I'},
	   {22,'E','I'},{18,'E','I'},{17,'E','I'},{17,'E','I'},{16,'E','I'},
	   {14,'D','I'},{10,'D','I'},{16,'D','I'},{15,'D','I'},{13,'C','I'},
	   {12,'C','I'},{16,'D','I'},{13,'C','I'},{12,'C','I'},{9,'C','I'}}},
{116,120,0, {{24,'E',0},{22,'E',0},{20,'E',0},{18,'E',0},{22,'E','I'},
	   {20,'E','I'},{16,'E','I'},{16,'E','I'},{16,'E','I'},{15,'D','I'},
	   {13,'D','I'},{9,'C','I'},{15,'D','I'},{14,'C','I'},{13,'C','I'},
	   {11,'C','I'},{15,'D','I'},{12,'C','I'},{11,'C','I'},{8,'C','I'}}},
{111,115,0, {{22,'E',0},{20,'E',0},{18,'E',0},{16,'D',0},{20,'E','I'},
	   {18,'E','I'},{14,'E','I'},{15,'D','I'},{15,'D','I'},{14,'D','I'},
	   {13,'D','I'},{9,'C','I'},{14,'D','I'},{13,'C','I'},{12,'C','I'},
	   {10,'C','I'},{14,'C','I'},{12,'C','I'},{10,'C','I'},{8,'B','I'}}},
{106,110,0, {{20,'E',0},{18,'E',0},{16,'E',0},{14,'D',0},{18,'E','I'},
	   {16,'D','I'},{13,'D','I'},{14,'D','I'},{14,'D','I'},{13,'D','I'},
	   {12,'C','I'},{8,'C','I'},{13,'C','I'},{12,'C','I'},{12,'C','I'},
	   {10,'C','I'},{14,'C','I'},{11,'C','I'},{10,'B','I'},{7,'B','I'}}},
{101,105,0, {{18,'D',0},{17,'E',0},{15,'D',0},{13,'D',0},{16,'D','I'},
	   {14,'D','I'},{12,'D','I'},{13,'D','I'},{13,'C','I'},{12,'C','I'},
	   {11,'C','I'},{8,'C','I'},{12,'C','I'},{11,'C','I'},{11,'B','I'},
	   {9,'B','I'},{13,'C','I'},{10,'B','I'},{9,'B','I'},{7,'B','I'}}},
{100,100,1, {{42,'E','I'},{40,'E','I'},{38,'E','I'},{36,'E','I'},{38,'E','I'},
	   {35,'E','I'},{32,'E','I'},{30,'E','I'},{26,'E','I'},{26,'E','I'},
	   {20,'E','I'},{16,'E','I'},{26,'E','I'},{26,'E','I'},{20,'E','I'},
	   {20,'E','I'},{22,'E','I'},{22,'E','I'},{18,'E','I'},{14,'E','I'}}},
{96,100,0, {{16,'D',0},{16,'D',0},{14,'D',0},{12,'C',0},{14,'D','I'},
	   {12,'D','I'},{11,'D','I'},{12,'C','I'},{12,'D','I'},{11,'C','I'},
	   {10,'C','I'},{7,'B','I'},{11,'C','I'},{10,'B','I'},{11,'B','I'},
	   {8,'B','I'},{12,'C','I'},{10,'B','I'},{9,'B','I'},{7,'B','I'}}},
{91,95,0, {{15,'D',0},{15,'D',0},{13,'D',0},{11,'C',0},{12,'D','I'},
	   {10,'C','I'},{10,'C','I'},{11,'C','I'},{11,'C','I'},{10,'C','I'},
	   {9,'B','I'},{7,'B','I'},{10,'B','I'},{9,'B','I'},{10,'A','I'},
	   {8,'A','I'},{11,'B','I'},{9,'B','I'},{8,'B','I'},{6,'A','I'}}},
{86,90,0, {{14,'D',0},{14,'D',0},{12,'C',0},{10,'B',0},{8,'C','I'},
	   {8,'C','I'},{9,'C','I'},{10,'C','I'},{10,'C','I'},{9,'B','I'},
	   {8,'B','I'},{6,'B','I'},{9,'B','I'},{8,'B','I'},{10,'A','I'},
	   {7,'A','I'},{10,'B','I'},{9,'A','I'},{8,'A','I'},{6,'A','I'}}},
{81,85,0, {{12,'C',0},{13,'D',0},{11,'C',0},{9,'B',0},{7,'C','I'},
	   {7,'C','I'},{8,'C','I'},{9,'B','I'},{9,'B','I'},{8,'B','I'},
	   {7,'A','I'},{6,'A','I'},{8,'A','I'},{7,'A','I'},{9,'A','I'},
	   {6,'A','I'},{9,'A','I'},{8,'A','I'},{7,'A','I'},{6,'A','I'}}},
{76,80,0, {{12,'C',0},{12,'C',0},{10,'B',0},{8,'A',0},{6,'B','I'},
	   {6,'B','I'},{7,'B','I'},{8,'B','I'},{8,'B','I'},{7,'A','I'},
	   {6,'A','I'},{5,'A','I'},{7,'A','I'},{6,'A','I'},{9,'A','I'},
	   {6,'A','I'},{8,'A','I'},{8,'A','I'},{7,'A','I'},{5,'A','I'}}},
{71,75,0, {{11,'B',0},{11,'C',0},{9,'B',0},{7,'A',0},{4,'B','I'},
	   {5,'B','I'},{6,'B','I'},{7,'A','I'},{7,'A','I'},{6,'A','I'},
	   {5,'A','I'},{4,'A','I'},{6,0,0},{5,'A','I'},{8,'A','I'},
	   {5,'A','I'},{7,'A','I'},{7,'A','I'},{6,'A','I'},{5,'A','I'}}},
{66,70,0, {{10,'A',0},{10,'B',0},{8,'A',0},{6,0,0},{3,'A','I'},
	   {4,'B','I'},{5,'A','I'},{6,'A','I'},{5,'A','I'},{5,0,0},
	   {4,0,0},{3,'A','I'},{5,0,0},{4,0,0},{7,'A','I'},
	   {4,'A','I'},{6,0,0},{7,'A','I'},{6,'A','I'},{5,'A','I'}}},
{61,65,0, {{0,0,0},{9,'B',0},{0,0,0},{0,0,0},{2,0,0},
	   {3,'A','I'},{4,'A','I'},{5,'A','I'},{3,0,0},{4,0,0},
	   {3,0,0},{2,0,0},{4,0,0},{3,0,0},{6,'A','I'},
	   {4,'A','I'},{5,0,0},{6,0,0},{5,'A','I'},{4,'A','I'}}},
{56,60,0, {{0,0,0},{8,'A',0},{0,0,0},{0,0,0},{0,0,0},
	   {2,0,0},{3,0,0},{4,'A','I'},{1,0,0},{2,0,0},
	   {2,0,0},{2,0,0},{3,0,0},{2,0,0},{5,0,0},
	   {3,0,0},{4,0,0},{5,0,0},{5,'A','I'},{4,'A','I'}}},
{51,55,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{2,0,0},{3,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{1,0,0},{2,0,0},{2,0,0},{4,0,0},
	   {2,0,0},{3,0,0},{4,0,0},{4,0,0},{3,'A','I'}}},
{46,50,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{2,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{1,0,0},{1,0,0},{1,0,0},{3,0,0},
	   {2,0,0},{2,0,0},{3,0,0},{4,0,0},{3,0,0}}},
{41,45,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{1,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{1,0,0},{2,0,0},
	   {2,0,0},{1,0,0},{2,0,0},{3,0,0},{2,0,0}}},
{36,40,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0},
	   {1,0,0},{0,0,0},{1,0,0},{2,0,0},{2,0,0}}},
{31,35,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {1,0,0},{0,0,0},{0,0,0},{1,0,0},{1,0,0}}},
{21,30,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{1,0,0}}},
{11,20,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
	   {0,0,0},{0,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}}},
{03,10,0, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}}},
{2,02,1, {{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}}},
{1,01,1, {{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
	   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}}}};


main()
{
int file;
int i,j,sz;
char *rdata;


  if ((file = open("tab_sio.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &attk[0].st, sizeof(attk));
  close(file);
}
