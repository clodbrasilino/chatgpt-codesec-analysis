#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_STRING_LEN 1024
#define MAX_DICT_SIZE 1000000
#define MAX_TOTAL_ENTRIES 1000000

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static size_t safe_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static bool is_valid_string(const char *s, size_t max_len) {
    if (s == NULL) {
        return false;
    }
    size_t len = safe_strlen(s, max_len);
    return len < max_len;
}

static bool contains_special_chars(const char *s, size_t len) {
    if (s == NULL) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '\'' || s[i] == '\\' || s[i] == '\0') {
            return true;
        }
    }
    return false;
}

static char* safe_strdup(const char *s, size_t max_len) {
    if (s == NULL) {
        return NULL;
    }
    size_t len = safe_strlen(s, max_len);
    if (len >= max_len) {
        return NULL;
    }
    if (len > SIZE_MAX - 1) {
        return NULL;
    }
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        memcpy(copy, s, len);
    }
    copy[len] = '\0';
    return copy;
}

int dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0 || capacity > MAX_DICT_SIZE) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(DictEntry)) {
        return -1;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
            dict->entries[i].key = NULL;
            dict->entries[i].value = NULL;
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->entries == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    
    size_t key_len = safe_strlen(key, MAX_STRING_LEN);
    size_t value_len = safe_strlen(value, MAX_STRING_LEN);
    
    if (key_len == 0 || key_len >= MAX_STRING_LEN || value_len >= MAX_STRING_LEN) {
        return -1;
    }
    
    if (contains_special_chars(key, key_len) || contains_special_chars(value, value_len)) {
        return -1;
    }
    
    char *new_key = safe_strdup(key, MAX_STRING_LEN);
    if (new_key == NULL) {
        return -1;
    }
    
    char *new_value = safe_strdup(value, MAX_STRING_LEN);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }
    
    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = new_value;
    dict->size++;
    return 0;
}

static bool safe_add_size(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return false;
    }
    *result = a + b;
    return true;
}

static bool validate_dict(const Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL) {
        return false;
    }
    if (dict->size > dict->capacity || dict->size > MAX_DICT_SIZE) {
        return false;
    }
    return true;
}

