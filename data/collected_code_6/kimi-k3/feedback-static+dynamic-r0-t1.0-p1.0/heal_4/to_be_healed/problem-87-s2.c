#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static bool is_valid_string(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return (len < max_len);
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static char* safe_strdup(const char *str, size_t max_len) {
    if (str == NULL || !is_valid_string(str, max_len)) {
        return NULL;
    }
    
    size_t len = safe_strlen(str, max_len);
    char *new_str = malloc(len + 1);
    if (new_str == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str, str, len);
    }
    new_str[len] = '\0';
    return new_str;
}

int dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(DictEntry)) {
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
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    const size_t MAX_STRING_LEN = 1024;
    
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        return -1;
    }
    if (!is_valid_string(key, MAX_STRING_LEN) || !is_valid_string(value, MAX_STRING_LEN)) {
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

char* merge_dictionaries(const Dictionary *d1, const Dictionary *d2, const Dictionary *d3) {
    const size_t MAX_STRING_LEN = 1024;
    const size_t MAX_TOTAL_SIZE = 65536;
    
    if (d1 == NULL || d2 == NULL || d3 == NULL) {
        return NULL;
    }
    
    size_t total_size = d1->size + d2->size + d3->size;
    if (total_size == 0) {
        char *empty = malloc(3);
        if (empty != NULL) {
            empty[0] = '{';
            empty[1] = '}';
            empty[2] = '\0';
        }
        return empty;
    }
    
    if (total_size > MAX_TOTAL_SIZE) {
        return NULL;
    }
    
    size_t buffer_size = 3;
    const Dictionary *dicts[3] = {d1, d2, d3};
    
    for (int d = 0; d < 3; d++) {
        for (size_t i = 0; i < dicts[d]->size; i++) {
            if (!is_valid_string(dicts[d]->entries[i].key, MAX_STRING_LEN) ||
                !is_valid_string(dicts[d]->entries[i].value, MAX_STRING_LEN)) {
                return NULL;
            }
            
            size_t key_len = safe_strlen(dicts[d]->entries[i].key, MAX_STRING_LEN);
            size_t value_len = safe_strlen(dicts[d]->entries[i].value, MAX_STRING_LEN);
            
            if (buffer_size > SIZE_MAX - key_len - value_len - 6) {
                return NULL;
            }
            
            buffer_size += key_len + value_len + 6;
        }
    }
    
    char *result = malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }
    
    size_t pos = 0;
    result[pos++] = '{';
    
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
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
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
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
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
    
    if (pos + 2 > buffer_size) {
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