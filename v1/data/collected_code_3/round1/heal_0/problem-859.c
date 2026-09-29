#include <stdio.h>
#include <stdlib.h>

void printSublists(int *arr, int n) {
    for (int i = 0; i < (1<<n); i++) {
        printf("{ ");
        for (int j = 0; j < n; j++) {
            if ((i & (1<<j)) != 0) {
                printf("%d ", arr[j]);
            }
        }
        printf("}\n");
    }
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    printSublists(arr, n);
    return 0;
}