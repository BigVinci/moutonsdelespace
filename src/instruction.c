#include "../include/common/instruction.h"


/** INIT_OPVALUE
 * commande qui initialise une structure OP_VAL*
 * @return OP_VAL* initialisé
 */
OP_VAL* init_opvalue(void)
{
    OP_VAL* opvalue=calloc(1, sizeof(OP_VAL));

// liste des valeurs utilisables lors de chaque instruction
    (*opvalue).rt=0;(*opvalue).rs=0;(*opvalue).rd=0;(*opvalue).sa=0;(*opvalue).immediate=0;(*opvalue).offset=0;;(*opvalue).target=0;

// liste des registres modifiables par chaque instruction, initialisé à 35 car le registre $35 n'existe pas
    (*opvalue).rt_num=35;(*opvalue).rs_num=35;(*opvalue).rd_num=35;(*opvalue).sa_num=35;
    return opvalue;
}


/** REALISE_INSTR
 * commande qui exécute l'instruction associée à la commande lue par disasm et qui met à jour le tableau de registres en conséquence
 * @param opvalue contient une structure OP_VAL*
 * @param vname contient le nom de la commande à exécuter (ex : "ADD", "ADDI", "SLL", "NOP", ...)
 * @param tab_reg contient le tableau des registres
 * @return 0 si réussi, 1 si fail
 */
int realise_instr(OP_VAL* op1, char** name, reg* tab_reg, mem vmem)
{
    printf("\n");

    if(strcmp(*name,"ADD")==0)
        return instr_add(op1);

    else if (strcmp(*name,"NOP")==0)
        return instr_nop(op1);

    else if (strcmp(*name,"ADDU")==0)
        return instr_addu(op1);

    else if (strcmp(*name,"AND")==0)
        return instr_and(op1);

    else if (strcmp(*name,"MFHI")==0)
        return instr_mfhi(op1,tab_reg);

    else if (strcmp(*name,"MFLO")==0)
        return instr_mflo(op1,tab_reg);

    else if (strcmp(*name,"OR")==0)
        return instr_or(op1);

    else if (strcmp(*name,"SEB")==0)
        return instr_seb(op1);

    else if (strcmp(*name,"SLTU")==0)
        return instr_sltu(op1);

    else if (strcmp(*name,"SUBU")==0)
        return instr_subu(op1);

    else if (strcmp(*name,"XOR")==0)
        return instr_xor(op1);

    else if (strcmp(*name,"BREAK")==0)
        return instr_break(op1);

    else if (strcmp(*name,"DIV")==0)
        return instr_div(op1,tab_reg);

    else if (strcmp(*name,"JALR")==0)
        return instr_jalr(op1,tab_reg);

    else if (strcmp(*name,"JR")==0)
        return instr_jr(op1,tab_reg);

    else if (strcmp(*name,"MULT")==0)
        return instr_mult(op1,tab_reg);

    else if (strcmp(*name,"SLL")==0)
        return instr_sll(op1);

    else if (strcmp(*name,"SRA")==0)
        return instr_sra(op1);

    else if (strcmp(*name,"SRL")==0)
        return instr_srl(op1);

    else if (strcmp(*name,"SUB")==0)
        return instr_sub(op1);

    else if (strcmp(*name,"SYSCALL")==0)
        return instr_syscall(op1, tab_reg, vmem);

    else if (strcmp(*name,"ADDI")==0)
        return instr_addi(op1);

    else if (strcmp(*name,"ADDIU")==0)
        return instr_addiu(op1);

    else if (strcmp(*name,"ANDI")==0)
        return instr_andi(op1);

    else if (strcmp(*name,"BEQ")==0)
        return instr_beq(op1,tab_reg);

    else if (strcmp(*name,"BGTZ")==0)
        return instr_bgtz(op1,tab_reg);

    else if (strcmp(*name,"BLEZ")==0)
        return instr_blez(op1,tab_reg);

    else if (strcmp(*name,"BNE")==0)
        return instr_bne(op1,tab_reg);

    else if (strcmp(*name,"J")==0)
        return instr_j(op1,tab_reg);

    else if (strcmp(*name,"JAL")==0)
        return instr_jal(op1,tab_reg);

    else if (strcmp(*name,"LB")==0)
        return instr_lb(op1, vmem);

    else if (strcmp(*name,"LBU")==0)
        return instr_lbu(op1, vmem);

    else if (strcmp(*name,"LUI")==0)
        return instr_lui(op1);

    else if (strcmp(*name,"LW")==0)
        return instr_lw(op1, vmem);

    else if (strcmp(*name,"ORI")==0)
        return instr_ori(op1);

    else if (strcmp(*name,"SB")==0)
        return instr_sb(op1, vmem);

    else if (strcmp(*name,"SLTIU")==0)
        return instr_sltiu(op1);

    else if (strcmp(*name,"SW")==0)
        return instr_sw(op1, vmem);

    else if (strcmp(*name,"BLTZ")==0)
        return instr_bltz(op1,tab_reg);

    else if (strcmp(*name,"BGEZ")==0)
        return instr_bgez(op1,tab_reg);

    WARNING_MSG("Aucune instructions ne correspond");
    return 1;
}


