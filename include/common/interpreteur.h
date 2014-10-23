#ifndef _INTERPRETEUR_H_
#define _INTERPRETEUR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* macros de DEBUG_MSG fournies , etc */
#include "notify.h"


/* taille max pour nos chaines de char */
#define MAX_STR 1024


/*************************************************************\
Valeur de retour speciales lorsqu'on pour la fonction
	int parse_and_execute_cmd_string(char *input) ;
Toute autre valeur signifie qu'une erreur est survenue
 \*************************************************************/
#define CMD_OK_RETURN_VALUE 0
#define CMD_EXIT_RETURN_VALUE -1
#define CMD_UNKOWN_RETURN_VALUE -2

/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT} inter_mode;

/* structure passee en parametre qui contient la connaissance de l'état de
 * l'interpreteur
 */
typedef struct {
    inter_mode mode;    /* mode de l'interpréteur */ 
    char input[MAX_STR];
    char * from;
    char first_token;
    FILE* file;
} *interpreteur;


/* type de token (exemple) */
enum {HEXA,BYTE,WORD,INTEGER,OCTAL,REG,ELF,UNKNOWN};


interpreteur init_inter(void);
void del_inter(interpreteur inter);
void string_standardise( char* in, char* out );
int  acquire_line(FILE *fp, interpreteur inter);
void usage_ERROR_MSG( char *command );


#endif /* _INTERPRETEUR_H_ */ 
