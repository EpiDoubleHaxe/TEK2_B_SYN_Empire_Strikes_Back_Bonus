/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** csfml_empire
*/

#pragma once

#include "empire.h"
#include <SFML/Graphics.h>

struct csf_roman_s {
    roman_state_t state;
    int belly_size;
    sfSprite *sprite;
} typedef csf_roman_t;

struct csf_fork_s {
    int owner;
    sfSprite *sprite;
} typedef csf_fork_t;

struct csf_game_s {
    csf_roman_t **romans;
    csf_fork_t **forks;
    sfTexture *romanText;
    sfTexture *roman_sleep_text;
    sfTexture *roman_think_text;
    sfTexture *forkText;
    int nb_romans;
    int starting_belly_size;
    sfCircleShape *table;
} typedef csf_game_t;

enum csf_command_type_e {
    csf_cmd_none = -1,
    csf_cmd_eat,
    csf_cmd_think,
    csf_cmd_sleep,
    csf_cmd_take_fork,
    csf_cmd_release_fork,
} typedef csf_command_type_t;

struct csf_command_payload_s {
    csf_command_type_t command_type;
    int id;
    int target;
} typedef csf_command_payload_t;

int csfml(int nb_romans, int belly_size, int read_fd);
sfCircleShape *init_table();
csf_game_t *init_csf_game(int nb_romans, int belly_size);
void destroy_csf_game(csf_game_t *game);
void draw_game(sfRenderWindow *window, csf_game_t *game);
