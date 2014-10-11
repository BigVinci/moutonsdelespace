#include "../include/common/fonct_gestion.h"


/**
 * return le prochain token de la chaine actuellement
 * analysee par l'interpreteur
 * La fonction utilise une variable interne de l'interpreteur
 * pour gerer les premiers appels a strtok
 * @inter le pointeur vers l'interpreteur
 * @return un pointeur vers le token ou NULL
 */
char* get_next_token(interpreteur inter) { /* lis le token suivant */

  char       *token = NULL;
  char       *delim = " \t\n"; /* chaque terme est separe par un espace */

  if ( inter->first_token == 0 ) {
    token = strtok_r( inter->input, delim, &(inter->from) ); /*premier mot de la ligne entrée par l'utilisateur dans token */
    inter->first_token = 1;
  }
  else {
    token = strtok_r( NULL, delim, &(inter->from) ); /* si on a déjà commencé la lecture de la ligne, on ne recommence pas depuis le début */
  }

  if ( NULL == token ) { /* si la chaine de caractère est vide, on recommence depuis le début de la ligne */
    inter->first_token = 0;
  }

  return token;
}


/**
 * teste si un token est une valeur hexa
 * ATTENTION cette méthode n'est pas complete et ne fonctionnera pas dans tous les cas
 * essayer avec 0x567ZRT...
 *@param chaine le token à analyser
 *@return 0 si non-hexa, non null autrement
 */
int is_hexa(char*chaine)
{
    int i=0;
    int j;
    int k=0;
    int l=strlen(chaine);
    if(strlen(chaine)>2) // les deux premier caractères de l'hexa sont 0 et x, donc il faut que la chaine ait plus de deux caractère
    {
        for(j=2; j<l; j++)
        {
        if(     chaine[j]=='0'
            || chaine[j]=='1'
            || chaine[j]=='2'
            || chaine[j]=='3'
            || chaine[j]=='4'
            || chaine[j]=='5'
            || chaine[j]=='6'
            || chaine[j]=='7'
            || chaine[j]=='8'
            || chaine[j]=='9'
            || chaine[j]=='a' // chaine[j] est un caractère
            || chaine[j]=='b'
            || chaine[j]=='c'
            || chaine[j]=='d'
            || chaine[j]=='e'
            || chaine[j]=='f'
            || chaine[j]=='A' // chaine[j] est un caractère en majuscule
            || chaine[j]=='B'
            || chaine[j]=='C'
            || chaine[j]=='D'
            || chaine[j]=='E'
            || chaine[j]=='F')
                        {
                                    k++;
                                        }
        }
    }
    return (chaine!=NULL && strlen(chaine)>2
            && chaine[0]=='0'
            && chaine[1]=='x'
            && sscanf(chaine,"%x",&i)==1
            && l<11
            && k==(l-2) && chaine[l]=='\0');

}




/* test si la chaine de caractère est un octet */
int is_byte(char*chaine)
{   int l=0;
    int i=0;
    int k=0;
    l=strlen(chaine);
    for(i=0; i<l; i++)
    {
        if(chaine[i]=='0' || chaine[i]=='1')
        {
            k++;
        }
    }
    return(chaine!=NULL && k==l && l==8 && chaine[l]=='\0');
}






/* test si la chaine de caractère est un word */
int is_word(char* chaine)
{ int i=0;
	int k=0;
	int l=0;
	l=strlen(chaine);				//Pour chaque bit vérifie qu'il est bien égal soit à 0 soit à 1
    for(i=0; i<32; i++)
	{
		if(chaine[i]=='0' || chaine[i]=='1')
		{
		k++;
		}
	}
 return (chaine!=NULL && k==l && strlen(chaine)==32 && chaine[l]=='\0'); // Vérifie que tous les bits sont bien égaux à 1 ou à 0, et qu'il y en a bien 32
}






