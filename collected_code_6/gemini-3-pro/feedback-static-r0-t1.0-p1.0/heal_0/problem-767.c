#include <stdio.h>
#include <stdlib.h>

int countPairs(const int* arr, int n, int sum) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == sum) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 6;
    
    int result = countPairs(arr, n, sum);
    
    printf("Count of pairs is %d\n", result);
    
    return EXIT_SUCCESS;
}