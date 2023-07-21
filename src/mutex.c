/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** mutex
*/

#include "extern.h"
#include <pthread.h>

int mutex_lock(pthread_mutex_t *mutex)
{
    int ret = pthread_mutex_lock(mutex);
    lempire_take_fork(mutex);
    return ret;
}

int mutex_unlock(pthread_mutex_t *mutex)
{
    int ret = pthread_mutex_unlock(mutex);

    lempire_release_fork(mutex);
    return ret;
}

int mutex_trylock(pthread_mutex_t *mutex)
{
    int ret = pthread_mutex_trylock(mutex);

    if (ret == 0) {
        lempire_take_fork(mutex);
        return ret;
    }
    return ret;
}
