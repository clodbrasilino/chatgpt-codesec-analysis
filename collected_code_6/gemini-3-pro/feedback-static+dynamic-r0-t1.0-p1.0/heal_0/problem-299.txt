#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char *key;
    int value;
} Tuple;

typedef struct {
    char *key;
    long long total;
} Aggregate;

int calculate_max_aggregate(const Tuple *tuples, size_t length, long long *max_aggregate) {
    if (tuples == NULL || length == 0 || max_aggregate == NULL) {
        return -1;
    }

    Aggregate *aggs = (Aggregate *)malloc(length * sizeof(Aggregate));
    if (aggs == NULL) {
        return -1;
    }

    size_t num_aggs = 0;

    for (size_t i = 0; i < length; ++i) {
        if (tuples[i].key == NULL) {
            free(aggs);
            return -1;
        }

        int found = 0;
        for (size_t j = 0; j < num_aggs; ++j) {
            if (strcmp(tuples[i].key, aggs[j].key) == 0) {
                aggs[j].total += tuples[i].value;
                found = 1;
                break;
            }
        }

        if (!found) {
            aggs[num_aggs].key = tuples[i].key;
            aggs[num_aggs].total = tuples[i].value;
            num_aggs++;
        }
    }

    long long current_max = LLONG_MIN;
    for (size_t i = 0; i < num_aggs; ++i) {
        if (aggs[i].total > current_max) {
            current_max = aggs[i].total;
        }
    }

    *max_aggregate = current_max;
    free(aggs);

    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {"A", 10},
        {"B", 20},
        {"A", 50},
        {"C", 100},
        {"B", -5}
    };
    
    size_t length = sizeof(tuples) / sizeof(tuples[0]);
    long long max_val = 0;

    if (calculate_max_aggregate(tuples, length, &max_val) == 0) {
        printf("%lld\n", max_val);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}