/*
** EPITECH PROJECT, 2019
** SEMESTRE4
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ctype.h>

#define     MAGIC           "\177ELF"
#define     SECTION_LIMIT   core->shdr[i].sh_size

typedef long unsigned int   lui;

typedef struct obj_s {
    char            **filenames;
    int             return_value;
    int             fd;
    Elf64_Ehdr      *elf;
    Elf64_Shdr      *shdr;
    Elf64_Shdr      *strtable;
} obj_t;

typedef struct name_s {
    unsigned int    val;
    char*           name;
} name_t;

/* core_process.c */
char    **set_filenames(int ac, char **av);
void    process_file(obj_t *core);

/* core_output.c */
void    print_header(obj_t *core, char *filename);

/* section_dump.c */
void    section_dump(obj_t *core);

#endif /* !OBJDUMP_H_ */
