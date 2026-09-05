#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int* get_n_smallest(const int *data, size_t data_size, size_t n, size_t *result_size) {
    if (data == NULL || result_size == NULL || data_size == 0 || n == 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }
    
    size_t actual_n = (n < data_size) ? n : data_size;
    int *temp = malloc(data_size * sizeof(int));
    if (temp == NULL) {
        *result_size = 0;
        return NULL;
    }
    
    memcpy(temp, data, data_size * sizeof(int));
    qsort(temp, data_size, sizeof(int), compare_ints);
    
    int *result = malloc(actual_n * sizeof(int));
    if (result == NULL) {
        free(temp);
        *result_size = 0;
        return NULL;
    }
    
    memcpy(result, temp, actual_n * sizeof(int));
    free(temp);
    *result_size = actual_n;
    return result;
}

int main(void) {
    int dataset[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t result_size = 0;
    
    int *smallest = get_n_smallest(dataset, dataset_size, n, &result_size);
    
    if (smallest == NULL) {
        fprintf(stderr, "Error: Failed to retrieve smallest items\n");
        return EXIT_FAILURE;
    }
    
    printf("The %zu smallest items are: ", result_size);
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");
    
    free(smallest);
    return EXIT_SUCCESS;
}