#include <stdio.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int find_max_length_sublist(int *arr, int n) {
    if (n <= 0) return 0;

    int max_length = 1;
    int current_length = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            current_length++;
            max_length = MAX(max_length, current_length);
        } else {
            current_length = 1;
        }
    }

    return max_length;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_length = find_max_length_sublist(arr, n);
    printf("Maximum length of increasing sublist: %d\n", max_length);
    return 0;
}