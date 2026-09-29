#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[64];
    int value;
} Counter;

int compare_by_value(const void *a, const void *b) {
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;
    
    if (ca->value < cb->value) return -1;
    if (ca->value > cb->value) return 1;
    return 0;
}

int sort_counter_by_value(Counter *counters, size_t count) {
    if (counters == NULL || count == 0) {
        return -1;
    }
    qsort(counters, count, sizeof(Counter), compare_by_value);
    return 0;
}

int main(void) {
    Counter counters[] = {
        {"alpha", 42},
        {"beta", 17},
        {"gamma", 99},
        {"delta", 5}
    };
    size_t count = sizeof(counters) / sizeof(counters[0]);
    
    if (sort_counter_by_value(counters, count) != 0) {
        fprintf(stderr, "Failed to sort counters\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", counters[i].name, counters[i].value);
    }
    
    return EXIT_SUCCESS;
}