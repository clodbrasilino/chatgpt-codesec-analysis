#include <stdio.h>

#define SIZE 1000

void count_repeated(int arr[], int n) {
    int count[SIZE] = {0};
    int i;

    for(i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    for(i = 0; i < SIZE; i++) {
        if(count[i] > 1) {
            printf("%d appears %d times\n", i, count[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr)/sizeof(arr[0]);

    count_repeated(arr, n);

    return 0;
}