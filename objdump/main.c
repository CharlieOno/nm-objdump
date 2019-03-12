/*
** EPITECH PROJECT, 2019
** SEMESTRE4
** File description:
** main
*/

#include "objdump.h"

int     main(int ac, char **av)
{
    obj_t    *core = malloc(sizeof(obj_t));

    core->filenames = set_filenames(ac, av);
    core->return_value = 0;
    core->fd = 0;
    process_file(core);
    return (0);
}