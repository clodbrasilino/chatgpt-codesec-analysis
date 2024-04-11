#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void getFrequency(int arr[], int n) {
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
    int arr[] = {1, 2, 8, 3, 2, 2, 2, 5, 1};
    int n = sizeof(arr)/sizeof(arr[0]);

    getFrequency(arr, n);

    return 0;
}