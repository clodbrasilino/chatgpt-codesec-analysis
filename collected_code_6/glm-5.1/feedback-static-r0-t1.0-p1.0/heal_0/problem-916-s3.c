#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findTriplet(int *arr, int n, int target) {
    if (arr == NULL) {
        return 0;
    }
    if (n < 3) {
        return 0;
    }
    
    qsort(arr, n, sizeof(int), compare);
    
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            long long current_sum = (long long)arr[i] + arr[left] + arr[right];
            
            if (current_sum == target) {
                return 1;
            } else if (current_sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return 0;
}

int main(void) {
    int arr1[] = {1, 4, 45, 6, 10, 8};
    int target1 = 22;
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = findTriplet(arr1, n1, target1);
    printf("%d\n", result1);

    int arr2[] = {1, 2, 3};
    int target2 = 6;
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = findTriplet(arr2, n2, target2);
    printf("%d\n", result2);

    int arr3[] = {1, 2, 3};
    int target3 = 7;
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = findTriplet(arr3, n3, target3);
    printf("%d\n", result3);

    int result4 = findTriplet(NULL, 5, 10);
    printf("%d\n", result4);

    int arr5[] = {2147483647, 1, 2};
    int target5 = 2147483650;
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    int result5 = findTriplet(arr5, n5, target5);
    printf("%d\n", result5);

    return 0;
}