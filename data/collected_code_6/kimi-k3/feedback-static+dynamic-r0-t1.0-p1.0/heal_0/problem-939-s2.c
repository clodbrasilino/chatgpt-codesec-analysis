#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    
    dict->pairs = calloc(capacity, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    
    if (dict->size >= dict->capacity) {
        return -1;
    }
    
    char *key_copy = malloc(strlen(key) + 1);
    if (key_copy == NULL) {
        return -1;
    }
    
    char *value_copy = malloc(strlen(value) + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    
    strcpy(key_copy, key);
    strcpy(value_copy, value);
    
    dict->pairs[dict->size].key = key_copy;
    dict->pairs[dict->size].value = value_copy;
    dict->size++;
    
    return 0;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    if (dict->pairs != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
        }
        free(dict->pairs);
    }
    
    free(dict);
}

int compare_dicts(const void *a, const void *b) {
    const Dictionary *dict_a = *(const Dictionary * const *)a;
    const Dictionary *dict_b = *(const Dictionary * const *)b;
    
    if (dict_a == NULL && dict_b == NULL) {
        return 0;
    }
    if (dict_a == NULL) {
        return -1;
    }
    if (dict_b == NULL) {
        return 1;
    }
    
    if (dict_a->size == 0 && dict_b->size == 0) {
        return 0;
    }
    if (dict_a->size == 0) {
        return -1;
    }
    if (dict_b->size == 0) {
        return 1;
    }
    
    const char *key_a = dict_a->pairs[0].key;
    const char *key_b = dict_b->pairs[0].key;
    
    if (key_a == NULL && key_b == NULL) {
        return 0;
    }
    if (key_a == NULL) {
        return -1;
    }
    if (key_b == NULL) {
        return 1;
    }
    
    return strcmp(key_a, key_b);
}

int sort_dictionary_list(Dictionary **dicts, size_t count) {
    if (dicts == NULL || count == 0) {
        return -1;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (dicts[i] == NULL) {
            return -1;
        }
    }
    
    qsort(dicts, count, sizeof(Dictionary *), compare_dicts);
    return 0;
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL) {
        printf("NULL dictionary\n");
        return;
    }
    
    printf("{ ");
    for (size_t i = 0; i < dict->size; i++) {
        printf("\"%s\": \"%s\"", 
               dict->pairs[i].key ? dict->pairs[i].key : "NULL",
               dict->pairs[i].value ? dict->pairs[i].value : "NULL");
        if (i < dict->size - 1) {
            printf(", ");
        }
    }
    printf(" }\n");
}

int main(void) {
    const size_t dict_count = 4;
    Dictionary **dict_list = calloc(dict_count, sizeof(Dictionary *));
    if (dict_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    dict_list[0] = dict_create(3);
    dict_list[1] = dict_create(3);
    dict_list[2] = dict_create(3);
    dict_list[3] = dict_create(3);
    
    for (size_t i = 0; i < dict_count; i++) {
        if (dict_list[i] == NULL) {
            fprintf(stderr, "Failed to create dictionary %zu\n", i);
            for (size_t j = 0; j < i; j++) {
                dict_free(dict_list[j]);
            }
            free(dict_list);
            return EXIT_FAILURE;
        }
    }
    
    if (dict_add(dict_list[0], "zebra", "animal") != 0 ||
        dict_add(dict_list[0], "color", "striped") != 0) {
        fprintf(stderr, "Failed to add to dictionary 0\n");
        goto cleanup;
    }
    
    if (dict_add(dict_list[1], "apple", "fruit") != 0 ||
        dict_add(dict_list[1], "color", "red") != 0) {
        fprintf(stderr, "Failed to add to dictionary 1\n");
        goto cleanup;
    }
    
    if (dict_add(dict_list[2], "mango", "fruit") != 0 ||
        dict_add(dict_list[2], "color", "yellow") != 0) {
        fprintf(stderr, "Failed to add to dictionary 2\n");
        goto cleanup;
    }
    
    if (dict_add(dict_list[3], "banana", "fruit") != 0) {
        fprintf(stderr, "Failed to add to dictionary 3\n");
        goto cleanup;
    }
    
    printf("Before sorting:\n");
    for (size_t i = 0; i < dict_count; i++) {
        dict_print(dict_list[i]);
    }
    
    if (sort_dictionary_list(dict_list, dict_count) != 0) {
        fprintf(stderr, "Failed to sort dictionaries\n");
        goto cleanup;
    }
    
    printf("\nAfter sorting:\n");
    for (size_t i = 0; i < dict_count; i++) {
        dict_print(dict_list[i]);
    }
    
    for (size_t i = 0; i < dict_count; i++) {
        dict_free(dict_list[i]);
    }
    free(dict_list);
    
    return EXIT_SUCCESS;

cleanup:
    for (size_t i = 0; i < dict_count; i++) {
        dict_free(dict_list[i]);
    }
    free(dict_list);
    return EXIT_FAILURE;
}