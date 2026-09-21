#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 64
#define MAX_KEY_LENGTH 256

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[TABLE_SIZE];
    size_t count;
} Dictionary;

static unsigned int hash_key(const char *key, size_t len)
{
    unsigned int h = 5381;
    size_t i;
    for (i = 0; i < len; i++) {
        h = ((h << 5) + h) + (unsigned char)key[i];
    }
    return h % TABLE_SIZE;
}

void dict_init(Dictionary *dict)
{
    size_t i;
    if (dict == NULL) {
        return;
    }
    for (i = 0; i < TABLE_SIZE; i++) {
        dict->buckets[i] = NULL;
    }
    dict->count = 0;
}

bool dict_is_empty(const Dictionary *dict)
{
    if (dict == NULL) {
        return true;
    }
    return dict->count == 0;
}

int dict_put(Dictionary *dict, const char *key, int value)
{
    unsigned int idx;
    Entry *cur;
    Entry *entry;
    size_t key_len;

    if (dict == NULL || key == NULL) {
        return -1;
    }

    key_len = strnlen(key, MAX_KEY_LENGTH);
    if (key_len == MAX_KEY_LENGTH) {
        return -1;
    }

    idx = hash_key(key, key_len);
    cur = dict->buckets[idx];
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            cur->value = value;
            return 0;
        }
        cur = cur->next;
    }

    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        return -1;
    }
    entry->key = malloc(key_len + 1);
    if (entry->key == NULL) {
        free(entry);
        return -1;
    }
    memcpy(entry->key, key, key_len + 1);
    entry->value = value;
    entry->next = dict->buckets[idx];
    dict->buckets[idx] = entry;
    dict->count++;
    return 0;
}

int dict_remove(Dictionary *dict, const char *key)
{
    unsigned int idx;
    Entry *cur;
    Entry *prev;
    size_t key_len;

    if (dict == NULL || key == NULL) {
        return -1;
    }

    key_len = strnlen(key, MAX_KEY_LENGTH);
    if (key_len == MAX_KEY_LENGTH) {
        return -1;
    }

    idx = hash_key(key, key_len);
    cur = dict->buckets[idx];
    prev = NULL;
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            if (prev == NULL) {
                dict->buckets[idx] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur->key);
            free(cur);
            dict->count--;
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    return -1;
}

void dict_free(Dictionary *dict)
{
    size_t i;
    Entry *cur;
    Entry *next;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < TABLE_SIZE; i++) {
        cur = dict->buckets[i];
        while (cur != NULL) {
            next = cur->next;
            free(cur->key);
            free(cur);
            cur = next;
        }
        dict->buckets[i] = NULL;
    }
    dict->count = 0;
}

int main(void)
{
    Dictionary dict;
    dict_init(&dict);

    printf("Dictionary is empty: %s\n", dict_is_empty(&dict) ? "true" : "false");

    if (dict_put(&dict, "alpha", 1) != 0) {
        fprintf(stderr, "Error: failed to insert entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    printf("Dictionary is empty: %s\n", dict_is_empty(&dict) ? "true" : "false");

    if (dict_remove(&dict, "alpha") != 0) {
        fprintf(stderr, "Error: failed to remove entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    printf("Dictionary is empty: %s\n", dict_is_empty(&dict) ? "true" : "false");

    dict_free(&dict);
    return EXIT_SUCCESS;
}