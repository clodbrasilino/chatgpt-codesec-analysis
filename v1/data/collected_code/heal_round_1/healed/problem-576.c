#include <stdio.h>

int isSubArray(const int arr1[], const int n1, const int arr2[], const int n2) {
    int i, j, start = 0;
    for (i = 0; i < n1; i++) {
        for(j = 0; j < n2; j++){
            if(arr1[start + j] != arr2[j]) break;
        }
        if(j == n2) return 1;
        start++;
    }
    return 0;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
  
    int arr2[] = {3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    if (isSubArray(arr1, n1, arr2, n2)) {
        printf("arr2 is a subarray of arr1\n");
    } else {
        printf("arr2 is not a subarray of arr1\n");
    }

    return 0;
}