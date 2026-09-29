#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 64U

typedef struct {
    char *key;
    int value;
} Counter;

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

static int set_counter(Counter *counter, const char *key, int value)
{
    size_t len;
    size_t alloc_size;
    char *copy;

    if (counter == NULL || key == NULL) {
        return -1;
    }

    len = strnlen(key, KEY_SIZE);
    if (len >= KEY_SIZE) {
        return -1;
    }

    alloc_size = len + 1U;
    copy = malloc(alloc_size);
    if (copy == NULL) {
        return -1;
    }

    if (len > 0U && len < alloc_size) {
        memcpy(copy, key, len);
    }
    copy[len] = '\0';

    counter->key = copy;
    counter->value = value;
    return 0;
}

static void free_counters(Counter *counters, size_t count)
{
    size_t i;

    if (counters == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        free(counters[i].key);
        counters[i].key = NULL;
    }
    free(counters);
}

int main(void)
{
    size_t count = 5U;
    size_t i;
    Counter *counters = calloc(count, sizeof(Counter));

    if (counters == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (set_counter(&counters[0], "apple", 3) != 0 ||
        set_counter(&counters[1], "banana", 7) != 0 ||
        set_counter(&counters[2], "cherry", 1) != 0 ||
        set_counter(&counters[3], "date", 7) != 0 ||
        set_counter(&counters[4], "elderberry", 5) != 0) {
        fprintf(stderr, "Failed to initialize counters\n");
        free_counters(counters, count);
        return EXIT_FAILURE;
    }

    if (sort_counter_by_value(counters, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_counters(counters, count);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("%s: %d\n", counters[i].key, counters[i].value) < 0) {
            fprintf(stderr, "Output failed\n");
            free_counters(counters, count);
            return EXIT_FAILURE;
        }
    }

    free_counters(counters, count);
    return EXIT_SUCCESS;
}