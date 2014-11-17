#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

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

// contient les valeurs à mettre dans les registres (les valeurs sont dans rt, rs, rd, ...) et les numéros des registres à modifier (dans *_num)
typedef struct op_val_struct {int rt; int rs; int rd; int sa; int immediate; int offset; int target;
                              int rt_num; int rs_num; int rd_num; int sa_num; int immediate_num; int offset_num; int target_num;} OP_VAL;

OP_VAL* init_opvalue(void);
int realise_instr(OP_VAL* opvalue, char** vname, reg* tab_reg, mem vmem);
int maj_reg(OP_VAL* opvalue, reg* tab_reg);

// instructions arithmétiques
int instr_add(OP_VAL* opvalue);
int instr_addu(OP_VAL* opvalue);
int instr_addi(OP_VAL* opvalue);
int instr_addiu(OP_VAL* opvalue);
int instr_sub(OP_VAL* opvalue);
int instr_subu(OP_VAL* opvalue);
int instr_mult(OP_VAL* opvalue, reg* tab_reg);
int instr_div(OP_VAL* opvalue, reg* tab_reg);

// instructions logiques
int instr_and(OP_VAL* opvalue);
int instr_andi(OP_VAL* opvalue);
int instr_or(OP_VAL* opvalue);
int instr_ori(OP_VAL* opvalue);
int instr_xor(OP_VAL* opvalue);

// instructions de décalage
int instr_sll(OP_VAL* opvalue);
int instr_srl(OP_VAL* opvalue);
int instr_sra(OP_VAL* opvalue);


// fonctions auxilliaires pour les instructions de sign extend
int sign_extend_8(int a);
int sign_extend_16(int a);

// instructions set
int instr_seb(OP_VAL* opvalue);
int instr_slt(OP_VAL* opvalue);
int instr_sltu(OP_VAL* opvalue);
int instr_slti(OP_VAL* opvalue);
int instr_sltiu(OP_VAL* opvalue);

// instructions load/store
int instr_lw(OP_VAL* opvalue, mem vmem);
int instr_sw(OP_VAL* opvalue, mem vmem);
int instr_lb(OP_VAL* opvalue, mem vmem);
int instr_lbu(OP_VAL* opvalue, mem vmem);
int instr_sb(OP_VAL* opvalue, mem vmem);
int instr_lui(OP_VAL* opvalue);
int instr_mfhi(OP_VAL* opvalue, reg* tab_reg);
int instr_mflo(OP_VAL* opvalue, reg* tab_reg);

// instructions de branchement, de saut et de contrôle
int instr_beq(OP_VAL* opvalue);
int instr_bne(OP_VAL* opvalue);
int instr_bgez(OP_VAL* opvalue);
int instr_bgtz(OP_VAL* opvalue);
int instr_blez(OP_VAL* opvalue);
int instr_bltz(OP_VAL* opvalue);
int instr_j(OP_VAL* opvalue);
int instr_jal(OP_VAL* opvalue);
int instr_jalr(OP_VAL* opvalue);
int instr_jr(OP_VAL* opvalue);
int instr_break(OP_VAL* opvalue);
int instr_syscall(OP_VAL* opvalue);

//pseudo_instructions
int instr_nop(OP_VAL* opvalue);
int instr_move(OP_VAL* opvalue);
int instr_neg(OP_VAL* opvalue);
int instr_li16(OP_VAL* opvalue);
int instr_li32(OP_VAL* opvalue);
int instr_blt(OP_VAL* opvalue);

#endif /* _INSTRUCTION_H_ */
