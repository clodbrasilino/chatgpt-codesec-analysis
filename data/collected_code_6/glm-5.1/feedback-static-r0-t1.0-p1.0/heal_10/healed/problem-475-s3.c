#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
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

void init_counter(Counter *c, const char *key, int value) {
    if (c == NULL || key == NULL) return;
    size_t key_len = strlen(key);
    if (key_len >= sizeof(c->key)) {
        memcpy(c->key, key, sizeof(c->key) - 1);
        c->key[sizeof(c->key) - 1] = '\0';
    } else {
        memcpy(c->key, key, key_len + 1);
    }
    c->value = value;
}

void sort_counters(Counter *counters, size_t count) {
    if (counters == NULL || count == 0) {
        return;
    }
    qsort(counters, count, sizeof(Counter), compare_counters);
}

int main(void) {
    Counter counters[4];
    
    init_counter(&counters[0], "apples", 5);
    init_counter(&counters[1], "oranges", 2);
    init_counter(&counters[2], "bananas", 8);
    init_counter(&counters[3], "pears", 1);
    
    size_t count = sizeof(counters) / sizeof(counters[0]);

    sort_counters(counters, count);

    for (size_t i = 0; i < count; i++) {
        printf("%31s: %d\n", counters[i].key, counters[i].value);
    }

    return 0;
}