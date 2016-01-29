//************************************************************************************

#define PDB 1
#include <errno.h>
#include "pDBlibrary.h"

//************************************************************************************
char pdbDataLine[PDBLINESIZE];
FILE *pdbFilePointer;
void *pdbDataPointer;
int pdbRowID;

//************************************************************************************
void pdbPutNewLine(FILE *file) {
	fprintf(file, "\n");
}

//************************************************************************************
void pdbPutString(FILE *file, char *string) {
char buf[PDBLINESIZE];
int i=0, j=0;

		// remove any PIPE characters
	while (string[i] != '\0') {
		if (string[i] != '|') { buf[j++] = string[i]; }
		i++;
	}
	buf[i] = '\0';
		// remove some trailing spaces ....
	if (buf[i-1] == ' ') { 
		buf[i-1] = '\0'; 
		if (buf[i-2] == ' ') { 
			buf[i-2] = '\0'; 
			if (buf[i-3] == ' ') { buf[i-3] = '\0'; }
		}
	}

	fprintf(file, "%s|", buf);
}

//************************************************************************************
void pdbPutInt(FILE *file, int data) {

	fprintf(file, "%d|", data);
}

//************************************************************************************
void pdbPutFloat(FILE *file, float data) {

	fprintf(file, "%.4f|", data);
}

//************************************************************************************
char *pdbTokenize(char *string) {
static char *lastToken = NULL;
char *tmp;

	if (string == NULL) {
		string = lastToken;
		if (string == NULL)
			return NULL;
	}

	tmp = strstr(string, "|");
	if (tmp) {
		*tmp = '\0';
		lastToken = tmp + 1;
	} else {
		lastToken = NULL;
		return "";
	}
	return string;
}

//************************************************************************************
char *pdbGetString() {
	return pdbTokenize(NULL);
}

//************************************************************************************
int pdbGetInt() {
int v=0;
char *rv;

	if ((rv = pdbTokenize(NULL)) != NULL) { v = atoi(rv); }
	return v;
}

//************************************************************************************
float pdbGetFloat() {
float v=0;
char *rv;

	if ((rv = pdbTokenize(NULL)) != NULL) { v = (float )atof(rv); }
	return v;
}

//************************************************************************************
void pdbGetNewLine() {
	fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);	// skip the newline
	fgets(pdbDataLine, PDBLINESIZE, pdbFilePointer);

	pdbTokenize(pdbDataLine);
}

//************************************************************************************
int pdbAddRecord(char *file, int (*fp)(), void *DP) {
FILE *ofile;
int filesize=0, rowid=1;
struct stat buf;
char mbuf[10] = "";

		// check to see if we need to create it first
	if ((ofile = fopen(file, "r")) == NULL) {
		if ((ofile = fopen(file, "w")) != NULL) {
			fprintf(ofile, "=000000\n");
			fclose(ofile);
		}
	} else {
		fclose(ofile);
	}

		// increment the rowid value and write it out
	if ((ofile = fopen(file, "r+")) != NULL) {
		fgets(mbuf, 10, ofile);
		fseek(ofile, 0L, SEEK_SET);
		rowid = atoi(&mbuf[1]) + 1;
		fprintf(ofile, "=%6.6d", rowid);
		fclose(ofile);
		pdbRowID = rowid;
	} else {
		fprintf(stderr, "Error: Unable to increment ROWID %s %d\n", file, errno);
	   return -1;
	}

		// append the record onto the end of the file
	if ((ofile = fopen(file, "a")) != NULL) {
		if (stat(file, &buf) == 0) {
			filesize = buf.st_size;
			if (filesize == 0) {
				fprintf(ofile, "=000001\n");	// write the rowid counter
			}
		}
		if (filesize > 0) { filesize++; }
		fprintf(ofile, "+%d|", rowid);
		pdbFilePointer = ofile;
		pdbDataPointer = DP;
		(*fp)();
		fprintf(ofile, "\n");
		fclose(ofile);
	} else {
		fprintf(stderr, "Error: Unable to add ROW %s %d\n", file, errno);
	   return -1;
	}

	return rowid;
}

