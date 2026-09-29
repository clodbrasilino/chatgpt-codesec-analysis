#include <stdio.h>
#include <limits.h>

typedef struct {
    int start;
    int end;
} Sublist;

Sublist findMinLengthSublist(int arr[], int n) {
    Sublist minSublist = {0, 0};
    int minLength = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (j - i + 1 < minLength) {
                minLength = j - i + 1;
                minSublist.start = i;
                minSublist.end = j;
            }
        }
    }
    return minSublist;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    Sublist result = findMinLengthSublist(arr, n);
    printf("Minimum length sublist: Start index = %d, End index = %d\n", result.start, result.end);
    return 0;
}