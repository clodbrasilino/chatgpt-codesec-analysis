#include <stdio.h>

void countUniqueKeys(const int tuple[], const int size) {
    for (int i = 0; i < size; i++) {
        int currentKey = tuple[i];
        int uniqueCount = 0;

        for (int j = 0; j < i; j++) {
            if (tuple[j] == currentKey) {
                uniqueCount++;
                break;
            }
        }

        if (uniqueCount == 0) {
            int count = 1;
            for (int k = i + 1; k < size; k++) {
                if (tuple[k] == currentKey) {
                    count++;
                }
            }
            printf("Key %d: %d occurrence(s)\n", currentKey, count);
        }
    }
}

int main() {
    int tuple[] = {1, 2, 3, 1, 2, 1, 3};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    countUniqueKeys(tuple, size);

    return 0;
}
