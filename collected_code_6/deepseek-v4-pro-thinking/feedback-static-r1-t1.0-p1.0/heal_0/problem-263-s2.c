#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct DictEntry {
    char *key;
    int value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dict {
    DictEntry **buckets;
    size_t size;
    size_t count;
} Dict;

static size_t hash(const char *key) {
    size_t h = 5381;
    while (*key) {
        h = ((h << 5) + h) + (unsigned char)*key++;
    }
    return h;
}

Dict *dict_create(size_t size) {
    if (size == 0) size = 16;
    Dict *dict = malloc(sizeof(*dict));
    if (!dict) return NULL;
    dict->buckets = calloc(size, sizeof(DictEntry *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->size = size;
    dict->count = 0;
    return dict;
}

void dict_free(Dict *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; ++i) {
        DictEntry *entry = dict->buckets[i];
        while (entry) {
            DictEntry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int dict_get(const Dict *dict, const char *key, int *value) {
    if (!dict || !key || !value) return 0;
    size_t index = hash(key) % dict->size;
    DictEntry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            *value = entry->value;
            return 1;
        }
        entry = entry->next;
    }
    return 0;
}

int dict_set(Dict *dict, const char *key, int value) {
    if (!dict || !key) return 0;
    size_t index = hash(key) % dict->size;
    DictEntry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return 1;
        }
        entry = entry->next;
    }
    DictEntry *new_entry = malloc(sizeof(*new_entry));
    if (!new_entry) return 0;
    new_entry->key = malloc(strlen(key) + 1);
    if (!new_entry->key) {
        free(new_entry);
        return 0;
    }
    strcpy(new_entry->key, key);
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    dict->count++;
    return 1;
}

int dict_merge(Dict *dst, const Dict *src) {
    if (!dst || !src) return 0;
    for (size_t i = 0; i < src->size; ++i) {
        const DictEntry *entry = src->buckets[i];
        while (entry) {
            if (!dict_set(dst, entry->key, entry->value)) return 0;
            entry = entry->next;
        }
    }
    return 1;
}

int main(void) {
    Dict *a = dict_create(16);
    Dict *b = dict_create(16);
    if (!a || !b) {
        dict_free(a);
        dict_free(b);
        return 1;
    }
    if (!dict_set(a, "key1", 1) || !dict_set(a, "key2", 2)) {
        dict_free(a);
        dict_free(b);
        return 1;
    }
    if (!dict_set(b, "key2", 20) || !dict_set(b, "key3", 3)) {
        dict_free(a);
        dict_free(b);
        return 1;
    }
    if (!dict_merge(a, b)) {
        dict_free(a);
        dict_free(b);
        return 1;
    }
    int val;
    if (dict_get(a, "key1", &val)) printf("key1: %d\n", val);
    if (dict_get(a, "key2", &val)) printf("key2: %d\n", val);
    if (dict_get(a, "key3", &val)) printf("key3: %d\n", val);
    dict_free(a);
    dict_free(b);
    return 0;
}