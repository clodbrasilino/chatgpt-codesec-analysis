#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **string_to_list(const char *str, const char *delim, size_t *count) {
    if (!str || !delim || !count) return NULL;

    size_t capacity = 10;
    size_t size = 0;
    char **list = malloc(capacity * sizeof(char *));
    if (!list) return NULL;

    char *copy = strdup(str);
    if (!copy) {
        free(list);
        return NULL;
    }

    char *token = strtok(copy, delim);
    while (token != NULL) {
        if (size >= capacity) {
            capacity *= 2;
            char **new_list = realloc(list, capacity * sizeof(char *));
            if (!new_list) {
                for (size_t i = 0; i < size; i++) free(list[i]);
                free(list);
                free(copy);
                return NULL;
            }
            list = new_list;
        }

        list[size] = strdup(token);
        if (!list[size]) {
            for (size_t i = 0; i < size; i++) free(list[i]);
            free(list);
            free(copy);
            return NULL;
        }

        size++;
        token = strtok(NULL, delim);
    }

    free(copy);

    char **final_list = realloc(list, (size + 1) * sizeof(char *));
    if (!final_list) {
        for (size_t i = 0; i < size; i++) free(list[i]);
        free(list);
        return NULL;
    }
    list = final_list;
    list[size] = NULL;

    *count = size;
    return list;
}

void free_list(char **list) {
    if (!list) return;
    for (size_t i = 0; list[i] != NULL; i++) free(list[i]);
    free(list);
}

int main(void) {
    const char *input1 = "python programming";
    const char *input2 = "lists tuples strings";
    const char *input3 = "write a program";
    const char *delim = " ";
    size_t count = 0;

    char **list1 = string_to_list(input1, delim, &count);
    if (list1) {
        for (size_t i = 0; i < count; i++) printf("%s\n", list1[i]);
        free_list(list1);
    }

    char **list2 = string_to_list(input2, delim, &count);
    if (list2) {
        for (size_t i = 0; i < count; i++) printf("%s\n", list2[i]);
        free_list(list2);
    }

    char **list3 = string_to_list(input3, delim, &count);
    if (list3) {
        for (size_t i = 0; i < count; i++) printf("%s\n", list3[i]);
        free_list(list3);
    }

    return EXIT_SUCCESS;
}