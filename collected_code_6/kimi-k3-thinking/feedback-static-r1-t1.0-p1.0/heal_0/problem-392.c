#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

typedef struct {
    ull key;
    ull value;
    int used;
} Entry;

typedef struct {
    Entry *table;
    size_t capacity;
    size_t count;
} Map;

static size_t hash_key(ull key)
{
    key ^= key >> 33;
    key *= 0xff51afd7ed558ccdULL;
    key ^= key >> 33;
    key *= 0xc4ceb9fe1a85ec53ULL;
    key ^= key >> 33;
    return (size_t)key;
}

static int map_init(Map *m, size_t capacity)
{
    m->table = calloc(capacity, sizeof *m->table);
    if (m->table == NULL) {
        return -1;
    }
    m->capacity = capacity;
    m->count = 0;
    return 0;
}

static void map_free(Map *m)
{
    free(m->table);
    m->table = NULL;
    m->capacity = 0;
    m->count = 0;
}

static int map_grow(Map *m)
{
    size_t new_capacity = m->capacity * 2;
    Entry *new_table = calloc(new_capacity, sizeof *new_table);
    if (new_table == NULL) {
        return -1;
    }
    for (size_t i = 0; i < m->capacity; i++) {
        if (m->table[i].used) {
            size_t idx = hash_key(m->table[i].key) & (new_capacity - 1);
            while (new_table[idx].used) {
                idx = (idx + 1) & (new_capacity - 1);
            }
            new_table[idx] = m->table[i];
        }
    }
    free(m->table);
    m->table = new_table;
    m->capacity = new_capacity;
    return 0;
}

static int map_insert(Map *m, ull key, ull value)
{
    if ((m->count + 1) * 10 >= m->capacity * 7) {
        if (map_grow(m) != 0) {
            return -1;
        }
    }
    size_t idx = hash_key(key) & (m->capacity - 1);
    while (m->table[idx].used) {
        if (m->table[idx].key == key) {
            m->table[idx].value = value;
            return 0;
        }
        idx = (idx + 1) & (m->capacity - 1);
    }
    m->table[idx].used = 1;
    m->table[idx].key = key;
    m->table[idx].value = value;
    m->count++;
    return 0;
}

static int map_get(const Map *m, ull key, ull *out)
{
    size_t idx = hash_key(key) & (m->capacity - 1);
    while (m->table[idx].used) {
        if (m->table[idx].key == key) {
            *out = m->table[idx].value;
            return 1;
        }
        idx = (idx + 1) & (m->capacity - 1);
    }
    return 0;
}

static ull add_sat(ull a, ull b)
{
    if (ULLONG_MAX - a < b) {
        return ULLONG_MAX;
    }
    return a + b;
}

static ull max_sum(ull n, Map *memo)
{
    if (n == 0) {
        return 0;
    }
    ull cached = 0;
    if (map_get(memo, n, &cached)) {
        return cached;
    }
    ull sum = add_sat(max_sum(n / 2, memo),
              add_sat(max_sum(n / 3, memo),
              add_sat(max_sum(n / 4, memo),
                      max_sum(n / 5, memo))));
    ull best = (sum > n) ? sum : n;
    (void)map_insert(memo, n, best);
    return best;
}

int main(void)
{
    Map memo;
    if (map_init(&memo, 1024) != 0) {
        fprintf(stderr, "error: unable to allocate memory\n");
        return EXIT_FAILURE;
    }

    ull n = 0;
    printf("Enter n: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "error: unable to flush output\n");
        map_free(&memo);
        return EXIT_FAILURE;
    }
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "error: invalid input\n");
        map_free(&memo);
        return EXIT_FAILURE;
    }

    printf("f(%llu) = %llu\n", n, max_sum(n, &memo));
    map_free(&memo);
    return EXIT_SUCCESS;
}