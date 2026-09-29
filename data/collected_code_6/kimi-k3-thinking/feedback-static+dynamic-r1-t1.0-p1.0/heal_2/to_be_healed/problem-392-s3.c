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
    size_t size;
    int error;
} HashMap;

static unsigned long long hash_key(long long key)
{
    unsigned long long x = (unsigned long long)key;
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return x;
}

static int map_init(HashMap *map, size_t capacity)
{
    map->entries = calloc(capacity, sizeof(Entry));
    if (map->entries == NULL) {
        return -1;
    }
    map->capacity = capacity;
    map->size = 0;
    map->error = 0;
    return 0;
}

static void map_free(HashMap *map)
{
    free(map->entries);
    map->entries = NULL;
    map->capacity = 0;
    map->size = 0;
    map->error = 0;
}

static void map_insert(HashMap *map, long long key, long long value)
{
    size_t idx;

    if (map->error) {
        return;
    }

    if ((map->size + 1) * 10 >= map->capacity * 7) {
        size_t new_capacity = map->capacity * 2;
        Entry *new_entries = calloc(new_capacity, sizeof(Entry));
        if (new_entries == NULL) {
            map->error = 1;
            return;
        }
        for (size_t i = 0; i < map->capacity; i++) {
            if (map->entries[i].used) {
                idx = (size_t)(hash_key(map->entries[i].key) &
                               (unsigned long long)(new_capacity - 1));
                while (new_entries[idx].used) {
                    idx = (idx + 1) & (new_capacity - 1);
                }
                new_entries[idx] = map->entries[i];
            }
        }
        free(map->entries);
        map->entries = new_entries;
        map->capacity = new_capacity;
    }

    idx = (size_t)(hash_key(key) & (unsigned long long)(map->capacity - 1));
    while (map->entries[idx].used) {
        if (map->entries[idx].key == key) {
            map->entries[idx].value = value;
            return;
        }
        idx = (idx + 1) & (map->capacity - 1);
    }
    map->entries[idx].used = 1;
    map->entries[idx].key = key;
    map->entries[idx].value = value;
    map->size++;
}

static int map_get(const HashMap *map, long long key, long long *out)
{
    size_t idx = (size_t)(hash_key(key) & (unsigned long long)(map->capacity - 1));
    while (map->entries[idx].used) {
        if (map->entries[idx].key == key) {
            *out = map->entries[idx].value;
            return 1;
        }
        idx = (idx + 1) & (map->capacity - 1);
    }
    return 0;
}

long long max_sum(HashMap *map, long long n)
{
    long long cached = 0;
    long long sum;
    long long result;

    if (n <= 0) {
        return 0;
    }
    if (map_get(map, n, &cached)) {
        return cached;
    }

    sum = max_sum(map, n / 2)
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7450817597811000342 + 4501001037720840323 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1732,execs:588,op:havoc,rep:3)
         * UBSan: signed integer overflow: 5757701318346536355 + 3494343368814437927 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:122,execs:60,op:havoc,rep:3)
         */
        + max_sum(map, n / 3)
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8398291918862576268 + 2222080357473588128 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1732,execs:588,op:havoc,rep:3)
         * UBSan: signed integer overflow: 5666382357009461871 + 3981334378540040463 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:616,execs:230,op:havoc,rep:3)
         * UBSan: signed integer overflow: 8226523486358938340 + 5757701318346536355 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:122,execs:60,op:havoc,rep:3)
         */
        + max_sum(map, n / 4)
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8081784121119582512 + 1283111722703545350 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:616,execs:230,op:havoc,rep:3)
         * UBSan: signed integer overflow: 8859266286050122341 + 1405200995841481409 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:122,execs:60,op:havoc,rep:3)
         */
        + max_sum(map, n / 5);

    result = (sum > n) ? sum : n;
    map_insert(map, n, result);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000001,time:13829,execs:5122,op:havoc,rep:4; likely memory-safety defect
  */

int main(void)
{
    long long n;
    HashMap map;

    if (map_init(&map, 1024) != 0) {
        fprintf(stderr, "error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    while (scanf("%lld", &n) == 1) {
        long long answer;
        if (n < 0) {
            fprintf(stderr, "error: invalid input\n");
            map_free(&map);
            return EXIT_FAILURE;
        }
        answer = max_sum(&map, n);
        if (map.error) {
            fprintf(stderr, "error: memory allocation failed\n");
            map_free(&map);
            return EXIT_FAILURE;
        }
        printf("%lld\n", answer);
    }

    map_free(&map);
    return EXIT_SUCCESS;
}