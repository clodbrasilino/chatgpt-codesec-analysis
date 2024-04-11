#include <stdio.h>

float average(int arr[], int length) {
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += arr[i];
    }
    return (float)sum / length;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    float avg = average(arr, length);
    printf("Average is: %.2f\n", avg);
    return 0;
}