#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    int size;
} Tuple;

typedef struct {
    char **elements;
    int size;
} List;

List *tupleToList(Tuple *t, const char *str) {
    if (t == NULL || t->elements == NULL || str == NULL) return NULL;

    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) return NULL;

    list->size = t->size * 2;
    list->elements = (char **)malloc(list->size * sizeof(char *));
    if (list->elements == NULL) {
        free(list);
        return NULL;
    }

    for (int i = 0, j = 0; i < t->size; i++, j += 2) {
        list->elements[j] = strdup(t->elements[i]);
        if (list->elements[j] == NULL) {
            for (int k = 0; k < j; k++) free(list->elements[k]);
            free(list->elements);
            free(list);
            return NULL;
        }
        list->elements[j + 1] = strdup(str);
        if (list->elements[j + 1] == NULL) {
            for (int k = 0; k <= j; k++) free(list->elements[k]);
            free(list->elements);
            free(list);
            return NULL;
        }
    }

    return list;
}

void freeList(List *list) {
    if (list != NULL) {
        for (int i = 0; i < list->size; i++) {
            free(list->elements[i]);
        }
        free(list->elements);
        free(list);
    }
}

int main() {
    Tuple t = { .elements = (char *[]){"a", "b", "c"}, .size = 3 };
    const char *str = "X";

    List *list = tupleToList(&t, str);
    if (list != NULL) {
        for (int i = 0; i < list->size; i++) {
            printf("%s ", list->elements[i]);
        }
        printf("\n");
        freeList(list);
    } else {
        printf("Failed to convert tuple to list.\n");
    }

    return 0;
}