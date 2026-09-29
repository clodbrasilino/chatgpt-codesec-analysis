#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 16

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry *buckets[TABLE_SIZE];
    size_t count;
} Dictionary;

Dictionary *dict_create(void);
int dict_insert(Dictionary *dict, const char *key, const char *value);
int dict_is_empty(const Dictionary *dict);
void dict_destroy(Dictionary *dict);
static unsigned long hash_key(const char *key);

static unsigned long hash_key(const char *key)
{
    unsigned long hash = 5381UL;
    int c;

    while ((c = (unsigned char)*key++) != 0) {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }
    return hash % TABLE_SIZE;
}

Dictionary *dict_create(void)
{
    Dictionary *dict = malloc(sizeof(Dictionary));
    size_t i;

    if (dict == NULL) {
        return NULL;
    }
    for (i = 0; i < TABLE_SIZE; i++) {
        dict->buckets[i] = NULL;
    }
    dict->count = 0;
    return dict;
}

int dict_insert(Dictionary *dict, const char *key, const char *value)
{
    unsigned long index;
    Entry *entry;
    size_t key_len;
    size_t value_len;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    entry = malloc(sizeof(Entry));
    if (entry == NULL) {
        return -1;
    }

    key_len = strlen(key) + 1;
    value_len = strlen(value) + 1;

    entry->key = malloc(key_len);
    if (entry->key == NULL) {
        free(entry);
        return -1;
    }

    entry->value = malloc(value_len);
    if (entry->value == NULL) {
        free(entry->key);
        free(entry);
        return -1;
    }

    memcpy(entry->key, key, key_len);
    memcpy(entry->value, value, value_len);

    index = hash_key(key);
    entry->next = dict->buckets[index];
    dict->buckets[index] = entry;
    dict->count++;
    return 0;
}

int dict_is_empty(const Dictionary *dict)
{
    if (dict == NULL) {
        return 1;
    }
    return (dict->count == 0) ? 1 : 0;
}

void dict_destroy(Dictionary *dict)
{
    size_t i;
    Entry *entry;
    Entry *next;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < TABLE_SIZE; i++) {
        entry = dict->buckets[i];
        while (entry != NULL) {
            next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
        dict->buckets[i] = NULL;
    }
    dict->count = 0;
    free(dict);
}

int main(void)
{
    Dictionary *dict = dict_create();

    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_is_empty(dict) == 1) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    if (dict_insert(dict, "name", "Alice") != 0) {
        fprintf(stderr, "Failed to insert into dictionary\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_is_empty(dict) == 1) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    dict_destroy(dict);
    return EXIT_SUCCESS;
}