/** INIT_OPVALUE
 * commande qui met à jour le tableau de registres en fonction de la commande exécutée par realise_instr
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg contient le tableau des registres
 * @return 0 si réussi, 1 si fail
 */
int maj_reg(OP_VAL* opvalue, reg* tab_reg)
{   

    char* donnee=strdup("Initialisation");

    if (opvalue->rs_num<35)
    {
        sprintf(donnee, "%d", opvalue->rs);
        (tab_reg[opvalue->rs_num]->data)=strdup(donnee); // on met à jour le tableau de registre
    }

    if ((opvalue->rt_num)<35)
    {
        sprintf(donnee, "%d", opvalue->rt);
        (tab_reg[opvalue->rt_num]->data)=strdup(donnee); // on met à jour le tableau de registre
    }

    if (opvalue->rd_num<35)
    {
        sprintf(donnee, "%d", opvalue->rd);
        (tab_reg[opvalue->rd_num]->data)=strdup(donnee); // on met à jour le tableau de registre
    }

    if (opvalue->sa_num<35)
    {
        sprintf(donnee, "%d", opvalue->sa);
        (tab_reg[opvalue->sa_num]->data)=strdup(donnee); // on met à jour le tableau de registre
    }

    return CMD_OK_RETURN_VALUE;
}


// instructions arithmétiques

/** ADD
 * commande qui réalise l'instruction ADD
 * @param opvalue non modifiée si integer overflow, charge rd avec la somme rs+rt sinon
 * @return 0 si réussi, 1 si fail
 */
int instr_add(OP_VAL* opvalue)
{
    INFO_MSG("Command ADD");
    int dest=0;
    dest=(opvalue->rt+opvalue->rs);

    if(dest>2147483648) //on compare avec 2^31, le nombre maximal codable sur 32 bits
    {
        WARNING_MSG("Integer Overflow");
        return 1;
    }

    opvalue->rd=dest;
    return CMD_OK_RETURN_VALUE;
}


/** ADDU
 * commande qui réalise l'instruction ADDU
 * @param opvalue modifié: charge rd avec la somme rs+rt. Pas d'integer overflow
 * @return 0
 */
int instr_addu(OP_VAL* opvalue)
{
    INFO_MSG("Command ADDU");
    opvalue->rd=(opvalue->rs+opvalue->rt);
    return CMD_OK_RETURN_VALUE;
}


/** ADDI
 * commande qui réalise l'instruction ADDI
 * @param opvalue non modifiée si integer overflow, charge rt avec la somme rs+immediate sinon
 * @return 0 si réussi, 1 si fail
 */
int instr_addi(OP_VAL* opvalue)
{
    INFO_MSG("Command ADDI");
    int dest=((*opvalue).immediate+((*opvalue).rs));

    if(dest>2147483648) //on compare avec 2^31, le nombre maximal codable sur 32 bits
    {
        WARNING_MSG("Integer Overflow");
        return 1;
    }

    (*opvalue).rt=dest;
    return CMD_OK_RETURN_VALUE;
}


