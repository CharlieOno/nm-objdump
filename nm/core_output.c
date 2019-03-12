/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** core_output
*/

#include "nm.h"

void    print_title(int ac, char *filename)
{
    if (ac >= 3)
        printf("\n%s:\n", filename);
}

void    print_informations(symbol_t *symbol)
{
    if (symbol->value)
        printf("%016lx %c %s\n", symbol->value,
        symbol->type, symbol->name);
    else
        printf("                 %c %s\n", symbol->type,
        symbol->name);
}

void    print_symbols(nm_t *core)
{
    for (long unsigned int i = 1; i < NBR_SYMBOLS; i++) {
        if (strlen(core->symbols[i]->name) == 0 ||
        core->symbols[i]->type == STT_NOTYPE ||
        core->symbols[i]->type == STT_COMMON ||
        core->symbols[i]->type == 'A' ||
        core->symbols[i]->type == 'a')
            continue;
        print_informations(core->symbols[i]);
    }
}