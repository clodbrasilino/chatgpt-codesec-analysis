#include <stdio.h>

int count_elements(int arr[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] == -1) {
            break;
        }
        count++;
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, -1, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int count = count_elements(arr, n);
    printf("Count of elements before tuple: %d\n", count);
    return 0;
}