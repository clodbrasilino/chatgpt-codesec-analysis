#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Tuple {
    int first;
    int second;
};

int find_max_difference(const struct Tuple* tuples, size_t size, int* max_diff) {
    if (tuples == NULL || size == 0 || max_diff == NULL) {
        return -1;
    }

    *max_diff = -1;
    int max_found = -1;

    for (size_t i = 0; i < size; ++i) {
        int diff = tuples[i].first - tuples[i].second;
        if (diff < 0) {
            diff = -diff;
        }

        if (max_found == -1 || diff > max_found) {
            max_found = diff;
        }
    }

    *max_diff = max_found;
    return 0;
}

int main(void) {
    struct Tuple tuple_list[] = {
        {10, 5},
        {20, 35},
        {1, 100},
        {50, 50}
    };
    size_t size = sizeof(tuple_list) / sizeof(tuple_list[0]);
    int max_difference = 0;

    int status = find_max_difference(tuple_list, size, &max_difference);

    if (status == 0) {
        printf("Maximum difference: %d\n", max_difference);
    } else {
        printf("Error calculating maximum difference.\n");
    }

    return 0;
}