#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void findFrequency(int arr[], int n) {
    int freq[MAX] = {0};

    for(int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    for(int i = 0; i < MAX; i++) {
        if(freq[i] != 0) {
            printf("%d occurs %d times\n", i, freq[i]);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findFrequency(arr, n);

    return 0;
}