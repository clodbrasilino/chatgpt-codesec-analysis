#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

void findFrequency(int arr[], int n) {
    int freq[MAX] = {0};
    int i;

    for(i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    for(i = 0; i < MAX; i++) {
        if(freq[i] != 0) {
            printf("%d occurs %d times\n", i, freq[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr)/sizeof(arr[0]);

    findFrequency(arr, n);

    return 0;
}