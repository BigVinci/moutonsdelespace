#include "../include/common/cmd_gestion.h"




/** TEST
 * version de la commande test qui prend en entrée un hexa
 * la fonction verifie si le nombre est >=0
 * @param hexValue la valeur à afficher
 * @return 0 en case de succes, un nombre positif sinon
 */
int _testcmd(int hexValue) 
{
    if(hexValue <= 0) 
    {
        WARNING_MSG("command %s  - invalid call. The argument should be positive.\n", "test");
        return 2;
    }
    fprintf(stdout, "CMD TEST RESULT 0x%x\n", hexValue + 1);

    return CMD_OK_RETURN_VALUE;
}


/** SET_MEM_BYTE
 * version de la commande set mem byte
 * la fonction affecte une valeur dans la mémoire à l'adresse indiquée
 * @param byteValue la valeur à affecter
 * @param vaddr l'adresse où écrire la valeur, doit appartenir à un des segments suivants :  
 * @param vmem mémoire contenant l'adresse où doit être affectée la valeur
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _set_mem_bytecmd(uint8_t byteValue, uint32_t vaddr, mem vmem)
{
    int i;
    uint32_t addr;
    uint32_t addrrelle;

/* on vérifie que l'adresse existe */
    if (vaddr > 0xfffffffc) /* adresse : multiple de 4 -> la dernière adresse modifiable est 0xfffffffc */
    {
        WARNING_MSG("L'adresse demandée n'existe pas.\n");
        return 3;
    }

    /* on cherche l'adresse virtuelle exacte qui doit être modifiée (multiple de 4) */
    addr = (vaddr - (vaddr%4));

    for (i = 0; i < 6; ++i) /* on cherche dans quel segment est addr */
    {
        if ((vmem->seg[i].start._32 <= addr) && (vmem->seg[i+1].start._32 > addr))
        {
            INFO_MSG("Le segment modifié est %s.\n", vmem->seg[i].name);

            /* on cherche l'adresse réelle exacte */
            addrrelle = (addr - vmem->seg[i].start._32);

            /* on modifie la mémoire en gardant la représentation big endian */
            *((vmem->seg[i].content)+addrrelle) = 0x00;
            *((vmem->seg[i].content)+addrrelle+1) = 0x00;
            *((vmem->seg[i].content)+addrrelle+2) = 0x00;
            *((vmem->seg[i].content)+addrrelle+3) = byteValue;

            INFO_MSG("Modification du segment réalisée.\n");
            return CMD_OK_RETURN_VALUE;
        }
        else if (vmem->seg[6].start._32 <= addr) /* on regarde si addr est dans le dernier segment */
        {
            INFO_MSG("Le segment modifié est %s.\n", "[vsyscall]");

            /* on cherche l'adresse réelle exacte */
            addrrelle = (addr - vmem->seg[6].start._32);

            /* on modifie la mémoire en gardant la représentation big endian */
            *((vmem->seg[6].content)+addrrelle) = 0x00;
            *((vmem->seg[6].content)+addrrelle+1) = 0x00;
            *((vmem->seg[6].content)+addrrelle+2) = 0x00;
            *((vmem->seg[6].content)+addrrelle+3) = byteValue;

            INFO_MSG("Modification du segment réalisée.\n");
            return CMD_OK_RETURN_VALUE;
        }
    }
    ERROR_MSG("SHOULD NEVER BE HERE\n");
    return CMD_EXIT_RETURN_VALUE;
}


/** SET_MEM_MAP
 * version de la commande set mem word
 * la fonction affecte une valeur dans la mémoire à l'adresse indiquée
 * @param wordValue la valeur à affecter
 * @param vaddr l'adresse où écrire la valeur
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _set_mem_wordcmd(uint32_t wordValue, uint32_t vaddr)
{
	printf("Fonction non implémentée. Retourne toujours 0.\n");
	return CMD_OK_RETURN_VALUE;
}


/** SET_REG
 * version de la commande set reg
 * la fonction affecte une valeur au registre indiqué
 * @param wordValue la valeur à affecter
 * @param vaddr l'adresse où écrire la valeur
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _set_regcmd(uint32_t wordValue, reg vreg)
{
	printf("Fonction non implémentée. Retourne toujours 0.\n");
	return CMD_OK_RETURN_VALUE;
}


/** SET_MEM_MAP
 * version de la commande disp mem map
 * la fonction affiche le contenu de la carte mémoire du programme
 * @param vmem la mémoire à afficher
 * @return 0 en cas de succes, un nombre positif sinon
 */
 int _disp_mem_mapcmd(mem vmem)
 {
    printf("Carte mémoire virtuelle (7 segments) : \n");
    print_mem( vmem );
    return CMD_OK_RETURN_VALUE;
}


 /** DISP_MEM_REG
 * version de la commande disp mem reg
 * la fonction affiche une partie de la mémoire 
 * @param token indique les deux adresses séparées par ":"
 * @param vmem représente la mémoire
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _disp_mem_plagescmd(char* token, mem vmem)
 {
/* token contient vaddr1:vaddr2 */
    printf("Fonction non implémentée. Retourne toujours 0.\n");
    return CMD_OK_RETURN_VALUE;

