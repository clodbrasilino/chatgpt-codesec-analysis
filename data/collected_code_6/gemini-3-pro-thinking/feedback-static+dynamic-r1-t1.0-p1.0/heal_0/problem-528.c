#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

List* find_min_length_list(ListOfLists *lol);
void free_list_of_lists(ListOfLists *lol);

List* find_min_length_list(ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL || lol->count == 0) {
        return NULL;
    }

    List *min_list = &lol->lists[0];
    for (size_t i = 1; i < lol->count; i++) {
        if (lol->lists[i].length < min_list->length) {
            min_list = &lol->lists[i];
        }
    }

    return min_list;
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL) {
        if (lol->lists != NULL) {
            for (size_t i = 0; i < lol->count; i++) {
                free(lol->lists[i].data);
            }
            free(lol->lists);
        }
        free(lol);
    }
}

int main(void) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        return EXIT_FAILURE;
    }

    lol->count = 3;
    lol->lists = (List *)calloc(lol->count, sizeof(List));
    if (lol->lists == NULL) {
        free(lol);
        return EXIT_FAILURE;
    }

    lol->lists[0].length = 5;
    lol->lists[0].data = (int *)malloc(lol->lists[0].length * sizeof(int));

    lol->lists[1].length = 2;
    lol->lists[1].data = (int *)malloc(lol->lists[1].length * sizeof(int));

    lol->lists[2].length = 4;
    lol->lists[2].data = (int *)malloc(lol->lists[2].length * sizeof(int));

    if (lol->lists[0].data == NULL || lol->lists[1].data == NULL || lol->lists[2].data == NULL) {
        free_list_of_lists(lol);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lol->count; i++) {
        for (size_t j = 0; j < lol->lists[i].length; j++) {
            lol->lists[i].data[j] = (int)(i + j);
        }
    }

    List *min_list = find_min_length_list(lol);

    if (min_list != NULL) {
        printf("%zu\n", min_list->length);
    }

    free_list_of_lists(lol);

    return EXIT_SUCCESS;
}