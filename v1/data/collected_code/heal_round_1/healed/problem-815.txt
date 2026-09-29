#include <stdio.h>

void sortArray(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int count[3] = {0};

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0 || arr[i] > 2) {
            return;
        }
        count[arr[i]]++;
    }

    int index = 0;

    for (int i = 0; i < 3; i++) {
        while (count[i] > 0) {
            arr[index++] = i; 
            count[i]--;
        }
    }
}

int main() {
    int arr[] = {0, 1, 2, 0, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortArray(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}