/* test si la chaine de caractère est un entier  */
int is_integer(char* chaine)
{   int i=0;
    int k=0;
    int l=0;
    l=strlen(chaine);
    if (chaine[0]=='-') /* vérifie si le nombre est négatif */
    {
    	for(i=1; i<l; i++)
    	{
        	if(   chaine[i]=='0'
           || chaine[i]=='1'
           || chaine[i]=='2'
           || chaine[i]=='3'
           || chaine[i]=='4'
           || chaine[i]=='5'
           || chaine[i]=='6'
           || chaine[i]=='7'
           || chaine[i]=='8'
           || chaine[i]=='9')
            k++;
	}
	k++; /*cas i=0 */
    }
    else
    {
    for(i=0; i<l; i++)
      {
        if(   chaine[i]=='0'
           || chaine[i]=='1'
           || chaine[i]=='2'
           || chaine[i]=='3'
           || chaine[i]=='4'
           || chaine[i]=='5'
           || chaine[i]=='6'
           || chaine[i]=='7'
           || chaine[i]=='8'
           || chaine[i]=='9')  
            k++;
      }
    }
    return (chaine!=NULL && k==l && chaine[l]=='\0');
}





/* test si la chaine de caractère est un fichier elf */
int is_elf(char* chaine)
{	int l;
	l=strlen(chaine);

return ( chaine[l-4]=='.' && chaine[l-3]=='e' && chaine[l-2]=='l' && chaine[l-1]=='f' && chaine[l]=='\0');

}


/* test si la chaine de caractère est un registre existant */
int is_register(char* chaine)
{
 int i=0;
 int k=0;
 int l=0;
 int m=35;
 reg tab=init_tab_reg();
 l=strlen(chaine);
    for(i=0; i<m; i++)
    {
	if(strcmp(chaine,tab[i].name)==0 || strcmp(chaine, tab[i].mnemo)==0)
		{
		k++;
		}
    }
    return( chaine!=NULL && k==1 && chaine[l]=='\0');
}



/**
 * retourne le type du token (fonction tres incomplete)
 * @param chaine le token à analyser
 * @return un entier correspondant au type du token
 *
 */
int get_type(char* chaine) {
    if (is_hexa(chaine))
        return HEXA;
    else if (is_byte(chaine))
    	return BYTE;
    else if (is_word(chaine))
    	return WORD;
    else if (is_integer(chaine))
    	return INTEGER;
 /*   else if (is_octal(chaine))
    return OCTAL */
    else if (is_register(chaine))
    	return REG; 
    else if (is_elf(chaine))
    	return ELF;
    return UNKNOWN;
}



/**
*
* @brief parse la chaine courante de l'interpreteur a la recherche d'une commande, et execute cette commande.
* @param inter l'interpreteur qui demande l'analyse
* @return CMD_OK_RETURN_VALUE si la commande s'est executee avec succes (0)
* @return CMD_EXIT_RETURN_VALUE si c'est la commande exit. Dans ce cas, le programme doit se terminer. (-1)
* @return CMD_UNKOWN_RETURN_VALUE si la commande n'est pas reconnue. (-2)
* @return tout autre nombre (eg tout nombre positif) si erreur d'execution de la commande
*/
int execute_cmd(interpreteur inter, reg tabreg, mem vmem)
{
    DEBUG_MSG("input '%s'", inter->input);
    char cmdStr[MAX_STR];
    memset( cmdStr, '\0', MAX_STR );

    /* gestion des commandes vides, commentaires, etc*/
    if(strlen(inter->input) == 0
            || sscanf(inter->input, "%s", cmdStr) == 0
            || strlen(cmdStr) == 0
            || cmdStr[0] == '#') { /* ligne commence par # => commentaire*/
        return CMD_OK_RETURN_VALUE;
    }

    /*on identifie la commande avec un premier appel a get_next_token*/
    char * token = get_next_token(inter);

    /* test si la commande est exit */
    if(strcmp(token, "exit") == 0)
    {
        return exitcmd(inter);
    }
    /* test si la commande est test (lance testcmd et pas _testcmd !!) */
    else if(strcmp(token, "test") == 0)
    {
        return testcmd(inter);
    }
    /* test si la commande est load */
    else if(strcmp(token, "load") == 0)
    {
    return loadcmd(inter);
    }
    /* test si la commande est disp */
    else if(strcmp(token, "disp") == 0)
    {
    return dispcmd(inter, tabreg, vmem );
    }

    /* test si la commande est disasm */
    else if(strcmp(token, "disasm") == 0)
    {
    return disasmcmd(inter);
    }

    /* test si la commande est set */
    else if(strcmp(token, "set") == 0)
    {
    return setcmd(inter, tabreg);
    }

    /* test si la commande est assert */
    else if(strcmp(token, "assert") == 0)
    {
    return assertcmd(inter, tabreg, vmem);
    }

    /* test si la commande est resume */
    else if(strcmp(token, "resume") == 0)
    {
    resumecmd(inter);
    return CMD_OK_RETURN_VALUE;
    }

    /* test si la commande est debug */
    else if(strcmp(token, "debug") == 0)
    {
    debugcmd(inter);
    return CMD_OK_RETURN_VALUE;
    }

    /* si aucune commande n'est reconnue */
        WARNING_MSG("Unknown Command : '%s'\n", cmdStr);
    return CMD_UNKOWN_RETURN_VALUE;
}



