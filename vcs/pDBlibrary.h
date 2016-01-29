//************************************************************************************
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef VISUALC
#include <unistd.h>
#endif
#include <stdlib.h>

//************************************************************************************
#define PDBLINESIZE	10240

//************************************************************************************
#ifndef PDB
extern int pdbAddRecord(char *, int (*fp)(), void *);
extern int pdbKeySearch(char *, void (*fp)(), void *, int, char *, char *, char *);
extern int pdbUpdateRecord(char *, int (*fp)(), void *, char *, char *, char *);
extern int pdbDeleteRecord(char *, char *, char *, char *);
extern int pdbDeleteAllRecord(char *, char *, char *, char *);
extern int pdbCompactFile(char *);
extern int pdbClearFile(char *);
extern int pdbGetRowID(char *);
extern int pdbLoadAll(char *, int (*fp)());

extern void pdbPutString(FILE * , char *);
extern void pdbPutInt(FILE * , int);
extern void pdbPutFloat(FILE * , float);
extern void pdbPutNewLine(FILE *);

extern char * pdbTokenize(char *);

extern char *pdbGetString();
extern int pdbGetInt();
extern float pdbGetFloat();
extern void pdbGetNewLine();

extern char pdbDataLine[];
extern FILE *pdbFilePointer;
extern void *pdbDataPointer;
extern int pdbRowID;

extern void pdbTruncate(char *);

#else

int pdbAddRecord(char *, int (*fp)(), void *);
int pdbKeySearch(char *, void (*fp)(), void *, int, char *, char *, char *);
int pdbUpdateRecord(char *, int (*fp)(), void *, char *, char *, char *);
int pdbDeleteRecord(char *, char *, char *, char *);
int pdbDeleteAllRecord(char *, char *, char *, char *);
int pdbCompactFile(char *);
int pdbGetRowID(char *);

void pdbPutString(FILE * , char *);
void pdbPutInt(FILE * , int);
void pdbPutFloat(FILE * , float);
void pdbPutNewLine(FILE *);

char * pdbTokenize(char *);

char * pdbGetString();
int pdbGetInt();
float pdbGetFloat();
void pdbGetNewLine();
void pdbTruncate(char *);
#endif
