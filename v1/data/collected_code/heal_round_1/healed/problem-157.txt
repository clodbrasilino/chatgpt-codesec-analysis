#include <stdio.h>

void runLengthEncoding(const int arr[], const int n) {
    int i, count;
    for (i = 0; i < n; i++) {
        count = 1;
        while (i < n - 1 && arr[i] == arr[i + 1]) {
            count++;
            i++;
        }
        printf("%d%d", arr[i], count);
    }
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    runLengthEncoding(arr, n);
    return 0;
}