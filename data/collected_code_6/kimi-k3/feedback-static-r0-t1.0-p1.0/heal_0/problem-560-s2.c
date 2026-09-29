#include <stdio.h>
#include <stdlib.h>

int is_in_array(int *arr, int size, int value) {
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

int find_union(int *tuple1, int size1, int *tuple2, int size2, int *result) {
    int count = 0;
    int i;
    
    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        return -1;
    }
    
    if (size1 < 0 || size2 < 0) {
        return -1;
    }
    
    for (i = 0; i < size1; i++) {
        if (!is_in_array(result, count, tuple1[i])) {
            result[count] = tuple1[i];
            count++;
        }
    }
    
    for (i = 0; i < size2; i++) {
        if (!is_in_array(result, count, tuple2[i])) {
            result[count] = tuple2[i];
            count++;
        }
    }
    
    return count;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int *union_result = NULL;
    int union_size;
    int i;
    
    union_result = (int *)malloc((size1 + size2) * sizeof(int));
    if (union_result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    union_size = find_union(tuple1, size1, tuple2, size2, union_result);
    
    if (union_size < 0) {
        fprintf(stderr, "Error finding union\n");
        free(union_result);
        return EXIT_FAILURE;
    }
    
    printf("Tuple 1: ");
    for (i = 0; i < size1; i++) {
        printf("%d ", tuple1[i]);
    }
    printf("\n");
    
    printf("Tuple 2: ");
    for (i = 0; i < size2; i++) {
        printf("%d ", tuple2[i]);
    }
    printf("\n");
    
    printf("Union: ");
    for (i = 0; i < union_size; i++) {
        printf("%d ", union_result[i]);
    }
    printf("\n");
    
    free(union_result);
    
    return EXIT_SUCCESS;
}