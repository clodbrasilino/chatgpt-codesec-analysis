#include <stdio.h>

double positiveRatio(int arr[], int n) {
    int positiveCount = 0;
    int i;
    for(i = 0; i < n; i++){
        if(arr[i] > 0) {
            positiveCount++;
        }
    }
    return (double)positiveCount/n;
}

int main(void) {
    int arr[] = {1, -2, 3, -4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    double ratio = positiveRatio(arr, n);

    printf("Ratio of positive numbers: %f\n", ratio);
    return 0;
}