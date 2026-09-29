#include <stdio.h>
#define SIZE 100

void count_frequency(int arr[], int n) {
    int freq[SIZE] = {0};
    int i;

    for(i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    for(i = 0; i < SIZE; i++) {
        if(freq[i] != 0) {
            printf("%d occurs %d times\n", i, freq[i]);
        }
    }
}

int main() {
    int arr[2][3] = {{1, 2, 3}, {2, 3, 4}};
    int n = sizeof(arr)/sizeof(arr[0][0]);
    int flat_arr[n];
    int i, j, k = 0;

    for(i = 0; i < 2; i++) {
        for(j = 0; j < 3; j++) {
            flat_arr[k++] = arr[i][j];
        }
    }

    count_frequency(flat_arr, n);

    return 0;
}