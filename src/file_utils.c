#include <stdio.h>
#include "file_utils.h"

int check_path(const char *path) {
    FILE *file = fopen(path, "a");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    fclose(file);
    return 0;
}

