/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** symbol_type
*/

#include "nm.h"

char    symbol_weak_type(char type, Elf64_Sym symtab)
{
    if (ELF64_ST_BIND(symtab.st_info) == STB_WEAK) {
        type = 'W';
        if (symtab.st_shndx == SHN_UNDEF)
            type = 'w';
    }
    if (ELF64_ST_BIND(symtab.st_info) == STB_WEAK
    && ELF64_ST_TYPE(symtab.st_info) == STT_OBJECT) {
        type = 'V';
        if (symtab.st_shndx == SHN_UNDEF)
            type = 'v';
    }
    return (type);
}

char    symbol_from_list_type(char type, Elf64_Sym symtab, Elf64_Ehdr *elf,
Elf64_Shdr *shdr)
{
    static type_t   typelist[] = {
        {SHT_DYNAMIC, SHF_ALLOC | SHF_WRITE, 'D'},
        {SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR, 'T'},
        {SHT_PROGBITS, SHF_ALLOC | SHF_WRITE, 'D'},
        {SHT_PROGBITS, SHF_ALLOC, 'R'},
        {SHT_NOBITS, SHF_ALLOC | SHF_WRITE, 'B'},
        {SHT_NULL, 0, 'U'},
        {SHT_PROGBITS, 0, 'R'},
        {0, 0, 0}
    };

    for (int i = 0; typelist[i].c != 0; i++) {
        if (symtab.st_shndx >= elf->e_shnum)
            continue;
        if (shdr[symtab.st_shndx].sh_type == typelist[i].type
        && shdr[symtab.st_shndx].sh_flags == typelist[i].flags)
            type = typelist[i].c;
    }
    return (type);
}

char    symbol_array_type(char type, Elf64_Sym symtab, Elf64_Ehdr *elf,
Elf64_Shdr *shdr)
{
    if (symtab.st_shndx >= elf->e_shnum)
        return (type);
    if (shdr[symtab.st_shndx].sh_type == SHT_FINI_ARRAY
    || shdr[symtab.st_shndx].sh_type == SHT_INIT_ARRAY)
        type = 'T';
    return (type);
}

char    symbol_comabs_type(char type, Elf64_Sym symtab)
{
    if (symtab.st_shndx == SHN_COMMON)
        type = 'C';
    if (symtab.st_shndx == SHN_ABS)
        type = 'A';
    return (type);
}

char    get_symbol_type(Elf64_Shdr *shdr, Elf64_Ehdr *elf, Elf64_Sym symtab)
{
    char    type = '?';

    type = symbol_comabs_type(type, symtab);
    type = symbol_array_type(type, symtab, elf, shdr);
    type = symbol_from_list_type(type, symtab, elf, shdr);
    if (ELF64_ST_BIND(symtab.st_info) == STB_LOCAL)
        type += 32;
    if (ELF64_ST_BIND(symtab.st_info) == STB_GNU_UNIQUE)
        type = 'u';
    type = symbol_weak_type(type, symtab);
    return (type);
}