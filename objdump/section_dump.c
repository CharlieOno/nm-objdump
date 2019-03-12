/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** section_dump
*/

#include "objdump.h"

char    dump_byte(unsigned char data)
{
    printf("%02x", (data > 0) ? data : 0);
    return ((isprint(data)) ? data : '.');
}

void    section_byte_display(obj_t *core, int i, unsigned char *section_data)
{
    lui     byte = 0;
    char    byte_str[17];

    for (lui idx = 0; idx < SECTION_LIMIT;) {
        printf(" %04x", (unsigned)(core->shdr[i].sh_addr + idx));
        memset(&byte_str, 0, 17);
        for (; byte < 16; byte++) {
            if (byte % 4 == 0)
                printf(" ");
            if (idx + byte >= SECTION_LIMIT) {
                printf("  ");
                byte_str[byte] = ' ';
                continue;
            }
            byte_str[byte] = dump_byte(section_data[idx + byte]);
        }
        idx += byte;
        byte = 0;
        printf("  %s\n", byte_str);
    }
}

void    section_dump(obj_t *core)
{
    printf("\n");
    for (int i = 1; i < core->elf->e_shnum; i++) {
        if (core->shdr[i].sh_type == SHT_SYMTAB)
            break;
        if (strcmp((char*)((void*)core->elf + core->strtable->sh_offset +
        core->shdr[i].sh_name), ".bss") == 0)
            continue;
        printf("Contents of section %s:\n",(char*)((void*)core->elf +
        core->strtable->sh_offset + core->shdr[i].sh_name));
        section_byte_display(core, i, (unsigned char*)((void*)core->elf
        + core->shdr[i].sh_offset));
    }
}