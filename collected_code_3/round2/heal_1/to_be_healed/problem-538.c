#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Tuple;

Tuple* create_tuple(char **list, int size) {
    Tuple *tuple = malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple->items = malloc(size * sizeof(char *));
    tuple->size = size;

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*tuple.items + (long unsigned int)i * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple->items[i] = malloc((strlen(list[i]) + 1) * sizeof(char));
        strcpy(tuple->items[i], list[i]);
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    for (int i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main() {
    char *list[] = {"Hello", "World", "This", "Is", "C"};
    int size = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = create_tuple(list, size);

    for (int i = 0; i < tuple->size; i++) {
        printf("%s ", tuple->items[i]);
    }

    free_tuple(tuple);

    return 0;
}