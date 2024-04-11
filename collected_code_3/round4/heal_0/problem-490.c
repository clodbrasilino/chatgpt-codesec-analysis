#include <stdio.h>

typedef struct {
    int first;
    int second;
} Pair;

void findSymmetricPairs(Pair arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].first == arr[j].second && arr[i].second == arr[j].first) {
                printf("(%d, %d)\n", arr[i].first, arr[i].second);
            }
        }
    }
}

int main() {
    Pair arr[] = { {1, 2}, {3, 4}, {5, 6}, {4, 3}, {2, 1} };
    int n = sizeof(arr) / sizeof(arr[0]);
    findSymmetricPairs(arr, n);
    return 0;
}