/*************************************************************\
Les commandes de l'émulateur.

 Dans cette version, six commandes :
    "test" qui attend un nombre strictement positifs d'hexa strictement positifs et affiche ce(s) nombre() +1 dans le terminal
    "exit" qui quitte l'émulateur
    "load"
    "disp"
    "disasm"
    "set"
    "assert"
    "resume"
    "debug"

 \*************************************************************/



/**
 * version de la commande test qui analyse la chaine entrée à
 * l'interpreteur. Si la commande est correcte elle est executée.
 * Si la commande contient plusieurs parametres valides, elle
 * est excutée plusieurs fois.
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en case de succes, un nombre positif sinon
 */

int testcmd(interpreteur inter) {
    DEBUG_MSG("Chaine : %s", inter->input);
    int return_value=0;

    int no_args=1;
    /* la commande test attend un argument hexa */
    int hexValue;
    char * token=NULL;

    /* la boucle permet d'executer la commande de manière recurrente*/
    /* i.e., tant qu'il y a un hexa on continue*/
    while((token = get_next_token(inter))!=NULL && return_value==0) {
            no_args=0;
        switch(get_type(token)) {
        case HEXA:
            sscanf(token,"%x",&hexValue);
            return_value = _testcmd(hexValue);
            break;
        default :
            WARNING_MSG("value %s is not a valid argument of command %s\n",token,"testcmd");
            return 1;
        }
    }


    if(no_args)
	{
            WARNING_MSG("no argument given to command %s\n","testcmd");
            return 1;
        }


    return return_value;
}


/**
 * commande exit qui ne necessite pas d'analyse syntaxique
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en case de succes, un nombre positif sinon
 */
int exitcmd(interpreteur inter) {
    INFO_MSG("Bye bye !");
    return CMD_EXIT_RETURN_VALUE; /* retourne -1 et non pas 0 d'après le define initial non ? */
}


/**
 * commande qui alloue la mémoire et charge un fichier .elf en mémoire
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en cas de succes, un nombre positif sinon
 */
int loadcmd(interpreteur inter)
{
    printf("Fonction non implémentée.\n");
    return 0;
}


/**
 * commande qui affiche le code assembleur
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en cas de succes, un nombre positif sinon
 */
int disasmcmd(interpreteur inter)    /* A ne pas créer pour le moment */
{
    printf("Fonction non implémentée.\n");
    return 0;
}


/**
 * commande qui modifie une valeur en mémoire ou un registre
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en cas de succes, un nombre positif sinon
 */
