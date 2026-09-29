#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_common_first(Tuple *tuples, int count) {
    if (tuples == NULL || count <= 0) {
        return -1;
    }

    int candidate = tuples[0].first;
    for (int i = 1; i < count; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (tuples[j].first == candidate && tuples[j].second == tuples[i].second) {
                found++;
            }
        }
        if (found == 0) {
            return -1;
        }
    }
    return candidate;
}

int main() {
    Tuple tuples[] = {
        {1, 10},
        {1, 20},
        {1, 30},
        {2, 40},
        {1, 50}
    };
    int count = sizeof(tuples) / sizeof(tuples[0]);
    int result = find_common_first(tuples, count);
    printf("Common first: %d\n", result);

    Tuple tuples2[] = {
        {1, 10},
        {2, 20},
        {3, 30}
    };
    count = sizeof(tuples2) / sizeof(tuples2[0]);
    result = find_common_first(tuples2, count);
    printf("Common first: %d\n", result);

    Tuple tuples3[] = {
        {5, 10},
        {5, 20}
    };
    count = sizeof(tuples3) / sizeof(tuples3[0]);
    result = find_common_first(tuples3, count);
    printf("Common first: %d\n", result);

    return 0;
}