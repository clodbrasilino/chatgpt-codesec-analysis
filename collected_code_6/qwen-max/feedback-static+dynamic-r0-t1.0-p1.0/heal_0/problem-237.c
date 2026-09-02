#include <stdio.h>
#include <stdlib.h>

struct Record {
    int key;
    int value;
};

int compare(const void *a, const void *b) {
    return ((struct Record *)a)->value - ((struct Record *)b)->value;
}

int countSimilarOccurrences(struct Record *records, int n) {
    if (n == 0) {
        return 0;
    }

    qsort(records, n, sizeof(struct Record), compare);

    int count = 1, maxCount = 1;

    for (int i = 1; i < n; ++i) {
        if (records[i].value == records[i - 1].value) {
            count++;
            if (count > maxCount) {
                maxCount = count;
            }
        } else {
            count = 1;
        }
    }

    return maxCount;
}

int main() {
    struct Record records[] = {{1, 2}, {2, 3}, {3, 2}, {4, 3}, {5, 2}};
    int n = sizeof(records) / sizeof(records[0]);

    int result = countSimilarOccurrences(records, n);
    printf("The maximum number of similar occurrences: %d\n", result);

    return 0;
}