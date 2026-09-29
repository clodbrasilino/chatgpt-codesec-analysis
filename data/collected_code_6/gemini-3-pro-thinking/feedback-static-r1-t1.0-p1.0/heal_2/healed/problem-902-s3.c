#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
    size_t capacity;
} Dictionary;

char *duplicate_string(const char *src);
Dictionary *create_dictionary(size_t initial_capacity);
void free_dictionary(Dictionary *dict);
int insert_or_add(Dictionary *dict, const char *key, int value);
Dictionary *combine_dictionaries(const Dictionary *dict1, const Dictionary *dict2);

char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }
    size_t max_len = 4096;
    size_t len = 0;
    while (len < max_len && src[len] != '\0') {
        len++;
    }
    char *dst = (char *)malloc(len + 1);
    if (!dst) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    dst[len] = '\0';
    return dst;
}

Dictionary *create_dictionary(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 8;
    }
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->pairs = (KeyValuePair *)calloc(initial_capacity, sizeof(KeyValuePair));
    if (!dict->pairs) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i].key);
    }
    free(dict->pairs);
    free(dict);
}

int insert_or_add(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) {
        return -1;
    }
    for (size_t i = 0; i < dict->count; i++) {
        if (strncmp(dict->pairs[i].key, key, 4096) == 0) {
            dict->pairs[i].value += value;
            return 0;
        }
    }
    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        if (new_capacity == 0) {
            new_capacity = 8;
        }
        KeyValuePair *new_pairs = (KeyValuePair *)realloc(dict->pairs, new_capacity * sizeof(KeyValuePair));
        if (!new_pairs) {
            return -1;
        }
        dict->pairs = new_pairs;
        dict->capacity = new_capacity;
    }
    char *new_key = duplicate_string(key);
    if (!new_key) {
        return -1;
    }
    dict->pairs[dict->count].key = new_key;
    dict->pairs[dict->count].value = value;
    dict->count++;
    return 0;
}

Dictionary *combine_dictionaries(const Dictionary *dict1, const Dictionary *dict2) {
    if (!dict1 || !dict2) {
        return NULL;
    }
    Dictionary *result = create_dictionary(dict1->count + dict2->count);
    if (!result) {
        return NULL;
    }
    for (size_t i = 0; i < dict1->count; i++) {
        if (insert_or_add(result, dict1->pairs[i].key, dict1->pairs[i].value) != 0) {
            free_dictionary(result);
            return NULL;
        }
    }
    for (size_t i = 0; i < dict2->count; i++) {
        if (insert_or_add(result, dict2->pairs[i].key, dict2->pairs[i].value) != 0) {
            free_dictionary(result);
            return NULL;
        }
    }
    return result;
}

int main(void) {
    Dictionary *dict1 = create_dictionary(8);
    if (!dict1) {
        return EXIT_FAILURE;
    }
    Dictionary *dict2 = create_dictionary(8);
    if (!dict2) {
        free_dictionary(dict1);
        return EXIT_FAILURE;
    }
    if (insert_or_add(dict1, "apple", 5) != 0 ||
        insert_or_add(dict1, "banana", 3) != 0 ||
        insert_or_add(dict1, "orange", 2) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return EXIT_FAILURE;
    }
    if (insert_or_add(dict2, "apple", 4) != 0 ||
        insert_or_add(dict2, "banana", 7) != 0 ||
        insert_or_add(dict2, "grape", 6) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return EXIT_FAILURE;
    }
    Dictionary *combined = combine_dictionaries(dict1, dict2);
    if (!combined) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < combined->count; i++) {
        printf("%s: %d\n", combined->pairs[i].key, combined->pairs[i].value);
    }
    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(combined);
    return EXIT_SUCCESS;
}