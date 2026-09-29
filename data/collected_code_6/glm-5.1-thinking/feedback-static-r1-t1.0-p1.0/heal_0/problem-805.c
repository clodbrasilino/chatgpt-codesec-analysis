#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

struct List {
    int *data;
    size_t size;
};

struct List *find_max_sum_list(struct List *lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    struct List *max_list = NULL;
    long long max_sum = 0;

    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i].data == NULL || lists[i].size == 0) {
            continue;
        }

        long long current_sum = 0;
        for (size_t j = 0; j < lists[i].size; j++) {
            current_sum += lists[i].data[j];
        }

        if (max_list == NULL || current_sum > max_sum) {
            max_sum = current_sum;
            max_list = &lists[i];
        }
    }

    return max_list;
}

int main(void) {
    size_t num_lists = 3;
    struct List *lists = malloc(num_lists * sizeof(struct List));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0].size = 3;
    lists[0].data = malloc(lists[0].size * sizeof(int));
    if (lists[0].data == NULL) {
        free(lists);
        return EXIT_FAILURE;
    }
    lists[0].data[0] = 1;
    lists[0].data[1] = 2;
    lists[0].data[2] = 3;

    lists[1].size = 4;
    lists[1].data = malloc(lists[1].size * sizeof(int));
    if (lists[1].data == NULL) {
        free(lists[0].data);
        free(lists);
        return EXIT_FAILURE;
    }
    lists[1].data[0] = 4;
    lists[1].data[1] = 5;
    lists[1].data[2] = 6;
    lists[1].data[3] = 7;

    lists[2].size = 3;
    lists[2].data = malloc(lists[2].size * sizeof(int));
    if (lists[2].data == NULL) {
        free(lists[1].data);
        free(lists[0].data);
        free(lists);
        return EXIT_FAILURE;
    }
    lists[2].data[0] = -1;
    lists[2].data[1] = -2;
    lists[2].data[2] = -3;

    struct List *result = find_max_sum_list(lists, num_lists);

    if (result != NULL) {
        for (size_t i = 0; i < result->size; i++) {
            printf("%d ", result->data[i]);
        }
        printf("\n");
    }

    free(lists[2].data);
    free(lists[1].data);
    free(lists[0].data);
    free(lists);

    return EXIT_SUCCESS;
}