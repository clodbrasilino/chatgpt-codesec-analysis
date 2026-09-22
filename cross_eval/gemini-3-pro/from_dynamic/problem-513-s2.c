#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tuple {
    char **elements;
    size_t size;
};

struct List {
    char **elements;
    size_t size;
};

struct List* convert_tuple_to_list(const struct Tuple *tuple, const char *to_add) {
    if (tuple == NULL || tuple->elements == NULL || to_add == NULL) {
        return NULL;
    }

    struct List *list = (struct List *)malloc(sizeof(struct List));
    if (list == NULL) {
        return NULL;
    }

    list->size = tuple->size * 2;
    list->elements = (char **)malloc(list->size * sizeof(char *));
    if (list->elements == NULL) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == NULL) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list->elements[j]);
            }
            free(list->elements);
            free(list);
            return NULL;
        }

        list->elements[i * 2] = strdup(tuple->elements[i]);
        if (list->elements[i * 2] == NULL) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list->elements[j]);
            }
            free(list->elements);
            free(list);
            return NULL;
        }

        list->elements[i * 2 + 1] = strdup(to_add);
        if (list->elements[i * 2 + 1] == NULL) {
            free(list->elements[i * 2]);
            for (size_t j = 0; j < i * 2; j++) {
                free(list->elements[j]);
            }
            free(list->elements);
            free(list);
            return NULL;
        }
    }

    return list;
}

void free_list(struct List *list) {
    if (list != NULL) {
        if (list->elements != NULL) {
            for (size_t i = 0; i < list->size; i++) {
                free(list->elements[i]);
            }
            free(list->elements);
        }
        free(list);
    }
}

int main(void) {
    char *elements[] = {"apple", "banana", "cherry"};
    struct Tuple tuple;
    tuple.elements = elements;
    tuple.size = 3;

    const char *to_add = "fruit";

    struct List *list = convert_tuple_to_list(&tuple, to_add);

    if (list != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            printf("%s\n", list->elements[i]);
        }
        free_list(list);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}