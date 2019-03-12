/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** symbol_struct
*/

#include "nm.h"

symbol_t    **get_symbol_list(nm_t *core, Elf64_Shdr *shdr, Elf64_Ehdr *elf)
{
    symbol_t    **symbols;

    symbols = malloc(sizeof(symbol_t*) * (NBR_SYMBOLS + 1));
    symbols[NBR_SYMBOLS] = NULL;
    for (long unsigned int i = 1; i < NBR_SYMBOLS; i++) {
        symbols[i] = malloc(sizeof(symbol_t));
        symbols[i]->value = core->symtab_start[i].st_value;
        symbols[i]->type = get_symbol_type(shdr, elf, core->symtab_start[i]);
        symbols[i]->name = &core->symstr[core->symtab_start[i].st_name];
    }
    return (symbols);
}

void    get_symbol_sections(nm_t *core, Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
    for (int i = 0; i < elf->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB) {
            core->symtab_start = (Elf64_Sym*)((void*)elf + shdr[i].sh_offset);
            core->symtab_end = core->symtab_start + shdr[i].sh_size;
            core->symstr = (char*)((void*)elf +
            shdr[shdr[i].sh_link].sh_offset);
        }
    }
}

void    get_symbol_infos(nm_t *core)
{
    void            *buf;
    struct stat     s;
    Elf64_Ehdr      *elf;
    Elf64_Shdr      *shdr;

    fstat(core->fd, &s);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, core->fd, 0);
    elf = buf;
    shdr = (Elf64_Shdr*)(buf + elf->e_shoff);
    get_symbol_sections(core, elf, shdr);
    core->symbols = get_symbol_list(core, shdr, elf);
    core->symbols = sort_symbol_list(core);
}