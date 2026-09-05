#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **convert_tuple_to_list(char **tuple, size_t tuple_size, const char *str, size_t *list_size) {
    if (tuple == NULL || str == NULL || list_size == NULL) {
        return NULL;
    }

    size_t new_size = tuple_size * 2;
    char **list = (char **)malloc(new_size * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < tuple_size; i++) {
        size_t list_idx = i * 2;

        if (tuple[i] != NULL) {
            list[list_idx] = strdup(tuple[i]);
        } else {
            list[list_idx] = NULL;
        }

        list[list_idx + 1] = strdup(str);

        if ((tuple[i] != NULL && list[list_idx] == NULL) || list[list_idx + 1] == NULL) {
            for (size_t j = 0; j <= list_idx + 1; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
    }

    *list_size = new_size;
    return list;
}

void free_list(char **list, size_t size) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *str = "INSERT";
    size_t list_size = 0;

    char **list = convert_tuple_to_list(tuple, tuple_size, str, &list_size);
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL) {
            printf("%s\n", list[i]);
        }
    }

    free_list(list, list_size);

    return EXIT_SUCCESS;
}