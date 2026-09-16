#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_sum(int** list_of_lists, int* sizes, int num_lists) {
    if (list_of_lists == NULL || sizes == NULL || num_lists <= 0) {
        return 0;
    }

    int max_sum = INT_MIN;
    int has_elements = 0;

    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] == NULL || sizes[i] <= 0) {
            continue;
        }

        int current_sum = 0;
        for (int j = 0; j < sizes[i]; j++) {
            current_sum += list_of_lists[i][j];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        has_elements = 1;
    }

    if (!has_elements) {
        return 0;
    }

    return max_sum;
}

int main(void) {
    int num_lists = 3;
    int** list_of_lists = (int**)malloc(num_lists * sizeof(int*));
    int* sizes = (int*)malloc(num_lists * sizeof(int));
    
    if (list_of_lists == NULL || sizes == NULL) {
        if (list_of_lists != NULL) free(list_of_lists);
        if (sizes != NULL) free(sizes);
        return 1;
    }

    sizes[0] = 3;
    list_of_lists[0] = (int*)malloc(sizes[0] * sizeof(int));
    if (list_of_lists[0] != NULL) {
        list_of_lists[0][0] = 1;
        list_of_lists[0][1] = 2;
        list_of_lists[0][2] = 3;
    }

    sizes[1] = 2;
    list_of_lists[1] = (int*)malloc(sizes[1] * sizeof(int));
    if (list_of_lists[1] != NULL) {
        list_of_lists[1][0] = 4;
        list_of_lists[1][1] = 5;
    }

    sizes[2] = 4;
    list_of_lists[2] = (int*)malloc(sizes[2] * sizeof(int));
    if (list_of_lists[2] != NULL) {
        list_of_lists[2][0] = 1;
        list_of_lists[2][1] = 1;
        list_of_lists[2][2] = 1;
        list_of_lists[2][3] = 1;
    }

    int success = 1;
    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] == NULL) {
            success = 0;
            break;
        }
    }

    if (success) {
        int max_sum = find_max_sum(list_of_lists, sizes, num_lists);
        printf("%d\n", max_sum);
    }

    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] != NULL) {
            free(list_of_lists[i]);
            list_of_lists[i] = NULL;
        }
    }
    
    free(list_of_lists);
    list_of_lists = NULL;
    
    free(sizes);
    sizes = NULL;

    return success ? 0 : 1;
}