#include <stdio.h>
#include <stdbool.h>

bool isSubset(const int* superSet, int superSetSize, const int* subSet, int subSetSize) {
    for (int i = 0; i < subSetSize; ++i) {
        bool found = false;
        for (int j = 0; j < superSetSize; ++j) {
            if (subSet[i] == superSet[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    int superSet[] = {1, 2, 3, 4, 5};
    int subSet[] = {2, 3, 5};
    int superSetSize = sizeof(superSet) / sizeof(superSet[0]);
    int subSetSize = sizeof(subSet) / sizeof(subSet[0]);

    if (isSubset(superSet, superSetSize, subSet, subSetSize)) {
        printf("Array is a subset.\n");
    } else {
        printf("Array is not a subset.\n");
    }

    return 0;
}