/** ADDIU
 * commande qui réalise l'instruction ADDIU
 * @param opvalue modifié: charge rt avec la somme rs+immediate. Pas d'integer overflow
 * @return 0
 */
int instr_addiu(OP_VAL* opvalue)
{
    INFO_MSG("Command ADDIU");
    opvalue->rt=(opvalue->rs+opvalue->immediate);
    return CMD_OK_RETURN_VALUE;
}


/** SUB
 * commande qui réalise l'instruction SUB
 * @param opvalue modifié: charge rd avec la différence rs_rt, non modifié si Integer Overflow
 * @return 0 si réussi, 1 si fail
 */
int instr_sub(OP_VAL* opvalue)
{
    INFO_MSG("Command SUB");
    int dest=0;
    dest=(opvalue->rs)-(opvalue->rt);

    if((dest<-2147483648)|(dest>2147483647))
    {
        WARNING_MSG("Integer Overflow occurs");
        return 1;
    }

    opvalue->rd=dest;
    return CMD_OK_RETURN_VALUE;
}


/** SUBU
 * commande qui réalise l'instruction SUBU
 * @param opvalue modifié: charge rd avec la différence rs_rt
 * @return 0
 */
int instr_subu(OP_VAL* opvalue)
{
    INFO_MSG("Command SUBU");
    opvalue->rd=(opvalue->rs)-(opvalue->rt);
    return CMD_OK_RETURN_VALUE;
}


/** MULT
 * commande qui réalise l'instruction MULT
 * @param opvalue contient une structure OP_VAL* à modifier
 * @param tab_reg le tableau de registre
 * @return 0
 */
int instr_mult(OP_VAL* opvalue,reg* tab_reg)
{
    INFO_MSG("Command MULT");
    int a=opvalue->rs;
    int b=opvalue->rt;

    long long c=a*b;
    long long d=0;
    long long sign1=0x00000000ffffffff;
    long long sign2=0xffffffff00000000;

    d=c&sign1;
    sprintf(tab_reg[34]->data, "%lld", d); // on met à jour le tableau de registre LO = Ligne 34

    d=c&sign2;
    d>>=16;
    d=d&sign1;
    sprintf(tab_reg[33]->data, "%lld", d); // on met à jour le tableau de registre, HI = Ligne 33

    return CMD_OK_RETURN_VALUE;
}


/** DIV
 * commande qui réalise l'instruction DIV
 * @param opvalue contient une structure OP_VAL* à modifier
 * @param tab_reg le tableau de registre
 * @return 0
 */
int instr_div(OP_VAL* opvalue,reg* tab_reg)
{
    INFO_MSG("Command DIV");

    if ((opvalue->rt)==0)
    {
	WARNING_MSG("Division par zéro, résultat imprévisible");
	return 1;
    }

    sprintf(tab_reg[33]->data, "%d",  ( (opvalue->rs)/(opvalue->rt)) ); // on met à jour le tableau de registre
    sprintf(tab_reg[34]->data, "%d",  ( (opvalue->rs)%(opvalue->rt)) ); // on met à jour le tableau de registre
    return CMD_OK_RETURN_VALUE;
}


// instructions logiques

/** AND
 * commande qui réalise l'instruction AND
 * @param opvalue modifié: charge rd avec le résultat d'un ET logique entre rs et rt.
 * @return 0
 */
int instr_and(OP_VAL* opvalue) //bitwise logical AND
{
    INFO_MSG("Command AND");
    opvalue->rd=((opvalue->rs)&(opvalue->rt));
    return CMD_OK_RETURN_VALUE;
}


/** ANDI
 * commande qui réalise l'instruction ANDI
 * @param opvalue modifié: charge rd le résultat d'un ET logique entre rs et immediate.
 * @return 0
 */
int instr_andi(OP_VAL* opvalue) //bitwise logical AND
{
    INFO_MSG("Command ANDI");
    opvalue->rt=((opvalue->rs)&(opvalue->immediate));
    return CMD_OK_RETURN_VALUE;
}


/** OR
 * commande qui réalise l'instruction OR
 * @param opvalue modifié: charge rd avec le résultat d'un OU logique entre rs et rt.
 * @return 0
 */
