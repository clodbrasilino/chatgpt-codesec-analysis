#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int freq[MAX_SIZE];

void findFrequency(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 2, 3, 1, 1, 2, 3, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    findFrequency(arr, n);

    for(int i = 0; i < MAX_SIZE; i++) {
        if(freq[i] != 0) {
            printf("%d occurs %d times\n", i, freq[i]);
        }
    }

    return 0;
}