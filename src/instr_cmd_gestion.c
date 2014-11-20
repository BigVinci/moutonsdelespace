#include "../include/common/instr_cmd_gestion.h"

/* **************************************************************************************************** */
/*                           Copie de fonctions présentes dans cmd_gestion.c                            */


/** SET_MEM_BYTE
 * version de la commande set mem byte
 * la fonction affecte une valeur dans la mémoire à l'adresse indiquée
 * @param byteValue la valeur à affecter
 * @param vaddr l'adresse où écrire la valeur, doit appartenir à un des segments suivants :  
 * @param vmem mémoire contenant l'adresse où doit être affectée la valeur
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _set_mem_bytecmd_2(uint8_t byteValue, uint32_t vaddr, mem vmem)
{
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
            // on cherche l'adresse réelle exacte 
            addrreelle = (vaddr - vmem->seg[i].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[i].content)+addrreelle) = byteValue;

            return CMD_OK_RETURN_VALUE;
        }
        else if (vmem->seg[6].start._32 <= vaddr) // on regarde si addr est dans le dernier segment 
        {
            // on cherche l'adresse réelle exacte 
            addrreelle = (vaddr - vmem->seg[6].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[6].content)+addrreelle) = byteValue;

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
int _set_mem_wordcmd_2(uint32_t wordValue, uint32_t vaddr, mem vmem)
{
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

            // on cherche l'adresse réelle exacte 
            addrrelle = (vaddr - vmem->seg[6].start._32);

            // on modifie la mémoire en gardant la représentation big endian 
            *((vmem->seg[6].content)+addrrelle) = byteValue[0];
            *((vmem->seg[6].content)+addrrelle+1) = byteValue[1];
            *((vmem->seg[6].content)+addrrelle+2) = byteValue[2];
            *((vmem->seg[6].content)+addrrelle+3) = byteValue[3];

            return CMD_OK_RETURN_VALUE;
        }
    }
    ERROR_MSG("SHOULD NEVER BE HERE");
    return CMD_EXIT_RETURN_VALUE;
}


/** DISP_REG_REGISTER
 * Fonction qui affiche la valeur contenue dans le registre donné 
 * @param vname le nom du registre à afficher et 
 * @param tab le tableau des registres 
 * @return 0 si réussi, 1 si fail
 */
int _disp_reg_registercmd_2(char* vname, reg* tab)
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


/** DISP_MEM_OFFSET
 * version de la commande disp mem reg
 * la fonction affiche une partie de la mémoire 
 * @param token indique les deux adresses séparées par ":"
 * @param vmem représente la mémoire
 * @return 0 en cas de succes, un nombre positif sinon
 */
int _disp_mem_offsetcmd_2(char* addr1, int offset, mem vmem)
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
