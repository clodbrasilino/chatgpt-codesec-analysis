#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100003

struct Entry {
    unsigned long long key;
    unsigned long long value;
    struct Entry* next;
};

static struct Entry* table[TABLE_SIZE];

static unsigned long long hash_key(unsigned long long key) {
    return key % TABLE_SIZE;
}

static struct Entry* search(unsigned long long key) {
    unsigned long long h = hash_key(key);
    struct Entry* e = table[h];
    while (e != NULL) {
        if (e->key == key) {
            return e;
        }
        e = e->next;
    }
    return NULL;
}

static int insert(unsigned long long key, unsigned long long value) {
    unsigned long long h = hash_key(key);
    struct Entry* e = (struct Entry*)malloc(sizeof(struct Entry));
    if (e == NULL) {
        return -1;
    }
    e->key = key;
    e->value = value;
    e->next = table[h];
    table[h] = e;
    return 0;
}

static void free_table(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Entry* e = table[i];
        while (e != NULL) {
            struct Entry* next = e->next;
            free(e);
            e = next;
        }
        table[i] = NULL;
    }
}

unsigned long long f(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    struct Entry* e = search(n);
    if (e != NULL) {
        return e->value;
    }
    unsigned long long sum = f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5);
    unsigned long long result = n > sum ? n : sum;
    if (insert(n, result) != 0) {
        exit(1);
    }
    return result;
}

int main(void) {
    unsigned long long n;
    if (scanf("%llu", &n) == 1) {
        printf("%llu\n", f(n));
    }
    free_table();
    return 0;
}