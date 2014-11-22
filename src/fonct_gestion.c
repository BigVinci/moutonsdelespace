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
  char       *delim = " \t"; /* chaque terme est separe par un espace */

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
 * test si un token est une valeur hexa
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


/**
 * test si la chaine de caractère est un octet
 *@param chaine le token à analyser
 *@return 0 si non-byte, non null autrement
 */
int is_byte(char* chaine)
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


/**
 * test si la chaine de caractère est un word (32 bits)
 * @param chaine le token à analyser
 * @return 0 si non-word, non null autrement
 */
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


/**
 * test si la chaine de caractère est un entier
 *@param chaine le token à analyser
 *@return 0 si non-integer, non null autrement
 */
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


/**
 * test si la chaine de caractère est un fichier objet ELF
 *@param chaine le token à analyser
 *@return 0 si non-elf, non null autrement
 */
int is_elf(char* chaine)
{	int l;
	l=strlen(chaine);

return (chaine[l-2]=='.' && chaine[l-1]=='o' && chaine[l]=='\0');

}


/**
 * test si la chaine de caractère est un registre
 *@param chaine le token à analyser
 *@return 0 si non-reg, non null autrement
 */
int is_register(char* chaine)
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
		k++;
		}
    }
    return( chaine!=NULL && k==1 && chaine[l]=='\0');
}



/**
 * retourne le type du token
 * @param chaine le token à analyser
 * @return 0 si la le type de la chaine ne correspond pas
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
    else if (is_register(chaine))
    	return REG; 
    else if (is_elf(chaine))
    	return ELF;
    return UNKNOWN;
}



/**
 * @brief parse la chaine courante de l'interpreteur a la recherche d'une commande, et execute cette commande.
 * @param inter l'interpreteur qui demande l'analyse
 * 
 * @return CMD_OK_RETURN_VALUE si la commande s'est executee avec succes (0)
 * @return CMD_EXIT_RETURN_VALUE si c'est la commande exit. Dans ce cas, le programme doit se terminer. (-1)
 * @return CMD_UNKOWN_RETURN_VALUE si la commande n'est pas reconnue. (-2)
 * @return tout autre nombre (eg tout nombre positif) si erreur d'execution de la commande
 */
int execute_cmd(interpreteur inter, reg* tabreg, mem* vmem, FILE* fp)
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
    	return loadcmd(inter, vmem);
    }

    /* test si la commande est disp */
    else if(strcmp(token, "disp") == 0)
    {
    	return dispcmd(inter, tabreg, *vmem );
    }

    /* test si la commande est disasm */
    else if(strcmp(token, "disasm") == 0)
    {
    	return disasmcmd(inter, *vmem, tabreg);
    }

    /* test si la commande est set */
    else if(strcmp(token, "set") == 0)
    {
    	return setcmd(inter, tabreg, *vmem);
    }

    /* test si la commande est assert */
    else if(strcmp(token, "assert") == 0)
    {
    	return assertcmd(inter, tabreg, *vmem);
    }

    /* test si la commande est resume */
    else if(strcmp(token, "resume") == 0)
    {
    	resumecmd(inter, fp);
    	return CMD_OK_RETURN_VALUE;
    }

    /* test si la commande est debug */
    else if(strcmp(token, "debug") == 0)
    {
    	debugcmd(inter, fp);
    	return CMD_OK_RETURN_VALUE;
    }

    /* test si la commande est debug */
    else if(strcmp(token, "run") == 0)
    {
    	return runcmd(inter, tabreg, *vmem);
    }

    /* test si la commande est debug */
    else if(strcmp(token, "step") == 0)
    {
    	return stepcmd(inter, tabreg, *vmem);
    }

    /* test si la commande est debug */
    else if(strcmp(token, "break") == 0)
    {
    	return breakcmd(inter, tabreg, *vmem);
    }

    /* si aucune commande n'est reconnue */
    WARNING_MSG("Unknown Command : '%s'", cmdStr);
    return CMD_UNKOWN_RETURN_VALUE;
}



/*************************************************************\
Les commandes de l'émulateur.

 Dans cette version, douze commandes :
    "test" qui attend un nombre strictement positifs d'hexa strictement positifs et affiche ce(s) nombre() +1 dans le terminal
    "exit" qui quitte l'émulateur
    "load" qui charge un fichier objet ELF .o (laod.c)
    "disp" qui affiche (des éléments de) la mémoire ou de(s) registre(s)
    "disasm" qui affiche les instructions présentes dans la plage de données précisée (incluses dans .text) (disasm.c)
    "set" qui modifie la valeur d'une adresse mémoire ou d'un registre
    "assert" qui compare une valeur avec la valeur d'une adresse mémoire ou celle d'un registre
    "resume" qui repasse au mode SCRIPT après être arrivé en mode INTERACTIF à l'aide de debug
    "debug" qui permet de sortir du mode SCRIPT afin d'être en mode INTERACTIF

    "run" qui
    "step" qui
    "break" qui

 \*************************************************************/



