#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "users.h"
#include "processes.h"
#include "help.h"
#include "file_utils.h"

int main(int argc, char *argv[]) {
    char *log_path = NULL;
    char *error_path = NULL;
    int opt;

    static struct option long_options[] = {
        {"users", no_argument, 0, 'u'},
        {"processes", no_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {"log", required_argument, 0, 'l'},
        {"errors", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    int long_index = 0;
    while ((opt = getopt_long(argc, argv, "uphl:e:", long_options, &long_index)) != -1) {
        switch (opt) {
            case 'u':
                print_users();
                break;
            case 'p':
                print_processes();
                break;
            case 'h':
                print_help();
                return 0;
            case 'l':
                log_path = optarg;
                if (check_path(log_path) != 0) {
                    return 1;
                }
                break;
            case 'e':
                error_path = optarg;
                if (check_path(error_path) != 0) {
                    return 1;
                }
                break;
            default:
                fprintf(stderr, "Неизвестная опция -%c\n", optopt);
                print_help();
                return 1;
        }
    }

    if (log_path != NULL) {
        freopen(log_path, "a", stdout);
    }

    if (error_path != NULL) {
        freopen(error_path, "a", stderr);
    }

    if (log_path != NULL) {
        print_users();
        print_processes();
    }

    return 0;
}

