#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int isSymmetric(const Pair a, const Pair b) {
    return (a.first == b.second && a.second == b.first);
}

Pair* extractSymmetricPairs(const Pair* pairs, int size, int* resultSize) {
    *resultSize = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (isSymmetric(pairs[i], pairs[j])) {
                (*resultSize)++;
                break;
            }
        }
    }

    if (*resultSize == 0) {
        return NULL;
    }

    Pair* symmetricPairs = (Pair*)malloc(*resultSize * sizeof(Pair));
    int index = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (isSymmetric(pairs[i], pairs[j])) {
                symmetricPairs[index++] = pairs[i];
                break;
            }
        }
    }
    return symmetricPairs;
}

int main() {
    const Pair pairs[] = {{1, 2}, {3, 4}, {2, 1}, {5, 6}, {6, 5}};
    int size = 5;
    int resultSize;

    Pair* symmetricPairs = extractSymmetricPairs(pairs, size, &resultSize);

    if (symmetricPairs != NULL) {
        for (int i = 0; i < resultSize; ++i) {
            printf("(%d, %d)\n", symmetricPairs[i].first, symmetricPairs[i].second);
        }
        free(symmetricPairs);
    } else {
        printf("No symmetric pairs found.\n");
    }

    return 0;
}