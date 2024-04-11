#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int firstElementKTimes(int arr[], int n, int k) {
    int hash[MAX] = {0};
    int i;

    for(i = 0; i < n; i++)
        hash[arr[i]]++;

    for(i = 0; i < n; i++)
        if(hash[arr[i]] == k)
            return arr[i];

    return -1;
}

int main() {
    int arr[] = {1, 7, 4, 3, 4, 8, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 2;
    printf("%d", firstElementKTimes(arr, n, k));
    return 0;
}