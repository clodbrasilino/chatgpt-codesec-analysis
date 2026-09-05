#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_strings(char **strings, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            size_t len = strlen(strings[i]);
            if (len > 0) {
                size_t left = 0;
                size_t right = len - 1;
                while (left < right) {
                    char temp = strings[i][left];
                    strings[i][left] = strings[i][right];
                    strings[i][right] = temp;
                    left++;
                    right--;
                }
            }
        }
    }
}

int main(void) {
    size_t count = 5;
    char **list = malloc(count * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0] = malloc(6 * sizeof(char));
    list[1] = malloc(6 * sizeof(char));
    list[2] = malloc(2 * sizeof(char));
    list[3] = malloc(5 * sizeof(char));
    list[4] = NULL;

    if (!list[0] || !list[1] || !list[2] || !list[3]) {
        for (size_t i = 0; i < 4; i++) {
            free(list[i]);
        }
        free(list);
        return EXIT_FAILURE;
    }

    strcpy(list[0], "hello");
    strcpy(list[1], "world");
    strcpy(list[2], "");
    strcpy(list[3], "test");

    reverse_strings(list, count);

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            printf("%s\n", list[i]);
        }
    }

    for (size_t i = 0; i < 4; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}