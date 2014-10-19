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
    DEBUG_MSG("La fonction set_mem_byte a été lancée.\n"); //On vérifie que la bonne fonction s'ouvre
    int i;
    uint32_t addr;
    uint32_t addrrelle;

// on vérifie que l'adresse existe 
    if (vaddr > 0xfffffffc) // adresse : multiple de 4 -> la dernière adresse modifiable est 0xfffffffc 
    {
        WARNING_MSG("L'adresse demandée n'existe pas.\n");
        return 3;
    }

    // on cherche l'adresse virtuelle exacte qui doit être modifiée (multiple de 4) 
    addr = (vaddr - (vaddr%4));

    for (i = 0; i < 6; ++i) // on cherche dans quel segment est addr 
    {
        if ((vmem->seg[i].start._32 <= addr) && (vmem->seg[i+1].start._32 > addr))
        {
            INFO_MSG("Le segment modifié est %s.\n", vmem->seg[i].name);

            // on cherche l'adresse réelle exacte 
            addrrelle = (addr - vmem->seg[i].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[i].content)+addrrelle) = 0x00;
            *((vmem->seg[i].content)+addrrelle+1) = 0x00;
            *((vmem->seg[i].content)+addrrelle+2) = 0x00;
            *((vmem->seg[i].content)+addrrelle+3) = byteValue;

            INFO_MSG("Modification du segment réalisée.\n");
            return CMD_OK_RETURN_VALUE;
        }
        else if (vmem->seg[6].start._32 <= addr) // on regarde si addr est dans le dernier segment 
        {
            INFO_MSG("Le segment modifié est %s.\n", "[vsyscall]");

            // on cherche l'adresse réelle exacte 
            addrrelle = (addr - vmem->seg[6].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
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
int _set_mem_wordcmd(uint32_t wordValue, uint32_t vaddr, mem vmem)
{
    DEBUG_MSG("La fonction set_mem_word a été lancée.\n"); //On vérifie que la bonne fonction s'ouvre
	int i;
    uint32_t addr;
    uint32_t addrrelle;
    uint8_t byteValue[4]={0};

    // on vérifie que l'adresse existe 
    if (vaddr > 0xfffffffc) // adresse : multiple de 4 -> la dernière adresse modifiable est 0xfffffffc 
    {
        WARNING_MSG("L'adresse demandée n'existe pas.\n");
        return 3;
    }

    for (i = 0; i < 4; ++i) // on transforme le word en 4 octets distincts 
    {
        byteValue[i] = ((uint8_t*)&wordValue)[3-i];
    }

    // on cherche l'adresse virtuelle exacte qui doit être modifiée (multiple de 4) 
    addr = (vaddr - (vaddr%4));

    for (i = 0; i < 6; ++i) // on cherche dans quel segment est addr 
    {
        if ((vmem->seg[i].start._32 <= addr) && (vmem->seg[i+1].start._32 > addr))
        {
            INFO_MSG("Le segment modifié est %s.\n", vmem->seg[i].name);

            // on cherche l'adresse réelle exacte 
            addrrelle = (addr - vmem->seg[i].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[i].content)+addrrelle) = byteValue[0];
            *((vmem->seg[i].content)+addrrelle+1) = byteValue[1];
            *((vmem->seg[i].content)+addrrelle+2) = byteValue[2];
            *((vmem->seg[i].content)+addrrelle+3) = byteValue[3];

            INFO_MSG("Modification du segment réalisée.\n");
            return CMD_OK_RETURN_VALUE;
        }
        else if (vmem->seg[6].start._32 <= addr) // on regarde si addr est dans le dernier segment 
        {
            INFO_MSG("Le segment modifié est %s.\n", "[vsyscall]");

            // on cherche l'adresse réelle exacte 
            addrrelle = (addr - vmem->seg[6].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[6].content)+addrrelle) = byteValue[0];
            *((vmem->seg[6].content)+addrrelle+1) = byteValue[1];
            *((vmem->seg[6].content)+addrrelle+2) = byteValue[2];
            *((vmem->seg[6].content)+addrrelle+3) = byteValue[3];

            INFO_MSG("Modification du segment réalisée.\n");
            return CMD_OK_RETURN_VALUE;
        }
    }
    ERROR_MSG("SHOULD NEVER BE HERE\n");
    return CMD_EXIT_RETURN_VALUE;
}


