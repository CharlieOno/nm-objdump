/*
** EPITECH PROJECT, 2019
** SEMESTRE4
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ctype.h>

#define     NBR_SYMBOLS     ((core->symtab_end - core->symtab_start) / \
                            sizeof(symbol_t))
#define     MAGIC           "\177ELF"

typedef struct type_s {
    Elf64_Word              type;
    Elf64_Xword             flags;
    char                    c;
} type_t;

typedef struct symbol_s {
    long unsigned int       value;
    char                    type;
    char                    *name;
} symbol_t;

typedef struct nm_s {
    char            **filenames;
    int             return_value;
    int             fd;
    Elf64_Sym       *symtab_start;
    Elf64_Sym       *symtab_end;
    char            *symstr;
    symbol_t        **symbols;
} nm_t;

// typedef struct type_s {
// } type_t;

/* symbol_sort.c */
symbol_t    **sort_symbol_list(nm_t *core);

/* symbol_type.c */
char    get_symbol_type(Elf64_Shdr *shdr, Elf64_Ehdr *elf, Elf64_Sym symtab);

/* symbol_struct.c */
void        get_symbol_infos(nm_t *core);
void        get_symbol_sections(nm_t *core, Elf64_Ehdr *elf, Elf64_Shdr *shdr);
symbol_t    **get_symbol_list(nm_t *core, Elf64_Shdr *shdr, Elf64_Ehdr *elf);

/* core_process.c */
char    **set_filenames(int ac, char **av);
void    process_file(nm_t *core, int ac);

/* core_output.c */
void    print_title(int ac, char *filename);
void    print_symbols(nm_t *core);

#endif /* !NM_H_ */
