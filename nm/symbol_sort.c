/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** symbol_sort
*/

#include "nm.h"

void        swap_symbol(symbol_t *a, symbol_t *b)
{
    symbol_t *swap = malloc(sizeof(symbol_t));

    swap->value = b->value;
    swap->type = b->type;
    swap->name = malloc(sizeof(char) * (strlen(b->name) + 1));
    swap->name[0] = 0;
    swap->name = strcat(swap->name, b->name);
    swap->name[strlen(b->name)] = 0;
    b->value = a->value;
    b->type = a->type;
    b->name = a->name;
    a->value = swap->value;
    a->type = swap->type;
    a->name = swap->name;
}

int         compare_symbol_name(char *a, char *b)
{
    int idx_a = 0;
    int idx_b = 0;

    for (; a[idx_a] == '_'; idx_a++);
    for (; b[idx_b] == '_'; idx_b++);
    if (strcmp(a + idx_a, b + idx_b) == 0)
        return (idx_b > idx_a);
    while (1) {
        if (a[idx_a] == 0 || b[idx_b] == 0)
            return ((b[idx_b] == 0) ? 1 : 0);
        for (; !isalnum(a[idx_a]); idx_a++);
        for (; !isalnum(b[idx_b]); idx_b++);
        if (tolower(a[idx_a]) != tolower(b[idx_b]))
            return (tolower(a[idx_a]) - tolower(b[idx_b]));
        idx_a += 1;
        idx_b += 1;
    }
    return (0);
}

symbol_t    **sort_symbol_list(nm_t *core)
{
    symbol_t    **res;
    long unsigned int i = 0;
    long unsigned int j = 0;

    res = malloc(sizeof(symbol_t*) * (NBR_SYMBOLS + 1));
    for (long unsigned int i = 1; i < NBR_SYMBOLS; i++)
        res[i] = core->symbols[i];
    for (i = 1; i < NBR_SYMBOLS; i++)
        for (j = 1; j < NBR_SYMBOLS - i; j++)
            if (compare_symbol_name(res[j]->name, res[j + 1]->name) > 0)
                swap_symbol(res[j], res[j + 1]);
    return (res);
}