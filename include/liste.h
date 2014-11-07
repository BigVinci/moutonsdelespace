#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* macros de DEBUG_MSG fournies , etc */
#include "common/notify.h"

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* les différents types utiles */
#include "common/types.h"
#include "mem.h"
#include "reg.h"

#include "common/interpreteur.h"

typedef struct maillon {char* data; struct maillon* suiv;} MAILLON;
typedef MAILLON* Liste;

Liste init_liste();
int vide_liste(Liste L);
void suppr_liste(Liste L);

Liste suppr_bp(Liste L, char* adress);
Liste add_bp(Liste L, char* adress);
void disp_bp(Liste L);
int absent_bp(Liste L, char* adress);

#endif /* _LISTE_H_ */
