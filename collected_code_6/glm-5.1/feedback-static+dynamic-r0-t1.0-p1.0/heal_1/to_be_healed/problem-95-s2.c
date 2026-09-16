#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_min_length(int *list, size_t size) {
    if (list == NULL) {
        return -1;
    }
    if (size == 0) {
        return -1;
    }
    int min_len = INT_MAX;
    size_t current_len = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] == 0) {
            if (current_len > 0 && current_len < (size_t)min_len) {
                min_len = (int)current_len;
            }
            current_len = 0;
        } else {
            current_len++;
        }
    }
    if (current_len > 0 && current_len < (size_t)min_len) {
        min_len = (int)current_len;
    }
    if (min_len == INT_MAX) {
        return -1;
    }
    return min_len;
}

int main(void) {
    int arr1[] = {5, 1, 2, 0, 7, 8, 0, 4, 5, 6, 2, 0, 9, 3};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_min_length(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {1, 2, 3, 4};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_min_length(arr2, size2);
    printf("%d\n", result2);

    int *arr3 = NULL;
    size_t size3 = 0;
    int result3 = find_min_length(arr3, size3);
    printf("%d\n", result3);

    int arr4[] = {0, 0, 0};
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    int result4 = find_min_length(arr4, size4);
    printf("%d\n", result4);

    return 0;
}