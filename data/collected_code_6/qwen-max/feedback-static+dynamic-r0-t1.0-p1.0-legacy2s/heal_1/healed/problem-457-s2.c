#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int start;
    int end;
} Sublist;

Sublist findMinimumSublist(const int arr[], int n) {
    if (n <= 0) return (Sublist){-1, -1};

    int min_sum = INT_MAX;
    int current_sum = 0;
    int start = 0, end = 0, s = 0;

    for (int i = 0; i < n; ++i) {
        current_sum += arr[i];

        if (current_sum < min_sum) {
            min_sum = current_sum;
            start = s;
            end = i;
        }

        if (current_sum > 0) {
            current_sum = 0;
            s = i + 1;
        }
    }

    return (Sublist){start, end};
}

int main() {
    int arr[] = {2, 3, -5, 6, -7, 4, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Sublist result = findMinimumSublist(arr, n);
    if (result.start != -1 && result.end != -1) {
        printf("Sublist with minimum sum is from index %d to %d\n", result.start, result.end);
    } else {
        printf("No valid sublist found.\n");
    }

    return 0;
}