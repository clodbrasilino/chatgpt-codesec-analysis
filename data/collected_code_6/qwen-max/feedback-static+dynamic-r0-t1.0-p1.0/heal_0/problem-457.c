#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int start;
    int end;
} Sublist;

Sublist find_min_length_sublist(int *arr, int n) {
    if (n == 0) return (Sublist){-1, -1};

    int min_length = INT_MAX;
    Sublist result = {-1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int length = j - i;
            if (length < min_length) {
                min_length = length;
                result.start = i;
                result.end = j - 1;
            }
        }
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    Sublist min_sublist = find_min_length_sublist(arr, n);
    if (min_sublist.start != -1 && min_sublist.end != -1) {
        printf("Minimum length sublist: start=%d, end=%d\n", min_sublist.start, min_sublist.end);
    } else {
        printf("Empty list.\n");
    }

    return 0;
}