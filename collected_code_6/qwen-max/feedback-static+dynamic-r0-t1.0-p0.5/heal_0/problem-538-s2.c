#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    int size;
} StringTuple;

StringTuple *create_string_tuple(char *str_list[], int size) {
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->strings = (char **)malloc(size * sizeof(char *));
    if (tuple->strings == NULL) {
        free(tuple);
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        tuple->strings[i] = strdup(str_list[i]);
        if (tuple->strings[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(tuple->strings[j]);
            }
            free(tuple->strings);
            free(tuple);
            return NULL;
        }
    }
    tuple->size = size;
    return tuple;
}

void free_string_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        for (int i = 0; i < tuple->size; ++i) {
            free(tuple->strings[i]);
        }
        free(tuple->strings);
        free(tuple);
    }
}

int main() {
    char *str_list[] = {"apple", "banana", "cherry"};
    int size = 3;
    StringTuple *tuple = create_string_tuple(str_list, size);
    if (tuple != NULL) {
        for (int i = 0; i < tuple->size; ++i) {
            printf("%s\n", tuple->strings[i]);
        }
        free_string_tuple(tuple);
    }
    return 0;
}