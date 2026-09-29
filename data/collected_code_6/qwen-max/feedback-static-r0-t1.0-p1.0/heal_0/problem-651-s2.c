#include <stdio.h>
#include <stdbool.h>

bool isSubset(int *subset, int subsetSize, int *superset, int supersetSize) {
    for (int i = 0; i < subsetSize; i++) {
        bool found = false;
        for (int j = 0; j < supersetSize; j++) {
            if (subset[i] == superset[j]) {
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
    int subset[] = {1, 2};
    int superset[] = {1, 2, 3, 4};
    int subsetSize = sizeof(subset) / sizeof(subset[0]);
    int supersetSize = sizeof(superset) / sizeof(superset[0]);

    if (isSubset(subset, subsetSize, superset, supersetSize)) {
        printf("Subset is a subset of Superset.\n");
    } else {
        printf("Subset is not a subset of Superset.\n");
    }

    return 0;
}