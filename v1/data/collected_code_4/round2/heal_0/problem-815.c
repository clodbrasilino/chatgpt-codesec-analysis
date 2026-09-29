#include <stdio.h>

void sortArray(int arr[], int n) {
    int countZero = 0, countOne = 0, countTwo = 0;

    for(int i = 0; i < n; i++) {
        if(arr[i] == 0) 
            countZero++;
        else if(arr[i] == 1)
            countOne++;
        else 
            countTwo++;
    }

    int i = 0;

    while(i < countZero) {
        arr[i++] = 0;
    }

    while(i < countZero + countOne) {
        arr[i++] = 1;
    }

    while(i < n) { 
        arr[i++] = 2;
    }
}

int main() {
    int arr[] = {0, 1, 2, 0, 2, 0, 1, 2, 1, 0, 1, 2, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortArray(arr, n);

    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}