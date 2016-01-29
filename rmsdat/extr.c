#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>
#include <ctype.h>

char dam[3], fn[20], x[20][6], il[120], tn[32][4];

int roll=190, fc[32];

FILE *ifl, *ofl;

main(argc, argv)
int argc;
char **argv;
{
int i,j,k, l, z=0;
char ar[3][4];

fc[z] = 103;strcpy(&tn[z++][0], "af");
fc[z] = 115;strcpy(&tn[z++][0], "ba");
fc[z] = 127;strcpy(&tn[z++][0], "bo");
fc[z] = 123;strcpy(&tn[z++][0], "bs");
fc[z] = 104;strcpy(&tn[z++][0], "cb");
fc[z] = 123;strcpy(&tn[z++][0], "cl");
fc[z] = 114;strcpy(&tn[z++][0], "da");
fc[z] = 102;strcpy(&tn[z++][0], "dt");
fc[z] = 123;strcpy(&tn[z++][0], "fa");
fc[z] = 123;strcpy(&tn[z++][0], "fl");
fc[z] = 132;strcpy(&tn[z++][0], "ha");
fc[z] = 111;strcpy(&tn[z++][0], "hc");
fc[z] = 110;strcpy(&tn[z++][0], "ja");
fc[z] = 100;strcpy(&tn[z++][0], "lb");
fc[z] = 105;strcpy(&tn[z++][0], "lc");
fc[z] = 134;strcpy(&tn[z++][0], "ma");
fc[z] = 117;strcpy(&tn[z++][0], "mg");
fc[z] = 93;strcpy(&tn[z++][0], "ml");
fc[z] = 133;strcpy(&tn[z++][0], "ms");
fc[z] = 112;strcpy(&tn[z++][0], "pl");
fc[z] = 135;strcpy(&tn[z++][0], "qs");
fc[z] = 132;strcpy(&tn[z++][0], "ra");
fc[z] = 98;strcpy(&tn[z++][0], "sb");
fc[z] = 123;strcpy(&tn[z++][0], "sc");
fc[z] = 100;strcpy(&tn[z++][0], "sl");
fc[z] = 125;strcpy(&tn[z++][0], "sp");
fc[z] = 123;strcpy(&tn[z++][0], "ss");
fc[z] = 113;strcpy(&tn[z++][0], "th");
fc[z] = 128;strcpy(&tn[z++][0], "wh");
fc[z] = 109;strcpy(&tn[z++][0], "wm");
fc[z] = 138;strcpy(&tn[z++][0], "wp");

	if (argc != 2)
	{
		puts("Not enougn arguements .... sorry");
		exit(0);
	}

	strcpy(fn, "attkXX.c");

	strncpy(&fn[4], argv[1], 2);

	printf("Now Writting file %s\n", fn);

	if ((ofl = fopen(fn, "w+")) == NULL)
	{
		puts("Can't open file for writting ... sorry");
		exit(0);
	}

	if ((ifl = fopen(argv[1], "r")) == NULL)
	{
		puts("Can't open file for reading ... sorry");
		exit(0);
	}
	strncpy(&fn[0], argv[1], 2);
	fn[2] = '\0';
fprintf(ofl, "#include <stdio.h>\n");
fprintf(ofl, "#include <stdlib.h>\n");
fprintf(ofl, "#include <fcntl.h>\n");
fprintf(ofl, "#include <string.h>\n");
fprintf(ofl, "\n");
fprintf(ofl, "typedef struct attk_tab2 {\n");
fprintf(ofl, "    int	st;		\n");
fprintf(ofl, "    int	ed;		\n");
fprintf(ofl, "    char um_flag;	\n");
fprintf(ofl, "    char res[20][3];\n");
fprintf(ofl, "} attk_tab2;\n");
fprintf(ofl, "\n");
for (z=0; z<32; z++)
  if (strcasecmp(&tn[z][0], &fn[0]) == 0)
	break;
fprintf(ofl, "attk_tab2 attk[%d] = {\n", fc[z]-2);

	fgets(&il[0], 120, ifl);
	fgets(&il[0], 120, ifl);

	memset(&x[0][0], '\0', sizeof(x));

	while(fgets(&il[0], 120, ifl) != 0L)
	{
           sscanf(il,"%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", 
	  &roll, &x[0][0],&x[1][0],&x[2][0],&x[3][0],&x[4][0],&x[5][0],&x[6][0],
	   &x[7][0],&x[8][0],&x[9][0],&x[10][0],&x[11][0],&x[12][0],&x[13][0],
	   &x[14][0],&x[15][0],&x[16][0],&x[17][0],&x[18][0],&x[19][0]);
	
	   if (roll < 150)
	   {
	      fprintf(ofl, "}},\n");
	      fprintf(ofl, "{%d,%d,0, {", roll, roll);
	   }
	   else
	      fprintf(ofl, "{%d,350,0, {", roll);

	   for (i=19;i>-1;i--)
	   {
		ar[0][0] = ar[1][0] = ar[2][0] = '\0';
		ar[0][1] = ar[1][1] = ar[2][1] = '\0';
		k = 3;
		l = strlen(&x[i][0])-1;
		for (j=l;j>-1;j--)
		{
		   if (x[i][j] >= 'A' && x[i][j] <= 'Z')
		   {
			k--;
			ar[k][0] = x[i][j];
		   }
		   else
		   {
			x[i][j+1] = '\0';
			strcpy(&ar[0][0], &x[i][0]);
			break;
		   }
		}
		if (k == 2)
		   fprintf(ofl, "{%s,'%s',0}", &ar[0][0], &ar[2][0]);
		else
		   fprintf(ofl, "{%s,'%s','%s'}", &ar[0][0], &ar[1][0], &ar[2][0]);
		if (i > 0)
		   fprintf(ofl, ",");
		if (i == 5 || i == 10 || i == 15)
		   fprintf(ofl, "\n\t   ");
	   }
	}
	fprintf(ofl, "}}};\n\n");

fprintf(ofl, "\n");
fprintf(ofl, "main()\n");
fprintf(ofl, "{\n");
fprintf(ofl, "int file;\n");
fprintf(ofl, "\n");
fprintf(ofl, "  if ((file = open(Xtab_%s.datX, O_CREAT | O_RDWR | O_TRUNC| O_BINARY)) == -1)\n", fn);
fprintf(ofl, "  {\n");
fprintf(ofl, "     exit(0);\n");
fprintf(ofl, "  }\n");
fprintf(ofl, "  write(file, &attk[0].st, sizeof(attk));\n");
fprintf(ofl, "  close(file);\n");
fprintf(ofl, "}\n");

	fclose(ifl);
	fclose(ofl);

	exit(0);
}
