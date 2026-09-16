#include <stdio.h>
#include <stdlib.h>

struct ElementCount {
    int value;
    int count;
};

int findMaxOccurrence(const int *arr, size_t size, int *result) {
    if (arr == NULL || size == 0 || result == NULL) {
        return -1;
    }

    struct ElementCount *counts = (struct ElementCount *)malloc(size * sizeof(struct ElementCount));
    if (counts == NULL) {
        return -1;
    }

    size_t uniqueCount = 0;
    for (size_t i = 0; i < size; ++i) {
        int found = 0;
        for (size_t j = 0; j < uniqueCount; ++j) {
            if (counts[j].value == arr[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[uniqueCount].value = arr[i];
            counts[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    int maxCount = 0;
    int maxValue = arr[0];

    for (size_t i = 0; i < uniqueCount; ++i) {
        if (counts[i].count > maxCount) {
            maxCount = counts[i].count;
            maxValue = counts[i].value;
        }
    }

    *result = maxValue;
    free(counts);

    return 0;
}

int main(void) {
    int list[] = {1, 3, 2, 3, 4, 1, 3, 5, 3, 2};
    size_t size = sizeof(list) / sizeof(list[0]);
    int maxOccurringItem;

    if (findMaxOccurrence(list, size, &maxOccurringItem) == 0) {
        printf("Item with maximum occurrences: %d\n", maxOccurringItem);
    } else {
        printf("Failed to find maximum occurrence.\n");
    }

    return 0;
}