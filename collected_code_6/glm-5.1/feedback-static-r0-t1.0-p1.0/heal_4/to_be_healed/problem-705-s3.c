#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} List;

int compare_lists(const void *a, const void *b) {
    const List *list_a = (const List *)a;
    const List *list_b = (const List *)b;

    if (list_a->length < list_b->length) {
        return -1;
    }
    if (list_a->length > list_b->length) {
        return 1;
    }

    for (size_t i = 0; i < list_a->length; i++) {
        if (list_a->data[i] < list_b->data[i]) {
            return -1;
        }
        if (list_a->data[i] > list_b->data[i]) {
            return 1;
        }
    }

    return 0;
}

void sort_list_of_lists(List *lists, size_t count) {
    if (lists == NULL || count == 0) {
        return;
    }
    qsort(lists, count, sizeof(List), compare_lists);
}

void free_list_of_lists(List *lists, size_t count) {
    if (lists == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
        lists[i].length = 0;
    }
    free(lists);
}

int main(void) {
    size_t count = 5;
    List *lists = (List *)malloc(count * sizeof(List));
    if (lists == NULL) {
        return 1;
    }

    int a0[] = {5, 2};
    int a1[] = {1, 2, 3, 4};
    int a2[] = {1, 2, 3};
    int a3[] = {1, 0};
    int a4[] = {1, 2, 3};

    lists[0].length = sizeof(a0) / sizeof(a0[0]);
    lists[0].data = (int *)malloc(lists[0].length * sizeof(int));
    if (lists[0].data == NULL) { free_list_of_lists(lists, 0); return 1; }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[0].data, a0, (lists[0].length < sizeof(a0) / sizeof(a0[0]) ? lists[0].length : sizeof(a0) / sizeof(a0[0])) * sizeof(int));

    lists[1].length = sizeof(a1) / sizeof(a1[0]);
    lists[1].data = (int *)malloc(lists[1].length * sizeof(int));
    if (lists[1].data == NULL) { free_list_of_lists(lists, 1); return 1; }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[1].data, a1, (lists[1].length < sizeof(a1) / sizeof(a1[0]) ? lists[1].length : sizeof(a1) / sizeof(a1[0])) * sizeof(int));

    lists[2].length = sizeof(a2) / sizeof(a2[0]);
    lists[2].data = (int *)malloc(lists[2].length * sizeof(int));
    if (lists[2].data == NULL) { free_list_of_lists(lists, 2); return 1; }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[2].data, a2, (lists[2].length < sizeof(a2) / sizeof(a2[0]) ? lists[2].length : sizeof(a2) / sizeof(a2[0])) * sizeof(int));

    lists[3].length = sizeof(a3) / sizeof(a3[0]);
    lists[3].data = (int *)malloc(lists[3].length * sizeof(int));
    if (lists[3].data == NULL) { free_list_of_lists(lists, 3); return 1; }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[3].data, a3, (lists[3].length < sizeof(a3) / sizeof(a3[0]) ? lists[3].length : sizeof(a3) / sizeof(a3[0])) * sizeof(int));

    lists[4].length = sizeof(a4) / sizeof(a4[0]);
    lists[4].data = (int *)malloc(lists[4].length * sizeof(int));
    if (lists[4].data == NULL) { free_list_of_lists(lists, 4); return 1; }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(lists[4].data, a4, (lists[4].length < sizeof(a4) / sizeof(a4[0]) ? lists[4].length : sizeof(a4) / sizeof(a4[0])) * sizeof(int));

    printf("Before sorting:\n");
    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < lists[i].length; j++) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    sort_list_of_lists(lists, count);

    printf("\nAfter sorting:\n");
    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < lists[i].length; j++) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    free_list_of_lists(lists, count);

    return 0;
}