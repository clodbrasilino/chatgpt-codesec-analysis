#include <stdio.h>
#include <stdlib.h>

int first_missing_positive(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        while (arr[i] > 0 && arr[i] <= n && arr[arr[i] - 1] != arr[i]) {
            int temp = arr[i];
            arr[i] = arr[arr[i] - 1];
            arr[arr[i] - 1] = temp;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (arr[i] != i + 1) {
            return i + 1;
        }
    }
    
    return n + 1;
}

int main(void) {
    int test1[] = {3, 4, -1, 1};
    int test2[] = {1, 2, 0};
    int test3[] = {7, 8, 9, 11, 12};
    int test4[] = {2, 3, 7, 6, 8, -1, -10, 15};
    int test5[] = {1, 2, 3, 4, 5};
    
    printf("%d\n", first_missing_positive(test1, 4));
    printf("%d\n", first_missing_positive(test2, 3));
    printf("%d\n", first_missing_positive(test3, 5));
    printf("%d\n", first_missing_positive(test4, 8));
    printf("%d\n", first_missing_positive(test5, 5));
    
    return 0;
}