/** SET_REG
 * version de la commande set reg
 * la fonction affecte une valeur au registre indiqué
 * @param wordValue la valeur à affecter
 * @param vreg le registre à affecter
 * @param tab_reg le tableau de registre qui sera modifié 
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _set_regcmd(uint32_t wordValue, reg vreg, reg* tab_reg)
{
    int i;
    DEBUG_MSG("La fonction set_reg a été lancée.\n"); //On vérifie que la bonne fonction s'ouvre
    char* datareg;
	for (i = 0; i < 35; ++i)
    {
        if (strcmp(tab_reg[i]->name,vreg->name)==0 || strcmp(tab_reg[i]->mnemo,vreg->name)==0) // on cherche le registre adéquat
        {
            sprintf(datareg,"%u", wordValue); // converti uint32_t en char*
            strcpy(tab_reg[i]->data,datareg); // copie datareg dans le registre sélectionné
            return CMD_OK_RETURN_VALUE;
        }
    }
    ERROR_MSG("SHOULD NEVER BE HERE\n");
    return CMD_EXIT_RETURN_VALUE;	
}


/** SET_MEM_MAP
 * version de la commande disp mem map
 * la fonction affiche le contenu de la carte mémoire du programme
 * @param vmem la mémoire à afficher
 * @return 0 en cas de succes, un nombre positif sinon
 */
 int _disp_mem_mapcmd(mem vmem)
 {
    DEBUG_MSG("La fonction disp_mem_map a été lancée.\n"); //On vérifie que la bonne fonction s'ouvre
    printf("Carte mémoire virtuelle (%u segments) : \n", vmem->nseg);
    print_mem( vmem );
    return CMD_OK_RETURN_VALUE;
}


 /** DISP_MEM_PLAGES
 * version de la commande disp mem reg
 * la fonction affiche une partie de la mémoire 
 * @param token indique les deux adresses séparées par ":"
 * @param vmem représente la mémoire
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _disp_mem_plagescmd(uint32_t addr1, uint32_t addr2, mem vmem)
 {
    DEBUG_MSG("La fonction disp_mem_plages a été lancée.\n"); //On vérifie que la bonne fonction s'ouvre
    int i, no_printf=1;
    uint32_t addr;
    uint32_t addr_end=addr2;

    if (addr1 == addr2) // si les bornes sont inversées 
    {
        addr=addr2+1; // si les bornes sont égales, on affiche la seule valeur existant (ie celle des bornes)
    }

    if (addr1 > addr2) // si les bornes sont inversées 
    {
        WARNING_MSG("%u : %u sera affiché à la place de %u : %u (car cette plage ne peut exister)", addr2, addr1, addr1, addr2);
        addr=addr1; addr1=addr2; addr2=addr; // on inverse les bornes 
    }

    printf("Affichage de la plage de données %u : %u \n", addr1, addr2);
    for (i = 0; i < 8; ++i)
    {
        if (vmem->seg[i].start._32 <= addr1 && (vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr1)  // on vérifie que l'on est dans le bon segment 
        {
            addr = (addr1 - vmem->seg[i].start._32); // on cherche les adresses à afficher dans la mémoire physique
            if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr2)
            { // on vérifie que les bornes sont incluses dans le même segment
                addr_end = vmem->seg[i].start._32 + vmem->seg[i].size._32 + 1; // si ce n'est pas le cas, on s'arrête au dernier octet du segment 
            }

            printf("Affichage de la plage de données %u : %u incluse dans le segment %s\n", addr1, addr2, vmem->seg[i].name);

            while (addr1 < addr_end)
            {
                printf("%d  ", (unsigned char)addr); // on affiche l'adresse de départ chaque 10 octets 
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // premier byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // deuxieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // troisieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // quatrieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // cinquieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // sixieme byte 
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // septieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // huitieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // neuvieme byte 
                printf("%s\n", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // dixieme byte et retour à la ligne chaque 10 éléments
            }
            no_printf=0; // on a fini l'affichage
            addr_end=addr2; // on récupère la donnée initiale pour le segment suivant 
        }
        // puis on regarde dans un autre segment grâce à la boucle for
    } 

    if (no_printf==1)
    {
        WARNING_MSG("Votre plage de données n'a pas pu être affichée");
        return 1;
    }

    return CMD_OK_RETURN_VALUE;
 }


 /** DISP_MEM_OFFSET
 * version de la commande disp mem reg
 * la fonction affiche une partie de la mémoire 
 * @param token indique les deux adresses séparées par ":"
 * @param vmem représente la mémoire
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _disp_mem_offsetcmd(uint32_t addr1, int offset, mem vmem)
{
DEBUG_MSG("La fonction disp_mem_offset a été lancée.\n"); //On vérifie que la bonne fonction s'ouvre
    int i, no_printf=1;
    uint32_t addr;
    uint32_t addr_end=addr1+offset;

    if (offset<0) // si les bornes sont inversées 
    {
        WARNING_MSG("Veuillez entrer un offset positif"); 
        return 1;
    }

    printf("Affichage de la plage de données %u : %u \n", addr1, addr_end);
    for (i = 0; i < 8; ++i)
    {
        if (vmem->seg[i].start._32 <= addr1 && (vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr1)  // on vérifie que l'on est dans le bon segment 
        {
            addr = (addr1 - vmem->seg[i].start._32); // on cherche les adresses à afficher dans la mémoire physique
            if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr_end)
            { // on vérifie que les bornes sont incluses dans le même segment
                addr_end = vmem->seg[i].start._32 + vmem->seg[i].size._32 + 1; // si ce n'est pas le cas, on s'arrête au dernier octet du segment 
            }

            printf("Affichage de la plage de données %u : %u incluse dans le segment %s\n", addr1, addr_end, vmem->seg[i].name);

            while (addr1 < addr_end)
            {
                printf("%d  ", (unsigned char)addr); // on affiche l'adresse de départ chaque 10 octets 
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // premier byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // deuxieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // troisieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // quatrieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // cinquieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // sixieme byte 
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // septieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // huitieme byte
                printf("%s  ", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // neuvieme byte 
                printf("%s\n", (unsigned char*)vmem->seg[i].content+addr); addr++; addr1++; // dixieme byte et retour à la ligne chaque 10 éléments
            }
            no_printf=0; // on a fini l'affichage
            addr_end=addr1+offset; // on récupère la donnée initiale pour le segment suivant 
        }
        // puis on regarde dans un autre segment grâce à la boucle for
    } 

    if (no_printf==1)
    {
        WARNING_MSG("Votre plage de données n'a pas pu être affichée");
        return 1;
    }

    return CMD_OK_RETURN_VALUE;
}


/** DISP_REG_REGISTER
 * Fonction qui affiche la valeur contenue dans le registre donné (un seul registre pour le moment)
 * @param vname le nom du registre à afficher et 
 * @param tab le tableau des registres 
 * @return 0 si réussi, 1 si fail
 */
