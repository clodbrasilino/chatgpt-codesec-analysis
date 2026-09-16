#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} List;

typedef struct {
    List *lists;
    int count;
} ListOfLists;

int remove_empty_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return -1;
    }

    if (lol->lists == NULL && lol->count > 0) {
        return -1;
    }

    int write_idx = 0;

    for (int i = 0; i < lol->count; i++) {
        if (lol->lists[i].size > 0) {
            if (write_idx != i) {
                lol->lists[write_idx] = lol->lists[i];
            }
            write_idx++;
        } else {
            free(lol->lists[i].data);
            lol->lists[i].data = NULL;
        }
    }

    lol->count = write_idx;

    if (write_idx == 0) {
        free(lol->lists);
        lol->lists = NULL;
    } else {
        List *tmp = realloc(lol->lists, (size_t)write_idx * sizeof(List));
        if (tmp != NULL) {
            lol->lists = tmp;
        }
    }

    return 0;
}

int main(void) {
    ListOfLists lol;
    lol.count = 5;
    lol.lists = malloc((size_t)lol.count * sizeof(List));
    if (lol.lists == NULL) {
        return 1;
    }

    lol.lists[0].size = 0;
    lol.lists[0].data = NULL;

    lol.lists[1].size = 3;
    lol.lists[1].data = malloc(3 * sizeof(int));
    if (lol.lists[1].data == NULL) {
        free(lol.lists);
        return 1;
    }
    lol.lists[1].data[0] = 1;
    lol.lists[1].data[1] = 2;
    lol.lists[1].data[2] = 3;

    lol.lists[2].size = 0;
    lol.lists[2].data = NULL;

    lol.lists[3].size = 2;
    lol.lists[3].data = malloc(2 * sizeof(int));
    if (lol.lists[3].data == NULL) {
        free(lol.lists[1].data);
        free(lol.lists);
        return 1;
    }
    lol.lists[3].data[0] = 4;
    lol.lists[3].data[1] = 5;

    lol.lists[4].size = 0;
    lol.lists[4].data = NULL;

    if (remove_empty_lists(&lol) != 0) {
        return 1;
    }

    for (int i = 0; i < lol.count; i++) {
        printf("List %d: [", i);
        for (int j = 0; j < lol.lists[i].size; j++) {
            printf("%d", lol.lists[i].data[j]);
            if (j < lol.lists[i].size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    for (int i = 0; i < lol.count; i++) {
        free(lol.lists[i].data);
    }
    free(lol.lists);

    return 0;
}