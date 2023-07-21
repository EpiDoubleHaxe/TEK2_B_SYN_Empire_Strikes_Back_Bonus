/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** empire
*/

#include "empire.h"
#include <stdlib.h>
#include <unistd.h>

void *roman_rountine(roman_t *roman)
{
    int ret = 0;

    while (roman->belly_size > 0) {
        mutex_lock(roman->fork_small);
        if (
        mutex_trylock(roman->fork_big) != 0) {
            roman_think(roman);
            mutex_lock(roman->fork_big);
        }
        roman_eat(roman);
        mutex_unlock(roman->fork_big);
        mutex_unlock(roman->fork_small);
        roman_sleep(roman);
    }
    destroy_roman(roman);
    pthread_exit(&ret);
}

int empire(int meals, int nb_r)
{
    pthread_t *threads = calloc(sizeof(pthread_t), nb_r);
    pthread_mutex_t *mutex = init_mutexes(nb_r);

    if (mutex == NULL || threads == NULL)
        return 84;
    for (int k = 0; k < nb_r - 1; k++)
        if (pthread_create(threads + k, NULL, (void *(*)(void *))roman_rountine,
        init_roman(meals, &mutex[k], &mutex[k + 1])) != 0)
            return 84;
    if (
    pthread_create(threads + nb_r - 1, NULL, (void *(*)(void *))roman_rountine,
    init_roman(meals, mutex, &mutex[nb_r - 1])) != 0)
        return 84;
    for (int i = 0; i < nb_r; i++) {
        pthread_join(threads[i], NULL);
        pthread_mutex_destroy(&mutex[i]);
    }
    free(threads);
    free(mutex);
    return 0;
}
