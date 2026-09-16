#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

void remove_empty_lists(ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL) {
        return;
    }

    size_t write_idx = 0;
    for (size_t i = 0; i < lol->count; i++) {
        if (lol->lists[i].size == 0 || lol->lists[i].data == NULL) {
            if (lol->lists[i].data != NULL) {
                free(lol->lists[i].data);
                lol->lists[i].data = NULL;
            }
        } else {
            if (write_idx != i) {
                lol->lists[write_idx] = lol->lists[i];
                lol->lists[i].data = NULL;
                lol->lists[i].size = 0;
            }
            write_idx++;
        }
    }

    lol->count = write_idx;

    if (write_idx == 0) {
        free(lol->lists);
        lol->lists = NULL;
    } else {
        List *trimmed = (List *)realloc(lol->lists, write_idx * sizeof(List));
        if (trimmed != NULL) {
            lol->lists = trimmed;
        }
    }
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    if (lol->lists != NULL) {
        for (size_t i = 0; i < lol->count; i++) {
            if (lol->lists[i].data != NULL) {
                free(lol->lists[i].data);
            }
        }
        free(lol->lists);
        lol->lists = NULL;
    }
    lol->count = 0;
}

void print_list_of_lists(const ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL) {
        printf("Empty list of lists\n");
        return;
    }
    printf("List of lists (%zu entries):\n", lol->count);
    for (size_t i = 0; i < lol->count; i++) {
        printf("  [%zu]: [", i);
        for (size_t j = 0; j < lol->lists[i].size; j++) {
            printf("%d", lol->lists[i].data[j]);
            if (j + 1 < lol->lists[i].size) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void) {
    ListOfLists lol;
    lol.count = 5;
    lol.lists = (List *)malloc(5 * sizeof(List));
    if (lol.lists == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    lol.lists[0].data = NULL;
    lol.lists[0].size = 0;

    lol.lists[1].data = (int *)malloc(3 * sizeof(int));
    if (lol.lists[1].data == NULL) { free(lol.lists); return 1; }
    lol.lists[1].data[0] = 1;
    lol.lists[1].data[1] = 2;
    lol.lists[1].data[2] = 3;
    lol.lists[1].size = 3;

    lol.lists[2].data = NULL;
    lol.lists[2].size = 0;

    lol.lists[3].data = (int *)malloc(2 * sizeof(int));
    if (lol.lists[3].data == NULL) {
        free(lol.lists[1].data);
        free(lol.lists);
        return 1;
    }
    lol.lists[3].data[0] = 4;
    lol.lists[3].data[1] = 5;
    lol.lists[3].size = 2;

    lol.lists[4].data = NULL;
    lol.lists[4].size = 0;

    printf("Before:\n");
    print_list_of_lists(&lol);

    remove_empty_lists(&lol);

    printf("\nAfter:\n");
    print_list_of_lists(&lol);

    free_list_of_lists(&lol);

    return 0;
}