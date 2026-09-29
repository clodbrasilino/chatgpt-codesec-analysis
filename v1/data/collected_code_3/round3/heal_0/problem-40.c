#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int frequency[MAX][2];

void findFrequency(int arr[], int n) {
    for(int i = 0; i < MAX; i++) {
        frequency[i][0] = -1;
        frequency[i][1] = 0;
    }

    for(int i = 0; i < n; i++) {
        int j;
        for(j = 0; j < n; j++) {
            if(frequency[j][0] == arr[i]) {
                frequency[j][1]++;
                break;
            }
        }
        if(j == n) {
            frequency[j][0] = arr[i];
            frequency[j][1] = 1;
        }
    }
}

void printFrequency() {
    for(int i = 0; i < MAX; i++) {
        if(frequency[i][0] != -1) {
            printf("%d occurs %d times\n", frequency[i][0], frequency[i][1]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 1, 1, 2, 2, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    findFrequency(arr, n);
    printFrequency();

    return 0;
}