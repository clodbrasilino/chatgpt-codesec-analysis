#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define DICT_MAX_KEY_LEN 4096

typedef struct {
    char *key;
    int value;
    bool occupied;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t capacity;
    size_t size;
} Dictionary;

static size_t safe_strnlen(const char *str, size_t maxlen)
{
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    return len;
}

static unsigned long hash_string(const char *str)
{
    unsigned long hash = 5381UL;
    unsigned char c;
    while ((c = (unsigned char)*str++) != 0) {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }
    return hash;
}

static bool safe_copy_string(char *dest, size_t dest_size, const char *src, size_t src_len)
{
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }
    if (src_len >= dest_size) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return true;
}

bool dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL || capacity == 0) {
        return false;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return false;
    }
    dict->capacity = capacity;
    dict->size = 0;
    return true;
}

bool dict_set(Dictionary *dict, const char *key, int value)
{
    if (dict == NULL || dict->entries == NULL || key == NULL || dict->capacity == 0) {
        return false;
    }
    size_t key_len = safe_strnlen(key, DICT_MAX_KEY_LEN + 1);
    if (key_len > DICT_MAX_KEY_LEN) {
        return false;
    }
    size_t start = hash_string(key) % dict->capacity;
    size_t index = start;
    do {
        if (!dict->entries[index].occupied) {
            if (dict->size >= dict->capacity) {
                return false;
            }
            size_t buf_size = key_len + 1;
            char *key_copy = malloc(buf_size);
            if (key_copy == NULL) {
                return false;
            }
            if (!safe_copy_string(key_copy, buf_size, key, key_len)) {
                free(key_copy);
                return false;
            }
            dict->entries[index].key = key_copy;
            dict->entries[index].value = value;
            dict->entries[index].occupied = true;
            dict->size++;
            return true;
        }
        if (strcmp(dict->entries[index].key, key) == 0) {
            dict->entries[index].value = value;
            return true;
        }
        index = (index + 1) % dict->capacity;
    } while (index != start);
    return false;
}

char **dict_keys(const Dictionary *dict, size_t *out_count)
{
    if (dict == NULL || out_count == NULL) {
        return NULL;
    }
    *out_count = 0;
    if (dict->entries == NULL || dict->size == 0) {
        return NULL;
    }
    if (dict->size > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }
    char **keys = malloc(dict->size * sizeof(*keys));
    if (keys == NULL) {
        return NULL;
    }
    size_t count = 0;
    for (size_t i = 0; i < dict->capacity && count < dict->size; i++) {
        if (dict->entries[i].occupied) {
            size_t key_len = safe_strnlen(dict->entries[i].key, DICT_MAX_KEY_LEN + 1);
            if (key_len > DICT_MAX_KEY_LEN) {
                for (size_t j = 0; j < count; j++) {
                    free(keys[j]);
                }
                free(keys);
                return NULL;
            }
            size_t len = key_len + 1;
            keys[count] = malloc(len);
            if (keys[count] == NULL) {
                for (size_t j = 0; j < count; j++) {
                    free(keys[j]);
                }
                free(keys);
                return NULL;
            }
            if (!safe_copy_string(keys[count], len, dict->entries[i].key, key_len)) {
                free(keys[count]);
                for (size_t j = 0; j < count; j++) {
                    free(keys[j]);
                }
                free(keys);
                return NULL;
            }
            count++;
        }
    }
    *out_count = count;
    return keys;
}

void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->capacity; i++) {
            if (dict->entries[i].occupied) {
                free(dict->entries[i].key);
                dict->entries[i].key = NULL;
            }
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->capacity = 0;
    dict->size = 0;
}

int main(void)
{
    Dictionary dict;
    if (!dict_init(&dict, 16)) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_set(&dict, "apple", 1) ||
        !dict_set(&dict, "banana", 2) ||
        !dict_set(&dict, "cherry", 3)) {
        fprintf(stderr, "Failed to insert into dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    size_t count = 0;
    char **keys = dict_keys(&dict, &count);
    if (keys == NULL) {
        fprintf(stderr, "Failed to retrieve keys\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", keys[i]);
        free(keys[i]);
    }
    free(keys);

    dict_free(&dict);
    return EXIT_SUCCESS;
}