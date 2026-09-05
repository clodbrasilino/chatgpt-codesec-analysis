#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

void findSymmetricPairs(const Pair *pairs, size_t size) {
    size_t i;
    size_t j;
    int found = 0;

    if (pairs == NULL || size == 0) {
        printf("No symmetric pairs found.\n");
        return;
    }

    printf("Symmetric pairs:\n");
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first) {
                printf("(%d, %d) and (%d, %d)\n",
                       pairs[i].first, pairs[i].second,
                       pairs[j].first, pairs[j].second);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No symmetric pairs found.\n");
    }
}

int main(void) {
    Pair pairs[] = {
        {1, 2},
        {3, 4},
        {2, 1},
        {5, 6},
        {4, 3},
        {7, 8}
    };
    size_t size = sizeof(pairs) / sizeof(pairs[0]);

    findSymmetricPairs(pairs, size);

    return 0;
}