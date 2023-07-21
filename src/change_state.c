/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** change_state
*/

#include "empire.h"
#include "extern.h"
#include <unistd.h>

void roman_eat(roman_t *roman)
{
    roman->state = EATING;
    roman->belly_size -= 1;
    lempire_eat();
    usleep(300 + (my_rand(roman->rand_seed) % 100));
}

void roman_think(roman_t *roman)
{
    roman->state = THINKING;
    lempire_think();
    usleep(300 + (my_rand(roman->rand_seed) % 100));
}

void roman_sleep(roman_t *roman)
{
    roman->state = RESTING;
    lempire_sleep();
}
