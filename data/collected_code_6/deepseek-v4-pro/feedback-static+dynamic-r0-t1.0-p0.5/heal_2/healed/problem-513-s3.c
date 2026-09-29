#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tuple_to_list(const char *tuple[], int tuple_size, const char *str, int *list_size) {
    if (tuple == NULL || str == NULL || list_size == NULL || tuple_size <= 0) {
        if (list_size != NULL) {
            *list_size = 0;
        }
        return NULL;
    }

    char **list = (char **)malloc(tuple_size * sizeof(char *));
    if (list == NULL) {
        *list_size = 0;
        return NULL;
    }

    size_t str_len = strnlen(str, 1024);

    for (int i = 0; i < tuple_size; i++) {
        if (tuple[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        size_t tuple_len = strnlen(tuple[i], 1024);
        size_t total_len = tuple_len + str_len + 1;
        list[i] = (char *)malloc(total_len);
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        snprintf(list[i], total_len, "%s%s", tuple[i], str);
    }

    *list_size = tuple_size;
    return list;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    int list_size = 0;

    char **list = tuple_to_list(tuple, tuple_size, "_fruit", &list_size);

    if (list == NULL) {
        fprintf(stderr, "Error: Failed to convert tuple to list\n");
        return 1;
    }

    for (int i = 0; i < list_size; i++) {
        printf("%s\n", list[i]);
        free(list[i]);
    }
    free(list);

    return 0;
}