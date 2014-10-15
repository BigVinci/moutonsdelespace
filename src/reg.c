#include "../include/reg.h"

/**
 * Crée un registre et l'initialise
 * @param name  	le nom du registre tel que $0
 * @param mnemo  	le nom mnémonique du registre tel que $zero
 * @return 			le registre créé ou NULL en cas d'échec
 */

/* initialise un registre */
reg init_reg(char* namereg, char* mnemoreg) 
{
    reg vreg = calloc( 1, sizeof( *vreg ) ); 

    if ( NULL == vreg ) {
        WARNING_MSG( "Unable to allocate memory for vreg" );
        return NULL;
    }
   
    else {
    	vreg->name = namereg;
    	vreg->mnemo = mnemoreg;
    	vreg->data = 0; /* registre initialisé à la valeur 0 */
    }

    return vreg;
}

/* libère la mémoire allouée pour un registre */ 
void del_reg (reg vreg)
{
if ( NULL != vreg ) 
	{
        free( vreg );
    	}
    return;
}

/**
 * Permet de copier un registre placé en entrée 
 * @param registre :token indiquant le registre à copier (registre reconnaissable par son nom)
 * @param cop_reg : registre recevant les données de "registre"
 */ 
reg to_reg(char* chaine)
{
 int i=0;
 int k=0;
 int l=0;
 int m=35;
 reg* tab=init_tab_reg();
 l=strlen(chaine);
    for(i=0; i<m; i++)
    {
	if(strcmp(chaine,tab[i]->name)==0 || strcmp(chaine, tab[i]->mnemo)==0)
		{
		k=i;
		}
    }
    return tab[k];
}


/**
 * Crée l'ensemble des registres
 * @return 	le registre créé ou NULL en cas d'échec
 */
reg* init_tab_reg(void)
{
	reg* tab = calloc(35, sizeof(*tab));
	tab[0]=init_reg("$0", "$zero");
	tab[1]=init_reg("$1", "$at");
	tab[2]=init_reg("$2", "$v0");
	tab[3]=init_reg("$3", "$v1");
	tab[4]=init_reg("$4", "$a0");
	tab[5]=init_reg("$5", "$a1");
	tab[6]=init_reg("$6", "$a2");
	tab[7]=init_reg("$7", "$a3");
	tab[8]=init_reg("$8", "$t0");
	tab[9]=init_reg("$9", "$t1");
	tab[10]=init_reg("$10", "$t2");
	tab[11]=init_reg("$11", "$t3");
	tab[12]=init_reg("$12", "$t4");
	tab[13]=init_reg("$13", "$t5");
	tab[14]=init_reg("$14", "$t6");
	tab[15]=init_reg("$15", "$t7");
	tab[16]=init_reg("$16", "$s0");
	tab[17]=init_reg("$17", "$s1");
	tab[18]=init_reg("$18", "$s2");
	tab[19]=init_reg("$19", "$s3");
	tab[20]=init_reg("$20", "$s4");
	tab[21]=init_reg("$21", "$s5");
	tab[22]=init_reg("$22", "$s6");
	tab[23]=init_reg("$23", "$s7");
	tab[24]=init_reg("$24", "$t8");
	tab[25]=init_reg("$25", "$t9");
	tab[26]=init_reg("$26", "$k0");
	tab[27]=init_reg("$27", "$k1");
	tab[28]=init_reg("$28", "$gp");
	tab[29]=init_reg("$29", "$sp");
	tab[30]=init_reg("$30", "$fp");
	tab[31]=init_reg("$31", "$ra");
	tab[32]=init_reg("$32", "$PC");
	tab[33]=init_reg("$33", "$HI");
	tab[34]=init_reg("$34", "$LO");

	return tab;
}

/* libère la mémoire allouée pour un tableau de registre */
void del_tab_reg(reg* tabreg)
{
	int i;
	if (tabreg!=NULL)
	{
		for (i = 0; i < 35; ++i)
		{
			free (tabreg+i);
		}
		free (tabreg);
	}
	return;
	
}