int setcmd(interpreteur inter, reg tabreg)
{
    DEBUG_MSG("Chaine en entrée : %s", inter->input);
    int return_value=0;
    int no_args_1=1, no_args_2=1, no_args_3=1, no_args_4=1, no_args_5=1; /* permet de tester s'il manque un argument dans la boucle while suivante */

    char* token=NULL;

    /* la commande set permet d'affecter une valeur integer à une adresse non signée sur 32 bits ou à un registre */
    uint32_t addrValue; /* argument uint32_t (adresse) */
    uint32_t intValue;	/* valeur sur 32 bits */
    reg regValue=NULL;       /* argument registre */

    /* la boucle permet d'executer la commande de manière recurrente*/
    while((token = get_next_token(inter))!=NULL && return_value==0)
    {
    no_args_1=0; /* il y a un argument puisque token != NULL */

/* la commande set attend soit le terme "reg", soit le terme "mem" */
    if(!strcmp(token,"mem")) /* commande entrée : set mem ... */
        {
            while((token = get_next_token(inter))!=NULL && return_value==0)
            {no_args_2=0;
	    if (!strcmp(token,"byte")) /* commande entrée : set mem byte ... */
                 {while((token = get_next_token(inter))!=NULL && return_value==0)
                  {no_args_3=0;
                    if (get_type(token)==WORD) /* adresse non signée sur 32 bits */
		               {
                        sscanf(token,"%u",&addrValue); /* met l'adresse non signée dans addrValue */
                        if ((token = get_next_token(inter))!=NULL)
                        {
                            if (get_type(token)==INTEGER) /* on vérifie que la valeur est un entier */
                                {
				                    if (get_next_token(inter)==NULL) /* la chaine de caractère est bien finie */
                                    {
                                    sscanf(token,"%u",&intValue);
                                    INFO_MSG("La commande set mem byte <adresse> <valeur> est exécutée.\n");
                                    return_value= _set_mem_bytecmd(intValue, addrValue);  
                                    }
                                    else 
                                        {WARNING_MSG("Il y a trop d'arguments.\n");
                                        return 1;}
                                }
                            else
                                {WARNING_MSG("La valeur à affecter en mémoire n'est pas un entier alors qu'elle devrait l'être.\n");
                                return 1;}
                        }
                        else
		                  {WARNING_MSG("La valeur à affecter en mémoire n'est pas précisée.\n");
                            return 1;}
		              } /* fin du get_type == WORD */

                    else /* si get_type(token)) ne renvoie pas WORD */
		              {WARNING_MSG("value %s is not a valid argument of command %s\n",token,"setcmd mem byte");
                          return 1;}
                  }
		         }

	    else if (!strcmp(token,"word")) /* commande entrée : set mem word ... */
		{
                while((token = get_next_token(inter))!=NULL && return_value==0)
                 {no_args_4=0;
                    if (get_type(token)==WORD) /* adresse non signée sur 32 bits */
		    {
                    {
			sscanf(token,"%u",&addrValue); /* met l'adresse non signée dans addrValue */
                        if ((token = get_next_token(inter))!=NULL)
                        {
                            if (get_type(token)==INTEGER) /* on vérifie que la valeur est un entier */
                                {
                                    if (get_next_token(inter)==NULL) /* la chaine de caractère est bien finie */
                                    {
                				    sscanf(token,"%u",&intValue);
                                    INFO_MSG("La commande set mem word <adresse> <valeur> est exécutée.\n");
                                    return_value= _set_mem_wordcmd(intValue, addrValue);
                                    }
                                    else 
                                        {WARNING_MSG("Il y a trop d'arguments.\n");
                                        return 1;}
                                }
                            else
                                {WARNING_MSG("La valeur à affecter en mémoire n'est pas un entier alors qu'elle devrait l'être.\n");
                                return 1;}
                        }
                        else
			{WARNING_MSG("La valeur à affecter en mémoire n'est pas précisée.\n");
                        return 1;}
	                }
		    } /* fin du case WORD */
                    else
		    {WARNING_MSG("value %s is not a valid argument of command %s\n",token,"setcmd mem word");
                    return 1;}
                 } /* fin du while */
	        } /* fin du cas "set mem word" */
	    else /* cas ou le token n'est ni word, ni byte après la commande set mem */
	    {WARNING_MSG("value %s is not a valid argument of command %s\n",token,"setcmd mem");
            return 1;}
	    } /* fin du while */
        } /* fin du cas "set mem" */
    else /* dans le cas où la commande entrée n'est pas set mem */
        {
        if(!strcmp(token,"reg")) /* commande entrée : set reg ... */
            {
            while((token = get_next_token(inter))!=NULL && return_value==0)
            {no_args_5=0;
                if ((token = get_next_token(inter))!=NULL)
                {
                    if (get_type(token)==REG) /* vérifie qu'on a bien un registre après la commande "set reg" */
                    {
                        copy_reg(token, regValue); /* copie le registre token dans regValue */
                        if ((token = get_next_token(inter))!=NULL)
                        {
                            if (get_type(token)==INTEGER) /* on vérifie que la valeur est un entier */
                                {
                                    if (get_next_token(inter)==NULL) /* la chaine de caractère est bien finie */
                                    {
				                    sscanf(token,"%u",&intValue);
                                    INFO_MSG("La commande set reg <registre> <valeur> est exécutée.\n");
                                    return_value= _set_regcmd(intValue, regValue);
                                    }
                                    else 
                                        {WARNING_MSG("Il y a trop d'arguments.\n");
                                        return 1;}
                                }
                            else
                            {WARNING_MSG("La valeur à affecter en mémoire n'est pas un entier alors qu'elle devrait l'être.\n");
                            return 1;}
                        }
                        else
			{WARNING_MSG("La valeur à affecter en mémoire n'est pas précisée.\n");
                        return 1;}
                    }
                    else
		    {WARNING_MSG("Le type attendu après 'set reg' est REG (un registre).\n");
                    return 1;}
                }
                else
		{WARNING_MSG("Un registre est attendu après la commande 'set reg'.\n");
                return 1;}
            } /* fin du while */
            } /* fin du strcmp reg */
        else /* cas où token n'est pas un caractère attendu */
            {WARNING_MSG("value %s is not a valid argument of command %s\n",token,"setcmd");
            return 1;}
	} /* fin du else dans le cas où la commande entrée n'est pas set mem */
    } /* fin de la boucle while initiale */

/* on teste le nombre d'argument pour chaque possibilité */
    if (no_args_1)
    {
        WARNING_MSG("no argument given to command %s\n","setcmd");
        return 1;
    }

    if (no_args_2)
    {
        WARNING_MSG("no argument given to command %s\n","setcmd mem");
        return 1;
    }

    if (no_args_3)
    {
        WARNING_MSG("no argument given to command %s\n","setcmd mem byte");
        return 1;
    }

    if (no_args_4)
    {
        WARNING_MSG("no argument given to command %s\n","setcmd mem word");
        return 1;
    }

    if (no_args_5)
    {
        WARNING_MSG("no argument given to command %s\n","setcmd reg");
        return 1;
    }

    return return_value; /* retourne 0 si la commande a bien été exécutée */
}


