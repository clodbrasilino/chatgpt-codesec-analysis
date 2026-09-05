#include <stdio.h>
#include <stdlib.h>

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* result = NULL;
    *returnSize = 0;

    if (nums1Size == 0 || nums2Size == 0 || nums1 == NULL || nums2 == NULL) {
        return NULL;
    }

    result = (int*)malloc(nums1Size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    int count = 0;

    for (int i = 0; i < nums1Size; i++) {
        for (int k = 0; k < count; k++) {
            if (result[k] == nums1[i]) {
                goto next_i;
            }
        }

        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {
                result[count] = nums1[i];
                count++;
                break;
            }
        }

        next_i:;
    }

    if (count == 0) {
        free(result);
        result = NULL;
        return NULL;
    }

    int* trimmed = (int*)realloc(result, count * sizeof(int));
    if (trimmed != NULL) {
        result = trimmed;
    }

    *returnSize = count;
    return result;
}

int main() {
    int arr1[] = {4, 9, 5};
    int arr2[] = {9, 4, 9, 8, 4};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int returnSize = 0;

    int* res = intersection(arr1, size1, arr2, size2, &returnSize);

    if (res != NULL) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
        free(res);
    }

    return 0;
}