/**
 * TESTCMD
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
            WARNING_MSG("value %s is not a valid argument of command %s",token,"testcmd");
            return 1;
        }
    }


    if(no_args)
	{
            WARNING_MSG("no argument given to command %s","testcmd");
            return 1;
        }


    return return_value;
}


/**
 * EXITCMD
 * commande exit qui ne necessite pas d'analyse syntaxique
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en case de succes, un nombre positif sinon
 */
int exitcmd(interpreteur inter) {
    INFO_MSG("Bye bye !");
    return CMD_EXIT_RETURN_VALUE; 
}


/**
 * LOADCMD
 * commande qui alloue la mémoire et charge un fichier .elf en mémoire
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en cas de succes, un nombre positif sinon
 */
int loadcmd(interpreteur inter, mem* vmem)
{
    DEBUG_MSG("Chaine en entrée : %s", inter->input);
    int no_args=1; /* permet de tester s'il manque un argument dans la boucle while suivante */
    char* token=NULL; char* token2=NULL;

    /* la boucle permet d'executer la commande de manière recurrente*/
    while((token = get_next_token(inter))!=NULL) /* token reçoit le nom du fichier objet ELF à charger */
    {
    no_args=0; /* il y a un argument puisque token != NULL */

        if ((token2=get_next_token(inter))!=NULL) /* si il y a trop d'arguments */ 
        {
            if (get_type(token2)!=HEXA)
            {
                WARNING_MSG("Il y a trop d'arguments pour la commande %s","load");
                return 1;
            }
        }

        /* la commande load attend un fichier objet ELF */
        if(is_elf(token)) /* on vérifie qu'il s'agit bien d'un fichier objet ELF */
        {
            DEBUG_MSG("Commande load entrée");
            *vmem = load(token, token2);
            return CMD_OK_RETURN_VALUE;
        }
        else /* si le token n'est pas un fichier objet ELF */
        {
            WARNING_MSG("Value %s is not a valid argument of command %s. Un fichier objet ELF est attendu",token,"load");
            return 1;
        }
    } /* fin du while */

    if (no_args==1) /* si aucun fichier n'est indiqué après la fonction load */
    {
        WARNING_MSG("no argument given to command %s","load");
        return 1;
    }
    ERROR_MSG("SHOULD NEVER BE HERE\n");
    return CMD_EXIT_RETURN_VALUE;
}




/** 
 * DISASMCMD
 * commande qui affiche le code assembleur
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en cas de succes, un nombre positif sinon
 */
int disasmcmd(interpreteur inter, mem vmem, reg* tab_reg)    
{
    int i=0;

    if (vmem==NULL) 
    {
	WARNING_MSG("You have to load a memory");
        return 1;
    }

    char* token1; char* token2; char* token3;
    if((token1=get_next_token(inter)) == NULL || (token2=get_next_token(inter))== NULL || (token3=get_next_token(inter))== NULL) /* on vérifie que la plage est indiqué pour disp mem */
    {
        WARNING_MSG("Vous devez indiquer la plage de donnée que vous souhaitez visualiser avec la commande %s","disasm");
        return 1;
    }

    int offsetValue;     // argment int (offset) 

    if (strcmp(token2,":")==0 && get_type(token1)==HEXA && get_type(token3)==HEXA) /* range avec deux adresses */
    {
        INFO_MSG("La commande disasm %s : %s est exécutée", token1, token3);
        i=_disasm_range_hexacmd(token1, token3, vmem, tab_reg);

        if (i==0) // on vérifie qu'il n'y a pas une erreur
        while ((token1=get_next_token(inter))!=NULL && (token2=get_next_token(inter))!=NULL && (token3=get_next_token(inter))!=NULL)
        {
            if (get_type(token1)==HEXA && strcmp(token2,":")==0 && get_type(token3)==HEXA)
                i+=_disasm_range_hexacmd(token1, token3, vmem, tab_reg); 
            else 
            {
                WARNING_MSG("%s %s %s are not valid argument of command %s , expecting 'hexa : hexa' !", token1, token2, token3, "disasm");
                return 1;
            }
        }

        return i;
    }

    else if (strcmp(token2,"+")==0 && get_type(token1)==HEXA && get_type(token3)==INTEGER) /* range avec offset */
    {
        sscanf(token3,"%d",&offsetValue);
        INFO_MSG("La commande disasm %s + %s est exécutée", token1, token3);
        i=_disasm_range_offsetcmd(token1, offsetValue, vmem, tab_reg);

        if (i==0) // on vérifie qu'il n'y a pas une erreur
        while ((token1=get_next_token(inter))!=NULL && (token2=get_next_token(inter))!=NULL && (token3=get_next_token(inter))!=NULL)
        {
            if (get_type(token1)==HEXA && strcmp(token2,"+")==0 && get_type(token3)==INTEGER)
            {
                sscanf(token3,"%d",&offsetValue);
                i+=_disasm_range_offsetcmd(token1, offsetValue, vmem, tab_reg);
            }
            else 
            {
                WARNING_MSG("%s %s %s are not valid argument of command %s , expecting 'hexa : hexa' !", token1, token2, token3, "disasm");
                return 1;
            }
        }

        return i;
    }

    else
    {
        WARNING_MSG("La plage de données doit être 'hexa : hexa' ou 'hexa + offset' pour lancer la commande %s","disasm");
        return 1;
    }
}


