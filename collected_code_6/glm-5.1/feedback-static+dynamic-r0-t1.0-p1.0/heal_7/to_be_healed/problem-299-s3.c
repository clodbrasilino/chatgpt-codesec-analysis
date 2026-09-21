#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_SIZE];
    int value;
} Tuple;

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_SIZE];
    long long aggregate;
} Aggregate;

long long calculate_max_aggregate(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return 0;
    }

    Aggregate *aggregates = (Aggregate *)malloc(count * sizeof(Aggregate));
    if (aggregates == NULL) {
        return 0;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < count; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (strncmp(aggregates[j].key, tuples[i].key, KEY_SIZE) == 0) {
                aggregates[j].aggregate += tuples[i].value;
                found = 1;
                break;
            }
        }
        if (!found) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(aggregates[unique_count].key, tuples[i].key, KEY_SIZE - 1);
            aggregates[unique_count].key[KEY_SIZE - 1] = '\0';
            aggregates[unique_count].aggregate = tuples[i].value;
            unique_count++;
        }
    }

    long long max_aggregate = 0;
    int has_valid_aggregate = 0;

    for (size_t i = 0; i < unique_count; i++) {
        if (!has_valid_aggregate || aggregates[i].aggregate > max_aggregate) {
            max_aggregate = aggregates[i].aggregate;
            has_valid_aggregate = 1;
        }
    }

    free(aggregates);
    return max_aggregate;
}

int main(void) {
    Tuple tuples[] = {
        {"A", 10},
        {"B", 20},
        {"A", 15},
        {"C", 5},
        {"B", 10},
        {"C", 25}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    long long max_aggregate = calculate_max_aggregate(tuples, count);

    printf("%lld\n", max_aggregate);

    return 0;
}