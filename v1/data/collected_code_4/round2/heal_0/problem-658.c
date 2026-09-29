#include <stdio.h>

#define MAX_SIZE 100

int findMaxOcurring(int arr[], int n) {
    int count[MAX_SIZE] = {0};
    int max = 0;
    int result = -1;

    for(int i = 0; i < n; i++) {
        count[arr[i]]++;

        if(max < count[arr[i]]) {
            max = count[arr[i]];
            result = arr[i];
        } else if(max == count[arr[i]]) {
            if(result > arr[i])
                result = arr[i];
        }
    }
    return result;
}

int main() {
    int arr[] = {3,4,2,2,3,1,1,1,3,4,4,4};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", findMaxOcurring(arr, n));

    return 0;
}