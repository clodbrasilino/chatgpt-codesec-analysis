#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t len;
} List;

int compare_lists(const void *a, const void *b) {
    const List *la = (const List *)a;
    const List *lb = (const List *)b;

    if (la->len < lb->len) return -1;
    if (la->len > lb->len) return 1;

    for (size_t i = 0; i < la->len; i++) {
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
    List *lists = malloc(num_lists * sizeof(List));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    int data0[] = {3, 2, 1};
    lists[0].len = sizeof(data0) / sizeof(data0[0]);
    lists[0].data = malloc(lists[0].len * sizeof(int));
    if (lists[0].data == NULL) {
        free(lists);
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[0].data, data0, lists[0].len * sizeof(int));

    int data1[] = {1, 1};
    lists[1].len = sizeof(data1) / sizeof(data1[0]);
    lists[1].data = malloc(lists[1].len * sizeof(int));
    if (lists[1].data == NULL) {
        free_lists(lists, 1);
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[1].data, data1, lists[1].len * sizeof(int));

    int data2[] = {2, 2};
    lists[2].len = sizeof(data2) / sizeof(data2[0]);
    lists[2].data = malloc(lists[2].len * sizeof(int));
    if (lists[2].data == NULL) {
        free_lists(lists, 2);
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[2].data, data2, lists[2].len * sizeof(int));

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