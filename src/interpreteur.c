#include "../include/common/interpreteur.h"


/* prompt du mode shell interactif */
#define PROMPT_STRING "MipsShell : > "


/**
 * allocation et init interpreteur
 * @return un pointeur vers une structure allouÃ©e dynamiquement
 */
interpreteur init_inter(void) 
{
    interpreteur inter = calloc(1,sizeof(*inter));
    if (inter ==NULL)
        ERROR_MSG("impossible d'allouer un nouvel interpreteur");

    inter->file = calloc(1,sizeof(FILE));
    if (inter->file ==NULL)
        ERROR_MSG("impossible d'allouer un nouvel interpreteur");

    inter->BP = calloc(1,sizeof(Liste));
    if (inter->file ==NULL)
        ERROR_MSG("impossible d'allouer un nouvel interpreteur");
    
    return inter;
}

/**
 * desallocation de l'interpreteur
 * @param inter le pointeur vers l'interpreteur Ã  libérer
 */
void del_inter(interpreteur inter) 
{
	if (inter->file !=NULL)
    	free(inter->file);

    if ( !vide_liste(*(inter->BP)) )
        suppr_liste(*(inter->BP));

    if (inter !=NULL)
        free(inter);
}



/*************************************************************\
 Les deux fonctions principales de l'emulateur.
	execute_cmd : parse la commande et l'execute en appelant la bonne fonction C
                  commande présente dans fonc_gestion.c 
	acquire_line : recupere une ligne (donc une "commande") dans le flux
 \*************************************************************/




/**
 * @param in Input line (possibly very badly written).
 * @param out Line in a suitable form for further analysis.
 * @return nothing
 * @brief This function will prepare a line for further analysis.
 *
 * This function will prepare a line for further analysis and check for low-level syntax errors.
 * colon, brackets, commas are surrounded with blank; tabs are replaced with blanks.
 * negs '-' are attached to the following token (e.g., "toto -   56" -> "toto -56")  .
 */
void string_standardise( char* in, char* out ) {
    unsigned int i=0, j;

    /* i et j dans un for ???????? */
    for ( j= 0; i< strlen(in); i++ ) {

        /* insert blanks around special characters*/
        if (in[i]==':' || in[i]=='+' || in[i]=='~') {
            out[j++]=' ';
            out[j++]=in[i];
            out[j++]=' ';

        }

        /* remove blanks after negation*/
        else if (in[i]=='-') {
            out[j++]=' ';
            out[j++]=in[i];
            while (isblank((int) in[i+1])) i++;
        }

        /* insert one blank before comments */
        else if (in[i]=='#') {
            out[j++]=' ';
            out[j++]=in[i];
        }
        /* translate tabs into white spaces*/
        else if (isblank((int) in[i])) out[j++]=' ';
        else out[j++]=in[i];
    }
}


/**
 *
 * @brief extrait la prochaine ligne du flux fp.
 * Si fp ==stdin, utilise la librairie readline pour gestion d'historique de commande.
 *
 * @return 0 si succes.
 * @return un nombre non nul si aucune ligne lue
 */
int  acquire_line(FILE *fp, interpreteur inter) {
    char* chunk =NULL;

    memset(inter->input, '\0', MAX_STR );
    inter->first_token =0;
    if (inter->mode==SCRIPT) {
        // mode fichier
        // acquisition d'une ligne dans le fichier
        chunk =calloc(MAX_STR, sizeof(*chunk));
        char * ret = fgets(chunk, MAX_STR, fp );
        if(ret == NULL) {
            free(chunk);
            return 1;
        }
        // si windows remplace le \r du '\r\n' (fin de ligne windows) par \0
        if(strlen(ret) >1 && ret[strlen(ret) -2] == '\r') {
            ret[strlen(ret)-2] = '\0';
        }
        // si unix remplace le \n par \0
        else if(strlen(ret) >0 && ret[strlen(ret) -1] == '\n') {
            ret[strlen(ret)-1] = '\0';
        }

    }
    else {
        /* mode shell interactif */
        /* on utilise la librarie libreadline pour disposer d'un historique */
        chunk = readline( PROMPT_STRING );
        if (chunk == NULL || strlen(chunk) == 0) {
            /* commande vide... */
            if (chunk != NULL) free(chunk);
            return 1;
        }
        /* ajout de la commande a l'historique, librairie readline */
        add_history( chunk );

    }
    // standardisation de la ligne d'entree (on met des espaces lÃ  ou il faut)
    string_standardise(chunk, inter->input);

    free( chunk ); // liberation de la memoire allouee par la fonction readline() ou par calloc()

    DEBUG_MSG("Ligne acquise '%s'", inter->input); /* macro DEBUG_MSG : uniquement si compil en mode DEBUG_MSG */
    return 0;
}


/****************/
void usage_ERROR_MSG( char *command ) {
    fprintf( stderr, "Usage: %s [file.emul]\n   If no file is given, executes in Shell mode.", command );
}




