#include "../include/liste.h"


/** 
 * INIT_LISTE
 * commande qui crée et alloue une liste
 * @return la liste ainsi créée
 */
liste init_liste()
{
    liste l=NULL;
    return l;
}


/** 
 * SUPPR_BP
 * commande qui supprime une liste 
 * @param l la liste à supprimer
 */
void suppr_liste(liste l)
{
    if (l!=NULL)
    {
	free(l);
    }
}


/** 
 * SUPPR_BP
 * commande qui supprime un élément d'une liste 
 * @param l la liste dont on doit supprimer l'élément
 * @param adress indique l'adresse qui doit être supprimé de la liste des breakpoint
 * @return la liste sans l'élément à supprimer
 */
liste suppr_bp(liste l, char* adress)
{
    WARNING_MSG("Fonction non implémentée");
    liste l=init_liste();
    return l;
}


/** 
 * ADD_BP
 * commande qui ajoute un élément à une liste
 * @param l la liste qui doit recevoir l'élément
 * @param adress indique l'adresse qui doit être ajouté à la liste des breakpoint
 * @return la liste une fois l'élément ajouté
 */
liste add_bp(liste l, char* adress)
{
    if (l==NULL)
    {
	
    }

    WARNING_MSG("Fonction non implémentée");
    return l;
}


/** 
 * DISP_BP
 * commande qui affiche une liste
 * @param l la liste à afficher
 */
void disp_bp(liste l)
{
    WARNING_MSG("Fonction non implémentée");
}
