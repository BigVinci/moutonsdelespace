#include "../include/common/instruction.h"


/** INIT_OPVALUE
 * commande qui initialise une structure OP_VAL*
 * @return OP_VAL* initialisé
 */
OP_VAL* init_opvalue(void)
{
    OP_VAL* opvalue=calloc(1, sizeof(OP_VAL));

// liste des valeurs utilisables lors de chaque instruction
    (*opvalue).rt=0;(*opvalue).rs=0;(*opvalue).rd=0;(*opvalue).sa=0;(*opvalue).immediate=0;(*opvalue).offset=0;

// liste des registres modifiables par chaque instruction, initialisé à 35 car le registre $35 n'existe pas
    (*opvalue).rt_num=35;(*opvalue).rs_num=35;(*opvalue).rd_num=35;(*opvalue).sa_num=35;(*opvalue).immediate_num=35;(*opvalue).offset_num=35;
    return opvalue;
}


/** REALISE_INSTR
 * commande qui exécute l'instruction associée à la commande lue par disasm et qui met à jour le tableau de registres en conséquence
 * @param opvalue contient une structure OP_VAL*
 * @param vname contient le nom de la commande à exécuter (ex : "ADD", "ADDI", "SLL", "NOP", ...)
 * @param tab_reg contient le tableau des registres
 * @return 0 si réussi, 1 si fail
 */
int realise_instr(OP_VAL* opvalue, char** vname, reg* tab_reg)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


/** INIT_OPVALUE
 * commande qui met à jour le tableau de registres en fonction de la commande exécutée par realise_instr
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg contient le tableau des registres
 * @return 0 si réussi, 1 si fail
 */
int maj_reg(OP_VAL* opvalue, reg* tab_reg)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


// instructions arithmétiques

/** ADD
 * commande qui 
 * @param opvalue contient une structure OP_VAL* possédant toutes les informations nécessaires à la mise à jour du tableau de registres
 * @return 0 si réussi, 1 si fail
 */
int instr_add(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_addu(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_addi(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}

int instr_addiu(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_sub(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_subu(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_mult(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_div(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


// instructions logiques
int instr_and(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_andi(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_or(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_ori(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_xor(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


// instructions de décalage

int instr_sll(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_srl(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_sra(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


// instructions set

int instr_seb(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_slt(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_sltu(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_slti(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_sltiu(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


// instructions load/store

int instr_lw(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_sw(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_lb(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_lbu(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_sb(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_lui(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_mfhi(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


int instr_mflo(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


// instructions de branchement, de saut et de contrôle

int instr_beq(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


int instr_bne(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


int instr_bgez(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


int instr_bgtz(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


int instr_blez(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


int instr_bltz(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


/** INSTR_J
 * commande qui permet d'effectuer un branchement aligné à 256Mo dans la région mémoire du PC
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 dès que réussi
 */
int instr_j(OP_VAL* opvalue)
{
    unsigned a=((opvalue->target)<<2); 
    (opvalue->target)=a; // on ne peut rajouter les 4 bits de poids fort ici car le tableau de registre n'est pas présent

    WARNING_MSG("La structure opvalue a été modifée");
    return CMD_OK_RETURN_VALUE;
}


int instr_jal(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée");
    return CMD_OK_RETURN_VALUE;
}


/** INSTR_JALR
 * commande qui initialise le registre $rd à $31 si besoin et qui met à jour ce registre ainsi que $rs
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_jalr(OP_VAL* opvalue)
{
    if ((opvalue->rs_num)!=35)
    {
        if (((opvalue)->rd_num)!=35) // si rd n'est pas spécifié, le registre $31 sera utilisé par défaut
            ((opvalue)->rd_num)=31;

        // il faut mettre à jour rd et rs

        return CMD_OK_RETURN_VALUE;
    }

    WARNING_MSG("L'instruction JALR n'a pas fonctionné car opvalue n'a pas été modifié comme prévu");
    return 1;
}


int instr_jr(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


int instr_break(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - non comprise");
    return CMD_OK_RETURN_VALUE;
}


int instr_syscall(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - non comprise");
    return CMD_OK_RETURN_VALUE;
}



//pseudo_instructions - non prioritaire pour le livrable 3

int instr_nop(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


/** INSTR_MOVE
 * commande qui copie le contenu du registre $rs dans le registre destination $rt
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_move(OP_VAL* opvalue)
{
    if((opvalue->rt_num)==35 || (opvalue->rs_num)==35)
    {
        WARNING_MSG("Ces registres ne peuvent être modifiés. L'instruction instr_move ne peut être exécutée");
        return 1;
    }

    (opvalue->rt)=(opvalue->rs);
    return CMD_OK_RETURN_VALUE;
}


/** INSTR_NEG
 * commande qui copie l'opposé du contenu du registre $rs (-$rs) dans le registre $rt
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_neg(OP_VAL* opvalue)
{
    if((opvalue->rt_num)==35 || (opvalue->rs_num)==35)
    {
        WARNING_MSG("Ces registres ne peuvent être modifiés. L'instruction instr_move ne peut être exécutée");
        return 1;
    }

    (opvalue->rt)=(opvalue->rs);
    return CMD_OK_RETURN_VALUE;
}


/** INSTR_LI16
 * commande qui place la valeur immediate sur 16 bits dans le registre $rt sur 32 bits
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_li16(OP_VAL* opvalue)  // immediate sur 16 bits
{
    if((opvalue->rt_num)==35)
    {
        WARNING_MSG("Ce registre ne peut être modifié. L'instruction instr_move ne peut être exécutée");
        return 1;
    }

    (opvalue->rt)=(opvalue->immediate);
    return CMD_OK_RETURN_VALUE;
}


int instr_li32(OP_VAL* opvalue)  // immediate sur 32 bits
{
    WARNING_MSG("Fonction non implémentée - non comprise");
    return CMD_OK_RETURN_VALUE;
}


int instr_blt(OP_VAL* opvalue)
{
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}


