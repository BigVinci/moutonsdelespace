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
        WARNING_MSG("command %s  - invalid call. The argument should be positive", "test");
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
    DEBUG_MSG("La fonction set_mem_byte a été lancée"); //On vérifie que la bonne fonction s'ouvre
    int i;
    uint32_t addrreelle;

    if (byteValue>0xff)
    {
	WARNING_MSG("Seul un nombre inférieur ou égal à 255 peut être entré dans cet octet");
	return 1;
    }

    // on vérifie que l'adresse existe 
    if (vaddr > 0xffffffff) // adresse : multiple de 4 -> la dernière adresse modifiable est 0xfffffffc 
    {
        WARNING_MSG("L'adresse demandée n'existe pas");
        return 3;
    }

    for (i = 0; i < 6; ++i) // on cherche dans quel segment est addr 
    {
        if ((vmem->seg[i].start._32 <= vaddr) && (vmem->seg[i+1].start._32 > vaddr))
        {
            INFO_MSG("Le segment modifié est %s", vmem->seg[i].name);

            // on cherche l'adresse réelle exacte 
            addrreelle = (vaddr - vmem->seg[i].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[i].content)+addrreelle) = byteValue;

            INFO_MSG("Modification du segment réalisée");
            return CMD_OK_RETURN_VALUE;
        }
        else if (vmem->seg[6].start._32 <= vaddr) // on regarde si addr est dans le dernier segment 
        {
            INFO_MSG("Le segment modifié est %s", "[vsyscall]");

            // on cherche l'adresse réelle exacte 
            addrreelle = (vaddr - vmem->seg[6].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[6].content)+addrreelle) = byteValue;

            INFO_MSG("Modification du segment réalisée");
            return CMD_OK_RETURN_VALUE;
        }
    }
    ERROR_MSG("SHOULD NEVER BE HERE");
    return CMD_EXIT_RETURN_VALUE;
}


