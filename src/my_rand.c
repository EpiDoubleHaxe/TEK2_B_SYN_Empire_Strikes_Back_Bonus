/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** my_rand
*/

#include <stddef.h>

int my_rand(unsigned int *seedptr)
{
    unsigned int seed = 0;

    if (seedptr != NULL) {
        seed = *seedptr;
        *seedptr = *seedptr * 1103515245 + 12345;
    }
    return (unsigned int)(seed / 65536) % 32768;
}
