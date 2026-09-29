#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int len;
} List;

int compare_lists(const void *a, const void *b) {
    const List *la = (const List *)a;
    const List *lb = (const List *)b;

    if (la->len < lb->len) return -1;
    if (la->len > lb->len) return 1;

    size_t min_len = la->len;
    for (size_t i = 0; i < min_len; i++) {
        if (la->data[i] < lb->data[i]) return -1;
        if (la->data[i] > lb->data[i]) return 1;
    }

    return 0;
}

void free_lists(List *lists, size_t count) {
    if (lists == NULL) return;
    for (size_t i = 0; i < count; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
        lists[i].len = 0;
    }
    free(lists);
}

int main(void) {
    size_t num_lists = 3;
    List *lists = (List *)malloc(num_lists * sizeof(List));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    int data0[] = {3, 2, 1};
    lists[0].data = (int *)malloc(3 * sizeof(int));
    if (lists[0].data == NULL) {
        free(lists);
        return EXIT_FAILURE;
    }
    memcpy(lists[0].data, data0, 3 * sizeof(int));
    lists[0].len = 3;

    int data1[] = {1, 1};
    lists[1].data = (int *)malloc(2 * sizeof(int));
    if (lists[1].data == NULL) {
        free_lists(lists, 1);
        return EXIT_FAILURE;
    }
    memcpy(lists[1].data, data1, 2 * sizeof(int));
    lists[1].len = 2;

    int data2[] = {2, 2};
    lists[2].data = (int *)malloc(2 * sizeof(int));
    if (lists[2].data == NULL) {
        free_lists(lists, 2);
        return EXIT_FAILURE;
    }
    memcpy(lists[2].data, data2, 2 * sizeof(int));
    lists[2].len = 2;

    qsort(lists, num_lists, sizeof(List), compare_lists);

    for (size_t i = 0; i < num_lists; i++) {
        printf("[");
        for (size_t j = 0; j < lists[i].len; j++) {
            printf("%d", lists[i].data[j]);
            if (j < lists[i].len - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    free_lists(lists, num_lists);

    return EXIT_SUCCESS;
}