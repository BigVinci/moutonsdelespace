#include "../include/common/disasm.h"


/** DISASMCMD RANGE HEXA
 * commande qui lis chaque instruction et qui les désassemble à l'aide de la fonction disasm
 * @param addrValue1 l'adresse de départ où le désassemblage débute
 * @param addrValue2 l'adresse de fin où le désassemblage s'arrête
 * @param vmem la mémoire où est chargé le fichier objet ELF à désassembler
 * @param tab_reg le tableau de registre
 * @return 0 si réussite, 1 si fail 
 */
int _disasm_range_hexacmd(char* addr1, char* addr2, mem vmem, reg* tab_reg)
{
    int no_args=1, i=0, j=0;
    uint32_t addrreelle;

    int* value1=calloc(1, sizeof(int)); int* value2=calloc(1, sizeof(int));
    int* value3=calloc(1, sizeof(int)); int* value4=calloc(1, sizeof(int)); // représente les 4 octets à vérifier

    unsigned int addr_start; sscanf(addr1, "%x", &addr_start);
    unsigned int addr_end; sscanf(addr2, "%x", &addr_end);
    int addr_end2=(vmem->seg[1].start._32+vmem->seg[1].size._32);
    char* contenu=calloc(1, sizeof(char));

    if (addr_start < 4096) {addr_start=4096; strcpy(addr1, "0x1000");} // on vérifie que l'adresse de départ est bien dans le .text
    if (addr_end < 4096) {addr_end=4096; strcpy(addr2, "0x1000");} // on vérifie que l'adresse de fin est bien dans le .text
    if (addr_end > addr_end2) {addr_end=addr_end2;} // on vérifie que l'adresse de fin est bien dans le .text

    if (addr_start > addr_end) // si les bornes sont inversées 
    {
        WARNING_MSG("%s : %s sera affiché à la place de %s : %s (car cette plage ne peut exister)", addr2, addr1, addr1, addr2);
        addr_end2=addr_end; addr_end=addr_start; addr_start=addr_end2; // on inverse les bornes en utilisant addr_end2 car cette variable n'est plus utile pour la suite
    }

    if (((addr_start-vmem->seg[0].start._32)%4)!=0) // on doit commencer au début d'une instruction
    {
        WARNING_MSG("Cette adresse n'est pas valide. Veuillez indiquer l'adresse de début d'une instruction");
        return 1;
    }

    if (addr_end > (vmem->seg[0].start._32+vmem->seg[0].size._32)) // on doit finir dans le .text
    {
        WARNING_MSG("Cette adresse n'est pas valide. Veuillez indiquer une adresse de fin appartenant au .text");
        return 1;
    }

    def* dico=mem_dico("dico_instr.txt");

    INFO_MSG("Lancement de la fonction disasm %s : %s", addr1, addr2);
    while (addr_start<=addr_end)
    {
	no_args=0; 
	int* a=calloc(1, sizeof(int));


	    addrreelle=(addr_start-(vmem->seg[0].start._32));

            *value1=vmem->seg[0].content[addrreelle]; // on récupère chaque byte de l'adresse indiquée
            *value2=vmem->seg[0].content[addrreelle+1];
            *value3=vmem->seg[0].content[addrreelle+2]; 
            *value4=vmem->seg[0].content[addrreelle+3];
	    *a = (*value4) + 256*(*value3) + 256*256*(*value2) + 256*256*256*(*value1);

	    sprintf(contenu, "%x", *a); // on converti la valeur de l'octet ciblé en char*


	j=disasm(contenu, dico, tab_reg, addr1);

	if (j!=0) // erreur dans disasm
	{
	    WARNING_MSG("La fonction disasm a retourné une erreur, arrêt du désassemblage");
            return 1;
	}

	i+=4;
	addr_start+=4; sprintf(addr1, "%x", addr_start);	
    }

    if (no_args==1) // si il ne se passe rien
    {
        WARNING_MSG("Impossible d'effectuer la fonction disasm");
        return 1;
    }

    free (dico);
    return CMD_OK_RETURN_VALUE;
}


/** DISASMCMD RANGE OFFSET
 * commande qui lis chaque instruction et qui les désassemble à l'aide de la fonction disasm
 * @param addrValue1 l'adresse de départ où le désassemblage débute
 * @param offsetValue le nombre d'adresse à désassembler
 * @param vmem la mémoire où est chargé le fichier objet ELF à désassembler
 * @param tab_reg le tableau de registre
 * @return 0 si réussite, 1 si fail 
 */
