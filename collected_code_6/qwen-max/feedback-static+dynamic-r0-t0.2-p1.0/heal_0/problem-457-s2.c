#include <stdio.h>
#include <limits.h>

typedef struct {
    int start;
    int end;
} Sublist;

Sublist findMinLengthSublist(int arr[], int n) {
    if (n == 0) return (Sublist){-1, -1};

    int min_length = INT_MAX;
    Sublist result = {-1, -1};

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int length = j - i + 1;
            if (length < min_length) {
                min_length = length;
                result.start = i;
                result.end = j;
            }
        }
    }

    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    Sublist sublist = findMinLengthSublist(arr, n);

    if (sublist.start != -1 && sublist.end != -1) {
        printf("Minimum length sublist: from index %d to %d\n", sublist.start, sublist.end);
    } else {
        printf("No valid sublist found.\n");
    }

    return 0;
}