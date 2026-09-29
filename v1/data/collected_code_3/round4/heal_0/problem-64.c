#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int compare(const void* a, const void* b) {
    Pair* pairA = (Pair*) a;
    Pair* pairB = (Pair*) b;
    if (pairA->first != pairB->first)
        return pairA->first - pairB->first;
    else
        return pairA->second - pairB->second;
}

void sortPairs(Pair* pairs, size_t count) {
    qsort(pairs, count, sizeof(Pair), compare);
}

int main() {
    Pair pairs[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    size_t count = sizeof(pairs) / sizeof(Pair);

    sortPairs(pairs, count);

    for (size_t i = 0; i < count; ++i) {
        printf("(%d, %d)\n", pairs[i].first, pairs[i].second);
    }

    return 0;
}