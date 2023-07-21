/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** main
*/

#include "empire.h"
#include "extern.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int n_romans = 0;
    int belly_size = 0;

    RCFStartup(argc, argv);
    for (int opt; (opt = getopt(argc, argv, "p:e:")) != -1;) {
        switch (opt) {
        default:
            return 84;
        case 'p':
            n_romans = atoi(optarg);
            break;
        case 'e':
            belly_size = atoi(optarg);
        }
    }
    if (n_romans <= 1 || belly_size <= 0)
        return 84;
    n_romans = empire(belly_size, n_romans);
    RCFCleanup();
    return n_romans;
}