/** 
 * SETCMD
 * commande qui modifie une valeur en mémoire ou un registre
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 en cas de succes, un nombre positif sinon
 */
int setcmd(interpreteur inter, reg* tabreg, mem vmem)
{
    if (vmem==NULL) 
    {
	WARNING_MSG("You have to load a memory");
        return 1;
    }

    DEBUG_MSG("Chaine en entrée : %s", inter->input);
    char* token1=NULL; char* token2=NULL; char* token3=NULL; char* token4=NULL; char* token5=NULL;

    /* la commande set permet d'affecter une valeur integer à une adresse non signée sur 32 bits ou à un registre */
    unsigned int addrValue;  /* argument uint32_t (adresse) */
    unsigned int intValue;   /* valeur sur 8 ou 32 bits */
    reg regValue=NULL;       /* argument registre */

    if ((token1=get_next_token(inter))==NULL)
    {
	WARNING_MSG("You have to indicate a valid argument for the command %s, expecting reg or mem","set");
        return 1;
    }

    if (strcmp(token1,"mem")!=0 && strcmp(token1,"reg")!=0) // test de token 
    {
	WARNING_MSG("You have to indicate a valid argument for the command %s, expecting reg or mem","set");
        return 1;
    }

    if ((token2=get_next_token(inter))==NULL) // test de token1
    {
	WARNING_MSG("You have to indicate a valid argument for the command %s %s, expecting a register (reg) or byte or word (mem)","set", token1);
        return 1;
    }

    if (strcmp(token2,"byte")!=0 && strcmp(token2,"word")!=0 && get_type(token2)!=REG) // test du type de token1
    {
	WARNING_MSG("You have to indicate a valid argument for the command %s %s, expecting a register (reg) or 'byte' or 'word' (mem)","set", token1);
        return 1;
    }

    if ((token3=get_next_token(inter))==NULL) // test de token2
    {
	WARNING_MSG("You have to indicate a valid argument (integer or hexa) for the command %s %s %s","set", token1, token2);
        return 1;
    }

    if ((token4=get_next_token(inter))==NULL && strcmp(token1,"mem")==0 && get_type(token3)==HEXA) // on vérifie le nombre d'arguments pour "mem"
    {
	WARNING_MSG("You have to indicate a valid argument (integer) for the command %s %s %s %s","set", token1, token2, token3);
        return 1;
    }

    if (token4==NULL && strcmp(token1,"mem")==0 && get_type(token3)!=HEXA) // on vérifie le nombre d'arguments pour "mem"
    {
	WARNING_MSG("You have to indicate a valid argument (hexa) for the command %s %s %s ","set", token1, token2);
        return 1;
    }


    if (token4!=NULL && strcmp(token1,"mem")!=0) // on vérifie le nombre d'arguments pour "reg"
    {
	WARNING_MSG("Too many arguments for the command %s %s %s %s","set", token1, token2, token3);
        return 1;
    }

    if ((token5=get_next_token(inter))!=NULL && strcmp(token1,"mem")==0) // on vérifie le nombre d'arguments pour "mem"
    {
	WARNING_MSG("Too many arguments for the command %s %s %s %s %s","set", token1, token2, token3, token4);
        return 1;
    }

    if (strcmp(token1,"mem")==0 && get_type(token4)!=INTEGER) // on vérifie le type de token4
    {
	WARNING_MSG("Expecting an integer for the command %s %s %s %s","set", token1, token2, token3);
        return 1;
    }

    if (get_type(token3)!=HEXA && strcmp(token1,"mem")==0) // on vérifie le type d'argment pour mem
    {
	WARNING_MSG("Expecting an hexa for the command %s %s %s","set", token1, token2);
        return 1;
    }

    if (get_type(token3)!=INTEGER && strcmp(token1,"reg")==0) // on vérifie le type d'argment pour reg
    {
	WARNING_MSG("Expecting an integer for the command %s %s %s","set", token1, token2);
        return 1;
    }

// début de la lecture 
    if (strcmp(token1,"mem")==0 && strcmp(token2,"byte")==0 && get_type(token3)==HEXA && get_type(token4)==INTEGER)
    {
	DEBUG_MSG("Commande set mem byte entrée");
	sscanf(token3,"%x",&addrValue); // met l'adresse non signée dans addrValue : passe du type hexa au type uint32_t 
	sscanf(token4,"%d",&intValue);  // on met la valeur de token dans intValue 
	INFO_MSG("La commande set mem byte <adresse> %u est exécutée", intValue);
	return _set_mem_bytecmd(intValue, addrValue, vmem); 
    }

    else if (strcmp(token1,"mem")==0 && strcmp(token2,"word")==0 && get_type(token3)==HEXA && get_type(token4)==INTEGER)
    {
	DEBUG_MSG("Commande set mem word entrée");
	sscanf(token3,"%x",&addrValue);  // met l'adresse non signée dans addrValue : passe du type hexa au type uint32_t 
	sscanf(token4,"%d",&intValue);   // on met la valeur de token dans intValue 
	INFO_MSG("La commande set mem word <adresse> %u est exécutée", intValue);
	return _set_mem_wordcmd(intValue, addrValue, vmem); 
    }

    else if (strcmp(token1,"reg")==0 && get_type(token2)==REG && get_type(token3)==INTEGER)
    {
	DEBUG_MSG("Commande set reg entrée");
	regValue = to_reg(token2);     // copie le registre token dans regValue
	sscanf(token3,"%u",&intValue); // on met la valeur de token dans intValue
	INFO_MSG("La commande set reg %s %d est exécutée", token2, intValue);
	return _set_regcmd(intValue, regValue, tabreg);
    }
// fin de la lecture

    ERROR_MSG("SHOULD NEVER BE HERE");
    return CMD_EXIT_RETURN_VALUE;
}

