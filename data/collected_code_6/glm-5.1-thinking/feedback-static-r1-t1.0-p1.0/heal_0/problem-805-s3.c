#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t len;
} IntList;

typedef struct {
    IntList *lists;
    size_t len;
} ListOfLists;

IntList *find_max_sum_list(ListOfLists *lol) {
    if (lol == NULL || lol->len == 0 || lol->lists == NULL) {
        return NULL;
    }

    long long max_sum = LLONG_MIN;
    IntList *max_list = NULL;

    for (size_t i = 0; i < lol->len; i++) {
        IntList current = lol->lists[i];
        if (current.len > 0 && current.data == NULL) {
            continue;
        }

        long long current_sum = 0;
        for (size_t j = 0; j < current.len; j++) {
            current_sum += current.data[j];
        }

        if (max_list == NULL || current_sum > max_sum) {
            max_sum = current_sum;
            max_list = &lol->lists[i];
        }
    }

    return max_list;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {10, 20, 30};
    int data3[] = {-5, -10};

    ListOfLists lol;
    lol.len = 3;
    lol.lists = malloc(sizeof(IntList) * lol.len);

    if (lol.lists == NULL) {
        return EXIT_FAILURE;
    }

    lol.lists[0].data = data1;
    lol.lists[0].len = sizeof(data1) / sizeof(data1[0]);

    lol.lists[1].data = data2;
    lol.lists[1].len = sizeof(data2) / sizeof(data2[0]);

    lol.lists[2].data = data3;
    lol.lists[2].len = sizeof(data3) / sizeof(data3[0]);

    IntList *result = find_max_sum_list(&lol);

    if (result != NULL) {
        printf("List with highest sum: ");
        for (size_t i = 0; i < result->len; i++) {
            printf("%d ", result->data[i]);
        }
        printf("\n");
    } else {
        printf("No valid list found.\n");
    }

    free(lol.lists);

    return EXIT_SUCCESS;
}