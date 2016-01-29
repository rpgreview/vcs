#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

move_tab movemm[23] = {
{-151,-999, {0,0,0,0,0,0,0,0,0}},
{-150,-101, {10,0,0,0,0,0,0,0,0}},
{-100,-51, {30,10,0,0,0,0,0,0,0}},
{-50,-26, {50,30,10,0,0,0,0,0,0}},
{-25,0, {70,50,30,5,0,0,0,0,0}},
{1,20, {80,60,50,10,5,0,0,0,0}},
{21,40, {90,70,60,20,10,5,0,0,0}},
{41,55, {100,80,70,30,20,10,5,0,0}},
{56,65, {100,90,80,40,30,20,10,0,0}},
{66,75, {100,100,90,50,40,30,20,5,0}},
{76,85, {100,100,100,60,50,40,30,10,0}},
{86,95, {100,100,100,70,60,50,40,20,5}},
{96,105, {110,100,100,80,70,60,50,25,10}},
{106,115, {110,110,100,90,80,70,60,30,20}},
{116,125, {120,110,110,100,90,80,70,40,30}},
{126,135, {120,120,110,100,100,90,80,50,40}},
{136,145, {130,120,120,110,100,100,90,60,50}},
{146,155, {130,130,120,110,110,100,100,70,60}},
{156,165, {140,130,130,120,110,110,100,80,70}},
{166,185, {140,140,130,120,120,110,110,90,80}},
{186,225, {150,140,140,130,120,120,110,100,90}},
{226,275, {150,150,140,130,130,120,120,100,100}},
{276,350, {160,150,150,140,130,130,120,110,100}}    };


main()
{
int file, i,j,sz;
char *rdata;

  if ((file = open("tab_mm.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     printf("\nUnable to OPEN tab_mm.dat\n");
     exit(0);
  }
  write(file, &movemm[0].st, sizeof(movemm));
  close(file);

}
