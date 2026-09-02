#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char **strs;
    int size;
} Tuple;

Tuple create_tuple(int size) {
    Tuple t;
    t.size = size;
    t.strs = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; ++i) {
        t.strs[i] = NULL;
    }
    return t;
}

void free_tuple(Tuple *t) {
    for (int i = 0; i < t->size; ++i) {
        free(t->strs[i]);
    }
    free(t->strs);
    t->strs = NULL;
    t->size = 0;
}

Tuple string_list_to_tuple(char *list[], int size) {
    Tuple t = create_tuple(size);
    for (int i = 0; i < size; ++i) {
        t.strs[i] = strdup(list[i]);
    }
    return t;
}

int main() {
    char *strings[] = {"hello", "world", "tuple"};
    int size = 3;

    Tuple t = string_list_to_tuple(strings, size);

    for (int i = 0; i < t.size; ++i) {
        printf("%s\n", t.strs[i]);
    }

    free_tuple(&t);

    return 0;
}