int instr_or(OP_VAL* opvalue)
{
    INFO_MSG("Command OR");
    opvalue->rd=((opvalue->rs)|(opvalue->rt));
    return CMD_OK_RETURN_VALUE;
}


/** ORI
 * commande qui réalise l'instruction ORI
 * @param opvalue modifié: charge rd le résultat d'un OU logique entre rs et immediate.
 * @return 0
 */
int instr_ori(OP_VAL* opvalue)
{
    INFO_MSG("Command ORI");
    opvalue->rt=((opvalue->rs)|(opvalue->immediate));
    return CMD_OK_RETURN_VALUE;
}


/** XOR
 * commande qui réalise l'instruction XOR
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_xor(OP_VAL* opvalue)
{
    INFO_MSG("Command XOR");
    opvalue->rd=(opvalue->rs)^(opvalue->rt);
    return CMD_OK_RETURN_VALUE;
}


// instructions de décalage

/** SLL
 * commande qui réalise l'instruction SLL
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_sll(OP_VAL* opvalue)
{
    INFO_MSG("Command SLL");
    opvalue->rd=(opvalue->rt)<<(opvalue->sa);
    return CMD_OK_RETURN_VALUE;
}

/** SRL
 * commande qui réalise l'instruction SRL
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_srl(OP_VAL* opvalue)
{
    INFO_MSG("Command SRL");
    int i=0;
    int a=opvalue->rt;
    int sign=0x7fffffff;

    for(i=0; i<(opvalue->sa); i++)
    {
        a>>=1;
        a=a&sign;
    }

    opvalue->rd=a;
    return CMD_OK_RETURN_VALUE;
}


/** SRA
 * commande qui réalise l'instruction SRA
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_sra(OP_VAL* opvalue)
{
    INFO_MSG("Command SRA");
    opvalue->rd=(opvalue->rt)>>(opvalue->sa);
    return CMD_OK_RETURN_VALUE;
}


// instructions set

/** sign_extend_8
 * fonction qui transforme un entier de 8 bits en son entier sign extended
 * @param entier dont on doit étendre le signe
 * @return entier sign extended
 */
int sign_extend_8(int a)
{
    int mask=0x000000ff;
    int mask2=0xffffff00;
    int sign=a&mask;
    printf("a:%x\n", a );
    printf("sign: %x\n", sign);
    if(a<0)
    {
        int b=sign+mask2;
        return b;

    }
    return sign;
}


/** sign_extend_16
 * fonction qui transforme un entier de 8 bits en son entier sign extended
 * @param entier dont on doit étendre le signe
 * @return entier sign extended
 */
int sign_extend_16(int a)
{
    int mask=0x0000ffff;
    int mask2=0xffff0000;
    int sign=a&mask;
    if(a<0)
    {
        int b=sign+mask2;
        return b;

    }
    return sign;

}




int instr_seb(OP_VAL* opvalue)
{
    INFO_MSG("Command SEB");

    int a=opvalue->rt;
    int b=sign_extend_8(a);
    opvalue->rd=b;

    return CMD_OK_RETURN_VALUE;


}






/** SLT
 * commande qui réalise l'instruction SLT
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_slt(OP_VAL* opvalue)
{
    INFO_MSG("Command SLT");

    if(opvalue->rs<opvalue->rt)
    {
        opvalue->rd=1; //True
        return CMD_OK_RETURN_VALUE;
    }

    opvalue->rd=0; //False
    return CMD_OK_RETURN_VALUE;
}


/** SLTU
 * commande qui réalise l'instruction SLTU
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */


int instr_sltu(OP_VAL*opvalue)
{
    INFO_MSG("Command SLTU");
    int c=opvalue->rs;
    if(c<0)
    {
        c=-c;
    }

    int d=opvalue->rt;
    if(d<0)
    {
        d=-d;
    }


    if(c<d)
    {
        opvalue->rd=1; //True
         return CMD_OK_RETURN_VALUE;
    }

    opvalue->rd=0; //False
     return CMD_OK_RETURN_VALUE;


}





