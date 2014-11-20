#ifndef _INSTR_CMD_GESTION_H_
#define _INSTR_CMD_GESTION_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* macros de DEBUG_MSG fournies , etc */
#include "notify.h"

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* les différents types utiles */
#include "types.h"
#include "../mem.h"
#include "../reg.h"

#include "interpreteur.h"

// cmd_gestion.c 
int _set_mem_bytecmd_2(uint8_t byteValue, uint32_t vaddr, mem vmem);
int _set_mem_wordcmd_2(uint32_t wordValue, uint32_t vaddr, mem vmem);
int _disp_reg_registercmd_2(char* vname, reg* tab);
int _disp_mem_offsetcmd_2(char* addr1, int offset, mem vmem);

#endif /* _INSTR_CMD_GESTION_H_ */