/*    int i;
    printf("Affichage des données demandées. \n");
    printf("%u", vhexa1);
    for (int i = 0; i < 7; ++i)
    {
        if (vmem->seg[i].start <= vhexa1)  on s'arrête au segment contenant la première adresse demandée 
        {
            if ((vmem->seg[i].start + vsize._32) <= vhexa1)  cas où l'adresse n'est pas utilisée 
            {
                printf("00");
            }
            else ()
        }
    } */
 }


/** DISP_REG_REGISTER
 * Fonction qui affiche la valeur contenue dans le registre donné (un seul registre pour le moment)
 * @param vname le nom du registre à afficher et 
 * @param tab le tableau des registres 
 * @return 0 si réussi, 1 si fail
 */
int _disp_reg_registercmd(char* vname, reg* tab)
{   
    DEBUG_MSG("La fonction disp_reg_register a été lancée.\n"); //on vérifie qu'on se trouve dans la bonne fonction
    int i=0;
    int j=0;
    for (i=0; i<35; i++)
    {
	if(strcmp(vname,tab[i]->name)==0 || strcmp(vname, tab[i]->mnemo)==0) /* si le nom vname est un nom de registre */
	j=i; i=39;
    }

    if (i==35) /* aucun registre ne porte ce nom */
    {
	INFO_MSG("Le registre indiqué n'existe pas.\n");
	return 1;
    }

    if (i==39) /* un registre porte le nom ou le mnémo vname */
    {
	INFO_MSG("La valeur du registre est :\n");
	printf(" %s : %s  \n", tab[j]->name, tab[j]->data); //On affiche le nom du registre et sa data (attention, ne fonctionne que pour un seul registre)
    }
    return CMD_OK_RETURN_VALUE;
}


/** DISP_REG_ALL
 * Fonction qui affiche le contenu de tous les registres
 * @param tab_reg le tableau de tous les registres
 * @return 0 si réussi, 1 si fail
 */
int _disp_reg_allcmd(reg* tab_reg)
{    
    DEBUG_MSG("La fonction disp_reg_all a été lancée.\n"); //On vérifie que la bonne fonction s'ouvre
    int k=4; 
    int j=0;
    while(j!=35)
    {
	j++; /* on vérifie une fois chaque registre */
	INFO_MSG("Voici la liste des registres :\n");
        printf(" %s : %s ",(*tab_reg)->name,(*tab_reg)->data); //Pour chaque registre, on affiche son nom et sa data
        tab_reg++;                                           // On passe au registre suivant
        k--;                                                   //On décrémente k
        if(k==0)
        {
            printf("\n");                                       //On va à la ligne tout les 4 registre
            k=4;
        }
    }
    return CMD_OK_RETURN_VALUE;
}


/** RESUME
 * fonction qui reprend l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */
void _resumecmd(interpreteur inter)
{
  WARNING_MSG("Fonction resume pas encore implementée");
}


/** ASSERT_REG
 * Fonction qui compare le contenu d'un registre à la valeur val
 * @param r le registre à utiliser
 * @param val la valeur à vérifier
 * @return 0 si les deux valeurs sont identiques, 1 si fail
 */
int _assert_regcmd(reg r, int valeur)
{   
    char* val=NULL;
    sprintf(val, "%d", valeur); /* on converti valeur en chaîne de caractère */
    DEBUG_MSG("L'ouverture d'assert_reg a fonctionnée.\n"); //On vérifie qu'on est dans la bonne fonction
    if(strcmp((r->data),val)==0) //On compare la valeur entrée avec le contenu du registre
    {
	INFO_MSG("Les deux valeurs sont identiques.\n");
        return CMD_OK_RETURN_VALUE; //retourne 0 si égal, 1 sinon
    }
    INFO_MSG("Les deux valeurs ne sont pas identiques.\n");
    return 1;
}


/** ASSERT_BYTE
 * Fonction qui vérifie si la valeur à l'adresse donnée est bien la valeur val précisée 
 * @param adress l'adresse virtuelle
 * @param val la valeur à vérifier
 * @param vmem la mémoire
 * @return 0 si réussi, 1 si fail
 */
int _assert_bytecmd(uint32_t adress, int valeur, mem vmem)
{   
    printf("Fonction non implémentée. Retourne toujours 0.\n");
    return CMD_OK_RETURN_VALUE;
}


/** ASSERT_WORD
 * Fonction qui vérifie si la valeur à l'adresse donnée est bien la valeur val précisée 
 * @param adress l'adresse virtuelle à considèrer
 * @param valeur la valeur à vérifier
 * @param vmem la mémoire
 * @return 0 si réussi, 1 si fail
 */
int _assert_wordcmd(uint32_t adress, int valeur, mem vmem)
{   
    printf("Fonction non implémentée. Retourne toujours 0.\n");
    return CMD_OK_RETURN_VALUE;
}


/** DEBUGCMD
 * fonction qui arrete l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */
void _debugcmd(interpreteur inter)
{
WARNING_MSG("fonction debug pas encore implementée ");
}
