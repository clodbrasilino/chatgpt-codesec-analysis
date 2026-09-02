#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue **buckets;
    size_t bucket_count;
} Dictionary;

static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

Dictionary *dictionary_create(size_t bucket_count) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->buckets = (KeyValue **)calloc(bucket_count, sizeof(KeyValue *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    dict->bucket_count = bucket_count;
    return dict;
}

void dictionary_destroy(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->bucket_count; i++) {
        KeyValue *current = dict->buckets[i];
        while (current != NULL) {
            KeyValue *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    unsigned long hash = hash_string(key);
    size_t index = hash % dict->bucket_count;
    
    KeyValue *current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return -1;
    }
    new_pair->key = (char *)malloc(strlen(key) + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        return -1;
    }
    strcpy(new_pair->key, key);
    new_pair->value = value;
    new_pair->next = dict->buckets[index];
    dict->buckets[index] = new_pair;
    return 0;
}

int dictionary_contains(const Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return 0;
    }
    unsigned long hash = hash_string(key);
    size_t index = hash % dict->bucket_count;
    
    KeyValue *current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int main(void) {
    Dictionary *dict = dictionary_create(16);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }
    
    dictionary_insert(dict, "apple", 1);
    dictionary_insert(dict, "banana", 2);
    dictionary_insert(dict, "cherry", 3);
    
    const char *test_keys[] = {"apple", "banana", "grape", "cherry", NULL};
    
    for (int i = 0; test_keys[i] != NULL; i++) {
        if (dictionary_contains(dict, test_keys[i])) {
            printf("Key '%s' is present in the dictionary.\n", test_keys[i]);
        } else {
            printf("Key '%s' is NOT present in the dictionary.\n", test_keys[i]);
        }
    }
    
    dictionary_destroy(dict);
    return EXIT_SUCCESS;
}