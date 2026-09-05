#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool has_common_element(const int *list1, size_t size1, const int *list2, size_t size2) {
    if (list1 == NULL || list2 == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int arr3[] = {11, 12, 3, 14, 15};

    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    bool result1 = has_common_element(arr1, size1, arr2, size2);
    bool result2 = has_common_element(arr1, size1, arr3, size3);

    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}