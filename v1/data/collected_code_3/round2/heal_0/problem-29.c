#include <stdio.h>

int getOddOccurrence(int arr[], int arr_size) {
    int i;
    int res = 0;
    for (i = 0; i < arr_size; i++) {
        res = res ^ arr[i];
    }
    return res;
}

int main() {
    int arr[] = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", getOddOccurrence(arr, n));
    return 0;
}