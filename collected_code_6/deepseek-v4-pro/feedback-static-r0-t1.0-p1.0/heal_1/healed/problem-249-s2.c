#include <stdio.h>
#include <stdlib.h>

int* intersect(const int* nums1, int nums1Size, const int* nums2, int nums2Size, int* returnSize) {
    int initialSize = nums1Size < nums2Size ? nums1Size : nums2Size;
    int* result = (int*)malloc(initialSize * sizeof(int));
    int* visited = (int*)calloc(nums2Size, sizeof(int));
    *returnSize = 0;
    
    if (result == NULL || visited == NULL) {
        free(result);
        free(visited);
        *returnSize = -1;
        return NULL;
    }
    
    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j] && !visited[j]) {
                result[(*returnSize)++] = nums1[i];
                visited[j] = 1;
                break;
            }
        }
    }
    
    free(visited);
    
    if (*returnSize == 0) {
        free(result);
        return NULL;
    }
    
    int* temp = (int*)realloc(result, (*returnSize) * sizeof(int));
    if (temp == NULL) {
        free(result);
        *returnSize = -1;
        return NULL;
    }
    
    return temp;
}

int main() {
    int nums1[] = {1, 2, 2, 1};
    int nums2[] = {2, 2};
    int returnSize;
    
    int* result = intersect(nums1, 4, nums2, 2, &returnSize);
    
    if (result == NULL) {
        printf("[]\n");
    } else {
        printf("[");
        for (int i = 0; i < returnSize; i++) {
            printf("%d", result[i]);
            if (i < returnSize - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    }
    
    int nums3[] = {4, 9, 5};
    int nums4[] = {9, 4, 9, 8, 4};
    returnSize = 0;
    
    result = intersect(nums3, 3, nums4, 5, &returnSize);
    
    if (result == NULL) {
        printf("[]\n");
    } else {
        printf("[");
        for (int i = 0; i < returnSize; i++) {
            printf("%d", result[i]);
            if (i < returnSize - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    }
    
    return 0;
}