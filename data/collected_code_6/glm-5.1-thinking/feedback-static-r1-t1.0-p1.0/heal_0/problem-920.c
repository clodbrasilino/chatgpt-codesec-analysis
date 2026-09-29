#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TUPLE_SIZE 3

typedef struct {
    void *items[TUPLE_SIZE];
} Tuple;

typedef struct {
    Tuple **data;
    size_t size;
} TupleList;

Tuple *create_tuple(void *v0, void *v1, void *v2) {
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->items[0] = v0;
    t->items[1] = v1;
    t->items[2] = v2;
    return t;
}

void remove_all_none_tuples(TupleList *list) {
    if (list == NULL || list->data == NULL) {
        return;
    }
    size_t write_idx = 0;
    for (size_t i = 0; i < list->size; i++) {
        Tuple *current = list->data[i];
        bool all_none = true;
        if (current != NULL) {
            for (size_t j = 0; j < TUPLE_SIZE; j++) {
                if (current->items[j] != NULL) {
                    all_none = false;
                    break;
                }
            }
        }
        if (all_none) {
            free(current);
        } else {
            list->data[write_idx] = current;
            write_idx++;
        }
    }
    list->size = write_idx;
    if (list->size == 0) {
        free(list->data);
        list->data = NULL;
    } else {
        Tuple **shrunk_data = realloc(list->data, sizeof(Tuple *) * list->size);
        if (shrunk_data != NULL) {
            list->data = shrunk_data;
        }
    }
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->data != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            free(list->data[i]);
        }
        free(list->data);
    }
    free(list);
}

int main(void) {
    TupleList *list = malloc(sizeof(TupleList));
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    list->size = 4;
    list->data = malloc(sizeof(Tuple *) * list->size);
    if (list->data == NULL) {
        free(list);
        return EXIT_FAILURE;
    }

    list->data[0] = create_tuple(NULL, NULL, NULL);
    list->data[1] = create_tuple((void *)"hello", NULL, NULL);
    if (list->data[1] == NULL) {
        free_tuple_list(list);
        return EXIT_FAILURE;
    }
    list->data[2] = create_tuple(NULL, NULL, NULL);
    list->data[3] = create_tuple(NULL, (void *)"world", NULL);
    if (list->data[3] == NULL) {
        free_tuple_list(list);
        return EXIT_FAILURE;
    }

    remove_all_none_tuples(list);

    for (size_t i = 0; i < list->size; i++) {
        Tuple *t = list->data[i];
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < TUPLE_SIZE; j++) {
            if (t->items[j] != NULL) {
                printf("%s ", (char *)t->items[j]);
            } else {
                printf("NULL ");
            }
        }
        printf("\n");
    }

    free_tuple_list(list);
    return EXIT_SUCCESS;
}