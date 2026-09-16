#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000003

typedef struct {
    unsigned long long key;
    unsigned long long val;
    int used;
} Entry;

Entry *table;

void init_table(void) {
    table = (Entry *)calloc(SIZE, sizeof(Entry));
    if (!table) {
        exit(EXIT_FAILURE);
    }
}

unsigned long long hash(unsigned long long key) {
    return key % SIZE;
}

void insert(unsigned long long key, unsigned long long val) {
    unsigned long long idx = hash(key);
    unsigned long long start_idx = idx;
    while (table[idx].used) {
        if (table[idx].key == key) {
            table[idx].val = val;
            return;
        }
        idx = (idx + 1) % SIZE;
        if (idx == start_idx) {
            exit(EXIT_FAILURE);
        }
    }
    table[idx].key = key;
    table[idx].val = val;
    table[idx].used = 1;
}

int search(unsigned long long key, unsigned long long *val) {
    unsigned long long idx = hash(key);
    unsigned long long start_idx = idx;
    while (table[idx].used) {
        if (table[idx].key == key) {
            *val = table[idx].val;
            return 1;
        }
        idx = (idx + 1) % SIZE;
        if (idx == start_idx) {
            return 0;
        }
    }
    return 0;
}

unsigned long long f(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    unsigned long long cached_val;
    if (search(n, &cached_val)) {
        return cached_val;
    }
    unsigned long long sum = f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5);
    unsigned long long result = n > sum ? n : sum;
    insert(n, result);
    return result;
}

int main(void) {
    init_table();
    unsigned long long n;
    if (scanf("%llu", &n) == 1) {
        printf("%llu\n", f(n));
    }
    free(table);
    return 0;
}