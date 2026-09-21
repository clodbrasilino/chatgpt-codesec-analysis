#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 64

typedef struct {
    char key[KEY_SIZE];
    int value;
} Counter;

static int copy_key(char dest[KEY_SIZE], const char *src) {
    size_t len;

    if (dest == NULL || src == NULL) {
        return -1;
    }

    len = strlen(src);
    if (len >= KEY_SIZE) {
        return -1;
    }

    memcpy(dest, src, len + 1);
    return 0;
}

int compare_counters(const void *a, const void *b) {
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;
    return (ca->value > cb->value) - (ca->value < cb->value);
}

int sort_counter_by_value(Counter *counters, size_t count) {
    if (counters == NULL || count == 0) {
        return -1;
    }
    qsort(counters, count, sizeof(Counter), compare_counters);
    return 0;
}

int main(void) {
    Counter counters[5];
    size_t count = sizeof(counters) / sizeof(counters[0]);

    if (copy_key(counters[0].key, "apple") != 0) return EXIT_FAILURE;
    counters[0].value = 5;

    if (copy_key(counters[1].key, "banana") != 0) return EXIT_FAILURE;
    counters[1].value = 2;

    if (copy_key(counters[2].key, "cherry") != 0) return EXIT_FAILURE;
    counters[2].value = 9;

    if (copy_key(counters[3].key, "date") != 0) return EXIT_FAILURE;
    counters[3].value = 1;

    if (copy_key(counters[4].key, "elderberry") != 0) return EXIT_FAILURE;
    counters[4].value = 7;

    if (sort_counter_by_value(counters, count) != 0) {
        fprintf(stderr, "Error: failed to sort counters\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", counters[i].key, counters[i].value);
    }

    return EXIT_SUCCESS;
}