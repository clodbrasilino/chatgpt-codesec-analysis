#include <stdbool.h>
#include <stdio.h>

bool checkConsecutive(int arr[], int n) {
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }
    if (max - min + 1 == n) {
        bool visited[n];
        for (int i = 0; i < n; i++) {
            if (visited[arr[i] - min] != false)
                return false;
            visited[arr[i] - min] = true;
        }
        return true;
    }
    return false;
}

int main() {
    int arr[] = {5, 2, 3, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (checkConsecutive(arr, n) == true)
        printf("Array contains consecutive integers\n");
    else
        printf("Array doesn't contain consecutive integers\n");
    return 0;
}