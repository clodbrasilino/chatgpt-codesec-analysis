#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

typedef struct {
    long long first;
    long long second;
} Tuple;

int find_min_difference(const Tuple *tuples, size_t count, unsigned long long *min_diff) {
    if (tuples == NULL || min_diff == NULL || count == 0) {
        return -1;
    }

    unsigned long long current_min = ULLONG_MAX;

    for (size_t i = 0; i < count; ++i) {
        unsigned long long diff;
        
        if (tuples[i].first > tuples[i].second) {
            diff = (unsigned long long)tuples[i].first - (unsigned long long)tuples[i].second;
        } else {
            diff = (unsigned long long)tuples[i].second - (unsigned long long)tuples[i].first;
        }

        if (diff < current_min) {
            current_min = diff;
        }
    }

    *min_diff = current_min;
    
    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {10LL, 25LL},
        {30LL, 28LL},
        {15LL, 15LL},
        {50LL, 60LL},
        {LLONG_MAX, -LLONG_MAX}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    unsigned long long min_diff = 0;

    if (find_min_difference(tuples, count, &min_diff) == 0) {
        printf("%llu\n", min_diff);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}