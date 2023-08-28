#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool checkEquality(char *list[], int size, char *str) {
    for (int i = 0; i < size; i++) {
        if (strcmp(list[i], str) != 0) {
            return false;
        }
    }
    return true;
}