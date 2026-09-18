#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 1024

typedef struct {
    long long key;
    long long value;
    int occupied;
} Entry;

typedef struct {
    Entry *entries;
    size_t capacity;
    size_t count;
} HashTable;

static size_t hash_key(long long key) {
    unsigned long long x = (unsigned long long)key;
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return (size_t)x;
}

static HashTable *table_create(size_t capacity) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (!table) return NULL;
    table->entries = (Entry *)calloc(capacity, sizeof(Entry));
    if (!table->entries) {
        free(table);
        return NULL;
    }
    table->capacity = capacity;
    table->count = 0;
    return table;
}

static void table_destroy(HashTable *table) {
    if (!table) return;
    free(table->entries);
    free(table);
}

static int resize_table(HashTable *table) {
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) return 0;
    Entry *new_entries = (Entry *)calloc(new_capacity, sizeof(Entry));
    if (!new_entries) return 0;
    Entry *old_entries = table->entries;
    size_t old_capacity = table->capacity;
    table->entries = new_entries;
    table->capacity = new_capacity;
    table->count = 0;
    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_entries[i].occupied) {
            size_t idx = hash_key(old_entries[i].key) & (new_capacity - 1);
            while (new_entries[idx].occupied) {
                idx = (idx + 1) & (new_capacity - 1);
            }
            new_entries[idx] = old_entries[i];
            table->count++;
        }
    }
    free(old_entries);
    return 1;
}

static int table_lookup(HashTable *table, long long key, long long *value) {
    size_t idx = hash_key(key) & (table->capacity - 1);
    while (table->entries[idx].occupied) {
        if (table->entries[idx].key == key) {
            *value = table->entries[idx].value;
            return 1;
        }
        idx = (idx + 1) & (table->capacity - 1);
    }
    return 0;
}

static int table_insert(HashTable *table, long long key, long long value) {
    if (table->count * 10 >= table->capacity * 7) {
        if (!resize_table(table)) return 0;
    }
    size_t idx = hash_key(key) & (table->capacity - 1);
    while (table->entries[idx].occupied) {
        if (table->entries[idx].key == key) {
            table->entries[idx].value = value;
            return 1;
        }
        idx = (idx + 1) & (table->capacity - 1);
    }
    table->entries[idx].occupied = 1;
    table->entries[idx].key = key;
    table->entries[idx].value = value;
    table->count++;
    return 1;
}

static long long max_sum(long long n, HashTable *table) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    long long cached;
    if (table_lookup(table, n, &cached)) return cached;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 5757701318346536355 + 3494343368814437927 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:169,execs:42,op:havoc,rep:12)
     * UBSan: signed integer overflow: 7450817597811000342 + 4501001037720840323 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1526,execs:258,op:havoc,rep:3)
     */
    long long sum = max_sum(n / 2, table) +
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: 5666382357009461871 + 3981334378540040463 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:13178,execs:1508,op:havoc,rep:3)
                     * UBSan: signed integer overflow: 8398291918862576268 + 2222080357473588128 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1526,execs:258,op:havoc,rep:3)
                     * UBSan: signed integer overflow: 8226523486358938340 + 5757701318346536355 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:169,execs:42,op:havoc,rep:12)
                     */
                    max_sum(n / 3, table) +
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: 8081784121119582512 + 1283111722703545350 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1526,execs:258,op:havoc,rep:3)
                     * UBSan: signed integer overflow: 8859266286050122341 + 1405200995841481409 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:169,execs:42,op:havoc,rep:12)
                     */
                    max_sum(n / 4, table) +
                    max_sum(n / 5, table);
    long long result = sum > n ? sum : n;
    (void)table_insert(table, n, result);
    return result;
}

int main(void) {
    HashTable *table = table_create(INITIAL_CAPACITY);
    if (!table) return 1;
    long long n;
    while (scanf("%lld", &n) == 1) {
        printf("%lld\n", max_sum(n, table));
    }
    table_destroy(table);
    return 0;
}