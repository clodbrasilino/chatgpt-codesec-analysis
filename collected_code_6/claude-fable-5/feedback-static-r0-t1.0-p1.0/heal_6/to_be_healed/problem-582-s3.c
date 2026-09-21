#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 16
#define MAX_STR_LEN 4096

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
static unsigned long hash_key(const char *key, size_t key_len);
static char *dup_bounded(const char *src, size_t *out_len);

static unsigned long hash_key(const char *key, size_t key_len)
{
    unsigned long hash = 5381UL;
    size_t i;

    for (i = 0; i < key_len; i++) {
        hash = ((hash << 5) + hash) + (unsigned long)(unsigned char)key[i];
    }
    return hash % TABLE_SIZE;
}

static char *dup_bounded(const char *src, size_t *out_len)
{
    size_t len;
    size_t alloc_size;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        return NULL;
    }

    if (len > (size_t)-1 - 1) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    alloc_size = len + 1;
    copy = malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'len<alloc_size' is always true [knownConditionTrueFalse]
     *  Condition 'len<alloc_size' is always true
     */
    if (len > 0 && len < alloc_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, src, len);
    }
    copy[len] = '\0';

    if (out_len != NULL) {
        *out_len = len;
    }
    return copy;
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

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    entry = malloc(sizeof(Entry));
    if (entry == NULL) {
        return -1;
    }

    entry->key = dup_bounded(key, &key_len);
    if (entry->key == NULL) {
        free(entry);
        return -1;
    }

    entry->value = dup_bounded(value, NULL);
    if (entry->value == NULL) {
        free(entry->key);
        free(entry);
        return -1;
    }

    index = hash_key(entry->key, key_len);
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