/** SLTI
 * commande qui réalise l'instruction SLTI
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_slti(OP_VAL* opvalue)
{
    INFO_MSG("Command SLTI");
    if(opvalue->rs < opvalue->immediate)
    {
        opvalue->rt=1; //True
        return CMD_OK_RETURN_VALUE;;
    }

    opvalue->rt=0; //False
    return CMD_OK_RETURN_VALUE;
}


/** SLTIU
 * commande qui réalise l'instruction SLTIU
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */

int instr_sltiu(OP_VAL*opvalue)
{
    INFO_MSG("Command SLTIU");
    int b=opvalue->rs;
    int immediate_signext=sign_extend_16(opvalue->immediate);


    if(b<immediate_signext)
    {
        opvalue->rt=1; //True
         return CMD_OK_RETURN_VALUE;
    }

    opvalue->rt=0; //False
     return CMD_OK_RETURN_VALUE;


}




// instructions load/store

/** LW
 * place dans $rt la valeur du WORD lue dans la mémoire à l'adresse offset(base)
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_lw(OP_VAL* opvalue, mem vmem)
{
    INFO_MSG("Command LW");

    uint32_t adress=(opvalue->rs)+(opvalue->offset);
    int i=0;

        while((vmem->seg[i].start._32)<adress)
        {
            i++;
        }

    int virtual_offset=adress-(vmem->seg[i].start._32);
    opvalue->rt=(vmem->seg[i].content[virtual_offset]);

    return CMD_OK_RETURN_VALUE;
}


/** SW
 * place à l'adresse offset(base) la valeur du WORD lue dans $rt
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_sw(OP_VAL* opvalue, mem vmem)
{
    INFO_MSG("Command SW");

    int a=(opvalue->rs)+(opvalue->offset);

    return _set_mem_wordcmd_2(opvalue->rt,a,vmem);

}


/** LB
 * place dans $rt la valeur du BYTE lue dans la mémoire à l'adresse offset(base)
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_lb(OP_VAL* opvalue, mem vmem)
{
    INFO_MSG("Command LB");

    uint32_t adress=(opvalue->rs)+(opvalue->offset);
    int i=0;

        while((vmem->seg[i].start._32)<adress)
        {
            i++;
        }

    int virtual_offset=adress-(vmem->seg[i].start._32);
    opvalue->rt=(vmem->seg[i].content[virtual_offset]);

    return CMD_OK_RETURN_VALUE;
}


/** LBU
 * place dans $rt la valeur non signée (zero extended) du BYTE lue dans la mémoire à l'adresse offset(base)
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_lbu(OP_VAL* opvalue, mem vmem)
{
    INFO_MSG("Command LBU");

    uint32_t adress=(opvalue->rs)+(opvalue->offset);
    int i=0;

        while((vmem->seg[i].start._32)<adress)
        {
            i++;
        }

    int virtual_offset=adress-(vmem->seg[i].start._32);

   unsigned int result_usigned=(int)(vmem->seg[i].content[virtual_offset]);
    opvalue->rt=result_usigned;


    return CMD_OK_RETURN_VALUE;
}


/** SB
 * place  à l'adresse offset(base) la valeur du BYTE lue dans $rt
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_sb(OP_VAL* opvalue, mem vmem)
{
    INFO_MSG("Command SB");
    int a=(opvalue->rs)+(opvalue->offset); //GPR base coresponds to rs
    return _set_mem_bytecmd_2(opvalue->rt, a, vmem);
}


/** LIU
 * commande qui réalise l'instruction LIU
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_lui(OP_VAL* opvalue)
{
    INFO_MSG("Command LUI");
    opvalue->rt=(opvalue->immediate)*65536; //on multiplie par 2^16, pour décaller 16 fois vers la gauche
    return CMD_OK_RETURN_VALUE;
}


/** MFHI
 * commande qui réalise l'instruction MFHI
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_mfhi(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command MFHI");
    sscanf(tab_reg[33]->data, "%d", &(opvalue->rd)); // converti le char* en integer et le place dans rd
    return CMD_OK_RETURN_VALUE;
}


/** MFLO
 * commande qui réalise l'instruction MFLO
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_mflo(OP_VAL* opvalue,reg* tab_reg)
{
    INFO_MSG("Command MFLO");
    sscanf(tab_reg[33]->data, "%d", &(opvalue->rd)); // converti le char* en integer et le place dans rd
    return CMD_OK_RETURN_VALUE;
}


// instructions de branchement, de saut et de contrôle

/** INSTR_BEQ
 * commande qui réalise un offset si les deux registres indiqués ont la même valeur
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 dès que réussi
 */
