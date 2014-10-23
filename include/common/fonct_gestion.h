#ifndef _FONCT_GESTION_H_
#define _FONCT_GESTION_H_



/* ensemble de fonctions */ 
/* contient les fonctions utiles à exit, test, disp, set, assert, resume et debug */
#include "cmd_gestion.h"

/* fonction load */
#include "load.h"

/* fonction disasm */
#include "disasm.h"

/* fonction reg */
#include "../reg.h"
#include "interpreteur.h"

char* get_next_token(interpreteur inter);
int is_hexa(char* chaine);
int is_byte(char* chaine);
int is_word(char* chaine);
int is_integer(char* chaine);
int is_elf(char* chaine);
int is_register(char* chaine);
int get_type(char* chaine);
int execute_cmd(interpreteur inter, reg* tabreg, mem* vmem, FILE* fp);

int testcmd( interpreteur inter );
int exitcmd( interpreteur inter );
int loadcmd( interpreteur inter, mem* vmem );
int dispcmd( interpreteur inter, reg* tab_reg, mem vmem );
int disasmcmd( interpreteur inter, mem vmem, reg* tab_reg );
int setcmd( interpreteur inter, reg* tab_reg, mem vmem );
void debugcmd( interpreteur inter, FILE* fp );
void resumecmd( interpreteur inter, FILE* fp ); 
int assertcmd( interpreteur inter, reg* tab_reg, mem vmem );

#endif /* _FONCT_GESTION_ */
