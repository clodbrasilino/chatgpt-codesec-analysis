#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
} SubList;

typedef struct {
    SubList *lists;
    size_t count;
} ListOfLists;

void filter_sublists(ListOfLists *lol, int min_val, int max_val) {
    if (!lol || !lol->lists) {
        return;
    }

    size_t keep_index = 0;

    for (size_t i = 0; i < lol->count; i++) {
        bool keep = true;

        if (lol->lists[i].data != NULL) {
            for (size_t j = 0; j < lol->lists[i].size; j++) {
                if (lol->lists[i].data[j] < min_val || lol->lists[i].data[j] > max_val) {
                    keep = false;
                    break;
                }
            }
        } else {
            keep = false; 
        }

        if (keep) {
            if (keep_index != i) {
                lol->lists[keep_index] = lol->lists[i];
            }
            keep_index++;
        } else {
            free(lol->lists[i].data);
            lol->lists[i].data = NULL;
            lol->lists[i].size = 0;
        }
    }

    lol->count = keep_index;
}

int main(void) {
    ListOfLists lol;
    lol.count = 3;
    lol.lists = malloc(lol.count * sizeof(SubList));

    if (!lol.lists) {
        return EXIT_FAILURE;
    }

    lol.lists[0].size = 3;
    lol.lists[0].data = malloc(lol.lists[0].size * sizeof(int));
    if (lol.lists[0].data) {
        lol.lists[0].data[0] = 1;
        lol.lists[0].data[1] = 2;
        lol.lists[0].data[2] = 3;
    }

    lol.lists[1].size = 2;
    lol.lists[1].data = malloc(lol.lists[1].size * sizeof(int));
    if (lol.lists[1].data) {
        lol.lists[1].data[0] = 10;
        lol.lists[1].data[1] = 20;
    }

    lol.lists[2].size = 3;
    lol.lists[2].data = malloc(lol.lists[2].size * sizeof(int));
    if (lol.lists[2].data) {
        lol.lists[2].data[0] = 2;
        lol.lists[2].data[1] = 4;
        lol.lists[2].data[2] = 5;
    }

    for (size_t i = 0; i < lol.count; i++) {
        if (!lol.lists[i].data) {
            for (size_t j = 0; j <= i; j++) {
                free(lol.lists[j].data);
            }
            free(lol.lists);
            return EXIT_FAILURE;
        }
    }

    filter_sublists(&lol, 1, 5);

    for (size_t i = 0; i < lol.count; i++) {
        for (size_t j = 0; j < lol.lists[i].size; j++) {
            printf("%d ", lol.lists[i].data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < lol.count; i++) {
        free(lol.lists[i].data);
    }
    free(lol.lists);

    return EXIT_SUCCESS;
}