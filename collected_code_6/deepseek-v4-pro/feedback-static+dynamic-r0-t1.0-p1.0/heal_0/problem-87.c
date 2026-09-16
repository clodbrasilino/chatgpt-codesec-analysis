#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 8
#define LOAD_FACTOR 0.75

typedef struct dict_entry {
    char *key;
    int value;
    int occupied;
} dict_entry;

typedef struct dict {
    dict_entry *entries;
    int capacity;
    int size;
} dict;

static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

static char *dup_string(const char *str) {
    size_t len = strlen(str) + 1;
    char *copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, str, len);
    }
    return copy;
}

static void dict_destroy(dict *d) {
    if (d == NULL) return;
    if (d->entries != NULL) {
        for (int i = 0; i < d->capacity; i++) {
            if (d->entries[i].occupied) {
                free(d->entries[i].key);
            }
        }
        free(d->entries);
    }
    d->entries = NULL;
    d->capacity = 0;
    d->size = 0;
}

static int dict_resize(dict *d, int new_capacity) {
    dict_entry *new_entries = calloc((size_t)new_capacity, sizeof(dict_entry));
    if (new_entries == NULL) return -1;

    for (int i = 0; i < d->capacity; i++) {
        if (d->entries[i].occupied) {
            unsigned long hash = hash_string(d->entries[i].key);
            int index = hash % new_capacity;
            while (new_entries[index].occupied) {
                index = (index + 1) % new_capacity;
            }
            new_entries[index].key = d->entries[i].key;
            new_entries[index].value = d->entries[i].value;
            new_entries[index].occupied = 1;
        }
    }
    free(d->entries);
    d->entries = new_entries;
    d->capacity = new_capacity;
    return 0;
}

static int dict_init(dict *d) {
    d->capacity = INITIAL_CAPACITY;
    d->size = 0;
    d->entries = calloc((size_t)d->capacity, sizeof(dict_entry));
    return d->entries != NULL ? 0 : -1;
}

static int dict_set(dict *d, const char *key, int value) {
    if ((double)(d->size + 1) / d->capacity > LOAD_FACTOR) {
        if (dict_resize(d, d->capacity * 2) != 0) return -1;
    }

    unsigned long hash = hash_string(key);
    int index = hash % d->capacity;
    int first_deleted = -1;

    while (d->entries[index].occupied || d->entries[index].key != NULL) {
        if (!d->entries[index].occupied && first_deleted == -1) {
            first_deleted = index;
        }
        if (d->entries[index].occupied && strcmp(d->entries[index].key, key) == 0) {
            d->entries[index].value = value;
            return 0;
        }
        index = (index + 1) % d->capacity;
    }

    int target = (first_deleted != -1) ? first_deleted : index;
    char *key_copy = dup_string(key);
    if (key_copy == NULL) return -1;
    d->entries[target].key = key_copy;
    d->entries[target].value = value;
    d->entries[target].occupied = 1;
    d->size++;
    return 0;
}

static int dict_get(const dict *d, const char *key, int *value) {
    if (d->entries == NULL) return 0;
    unsigned long hash = hash_string(key);
    int index = hash % d->capacity;

    while (d->entries[index].occupied || d->entries[index].key != NULL) {
        if (d->entries[index].occupied && strcmp(d->entries[index].key, key) == 0) {
            *value = d->entries[index].value;
            return 1;
        }
        index = (index + 1) % d->capacity;
    }
    return 0;
}

static void dict_merge(const dict *d1, const dict *d2, const dict *d3, dict *result) {
    for (int i = 0; i < d1->capacity; i++) {
        if (d1->entries[i].occupied) {
            dict_set(result, d1->entries[i].key, d1->entries[i].value);
        }
    }
    for (int i = 0; i < d2->capacity; i++) {
        if (d2->entries[i].occupied) {
            dict_set(result, d2->entries[i].key, d2->entries[i].value);
        }
    }
    for (int i = 0; i < d3->capacity; i++) {
        if (d3->entries[i].occupied) {
            dict_set(result, d3->entries[i].key, d3->entries[i].value);
        }
    }
}

static void dict_print(const dict *d) {
    printf("{");
    int first = 1;
    for (int i = 0; i < d->capacity; i++) {
        if (d->entries[i].occupied) {
            if (!first) printf(", ");
            printf("%s: %d", d->entries[i].key, d->entries[i].value);
            first = 0;
        }
    }
    printf("}\n");
}

int main(void) {
    dict a, b, c;
    if (dict_init(&a) != 0 || dict_init(&b) != 0 || dict_init(&c) != 0) {
        fprintf(stderr, "Failed to initialize dictionaries\n");
        dict_destroy(&a);
        dict_destroy(&b);
        dict_destroy(&c);
        return EXIT_FAILURE;
    }

    dict_set(&a, "apple", 1);
    dict_set(&a, "banana", 2);
    dict_set(&b, "cherry", 3);
    dict_set(&b, "date", 4);
    dict_set(&c, "elderberry", 5);
    dict_set(&c, "fig", 6);
    dict_set(&c, "apple", 100);

    dict merged;
    if (dict_init(&merged) != 0) {
        fprintf(stderr, "Failed to initialize merged dictionary\n");
        dict_destroy(&a);
        dict_destroy(&b);
        dict_destroy(&c);
        return EXIT_FAILURE;
    }

    dict_merge(&a, &b, &c, &merged);
    dict_print(&merged);

    int value;
    if (dict_get(&merged, "apple", &value)) {
        printf("apple is %d\n", value);
    }
    if (dict_get(&merged, "date", &value)) {
        printf("date is %d\n", value);
    }
    if (dict_get(&merged, "fig", &value)) {
        printf("fig is %d\n", value);
    }
    if (!dict_get(&merged, "grape", &value)) {
        printf("grape not found\n");
    }

    dict_destroy(&a);
    dict_destroy(&b);
    dict_destroy(&c);
    dict_destroy(&merged);
    return EXIT_SUCCESS;
}