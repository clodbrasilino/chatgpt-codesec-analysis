#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
long long find_max_sum(int **list_of_lists, int *sizes, int num_lists) {
    if (list_of_lists == NULL || sizes == NULL || num_lists <= 0) {
        return LLONG_MIN;
    }

    long long max_sum = LLONG_MIN;

    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] == NULL || sizes[i] < 0) {
            continue;
        }

        long long current_sum = 0;
        int has_elements = 0;

        for (int j = 0; j < sizes[i]; j++) {
            current_sum += (long long)list_of_lists[i][j];
            has_elements = 1;
        }

        if (has_elements && current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main(void) {
    int num_lists = 3;
    
    int **list_of_lists = (int **)malloc((size_t)num_lists * sizeof(int *));
    if (list_of_lists == NULL) {
        return EXIT_FAILURE;
    }
    
    int *sizes = (int *)malloc((size_t)num_lists * sizeof(int));
    if (sizes == NULL) {
        free(list_of_lists);
        return EXIT_FAILURE;
    }

    sizes[0] = 3;
    list_of_lists[0] = (int *)malloc((size_t)sizes[0] * sizeof(int));
    if (list_of_lists[0] != NULL) {
        list_of_lists[0][0] = 1;
        list_of_lists[0][1] = 2;
        list_of_lists[0][2] = 3;
    }

    sizes[1] = 2;
    list_of_lists[1] = (int *)malloc((size_t)sizes[1] * sizeof(int));
    if (list_of_lists[1] != NULL) {
        list_of_lists[1][0] = 4;
        list_of_lists[1][1] = 5;
    }

    sizes[2] = 4;
    list_of_lists[2] = (int *)malloc((size_t)sizes[2] * sizeof(int));
    if (list_of_lists[2] != NULL) {
        list_of_lists[2][0] = -1;
        list_of_lists[2][1] = -2;
        list_of_lists[2][2] = -3;
        list_of_lists[2][3] = 10;
    }

    int allocations_successful = 1;
    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] == NULL) {
            allocations_successful = 0;
            break;
        }
    }

    if (allocations_successful) {
        long long max_sum = find_max_sum(list_of_lists, sizes, num_lists);
        if (max_sum != LLONG_MIN) {
            printf("%lld\n", max_sum);
        } else {
            printf("No valid lists found.\n");
        }
    }

    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] != NULL) {
            free(list_of_lists[i]);
        }
    }
    free(list_of_lists);
    free(sizes);

    return EXIT_SUCCESS;
}