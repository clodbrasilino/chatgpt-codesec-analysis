#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_words(char **list, size_t *count, const char *target) {
    if (!list || !count || !target) return;

    size_t i = 0;
    while (i < *count) {
        if (list[i] && strstr(list[i], target)) {
            free(list[i]);
            for (size_t j = i; j < *count - 1; j++) {
                list[j] = list[j + 1];
            }
            list[*count - 1] = NULL;
            (*count)--;
        } else {
            i++;
        }
    }
}

int main() {
    size_t count = 4;
    char **list = malloc(count * sizeof(char *));
    if (!list) {
        return 1;
    }

    list[0] = strdup("apple");
    list[1] = strdup("banana");
    list[2] = strdup("cherry");
    list[3] = strdup("date");

    for (size_t i = 0; i < count; i++) {
        if (!list[i]) {
            for (size_t j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return 1;
        }
    }

    remove_words(list, &count, "a");

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}