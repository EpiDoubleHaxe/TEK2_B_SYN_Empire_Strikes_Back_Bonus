/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** init_csfml
*/

#include "csfml_empire.h"
#include "empire.h"
#include "math.h"
#include <stdlib.h>

sfCircleShape *init_table()
{
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setPosition(circle, (sfVector2f){400, 300});
    sfCircleShape_setRadius(circle, 300);
    sfCircleShape_setOrigin(circle, (sfVector2f){300, 300});
    sfCircleShape_setFillColor(circle, sfColor_fromRGB(153, 76, 0));
    return circle;
}

csf_roman_t *
init_csf_roman(int belly_size, sfTexture *text, sfVector2f pos, float angle)
{
    csf_roman_t *roman = calloc(sizeof(csf_roman_t), 1);

    if (roman == NULL)
        return NULL;
    roman->belly_size = belly_size;
    roman->state = RESTING;
    roman->sprite = sfSprite_create();
    sfSprite_setTexture(roman->sprite, text, sfTrue);
    sfSprite_setPosition(roman->sprite, pos);
    sfSprite_setOrigin(roman->sprite, (sfVector2f){10, 10});
    sfSprite_setRotation(roman->sprite, angle);
    sfSprite_setScale(roman->sprite, (sfVector2f){2, 2});
    return roman;
}

void destroy_csf_roman(csf_roman_t *roman)
{
    sfSprite_destroy(roman->sprite);
    free(roman);
}

csf_fork_t *init_csf_fork(sfTexture *text, sfVector2f pos, float angle)
{
    csf_fork_t *fork = calloc(sizeof(csf_roman_t), 1);

    if (fork == NULL)
        return NULL;
    fork->owner = -1;
    fork->sprite = sfSprite_create();
    sfSprite_setTexture(fork->sprite, text, sfTrue);
    sfSprite_setPosition(fork->sprite, pos);
    sfSprite_setOrigin(fork->sprite, (sfVector2f){10, 15});
    sfSprite_setRotation(fork->sprite, angle);
    return fork;
}

void destroy_fork(csf_fork_t *fork)
{
    sfSprite_destroy(fork->sprite);
    free(fork);
}

csf_game_t *init_csf_game(int nb_romans, int belly_size)
{
    csf_game_t *game = calloc(sizeof(csf_game_t), 1);

    game->table = init_table();
    game->nb_romans = nb_romans;
    game->starting_belly_size = belly_size;
    game->romanText = sfTexture_createFromFile("assets/romanus.png", NULL);
    game->roman_think_text =
    sfTexture_createFromFile("assets/romanus_think.png", NULL);
    game->roman_sleep_text =
    sfTexture_createFromFile("assets/romanus_sleep.png", NULL);
    game->forkText = sfTexture_createFromFile("assets/fork.png", NULL);
    game->romans = calloc(sizeof(csf_roman_t *), nb_romans);
    game->forks = calloc(sizeof(csf_fork_t *), nb_romans);
    for (int i = 0; i < nb_romans; ++i) {
        game->romans[i] = init_csf_roman(
        belly_size, game->romanText,
        (sfVector2f){
        400 + cosf(i * 2 * M_PI / nb_romans) * 250,
        300 + sinf(i * 2 * M_PI / nb_romans) * 250},
        (i * 360 / nb_romans) - 90);
        game->forks[i] = init_csf_fork(
        game->forkText,
        (sfVector2f){
        400 + cosf(((i * 2 * M_PI) + M_PI) / nb_romans) * 250,
        300 + sinf(((i * 2 * M_PI) + M_PI) / nb_romans) * 250},
        (((i * 360) + 180) / nb_romans) - 90);
    }
    return game;
}

void destroy_csf_game(csf_game_t *game)
{
    sfCircleShape_destroy(game->table);
    sfTexture_destroy(game->romanText);
    sfTexture_destroy(game->roman_sleep_text);
    sfTexture_destroy(game->roman_think_text);
    sfTexture_destroy(game->forkText);
    for (int i = 0; i < game->nb_romans; ++i) {
        destroy_csf_roman(game->romans[i]);
        destroy_fork(game->forks[i]);
    }
    free(game->romans);
    free(game->forks);
    free(game);
}

void draw_game(sfRenderWindow *window, csf_game_t *game)
{
    sfRenderWindow_drawCircleShape(window, game->table, NULL);
    for (int i = 0; i < game->nb_romans; ++i) {
        switch (game->romans[i]->state) {
        case EATING:
            sfSprite_setTexture(
            game->romans[i]->sprite, game->romanText, sfFalse);
            break;
        case RESTING:
            sfSprite_setTexture(
            game->romans[i]->sprite, game->roman_sleep_text, sfFalse);
            break;
        case THINKING:
            sfSprite_setTexture(
            game->romans[i]->sprite, game->roman_think_text, sfFalse);
            break;
        }
        sfRenderWindow_drawSprite(window, game->romans[i]->sprite, NULL);
        sfRenderWindow_drawSprite(window, game->forks[i]->sprite, NULL);
    }
}
