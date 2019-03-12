/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** core_process
*/

#include "objdump.h"

char    **set_filenames(int ac, char **av)
{
    char **filenames = NULL;

    if (ac == 1) {
        filenames = malloc(sizeof(char*) * 2);
        filenames[0] = malloc(sizeof(char) * strlen("a.out"));
        filenames[0] = strcpy(filenames[0], "a.out");
        filenames[1] = NULL;
        return (filenames);
    }
    return (av + 1);
}

int    check_elf(obj_t *core, int i)
{
    void            *buf;
    struct stat     s;
    Elf64_Ehdr      *elf;

    fstat(core->fd, &s);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, core->fd, 0);
    elf = buf;
    if (buf == MAP_FAILED)
        return (0);
    if (memcmp(elf, MAGIC, 4)) {
        fprintf(stderr, "objdump: %s: File format not recognized\n",
        core->filenames[i]);
        return (0);
    }
    return (1);
}

void    set_elf(obj_t *core)
{
    void            *buf;
    struct stat     s;

    fstat(core->fd, &s);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, core->fd, 0);
    core->elf = buf;
    core->shdr = (Elf64_Shdr*)(buf + core->elf->e_shoff);
    core->strtable = &core->shdr[core->elf->e_shstrndx];
}

void    process_file(obj_t *core)
{
    for (int i = 0; core->filenames[i] != NULL; i++) {
        core->fd = open(core->filenames[i], O_RDONLY);
        if (core->fd == -1) {
            core->return_value += 1;
            fprintf(stderr, "objdump: '%s': No such file\n",
            core->filenames[i]);
            continue;
        }
        if (check_elf(core, i) == 0)
            continue;
        set_elf(core);
        print_header(core, core->filenames[i]);
        section_dump(core);
    }
}