int _disp_reg_registercmd(char* vname, reg* tab)
{   
    DEBUG_MSG("La fonction disp_reg_register a été lancée.\n"); // on vérifie qu'on se trouve dans la bonne fonction
    int i=0;
    int j=0;
    for (i=0; i<35; i++)
    {
	if(strcmp(vname,tab[i]->name)==0 || strcmp(vname, tab[i]->mnemo)==0) // si le nom vname est un nom de registre 
	j=i; i=39;
    }

    if (i==35) // aucun registre ne porte ce nom 
    {
	INFO_MSG("Le registre indiqué n'existe pas.\n");
	return 1;
    }

    if (i==39) // un registre porte le nom ou le mnémo vname 
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
	j++; // on vérifie une fois chaque registre 
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
    sprintf(val, "%d", valeur); // on converti valeur en chaîne de caractère
    DEBUG_MSG("L'ouverture d'assert_reg a fonctionnée.\n"); // On vérifie qu'on est dans la bonne fonction
    if(strcmp((r->data),val)==0) // On compare la valeur entrée avec le contenu du registre
    {
	    INFO_MSG("Les deux valeurs sont identiques.\n");
        return CMD_OK_RETURN_VALUE; // retourne 0 si égal, 1 sinon
    }
    INFO_MSG("Les deux valeurs ne sont pas identiques.\n");
    return 1;
}


