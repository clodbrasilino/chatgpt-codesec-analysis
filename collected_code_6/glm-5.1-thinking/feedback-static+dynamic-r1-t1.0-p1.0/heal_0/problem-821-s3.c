#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct Dict {
    Entry **buckets;
    size_t capacity;
} Dict;

Dict* dict_create(size_t capacity);
void dict_destroy(Dict *dict);
int dict_set(Dict *dict, const char *key, const char *value);
const char* dict_get(Dict *dict, const char *key);
Dict* dict_merge(Dict *d1, Dict *d2);

unsigned long hash_key(const char *key, size_t capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

Dict* dict_create(size_t capacity) {
    Dict *dict = malloc(sizeof(Dict));
    if (!dict) return NULL;
    dict->buckets = calloc(capacity, sizeof(Entry*));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->capacity = capacity;
    return dict;
}

void dict_destroy(Dict *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->capacity; i++) {
        Entry *entry = dict->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int dict_set(Dict *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return -1;
    size_t index = hash_key(key, dict->capacity);
    Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            char *new_value = strdup(value);
            if (!new_value) return -1;
            free(entry->value);
            entry->value = new_value;
            return 0;
        }
        entry = entry->next;
    }
    Entry *new_entry = malloc(sizeof(Entry));
    if (!new_entry) return -1;
    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        return -1;
    }
    new_entry->value = strdup(value);
    if (!new_entry->value) {
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    return 0;
}

const char* dict_get(Dict *dict, const char *key) {
    if (!dict || !key) return NULL;
    size_t index = hash_key(key, dict->capacity);
    Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

Dict* dict_merge(Dict *d1, Dict *d2) {
    size_t cap1 = d1 ? d1->capacity : 0;
    size_t cap2 = d2 ? d2->capacity : 0;
    size_t capacity = cap1 + cap2;
    if (capacity == 0) capacity = 16;
    Dict *merged = dict_create(capacity);
    if (!merged) return NULL;
    if (d1) {
        for (size_t i = 0; i < d1->capacity; i++) {
            Entry *e = d1->buckets[i];
            while (e) {
                if (dict_set(merged, e->key, e->value) != 0) {
                    dict_destroy(merged);
                    return NULL;
                }
                e = e->next;
            }
        }
    }
    if (d2) {
        for (size_t i = 0; i < d2->capacity; i++) {
            Entry *e = d2->buckets[i];
            while (e) {
                if (dict_set(merged, e->key, e->value) != 0) {
                    dict_destroy(merged);
                    return NULL;
                }
                e = e->next;
            }
        }
    }
    return merged;
}

int main(void) {
    Dict *d1 = dict_create(16);
    if (!d1) return 1;
    Dict *d2 = dict_create(16);
    if (!d2) {
        dict_destroy(d1);
        return 1;
    }
    dict_set(d1, "name", "Alice");
    dict_set(d1, "age", "30");
    dict_set(d2, "city", "Wonderland");
    dict_set(d2, "age", "31");
    Dict *merged = dict_merge(d1, d2);
    if (!merged) {
        dict_destroy(d1);
        dict_destroy(d2);
        return 1;
    }
    const char *name = dict_get(merged, "name");
    const char *age = dict_get(merged, "age");
    const char *city = dict_get(merged, "city");
    printf("name: %s\n", name ? name : "(null)");
    printf("age: %s\n", age ? age : "(null)");
    printf("city: %s\n", city ? city : "(null)");
    dict_destroy(d1);
    dict_destroy(d2);
    dict_destroy(merged);
    return 0;
}