#include <stdio.h>

void convert_to_tuples(int arr[], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            printf("(%d, %d)\n", arr[i], arr[j]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    convert_to_tuples(arr, n);
    return 0;
}