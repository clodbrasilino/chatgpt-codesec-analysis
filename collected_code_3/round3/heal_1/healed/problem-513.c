#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
} List;

typedef struct {
    char **data;
    int size;
} Tuple;

List* tupleToList(Tuple *tuple, char *str) {
    List *list = malloc(sizeof(List));

    if (list == NULL) {
        fprintf(stderr, "Failed to allocate memory for list\n");
        exit(EXIT_FAILURE);
    }

    list->size = tuple->size * 2;
    list->data = malloc(list->size * sizeof(char*));

    if (list->data == NULL) {
        fprintf(stderr, "Failed to allocate memory for list data\n");
        free(list);
        exit(EXIT_FAILURE);
    }

    for(int i = 0, j = 0; i < tuple->size; i++) {
        list->data[j++] = tuple->data[i];
        list->data[j++] = str;
    }

    return list;
}

int main() {
    Tuple tuple;
    tuple.size = 3;
    tuple.data = malloc(tuple.size * sizeof(char*));

    if (tuple.data == NULL) {
        fprintf(stderr, "Failed to allocate memory for tuple data\n");
        exit(EXIT_FAILURE);
    }

    tuple.data[0] = "Hello";
    tuple.data[1] = "World";
    tuple.data[2] = "!";

    char *str = "Add";

    List *list = tupleToList(&tuple, str);

    for(int i = 0; i < list->size; i++) {
        printf("%s ", list->data[i]);
    }

    free(tuple.data);
    free(list->data);
    free(list);

    return 0;
}