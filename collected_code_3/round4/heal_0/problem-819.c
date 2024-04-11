#include <stdio.h>

void countDuplicates(int arr[], int n) {
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            count++;
        } else {
            printf("Element %d occurs %d times\n", arr[i - 1], count);
            count = 1;
        }
    }
    printf("Element %d occurs %d times\n", arr[n - 1], count);
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    countDuplicates(arr, n);
    return 0;
}