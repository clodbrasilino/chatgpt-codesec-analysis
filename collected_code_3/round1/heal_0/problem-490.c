#include <stdio.h>

typedef struct {
    int first;
    int second;
} Pair;

void extractSymmetricPairs(Pair arr[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i].first == arr[j].second && arr[i].second == arr[j].first) {
                printf("(%d, %d)\n", arr[i].first, arr[i].second);
            }
        }
    }
}

int main() {
    Pair arr[] = {{1, 2}, {3, 4}, {5, 6}, {4, 3}, {2, 1}, {6, 5}};
    int n = sizeof(arr)/sizeof(arr[0]);
    extractSymmetricPairs(arr, n);
    return 0;
}