#ifndef _DISASM_H_
#define _DISASM_H_

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
#include "instruction.h"

typedef struct definition {int nb_op; char type[100]; char name[100]; int sign; int masque; char op_mapping[100][100];} def; //Structure correspondant à une définition du dictionnaire
typedef struct instr {def definition; char code[100];} instruction; // structure correspondant à une instruction

typedef struct R_TYPE {unsigned int func:6, sa:5, rd:5, rt:5, rs:5, opcode:6;} R_TYPE; //structure qui defini un RTYPE
typedef struct I_TYPE {unsigned int immediate:16, rt:5, rs:5, opcode:6;} I_TYPE; //ITYPE
typedef struct J_TYPE {unsigned int target:26, opcode:6;} J_TYPE; //JTYPE

union inst_poly { R_TYPE r; I_TYPE i; J_TYPE j; unsigned int code;}; //Union reliant ces trois types

int _disasm_range_hexacmd(char* addrValue1, char* addrValue2, mem vmem, reg* tab_reg);
int _disasm_range_offsetcmd(char* addrValue1, int offsetValue, mem vmem, reg* tab_reg);

def* mem_dico(char*nom);

int if_j_type(unsigned int code_instr, OP_VAL* opvalue);
int if_i_type(unsigned int code_instr, instruction int_t, reg*tab_reg, OP_VAL* opvalue);
int if_r_type(unsigned int code_instr, instruction int_t, reg*tab_reg, OP_VAL* opvalue);
def trouve_def(char*code, def*tab_instr);
int disasm(char*code, def*tab_instr, reg*tab_reg,char*adress, char** name, OP_VAL* opvalue);



#endif /* _DISASM_H_ */