/** 
 * ASSERTCMD
 * commande qui vérifie la valeur d'un segment mémoire ou d'un registre
 * @param inter l'interpreteur qui demande l'analyse
 * @param tab le tableau de registre
 * @return 0 si ça a fonctionné, 1 sinon
 */
int assertcmd(interpreteur inter, reg* tab, mem vmem)
{   
    if (vmem==NULL) 
    {
	WARNING_MSG("You have to load a memory");
        return 1;
    }

    DEBUG_MSG("Chaine en entrée : %s", inter->input);

    unsigned int k; int i; int j=0;
    uint32_t addrValue; /* argument uint32_t (adresse) */

/* on enregistre la chaine de caractère entrée dans l'interpréteur */
    char* token1;
	if ((token1=get_next_token(inter))==NULL) 
	{
	    WARNING_MSG("no argument given to command %s, expecting 'reg' , 'word' or 'byte'","assertcmd");
        return 1;
	}
/* on test si l'argument suivant assert est bien un des arguments attendus */
    	if (strcmp(token1, "reg")!=0 && strcmp(token1, "word")!=0 && strcmp(token1, "byte")!=0)
    	{
        WARNING_MSG("argument given to command %s is not a valid argument, expecting 'reg', 'word' or 'byte'","assertcmd");
        return 1; /* il manque des arguments -> on quitte la fonction */
    	}

    char* token2;
	if ((token2=get_next_token(inter))==NULL)
	{
	WARNING_MSG("argument given to command %s is not a valid argument, expecting a register or an hexa","assertcmd");
        return 1; /* il manque des arguments -> on quitte la fonction */
	}

	if (get_type(token2)!=REG && get_type(token2)!=HEXA)
	{
        WARNING_MSG("argument given to command %s %s is not a valid argument, expecting a register or an hexa","assertcmd", token1);
        return 1; /* il manque des arguments -> on quitte la fonction */		
	}

    char* token3;
	if ((token3=get_next_token(inter))==NULL)
	{
        WARNING_MSG("no argument given to command %s %s %s, expecting a value (integer, 8bits, or 32bits)","assertcmd", token1, token2);
        return 1; /* il manque des arguments -> on quitte la fonction */		
	}

    char* token4=NULL;
	if ((token4=get_next_token(inter))!=NULL)
	{
        WARNING_MSG("Too many arguments given to command %s %s %s %s","assertcmd", token1, token2, token3);
        return 1; /* il y a trop d'arguments -> on quitte la fonction */
	}


if(strcmp(token1,"reg")==0) /* L'interpréteur a reçu "assert reg" */
{   DEBUG_MSG("Command assert_reg");

        if(get_type(token2)==REG) /* on vérifie que le token2 représente un registre */
        {
            if(get_type(token3)==INTEGER) /* on vérifie que le token3 représente un entier */
            {
              for (i=0; i<35; i++) /* on parcourt l'ensemble des registre */
                {
	               if(strcmp(token2,tab[i]->name)==0 || strcmp(token2, tab[i]->mnemo)==0) /* on recherche le registre "token2" */
	               j=i; /* le registre token2 est le ième registre */
                }
            sscanf(token3,"%u",&k); /* met la valeur de token3 dans k */
            INFO_MSG("La commande assert reg <registre> <valeur> est exécutée");
            return _assert_regcmd(tab[j], k);
            }  
          {WARNING_MSG("value %s is not a valid argument of command %s , expecting an integer",token3,"assert_reg <registre>"); return 1;}
        } 
    {WARNING_MSG("value %s is not a valid argument of command %s , expecting a register's name",token2,"assert_reg"); return 1;}

}


else if(strcmp(token1, "word")==0)
{  DEBUG_MSG("Command assert_word");

        if(get_type(token2)==HEXA) /* on vérifie que le token2 représente une adresse */
        {
            sscanf(token2,"%x",&addrValue);
            if(get_type(token3)==INTEGER) /* on vérifie que le token3 représente un entier  */
            {
		        sscanf(token3,"%u",&k); /* k prend la valeur indiquée par token3 */
                INFO_MSG("La commande assert word 0x%x %u est exécutée", addrValue, k);
                return _assert_wordcmd(addrValue, k, vmem);
            }  {WARNING_MSG("value %s is not a valid argument of command %s , expecting an integer 32 bits",token3,"assert_word <adresse>"); return 1;}
        } {WARNING_MSG("value %s is not a valid argument of command %s , expecting an adress",token2,"assert_word"); return 1;}

}


else if(strcmp(token1, "byte")==0)
{   
    DEBUG_MSG("Command assert_byte");
        if(get_type(token2)==HEXA) /* on vérifie que le token2 représente une adresse */
        {
            sscanf(token2,"%x",&addrValue);
            if(get_type(token3)==INTEGER) /* on vérifie que le token3 représente un entier */
            {
		sscanf(token3,"%u",&k); /* k prend la valeur indiquée par token3 */
                INFO_MSG("La commande assert byte 0x%x %u est exécutée", addrValue, k);
                return _assert_bytecmd(addrValue, k, vmem);
            }  
          {WARNING_MSG("value %s is not a valid argument of command %s , expecting an integer 8bits ",token3,"assert_byte <adresse>"); return 1;}
        } 
      {WARNING_MSG("value %s is not a valid argument of command %s , expecting an adress",token2,"assert_byte"); return 1;}

}
else 
 {WARNING_MSG("wrong argument for command %s, expecting 'reg' or 'word' or 'byte","assert cmd"); return 1;}
}


