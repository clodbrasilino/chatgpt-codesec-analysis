#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [1, 0], got <no output>
  *  test case 1 failed: expected [2, 3], got <no output>
  *  test case 0 failed: expected [2, 4, 9], got <no output>
  */

int* access_elements(const int* list, size_t list_size, const size_t* indices, size_t indices_count, size_t* result_size) {
    if (list == NULL || indices == NULL || result_size == NULL) {
        return NULL;
    }
    
    if (indices_count == 0) {
        *result_size = 0;
        return NULL;
    }
    
    int* result = malloc(indices_count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < indices_count; i++) {
        if (indices[i] >= list_size) {
            free(result);
            return NULL;
        }
        result[i] = list[indices[i]];
    }
    
    *result_size = indices_count;
    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    
    size_t indices[] = {0, 2, 4, 7};
    size_t indices_count = sizeof(indices) / sizeof(indices[0]);
    
    size_t result_size = 0;
    int* result = access_elements(list, list_size, indices, indices_count, &result_size);
    
    if (result != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size; i++) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    } else {
        printf("Error accessing elements\n");
    }
    
    return 0;
}