/** SET_MEM_WORD
 * version de la commande set mem word
 * la fonction affecte une valeur dans la mémoire à l'adresse indiquée
 * @param wordValue la valeur à affecter
 * @param vaddr l'adresse où écrire la valeur
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _set_mem_wordcmd(uint32_t wordValue, uint32_t vaddr, mem vmem)
{
    DEBUG_MSG("La fonction set_mem_word a été lancée"); //On vérifie que la bonne fonction s'ouvre
	int i;
    uint32_t addr;
    uint32_t addrrelle;
    uint8_t byteValue[4]={0};

    // on vérifie que l'adresse existe 
    if (vaddr > 0xfffffffc) // adresse : multiple de 4 -> la dernière adresse modifiable est 0xfffffffc 
    {
        WARNING_MSG("L'adresse demandée n'existe pas");
        return 1;
    }

    for (i = 0; i < 4; ++i) // on transforme le word en 4 octets distincts 
    {
        byteValue[i] = ((uint8_t*)&wordValue)[3-i];
    }

    for (i = 0; i < 6; ++i) // on cherche dans quel segment est addr 
    {
        if ((vmem->seg[i].start._32 <= vaddr) && (vmem->seg[i+1].start._32 > vaddr))
        {

    	    // l'adresse virtuelle exacte qui doit être modifiée doit être un multiple de 4 
    	    addr = ((vaddr - vmem->seg[i].start._32)%4);
    	    if (addr!=0)
    	    {
        	WARNING_MSG("L'adresse à modifier doit être un multiple de 4 depuis l'adresse de départ du segment.");
        	return 1;
    	    }

            INFO_MSG("Le segment modifié est %s", vmem->seg[i].name);

            // on cherche l'adresse réelle exacte 
            addrrelle = (vaddr - vmem->seg[i].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[i].content)+addrrelle) = byteValue[0];
            *((vmem->seg[i].content)+addrrelle+1) = byteValue[1];
            *((vmem->seg[i].content)+addrrelle+2) = byteValue[2];
            *((vmem->seg[i].content)+addrrelle+3) = byteValue[3];

            INFO_MSG("Modification du segment réalisée");
            return CMD_OK_RETURN_VALUE;
        }
        else if (vmem->seg[6].start._32 <= vaddr) // on regarde si addr est dans le dernier segment 
        {
    	    // l'adresse virtuelle exacte qui doit être modifiée doit être un multiple de 4 
    	    addr = ((vaddr - vmem->seg[i].start._32)%4);
    	    if (addr!=0)
    	    {
        	WARNING_MSG("L'adresse à modifier doit être un multiple de 4 depuis l'adresse de départ du segment.");
        	return 1;
    	    }

            INFO_MSG("Le segment modifié est %s", "[vsyscall]");

            // on cherche l'adresse réelle exacte 
            addrrelle = (vaddr - vmem->seg[6].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[6].content)+addrrelle) = byteValue[0];
            *((vmem->seg[6].content)+addrrelle+1) = byteValue[1];
            *((vmem->seg[6].content)+addrrelle+2) = byteValue[2];
            *((vmem->seg[6].content)+addrrelle+3) = byteValue[3];

            INFO_MSG("Modification du segment réalisée");
            return CMD_OK_RETURN_VALUE;
        }
    }
    ERROR_MSG("SHOULD NEVER BE HERE");
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
    DEBUG_MSG("La fonction set_reg a été lancée"); //On vérifie que la bonne fonction s'ouvre
    char* datareg=calloc(1, sizeof(char));

    for (i = 0; i < 35; ++i)
    {
        if (strcmp(tab_reg[i]->name,vreg->name)==0 || strcmp(tab_reg[i]->mnemo,vreg->name)==0) // on cherche le registre adéquat
        {   
            sprintf(datareg,"%u", wordValue); // converti uint32_t en char*
            tab_reg[i]->data=strdup(datareg); // copie datareg dans le registre sélectionné
            return CMD_OK_RETURN_VALUE;
        }
    }
    ERROR_MSG("SHOULD NEVER BE HERE");
    return CMD_EXIT_RETURN_VALUE;	
}


/** DISP_MEM_MAP
 * version de la commande disp mem map
 * la fonction affiche le contenu de la carte mémoire du programme
 * @param vmem la mémoire à afficher
 * @return 0 en cas de succes, un nombre positif sinon
 */
 int _disp_mem_mapcmd(mem vmem)
 {
    DEBUG_MSG("La fonction disp_mem_map a été lancée"); //On vérifie que la bonne fonction s'ouvre
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
int _disp_mem_plagescmd(char* addr1, char* addr2, mem vmem)
 {
    DEBUG_MSG("La fonction disp_mem_plages a été lancée"); // On vérifie que la bonne fonction s'ouvre
    int i, no_printf=1;
    unsigned int addr;
    unsigned int addr_end; sscanf(addr2, "%x", &addr_end);
    unsigned int addr_start; sscanf(addr1, "%x", &addr_start);
    int j=0, addr_end2=0;

    if (addr_start < 4096) {addr_start=4096; strcpy(addr1, "0x1000");}
    if (addr_end < 4096) {addr_end=4096; strcpy(addr2, "0x1000");}

    if (addr_end==addr_start)
    {
        addr_end++; // si les bornes sont égales, on affiche la seule valeur existante (ie celle des bornes)
    }

    if (addr_start > addr_end) // si les bornes sont inversées 
    {
        WARNING_MSG("%s : %s sera affiché à la place de %s : %s (car cette plage ne peut exister)", addr2, addr1, addr1, addr2);
        addr=addr_end; addr_end=addr_start; addr_start=addr; // on inverse les bornes 
    }

    printf("Affichage de la plage de données %x : %x \n", addr_start, addr_end);
    for (i = 0; i < 8; ++i)
    {
	if (vmem->seg[i].start._32 <= addr_start && (vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr_start && (vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_end) // si on est dans le bon segment mais que addr_end > fin du segment 
	{
	    addr_end2=addr_end; // on conserve l'adresse de fin initiale 
	    addr_end = vmem->seg[i].start._32 + vmem->seg[i].size._32; 
	}

	if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_start && addr_start < vmem->seg[i+1].start._32)
	{ // si addr_start est entre la fin d'un segment et le début du suivant
	    addr_start = vmem->seg[i+1].start._32; // si addr_start n'est pas dans un segment, on l'initialise au début du segment suivant 
	}

	if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_end && addr_end < vmem->seg[i+1].start._32)
	{ // si addr_end est entre la fin d'un segment et le début du suivant
	    addr_end = vmem->seg[i+1].start._32; // si addr_end n'est pas dans un segment, on l'initialise au début du segment suivant 
	}

        if (vmem->seg[i].start._32 <= addr_start && (vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr_start)  // on vérifie que l'on est dans le bon segment 
        {
            addr = (addr_start - vmem->seg[i].start._32); // on cherche les adresses à afficher dans la mémoire physique
            if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_end)
            { // on vérifie que les bornes sont incluses dans le même segment
                addr_end = vmem->seg[i].start._32 + vmem->seg[i].size._32 + 1; // si ce n'est pas le cas, on s'arrête au dernier octet du segment 
            }

            if (addr_start < addr_end) printf("\nAffichage de la plage de données %x : %x incluse dans le segment %s", addr_start, addr_end, vmem->seg[i].name);

            while (addr_start < addr_end)
            {
		if ((j%16)==0) 
		    {printf("\n"); printf("%08x  ", (vmem->seg[i].start._32)+addr);} // on affiche l'adresse de départ chaque 10 octets 
                printf("%02x  ", vmem->seg[i].content[addr]); addr++; addr_start++; j++;
            }
            no_printf=0; printf("\n");// on a fini l'affichage
             // on récupère la donnée initiale pour le segment suivant 
        }

	if (addr_end2!=0) {addr_start=vmem->seg[i+1].start._32; addr_end=addr_end2; addr_end2=0;j=0;}
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
int _disp_mem_offsetcmd(char* addr1, int offset, mem vmem)
{
    DEBUG_MSG("La fonction disp_mem_offset a été lancée"); // On vérifie que la bonne fonction s'ouvre
    int i, no_printf=1;
    if (offset<0) {offset=-offset; INFO_MSG("La valeur absolue de l'offset a été considéré");}
    char* addr2=calloc(1, sizeof(char)); 

    unsigned int addr;
    unsigned int addr_end; 
    unsigned int addr_start; sscanf(addr1, "%x", &addr_start);
    int j=0, addr_end2=0;

    if (addr_start < 4096) {addr_start=4096; strcpy(addr1, "0x1000");}

unsigned int val2;
sscanf(addr1, "%x", &val2);
val2 += offset;
sprintf(addr2, "%x", val2);
sscanf(addr2, "%x", &addr_end);

    if (addr_end < 4096) {addr_end=4096; strcpy(addr2, "0x1000");}

    if (addr_end==addr_start)
    {
        addr_end++; // si les bornes sont égales, on affiche la seule valeur existante (ie celle des bornes)
    }

    if (addr_start > addr_end) // si les bornes sont inversées 
    {
        WARNING_MSG("%s : %s sera affiché à la place de %s : %s (car cette plage ne peut exister)", addr2, addr1, addr1, addr2);
        addr=addr_end; addr_end=addr_start; addr_start=addr; // on inverse les bornes 
    }

    printf("Affichage de la plage de données %x : %x \n", addr_start, addr_end);
    for (i = 0; i < 8; ++i)
    {
	if (vmem->seg[i].start._32 <= addr_start && (vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr_start && (vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_end) // si on est dans le bon segment mais que addr_end > fin du segment 
	{
	    addr_end2=addr_end; // on conserve l'adresse de fin initiale 
	    addr_end = vmem->seg[i].start._32 + vmem->seg[i].size._32; 
	}

	if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_start && addr_start < vmem->seg[i+1].start._32)
	{ // si addr_start est entre la fin d'un segment et le début du suivant
	    addr_start = vmem->seg[i+1].start._32; // si addr_start n'est pas dans un segment, on l'initialise au début du segment suivant 
	}

	if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_end && addr_end < vmem->seg[i+1].start._32)
	{ // si addr_end est entre la fin d'un segment et le début du suivant
	    addr_end = vmem->seg[i+1].start._32; // si addr_end n'est pas dans un segment, on l'initialise au début du segment suivant 
	}

        if (vmem->seg[i].start._32 <= addr_start && (vmem->seg[i].start._32 + vmem->seg[i].size._32) > addr_start)  // on vérifie que l'on est dans le bon segment 
        {
            addr = (addr_start - vmem->seg[i].start._32); // on cherche les adresses à afficher dans la mémoire physique
            if ((vmem->seg[i].start._32 + vmem->seg[i].size._32) < addr_end)
            { // on vérifie que les bornes sont incluses dans le même segment
                addr_end = vmem->seg[i].start._32 + vmem->seg[i].size._32 + 1; // si ce n'est pas le cas, on s'arrête au dernier octet du segment 
            }

            if (addr_start < addr_end) printf("Affichage de la plage de données %x : %x incluse dans le segment %s", addr_start, addr_end, vmem->seg[i].name);

            while (addr_start < addr_end)
            {
		if ((j%16)==0) 
		    {printf("\n"); printf("%08x  ", (vmem->seg[i].start._32)+addr);} // on affiche l'adresse de départ chaque 10 octets 
                printf("%02x  ", vmem->seg[i].content[addr]); addr++; addr_start++; j++;
            }
            no_printf=0; printf("\n");// on a fini l'affichage
             // on récupère la donnée initiale pour le segment suivant 
        }

	if (addr_end2!=0) {addr_start=vmem->seg[i+1].start._32; addr_end=addr_end2; addr_end2=0;j=0;}
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
 * Fonction qui affiche la valeur contenue dans le registre donné 
 * @param vname le nom du registre à afficher et 
 * @param tab le tableau des registres 
 * @return 0 si réussi, 1 si fail
 */
int _disp_reg_registercmd(char* vname, reg* tab)
{   
    DEBUG_MSG("La fonction disp_reg_register a été lancée"); // on vérifie qu'on se trouve dans la bonne fonction
    int i=0;
    int j=0;
    for (i=0; i<35; i++)
    {
	if(strcmp(vname,tab[i]->name)==0 || strcmp(vname, tab[i]->mnemo)==0) // si le nom vname est un nom de registre 
	{j=i; i=38;}
    }

    if (i==35) // aucun registre ne porte ce nom 
    {
	INFO_MSG("Le registre indiqué n'existe pas");
	return 1;
    }

    if (i==39) // un registre porte le nom ou le mnémo vname 
    {
	INFO_MSG("La valeur du registre est :");
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
    DEBUG_MSG("La fonction disp_reg_all a été lancée"); //On vérifie que la bonne fonction s'ouvre
    int k=4; 
    int j=0;

    INFO_MSG("Voici la liste des registres :");
    while(j!=35)
    {
	j++; // on vérifie une fois chaque registre 
        printf(" %s : %s ",(*tab_reg)->name,(*tab_reg)->data); //Pour chaque registre, on affiche son nom et sa data
        tab_reg++;                                           // On passe au registre suivant
        k--;                                                   //On décrémente k
        if(k==0)
        {
            printf("\n");                                       //On va à la ligne tout les 4 registre
            k=4;
        }
    }
    printf("\n");
    return CMD_OK_RETURN_VALUE;
}


/** RESUME
 * fonction qui reprend l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */
int _resumecmd(interpreteur inter, FILE* fp)
{
  if(fp==0 || inter->mode!=INTERACTIF)
    {
        WARNING_MSG("Cette commande ne sert à rien");
        return 1;
    }
    fp=(inter->file);
    inter->mode=SCRIPT;

    return CMD_OK_RETURN_VALUE;
}


/** ASSERT_REG
 * Fonction qui compare le contenu d'un registre à la valeur val
 * @param r le registre à utiliser
 * @param val la valeur à vérifier
 * @return 0 si les deux valeurs sont identiques, 1 si fail
 */
int _assert_regcmd(reg r, int valeur)
{   
    char* val=calloc(1, sizeof(char));
    sprintf(val, "%d", valeur); // on converti valeur en chaîne de caractère
    DEBUG_MSG("L'ouverture d'assert_reg a fonctionnée"); // On vérifie qu'on est dans la bonne fonction
    if(strcmp((r->data),val)==0) // On compare la valeur entrée avec le contenu du registre
    {
	    INFO_MSG("Les deux valeurs sont identiques");
        return CMD_OK_RETURN_VALUE; // retourne 0 si égal, 1 sinon
    }
    INFO_MSG("Les deux valeurs ne sont pas identiques");
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
    int i; int* a=calloc(1, sizeof(int));
    char* val=calloc(1, sizeof(char)); char* valueaddr=calloc(1, sizeof(char));
    uint32_t addrreelle;

    *a=valeur;
    sprintf(val, "%x", *a); // on converti valeur en chaîne de caractère
    DEBUG_MSG("L'ouverture de la commande assert_byte a fonctionné"); // On vérifie qu'on est dans la bonne fonction

    // on cherche l'adresse à tester
    for (i = 0; i < vmem->nseg; ++i) // on parcourt les segments
    {
	if (i>0 && address < vmem->seg[i].start._32 && address > vmem->seg[i-1].start._32)
	{
	    WARNING_MSG("Cette adresse n'appartient à aucun segment");
	    return 1;
	}

	if (i==0 && address < vmem->seg[i].start._32)
	{
	    WARNING_MSG("Cette adresse n'appartient à aucun segment");
	    return 1;
	}
	
        if (vmem->seg[i].start._32 <= address && (vmem->seg[i].start._32+vmem->seg[i].size._32+1) > address ) // on cherche le segment contenant address
        {
            addrreelle=(address-(vmem->seg[i].start._32)); // on calcule l'adresse réelle à vérifier

	    *a=vmem->seg[i].content[addrreelle]; // on récupère la valeur dans l'adresse
	    sprintf(valueaddr, "%x", *a); // on converti la valeur de l'octet ciblé en char* (sous forme de integer)

            if(strcmp(valueaddr,val)==0) // On compare la valeur entrée avec le contenu de l'adresse
            {
                INFO_MSG("Les deux valeurs sont identiques"); printf("Les deux valeurs sont identiques. \n");
                return CMD_OK_RETURN_VALUE; // retourne 0 si égal, 1 sinon
            } 

        }
	
    }

    INFO_MSG("Les deux valeurs ne sont pas identiques");  printf("Les deux valeurs ne sont pas identiques. \n");
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
    int i; int* a=calloc(1, sizeof(int)); 

    int* value1=calloc(1, sizeof(int)); int* value2=calloc(1, sizeof(int));
    int* value3=calloc(1, sizeof(int)); int* value4=calloc(1, sizeof(int)); // représente les 4 octets à vérifier

    char* val=calloc(1, sizeof(char)); char* valueaddr=calloc(1, sizeof(char));
    uint32_t addrreelle;

    *a=valeur;
    sprintf(val, "%x", *a); // on converti valeur en chaîne de caractère
    DEBUG_MSG("L'ouverture de la commande assert_word a fonctionné"); // On vérifie qu'on est dans la bonne fonction

    // on cherche l'adresse à tester
    for (i = 0; i < vmem->nseg; ++i) // on parcourt les segments
    {
	if (i>0 && address < vmem->seg[i].start._32 && address > (vmem->seg[i-1].start._32+vmem->seg[i-1].size._32))
	{
	    WARNING_MSG("Cette adresse n'appartient à aucun segment");
	    return 1;
	}

	if (i==0 && address < vmem->seg[i].start._32)
	{
	    WARNING_MSG("Cette adresse n'appartient à aucun segment");
	    return 1;
	}
	
        if (vmem->seg[i].start._32 <= address && (vmem->seg[i].start._32+vmem->seg[i].size._32+1) > address ) // on cherche le segment contenant address
        {
            addrreelle=(address-(vmem->seg[i].start._32)); // on calcule l'adresse réelle à vérifier

            *value1=vmem->seg[i].content[addrreelle]; // on récupère chaque byte de l'adresse indiquée
            *value2=vmem->seg[i].content[addrreelle+1];
            *value3=vmem->seg[i].content[addrreelle+2];
            *value4=vmem->seg[i].content[addrreelle+3];
	    *a = (*value4) + 256*(*value3) + 256*256*(*value2) + 256*256*256*(*value1);

	    sprintf(valueaddr, "%x", *a); // on converti la valeur de l'octet ciblé en char*

            if(strcmp(valueaddr,val)==0) // On compare la valeur entrée avec le contenu de l'adresse
            {
                INFO_MSG("Les deux valeurs sont identiques");  printf("Les deux valeurs sont identiques. \n");
                return CMD_OK_RETURN_VALUE; // retourne 0 si égal, 1 sinon
            } 

        }
	
    }

    INFO_MSG("Les deux valeurs ne sont pas identiques");  printf("Les deux valeurs ne sont pas identiques. \n");
    return 1;
}


/** DEBUGCMD
 * fonction qui arrete l'execution d'un script de commande
 * @param inter l'interpreteur qui demande l'analyse
 * @return néant
 */
int _debugcmd(interpreteur inter, FILE* fp)
{
    if(fp==0 || inter->mode!=SCRIPT)
    {
        WARNING_MSG("Cette commande ne sert à rien");
        return 1;
    }

    FILE*f=fp;
    inter->file=f;
    fp=stdin;
    inter->mode=INTERACTIF;
    return CMD_OK_RETURN_VALUE;
}


/** MACHINE_STATE
 * fonction qui décrit la machine à état relative au désassemblage
 * @param cmd la commande qui permet de démarrer la fonction (run, step ou step into)
 * @param address l'adresse à charger dans PC pour démarrer 
 * @param L la liste des breakpoints issue de l'interpréteur
 * @param tab_reg le tableau de registres
 * @param vmem la mémoire contenant le code assembleur (dans .text)
 * @return 0 si réussi, 1 si fail
 */
int _machine_statecmd(char* cmd, char* address, Liste* L, reg* tab_reg, mem vmem)
{
    DEBUG_MSG("Lancement de la machine à état");
    STATE=NOT_S;
    unsigned int PC; sscanf(address, "%x", &PC);
    char* addresschar=calloc(1, sizeof(char));
    int i;
    
    char* instruction=calloc(1, sizeof(char));
    Liste BP=init_liste(); // on crée la liste de breakpoint
    BP=calloc(1, sizeof(Liste));
    BP=*L;

    while (1)
    {
        switch (STATE)
	{
        case NOT_S :
            if (strcmp(cmd, "run")==0) 
                STATE=RUN;
            else if (strcmp(cmd, "step")==0)
            {
                printf("La fonction n'est pas encore implémentée et équivaut actuellement à STEP INTO.\n");
                STATE=RUN;
                BP=add_bp(BP, PC+4);
            }
            else if (strcmp(cmd, "step into")==0)
            {
                BP=add_bp(BP,PC+4);
                STATE=RUN;
            }
            break;

        case RUN :
	    sprintf(addresschar, "%x", PC);
            i=_disasm_range_offsetcmd(addresschar, 0, vmem, tab_reg); // exécute la fonction
            PC+=4; // on passe à la ligne à désassembler suivante 
            if (i==1) STATE=TERM; // en cas d'erreur dans la fonction disasm
            else if(i==CMD_BREAK_RETURN_VALUE) STATE=PAUSE; // on s'arrête à cause de l'instruction BREAK
            else if(i==CMD_EXIT_RETURN_VALUE) STATE=OUT; // on s'arrête à cause de l'instruction SYSCALL - code de service 10
            else if (absent_bp(BP, PC)==0) STATE=PAUSE; // si l'adresse suivante est un breakpoint, on s'arrête avant l'exécution de celle-ci
            else if (PC>(vmem->seg[0].start._32+vmem->seg[0].size._32)) STATE=TERM;
            break;

        case PAUSE :
            scanf("%s", instruction);
            if (strcmp(instruction, "run")==0) 
                STATE=RUN;
            else if (strcmp(instruction, "step into")==0)
            {
//		PC+=4;
                STATE=RUN;
                BP=add_bp(BP, PC+4);
            }
            else if (strcmp(instruction, "step")==0)
            {
//		PC+=4;
                printf("La fonction n'est pas encore implémentée et équivaut actuellement à STEP. \n");
                BP=add_bp(BP, PC+4);
                STATE=RUN;
            }
            else if (strcmp(instruction, "exit")==0)
                STATE=OUT;
            break; 

        case TERM :
            printf("Le désassemblage est terminé. Vous pouvez supprimer la liste de breakpoint ou non (del) et soit recommencé (run, step, step into), soit quitter (exit).\n Pour initialiser une nouvelle liste de breakpoint, veuillez sortir (exit) et utiliser la fonction adéquate (break).\n");
            scanf("%s", instruction);
            if (strcmp(instruction, "del")==0)
            {
                BP=suppr_liste(BP);
            }
            else if (strcmp(instruction, "run")==0)
            {
                sscanf(address, "%x", &PC);
                STATE=RUN;
            }
            else if (strcmp(instruction, "step into")==0)
            {
                sscanf(address, "%x", &PC);
                STATE=RUN;
                BP=add_bp(BP, PC+4);
            }
            else if (strcmp(instruction, "step")==0)
            {
                sscanf(address, "%x", &PC);
                printf("La fonction n'est pas encore implémentée et équivaut actuellement à STEP INTO.\n");
                BP=add_bp(BP, PC+4);
                STATE=RUN;
            }
            else if (strcmp(instruction, "exit")==0)
                STATE=OUT;
            break;

        case OUT :
            *L=BP; // on conserve la liste de breakpoint modifiée
	    if (i==CMD_BREAK_RETURN_VALUE)
	    {
		return 1;
	    }
            return CMD_OK_RETURN_VALUE;
            break;
            
        default :
            // on ne modifie pas la liste de breakpoint en entrée car il y a eu une erreur
            printf("Le désassemblage ne s'est pas déroulé comme prévu.\n");
            return 1;
            break;
	}
    }
}
