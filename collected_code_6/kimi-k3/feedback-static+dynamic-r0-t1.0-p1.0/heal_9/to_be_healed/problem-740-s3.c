#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 1024
#define MAX_VALUE_LEN 4096

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->pairs = (KeyValuePair*)calloc(capacity, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void free_dictionary(Dictionary* dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

int add_pair(Dictionary* dict, const char* key, size_t key_len, const char* value, size_t value_len) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        return -1;
    }
    if (key_len >= MAX_KEY_LEN || value_len >= MAX_VALUE_LEN) {
        return -1;
    }
    
    dict->pairs[dict->size].key = (char*)malloc(key_len + 1);
    if (dict->pairs[dict->size].key == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->pairs[dict->size].key, key, key_len);
    dict->pairs[dict->size].key[key_len] = '\0';
    
    dict->pairs[dict->size].value = (char*)malloc(value_len + 1);
    if (dict->pairs[dict->size].value == NULL) {
        free(dict->pairs[dict->size].key);
        dict->pairs[dict->size].key = NULL;
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->pairs[dict->size].value, value, value_len);
    dict->pairs[dict->size].value[value_len] = '\0';
    
    dict->size++;
    return 0;
}

Dictionary* tuple_to_dict(const char* tuple[], size_t tuple_size) {
    if (tuple == NULL || tuple_size == 0) {
        return NULL;
    }
    size_t pair_count = tuple_size / 2;
    Dictionary* dict = create_dictionary(pair_count);
    if (dict == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < pair_count; i++) {
        const char* key = tuple[i * 2];
        const char* value = tuple[i * 2 + 1];
        if (key == NULL || value == NULL) {
            free_dictionary(dict);
            return NULL;
        }
        size_t key_len = strnlen(key, MAX_KEY_LEN);
        size_t value_len = strnlen(value, MAX_VALUE_LEN);
        if (key_len == MAX_KEY_LEN || value_len == MAX_VALUE_LEN) {
            free_dictionary(dict);
            return NULL;
        }
        if (add_pair(dict, key, key_len, value, value_len) != 0) {
            free_dictionary(dict);
            return NULL;
        }
    }
    return dict;
}

const char* get_value(Dictionary* dict, const char* key) {
    if (dict == NULL || key == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void print_dictionary(Dictionary* dict) {
    if (dict == NULL) {
        return;
    }
    printf("{");
    for (size_t i = 0; i < dict->size; i++) {
        printf("'%s': '%s'", dict->pairs[i].key, dict->pairs[i].value);
        if (i < dict->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void) {
    const char* tuple[] = {"name", "John", "age", "30", "city", "New York"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary* dict = tuple_to_dict(tuple, tuple_size);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    printf("Dictionary: ");
    print_dictionary(dict);

    const char* value = get_value(dict, "age");
    if (value != NULL) {
        printf("Value for key 'age': %s\n", value);
    }

    free_dictionary(dict);
    return EXIT_SUCCESS;
}