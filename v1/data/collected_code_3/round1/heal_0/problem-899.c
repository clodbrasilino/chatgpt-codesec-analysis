#include <stdio.h>
#include <stdbool.h>

bool checkSort(int arr[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (i != 0 && i != n - 2)
                return false;
            if (i == 0 && arr[i] > arr[i + 1] && arr[i] > arr[n - 1])
                return false;
            if (i == n - 2 && arr[i] > arr[i + 1] && arr[0] > arr[i + 1])
                return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (checkSort(arr, n))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}