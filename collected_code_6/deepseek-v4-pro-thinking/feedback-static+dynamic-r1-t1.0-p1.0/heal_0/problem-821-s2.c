#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict_entry {
    char *key;
    int value;
    struct dict_entry *next;
} dict_entry;

typedef struct dictionary {
    dict_entry *entries;
} dictionary;

dictionary *dict_create(void) {
    dictionary *dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = NULL;
    return dict;
}

void dict_destroy(dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    dict_entry *entry = dict->entries;
    while (entry != NULL) {
        dict_entry *next = entry->next;
        free(entry->key);
        free(entry);
        entry = next;
    }
    free(dict);
}

int dict_put(dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    dict_entry *entry = dict->entries;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return 0;
        }
        entry = entry->next;
    }
    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        return -1;
    }
    entry->key = malloc(strlen(key) + 1);
    if (entry->key == NULL) {
        free(entry);
        return -1;
    }
    memcpy(entry->key, key, strlen(key) + 1);
    entry->value = value;
    entry->next = dict->entries;
    dict->entries = entry;
    return 0;
}

dictionary *dict_merge(const dictionary *left, const dictionary *right) {
    if (left == NULL || right == NULL) {
        return NULL;
    }
    dictionary *merged = dict_create();
    if (merged == NULL) {
        return NULL;
    }
    const dict_entry *entry;
    for (entry = left->entries; entry != NULL; entry = entry->next) {
        if (dict_put(merged, entry->key, entry->value) != 0) {
            dict_destroy(merged);
            return NULL;
        }
    }
    for (entry = right->entries; entry != NULL; entry = entry->next) {
        if (dict_put(merged, entry->key, entry->value) != 0) {
            dict_destroy(merged);
            return NULL;
        }
    }
    return merged;
}

int main(void) {
    dictionary *left = dict_create();
    if (left == NULL) {
        return 1;
    }
    dictionary *right = dict_create();
    if (right == NULL) {
        dict_destroy(left);
        return 1;
    }
    if (dict_put(left, "a", 1) != 0 ||
        dict_put(left, "b", 2) != 0 ||
        dict_put(right, "b", 3) != 0 ||
        dict_put(right, "c", 4) != 0) {
        dict_destroy(left);
        dict_destroy(right);
        return 1;
    }
    dictionary *merged = dict_merge(left, right);
    if (merged == NULL) {
        dict_destroy(left);
        dict_destroy(right);
        return 1;
    }
    for (dict_entry *entry = merged->entries; entry != NULL; entry = entry->next) {
        printf("%s:%d\n", entry->key, entry->value);
    }
    dict_destroy(merged);
    dict_destroy(right);
    dict_destroy(left);
    return 0;
}