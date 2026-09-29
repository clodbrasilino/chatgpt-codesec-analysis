#include <stdio.h>

void findPairs(int arr[], int arrSize, int sum) {
    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[i] + arr[j] == sum) {
                printf("Pair found: %d + %d = %d\n", arr[i], arr[j], sum);
            }
        }
    }
}

int main() {
    int arr[] = {1, 5, 2, -1, 6, 3, 7};
    int sum = 6;
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    findPairs(arr, arrSize, sum);

    return 0;
}