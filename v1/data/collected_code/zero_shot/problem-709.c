#include <stdio.h>

void countUniqueKeys(int tuple[], int size) {
    // Iterate through the tuple array
    for (int i = 0; i < size; i++) {
        int currentKey = tuple[i];
        int uniqueCount = 0;

        // Check if the key is already counted
        for (int j = 0; j < i; j++) {
            if (tuple[j] == currentKey) {
                uniqueCount++;
                break;
            }
        }

        // If the key is not yet counted, count its occurrences
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
    // Example tuple: (1, 2, 3, 1, 2, 1, 3)
    int tuple[] = {1, 2, 3, 1, 2, 1, 3};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    countUniqueKeys(tuple, size);

    return 0;
}