/** 
 * commande qui vérifie la valeur d'un segment mémoire ou d'un registre
 * @param inter l'interpreteur qui demande l'analyse
 * @param tab le tableau de registre
 * @return 0 si ça a fonctionné, 1 sinon
 */
int assertcmd(interpreteur inter, reg tab, mem vmem)
{   
    DEBUG_MSG("Commande assert entrée.\n");

    int s=0; int k;

/* on enregistre la chaine de caractère entrée dans l'interpréteur */
    char* token1;
	if ((token1=get_next_token(inter))==NULL) 
	{
	    WARNING_MSG("no argument given to command %s\n","assertcmd");
            return 1;
	}
/* on test si l'argument suivant assert est bien un des arguments attendus */
    if (strcmp(token1, "reg")!=0 || strcmp(token1, "reg")!=0 || strcmp(token1, "reg")!=0)
    {
        WARNING_MSG("argument given to command %s\n is not a valid argument","assertcmd");
        return 1; /* il manque des arguments -> on quitte la fonction */
    }

    char* token2;
	if ((token2=get_next_token(inter))==NULL)
	{
	   	if (strcmp(token1, "reg")==0)
		{
	    	    WARNING_MSG("no argument given to command %s\n","assertcmd reg");
            	    return 1; /* il manque des arguments -> on quitte la fonction */
		}
		if (strcmp(token1, "word")==0)
		{
	    	    WARNING_MSG("no argument given to command %s\n","assertcmd word");
            	    return 1; /* il manque des arguments -> on quitte la fonction */
		}
		if (strcmp(token1, "byte")==0)
		{
	    	    WARNING_MSG("no argument given to command %s\n","assertcmd byte");
            	    return 1; /* il manque des arguments -> on quitte la fonction */
		}
	}
    char* token3;
	if ((token3=get_next_token(inter))==NULL)
	{
/* gestion des erreurs à finir */ 		
	}
    char* token4;
	if ((token4=get_next_token(inter))==NULL)
	{
/* gestion des erreurs à finir */ 
	}

    if(token4!=NULL)
    {
/* gestion des erreurs à finir */
    }

if(strcmp(token1,"reg")==0)
{   DEBUG_MSG("Command assert_reg");

        if(is_register(token2)!=0)
        {
            if(is_integer(token3)!=0)
            {
    int i; int j=0;
    for (i=0; i<35; i++)
    {
	if(strcmp(token2,tab[i].name)==0 || strcmp(token2, tab[i].mnemo)==0) /* on recherche le registre "token2" */
	j=i; 
    }
                s=_assert_regcmd(tab+j, token3); //attention token3=chaine de caractère !! pas un entier, a
                return s;
            }  {WARNING_MSG("value %s is not a valid argument of command %s , expecting an integer\n",token3,"assert_reg"); return 1;}
        } {WARNING_MSG("value %s is not a valid argument of command %s , expecting a register's name\n",token2,"assert_reg"); return 1;}

}


else if(strcmp(token1, "word")==0)
{  DEBUG_MSG("Command assert_word");
    char* token2=get_next_token(inter);

        if(is_hexa(token2)!=0)
        {
            char*token3=get_next_token(inter);

            if(is_integer(token3)!=0)
            {
		sscanf(token3,"%u",&k);
                s=_assert_wordcmd(token2, k, vmem);
                return s;
            }  {WARNING_MSG("value %s is not a valid argument of command %s , expecting an integer\n",token3,"assert_word"); return 1;}
        } {WARNING_MSG("value %s is not a valid argument of command %s , expecting an adress\n",token2,"assert_word"); return 1;}

}


else if(strcmp(token1, "byte")==0)
{   DEBUG_MSG("Command assert_byte");
    char* token2=get_next_token(inter);

        if(is_hexa(token2)!=0)
        {
            char*token3=get_next_token(inter);

            if(is_integer(token3)!=0)
            {
		sscanf(token3,"%u",&k);
                s=_assert_bytecmd(token2, k, vmem);
                return s;
            }  {WARNING_MSG("value %s is not a valid argument of command %s , expecting an integer\n",token3,"assert_byte"); return 1;}
        }  {WARNING_MSG("value %s is not a valid argument of command %s , expecting an adress\n",token2,"assert_byte"); return 1;}

}
 {WARNING_MSG("wrong argument for command %s, expecting 'reg' or 'word' or 'byte\n","disp"); return 1;}
}


