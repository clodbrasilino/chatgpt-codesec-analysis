#include <stdio.h>

float averageValue(int arr[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (float)sum/size;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr)/sizeof(int);
    float avg = averageValue(arr, size);
    printf("Average value of list: %f", avg);
    return 0;
}