#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int comparePairs(const void *a, const void *b) {
    return ((Pair *)a)->first - ((Pair *)b)->first;
}

void extractSymmetricPairs(Pair *list, int n, Pair *result, int *resultSize) {
    qsort(list, n, sizeof(Pair), comparePairs);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (list[i].first == list[j].second && list[i].second == list[j].first) {
                result[*resultSize].first = list[i].first;
                result[*resultSize].second = list[i].second;
                (*resultSize)++;
            }
        }
    }
}

int main() {
    Pair list[] = {{1, 2}, {3, 4}, {2, 1}, {4, 3}, {5, 6}};
    int n = sizeof(list) / sizeof(list[0]);
    Pair result[n];
    int resultSize = 0;

    extractSymmetricPairs(list, n, result, &resultSize);

    for (int i = 0; i < resultSize; i++) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    return 0;
}