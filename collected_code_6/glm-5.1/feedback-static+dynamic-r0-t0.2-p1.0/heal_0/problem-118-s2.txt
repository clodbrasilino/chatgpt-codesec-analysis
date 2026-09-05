#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **string_to_list(const char *str, const char *delim, size_t *count) {
    char **list = NULL;
    char *temp = NULL;
    char *token = NULL;
    size_t capacity = 0;
    size_t size = 0;

    if (str == NULL || delim == NULL || count == NULL) {
        return NULL;
    }

    temp = strdup(str);
    if (temp == NULL) {
        return NULL;
    }

    token = strtok(temp, delim);
    while (token != NULL) {
        if (size >= capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            char **new_list = realloc(list, capacity * sizeof(char *));
            if (new_list == NULL) {
                for (size_t i = 0; i < size; i++) {
                    free(list[i]);
                }
                free(list);
                free(temp);
                *count = 0;
                return NULL;
            }
            list = new_list;
        }

        list[size] = strdup(token);
        if (list[size] == NULL) {
            for (size_t i = 0; i < size; i++) {
                free(list[i]);
            }
            free(list);
            free(temp);
            *count = 0;
            return NULL;
        }

        size++;
        token = strtok(NULL, delim);
    }

    free(temp);

    char **final_list = realloc(list, (size + 1) * sizeof(char *));
    if (final_list != NULL) {
        list = final_list;
    }
    list[size] = NULL;

    *count = size;
    return list;
}

void free_list(char **list, size_t count) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *input = "Hello,world,this,is,a,test";
    const char *delim = ",";
    size_t count = 0;

    char **list = string_to_list(input, delim, &count);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    free_list(list, count);

    return EXIT_SUCCESS;
}