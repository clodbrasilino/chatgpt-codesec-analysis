#include <stdio.h>
#include <stdbool.h>

bool isSubarray(const int* array, size_t array_len, const int* subarray, size_t subarray_len) {
    if (array == NULL || subarray == NULL) {
        return false;
    }
    
    if (subarray_len == 0) {
        return true;
    }
    
    if (array_len < subarray_len) {
        return false;
    }

    for (size_t i = 0; i <= array_len - subarray_len; i++) {
        size_t j = 0;
        while (j < subarray_len && array[i + j] == subarray[j]) {
            j++;
        }
        if (j == subarray_len) {
            return true;
        }
    }

    return false;
}

int main(void) {
    int array[] = {1, 2, 3, 4, 5, 6, 7};
    int subarray1[] = {3, 4, 5};
    int subarray2[] = {3, 5, 6};

    size_t array_len = sizeof(array) / sizeof(array[0]);
    size_t subarray1_len = sizeof(subarray1) / sizeof(subarray1[0]);
    size_t subarray2_len = sizeof(subarray2) / sizeof(subarray2[0]);

    bool result1 = isSubarray(array, array_len, subarray1, subarray1_len);
    if (result1) {
        printf("subarray1 is a subarray of array\n");
    } else {
        printf("subarray1 is not a subarray of array\n");
    }

    bool result2 = isSubarray(array, array_len, subarray2, subarray2_len);
    if (result2) {
        printf("subarray2 is a subarray of array\n");
    } else {
        printf("subarray2 is not a subarray of array\n");
    }

    return 0;
}