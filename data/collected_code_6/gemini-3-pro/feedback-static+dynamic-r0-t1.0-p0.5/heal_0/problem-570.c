#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_words(char **list, int *list_size, const char *target) {
    if (list == NULL || list_size == NULL || target == NULL) {
        return;
    }

    int i = 0;
    while (i < *list_size) {
        if (list[i] != NULL && strstr(list[i], target) != NULL) {
            free(list[i]);
            for (int j = i; j < *list_size - 1; j++) {
                list[j] = list[j + 1];
            }
            list[*list_size - 1] = NULL;
            (*list_size)--;
        } else {
            i++;
        }
    }
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

    const char *target = "an";

    remove_words(list, &list_size, target);

    for (int i = 0; i < list_size; i++) {
        printf("%s\n", list[i]);
    }

    for (int i = 0; i < list_size; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}