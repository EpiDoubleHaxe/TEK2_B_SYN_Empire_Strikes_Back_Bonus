/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** empire
*/

#pragma once

#include "pthread.h"

enum roman_state_e {
    EATING,
    THINKING,
    RESTING
} typedef roman_state_t;

struct roman_s {
    roman_state_t state;
    pthread_mutex_t *fork_small;
    pthread_mutex_t *fork_big;
    int belly_size;
    unsigned int *rand_seed;
} typedef roman_t;

int empire(int meals, int nb_r);
int my_rand(unsigned int *seedptr);
void roman_eat(roman_t *roman);
void roman_think(roman_t *roman);
void roman_sleep(roman_t *roman);

roman_t *init_roman(int belly_size, pthread_mutex_t *mutex_small,
                    pthread_mutex_t *mutex_big);
void destroy_roman(roman_t *roman);

int mutex_lock(pthread_mutex_t *mutex);
int mutex_unlock(pthread_mutex_t *mutex);
int mutex_trylock(pthread_mutex_t *mutex);

pthread_mutex_t *init_mutexes(int nb);
