#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    int size;
} StringTuple;

StringTuple *create_tuple(char *str[], int size) {
    if (size < 0) return NULL;
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (!tuple) return NULL;
    tuple->strings = (char **)malloc(size * sizeof(char *));
    if (!tuple->strings) {
        free(tuple);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        tuple->strings[i] = strdup(str[i]);
        if (!tuple->strings[i]) {
            for (int j = 0; j < i; j++) {
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

void free_tuple(StringTuple *tuple) {
    if (!tuple) return;
    for (int i = 0; i < tuple->size; i++) {
        free(tuple->strings[i]);
    }
    free(tuple->strings);
    free(tuple);
}

int main() {
    char *list[] = {"one", "two", "three"};
    int size = 3;
    StringTuple *tuple = create_tuple(list, size);
    if (tuple) {
        for (int i = 0; i < tuple->size; i++) {
            printf("%s\n", tuple->strings[i]);
        }
        free_tuple(tuple);
    }
    return 0;
}