#ifndef _CMD_GESTION_H_
#define _CMD_GESTION_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*#include "../../src/interpreteur.c"*/

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* macros de DEBUG_MSG fournies , etc */
#include "notify.h"

/* les différents types utiles */
#include "types.h"
#include "../mem.h"

#include "interpreteur.h"


/*************************************************************\
Valeur de retour speciales lorsqu'on pour la fonction
	int parse_and_execute_cmd_string(char *input) ;
Toute autre valeur signifie qu'une erreur est survenue
 \*************************************************************/
#define CMD_OK_RETURN_VALUE 0
#define CMD_EXIT_RETURN_VALUE -1
#define CMD_UNKOWN_RETURN_VALUE -2


#ifndef _REG_
#define _REG_
/* définie la structure registre */
typedef struct registre
{
	char	*name;		/* nom du registre */ 
	char	*mnemo;		/* second nom du registre */ 
	vaddr32	address; 	/* adresse de destination sur 32 bits */  
	char	*data;		/* contenu du registre sur 32 bits */
}* reg; /* pointeur qui pointe sur un registre */ 

#endif /* _REG_ */


int _testcmd(int hexValue);
int _set_mem_bytecmd(uint8_t byteValue, uint32_t vaddr, mem vmem);
int _set_mem_wordcmd(uint32_t wordValue, uint32_t vaddr);
int _set_regcmd(uint32_t wordValue, reg vreg);
void _resumecmd(interpreteur inter);
int _disp_mem_mapcmd(mem vmem);
int _disp_mem_plagescmd(char* token, mem vmem);
int _disp_reg_registercmd(char* vname, reg tab);
int _disp_reg_allcmd(reg* tab_reg);
int _assert_regcmd(reg r, int valeur);
int _assert_bytecmd(uint32_t adress, int valeur, mem vmem);
int _assert_wordcmd(uint32_t adress, int valeur, mem vmem);
void _debugcmd(interpreteur inter);

#endif /* _CMD_GESTION_H_ */
