#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

players party[39];

main()
{
int file, x=0, i,j ,sz;
char *rdata;


  memset(&party[0].name[0], '\0', sizeof(players)*39);

  strcpy(&party[x++].name[0], "Bandit - 3");
  strcpy(&party[x++].name[0], "Bandit - 5");
  strcpy(&party[x++].name[0], "Bandit Ldr - 6");
  strcpy(&party[x++].name[0], "Bandit Ldr - 8");
  strcpy(&party[x++].name[0], "Bear, Cave ");
  strcpy(&party[x++].name[0], "Cave Drake");
  strcpy(&party[x++].name[0], "Cave Worm");
  strcpy(&party[x++].name[0], "Fell Beast");
  strcpy(&party[x++].name[0], "Fighter - 6");
  strcpy(&party[x++].name[0], "Fighter - 8");
  strcpy(&party[x++].name[0], "Ghost, Gtr");
  strcpy(&party[x++].name[0], "Ghost, Lsr ");
  strcpy(&party[x++].name[0], "Ghoul");
  strcpy(&party[x++].name[0], "Giant, Lge");
  strcpy(&party[x++].name[0], "Giant, Lsr");
  strcpy(&party[x++].name[0], "Golem");
  strcpy(&party[x++].name[0], "Kraken, Med");
  strcpy(&party[x++].name[0], "Kraken, Lge");
  strcpy(&party[x++].name[0], "Mage - 6");
  strcpy(&party[x++].name[0], "Mage - 9");
  strcpy(&party[x++].name[0], "Orc - 3");
  strcpy(&party[x++].name[0], "Orc - 5");
  strcpy(&party[x++].name[0], "Orc - 7");
  strcpy(&party[x++].name[0], "Skeleton, Lord ");
  strcpy(&party[x++].name[0], "Skeleton, Gtr");
  strcpy(&party[x++].name[0], "Spider, Gtr");
  strcpy(&party[x++].name[0], "Troll, Cave");
  strcpy(&party[x++].name[0], "Troll, Forest");
  strcpy(&party[x++].name[0], "Troll, Hill");
  strcpy(&party[x++].name[0], "Troll, Stone");
  strcpy(&party[x++].name[0], "Urak Hai");
  strcpy(&party[x++].name[0], "Vampire");
  strcpy(&party[x++].name[0], "Warg - 5");
  strcpy(&party[x++].name[0], "Warg - 8");
  strcpy(&party[x++].name[0], "Werewolf");
  strcpy(&party[x++].name[0], "Wight, Lesser");
  strcpy(&party[x++].name[0], "Wight, Minor");
  strcpy(&party[x++].name[0], "Wight, Major");
  strcpy(&party[x++].name[0], "Wolf - 6");

  for (x=0; x<39; x++)
    party[x].max_hits = party[x].cur_hits = 66;


  if ((file = open("tab_xm.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     printf("\nUnable to OPEN tab_xm.dat\n");
     exit(0);
  }
  write(file, &party[0].name[0], sizeof(players)*39);
  close(file);

}
