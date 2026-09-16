#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictEntry {
    char *key;
    int value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dictionary {
    DictEntry *head;
    int size;
} Dictionary;

static char *string_duplicate(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t length = strlen(str);
    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, str, length + 1);
    return copy;
}

Dictionary *dictionary_create(void) {
    Dictionary *dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    char *key_copy = string_duplicate(key);
    if (key_copy == NULL) {
        return -1;
    }
    DictEntry *entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        free(key_copy);
        return -1;
    }
    entry->key = key_copy;
    entry->value = value;
    entry->next = dict->head;
    dict->head = entry;
    dict->size++;
    return 0;
}

void dictionary_destroy(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    DictEntry *current = dict->head;
    while (current != NULL) {
        DictEntry *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    free(dict);
}

char **dictionary_get_keys(const Dictionary *dict, int *key_count) {
    if (dict == NULL) {
        if (key_count != NULL) {
            *key_count = 0;
        }
        return NULL;
    }
    if (key_count != NULL) {
        *key_count = dict->size;
    }
    if (dict->size == 0) {
        return NULL;
    }
    char **keys = malloc((size_t)dict->size * sizeof(*keys));
    if (keys == NULL) {
        if (key_count != NULL) {
            *key_count = 0;
        }
        return NULL;
    }
    int index = 0;
    for (const DictEntry *entry = dict->head; entry != NULL; entry = entry->next) {
        keys[index] = string_duplicate(entry->key);
        if (keys[index] == NULL) {
            int i;
            for (i = 0; i < index; i++) {
                free(keys[i]);
            }
            free(keys);
            if (key_count != NULL) {
                *key_count = 0;
            }
            return NULL;
        }
        index++;
    }
    return keys;
}

int main(void) {
    Dictionary *dict = dictionary_create();
    if (dict == NULL) {
        return 1;
    }
    if (dictionary_insert(dict, "apple", 1) != 0 ||
        dictionary_insert(dict, "banana", 2) != 0 ||
        dictionary_insert(dict, "cherry", 3) != 0) {
        dictionary_destroy(dict);
        return 1;
    }
    int expected_count = dict->size;
    int count = 0;
    char **keys = dictionary_get_keys(dict, &count);
    if (expected_count > 0 && (keys == NULL || count != expected_count)) {
        dictionary_destroy(dict);
        return 1;
    }
    if (expected_count == 0 && keys != NULL) {
        free(keys);
        dictionary_destroy(dict);
        return 1;
    }
    int i;
    for (i = 0; i < count; i++) {
        printf("%s\n", keys[i]);
    }
    for (i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
    dictionary_destroy(dict);
    return 0;
}