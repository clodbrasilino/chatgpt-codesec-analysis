#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    int count;
} StringTuple;

StringTuple *create_tuple(const char *const *list, int count) {
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->strings = (char **)malloc(count * sizeof(char *));
    if (tuple->strings == NULL) {
        free(tuple);
        return NULL;
    }
    for (int i = 0; i < count; ++i) {
        tuple->strings[i] = strdup(list[i]);
        if (tuple->strings[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(tuple->strings[j]);
            }
            free(tuple->strings);
            free(tuple);
            return NULL;
        }
    }
    tuple->count = count;
    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        for (int i = 0; i < tuple->count; ++i) {
            free(tuple->strings[i]);
        }
        free(tuple->strings);
        free(tuple);
    }
}

int main() {
    const char *list[] = {"one", "two", "three"};
    int count = 3;
    StringTuple *tuple = create_tuple(list, count);
    if (tuple != NULL) {
        for (int i = 0; i < tuple->count; ++i) {
            printf("%s\n", tuple->strings[i]);
        }
        free_tuple(tuple);
    } else {
        fprintf(stderr, "Failed to create tuple\n");
    }
    return 0;
}