int _disasm_range_offsetcmd(char* addr1, int offsetValue, mem vmem, reg* tab_reg)
{
    DEBUG_MSG("La fonction disasm_range_offset a été lancée"); //On vérifie que la bonne fonction s'ouvre

    char* addr2=calloc(1, sizeof(char));
    unsigned int val2;
    sscanf(addr1, "%x", &val2);
    val2 += offsetValue;
    sprintf(addr2, "%x", val2);
    return _disasm_range_hexacmd(addr1, addr2, vmem, tab_reg);
}


/**
 * Met en mémoire le dictionnaire (allocation)
 * @param nom le nom (ne pas oublier .txt !!) du dictionnaire
 * @return tableau de définition *def i.e. le dictionnaire
 */
def* mem_dico(char*nom)
{
    FILE*dico=NULL;
    dico=fopen(nom, "r"); //on ouvre le dico

    char definition[100];
    int i=0;
    char*token=NULL;
    def*tab=calloc(40, sizeof(def)); //allocation dynamique du tableau de définition
    int k=0;
    int j=0;

    for(i=0; i<40; i++) //remplissage de toutes les cases "définition"
    {
    	fgets(definition,100,dico); //on lit la ligne du dico puis on la découpe en token et on remplit les champs de la structure définition

    	token=strtok(definition," " );
    	sscanf(token,"%x", &((tab[i]).sign)); 
    	token=strtok(NULL," " );
    	sscanf(token,"%x", &((tab[i]).masque)); 
    	token=strtok(NULL," ");
    	sscanf(token,"%s", ((tab[i]).type));
    	token=strtok(NULL," ");
    	sscanf(token,"%s", ((tab[i]).name)); 
     	token=strtok(NULL," " );
    	sscanf(token,"%d", &((tab[i]).nb_op));

     	k=0;
    	j=0;

	for(j=0; j<tab[i].nb_op; j++) //ici on met un for, car il n'y a pas le même nombre d'opérande pour toutes instructions
	{
    	    token=strtok(NULL," ");
	    sscanf(token,"%s",(tab[i].op_mapping[k])); //on remplit le tableau d'operandes "op_mapping" 
	    k++;
	}
    }
    return tab;
}


/**
 * Affiche les registres si J TYPE
 * @param code_instr contient le code hexa de l'instruction
 * @return 0 
 */
int if_j_type(unsigned int code_instr) // l'instruction n'est pas en paramètre, car ici pas besoin de op_mapping
{
    union inst_poly inst;
    inst.code=code_instr; //on initialise l'union
//    int op_code_j=inst.j.opcode; // inutile pour le moment
    int target_j=inst.j.target;
    //on récupère la valeur de "target" et on l'affiche

    printf(" %d ",target_j);
    printf("\n");
    return CMD_OK_RETURN_VALUE;
}


/**
 * Affiche les registres si I TYPE
 * @param code_instr contient le code hexa de l'instruction
 * @param int_t contient la structure de l'instruction
 * @param tab_reg indique le tableau de registres
 * @return 0 si réussi, 1 si fail
 */
int if_i_type(unsigned int code_instr, instruction int_t, reg*tab_reg)
{
    union inst_poly inst;
    inst.code=code_instr; //initialisation de l'union
//    int op_code_i=inst.i.opcode; // inutile pour le moment
    int rs_i=inst.i.rs; //on récupère toutes les opérantes grace à l'union
    int rt_i=inst.i.rt;
    int immediate=inst.i.immediate;
    int offset=immediate;
    if (immediate > 32767) offset-=65542; // calcul de l'offset dans le cas où il est censé être négatif (complément à 2)
    char*s=NULL;
    char*reg=NULL;

    int i=0;
    for(i=0; i<(int_t.definition.nb_op); i++) //On teste les noms des opérandes pour les afficher dans le bon ordre, puis on les affiche
    {
        s=int_t.definition.op_mapping[i]; 
        if(strcmp(s,"rs")==0)
        {   
	    reg=(tab_reg[rs_i]->mnemo);
            printf(" %s", reg);
        }

        else if(strcmp(s,"rt")==0)
        {   
	    reg=(tab_reg[rt_i]->mnemo);
            printf(" %s", reg);
        }

        else if(strcmp(s,"immediate")==0)
        {
            printf(" %d", immediate);
        }

        else if(strcmp(s,"offset")==0)
        {
            printf(" %d", offset); //ce n'est pas immediate ici, mais ça correspond au nombre contenu dans "immediate"
        }

        else
	{
   	    WARNING_MSG("Impossible d'afficher l'opération"); //si aucune opérande ne corespond il y a un probleme
            return 1;
        }
    }
    printf("\n");
    return CMD_OK_RETURN_VALUE;
}


