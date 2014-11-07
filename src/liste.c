#include "../include/liste.h"


/** 
 * INIT_LISTE
 * commande qui crée et alloue une liste
 * @return la liste ainsi créée
 */
Liste init_liste()
{
    return NULL;
}


/** 
 * EST_VIDE
 * commande qui vérifie si une liste est vide
 * @return un positif si vide, 0 si non vide
 */
int est_vide(Liste L)
{
    return !L;
}


/** 
 * SUPPR_LISTE
 * commande qui supprime une liste 
 * @param L la liste à supprimer
 */
Liste suppr_liste(Liste L)
{
    if (!est_vide(L)) // si la liste n'est pas vide
    {
    return NULL;
    }
    return L;
}


/** 
 * SUPPR_BP
 * commande qui supprime un élément d'une liste 
 * @param L la liste dont on doit supprimer l'élément
 * @param adress indique l'adresse qui doit être supprimé de la liste des breakpoint
 * @return la liste sans l'élément à supprimer
 */
Liste suppr_bp(Liste L, char* adress)
{
    if (est_vide(L)) // si la liste est vide
    {
    printf("Cette liste est déjà vide.\n");
    return L;
    }

    Liste L1=init_liste();
    L1=calloc(1, sizeof(Liste));
    L1=L; // permet de ne pas perdre les éléments avant adress

    if (strcmp(L->data, adress)==0) // si l'élément à supprimer est le premier
    {
        if (L->suiv != NULL) return L->suiv; // on le supprime en débutant la liste par le deuxième élément s'il existe
    else return NULL;            // sinon cela revient à supprimer la liste 
    }        

// si l'élément à supprimer n'est pas le premier 
    if (L->suiv==NULL) // l'élément n'existe pas dans la liste
    {
    printf("L'élément ne peut être supprimé car il n'est pas dans la liste"); 
    return L;
    } 

    while(L->suiv!=NULL)
    {
        if (strcmp(L->suiv->data, adress)!=0) L=L->suiv; // on cherche l'élément à supprimer
    else                         // on a trouvé l'élément à supprimer
    {
        if (L->suiv->suiv != NULL) L->suiv=L->suiv->suiv; // cas où l'élément n'est pas le dernier de la liste
        else L->suiv=NULL;                    // cas où l'élément est le dernier de la liste
    }                        
    }

    return L1;
}


/** 
 * ADD_BP
 * commande qui ajoute un élément à une liste
 * @param L la liste qui doit recevoir l'élément
 * @param adress indique l'adresse qui doit être ajouté à la liste des breakpoint
 * @return la liste une fois l'élément ajouté
 */
Liste add_bp(Liste L, char* adress)
{
    if (est_vide(L)) // si la liste est vide
    {
    L=calloc(1, sizeof(Liste));
        L->data=strdup(adress);
        L->suiv=NULL;
    }

    if (absent_bp(L, adress)) // si la liste n'est pas vide & l'élément n'est pas présent dans la liste 
    {
        Liste p=init_liste(); // Liste qui permet de se déplacer de maillon en maillon sans toucher à L
    p=calloc(1, sizeof(Liste));
        p=L; 

        Liste L1=init_liste(); // Futur maillon à ajouter à la liste
        L1=calloc(1, sizeof(Liste));
    L1->data=strdup(adress); 

    int* i; int* j; int* k;
    i = calloc(1, sizeof(int)); j = calloc(1, sizeof(int)); k = calloc(1, sizeof(int));
    sscanf(p->data, "%x", &i); sscanf(adress, "%x", &j);  // permet de comparer les deux valeurs numériques

    if (p->suiv !=NULL) sscanf(p->suiv->data, "%x", &k); // on vérifie qu'il y ait plus strictement de un élément
    else 
    {
        if (i<j) {p->suiv=L1; return L;}    // on rajoute l'élément en seconde position (ie la fin dans ce cas particulier)
        else {L1->suiv=p; L=L1; return L;}  // on ajoute l'élément en première position
    }

// cas où il y a au moins deux éléments dans la liste
    if (j<i) // ajout en tête 
    {
        L1->suiv=L;
        return L1;
    }

    if (j<k && i<j) // ajout en seconde position 
    {
        L1->suiv=p->suiv;
            p->suiv=L1;
        return L;
    }

        while(k<j && p->suiv !=NULL) // ajout autre position
        {
            p=p->suiv;
        if (p->suiv!=NULL) sscanf(p->suiv->data, "%x", &k); // on check l'élément suivant
        }

        // on se situe sur le maillon d'élément inférieur à adress et dont le suivant est supérieur à adress
        if (p->suiv != NULL) // cas où k>j
    {
        L1->suiv=p->suiv;
            p->suiv=L1;
    }
    else // si on ajoute un élément à la fin de la liste
    {
        L1->suiv=NULL;
        p->suiv=L1; 
    }
    }

    return L;
}


/** 
 * DISP_BP
 * commande qui permet de visualiser une liste
 * @param L la liste à afficher
 */
void disp_bp(Liste L)
{
    if (est_vide(L))
    {
    printf("La liste est vide.\n");
    return;
    }

    Liste p=init_liste();
    p=calloc(1, sizeof(Liste));
    p=L;
    printf("%s\n", p->data); // la liste n'est pas vide
    while (p->suiv!=NULL)
    {
        p=p->suiv;
        printf("%s\n", p->data);
    }
}


/** 
 * ABSENT_BP
 * commande qui vérifie si un élément est déjà dans la liste
 * @param L la liste à parcourir
 * @param adress l'élément à rechercher dans la liste
 * @return 1 si absent, 0 si présent
 */
int absent_bp(Liste L, char* adress)
{
    if (est_vide(L)) return 1;
    if (strcmp(L->data, adress)==0) return 0; 

    while (L->suiv!=NULL)
    {
    L=L->suiv;
    if (strcmp(L->data, adress)==0) return 0;
    }

    return 1;
}