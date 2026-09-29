#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_SIZE];
    int value;
} Counter;

static size_t bounded_length(const char *source, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && source[len] != '\0') {
        len++;
    }
    return len;
}

static int safe_set_key(Counter *counter, const char *source)
{
    size_t len;
    size_t i;

    if (counter == NULL || source == NULL) {
        return -1;
    }

    len = bounded_length(source, sizeof(counter->key));
    if (len >= sizeof(counter->key)) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        counter->key[i] = source[i];
    }
    counter->key[len] = '\0';
    return 0;
}

static int compare_by_value(const void *a, const void *b)
{
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;

    if (ca->value < cb->value) {
        return 1;
    }
    if (ca->value > cb->value) {
        return -1;
    }
    return strcmp(ca->key, cb->key);
}

static int sort_counter_by_value(Counter *counters, size_t count)
{
    if (counters == NULL || count == 0U) {
        return -1;
    }
    qsort(counters, count, sizeof(Counter), compare_by_value);
    return 0;
}

int main(void)
{
    static const char *keys[] = { "apple", "banana", "cherry", "date", "elderberry" };
    static const int values[] = { 3, 7, 1, 7, 5 };
    size_t count = sizeof(keys) / sizeof(keys[0]);
    size_t i;
    Counter *counters = calloc(count, sizeof(Counter));

    if (counters == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (safe_set_key(&counters[i], keys[i]) != 0) {
            fprintf(stderr, "Key assignment failed\n");
            free(counters);
            return EXIT_FAILURE;
        }
        counters[i].value = values[i];
    }

    if (sort_counter_by_value(counters, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free(counters);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("%s: %d\n", counters[i].key, counters[i].value) < 0) {
            fprintf(stderr, "Output failed\n");
            free(counters);
            return EXIT_FAILURE;
        }
    }

    free(counters);
    return EXIT_SUCCESS;
}