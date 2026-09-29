#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[32];
    int value;
} Counter;

int compare_counters(const void *a, const void *b) {
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;
    if (ca->value < cb->value) return -1;
    if (ca->value > cb->value) return 1;
    return 0;
}

void sort_counters(Counter *counters, size_t count) {
    if (counters == NULL || count == 0) {
        return;
    }
    qsort(counters, count, sizeof(Counter), compare_counters);
}

Counter create_counter(const char *key, int value) {
    Counter c;
    c.value = value;
    if (key == NULL) {
        c.key[0] = '\0';
        return c;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(key);
    if (len >= sizeof(c.key)) {
        len = sizeof(c.key) - 1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(c.key, key, len);
    c.key[len] = '\0';
    return c;
}

int main(void) {
    Counter counters[4];
    counters[0] = create_counter("apples", 5);
    counters[1] = create_counter("oranges", 2);
    counters[2] = create_counter("bananas", 8);
    counters[3] = create_counter("pears", 1);
    
    size_t count = sizeof(counters) / sizeof(counters[0]);

    sort_counters(counters, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", counters[i].key, counters[i].value);
    }

    return 0;
}