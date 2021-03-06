#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "ADMPmerp.h"

attk_tab2 attk[32] = {
{100,100,1, {{33,'E','H'},{31,'E','H'},{29,'E','H'},{27,'E','H'},{31,'E','H'},
{30,'E','H'},{25,'E','H'},{25,'E','H'},{28,'E','H'},{27,'E','H'},
{22,'E','H'},{19,'E','H'},{24,'E','H'},{23,'E','H'},{19,'E','H'},
{19,'E','H'},{23,'E','H'},{22,'E','H'},{18,'E','H'},{15,'E','H'}}},
{99,99,1, {{31,'E','H'},{29,'E','H'},{27,'E','H'},{25,'E','H'},{29,'E','H'},
{28,'E','H'},{23,'E','H'},{23,'E','H'},{26,'E','H'},{25,'E','H'},
{20,'E','H'},{17,'D','H'},{22,'E','H'},{21,'D','H'},{17,'D','H'},
{17,'D','H'},{21,'E','H'},{20,'D','H'},{16,'D','H'},{13,'D','H'}}},
{98,98,1, {{31,'E','H'},{29,'E','H'},{27,'E','H'},{25,'E','H'},{29,'E','H'},
{28,'E','H'},{23,'E','H'},{23,'E','H'},{26,'E','H'},{25,'E','H'},
{20,'E','H'},{17,'D','H'},{22,'E','H'},{21,'D','H'},{17,'D','H'},
{17,'D','H'},{21,'E','H'},{20,'D','H'},{16,'D','H'},{13,'D','H'}}},
{97,97,1, {{29,'E','H'},{27,'E','H'},{25,'D','H'},{23,'D','H'},{27,'E','H'},
{26,'D','H'},{21,'D','H'},{21,'D','H'},{24,'E','H'},{23,'D','H'},
{18,'D','H'},{15,'D','H'},{20,'D','H'},{19,'D','H'},{15,'C','H'},
{15,'C','H'},{19,'D','H'},{18,'D','H'},{14,'D','H'},{11,'C','H'}}},
{96,96,1, {{29,'E','H'},{27,'E','H'},{25,'D','H'},{23,'D','H'},{27,'E','H'},
{26,'D','H'},{21,'D','H'},{21,'D','H'},{24,'E','H'},{23,'D','H'},
{18,'D','H'},{15,'D','H'},{20,'D','H'},{19,'D','H'},{15,'C','H'},
{15,'C','H'},{19,'D','H'},{18,'D','H'},{14,'D','H'},{11,'C','H'}}},
{93,95,0, {{28,'D','H'},{26,'D','H'},{24,'D','H'},{22,'C','H'},{26,'D','H'},
{25,'D','H'},{20,'D','H'},{20,'D','H'},{23,'D','H'},{22,'D','H'},
{17,'C','H'},{14,'C','H'},{19,'C','H'},{18,'C','H'},{14,'C','H'},
{14,'C','H'},{18,'C','H'},{17,'C','H'},{13,'C','H'},{10,'C','H'}}},
{89,92,0, {{27,'D','H'},{25,'D','H'},{22,'D','H'},{20,'C','H'},{25,'D','H'},
{23,'D','H'},{19,'D','H'},{18,'D','H'},{21,'D','H'},{20,'D','H'},
{16,'C','H'},{13,'C','H'},{19,'C','H'},{18,'C','H'},{14,'C','H'},
{14,'C','H'},{18,'C','H'},{17,'C','H'},{13,'C','H'},{10,'C','H'}}},
{85,88,0, {{26,'D','H'},{24,'D','H'},{20,'C','H'},{18,'C','H'},{24,'D','H'},
{21,'D','H'},{18,'D','H'},{17,'C','H'},{20,'D','H'},{19,'D','H'},
{15,'C','H'},{12,'C','H'},{18,'C','H'},{17,'C','H'},{14,'C','H'},
{13,'C','H'},{17,'C','H'},{16,'C','H'},{12,'C','H'},{9,'B','H'}}},
{81,84,0, {{25,'D','H'},{23,'D','H'},{18,'C','H'},{17,'C','H'},{23,'D','H'},
{19,'D','H'},{17,'C','H'},{16,'C','H'},{19,'D','H'},{18,'C','H'},
{14,'C','H'},{11,'C','H'},{18,'C','H'},{17,'C','H'},{13,'C','H'},
{13,'B','H'},{17,'C','H'},{16,'C','H'},{12,'C','H'},{9,'B','H'}}},
{77,80,0, {{24,'D','H'},{22,'D','H'},{17,'C','H'},{16,'C','H'},{22,'D','H'},
{17,'C','H'},{16,'C','H'},{15,'C','H'},{18,'C','H'},{17,'C','H'},
{13,'C','H'},{10,'C','H'},{17,'C','H'},{16,'C','H'},{13,'B','H'},
{12,'B','H'},{16,'C','H'},{15,'C','H'},{11,'B','H'},{8,'B','H'}}},
{73,76,0, {{23,'C','H'},{21,'C','H'},{16,'C','H'},{15,'C','H'},{21,'C','H'},
{16,'C','H'},{15,'C','H'},{14,'C','H'},{17,'C','H'},{16,'C','H'},
{12,'C','H'},{9,'B','H'},{16,'C','H'},{15,'C','H'},{12,'B','H'},
{12,'B','H'},{16,'C','H'},{15,'C','H'},{11,'B','H'},{8,'B','H'}}},
{69,72,0, {{22,'C','H'},{20,'C','H'},{15,'C','H'},{14,'C','H'},{20,'C','H'},
{15,'C','H'},{14,'C','H'},{13,'C','H'},{16,'C','H'},{15,'C','H'},
{11,'C','H'},{8,'B','H'},{15,'C','H'},{14,'C','H'},{12,'B','H'},
{11,'B','H'},{15,'C','H'},{14,'B','H'},{10,'B','H'},{7,'B','H'}}},
{65,68,0, {{21,'C','H'},{20,'C','H'},{14,'C','H'},{13,'B','H'},{19,'C','H'},
{14,'C','H'},{13,'C','H'},{12,'B','H'},{15,'C','H'},{14,'C','H'},
{10,'B','H'},{8,'B','H'},{14,'C','H'},{13,'B','H'},{11,'B','H'},
{11,'B','H'},{14,'B','H'},{13,'B','H'},{10,'B','H'},{7,'A','H'}}},
{61,64,0, {{20,'C','H'},{19,'C','H'},{13,'B','H'},{12,'B','H'},{18,'C','H'},
{13,'C','H'},{12,'B','H'},{11,'B','H'},{14,'C','H'},{13,'C','H'},
{9,'B','H'},{7,'B','H'},{13,'B','H'},{12,'B','H'},{11,'B','H'},
{10,'A','H'},{13,'B','H'},{12,'B','H'},{9,'B','H'},{6,'A','H'}}},
{57,60,0, {{19,'C','H'},{18,'C','H'},{12,'B','H'},{11,'B','H'},{17,'C','H'},
{12,'B','H'},{11,'B','H'},{10,'B','H'},{13,'C','H'},{12,'B','H'},
{8,'B','H'},{7,'B','H'},{12,'B','H'},{11,'B','H'},{10,'A','H'},
{9,'A','H'},{12,'B','H'},{11,'B','H'},{9,'A','H'},{6,'A','H'}}},
{53,56,0, {{18,'C','H'},{17,'C','H'},{11,'B','H'},{10,'B','H'},{16,'C','H'},
{11,'B','H'},{10,'B','H'},{9,'B','H'},{12,'B','H'},{11,'B','H'},
{7,'B','H'},{6,'A','H'},{11,'B','H'},{10,'B','H'},{9,'A','H'},
{8,'A','H'},{11,'B','H'},{10,'B','H'},{8,'A','H'},{5,'A','H'}}},
{49,52,0, {{17,'C','H'},{16,'B','H'},{10,'B','H'},{9,'B','H'},{15,'B','H'},
{10,'B','H'},{9,'B','H'},{8,'B','H'},{11,'B','H'},{10,'B','H'},
{6,'B','H'},{6,'A','H'},{10,'B','H'},{9,'B','H'},{8,'A','H'},
{7,'A','H'},{10,'B','H'},{9,'A','H'},{8,'A','H'},{5,'A','H'}}},
{45,48,0, {{16,'B','H'},{15,'B','H'},{9,'B','H'},{8,'A','H'},{14,'B','H'},
{9,'B','H'},{8,'B','H'},{7,'A','H'},{10,'B','H'},{9,'B','H'},
{5,'A','H'},{5,'A','H'},{9,'B','H'},{8,'B','H'},{7,'A','H'},
{6,'A','H'},{9,'B','H'},{8,'A','H'},{7,'A','H'},{4,'A','H'}}},
{41,44,0, {{15,'B','H'},{14,'B','H'},{8,'A','H'},{7,'A','H'},{13,'B','H'},
{8,'B','H'},{7,'A','H'},{6,'A','H'},{9,'B','H'},{8,'B','H'},
{4,'A','H'},{5,'A','H'},{8,'B','H'},{7,'A','H'},{6,'A','H'},
{5,'A','H'},{8,'A','H'},{7,'A','H'},{6,'A','H'},{4,'A','H'}}},
{37,40,0, {{14,'B','H'},{13,'B','H'},{7,'A','H'},{6,'A','H'},{12,'A','H'},
{7,'A','H'},{6,'A','H'},{5,'A','H'},{8,'B','H'},{7,'A','H'},
{4,'A','H'},{4,'A','H'},{7,'A','H'},{6,'A','H'},{5,'A','H'},
{4,'A','H'},{7,'A','H'},{6,'A','H'},{5,'A','H'},{3,0,0}}},
{33,36,0, {{13,'B','H'},{12,'A','H'},{6,'A','H'},{5,'A','H'},{11,'B','H'},
{6,'A','H'},{5,'A','H'},{4,'A','H'},{7,'A','H'},{6,'A','H'},
{3,'A','H'},{3,'A','H'},{6,'A','H'},{5,'A','H'},{4,'A','H'},
{3,'A','H'},{6,'A','H'},{5,'A','H'},{4,'A','H'},{3,0,0}}},
{29,32,0, {{12,'A','H'},{11,'A','H'},{5,'A','H'},{4,'A','H'},{9,'A','H'},
{5,'A','H'},{4,'A','H'},{3,'A','H'},{6,'A','H'},{5,'A','H'},
{3,'A','H'},{2,0,0},{5,'A','H'},{4,'A','H'},{3,0,0},
{2,0,0},{5,'A','H'},{4,'A','H'},{3,0,0},{2,0,0}}},
{25,28,0, {{11,'A','H'},{9,'A','H'},{4,'A','H'},{3,'A','H'},{7,'A','H'},
{4,'A','H'},{3,'A','H'},{2,0,0},{5,'A','H'},{4,'A','H'},
{2,0,0},{1,0,0},{4,'A','H'},{3,'A','H'},{2,0,0},
{1,0,0},{4,'A','H'},{3,'A','H'},{2,0,0},{1,0,0}}},
{21,24,0, {{9,'A','H'},{7,'A','H'},{3,'A','H'},{2,0,0},{6,'A','H'},
{3,'A','H'},{2,0,0},{1,0,0},{4,'A','H'},{3,'A','H'},
{1,0,0},{1,0,0},{3,'A','H'},{2,0,0},{1,0,0},
{0,0,0},{3,'A','H'},{2,0,0},{1,0,0},{0,0,0}}},
{17,20,0, {{7,'A','H'},{6,'A','H'},{2,0,0},{1,0,0},{4,'A','H'},
{2,0,0},{1,0,0},{0,0,0},{3,'A','H'},{2,0,0},
{1,0,0},{0,0,0},{2,0,0},{1,0,0},{0,0,0},
{0,0,0},{2,0,0},{1,0,0},{0,0,0},{0,0,0}}},
{13,16,0, {{5,'A','H'},{4,'A','H'},{1,0,0},{0,0,0},{2,0,0},
{1,0,0},{0,0,0},{0,0,0},{2,0,0},{1,0,0},
{0,0,0},{0,0,0},{1,0,0},{0,0,0},{0,0,0},
{0,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0}}},
{9,12,0, {{3,0,0},{2,0,0},{0,0,0},{0,0,0},{1,0,0},
{0,0,0},{0,0,0},{0,0,0},{1,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}},
{5,8,0, {{1,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}},
{4,04,1, {{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}}},
{3,03,1, {{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
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


  if ((file = open("tab_sfa.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     exit(0);
  }
  write(file, &attk[0].st, sizeof(attk));
  close(file);
}