//************************************************************************************
int pdbKeySearch(char *file, void (*fp)(), void *DP, int count, char *key1, char *key2, char *key3) {
char *cp1, *cp2, *cp3, buf[PDBLINESIZE], obuf[PDBLINESIZE];
FILE *ifile;
int flocation=8, ok=-1, len=0;
	
	pdbDataLine[0] = '\0';
	pdbDataPointer = DP;

	if ((ifile = fopen(file, "r")) != NULL) {
		pdbFilePointer = ifile;
		fgets(buf, PDBLINESIZE, ifile);
		while (fgets(buf, PDBLINESIZE, ifile) != NULL) {
			ok = -1;
			strcpy(obuf, buf);
			len = strlen(buf);
			cp1 = strtok(buf, "|");		// ignore the 1st field
			cp1 = strtok(NULL, "|");
			cp2 = strtok(NULL, "|");
			cp3 = strtok(NULL, "|");
			if (key1 != NULL && cp1 != NULL) {
				if (strcmp(key1, cp1) == 0) {
					ok = 1;
					if (key2 != NULL && cp2 != NULL) {
						if (strcmp(key2, cp2) == 0) {
							ok = 1;
							if (key3 != NULL && cp3 != NULL) {
								if (strcmp(key3, cp3) == 0) {
									ok = 1;
								} else {
									ok = -1;
								}
							}
						} else {
							ok = -1;
						}
					}
				}
				if (ok == 1) {
					strcpy(pdbDataLine, obuf);
					(*fp)();
					count--;
					if (count < 1) {
						fclose(ifile);
						return 0;
					}
				}
			}
			flocation += len;
		}
		fclose(ifile);
	} else {
		fprintf(stderr, "Error: Unable to open search file %s %d\n", file, errno);
	   return -1;
	}
	return 0;
}

//************************************************************************************
int pdbUpdateRecord(char *file, int (*fp)(), void *DP, char *key1, char *key2, char *key3) {
	if (pdbDeleteRecord(file, key1, key2, key3) == 0) {
		return pdbAddRecord(file, fp, DP);
	}
	return -1;
}

//************************************************************************************
int pdbDeleteRecord(char *file, char *key1, char *key2, char *key3) {
char *cp1, *cp2, *cp3, buf[PDBLINESIZE];
FILE *ifile;
int flocation=8, ok=-1, len=0;
	
	if ((ifile = fopen(file, "r+")) != NULL) {
		fgets(buf, PDBLINESIZE, ifile);
		while (fgets(buf, PDBLINESIZE, ifile) != NULL) {
			ok = -1;
			if ((len = strlen(buf)) == 0) {
				fclose(ifile);
				return 0;
			}
			cp1 = strtok(buf, "|");		// ignore the 1st field
			cp1 = strtok(NULL, "|");
			cp2 = strtok(NULL, "|");
			cp3 = strtok(NULL, "|");
			if (key1 != NULL && cp1 != NULL) {
				if (strcmp(key1, cp1) == 0) {
					ok = 1;
					if (key2 != NULL && cp2 != NULL) {
						if (strcmp(key2, cp2) == 0) {
							ok = 1;
							if (key3 != NULL && cp3 != NULL) {
								if (strcmp(key3, cp3) == 0) {
									ok = 1;
								} else {
									ok = -1;
								}
							}
						} else {
							ok = -1;
						}
					}
				}
				if (ok == 1) {
					if (fseek(ifile, flocation, SEEK_SET) == 0) {
						fprintf(ifile, "-");
					}
					fclose(ifile);
					return 0;
				}
			}
			flocation += len;
		}
		fclose(ifile);
	} else {
		if ((ifile = fopen(file, "a+")) != NULL) {
			fprintf(ifile, "=000000\n");
			fclose(ifile);
		}
		fprintf(stderr, "Error: Unable to open delete file %s %d\n", file, errno);
	   return -1;
	}
	return 0;
}

