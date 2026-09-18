#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int first;
    int second;
};

int find_minimum_difference(const struct Tuple *tuples, size_t count, unsigned long long *min_diff) {
    unsigned long long current_min;
    size_t i;

    if (tuples == NULL || min_diff == NULL || count == 0) {
        return -1;
    }

    current_min = (unsigned long long)-1;

    for (i = 0; i < count; ++i) {
        long long diff = (long long)tuples[i].first - (long long)tuples[i].second;
        unsigned long long abs_diff = diff >= 0 ? (unsigned long long)diff : (unsigned long long)(-diff);
        
        if (abs_diff < current_min) {
            current_min = abs_diff;
        }
    }

    *min_diff = current_min;
    return 0;
}

int main(void) {
    struct Tuple pairs[] = {
        {10, 20},
        {5, 2},
        {-10, 10},
        {100, 99}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    unsigned long long min_diff = 0;

    if (find_minimum_difference(pairs, count, &min_diff) == 0) {
        if (printf("%llu\n", min_diff) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}