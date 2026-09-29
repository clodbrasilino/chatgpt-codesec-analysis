#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 256

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[TABLE_SIZE];
} Dict;

unsigned int hash(const char *key) {
    unsigned int h = 0;
    while (*key) {
        h = (h * 31 + (unsigned char)*key) % TABLE_SIZE;
        key++;
    }
    return h;
}

Dict *dict_create(void) {
    Dict *d = malloc(sizeof(Dict));
    if (!d) return NULL;
    memset(d->buckets, 0, sizeof(d->buckets));
    return d;
}

void dict_destroy(Dict *d) {
    if (!d) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *e = d->buckets[i];
        while (e) {
            Entry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(d);
}

int dict_set(Dict *d, const char *key, int value) {
    if (!d || !key) return -1;
    unsigned int idx = hash(key);
    Entry *e = d->buckets[idx];
    while (e) {
        if (strcmp(e->key, key) == 0) {
            e->value = value;
            return 0;
        }
        e = e->next;
    }
    Entry *new_entry = malloc(sizeof(Entry));
    if (!new_entry) return -1;
    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        return -1;
    }
    new_entry->value = value;
    new_entry->next = d->buckets[idx];
    d->buckets[idx] = new_entry;
    return 0;
}

int dict_get(Dict *d, const char *key, int *out_value) {
    if (!d || !key || !out_value) return -1;
    unsigned int idx = hash(key);
    Entry *e = d->buckets[idx];
    while (e) {
        if (strcmp(e->key, key) == 0) {
            *out_value = e->value;
            return 0;
        }
        e = e->next;
    }
    return -1;
}

Dict *dict_combine(Dict *d1, Dict *d2) {
    if (!d1 || !d2) return NULL;
    Dict *result = dict_create();
    if (!result) return NULL;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *e = d1->buckets[i];
        while (e) {
            if (dict_set(result, e->key, e->value) != 0) {
                dict_destroy(result);
                return NULL;
            }
            e = e->next;
        }
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *e = d2->buckets[i];
        while (e) {
            int existing;
            if (dict_get(result, e->key, &existing) == 0) {
                if (dict_set(result, e->key, existing + e->value) != 0) {
                    dict_destroy(result);
                    return NULL;
                }
            } else {
                if (dict_set(result, e->key, e->value) != 0) {
                    dict_destroy(result);
                    return NULL;
                }
            }
            e = e->next;
        }
    }
    return result;
}

void dict_print(Dict *d) {
    if (!d) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *e = d->buckets[i];
        while (e) {
            printf("%s: %d\n", e->key, e->value);
            e = e->next;
        }
    }
}

int main(void) {
    Dict *d1 = dict_create();
    if (!d1) return 1;
    Dict *d2 = dict_create();
    if (!d2) { dict_destroy(d1); return 1; }

    dict_set(d1, "apple", 3);
    dict_set(d1, "banana", 5);
    dict_set(d1, "cherry", 7);

    dict_set(d2, "banana", 2);
    dict_set(d2, "cherry", 4);
    dict_set(d2, "date", 6);

    Dict *combined = dict_combine(d1, d2);
    if (!combined) { dict_destroy(d1); dict_destroy(d2); return 1; }

    dict_print(combined);

    dict_destroy(d1);
    dict_destroy(d2);
    dict_destroy(combined);
    return 0;
}