//************************************************************************************
int pdbDeleteAllRecord(char *file, char *key1, char *key2, char *key3) {
char *cp1, *cp2, *cp3, buf[PDBLINESIZE];
FILE *ifile;
int flocation=8, ok=-1, len=0;
	
	if ((ifile = fopen(file, "r+")) != NULL) {
		fgets(buf, PDBLINESIZE, ifile);
		while (fgets(buf, PDBLINESIZE, ifile) != NULL) {
			ok = -1;
			if ((len = strlen(buf)) == 0) {
				fclose(ifile);
				return 0;
			}
			cp1 = strtok(buf, "|");		// ignore the 1st field
			if ((cp1 = strtok(NULL, "|")) == NULL) {
				fclose(ifile);
				return 0;
			}
			cp2 = strtok(NULL, "|");
			cp3 = strtok(NULL, "|");
			if (key1 != NULL && cp1 != NULL) {
				if (strcmp(key1, cp1) == 0) {
					ok = 1;
					if (key2 != NULL && cp2 != NULL) {
						if (strcmp(key2, cp2) == 0) {
							ok = 1;
							if (key3 != NULL && cp3 != NULL) {
								if (strcmp(key3, cp3) == 0) {
									ok = 1;
								} else {
									ok = -1;
								}
							}
						} else {
							ok = -1;
						}
					}
				}
				if (ok == 1) {
					if (fseek(ifile, flocation, SEEK_SET) == 0) {
						fprintf(ifile, "-");
					} else {
						fclose(ifile);
						return -1;
					}
				}
			}
			flocation += len;
		}
		fclose(ifile);
	} else {
		fprintf(stderr, "Error: Unable to open delete file %s %d\n", file, errno);
		if ((ifile = fopen(file, "a+")) != NULL) {
			fprintf(ifile, "=000000\n");
			fclose(ifile);
		}
	   return -1;
	}
	return 0;
}

//************************************************************************************
int pdbCompactFile(char *file) {
char oname[PDBLINESIZE];
FILE *ifile, *ofile;

		// remove all the deleted records from the file
	sprintf(oname, "%s_", file);
	if (rename(file, oname) == 0) {
		if ((ofile = fopen(file, "w+")) != NULL) {
			if ((ifile = fopen(oname, "r")) != NULL) {
				while (fgets(oname, PDBLINESIZE, ifile) != NULL) {
					if (oname[0] == '+' || oname[0] == '=') {
						fputs(oname, ofile);
					}
				}
			} else {
				fclose(ofile);
			   return -1;
			}
			fclose(ofile);
			fclose(ifile);
		} else {
			fprintf(stderr, "Error: Unable to open cleaned file %s %d\n", file, errno);
		   return -1;
		}
	} else {
		fprintf(stderr, "Error: Unable to rename file %s %d\n", file, errno);
		return -1;
	}

	return 0;
}

//************************************************************************************
int pdbClearFile(char *file) {
FILE *tfile;

	if ((tfile = fopen(file, "w+")) != NULL) {
		fprintf(tfile, "=000000\n");
		fclose(tfile);
		return 0;
	}
	fprintf(stderr, "Error: Unable to open clear file %s %d\n", file, errno);
	return -1;
}

//************************************************************************************
int pdbGetRowID(char *file) {
FILE *ofile;
char mbuf[10];

	if ((ofile = fopen(file, "r")) != NULL) {
		fgets(mbuf, 10, ofile);
		fclose(ofile);
	} else {
		fprintf(stderr, "Error: Unable to open file %s %d\n", file, errno);
	   return -1;
	}
	return (atoi(&mbuf[1]) + 1);
}

//************************************************************************************
int pdbLoadAll(char *file, int (*fp)()) {
FILE *ifile;
	
	pdbDataLine[0] = '\0';

	if ((ifile = fopen(file, "r")) != NULL) {
		pdbFilePointer = ifile;
		fgets(pdbDataLine, PDBLINESIZE, ifile);
		while (fgets(pdbDataLine, PDBLINESIZE, ifile) != NULL) {
			(*fp)();
		}
		fclose(ifile);
	} else {
		fprintf(stderr, "Error: Unable to open file %s %d\n", file, errno);
	   return -1;
	}

	return 0;
}

//************************************************************************************
void pdbTruncate(char *file) {
FILE *ofile;

	if ((ofile = fopen(file, "w")) != NULL) {
		fprintf(ofile, "=000000\n");
		fclose(ofile);
	}
}
