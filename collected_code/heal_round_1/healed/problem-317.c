#include <stdio.h>

void modifyRunLengthEncoding(const int arr[], const int n) {
    for(int i = 0; i < n;) {
        int count = 1;
        while(i < n - 1 && arr[i] == arr[i + 1]) {
            count++;
            i++;
        }
        printf("%d %d ", count, arr[i]);
        i++;
    }
}

int main() {
    const int arr[] = {1, 1, 2, 3, 3, 3, 4, 4};
    const int n = sizeof(arr) / sizeof(arr[0]);
    modifyRunLengthEncoding(arr, n);
    return 0;
}