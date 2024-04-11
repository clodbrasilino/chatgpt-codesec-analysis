#include <stdio.h>

int count_occurrences(int arr[], int n, int x) {
    int count = 0;
    for (int i=0; i<n; i++)
        if (arr[i] == x)
            count++;
    return count;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    int x = 2;
    printf("%d occurs %d times\n", x, count_occurrences(arr, n, x));
    return 0;
}