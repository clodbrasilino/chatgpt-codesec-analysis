#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int isSymmetric(Pair a, Pair b) {
    return (a.first == b.second && a.second == b.first);
}

/* Possible weaknesses found:
 *  Parameter 'pairs' can be declared as pointer to const [constParameterPointer]
 */
Pair* extractSymmetricPairs(Pair* pairs, int size, int* resultSize) {
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
    Pair pairs[] = {{1, 2}, {3, 4}, {2, 1}, {5, 6}, {6, 5}};
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