/** 
 * DISPCMD
 * commande qui affiche la valeur d'un segment mémoire, d'un registre, ou la carte mémoire
 * @param inter l'interpreteur qui demande l'analyse
 * @return 0 si celà a fonctionné, 1 sinon
 */
int dispcmd(interpreteur inter, reg* tab_reg, mem vmem)
{
    int i=0;

    if (vmem==NULL) 
    {
        WARNING_MSG("You have to load a memory");
        return 1;
    }

    char* token1=NULL;
	if ((token1 = get_next_token(inter)) == NULL) /* on attend soit "mem" soit "reg" */
	{
	    WARNING_MSG("no argument given to command %s, expecting mem or reg","disp cmd");
        return 1;
	}

	if (strcmp(token1,"reg")!=0 && strcmp(token1,"mem")!=0) // si token1 n'est pas "mem" ou "reg"
	{
	    WARNING_MSG("value %s is not a valid argument of command %s, expecting mem or reg",token1, "disp cmd");
        return 1;
	}

    char* token2=NULL; // contient un hexa pour mem et un registre ou all pour reg
	if ((token2 = get_next_token(inter)) == NULL && (strcmp(token1,"reg")==0 || strcmp(token1,"mem")==0) ) 
	{
	    WARNING_MSG("no argument given to command %s %s, expecting map or a range of address for mem, all or a register for reg", "disp cmd", token1);
        return 1;
	}

    char* token3=NULL; token3=get_next_token(inter);
    char* token4=NULL; if (token3 != NULL) token4=get_next_token(inter);
    if(strcmp(token1,"mem")==0 && strcmp(token2,"map")!=0)
    {
	if (get_type(token2)!=HEXA) 
	    {WARNING_MSG("Expecting an hexa to the command %s","disp mem"); return 1;}

	else if (token3==NULL || strcmp(token3, ":")!=0) 
	{
        if (strcmp(token3, "+")!=0)
        {
            WARNING_MSG("Expecting a range of address, but there isn't ':' after %s", token2); 
            return 1;
        }
    }

	else if (token4== NULL || (get_type(token4)!=HEXA && get_type(token4)!=INTEGER))
	    {WARNING_MSG("Expecting a range of address (hexa) after %s %s", token1, token2); return 1;}
    }

    else if (token3!=NULL && get_type(token3)!=REG) // s'il ne doit pas y avoir de plage de donnée, on vérifie qu'il n'y a rien d'autre
    {
        WARNING_MSG("too many argument in this instruction %s","disp cmd");
        return 1;
    }

    int offsetValue; // argument int (offset) 

    if(strcmp(token1,"mem")==0) // La commande entrée est disp mem ... 
    {   
        DEBUG_MSG("Command disp_mem");
        if(get_type(token2)==HEXA && strcmp(token3,":")==0 && get_type(token4)==HEXA) // on test si token2 est un hexa, ie une adresse 
        {       
            INFO_MSG("La commande disp mem %s : %s est exécutée", token2, token4);
            i=_disp_mem_plagescmd(token2, token4, vmem); // on exécute la commande avec les deux adresses indiquées 

            if (i==0) // on vérifie qu'il n'y a pas une erreur
            while ((token2=get_next_token(inter))!=NULL && (token3=get_next_token(inter))!=NULL && (token4=get_next_token(inter))!=NULL)
            {
                if (get_type(token2)==HEXA && strcmp(token3,":")==0 && get_type(token4)==HEXA)
                    i+=_disp_mem_plagescmd(token2, token4, vmem); 
                else 
                {
                    WARNING_MSG("%s %s %s are not valid argument of command %s , expecting 'hexa : hexa' !", token2, token3, token4, "disp mem");
                    return 1;
                }
            }

            return i;
        }

        else if(get_type(token2)==HEXA && strcmp(token3,"+")==0 && get_type(token4)==INTEGER) // on test si token2 est un hexa, ie une adresse
        {       
            sscanf(token4,"%d",&offsetValue);
            INFO_MSG("La commande disp mem %s + %s est exécutée", token2, token4);
            i=_disp_mem_offsetcmd(token2, offsetValue, vmem); // on exécute la commande avec les deux adresses indiquées

            if (i==0) // on vérifie qu'il n'y a pas une erreur
            while ((token2=get_next_token(inter))!=NULL && (token3=get_next_token(inter))!=NULL && (token4=get_next_token(inter))!=NULL)
            {
                if (get_type(token2)==HEXA && strcmp(token3,"+")==0 && get_type(token4)==INTEGER)
                {
                    sscanf(token4,"%d",&offsetValue);
                    i+=_disp_mem_offsetcmd(token2, offsetValue, vmem); 
                }
                else 
                {
                    WARNING_MSG("%s %s %s are not valid argument of command %s , expecting 'hexa + integer' !", token2, token3, token4, "disp mem");
                    return 1;
                }
            }

            return i;
        }

        else if(strcmp(token2,"map")==0) // on test si token2 est "map" 
        {
            INFO_MSG("La commande disp mem map est exécutée");
            return _disp_mem_mapcmd(vmem);
        }

        else // si token1 n'est pas un des arguments attendus
        {
            WARNING_MSG("value %s is not a valid argument of command %s, expecting a range of adress or map", token2, "disp mem");
            return 1;
        }

    }

    else if(strcmp(token1, "reg")==0) /* La commande entrée est disp reg ... */
    {    
        DEBUG_MSG("Command disp_reg");

        if(get_type(token2)==REG)
        {
            INFO_MSG("La commande disp reg %s est exécutée", token2);
            i=_disp_reg_registercmd(token2 ,tab_reg);

	    if (token3!=NULL)
	    {
		if(get_type(token3)==REG)
		i+=_disp_reg_registercmd(token3 ,tab_reg);
		else
		{
                    WARNING_MSG("%s is not a valid argument of command %s, expecting a register !", token3, "disp reg");
                    return 1;
		}
	    }

	    if (token4!=NULL)
	    {
		if(get_type(token4)==REG)
		i+=_disp_reg_registercmd(token4 ,tab_reg);
		else
		{
                    WARNING_MSG("%s is not a valid argument of command %s, expecting a register !", token4, "disp reg");
                    return 1;
		}
	    }

            if (i==0)
            while((token2=get_next_token(inter))!=NULL && token3!=NULL && token4!=NULL)
            {
                if(get_type(token2)==REG)
                    i+=_disp_reg_registercmd(token2 ,tab_reg);
                else 
                {
                    WARNING_MSG("%s is not a valid argument of command %s, expecting a register !", token2, "disp reg");
                    return 1;
                }
            }    
	    return i;
        }

	else if (strcmp(token2, "all")==0)
	{
	    INFO_MSG("La commande disp reg %s est exécutée", token2);
	    return _disp_reg_allcmd(tab_reg);
	}

        else
        {
            WARNING_MSG("value %s is not a valid argument of command %s, expecting a register",token3,"disp reg"); 
            return 1;
        }

    }

    else
	{
	WARNING_MSG("value %s is not a valid argument of command %s, expecting mem or reg",token1,"disp cmd"); 
	return 1;
	}
    ERROR_MSG("SHOULD NEVER BE HERE\n");
    return CMD_EXIT_RETURN_VALUE;
}


