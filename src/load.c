#include <stdio.h>
#include <stdlib.h>
#include "../include/common/bits.h"
#include "../include/common/notify.h"
#include "../include/elf/elf.h"
#include "../include/elf/syms.h"
#include "../include/mem.h"

// On fixe ici une adresse basse dans la m�moire virtuelle. Le premier segment
// ira se loger � cette adresse.
#define START_MEM 0x1000
// nombre max de sections que l'on extraira du fichier ELF
#define NB_SECTIONS 4

// nom de chaque section
#define TEXT_SECTION_STR ".text"
#define RODATA_SECTION_STR ".rodata"
#define DATA_SECTION_STR ".data"
#define BSS_SECTION_STR ".bss"
#define PILE_SECTION_STR "[stack]"
#define LIB_SECTION_STR "[lib]"
#define VSYSCALL_SECTION_STR "[vsyscall]"


// Fonction permettant de verifier si une chaine de caracteres
// est bien dans la liste des symboles du fichier ELF
// parametres :
// 		name : le nom de la chaine recherch�e
//  		symtab : la table des symboles
//
// retourne 1 si present, 0 sinon
int is_in_symbols(char* name, stab symtab) {
    int i;
    for (i=0; i<symtab.size; i++) {
        if (!strcmp(symtab.sym[i].name,name)) return 1;
    }
    return 0;
}

// Cette fonction calcule le nombre de segments � prevoir
// Elle cherche dans les symboles si les sections predefinies
// s'y trouve
// parametres :
//  		symtab : la table des symboles
//
// retourne le nombre de sections trouv�es

unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections) {
    unsigned int n=0;
    int i;
    for (i=0; i<nb_sections; i++) {
        if (is_in_symbols(section_names[i],symtab)) n++; /* si le nom section_names[i] est dans la liste des symboles du fichier ELF, incr�mente */ 
    }
    return n;
}


// fonction permettant d'extraire une section du fichier ELF et de la charg�e dans le segment du m�me nom
// parametres :
//   fp         : le pointeur du fichier ELF
//   memory     : la structure de m�moire virtuelle
//   scn        : le nom de la section � charger
//   permission : l'entier repr�sentant les droits de lecture/ecriture/execution
//   add_start  : l'addresse virtuelle � laquelle la section doit �tre charg�e
//
// retourne 0 en cas de succes, une valeur non nulle sinon
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start) 
{
    byte *ehdr    = __elf_get_ehdr( fp );
    byte *content = NULL;
    uint  textsz  = 0;
    vsize sz;
    vaddr addr;

    byte *useless = elf_extract_section_header_table( ehdr, fp );
    free( useless );

    if ( NULL == ehdr ) 
    {
        WARNING_MSG( "Can't read ELF file" );
        return 1;
    }

    if ( 1 == attach_scn_to_mem(memory, scn, SCN_ATTR( WIDTH_FROM_EHDR( ehdr ), permissions ) ) ) 
    {
        WARNING_MSG( "Unable to create %s section", scn );
        free( ehdr );
        return 1;
    }

    content = elf_extract_scn_by_name( ehdr, fp, scn, &textsz, NULL );
    if ( NULL == content ) {
        WARNING_MSG( "Corrupted ELF file" );
        free( ehdr );
        return 1;
    }

    switch( WIDTH_FROM_EHDR(ehdr) ) {
    case 32 :
        sz._32   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._32 = add_start;
        break;
    case 64 :
        sz._64   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._64 = add_start;
        break;
    default :
        WARNING_MSG( "Wrong machine width" );
        return 1;
    }

    if ( 1 == fill_mem_scn(memory, scn, sz, addr, content ) ) {
        free( ehdr );
        free( content );
        WARNING_MSG( "Unable to fill in %s segment", scn );
        return 1;
    }

    free( content );
    free( ehdr );

    return 0;
}

// fonction affichant les octets d'un segment sur la sortie standard
// parametres :
//   		seg	: le segment de la m�moire virtuelle � afficher

void print_segment_raw_content(segment* seg) {
    int k;
    int word =0;
    if (seg!=NULL && seg->size._32>0) { /* on v�rifie que le segment n'est pas vide */ 
        for(k=0; k<seg->size._32; k+=4) { /* on lit chaque donn�e pr�sente dans le segment � afficher */ 
            if(k%16==0) printf("\n  0x%08x ",k); 	/* affiche l'adresse lue chaque multiple de 16 et retourne � la ligne � la fin d'un octet */
            word = *((unsigned int *) (seg->content+k));
            FLIP_ENDIANNESS(word);
            printf("%08x ",	word);  /* affiche chaque octet d'un segment */ 
        }
    }
}


