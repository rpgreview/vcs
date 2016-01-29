#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ADMPmerp.h"

equip_tab equ[77] = {
{1, "arrows(20)", "4bp", "3", "wodden shaft and iron tips."},
{1, "backpack", "2bp", "2-3", "Leather/canvas Holds 20lb"},
{1, "bedroll(light)", "2bp", "4-7", "2 season"},
{1, "bedroll(heady)", "7bp", "8-11", "4 season"},
{1, "boots", "1sp", "3-4", "leather"},
{1, "brush(writing)", "5cp", "0.25", ""},
{1, "bucket", "4bp", "2-3", "3 gallons"},
{1, "caltrops(5)", "8bp", "2", "portable spiketrap"},
{1, "candle", "4cp", "0.25", ""},
{1, "case", "4sp", "1", ""},
{1, "cask", "24bp", "5", ""},
{1, "chain", "6bp", "8", "Iron 10'"},
{1, "chalk(10)", "2bp", "0.25", ""},
{1, "charcoal", "22cp", "1", ""},
{1, "chisel", "9bp", "1", ""},
{1, "cloak", "9bp", "2-3", ""},
{1, "climbing pick", "28bp", "2", ""},
{1, "coat", "15bp", "5-9", ""},
{1, "crossbow bolts(20)", "11bp", "3", ""},
{1, "fire-starting bow", "8tp", "0.5", "starts fire in 5min"},
{1, "flint and steel", "1bp", "0.5", "starts fire in 3min"},
{1, "framepack", "33cp", "3-4", "holds 45lb"},
{1, "gloves", "2bp", "0.5", ""},
{1, "grappling hook", "1sp", "1", "d"},
{1, "hammer", "1sp", "1", ""},
{1, "hammock", "1bp", "2-3", ""},
{1, "harnes", "1sp", "4", ""},
{1, "hat", "6bp", "1", ""},
{1, "hood", "16cp", "0.5", ""},
{1, "ink", "14cp", "0.25", ""},
{1, "ladder", "32cp", "15", ""},
{1, "lantern", "12bp", "1-2", ""},
{1, "lock pick kit", "1sp", "0.5", ""},
{1, "mirror", "35bp", "0.5", ""},
{1, "nails(20)", "9tp", "0.5", ""},
{1, "oar", "6cp", "4-5", ""},
{1, "oil flask", "3bp", "1", ""},
{1, "padded undercoat", "6bp", "2-4", ""},
{1, "paddle", "5cp", "3", ""},
{1, "padlock", "23bp", "1", ""},
{1, "pants", "25cp", "1-2", ""},
{1, "paper(10)", "12bp", "0.25", ""},
{1, "parchment(10)", "2sp", "0.25", ""},
{1, "pegs", "9tp", "2", ""},
{1, "pitons", "2bp", "2-3", ""},
{1, "plank", "6tp", "11-12", ""},
{1, "pole", "5cp", "5-10", ""},
{1, "pot(cooking)", "7bp", "2-3", ""},
{1, "quiver", "1bp", "0.5", "hold 20 arrows/bolts"},
{1, "rope", "4bp", "4-7", ""},
{1, "rope(superior)", "12bp", "2-4", ""},
{1, "sack(50lb)", "8cp", "2-3", ""},
{1, "saddle", "5sp", "10-12", ""},
{1, "saddle bag", "8bp", "4-6", ""},
{1, "saw", "23bp", "2-3", ""},
{1, "scabbard", "3sp", "1", ""},
{1, "shirt", "3bp", "1", ""},
{1, "spade", "16bp", "3-4", ""},
{1, "sundial", "3sp", "1", ""},
{1, "surcoat", "9bp", "1-2", ""},
{1, "tarp", "1bp", "3-5", ""},
{1, "tent", "2sp", "8-10", ""},
{1, "tinderbox", "2cp", "0.25", ""},
{1, "torch", "3tp", "1", ""},
{1, "vial", "2bp", "0.25", ""},
{1, "water skin", "1cp", "0.25", ""},
{1, "weapon bolt", "5bp", "1", ""},
{1, "wedge(slaying)", "1cp", "1", ""},
{1, "wedge(splitting)", "3cp", "3", "iron"},
{1, "wire(10gauge)", "9bp", "3", "iron 100'"},
{1, "whistle", "2sp", "0.5", "range 1+mi."}
};

main()
{
int file, i, j, sz;
char *rdata;


  if ((file = open("tab_xe.dat", O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)
  {
     printf("\nUnable to OPEN tab_xe.dat\n");
     exit(0);
  }
  write(file, &equ[0].type, sizeof(equ));
  close(file);

}
