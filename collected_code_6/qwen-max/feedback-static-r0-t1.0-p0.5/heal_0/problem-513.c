#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

typedef struct {
    char **elements;
    size_t count;
} List;

List *tupleToList(Tuple *tuple, const char *separator) {
    if (tuple == NULL || tuple->elements == NULL || separator == NULL) {
        return NULL;
    }

    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->count = tuple->count * 2 - 1;
    list->elements = (char **)malloc(list->count * sizeof(char *));
    if (list->elements == NULL) {
        free(list);
        return NULL;
    }

    for (size_t i = 0, j = 0; i < tuple->count; ++i) {
        list->elements[j++] = strdup(tuple->elements[i]);
        if (j < list->count) {
            list->elements[j++] = strdup(separator);
        }
    }

    return list;
}

void freeList(List *list) {
    if (list != NULL) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->elements[i]);
        }
        free(list->elements);
        free(list);
    }
}

int main() {
    Tuple tuple = {
        .elements = (char *[]){"apple", "banana", "cherry"},
        .count = 3
    };

    const char *separator = ",";
    List *list = tupleToList(&tuple, separator);

    if (list != NULL) {
        for (size_t i = 0; i < list->count; ++i) {
            printf("%s ", list->elements[i]);
        }
        printf("\n");
        freeList(list);
    } else {
        printf("Failed to convert tuple to list.\n");
    }

    return 0;
}