/** DISPCMD
 * commande qui affiche la valeur d'un segment mémoire, d'un registre, ou la carte mémoire
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 si celà a fonctionné, 1 sinon
 */
int dispcmd(interpreteur inter, reg tab_reg, mem vmem)
{
    int s=0;
    char* token1;
	if ((token1 = get_next_token(inter)) == NULL) 
	{
	    WARNING_MSG("no argument given to command %s\n","disp cmd");
            return 1;
	}
    char* token2;
	if ((token2 = get_next_token(inter)) == NULL) 
	{
	    WARNING_MSG("no argument given to command %s\n","disp cmd");
            return 1;
	}
    char* token3;
    if((token3 = get_next_token(inter)) != NULL)
    {
        WARNING_MSG("too many argument in this instruction %s\n","disp");
        return 1;
    }


if(strcmp(token1,"mem")==0)
{   DEBUG_MSG("Command disp_mem");

        if(is_hexa(token2)!=0)
        {       _disp_mem_plagescmd(token2, vmem);

            }
            else if(strcmp(token2,"map")==0)
                    {
                      _disp_mem_mapcmd(vmem);
                    }
 {WARNING_MSG("value %s is not a valid argument of command %s , expecting an adress\n",token2,"disp mem");
 return 1;}// manque le retour d'erreur si pas le bon type

}


else if(strcmp(token1, "reg")==0)
{    DEBUG_MSG("Command disp_reg");

        if(is_register(token2)!=0)
        {
            s=_disp_reg_registercmd(token2 ,tab_reg);
        return s;

        }
        {WARNING_MSG("value %s is not a valid argument of command %s , expecting a register\n",token3,"disp reg"); 
	return 1;}// manque le retour d'erreur si pas le bon type

}
	{
	WARNING_MSG("value %s is not a valid argument of command %s , expecting an adress\n",token1,"disp reg"); 
	return 1;
	}
}


/** RESUMECMD
 * commande qui reprend l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */
void resumecmd(interpreteur inter)
{
    DEBUG_MSG("Command resume");
    char* token1=get_next_token(inter);
    if(token1!=NULL)
    {
    	{
	WARNING_MSG("Too many argument in this command\n");
     	return;
	}
    }
	_resumecmd(inter);
}


/** DEBUGCMD
 * commande qui arrete l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */


void debugcmd(interpreteur inter)
{
    DEBUG_MSG("Command debug");
    char* token1=get_next_token(inter);
	if(token1!=NULL)
	{
    	    {
		WARNING_MSG("Too many argument in this command\n");
		return;
            }
	}
	_debugcmd(inter);
}

