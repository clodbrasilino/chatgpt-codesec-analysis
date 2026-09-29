#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* str;
    int* list;
    size_t list_size;
} Tuple;

Tuple* create_tuple(char* str, int* list, size_t list_size) {
    Tuple* tuple = malloc(sizeof(Tuple));
    if (!tuple) return NULL; 

    tuple->str = malloc(strlen(str) + 1);
    if (!tuple->str) {
        free(tuple);
        return NULL;
    }
    strcpy(tuple->str, str);

    tuple->list = malloc(list_size * sizeof(int));
    if (!tuple->list) {
        free(tuple->str);
        free(tuple);
        return NULL;
    }
    memcpy(tuple->list, list, list_size * sizeof(int));
    tuple->list_size = list_size;
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple) {
        if (tuple->str) free(tuple->str);
        if (tuple->list) free(tuple->list);
        free(tuple);
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    Tuple* tuple = create_tuple("example", list, sizeof(list) / sizeof(int));

    if (!tuple) return 1;

    printf("String: %s\n", tuple->str);
    printf("List: ");
    for (size_t i = 0; i < tuple->list_size; i++) {
        printf("%d ", tuple->list[i]);
    }
    printf("\n");

    free_tuple(tuple);
    return 0;
}