#include<stdio.h>

int find_minimal_subsets(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if(max < arr[i]) {
            max = arr[i];
        }
    }

    int frequency[max + 1];
    for (int i = 0; i <= max; i++) {
        frequency[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        frequency[arr[i]]++;
    }

    int maxCount = 0;
    for (int i = 0; i <= max; i++) {
        if (frequency[i] > maxCount) {
            maxCount = frequency[i];
        }
    }

    return maxCount;
}

int main(){
    int arr[] = {1, 1, 2, 2, 3, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d", find_minimal_subsets(arr, size));

    return 0;
}