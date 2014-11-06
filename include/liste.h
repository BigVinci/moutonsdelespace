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
typedef MAILLON* liste;

liste init_liste();
void suppr_liste(liste l);

liste suppr_bp(liste l, char* adress);
liste add_bp(liste l, char* adress);
void disp_bp(liste l);

#endif /* _LISTE_H_ */
