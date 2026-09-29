#include <stdio.h>

#define MAX_ARR_LENGTH 256

void count_occurrences(int arr[], int len) {
    int counter[MAX_ARR_LENGTH] = {0};

    for(int i = 0; i < len; i++) {
        if(arr[i] < MAX_ARR_LENGTH && arr[i] >= 0) {
            counter[arr[i]]++;
        } else {
            printf("Array contains value(s) out of allowable range 0-%d.", MAX_ARR_LENGTH - 1);
            return;
        }
    }

    for(int i = 0; i < MAX_ARR_LENGTH; i++) {
        if(counter[i] > 0) {
            printf("Value %d occurred %d times.\n", i, counter[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 1, 2, 3, 2, 2, 4, 5, 6, 4, 5, 6, 6};
    int len = sizeof(arr) / sizeof(arr[0]);

    count_occurrences(arr, len);

    return 0;
}