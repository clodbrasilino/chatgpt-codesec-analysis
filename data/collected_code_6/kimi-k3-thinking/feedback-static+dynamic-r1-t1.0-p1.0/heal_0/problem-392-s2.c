#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long key;
    long long value;
    int used;
} Entry;

typedef struct {
    Entry *entries;
    size_t capacity;
    size_t count;
} HashMap;

static size_t hash_key(long long key, size_t capacity)
{
    unsigned long long x = (unsigned long long)key;
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return (size_t)(x % capacity);
}

static int hashmap_init(HashMap *map, size_t capacity)
{
    if (map == NULL || capacity == 0) {
        return 0;
    }
    map->entries = calloc(capacity, sizeof(Entry));
    if (map->entries == NULL) {
        return 0;
    }
    map->capacity = capacity;
    map->count = 0;
    return 1;
}

static void hashmap_free(HashMap *map)
{
    if (map != NULL) {
        free(map->entries);
        map->entries = NULL;
        map->capacity = 0;
        map->count = 0;
    }
}

static int hashmap_resize(HashMap *map)
{
    size_t new_capacity = map->capacity * 2;
    Entry *new_entries = calloc(new_capacity, sizeof(Entry));
    if (new_entries == NULL) {
        return 0;
    }
    for (size_t i = 0; i < map->capacity; i++) {
        if (map->entries[i].used) {
            size_t idx = hash_key(map->entries[i].key, new_capacity);
            while (new_entries[idx].used) {
                idx = (idx + 1) % new_capacity;
            }
            new_entries[idx] = map->entries[i];
        }
    }
    free(map->entries);
    map->entries = new_entries;
    map->capacity = new_capacity;
    return 1;
}

static int hashmap_put(HashMap *map, long long key, long long value)
{
    if (map->count * 10 >= map->capacity * 7) {
        if (!hashmap_resize(map)) {
            return 0;
        }
    }
    size_t idx = hash_key(key, map->capacity);
    while (map->entries[idx].used) {
        if (map->entries[idx].key == key) {
            map->entries[idx].value = value;
            return 1;
        }
        idx = (idx + 1) % map->capacity;
    }
    map->entries[idx].used = 1;
    map->entries[idx].key = key;
    map->entries[idx].value = value;
    map->count++;
    return 1;
}

static int hashmap_get(const HashMap *map, long long key, long long *value)
{
    if (map == NULL || value == NULL || map->capacity == 0) {
        return 0;
    }
    size_t idx = hash_key(key, map->capacity);
    size_t start = idx;
    while (map->entries[idx].used) {
        if (map->entries[idx].key == key) {
            *value = map->entries[idx].value;
            return 1;
        }
        idx = (idx + 1) % map->capacity;
        if (idx == start) {
            break;
        }
    }
    return 0;
}

static long long max_sum(long long n, HashMap *memo)
{
    if (n <= 0) {
        return 0;
    }
    long long cached = 0;
    if (hashmap_get(memo, n, &cached)) {
        return cached;
    }
    long long sum = max_sum(n / 2, memo)
                  + max_sum(n / 3, memo)
                  + max_sum(n / 4, memo)
                  + max_sum(n / 5, memo);
    long long result = (sum > n) ? sum : n;
    (void)hashmap_put(memo, n, result);
    return result;
}

int main(void)
{
    long long n = 0;
    printf("Enter a non-negative integer: ");
    if (scanf("%lld", &n) != 1 || n < 0) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    HashMap memo;
    if (!hashmap_init(&memo, 1024)) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    long long result = max_sum(n, &memo);
    printf("f(%lld) = %lld\n", n, result);

    hashmap_free(&memo);
    return EXIT_SUCCESS;
}