/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** csfml
*/

#include "csfml_empire.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

extern int ready;

csf_command_payload_t interpret_command(char *cmd)
{
    int len = strlen(cmd);

    if (strncmp("EAT ", cmd, 4) == 0 && len > 4)
        return ((csf_command_payload_t){
        .command_type = csf_cmd_eat,
        .id = atoi(cmd + 4)});
    if (strncmp("THINK ", cmd, 6) == 0 && len > 6)
        return ((csf_command_payload_t){
        .command_type = csf_cmd_think,
        .id = atoi(cmd + 6)});
    if (strncmp("SLEEP ", cmd, 6) == 0 && len > 6)
        return ((csf_command_payload_t){
        .command_type = csf_cmd_sleep,
        .id = atoi(cmd + 6)});
    if (strncmp("LOCK ", cmd, 5) == 0 && len > 5) {
        if (strchr(cmd + 5, ' ') == NULL) {
            return (csf_command_payload_t){.command_type = csf_cmd_none};
        }
        return ((csf_command_payload_t){
        .command_type = csf_cmd_take_fork,
        .id = atoi(cmd + 5),
        .target = atoi(strchr(cmd + 5, ' ') + 1)});
    }
    if (strncmp("UNLOCK ", cmd, 7) == 0 && len > 7)
        return ((csf_command_payload_t){
        .command_type = csf_cmd_release_fork,
        .id = atoi(cmd + 7)});
    return (csf_command_payload_t){.command_type = csf_cmd_none};
}

int evaluate_string(csf_game_t *game, char *str)
{
    csf_command_payload_t cmd = interpret_command(str);

    switch (cmd.command_type) {
    case csf_cmd_none:
        return -1;
    case csf_cmd_eat:
        game->romans[cmd.id]->state = EATING;
        printf("EAT\n");
        break;
    case csf_cmd_sleep:
        game->romans[cmd.id]->state = RESTING;
        printf("REST\n");
        break;
    case csf_cmd_think:
        game->romans[cmd.id]->state = THINKING;
        printf("THINK\n");
        break;
    case csf_cmd_take_fork:
        game->forks[cmd.target]->owner = cmd.id;
        break;
    case csf_cmd_release_fork:
        game->forks[cmd.id]->owner = -1;
        break;
    }
    return 0;
}

void read_line_from_fd(csf_game_t *game, int read_fd)
{
    static char buffer[2048] = {0};
    static int size = 0;
    char *tmp_buff;
    char *newline;
    fd_set read_fd_set;
    struct timeval timeval = {.tv_sec = 0};
    int nread = 0;
    int ret = -1;

    FD_SET(read_fd, &read_fd_set);
    select(read_fd + 1, &read_fd_set, NULL, NULL, &timeval);
    if (FD_ISSET(read_fd, &read_fd_set)) {
        nread = read(read_fd, buffer + size, 1024);
        if (nread <= 0)
            return;
        size += nread;
    }
    newline = strchr(buffer, '\n');
    while (newline != NULL && ret == -1) {
        tmp_buff = calloc(sizeof(char), 1024);
        memmove(tmp_buff, buffer, newline - buffer + 1);
        size = size - strlen(tmp_buff);
        memmove(buffer, newline + 1, strlen(newline) + 1);
        ret = evaluate_string(game, tmp_buff);
        newline = strchr(buffer, '\n');
        free(tmp_buff);
    }
}

int csfml(int nb_romans, int belly_size, int read_fd)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window =
    sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    sfEvent event;
    csf_game_t *game = init_csf_game(nb_romans, belly_size);
    char *buf;

    if (!window || !game)
        return 84;
    ready = 1;
    sfRenderWindow_setFramerateLimit(window, 30);
    while (sfRenderWindow_isOpen(window)) {
        read_line_from_fd(game, read_fd);
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_clear(window, sfBlack);
        draw_game(window, game);
        sfRenderWindow_display(window);
    }
    destroy_csf_game(game);
    sfRenderWindow_destroy(window);
    return 0;
}
