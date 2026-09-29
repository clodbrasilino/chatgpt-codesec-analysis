#include <stdio.h>

typedef struct {
    int first;
    int second;
} Pair;

void findSymmetricPairs(Pair arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].first == arr[j].second && arr[i].second == arr[j].first) {
                printf("(%d, %d) and (%d, %d) are symmetric pairs\n", arr[i].first, arr[i].second, arr[j].first, arr[j].second);
            }
        }
    }
}

int main() {
    Pair arr[] = {{1, 3}, {3, 1}, {4, 6}, {6, 4}, {5, 9}, {9, 5}, {7, 8}};
    int n = sizeof(arr)/sizeof(arr[0]);
    findSymmetricPairs(arr, n);
    return 0;
}