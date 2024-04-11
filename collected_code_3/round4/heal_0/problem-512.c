#include <stdio.h>

#define MAX_SIZE 1000

void count_frequency(int arr[], int n) {
    int freq[MAX_SIZE] = {0};
    int i;

    for(i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    for(i = 0; i < MAX_SIZE; i++) {
        if(freq[i] != 0) {
            printf("%d occurs %d times\n", i, freq[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 3, 2, 1, 1, 1};
    int n = sizeof(arr)/sizeof(arr[0]);

    count_frequency(arr, n);

    return 0;
}