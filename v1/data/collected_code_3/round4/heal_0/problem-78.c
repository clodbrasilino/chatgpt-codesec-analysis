#include <stdio.h>

int countSetBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int oddSetBits(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++)
        if (countSetBits(arr[i]) & 1)
            count++;
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", oddSetBits(arr, n));
    return 0;
}