int instr_beq(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command BEQ");
    
    char* data1=calloc(1, sizeof(char));char* data2=calloc(1, sizeof(char));
    data1=strdup(tab_reg[opvalue->rs]->data);data2=strdup(tab_reg[opvalue->rt]->data);

    if (strcmp(data1,data2)==0)
    {
        int offset=((opvalue->offset)*4); // on décale l'offset initial de 2 bits (soit un offset sur 18 bits)
    	char* data=calloc(1, sizeof(char));
        sprintf(data, "%x", offset); // converti l'entier sur 18 bits en char* contenant une adresse
    	tab_reg[32]->data=strdup(data);
    }
    else
        INFO_MSG("Les registres n'ont pas la même valeur");

    return CMD_OK_RETURN_VALUE;
}


/** INSTR_BNE
 * commande qui réalise un offset si les deux registres indiqués ont chacun une valeur différente
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 dès que réussi
 */
int instr_bne(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command BNE");
    
    char* data1=calloc(1, sizeof(char));char* data2=calloc(1, sizeof(char));
    data1=strdup(tab_reg[opvalue->rs]->data);data2=strdup(tab_reg[opvalue->rt]->data);

    if (strcmp(data1,data2)!=0)
    {
        int offset=((opvalue->offset)*4); // on décale l'offset initial de 2 bits (soit un offset sur 18 bits)
	char* data=calloc(1, sizeof(char));
        sprintf(data, "%x", offset); // converti l'entier sur 18 bits en char* contenant une adresse
	tab_reg[32]->data=strdup(data);
    }
    else
        INFO_MSG("Les registres ont la même valeur");

    return CMD_OK_RETURN_VALUE;
}


/** INSTR_BGEZ
 * commande qui réalise un offset si la valeur du registre est supérieure ou égale à 0
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 dès que réussi
 */
int instr_bgez(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command BGEZ");
    
    int a;
    sscanf(tab_reg[opvalue->rs]->data, "%x", &a);

    if (a>=0 && a<=2147483648) // si a appartient à {0; 2^31}
    {
        int offset=((opvalue->offset)*4); // on décale l'offset initial de 2 bits (soit un offset sur 18 bits)
	char* data=calloc(1, sizeof(char));
        sprintf(data, "%x", offset); // converti l'entier sur 18 bits en char* contenant une adresse
	tab_reg[32]->data=strdup(data);
    }
    else
        INFO_MSG("La valeur du registre est inférieure strictement à 0");

    return CMD_OK_RETURN_VALUE;
}


/** INSTR_BGEZ
 * commande qui réalise un offset si la valeur du registre est supérieure strictement à 0
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 dès que réussi
 */
int instr_bgtz(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command BGTZ");
    
    int a;
    sscanf(tab_reg[opvalue->rs]->data, "%x", &a);

    if (a>0 && a<=2147483648) // si a appartient à {1; 2^31}
    {
        int offset=((opvalue->offset)*4); // on décale l'offset initial de 2 bits (soit un offset sur 18 bits)
	char* data=calloc(1, sizeof(char));
        sprintf(data, "%x", offset); // converti l'entier sur 18 bits en char* contenant une adresse
	tab_reg[32]->data=strdup(data);
    }
    else
        INFO_MSG("La valeur du registre est inférieure ou égale à 0");

    return CMD_OK_RETURN_VALUE;
}


/** INSTR_BLEZ
 * commande qui réalise un offset si la valeur du registre est inférieure ou égale à 0
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 dès que réussi
 */
int instr_blez(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command BLEZ");
    
    int a;
    sscanf(tab_reg[opvalue->rs]->data, "%x", &a); // converti data en integer

    if (a==0 || (a>2147483648 && a<=4294967296)) // si a appartient à {2^31+1; 2^32} ou est nul (0=2^32)
    {
        int offset=((opvalue->offset)*4); // on décale l'offset initial de 2 bits (soit un offset sur 18 bits)
	char* data=calloc(1, sizeof(char));
        sprintf(data, "%x", offset); // converti l'entier sur 18 bits en char* contenant une adresse
	tab_reg[32]->data=strdup(data);
    }
    else
        INFO_MSG("La valeur du registre est supérieure strictement à 0");

    return CMD_OK_RETURN_VALUE;
}

