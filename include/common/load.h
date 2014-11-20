#ifndef _LOAD_H_
#define _LOAD_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bits.h"
#include "notify.h"
#include "../elf/elf.h"
#include "../elf/syms.h"
#include "../mem.h"
#include "../elf/relocator.h"

// On fixe ici une adresse basse dans la mémoire virtuelle. Le premier segment
// ira se loger à cette adresse.
#define START_MEM 0x1000
// nombre max de sections que l'on extraira du fichier ELF
#define NB_SECTIONS 4

// nom de chaque section
#define TEXT_SECTION_STR ".text"
#define RODATA_SECTION_STR ".rodata"
#define DATA_SECTION_STR ".data"
#define BSS_SECTION_STR ".bss"
#define HEAP_SECTION_STR "[heap]"
#define PILE_SECTION_STR "[stack]"
#define LIB_SECTION_STR "[lib]"
#define VSYSCALL_SECTION_STR "[vsyscall]"


int _load_section_in_memory(mem memory, char* scn,unsigned int permissions,unsigned long long add_start);
int is_in_symbols(char* name, stab symtab);
unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections);
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start);
void print_segment_raw_content(segment* seg);
void reloc_segment(FILE* fp, segment seg, mem memory,unsigned int endianness,stab symtab);
mem load(char* name);

#endif /* _LOAD_H_ */