// la fonction charge un fichier elf en entr�e en utilisant
// les arguments du prototype de la fonction main (cf. fiches infos)
//
mem load(char* name) 
{

    char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR}; 	/* 4 sections dont les noms ont �t� d�finie ci-dessus */ 
    unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};						/* d�crit les diff�rentes permissions possibles */ 
    unsigned int nsegments;		/* nombre de segment de m�moire */ 
    int i=0,j=0;
    unsigned int type_machine;
    unsigned int endianness;   //little ou big endian
    unsigned int bus_width;    // 32 bits ou 64bits
    unsigned int next_segment_start = START_MEM; // compteur pour designer le d�but de la prochaine section

    mem memory;  // memoire virtuelle, c'est elle qui contiendra toute les donn�es du programme
    stab symtab= new_stab(0); // table des symboles
    FILE * pf_elf;


    if ((pf_elf = fopen(name,"r")) == NULL) { /* si le fichier ne s'ouvre pas, on affiche un message erreur */
        ERROR_MSG("cannot open file %s", name);
    }

    if (!assert_elf_file(pf_elf)) /* si le fichier ne peut �tre lu, on affiche un message erreur */
        ERROR_MSG("file %s is not an ELF file", name);


    // recuperation des info de l'architecture
    elf_get_arch_info(pf_elf, &type_machine, &endianness, &bus_width);
    // et des symboles
    elf_load_symtab(pf_elf, bus_width, endianness, &symtab);


    nsegments = get_nsegments(symtab,section_names,NB_SECTIONS); /* ici, nsegments passe � 4 */

    // allouer la memoire virtuelle
    memory=init_mem(nsegments+3); /* nsegments incr�ment� pour pr�voir la pile et [vssyscall] */

    // Ne pas oublier d'allouer les differentes sections
    j=0;
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],symtab)) {
            elf_load_section_in_memory(pf_elf,memory, section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start+= ((memory->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k supp�rieur
//          print_segment_raw_content(&memory->seg[j]); /* affiche le contenu initial du segment */ 
            j++;
        }
    }

/* alloue le segment [lib] */
    vm->seg[NB_SECTIONS+1].name                  = "[lib]";     /* nom du segment */
    vm->seg[NB_SECTIONS+1].content               = NULL;        /* il n'y a aucune donn�e dans le segment */
    vm->seg[NB_SECTIONS+1].start._64             = 0x5000;      /* adresse de d�part du segment */
    vm->seg[NB_SECTIONS+1].size._64              = 0x0;         /* le segment est initialement vide */ 
    vm->seg[NB_SECTIONS+1].attr                  = r--;         /* permission sur le segment */

/* alloue la pile */
    vm->seg[NB_SECTIONS+2].name                  = "[stack]";   /* nom du segment */
    vm->seg[NB_SECTIONS+2].content               = NULL;        /* il n'y a aucune donn�e dans le segment */
    vm->seg[NB_SECTIONS+2].start._64             = 0xff7ff000;  /* adresse de d�part du segment */
    vm->seg[NB_SECTIONS+2].size._64              = 0x0;         /* le segment est initialement vide */
    vm->seg[NB_SECTIONS+2].attr                  = rw-;         /* permission sur le segment */

/* alloue le segment pour les appels systemes */
    vm->seg[NB_SECTIONS+3].name                  = "[vsyscall]";/* nom du segment */
    vm->seg[NB_SECTIONS+3].content               = NULL;        /* il n'y a aucune donn�e dans le segment */
    vm->seg[NB_SECTIONS+3].start._64             = 0xfffff000;  /* adresse de d�part du segment */
    vm->seg[NB_SECTIONS+3].size._64              = 0x0;         /* le segment est initialement vide */
    vm->seg[NB_SECTIONS+3].attr                  = r-x;         /* permission sur le segment */

    printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", name) ;
    print_mem(memory); /* affiche le contenu de la m�moire */ 
    stab32_print( symtab);	/* affiche les symboles contenus dans le tableau symtab */ 

    // on fait le m�nage avant de partir
    del_mem(memory);
    del_stab(symtab);
    fclose(pf_elf);
    puts("");
    return memory;
}