/** 
 * RESUMECMD
 * commande qui reprend l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */
void resumecmd(interpreteur inter, FILE* fp)
{
    DEBUG_MSG("Command resume");
    char* token1=get_next_token(inter);
    if(token1!=NULL)
    {
    	{
	    WARNING_MSG("Too many argument in this command");
     	return;
	    }
    }
	_resumecmd(inter, fp);
	return;
}


/** 
 * DEBUGCMD
 * commande qui arrete l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */
void debugcmd(interpreteur inter, FILE* fp)
{
    DEBUG_MSG("Command debug");
    char* token1=get_next_token(inter);
	if(token1!=NULL)
	{
    	{
		  WARNING_MSG("Too many argument in this command");
		  return;
        }
	}

	_debugcmd(inter, fp);
	return;
}

/** 
 * BREAKCMD
 * commande qui met un point d'arrêt à une ou plusieurs adresses
 * @param inter l'interpreteur qui demande l'analyse et qui contient la liste de breakpoint
 * @param tab_reg le tableau de registres dont PC
 * @param vmem la mémoire contenant le code assembleur (dans .text)
 * @return 0 si réussi, 1 si fail
 */
int breakcmd( interpreteur inter, reg* tab_reg, mem vmem)
{
    if (vmem==NULL) 
    {
    WARNING_MSG("You have to load a memory");
        return 1;
    }
    
    DEBUG_MSG("Command break");
    char* token1=get_next_token(inter); char* token2=NULL;
    int address=0;
    unsigned int BP;

    if (token1==NULL)
    {
        WARNING_MSG("no argument given to command %s, expecting 'add' , 'del' or 'list'","break");
        return 1;
    }

    if (strcmp(token1, "add")==0)
    {
        while ((token2=get_next_token(inter))!=NULL)
        {
            address=1;

            if (get_type(token2)!=HEXA) // on vérifie que l'on a bien une adresse
            {
                WARNING_MSG("%s if not a valid argument to command %s %s, expecting an address",token2, "break", token1);
                return 1;  
            }

            sscanf(token2, "%x", &BP);
            *(inter->BP)=add_bp(*(inter->BP), BP); // on rajoute chaque élément précisé
        }

        if (address==0) // s'il n'y a aucun argument après "add"
        {
            WARNING_MSG("no argument given to command %s %s, expecting an address","break", token1);
            return 1;  
        }

        return CMD_OK_RETURN_VALUE;
    }

    else if (strcmp(token1, "del")==0)
    {
        while ((token2=get_next_token(inter))!=NULL)
        {
            address=1;

            if (get_type(token2)!=HEXA && strcmp(token2, "all")!=0) // on vérifie que l'on a bien une adresse ou le mot "all"
            {
                WARNING_MSG("%s if not a valid argument to command %s %s, expecting an address or 'all' ",token2, "break", token1);
                return 1;  
            }

            if (strcmp(token2, "all")==0) // si la commande entrée est break del all
            {
                INFO_MSG("Suppression de tous les breakpoints");
                *(inter->BP)=suppr_liste(*(inter->BP)); // on supprime tous les breakpoints
            }
            else if (get_type(token2)==HEXA)
            {
                sscanf(token2, "%x", &BP);
                *(inter->BP)=suppr_bp(*(inter->BP), BP); // on supprime chaque élément précisé
            }
        }

        if (address==0) // s'il n'y a aucun argument après "add"
        {
            WARNING_MSG("no argument given to command %s %s, expecting an address or 'all' ","break", token1);
            return 1;  
        }

        return CMD_OK_RETURN_VALUE;
    }

    else if (strcmp(token1, "list")==0)
    {
        if((token2=get_next_token(inter))!=NULL)
        {
            WARNING_MSG("Too many arguments given to command %s %s","break", token1);
            return 1; 
        }

        disp_bp(*(inter->BP));
        return CMD_OK_RETURN_VALUE;
    }

    else
    {
        WARNING_MSG("Wrong argument to command %s","break");
        return 1;
    }

    WARNING_MSG("Should never be here");
    return 1;
}


