#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'nums1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'nums2' can be declared as pointer to const [constParameterPointer]
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* temp = (int*)malloc(nums1Size * sizeof(int));
    if (temp == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {
                int duplicate = 0;
                for (int k = 0; k < count; k++) {
                    if (temp[k] == nums1[i]) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    temp[count++] = nums1[i];
                }
                break;
            }
        }
    }

    int* result = NULL;
    if (count > 0) {
        result = (int*)malloc(count * sizeof(int));
        if (result == NULL) {
            free(temp);
            *returnSize = 0;
            return NULL;
        }
        for (int i = 0; i < count; i++) {
            result[i] = temp[i];
        }
    }
    
    free(temp);
    *returnSize = count;
    return result;
}

int main() {
    int nums1[] = {4, 9, 5};
    int nums2[] = {9, 4, 9, 8, 4};
    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);
    int returnSize = 0;

    int* result = intersection(nums1, nums1Size, nums2, nums2Size, &returnSize);

    if (result != NULL) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}