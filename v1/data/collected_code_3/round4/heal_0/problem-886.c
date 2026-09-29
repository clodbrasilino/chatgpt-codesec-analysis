#include <stdio.h>

float average(int arr[], int len) {
    int sum = 0;
    for(int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return (float)sum / len;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    float avg = average(arr, len);
    printf("Average: %.2f\n", avg);
    return 0;
}