/** 
 * STEPCMD
 * commande qui provoque l'exécution d'une ou plusieurs instructions après avoir ajouté un breakpoint
 * @param inter l'interpreteur qui demande l'analyse et qui contient la liste de breakpoint
 * @param tab_reg le tableau de registres dont PC
 * @param vmem la mémoire contenant le code assembleur (dans .text)
 * @return 0 si réussi, 1 si fail
 */
int stepcmd( interpreteur inter, reg* tab_reg, mem vmem)
{
    if (vmem==NULL) 
    {
    WARNING_MSG("You have to load a memory");
        return 1;
    }

    int a;
    sscanf(tab_reg[32]->data, "%d", &a);
    if (a<(vmem->seg[0].start._32) || a>(vmem->seg[0].start._32+vmem->seg[0].size._32)) 
    {
        char* data_start=strdup("Initialisation");
	INFO_MSG("Le PC est réinitialisé au début du segment .text car sa valeur courante n'appartient pas à ce segment");
        sprintf(data_start, "%x", vmem->seg[0].start._32);
        tab_reg[32]->data=data_start; // on initialise PC au début du point .text si il n'a pas encore été initialisé
    }

    DEBUG_MSG("Command step");
    char* token1=get_next_token(inter);
    char* token2=NULL;

    if (token1==NULL) // instruction STEP
    {
        return _machine_statecmd("step", tab_reg[32]->data, inter->BP, tab_reg, vmem);
    }

    else 
    {
        if((token2=get_next_token(inter))!=NULL || strcmp(token1, "into")!=0)
        {
            WARNING_MSG("Too many arguments to the command STEP (INTO)");
            return 1;
        }

        else if (strcmp(token1, "into")==0) // instruction STEP INTO
        {
            WARNING_MSG("Fonction non implémentée. Exécution de la fonction STEP");
            return _machine_statecmd("step", tab_reg[32]->data, inter->BP, tab_reg, vmem);
        }
    }

    WARNING_MSG("Should never be here");
    return 1;
}


