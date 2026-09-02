#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int find_triplet(int arr[], int n, int sum) {
    if (n < 3 || arr == NULL) {
        return 0;
    }
    
    qsort(arr, n, sizeof(int), compare);
    
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int current_sum = arr[i] + arr[left] + arr[right];
            
            if (current_sum == sum) {
                return 1;
            } else if (current_sum < sum) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return 0;
}

int main() {
    int arr[] = {12, 3, 4, 1, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 24;
    
    if (find_triplet(arr, n, sum)) {
        printf("Triplet found\n");
    } else {
        printf("Triplet not found\n");
    }
    
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int sum2 = 10;
    
    if (find_triplet(arr2, n2, sum2)) {
        printf("Triplet found\n");
    } else {
        printf("Triplet not found\n");
    }
    
    int arr3[] = {1, 2};
    /* Possible weaknesses found:
     *  Assignment 'n3=sizeof(arr3)/sizeof(arr3[0])', assigned value is 2
     */
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    /* Possible weaknesses found:
     *  The scope of the variable 'sum3' can be reduced. [variableScope]
     */
    int sum3 = 3;
    
    /* Possible weaknesses found:
     *  Condition 'n3>=3' is always false
     *  Condition 'n3>=3' is always false [knownConditionTrueFalse]
     */
    if (n3 >= 3) {
        if (find_triplet(arr3, n3, sum3)) {
            printf("Triplet found\n");
        } else {
            printf("Triplet not found\n");
        }
    } else {
        printf("Triplet not found\n");
    }
    
    return 0;
}