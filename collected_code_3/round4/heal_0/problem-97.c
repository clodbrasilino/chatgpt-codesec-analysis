#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int freq[MAX];

void findFrequency(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }
}

void printFrequency(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(freq[arr[i]] != -1) {
            printf("Frequency of %d: %d\n", arr[i], freq[arr[i]]);
            freq[arr[i]] = -1;
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
    for(int i = 0; i < MAX; i++) {
        freq[i] = 0;
    }
    findFrequency(arr, n);
    printFrequency(arr, n);
    return 0;
}