/** 
 * RUNCMD
 * commande qui lance le microprocesseur après avoir chargé PC 
 * @param inter l'interpreteur qui demande l'analyse et qui contient la liste de breakpoint
 * @param tab_reg le tableau de registres dont PC
 * @param vmem la mémoire contenant le code assembleur (dans .text)
 * @return 0 si réussi, 1 si fail
 */
int runcmd( interpreteur inter, reg* tab_reg, mem vmem)
{
    if (vmem==NULL) 
    {
    WARNING_MSG("You have to load a memory");
        return 1;
    }

    DEBUG_MSG("Command run");
    char* token1=get_next_token(inter);
    char* token2=NULL;

    int a;
    sscanf(tab_reg[32]->data, "%d", &a);
    char* data_start=strdup("Initialisation");
    if (a<(vmem->seg[0].start._32) || a>(vmem->seg[0].start._32+vmem->seg[0].size._32)) 
    {
	INFO_MSG("Le PC est réinitialisé au début du segment .text car sa valeur courante n'appartient pas à ce segment");
        sprintf(data_start, "%x", vmem->seg[0].start._32);
        tab_reg[32]->data=data_start; // on initialise PC au début du point .text si il n'a pas encore été initialisé
    }

    if ((a%4)!=a) 
    {
	a-=(a%4);
        sprintf(data_start, "%x", a);
        tab_reg[32]->data=data_start; // on initialise PC au début du point .text si il n'a pas encore été initialisé
    }

    if (token1==NULL) // si l'adresse est omise, on démarre à l'adresse courante du PC
    {
	   return _machine_statecmd("run", tab_reg[32]->data, inter->BP, tab_reg, vmem);
    }

    if ((token2=get_next_token(inter))!=NULL) // on vérifie qu'il n'y ait pas trop d'arguments
    {
	   WARNING_MSG("Too many arguments givent to command %s %s","run", token1);
	   return 1;
    }

    if (get_type(token1)!=HEXA)
    {
	   WARNING_MSG("%s is not a valid argument for %s, expecting an adress",token1, "run cmd");
	   return 1;
    }

    unsigned int addr_start; sscanf(token1, "%x", &addr_start);
    if (addr_start<vmem->seg[0].start._32) // si l'adresse de départ est avant le début de la section .text
    {
        INFO_MSG("L'adresse de départ ne sera pas %s mais %x",token1, vmem->seg[0].start._32);
        addr_start=vmem->seg[0].start._32;
        sprintf(token1, "%x", addr_start); // on modifie token1 en conséquence
    }

    if (addr_start>(vmem->seg[0].start._32+vmem->seg[0].size._32))
    {
        WARNING_MSG("L'adresse de départ est trop grande");
        return 1;
    }

    tab_reg[32]->data=token1; // on initialise PC à la valeur précisée par l'utilisateur
    return _machine_statecmd("run", tab_reg[32]->data, inter->BP, tab_reg, vmem); 
}
