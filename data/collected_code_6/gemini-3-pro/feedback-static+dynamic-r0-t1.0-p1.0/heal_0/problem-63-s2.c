#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Tuple {
    int first;
    int second;
};

int find_max_difference(const struct Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return -1; 
    }

    int max_diff = -1;

    for (size_t i = 0; i < size; ++i) {
        int diff = abs(tuples[i].first - tuples[i].second);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }

    return max_diff;
}

int main(void) {
    struct Tuple tuples[] = {
        {10, 5},
        {20, 35},
        {8, 8},
        {100, 42}
    };
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    int max_difference = find_max_difference(tuples, size);

    if (max_difference != -1) {
        printf("Maximum difference: %d\n", max_difference);
    } else {
        printf("Invalid input or empty list.\n");
    }

    return 0;
}