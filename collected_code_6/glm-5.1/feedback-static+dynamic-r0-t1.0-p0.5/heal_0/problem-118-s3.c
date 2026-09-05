#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **string_to_list(const char *str, const char *delim, size_t *count) {
    size_t capacity = 10;
    size_t size = 0;
    char **list = malloc(capacity * sizeof(char *));
    if (!list) {
        return NULL;
    }

    char *copy = strdup(str);
    if (!copy) {
        free(list);
        return NULL;
    }

    char *token = strtok(copy, delim);
    while (token != NULL) {
        if (size >= capacity) {
            capacity *= 2;
            char **temp = realloc(list, capacity * sizeof(char *));
            if (!temp) {
                for (size_t i = 0; i < size; i++) {
                    free(list[i]);
                }
                free(list);
                free(copy);
                return NULL;
            }
            list = temp;
        }

        list[size] = strdup(token);
        if (!list[size]) {
            for (size_t i = 0; i < size; i++) {
                free(list[i]);
            }
            free(list);
            free(copy);
            return NULL;
        }

        size++;
        token = strtok(NULL, delim);
    }

    free(copy);

    char **temp = realloc(list, (size + 1) * sizeof(char *));
    if (temp) {
        list = temp;
    }
    list[size] = NULL;

    *count = size;
    return list;
}

void free_list(char **list) {
    if (!list) {
        return;
    }
    for (size_t i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *input = "apple,banana,cherry,date";
    const char *delim = ",";
    size_t count = 0;

    char **list = string_to_list(input, delim, &count);
    if (!list) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    free_list(list);

    return EXIT_SUCCESS;
}