#include <stdbool.h>
#include <stdio.h>

bool isMajority(int arr[], int size, int candidate) {
    int i, freq = 0;
    for(i=0; i<size; i++) {
        if(arr[i] == candidate) {
            freq++;
        }

        if(freq > size/2) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    int candidate = arr[size/2];

    if(isMajority(arr, size, candidate)) { 
        printf("%d is the majority element\n", candidate); 
    }
    else {
        printf("There is no majority element\n");
    }

    return 0;
}