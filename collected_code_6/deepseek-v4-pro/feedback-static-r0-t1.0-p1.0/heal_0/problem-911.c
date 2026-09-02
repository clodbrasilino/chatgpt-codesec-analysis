#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare_asc(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compare_desc(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 > arg2) return -1;
    if (arg1 < arg2) return 1;
    return 0;
}

int maxProductOfThree(int arr[], int n) {
    if (n < 3) {
        return INT_MIN;
    }
    
    int *pos = malloc(n * sizeof(int));
    int *neg = malloc(n * sizeof(int));
    if (pos == NULL || neg == NULL) {
        free(pos);
        free(neg);
        return INT_MIN;
    }
    
    int pos_count = 0;
    int neg_count = 0;
    int zero_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            pos[pos_count++] = arr[i];
        } else if (arr[i] < 0) {
            neg[neg_count++] = arr[i];
        } else {
            zero_count++;
        }
    }
    
    qsort(pos, pos_count, sizeof(int), compare_desc);
    qsort(neg, neg_count, sizeof(int), compare_asc);
    
    int candidates[6];
    int cand_count = 0;
    
    if (pos_count >= 3) {
        candidates[cand_count++] = pos[0] * pos[1] * pos[2];
    }
    
    if (pos_count >= 1 && neg_count >= 2) {
        candidates[cand_count++] = pos[0] * neg[0] * neg[1];
    }
    
    if (pos_count >= 2 && neg_count >= 1) {
        candidates[cand_count++] = pos[0] * pos[1] * neg[neg_count - 1];
    }
    
    if (pos_count == 2 && zero_count >= 1) {
        candidates[cand_count++] = pos[0] * pos[1] * 0;
    }
    
    if (pos_count == 1 && neg_count >= 2) {
        candidates[cand_count++] = pos[0] * neg[0] * neg[1];
    }
    
    if (neg_count >= 3) {
        candidates[cand_count++] = neg[neg_count - 1] * neg[neg_count - 2] * neg[neg_count - 3];
    }
    
    if (zero_count >= 1) {
        candidates[cand_count++] = 0;
    }
    
    if (pos_count == 1 && neg_count == 1 && zero_count >= 1) {
        candidates[cand_count++] = 0;
    }
    
    if (pos_count >= 1 && neg_count >= 1 && zero_count >= 1) {
        candidates[cand_count++] = 0;
    }
    
    if (pos_count >= 2 && neg_count >= 1 && zero_count >= 1) {
        candidates[cand_count++] = 0;
    }
    
    if (cand_count == 0) {
        if (zero_count >= 1) {
            free(pos);
            free(neg);
            return 0;
        }
        free(pos);
        free(neg);
        return INT_MIN;
    }
    
    int max_product = candidates[0];
    for (int i = 1; i < cand_count; i++) {
        if (candidates[i] > max_product) {
            max_product = candidates[i];
        }
    }
    
    free(pos);
    free(neg);
    return max_product;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", maxProductOfThree(arr1, n1));
    
    int arr2[] = {-10, -10, 5, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", maxProductOfThree(arr2, n2));
    
    int arr3[] = {-1, -2, -3, -4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", maxProductOfThree(arr3, n3));
    
    int arr4[] = {-1, 0, 1, 2};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", maxProductOfThree(arr4, n4));
    
    int arr5[] = {0, 0, 0};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", maxProductOfThree(arr5, n5));
    
    int arr6[] = {-4, -3, -2, -1, 60};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);
    printf("%d\n", maxProductOfThree(arr6, n6));
    
    int arr7[] = {-5, 1, 2, 3};
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    printf("%d\n", maxProductOfThree(arr7, n7));
    
    return 0;
}