/*
** EPITECH PROJECT, 2019
** SEMESTRE4
** File description:
** main
*/

#include "nm.h"

int     main(int ac, char **av)
{
    nm_t    *core = malloc(sizeof(nm_t));

    core->filenames = set_filenames(ac, av);
    core->return_value = 0;
    core->fd = 0;
    process_file(core, ac);
    return (core->return_value);
}