/**
 * Affiche les registres si R TYPE
 * @param code_instr contient le code hexa de l'instruction
 * @param int_t contient la structure de l'instruction
 * @param tab_reg indique le tableau de registres
 * @return 0 si réussi, 1 si fail
 */
int if_r_type(unsigned int code_instr, instruction int_t, reg*tab_reg)
{
    union inst_poly inst;
    inst.code=code_instr; //initialisation de l'union
//    int op_code_r=inst.r.opcode; // inutile pour le moment
    int rs_r=inst.r.rs; //récupération des paramètres
    int rt_r=inst.r.rt;
    int rd_r=inst.r.rd;
    int sa_r=inst.r.sa;
//    int func_r=inst.r.func; // inutile pour le moment

    char*s=NULL;
    char*reg=NULL;

    int i=0;
    for(i=0; i<(int_t.definition.nb_op); i++) //affichage des opérandes dans le bon ordre
    {
        s=int_t.definition.op_mapping[i];

        if(strcmp(s,"rs")==0)
        {   
	    reg=(tab_reg[rs_r]->mnemo);
            printf(" %s", reg);
        }

        else if(strcmp(s,"rt")==0)
        {   
	    reg=(tab_reg[rt_r]->mnemo);
            printf(" %s", reg);
        }

        else  if(strcmp(s,"rd")==0)
        {   
	    reg=(tab_reg[rd_r]->mnemo);
            printf(" %s", reg);
        }

        else if(strcmp(s,"sa")==0)
        {   
	    reg=(tab_reg[sa_r]->mnemo);
            printf(" %s", reg);
        }

        else
	{
   	    WARNING_MSG("Impossible d'afficher l'opération"); //si aucune ne corespond, renvois d'une erreur 
            return 1;
        }
    }
    printf("\n");
    return CMD_OK_RETURN_VALUE;
}


/**
 * Trouve la définition corespondant à l'instruction
 * @param code contient le code de l'instruction
 * @param tab_instr correspond au dictionnaire
 * @return la définition recherchée
 */
def trouve_def(char*code, def*tab_instr)
{
    int code_int=0; int i=0; int sign_code=0;
    sscanf(code,"%x",&code_int); //on transforme le code en entier hexadecimal

    for(i=0; i<40; i++)
    {
        sign_code=code_int&(tab_instr[i].masque); //on applique le masque pour chaque ligne du dictionnaire
        if((tab_instr[i].sign)==sign_code) //on compare les signatures obtenues avec celles du dictionnaire
    	{
            return tab_instr[i];
    	}
    }
    WARNING_MSG("Cette instruction ne correspond à aucune définition");
    def a; a.nb_op=0; a.type[0]=0; a.name[0]=0; // a est au type def ce que NULL est au type void*
    return a;
}


/** DISASMCMD
 * Affiche le résultat du désasemblage
 * @param code contient le code de l'instruction 
 * @param tab_instr contient le dictionnaire
 * @param tab_reg contient le tableau des registres
 * @param adress indique l'adresse virtuelle de l'instruction
 * @return 0 si réussi, 1 si fail
 */
int disasm(char* code, def* tab_instr, reg*tab_reg,char*adress)
{ 
    instruction int_t;
    int adresse_virtuelle=0;

    sscanf(code, "%s", int_t.code);
    sscanf(adress, "%x", &adresse_virtuelle);
    (int_t.definition)=trouve_def(code, tab_instr);
    printf("%x :: %s",adresse_virtuelle ,int_t.definition.name  ); // affiche l'adresse virtuelle et le nom

    unsigned int code_instr=0;
    sscanf(code,"%x", &code_instr);

    if(strcmp(int_t.definition.type,"R")==0)
    {
  	return if_r_type(code_instr,int_t,tab_reg); // si RTYPE renvoi vers la fonction d'affichage RTYPE
    }

    else if(strcmp(int_t.definition.type,"I")==0)
    {
   	return if_i_type(code_instr,int_t,tab_reg); // si ITYPE renvoi vers la fonction d'affichage ITYPE
    }

    else if (strcmp(int_t.definition.type,"J")==0)
    {
  	return  if_j_type(code_instr); // si JTYPE renvoi vers la fonction d'affichage JTYPE
    }

    else
    {
    	WARNING_MSG("Unknown type");
    	return 1;
    }
}