char* merge_dictionaries(const Dictionary *d1, const Dictionary *d2, const Dictionary *d3) {
    if (!validate_dict(d1) || !validate_dict(d2) || !validate_dict(d3)) {
        return NULL;
    }
    
    size_t total_size = 0;
    if (!safe_add_size(d1->size, d2->size, &total_size)) {
        return NULL;
    }
    if (!safe_add_size(total_size, d3->size, &total_size)) {
        return NULL;
    }
    
    if (total_size > MAX_TOTAL_ENTRIES) {
        return NULL;
    }
    
    if (total_size == 0) {
        char *empty = malloc(3);
        if (empty != NULL) {
            empty[0] = '{';
            empty[1] = '}';
            empty[2] = '\0';
        }
        return empty;
    }
    
    size_t buffer_size = 3;
    const Dictionary *dicts[3] = {d1, d2, d3};
    
    for (int d = 0; d < 3; d++) {
        for (size_t i = 0; i < dicts[d]->size; i++) {
            if (dicts[d]->entries[i].key == NULL || dicts[d]->entries[i].value == NULL) {
                return NULL;
            }
            
            size_t key_len = safe_strlen(dicts[d]->entries[i].key, MAX_STRING_LEN);
            size_t value_len = safe_strlen(dicts[d]->entries[i].value, MAX_STRING_LEN);
            
            if (key_len >= MAX_STRING_LEN || value_len >= MAX_STRING_LEN) {
                return NULL;
            }
            
            if (contains_special_chars(dicts[d]->entries[i].key, key_len) ||
                contains_special_chars(dicts[d]->entries[i].value, value_len)) {
                return NULL;
            }
            
            size_t entry_size = 0;
            if (!safe_add_size(key_len, value_len, &entry_size)) {
                return NULL;
            }
            if (!safe_add_size(entry_size, 6, &entry_size)) {
                return NULL;
            }
            if (i > 0 || d > 0) {
                if (!safe_add_size(entry_size, 2, &entry_size)) {
                    return NULL;
                }
            }
            if (!safe_add_size(buffer_size, entry_size, &buffer_size)) {
                return NULL;
            }
        }
    }
    
    if (buffer_size > SIZE_MAX - 1) {
        return NULL;
    }
    
    char *result = malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }
    
    size_t pos = 0;
    if (pos < buffer_size) {
        result[pos++] = '{';
    }
    
    int first = 1;
    for (int d = 0; d < 3; d++) {
        for (size_t i = 0; i < dicts[d]->size; i++) {
            size_t key_len = safe_strlen(dicts[d]->entries[i].key, MAX_STRING_LEN);
            size_t value_len = safe_strlen(dicts[d]->entries[i].value, MAX_STRING_LEN);
            
            if (!first) {
                if (pos + 2 >= buffer_size) {
                    free(result);
                    return NULL;
                }
                result[pos++] = ',';
                result[pos++] = ' ';
            }
            
            if (pos + 1 >= buffer_size) {
                free(result);
                return NULL;
            }
            result[pos++] = '\'';
            
            if (key_len > 0) {
                if (pos + key_len >= buffer_size) {
                    free(result);
                    return NULL;
                }
                memcpy(result + pos, dicts[d]->entries[i].key, key_len);
                pos += key_len;
            }
            
            if (pos + 4 >= buffer_size) {
                free(result);
                return NULL;
            }
            result[pos++] = '\'';
            result[pos++] = ':';
            result[pos++] = ' ';
            result[pos++] = '\'';
            
            if (value_len > 0) {
                if (pos + value_len >= buffer_size) {
                    free(result);
                    return NULL;
                }
                memcpy(result + pos, dicts[d]->entries[i].value, value_len);
                pos += value_len;
            }
            
            if (pos + 1 >= buffer_size) {
                free(result);
                return NULL;
            }
            result[pos++] = '\'';
            first = 0;
        }
    }
    
    if (pos + 2 >= buffer_size) {
        free(result);
        return NULL;
    }
    result[pos++] = '}';
    result[pos] = '\0';
    
    return result;
}

int main(void) {
    Dictionary dict1, dict2, dict3;
    
    if (dict_init(&dict1, 10) != 0) {
        fprintf(stderr, "Failed to initialize dict1\n");
        return EXIT_FAILURE;
    }
    if (dict_init(&dict2, 10) != 0) {
        fprintf(stderr, "Failed to initialize dict2\n");
        dict_free(&dict1);
        return EXIT_FAILURE;
    }
    if (dict_init(&dict3, 10) != 0) {
        fprintf(stderr, "Failed to initialize dict3\n");
        dict_free(&dict1);
        dict_free(&dict2);
        return EXIT_FAILURE;
    }
    
    if (dict_add(&dict1, "name", "Alice") != 0 ||
        dict_add(&dict1, "age", "30") != 0 ||
        dict_add(&dict2, "city", "New York") != 0 ||
        dict_add(&dict2, "country", "USA") != 0 ||
        dict_add(&dict3, "occupation", "Engineer") != 0 ||
        dict_add(&dict3, "language", "C") != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_free(&dict1);
        dict_free(&dict2);
        dict_free(&dict3);
        return EXIT_FAILURE;
    }
    
    char *merged = merge_dictionaries(&dict1, &dict2, &dict3);
    if (merged == NULL) {
        fprintf(stderr, "Failed to merge dictionaries\n");
        dict_free(&dict1);
        dict_free(&dict2);
        dict_free(&dict3);
        return EXIT_FAILURE;
    }
    
    printf("%s\n", merged);
    
    free(merged);
    dict_free(&dict1);
    dict_free(&dict2);
    dict_free(&dict3);
    
    return EXIT_SUCCESS;
}