/** INSTR_BLEZ
 * commande qui réalise un offset si la valeur du registre est inférieure strictement à 0
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 dès que réussi
 */
int instr_bltz(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command BLTZ");
    
    int a;
    sscanf(tab_reg[opvalue->rs]->data, "%x", &a); // converti data en integer

    if (a>2147483648 && a<4294967296) // si a appartient à {2^31+1; 2^32-1}
    {
        int offset=((opvalue->offset)*4); // on décale l'offset initial de 2 bits (soit un offset sur 18 bits)
	char* data=calloc(1, sizeof(char));
        sprintf(data, "%x", offset); // converti l'entier sur 18 bits en char* contenant une adresse
	tab_reg[32]->data=strdup(data);
    }
    else
        INFO_MSG("La valeur du registre est supérieure ou égale à 0");

    return CMD_OK_RETURN_VALUE;
}


/** INSTR_J
 * commande qui permet d'effectuer un branchement aligné à 256Mo dans la région mémoire du PC
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 dès que réussi
 */
int instr_j(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command J");
    unsigned int a=((opvalue->target)<<2); // on décale la target initiale de 2 bits (soit target sur 28 bits)

    // on veut rajouter les 4 bits de poids fort du PC
    char* data=calloc(1, sizeof(char));
    int b=0;
    data=strdup(tab_reg[32]->data); // on récupère l'adresse du PC dans data
    sscanf(data,"%d",&b); // converti data en integer dans b
    b=(b>>28); // on décale la valeur de b de 28 bits sur la droite : on ne garde que les 4 bits de poids fort
    a+=b<<28; // on rajoute ces 4 bits de poids fort devant les 28 bits de a, a fait désormais 32 bits

    sprintf(data, "%x", a); // converti la valeur de a en char* sous la forme d'un hexadécimal (ie une adresse)
    tab_reg[32]->data=strdup(data);

    return CMD_OK_RETURN_VALUE;
}


/** INSTR_JAL
 * commande qui permet d'effectuer un branchement aligné à 256Mo dans la région mémoire du PC après avoir renseigné l'adresse suivant le saut dans le registre $ra
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC et $ra ($31) à modifier
 * @return 0 dès que réussi
 */
