#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_words(char **list, int *list_size, const char *target) {
    if (list == NULL || list_size == NULL || target == NULL) {
        return;
    }

    int write_index = 0;
    for (int i = 0; i < *list_size; i++) {
        if (list[i] != NULL) {
            if (strstr(list[i], target) == NULL) {
                list[write_index] = list[i];
                write_index++;
            } else {
                free(list[i]);
                list[i] = NULL;
            }
        }
    }
    *list_size = write_index;
}

int main(void) {
    int list_size = 5;
    char **list = malloc(list_size * sizeof(char *));
    if (list == NULL) {
        return 1;
    }

    list[0] = strdup("apple");
    list[1] = strdup("banana");
    list[2] = strdup("cherry");
    list[3] = strdup("date");
    list[4] = strdup("elderberry");

    for (int i = 0; i < list_size; i++) {
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return 1;
        }
    }

    const char *target = "a";

    remove_words(list, &list_size, target);

    for (int i = 0; i < list_size; i++) {
        printf("%s\n", list[i]);
        free(list[i]);
    }

    free(list);

    return 0;
}