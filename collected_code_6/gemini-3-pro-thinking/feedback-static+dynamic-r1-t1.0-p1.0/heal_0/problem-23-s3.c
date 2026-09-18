#include <stdio.h>
#include <stdlib.h>

int find_max_sum(int **lists, const size_t *sizes, size_t num_lists, long long *max_sum) {
    long long current_max = 0;
    int has_elements = 0;

    if (!lists || !sizes || !max_sum || num_lists == 0) {
        return -1;
    }

    for (size_t i = 0; i < num_lists; i++) {
        long long current_sum = 0;

        if (!lists[i] && sizes[i] > 0) {
            return -1;
        }

        for (size_t j = 0; j < sizes[i]; j++) {
            current_sum += lists[i][j];
        }

        if (!has_elements || current_sum > current_max) {
            current_max = current_sum;
            has_elements = 1;
        }
    }

    if (!has_elements) {
        return -1;
    }

    *max_sum = current_max;
    return 0;
}

int main(void) {
    size_t num_lists = 3;
    long long max_sum = 0;
    int **lists = NULL;
    size_t *sizes = NULL;

    lists = malloc(num_lists * sizeof(int *));
    if (!lists) {
        return EXIT_FAILURE;
    }

    sizes = malloc(num_lists * sizeof(size_t));
    if (!sizes) {
        free(lists);
        return EXIT_FAILURE;
    }

    sizes[0] = 3;
    sizes[1] = 2;
    sizes[2] = 4;

    for (size_t i = 0; i < num_lists; i++) {
        lists[i] = malloc(sizes[i] * sizeof(int));
        if (!lists[i]) {
            for (size_t j = 0; j < i; j++) {
                free(lists[j]);
            }
            free(lists);
            free(sizes);
            return EXIT_FAILURE;
        }
    }

    lists[0][0] = 1;
    lists[0][1] = 2;
    lists[0][2] = 3;

    lists[1][0] = 4;
    lists[1][1] = 5;

    lists[2][0] = 10;
    lists[2][1] = -2;
    lists[2][2] = 3;
    lists[2][3] = 4;

    if (find_max_sum(lists, sizes, num_lists, &max_sum) == 0) {
        printf("%lld\n", max_sum);
    } else {
        printf("Error calculating maximum sum.\n");
    }

    for (size_t i = 0; i < num_lists; i++) {
        free(lists[i]);
    }
    free(lists);
    free(sizes);

    return EXIT_SUCCESS;
}