/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** init_roman
*/

#include "empire.h"
#include <stdlib.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"

roman_t *init_roman(
int belly_size, pthread_mutex_t *mutex_small, pthread_mutex_t *mutex_big)
{
    roman_t *roman = calloc(sizeof(roman_t), 1);

    if (roman == NULL)
        return NULL;
    roman->state = RESTING;
    roman->belly_size = belly_size;
    roman->rand_seed = calloc(sizeof(unsigned int), 1);
    if (roman->rand_seed == NULL)
        return NULL;
    (*roman->rand_seed) = time(NULL) + (unsigned int)(roman);
    roman->fork_small = mutex_small;
    roman->fork_big = mutex_big;
    return roman;
}

void destroy_roman(roman_t *roman)
{
    free(roman->rand_seed);
    free(roman);
}

pthread_mutex_t *init_mutexes(int nb)
{
    pthread_mutex_t *ret = calloc(sizeof(pthread_mutex_t), nb);

    if (ret == NULL)
        return NULL;
    for (int j = 0; j < nb; ++j)
        if (pthread_mutex_init(&ret[j], NULL) != 0)
            return NULL;
    return ret;
}

pthread_mutex_t *init_threads(int nb)
{
    pthread_mutex_t *ret = calloc(sizeof(pthread_mutex_t), nb);

    if (ret == NULL)
        return NULL;
    for (int j = 0; j < nb; ++j)
        if (pthread_mutex_init(&ret[j], NULL) != 0)
            return NULL;
    return NULL;
}

#pragma GCC diagnostic pop