int instr_jal(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command JAL (contient l'instruction J)");

    // on conserve la valeur suivante de PC ($32) en la mettant dans $ra ($31)
    unsigned int a=0;
    char* data=calloc(1, sizeof(char));
    sscanf(tab_reg[32]->data,"%x", &a); // converti un char* en integer
    a=a+8; // permet de cibler l'instruction suivant le saut en ignorant le NOP 
    sprintf(data,"%x", a); // converti un integer en char*
    tab_reg[31]->data=strdup(data);

    // puis on effectue l'instruction J
    instr_j(opvalue, tab_reg);

    return CMD_OK_RETURN_VALUE;
}


/** INSTR_JALR
 * commande qui effectue un saut à l'adresse rs et place l'adresse de retour (après le saut) dans rd ($31 si non spécifié)
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC et $rs à modifier * @return 0 si réussi, 1 si fail
 * @return 0 si réussi, 1 si fail
 */
int instr_jalr(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command JALR");
    if ((opvalue->rs_num)<35) // on vérifie qu'un registre ait bien été précisé dans rs
    {
        if (((opvalue)->rd_num)>35) // si rd n'est pas spécifié, le registre $31 sera utilisé par défaut
            ((opvalue)->rd_num)=31;

        // on conserve la valeur suivante de PC ($32) en la mettant dans $rd (cf instruction JAL)
        unsigned int a;
        sscanf(tab_reg[32]->data,"%d", &a); // converti un char* en integer
        a=a+4; // permet de cibler l'instruction suivant le saut
        char* data=calloc(1, sizeof(char));
        sprintf(data,"%d", a); // converti un integer en char*
        tab_reg[(opvalue)->rd_num]->data=strdup(data);

        // on effectue le saut à l'adresse rs en mettant son contenu dans PC
        sprintf(data,"%d", (opvalue)->rs); // converti un integer en char*
        tab_reg[32]->data=strdup(data);
        
        return CMD_OK_RETURN_VALUE;
    }

    WARNING_MSG("Aucun saut n'est spécifié dans $rs, l'instruction ne peut être exécutée");
    return 1;
}


/** INSTR_JR
 * commande qui effectue un saut à l'adresse contenant dans $rs
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg le tableau de registres contenant PC à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_jr(OP_VAL* opvalue, reg* tab_reg)
{
    INFO_MSG("Command JR");
    
    if ((opvalue->rs_num)<35) // on vérifie qu'un registre ait bien été précisé dans rs
    {
        // on effectue le saut à l'adresse rs en mettant son contenu dans PC
	char* data=calloc(1, sizeof(char));
        sprintf(data,"%d", (opvalue)->rs); // converti un integer en char*
	tab_reg[32]->data=strdup(data);

        return CMD_OK_RETURN_VALUE;
    }

    WARNING_MSG("Aucun saut n'est spécifié dans $rs, l'instruction ne peut être exécutée");
    return 1;
}


int instr_break(OP_VAL* opvalue)
{
    INFO_MSG("Command BREAK");
    return CMD_BREAK_RETURN_VALUE;
}


/** INSTR_SYSCALL
 * commande qui provoque un appel système et exécute le service demandé (selon la valeur de $v0)
 * @param opvalue contient une structure OP_VAL*
 * @param tab_reg contient le tableau de registre dont $v0 et $a0
 * @return 0 si réussi, -1 si exit, 1 si fail
 */
int instr_syscall(OP_VAL* opvalue, reg* tab_reg, mem vmem)
{
    INFO_MSG("Command SYSCALL");

    int a;
    sscanf(tab_reg[2]->data, "%d", &a);
    switch(a)
    {
    case 1 :
        INFO_MSG("Code de service : 1 - Affiche un entier");
        return _disp_reg_registercmd_2("$a0", tab_reg);
	break;

    case 4 :
        INFO_MSG("Code de service : 4 - Affiche une chaîne de caractère");
        return _disp_mem_offsetcmd_2(tab_reg[4]->data, 0, vmem);
	break;

    case 5 : 
        WARNING_MSG("Code de service : 5 - fonction non implémentée");
        break; 

    case 8 : 
        WARNING_MSG("Code de service : 8 - fonction non implémentée");
        break;

    case 10 : 
        INFO_MSG("Code de service : 10 - Sortie du programme");
        return CMD_EXIT_RETURN_VALUE; // entraîne la sortie du programme
	break;

    default : 
        WARNING_MSG("Code de service inexistant");
        return 1;
	break;
    }

    WARNING_MSG("Should never be here");
    return 1;
}



//pseudo_instructions - non prioritaire pour le livrable 3

/** NOP
 * commande qui retourne 0 (permet de lire une ligne sans rien faire, ie patienter)
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0
 */
int instr_nop(OP_VAL* opvalue) //bitwise logical AND
{
    INFO_MSG("Command NOP");
    return CMD_OK_RETURN_VALUE;
}


/** INSTR_MOVE
 * commande qui copie le contenu du registre $rs dans le registre destination $rt
 * @param opvalue contient une structure OP_VAL* à modifier
 * @return 0 si réussi, 1 si fail
 */
int instr_move(OP_VAL* opvalue)
{
    INFO_MSG("Command MOVE");
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
    INFO_MSG("Command NEG");
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
    INFO_MSG("Command LI16");
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
    INFO_MSG("Command LI32");
    WARNING_MSG("Fonction non implémentée - non comprise");
    return CMD_OK_RETURN_VALUE;
}


int instr_blt(OP_VAL* opvalue)
{
    INFO_MSG("Command BLT");
    WARNING_MSG("Fonction non implémentée - la structure opvalue n'a pas besoin d'être modifée");
    return CMD_OK_RETURN_VALUE;
}