/** ASSERT_BYTE
 * Fonction qui vérifie si la valeur à l'adresse donnée est bien la valeur val précisée 
 * @param adress l'adresse virtuelle
 * @param val la valeur à vérifier (de type byte)
 * @param vmem la mémoire
 * @return 0 si les deux valeurs sont identiques, 1 si fail
 */
int _assert_bytecmd(uint32_t address, int valeur, mem vmem)
{   
    int i;
    char* val=NULL; char* valueaddr=NULL;
    uint32_t addrrelle;

    sprintf(val, "%d", valeur); // on converti valeur en chaîne de caractère
    DEBUG_MSG("L'ouverture de la commande assert_byte a fonctionné.\n"); // On vérifie qu'on est dans la bonne fonction

    // on cherche l'adresse à tester
    for (i = 0; i < vmem->nseg; ++i) // on parcourt les segments
    {
        if (vmem->seg[i].start._32 < address && vmem->seg[i].size._32 > address ) // on cherche le segment contenant address
        {
            addrrelle=(address-(vmem->seg[i].start._32)); // on calcule l'adresse réelle à vérifier
            valueaddr=(char*)(vmem->seg[i].content+addrrelle+3); // représentation big endian : on ne vérifie que le dernier octet
            if(strcmp(valueaddr,val)==0 && (vmem->seg[i].content+addrrelle)==0 && (vmem->seg[i].content+addrrelle+1)==0 && (vmem->seg[i].content+addrrelle+2)==0) // On compare la valeur entrée avec le contenu de l'adresse
            {
                INFO_MSG("Les deux valeurs sont identiques.\n");
                return CMD_OK_RETURN_VALUE; // retourne 0 si égal, 1 sinon
            } 
        }
    }

    INFO_MSG("Les deux valeurs ne sont pas identiques.\n");
    return 1;
}


/** ASSERT_WORD
 * Fonction qui vérifie si la valeur à l'adresse donnée est bien la valeur val précisée 
 * @param adress l'adresse virtuelle à considèrer
 * @param valeur la valeur à vérifier (de type word)
 * @param vmem la mémoire
 * @return 0 si les deux valeurs sont identiques, 1 si fail
 */
int _assert_wordcmd(uint32_t address, int valeur, mem vmem)
{   
    int i;
    char* val=NULL; 
    byte value1, value2, value3, value4; // représente les 4 octets à vérifier
    word valueaddr; char* valaddr=NULL;
    uint32_t addrrelle;

    sprintf(val, "%d", valeur); // on converti valeur en chaîne de caractère
    DEBUG_MSG("L'ouverture de la commande assert_word a fonctionné.\n"); // On vérifie qu'on est dans la bonne fonction

    // on cherche l'adresse à tester
    for (i = 0; i < vmem->nseg; ++i) // on parcourt les segments
    {
        if (vmem->seg[i].start._32 < address && vmem->seg[i].size._32 > address ) // on cherche le segment contenant address
        {
            addrrelle=(address-(vmem->seg[i].start._32)); // on calcule l'adresse réelle à vérifier
            value1=*(vmem->seg[i].content+addrrelle); // on récupère chaque byte de l'adresse indiquée
            value2=*(vmem->seg[i].content+addrrelle+1);
            value3=*(vmem->seg[i].content+addrrelle+2);
            value4=*(vmem->seg[i].content+addrrelle+3);

            valueaddr=((((((value1 << 8)+value2) << 8)+value3) << 8)+value4 ); // on récupère la valeur sur 32 bits pour pouvoir la comparer
            *valaddr=(unsigned char)(valueaddr);

            if(strcmp(valaddr,val)==0) // On compare la valeur entrée avec le contenu de l'adresse
            {
                INFO_MSG("Les deux valeurs sont identiques.\n");
                return CMD_OK_RETURN_VALUE; // retourne 0 si égal, 1 sinon
            } 
        }
    }

    INFO_MSG("Les deux valeurs ne sont pas identiques.\n");
    return 1;
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
