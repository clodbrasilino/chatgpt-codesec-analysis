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
    int arr[] = {5, 7, 9, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int o = 0;
    int m = 1;
    printf("Count = %d", countNumbers(arr, n, o, m));
    return 0;
}