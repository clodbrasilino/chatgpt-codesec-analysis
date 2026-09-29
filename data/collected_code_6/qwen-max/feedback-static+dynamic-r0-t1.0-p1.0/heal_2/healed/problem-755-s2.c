#include <stdio.h>
#include <limits.h>

int find_second_smallest(const int arr[], int n) {
    int smallest = INT_MAX, second_smallest = INT_MAX;
    int found_smallest = 0, found_second_smallest = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
            found_smallest = 1;
            found_second_smallest = found_smallest && (second_smallest != INT_MAX);
        } else if (arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
            found_second_smallest = 1;
        }
    }

    if (!found_second_smallest) {
        return -2;
    }

    return second_smallest;
}

int main() {
    const int arr[] = {4, 2, 1, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = find_second_smallest(arr, n);
    if (result == -2) {
        printf("No second smallest element found.\n");
    } else {
        printf("Second smallest element is: %d\n", result);
    }
    return 0;
}