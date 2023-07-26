/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** mutex
*/

#include "empire.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int mutex_lock(roman_t *roman, pthread_mutex_t *mutex)
{
    char str[16];
    int ret = pthread_mutex_lock(mutex);

    if (mutex == roman->fork_small)
        sprintf(str, "LOCK %d %d\n", roman->id, roman->fork_small_id);
    else
        sprintf(str, "LOCK %d %d\n", roman->id, roman->fork_big_id);
    //write(roman->write_fd, str, strlen(str));
    return ret;
}

int mutex_unlock(roman_t *roman, pthread_mutex_t *mutex)
{
    char str[16];
    int ret = pthread_mutex_unlock(mutex);

    if (mutex == roman->fork_small)
        sprintf(str, "UNLOCK %d\n", roman->fork_small_id);
    else
        sprintf(str, "UNLOCK %d\n", roman->fork_big_id);
    //write(roman->write_fd, str, strlen(str));
    return ret;
}

int mutex_trylock(roman_t *roman, pthread_mutex_t *mutex)
{
    char str[16];
    int ret = pthread_mutex_trylock(mutex);

    if (ret == 0) {
        if (mutex == roman->fork_small)
            sprintf(str, "LOCK %d %d\n", roman->id, roman->fork_small_id);
        else
            sprintf(str, "LOCK %d %d\n", roman->id, roman->fork_big_id);
        //write(roman->write_fd, str, strlen(str));
        return ret;
    }
    return ret;
}
