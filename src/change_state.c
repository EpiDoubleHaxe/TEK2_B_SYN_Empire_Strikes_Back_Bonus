/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** change_state
*/

#include "empire.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void roman_eat(roman_t *roman)
{
    char str[16];

    sprintf(str, "EAT %d\n", roman->id);
    roman->state = EATING;
    roman->belly_size -= 1;
    write(roman->write_fd, str, strlen(str));
}

void roman_think(roman_t *roman)
{
    char str[16];

    sprintf(str, "THINK %d\n", roman->id);
    roman->state = THINKING;
    write(roman->write_fd, str, strlen(str));
}

void roman_sleep(roman_t *roman)
{
    char str[16];

    sprintf(str, "SLEEP %d\n", roman->id);
    roman->state = RESTING;
    write(roman->write_fd, str, strlen(str));
}
