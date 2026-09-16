#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
} TupleList;

int init_tuple_list(TupleList *list, size_t size) {
    if (list == NULL) {
        return -1;
    }
    list->data = malloc(size * sizeof(Tuple));
    if (list->data == NULL) {
        return -1;
    }
    list->size = size;
    return 0;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL && list->data != NULL) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
    }
}

int find_inversions(const TupleList *list, size_t *inversion_count) {
    if (list == NULL || list->data == NULL || inversion_count == NULL) {
        return -1;
    }
    *inversion_count = 0;
    for (size_t i = 0; i < list->size; i++) {
        for (size_t j = i + 1; j < list->size; j++) {
            if ((list->data[i].x > list->data[j].x && list->data[i].y < list->data[j].y) ||
                (list->data[i].x < list->data[j].x && list->data[i].y > list->data[j].y)) {
                (*inversion_count)++;
            }
        }
    }
    return 0;
}

int main(void) {
    TupleList list;
    size_t inversion_count = 0;
    size_t size = 5;

    if (init_tuple_list(&list, size) != 0) {
        fprintf(stderr, "Failed to initialize tuple list\n");
        return EXIT_FAILURE;
    }

    list.data[0].x = 1; list.data[0].y = 5;
    list.data[1].x = 2; list.data[1].y = 4;
    list.data[2].x = 3; list.data[2].y = 3;
    list.data[3].x = 4; list.data[3].y = 2;
    list.data[4].x = 5; list.data[4].y = 1;

    if (find_inversions(&list, &inversion_count) != 0) {
        fprintf(stderr, "Failed to find inversions\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Number of inversions: %zu\n", inversion_count);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}