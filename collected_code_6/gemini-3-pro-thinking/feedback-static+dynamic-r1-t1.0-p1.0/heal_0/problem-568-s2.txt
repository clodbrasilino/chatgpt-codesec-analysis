#include <stdlib.h>

typedef struct KeyValuePair {
    char *key;
    char *value;
    struct KeyValuePair *next;
} KeyValuePair;

typedef struct Dictionary {
    size_t capacity;
    size_t size;
    KeyValuePair **buckets;
} Dictionary;

typedef struct DictionaryList {
    size_t count;
    Dictionary **dictionaries;
} DictionaryList;

Dictionary* create_empty_dictionary(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->capacity = capacity;
    dict->size = 0;
    dict->buckets = (KeyValuePair **)calloc(capacity, sizeof(KeyValuePair *));
    
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    
    if (dict->buckets) {
        for (size_t i = 0; i < dict->capacity; ++i) {
            KeyValuePair *current = dict->buckets[i];
            while (current) {
                KeyValuePair *next_node = current->next;
                free(current->key);
                free(current->value);
                free(current);
                current = next_node;
            }
        }
        free(dict->buckets);
    }
    free(dict);
}

DictionaryList* create_dictionary_list(size_t count) {
    if (count == 0) {
        return NULL;
    }

    DictionaryList *list = (DictionaryList *)malloc(sizeof(DictionaryList));
    if (!list) {
        return NULL;
    }

    list->count = count;
    list->dictionaries = (Dictionary **)calloc(count, sizeof(Dictionary *));
    if (!list->dictionaries) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        list->dictionaries[i] = create_empty_dictionary(16);
        if (!list->dictionaries[i]) {
            for (size_t j = 0; j < i; ++j) {
                free_dictionary(list->dictionaries[j]);
            }
            free(list->dictionaries);
            free(list);
            return NULL;
        }
    }

    return list;
}

void free_dictionary_list(DictionaryList *list) {
    if (!list) {
        return;
    }

    if (list->dictionaries) {
        for (size_t i = 0; i < list->count; ++i) {
            free_dictionary(list->dictionaries[i]);
        }
        free(list->dictionaries);
    }
    free(list);
}

int main(void) {
    size_t list_size = 10;
    DictionaryList *list = create_dictionary_list(list_size);
    
    if (!list) {
        return EXIT_FAILURE;
    }

    free_dictionary_list(list);

    return EXIT_SUCCESS;
}