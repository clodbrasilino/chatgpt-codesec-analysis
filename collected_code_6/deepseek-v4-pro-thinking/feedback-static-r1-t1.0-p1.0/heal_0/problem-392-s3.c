#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    long long key;
    long long value;
    int used;
} Entry;

typedef struct {
    Entry *entries;
    size_t capacity;
    size_t size;
} Table;

static size_t hash_key(long long key) {
    unsigned long long x = (unsigned long long)key;
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return (size_t)x;
}

static Table *table_create(size_t capacity) {
    Table *t = malloc(sizeof(*t));
    if (t == NULL) {
        return NULL;
    }
    t->entries = calloc(capacity, sizeof(*t->entries));
    if (t->entries == NULL) {
        free(t);
        return NULL;
    }
    t->capacity = capacity;
    t->size = 0;
    return t;
}

static void table_free(Table *t) {
    if (t != NULL) {
        free(t->entries);
        free(t);
    }
}

static long long *table_get(Table *t, long long key) {
    size_t i = hash_key(key) % t->capacity;
    while (t->entries[i].used) {
        if (t->entries[i].key == key) {
            return &t->entries[i].value;
        }
        i = (i + 1) % t->capacity;
    }
    return NULL;
}

static int table_resize(Table *t) {
    if (t->capacity > (size_t)-1 / 2) {
        return -1;
    }
    size_t new_capacity = t->capacity * 2;
    Entry *new_entries = calloc(new_capacity, sizeof(*new_entries));
    if (new_entries == NULL) {
        return -1;
    }
    for (size_t i = 0; i < t->capacity; ++i) {
        if (t->entries[i].used) {
            size_t j = hash_key(t->entries[i].key) % new_capacity;
            while (new_entries[j].used) {
                j = (j + 1) % new_capacity;
            }
            new_entries[j] = t->entries[i];
        }
    }
    free(t->entries);
    t->entries = new_entries;
    t->capacity = new_capacity;
    return 0;
}

static int table_put(Table *t, long long key, long long value) {
    if ((t->size + 1) * 10 >= t->capacity * 7) {
        if (table_resize(t) != 0) {
            return -1;
        }
    }
    size_t i = hash_key(key) % t->capacity;
    while (t->entries[i].used) {
        if (t->entries[i].key == key) {
            t->entries[i].value = value;
            return 0;
        }
        i = (i + 1) % t->capacity;
    }
    t->entries[i].key = key;
    t->entries[i].value = value;
    t->entries[i].used = 1;
    ++t->size;
    return 0;
}

static long long f(long long n, Table *memo) {
    if (n <= 1) {
        return n;
    }
    long long *cached = table_get(memo, n);
    if (cached != NULL) {
        return *cached;
    }
    long long sum = f(n / 2, memo) + f(n / 3, memo) + f(n / 4, memo) + f(n / 5, memo);
    long long result = sum > n ? sum : n;
    if (table_put(memo, n, result) != 0) {
        return result;
    }
    return result;
}

int main(void) {
    Table *memo = table_create(1024);
    if (memo == NULL) {
        return 1;
    }
    long long n;
    while (scanf("%lld", &n) == 1) {
        printf("%lld\n", f(n, memo));
    }
    table_free(memo);
    return 0;
}