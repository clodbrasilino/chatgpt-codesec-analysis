#include <stdio.h>
#include <stdlib.h>

typedef struct Pair {
    int first;
    int second;
} Pair;

int compare(const void *a, const void *b) {
    return (*(Pair*)a).second - (*(Pair*)b).second;
}

int findLongestChain(Pair *pairs, int n) {
    qsort(pairs, n, sizeof(Pair), compare);
    int maxChain = 1;
    int last = pairs[0].second;
    for (int i = 1; i < n; i++) {
        if (pairs[i].first > last) {
            last = pairs[i].second;
            maxChain++;
        }
    }
    return maxChain;
}

int main() {
    Pair pairs[] = {{5, 24}, {39, 60}, {5, 5}, {25, 30}, {3, 19}};
    int n = sizeof(pairs) / sizeof(pairs[0]);
    printf("%d\n", findLongestChain(pairs, n));
    return 0;
}