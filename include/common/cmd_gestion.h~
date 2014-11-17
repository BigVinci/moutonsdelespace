#ifndef _CMD_GESTION_H_
#define _CMD_GESTION_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* macros de DEBUG_MSG fournies , etc */
#include "notify.h"

/* les différents types utiles */
#include "types.h"
#include "../mem.h"
#include "../reg.h"
#include "../liste.h"

#include "interpreteur.h"
#include "disasm.h"


/*************************************************************\
Valeur de retour speciales lorsqu'on pour la fonction
	int parse_and_execute_cmd_string(char *input) ;
Toute autre valeur signifie qu'une erreur est survenue
 \*************************************************************/
#define CMD_OK_RETURN_VALUE 0
#define CMD_EXIT_RETURN_VALUE -1
#define CMD_UNKOWN_RETURN_VALUE -2

enum {NOT_S, RUN, PAUSE, TERM, OUT} STATE;

int _testcmd(int hexValue);

int _set_mem_bytecmd(uint8_t byteValue, uint32_t vaddr, mem vmem);
int _set_mem_wordcmd(uint32_t wordValue, uint32_t vaddr, mem vmem);
int _set_regcmd(uint32_t wordValue, reg vreg, reg* tab_reg);

int _disp_mem_mapcmd(mem vmem);
int _disp_mem_plagescmd(char* addr1, char* addr2, mem vmem);
int _disp_mem_offsetcmd(char* addr, int offset, mem vmem);
int _disp_reg_registercmd(char* vname, reg* tab_reg);
int _disp_reg_allcmd(reg* tab_reg);

int _assert_regcmd(reg r, int valeur);
int _assert_bytecmd(uint32_t adress, int valeur, mem vmem);
int _assert_wordcmd(uint32_t adress, int valeur, mem vmem);

int _debugcmd(interpreteur inter, FILE* fp);
int _resumecmd(interpreteur inter, FILE* fp);

int _machine_statecmd(char* cmd, char* address, Liste* L, reg* tab_reg, mem vmem);

#endif /* _CMD_GESTION_H_ */
