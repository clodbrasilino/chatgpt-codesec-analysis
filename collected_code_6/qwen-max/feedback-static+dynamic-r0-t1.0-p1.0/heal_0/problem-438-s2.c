#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int count_bidirectional_pairs(Tuple *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if ((arr[i].first == arr[j].second && arr[i].second == arr[j].first)) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    Tuple tuples[] = {{1, 2}, {2, 1}, {3, 4}, {4, 3}, {5, 6}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int result = count_bidirectional_pairs(tuples, n);
    printf("Number of bidirectional tuple pairs: %d\n", result);
    return 0;
}