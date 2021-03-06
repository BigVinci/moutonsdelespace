/**
 * @file emulMips.c
 * @author François Cayre, Nicolas Castagné, François Portet
 * @brief Main pour le début du projet émulateur MIPS.
 *
 */
#include "../include/common/fonct_gestion.h"
#include "../include/mem.h"
#include "../include/common/load.h"

/* prompt du mode shell interactif */
#define PROMPT_STRING "MipsShell : > "



/**
 * Programme principal
 */

int main ( int argc, char *argv[] )
{
    // exemples d'utilisation des macros du fichier notify.h
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]); // macro INFO_MSG
    WARNING_MSG("Un message WARNING_MSG !"); // macro INFO_MSG
    DEBUG_MSG("Un message DEBUG_MSG !"); // macro DEBUG_MSG : uniquement si compil en mode DEBUG_MSG
    interpreteur inter=init_inter(); // structure gardant les infos et etats de l'interpreteur
    FILE *fp = NULL; // le flux dans lequel les commandes seront lues : stdin (mode shell) ou un fichier

    if ( argc > 2 ) {		// si il y a plus de 2 arguments en entree
        usage_ERROR_MSG( argv[0] );
        exit( EXIT_FAILURE );	// erreur : on sort
    }
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage_ERROR_MSG( argv[0] );
        exit( EXIT_SUCCESS );
    }

    // on initialise le tableau de registre
    reg* tabreg=init_tab_reg();

    // on cr�e la m�moire et on l'alloue dynamiquement
    mem* vmem = calloc(1, sizeof(*vmem)); //initialisation de la m�moire
//    *vmem = init_mem(7);

    if(argc > 1) // en mode SCRIPT, on utilise la m�moire cr��e lors du load du fichier elf
        {
                if (vmem == NULL) // on v�rifie que la m�moire ait bien �t� cr��e
                {
                    WARNING_MSG( "Unable to allocate host memory for vmem" );
                    exit (EXIT_FAILURE );
                }
        }

    //par defaut : mode shell interactif
    fp = stdin;
    inter->mode = INTERACTIF;
    if(argc == 2) {
        // mode fichier de commandes
        fp = fopen( argv[1], "r" );
        if ( fp == NULL )
	{
            perror( "fopen" );
            exit( EXIT_FAILURE );
        }
        inter->mode = SCRIPT;
    }

    // boucle infinie : lit puis execute une cmd en boucle
    while ( 1 ) {


        if (acquire_line( fp,  inter)  == 0 ) {
	 int res;
            // Une nouvelle ligne a ete acquise dans le flux fp
            res = execute_cmd(inter, tabreg, vmem, fp);     // execution de la commande en mode SCRIPT

            // traitement des erreurs
            switch(res) {
            case CMD_OK_RETURN_VALUE:
                break;
            case CMD_EXIT_RETURN_VALUE:
                // sortie propre du programme
                if ( fp != stdin ) {
                    fclose( fp );
                }
//                del_inter(inter);
		del_mem(*vmem);
                exit(EXIT_SUCCESS);
                break;
            default:
                // erreur durant l'execution de la commande
                // En mode "fichier" toute erreur implique la fin du programme !
                if (inter->mode == SCRIPT) {
                    fclose( fp );
//                    del_inter(inter);
    	    	    del_mem(*vmem);
                    // macro ERROR_MSG : message d'erreur puis fin de programme !
                    ERROR_MSG("ERREUR DETECTEE. Aborts");
                }
                break;
            }
        }
        if( inter->mode == SCRIPT && feof(fp) ) {
            // mode fichier, fin de fichier => sortie propre du programme
            DEBUG_MSG("FIN DE FICHIER");
            fclose( fp );
            del_inter(inter);
    	    del_mem(*vmem);
            exit(EXIT_SUCCESS);
        }
    }
    // tous les cas de sortie du programme sont g�r�es plus haut
    ERROR_MSG("SHOULD NEVER BE HERE\n");
}
