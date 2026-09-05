#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *str)
{
    size_t length;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    length = strlen(str);
    copy = (char *)malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, str, length + 1);
    return copy;
}

int dictionary_init(Dictionary *dict, size_t initial_capacity)
{
    if (dict == NULL || initial_capacity == 0) {
        return -1;
    }

    dict->pairs = (KeyValuePair *)calloc(initial_capacity, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        return -1;
    }

    dict->size = 0;
    dict->capacity = initial_capacity;
    return 0;
}

int dictionary_contains_key(const Dictionary *dict, const char *key)
{
    size_t i;

    if (dict == NULL || dict->pairs == NULL || key == NULL) {
        return 0;
    }

    for (i = 0; i < dict->size; i++) {
        if (dict->pairs[i].key != NULL && strcmp(dict->pairs[i].key, key) == 0) {
            return 1;
        }
    }

    return 0;
}

int dictionary_insert(Dictionary *dict, const char *key, int value)
{
    KeyValuePair *new_pairs;
    size_t new_capacity;
    size_t i;

    if (dict == NULL || key == NULL) {
        return -1;
    }

    for (i = 0; i < dict->size; i++) {
        if (dict->pairs[i].key != NULL && strcmp(dict->pairs[i].key, key) == 0) {
            dict->pairs[i].value = value;
            return 0;
        }
    }

    if (dict->size == dict->capacity) {
        new_capacity = dict->capacity * 2;
        new_pairs = (KeyValuePair *)realloc(dict->pairs, new_capacity * sizeof(KeyValuePair));
        if (new_pairs == NULL) {
            return -1;
        }
        dict->pairs = new_pairs;
        dict->capacity = new_capacity;
    }

    dict->pairs[dict->size].key = duplicate_string(key);
    if (dict->pairs[dict->size].key == NULL) {
        return -1;
    }

    dict->pairs[dict->size].value = value;
    dict->size++;
    return 0;
}

void dictionary_destroy(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }

    if (dict->pairs != NULL) {
        for (i = 0; i < dict->size; i++) {
            free(dict->pairs[i].key);
            dict->pairs[i].key = NULL;
        }
        free(dict->pairs);
        dict->pairs = NULL;
    }

    dict->size = 0;
    dict->capacity = 0;
}

int main(void)
{
    Dictionary dict;
    const char *search_key = "banana";

    if (dictionary_init(&dict, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dictionary_insert(&dict, "apple", 1) != 0 ||
        dictionary_insert(&dict, "banana", 2) != 0 ||
        dictionary_insert(&dict, "cherry", 3) != 0) {
        fprintf(stderr, "Failed to insert into dictionary\n");
        dictionary_destroy(&dict);
        return EXIT_FAILURE;
    }

    if (dictionary_contains_key(&dict, search_key)) {
        printf("Key \"%s\" is present in the dictionary\n", search_key);
    } else {
        printf("Key \"%s\" is not present in the dictionary\n", search_key);
    }

    if (dictionary_contains_key(&dict, "grape")) {
        printf("Key \"grape\" is present in the dictionary\n");
    } else {
        printf("Key \"grape\" is not present in the dictionary\n");
    }

    dictionary_destroy(&dict);
    return EXIT_SUCCESS;
}