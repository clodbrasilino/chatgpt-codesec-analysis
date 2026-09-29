#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [5, 7], got <no output>
  *  test case 0 failed: expected [1, 3, 5], got <no output>
  *  test case 2 failed: expected [1, 3], got <no output>
  */

int* remove_even(const int* arr, size_t size, size_t* new_size) {
    if (arr == NULL || new_size == NULL) {
        return NULL;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }
    
    *new_size = count;
    
    if (count == 0) {
        return NULL;
    }
    
    int* result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            result[index++] = arr[i];
        }
    }
    
    return result;
}

int main(void) {
    int test1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(test1) / sizeof(test1[0]);
    size_t new_size1 = 0;
    int* result1 = remove_even(test1, size1, &new_size1);
    if (result1 != NULL) {
        printf("[");
        for (size_t i = 0; i < new_size1; i++) {
            printf("%d", result1[i]);
            if (i < new_size1 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result1);
    }
    
    int test2[] = {2, 4, 5, 6, 7};
    size_t size2 = sizeof(test2) / sizeof(test2[0]);
    size_t new_size2 = 0;
    int* result2 = remove_even(test2, size2, &new_size2);
    if (result2 != NULL) {
        printf("[");
        for (size_t i = 0; i < new_size2; i++) {
            printf("%d", result2[i]);
            if (i < new_size2 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result2);
    }
    
    int test3[] = {1, 2, 3, 4};
    size_t size3 = sizeof(test3) / sizeof(test3[0]);
    size_t new_size3 = 0;
    int* result3 = remove_even(test3, size3, &new_size3);
    if (result3 != NULL) {
        printf("[");
        for (size_t i = 0; i < new_size3; i++) {
            printf("%d", result3[i]);
            if (i < new_size3 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result3);
    }
    
    return EXIT_SUCCESS;
}