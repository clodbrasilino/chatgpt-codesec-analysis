#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT_CAPACITY 256

typedef struct DictEntry {
    char *key;
    int value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dictionary {
    DictEntry *buckets[DICT_CAPACITY];
    int size;
    DictEntry **entries;
} Dictionary;

static unsigned long hash_key(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % DICT_CAPACITY;
}

Dictionary *dict_create(void) {
    Dictionary *dict = calloc(1, sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->size = 0;
    dict->entries = NULL;
    return dict;
}

int dict_set(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    unsigned long index = hash_key(key);
    DictEntry *entry = dict->buckets[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return 0;
        }
        entry = entry->next;
    }
    DictEntry *new_entry = malloc(sizeof(DictEntry));
    if (new_entry == NULL) {
        return -1;
    }
    new_entry->key = strdup(key);
    if (new_entry->key == NULL) {
        free(new_entry);
        return -1;
    }
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    dict->size++;
    DictEntry **tmp = realloc(dict->entries, sizeof(DictEntry *) * (size_t)dict->size);
    if (tmp == NULL) {
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    dict->entries = tmp;
    dict->entries[dict->size - 1] = new_entry;
    return 0;
}

int dict_get_by_index(Dictionary *dict, int index, char **out_key, int *out_value) {
    if (dict == NULL || out_key == NULL || out_value == NULL) {
        return -1;
    }
    if (index < 0 || index >= dict->size) {
        return -1;
    }
    *out_key = dict->entries[index]->key;
    *out_value = dict->entries[index]->value;
    return 0;
}

void dict_destroy(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (int i = 0; i < DICT_CAPACITY; i++) {
        DictEntry *entry = dict->buckets[i];
        while (entry != NULL) {
            DictEntry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->entries);
    free(dict);
}

int main(void) {
    Dictionary *dict = dict_create();
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }
    dict_set(dict, "apple", 10);
    dict_set(dict, "banana", 20);
    dict_set(dict, "cherry", 30);
    dict_set(dict, "date", 40);
    dict_set(dict, "elderberry", 50);

    char *key = NULL;
    int value = 0;
    int result;

    for (int i = 0; i < 5; i++) {
        result = dict_get_by_index(dict, i, &key, &value);
        if (result == 0) {
            printf("Index %d: key=\"%s\", value=%d\n", i, key, value);
        } else {
            printf("Index %d: access failed\n", i);
        }
    }

    result = dict_get_by_index(dict, -1, &key, &value);
    if (result != 0) {
        printf("Negative index properly rejected\n");
    }

    result = dict_get_by_index(dict, 100, &key, &value);
    if (result != 0) {
        printf("Out-of-bounds index properly rejected\n");
    }

    result = dict_get_by_index(NULL, 0, &key, &value);
    if (result != 0) {
        printf("NULL dictionary properly rejected\n");
    }

    dict_destroy(dict);
    return 0;
}