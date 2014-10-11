#ifndef _FONCT_GESTION_H_
#define _FONCT_GESTION_H_



/* ensemble de fonctions */ 
/* contient les fonctions utiles à exit, test, disp, disasm et set */
#include "cmd_gestion.h"

/* fonction load */
//#include "../../src/load.c" 

/* fonction reg */
#include "../reg.h"
#include "interpreteur.h"

char* get_next_token(interpreteur inter);
int is_hexa(char* chaine);
/* autres fonctions is_ */
int get_type(char* chaine);
int execute_cmd(interpreteur inter, reg tabreg, mem vmem);

int testcmd( interpreteur inter );
int exitcmd( interpreteur inter );
int loadcmd( interpreteur inter );
int dispcmd( interpreteur inter, reg tab_reg, mem vmem );
int disasmcmd( interpreteur inter );
int setcmd( interpreteur inter, reg tabreg );
void debugcmd( interpreteur inter );
void resumecmd( interpreteur inter ); 
int assertcmd( interpreteur inter, reg tab, mem vmem );

#endif /* _FONCT_GESTION_ */
