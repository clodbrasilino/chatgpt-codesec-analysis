#include <stdio.h>

void findLargestDivisibleSubset(int arr[], int n) {
    int largest = 0;
    int index = -1;
    int divCount[n];
    int previous[n];
    for (int i=0; i<n; i++) {
        divCount[i] = 1;
        previous[i] = -1;
        for (int j=0; j<i; j++) {
            if (arr[i] % arr[j] == 0) {
                if (1 + divCount[j] > divCount[i]) {
                    divCount[i] = 1 + divCount[j];
                    previous[i] = j;
                }
            }
        }
        if (divCount[i] > largest) {
            largest = divCount[i];
            index = i;
        }
    }
    while (index != -1) {
        printf("%d ", arr[index]);
        index = previous[index];
    }
}

int main() {
    int arr[] = {18, 1, 3, 6, 13, 17};
    int n = sizeof(arr)/sizeof(arr[0]);
    findLargestDivisibleSubset(arr, n);
    return 0;
}