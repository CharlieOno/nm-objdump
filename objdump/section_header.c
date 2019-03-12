/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** core_output
*/

#include "objdump.h"

static name_t const name[18] = {
    {EM_NONE, "None"},
    {EM_M32, "WE32100"},
    {EM_SPARC, "Sparc"},
    {EM_386, "Intel 80386"},
    {EM_68K, "MC68000"},
    {EM_PPC64, "objdumpPowerPC64"},
    {EM_88K, "MC88000"},
    {EM_PARISC, "HPPA"},
    {EM_SPARC32PLUS, "Sparc v8+"},
    {EM_PPC, "PowerPC"},
    {EM_S390, "IBM S/390"},
    {EM_MIPS, "MIPS R3000"},
    {EM_ARM, "ARM"},
    {EM_860, "Intel 80860"},
    {EM_SH, "Renesas / SuperH SH"},
    {EM_SPARCV9, "Sparc v9"},
    {EM_IA_64, "Intel IA-64"},
    {EM_X86_64, "i386:x86-64"}
};

char    *get_name(obj_t *core)
{
    for (int i = 0; i < 18; i++)
        if (name[i].val == core->elf->e_machine)
            return (name[i].name);
    return ("i386:x86-64");
}

char    *get_flag(obj_t *core)
{
    switch (core->elf->e_type) {
        case ET_REL:
            return ("0x00000011:\nHAS_RELOC, HAS_SYMS");
        case ET_EXEC:
            return ("0x00000112:\nEXEC_P, HAS_SYMS, D_PAGED");
        case ET_DYN:
            return ("0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED");
        case ET_CORE:
            return ("Core\n");
    }
    return ("(null)");
}

void    print_header(obj_t *core, char *filename)
{
    printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: %s, flags %s\n", get_name(core), get_flag(core));
    printf("start address 0x%016lx\n", core->elf->e_entry);
}