/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** empire
*/

#pragma once

#include "pthread.h"

enum roman_state_e
{
    EATING,
    THINKING,
    RESTING
} typedef roman_state_t;

struct roman_s
{
    roman_state_t state;
    pthread_mutex_t *fork_small;
    int fork_small_id;
    pthread_mutex_t *fork_big;
    int fork_big_id;
    int belly_size;
    unsigned int *rand_seed;
    int write_fd;
    int id;
} typedef roman_t;

int empire(int meals, int nb_r);
int my_rand(unsigned int *seedptr);
void roman_eat(roman_t *roman);
void roman_think(roman_t *roman);
void roman_sleep(roman_t *roman);

roman_t *init_roman(
int belly_size, pthread_mutex_t *mutex_small, pthread_mutex_t *mutex_big,
int write_fd, int id, int fork_id_small, int fork_id_big);
void destroy_roman(roman_t *roman);

int mutex_lock(roman_t *roman, pthread_mutex_t *mutex);
int mutex_unlock(roman_t *roman, pthread_mutex_t *mutex);
int mutex_trylock(roman_t *roman, pthread_mutex_t *mutex);

pthread_mutex_t *init_mutexes(int nb);
