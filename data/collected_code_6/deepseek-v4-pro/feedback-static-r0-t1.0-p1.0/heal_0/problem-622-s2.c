#include <stdio.h>

float median(int arr1[], int arr2[], int n) {
    int lo1 = 0, hi1 = n;
    
    while (lo1 <= hi1) {
        int mid1 = (lo1 + hi1) / 2;
        int mid2 = n - mid1;
        
        int l1 = (mid1 == 0) ? -2147483648 : arr1[mid1 - 1];
        int r1 = (mid1 == n) ? 2147483647 : arr1[mid1];
        int l2 = (mid2 == 0) ? -2147483648 : arr2[mid2 - 1];
        int r2 = (mid2 == n) ? 2147483647 : arr2[mid2];
        
        if (l1 <= r2 && l2 <= r1) {
            if (n % 2 == 0) {
                int max_left = (l1 > l2) ? l1 : l2;
                int min_right = (r1 < r2) ? r1 : r2;
                return (max_left + min_right) / 2.0f;
            } else {
                int max_left = (l1 > l2) ? l1 : l2;
                return (float)max_left;
            }
        } else if (l1 > r2) {
            hi1 = mid1 - 1;
        } else {
            lo1 = mid1 + 1;
        }
    }
    
    return -1.0f;
}

int main(void) {
    int n;
    
    printf("Enter size of arrays: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid size\n");
        return 1;
    }
    
    int arr1[100], arr2[100];
    
    printf("Enter first sorted array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
    }
    
    printf("Enter second sorted array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr2[i]);
    }
    
    float result = median(arr1, arr2, n);
    printf("Median: %.2f\n", result);
    
    return 0;
}