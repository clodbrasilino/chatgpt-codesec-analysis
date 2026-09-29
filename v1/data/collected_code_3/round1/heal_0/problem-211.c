#include <stdio.h>

int countNumbers(int arr[], int n, int o, int m) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if ((arr[i] & (1 << o)) && (arr[i] & (1 << m)))
            count++;
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int o = 1;
    int m = 2;
    printf("Count of numbers is %d", countNumbers(arr, n, o, m));
    return 0;
}