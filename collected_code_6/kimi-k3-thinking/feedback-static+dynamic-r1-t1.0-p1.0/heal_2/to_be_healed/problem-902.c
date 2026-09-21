#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TABLE_SIZE 101
#define MAX_KEY_LENGTH 1024U

typedef struct Entry {
    char *key;
    long value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[TABLE_SIZE];
    size_t count;
} Dict;

static size_t bounded_strnlen(const char *s, size_t maxlen)
{
    size_t len = 0U;

    if (s == NULL) {
        return 0U;
    }
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

static int key_is_valid(const char *key)
{
    if (key == NULL) {
        return 0;
    }
    return bounded_strnlen(key, MAX_KEY_LENGTH + 1U) <= MAX_KEY_LENGTH;
}

static unsigned long hash_key(const char *key)
{
    unsigned long hash = 5381UL;
    size_t i;
    size_t len;

    len = bounded_strnlen(key, MAX_KEY_LENGTH + 1U);
    for (i = 0U; i < len; i++) {
        hash = ((hash << 5) + hash) + (unsigned long)(unsigned char)key[i];
    }

    return hash % (unsigned long)TABLE_SIZE;
}

static char *copy_string(const char *src)
{
    size_t len;
    char *dup;

    len = bounded_strnlen(src, MAX_KEY_LENGTH + 1U);
    if (len > MAX_KEY_LENGTH) {
        return NULL;
    }
    dup = (char *)malloc(len + 1U);
    if (dup == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dup, src, len);
    dup[len] = '\0';
    return dup;
}

static Entry *entry_create(const char *key, long value)
{
    Entry *entry = (Entry *)malloc(sizeof(Entry));

    if (entry == NULL) {
        return NULL;
    }
    entry->key = copy_string(key);
    if (entry->key == NULL) {
        free(entry);
        return NULL;
    }
    entry->value = value;
    entry->next = NULL;
    return entry;
}

Dict *dict_create(void)
{
    return (Dict *)calloc(1U, sizeof(Dict));
}

void dict_free(Dict *dict)
{
    size_t i;
    Entry *entry;
    Entry *next;

    if (dict == NULL) {
        return;
    }
    for (i = 0U; i < (size_t)TABLE_SIZE; i++) {
        entry = dict->buckets[i];
        while (entry != NULL) {
            next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict);
}

int dict_set(Dict *dict, const char *key, long value)
{
    unsigned long index;
    Entry *entry;

    if (dict == NULL || !key_is_valid(key)) {
        return -1;
    }
    index = hash_key(key);
    entry = dict->buckets[index];
    while (entry != NULL) {
        if (strncmp(entry->key, key, MAX_KEY_LENGTH + 1U) == 0) {
            entry->value = value;
            return 0;
        }
        entry = entry->next;
    }
    entry = entry_create(key, value);
    if (entry == NULL) {
        return -1;
    }
    entry->next = dict->buckets[index];
    dict->buckets[index] = entry;
    dict->count++;
    return 0;
}

int dict_get(const Dict *dict, const char *key, long *out_value)
{
    unsigned long index;
    Entry *entry;

    if (dict == NULL || !key_is_valid(key) || out_value == NULL) {
        return -1;
    }
    index = hash_key(key);
    entry = dict->buckets[index];
    while (entry != NULL) {
        if (strncmp(entry->key, key, MAX_KEY_LENGTH + 1U) == 0) {
            *out_value = entry->value;
            return 0;
        }
        entry = entry->next;
    }
    return -1;
}

Dict *dict_combine(const Dict *first, const Dict *second)
{
    Dict *result;
    size_t i;
    Entry *entry;
    long existing;
    long sum;

    if (first == NULL || second == NULL) {
        return NULL;
    }
    result = dict_create();
    if (result == NULL) {
        return NULL;
    }
    for (i = 0U; i < (size_t)TABLE_SIZE; i++) {
        for (entry = first->buckets[i]; entry != NULL; entry = entry->next) {
            if (dict_set(result, entry->key, entry->value) != 0) {
                dict_free(result);
                return NULL;
            }
        }
    }
    for (i = 0U; i < (size_t)TABLE_SIZE; i++) {
        for (entry = second->buckets[i]; entry != NULL; entry = entry->next) {
            sum = entry->value;
            if (dict_get(result, entry->key, &existing) == 0) {
                if ((entry->value > 0L && existing > LONG_MAX - entry->value) ||
                    (entry->value < 0L && existing < LONG_MIN - entry->value)) {
                    dict_free(result);
                    return NULL;
                }
                sum = existing + entry->value;
            }
            if (dict_set(result, entry->key, sum) != 0) {
                dict_free(result);
                return NULL;
            }
        }
    }
    return result;
}

static void dict_print(const Dict *dict)
{
    size_t i;
    Entry *entry;

    if (dict == NULL) {
        return;
    }
    for (i = 0U; i < (size_t)TABLE_SIZE; i++) {
        entry = dict->buckets[i];
        while (entry != NULL) {
            (void)printf("%s: %ld\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}

int main(void)
{
    Dict *first = dict_create();
    Dict *second = dict_create();
    Dict *combined;
    int status;

    if (first == NULL || second == NULL) {
        dict_free(first);
        dict_free(second);
        return EXIT_FAILURE;
    }

    status = dict_set(first, "apple", 3L);
    status |= dict_set(first, "banana", 5L);
    status |= dict_set(first, "cherry", 7L);
    status |= dict_set(second, "banana", 2L);
    status |= dict_set(second, "cherry", 1L);
    status |= dict_set(second, "date", 4L);

    if (status != 0) {
        dict_free(first);
        dict_free(second);
        return EXIT_FAILURE;
    }

    combined = dict_combine(first, second);
    if (combined == NULL) {
        dict_free(first);
        dict_free(second);
        return EXIT_FAILURE;
    }

    dict_print(combined);

    dict_free(first);
    dict_free(second);
    dict_free(combined);

    return EXIT_SUCCESS;
}