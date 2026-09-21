#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LENGTH];
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

bool set_counter_name(Counter *counter, const char *name) {
    if (counter == NULL || name == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t name_len = strlen(name);
    if (name_len >= MAX_NAME_LENGTH) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(counter->name, name, MAX_NAME_LENGTH - 1);
    counter->name[MAX_NAME_LENGTH - 1] = '\0';
    return true;
}

int main(void) {
    Counter counters[4];
    
    if (!set_counter_name(&counters[0], "alpha") ||
        !set_counter_name(&counters[1], "beta") ||
        !set_counter_name(&counters[2], "gamma") ||
        !set_counter_name(&counters[3], "delta")) {
        fprintf(stderr, "Failed to set counter names\n");
        return EXIT_FAILURE;
    }
    
    counters[0].value = 42;
    counters[1].value = 17;
    counters[2].value = 99;
    counters[3].value = 5;
    
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