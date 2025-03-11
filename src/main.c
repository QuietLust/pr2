#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "users.h"
#include "processes.h"
#include "help.h"
#include "file_utils.h"

int main(int argc, char *argv[]) {
    char *log_file = NULL;
    char *error_file = NULL;
    int option;
    int show_users = 0, show_processes = 0, show_help = 0;

    static struct option long_opts[] = {
        {"users", no_argument, 0, 'u'},
        {"processes", no_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {"log", required_argument, 0, 'l'},
        {"errors", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    int opt_index = 0;
    while ((option = getopt_long(argc, argv, "uphl:e:", long_opts, &opt_index)) != -1) {
        switch (option) {
            case 'u':
                show_users = 1;
                break;
            case 'p':
                show_processes = 1;
                break;
            case 'h':
                show_help = 1;
                break;
            case 'l':
                log_file = optarg;
                if (check_path(log_file) != 0) {
                    return 1;
                }
                break;
            case 'e':
                error_file = optarg;
                if (check_path(error_file) != 0) {
                    return 1;
                }
                break;
            default:
                if (error_file != NULL) {
                    freopen(error_file, "a", stderr);
                }
                fprintf(stderr, "Неизвестная опция -%c\n", optopt);
                print_help();
                return 1;
        }
    }

    if (log_file != NULL) {
        freopen(log_file, "w", stdout);
    }

    if (error_file != NULL) {
        freopen(error_file, "a", stderr);
    }

    if (show_help) {print_help(); return 0;}
    if (!show_users && !show_processes) {printf("Не заданы явные аргументы \n"); print_help(); return 1;}
    if (show_users) {print_users();}
    if (show_processes) {print_processes();}

    return 0;
}
