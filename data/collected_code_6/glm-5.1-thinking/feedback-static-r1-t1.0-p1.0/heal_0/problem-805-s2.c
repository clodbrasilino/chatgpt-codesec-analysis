#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t len;
} IntList;

IntList *find_max_sum_list(IntList *lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    IntList *max_list = NULL;
    long long max_sum = LLONG_MIN;
    int found = 0;

    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i].data != NULL && lists[i].len > 0) {
            long long current_sum = 0;
            for (size_t j = 0; j < lists[i].len; j++) {
                current_sum += lists[i].data[j];
            }
            if (!found || current_sum > max_sum) {
                max_sum = current_sum;
                max_list = &lists[i];
                found = 1;
            }
        }
    }

    return max_list;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {10, 20, 30};
    int c[] = {-5, -10};
    int d[] = {5};

    size_t num_lists = 4;
    IntList *lists = malloc(num_lists * sizeof(IntList));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0].data = a;
    lists[0].len = sizeof(a) / sizeof(a[0]);
    lists[1].data = b;
    lists[1].len = sizeof(b) / sizeof(b[0]);
    lists[2].data = c;
    lists[2].len = sizeof(c) / sizeof(c[0]);
    lists[3].data = NULL;
    lists[3].len = 0;

    IntList *result = find_max_sum_list(lists, num_lists);

    if (result != NULL) {
        printf("List with highest sum: ");
        for (size_t i = 0; i < result->len; i++) {
            printf("%d ", result->data[i]);
        }
        printf("\n");
    } else {
        printf("No valid lists found.\n");
    }

    free(lists);

    return EXIT_SUCCESS;
}