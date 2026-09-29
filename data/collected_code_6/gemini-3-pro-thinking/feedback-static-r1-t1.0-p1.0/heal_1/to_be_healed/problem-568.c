#include <stdlib.h>
#include <stdio.h>

typedef struct KeyValuePair {
    char *key;
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::value' is never used. [unusedStructMember]
     */
    void *value;
    struct KeyValuePair *next;
} KeyValuePair;

typedef struct Dictionary {
    KeyValuePair **buckets;
    size_t bucket_count;
} Dictionary;

typedef struct DictionaryList {
    Dictionary **dictionaries;
    size_t length;
} DictionaryList;

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    if (dict->buckets) {
        for (size_t i = 0; i < dict->bucket_count; i++) {
            KeyValuePair *current = dict->buckets[i];
            while (current) {
                KeyValuePair *next = current->next;
                free(current->key);
                free(current);
                current = next;
            }
        }
        free(dict->buckets);
    }
    free(dict);
}

Dictionary* create_empty_dictionary(size_t bucket_count) {
    if (bucket_count == 0) {
        return NULL;
    }
    
    Dictionary *dict = malloc(sizeof(*dict));
    if (!dict) {
        return NULL;
    }
    
    dict->bucket_count = bucket_count;
    dict->buckets = calloc(bucket_count, sizeof(*(dict->buckets)));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    
    return dict;
}

void free_dictionary_list(DictionaryList *list) {
    if (!list) {
        return;
    }
    if (list->dictionaries) {
        for (size_t i = 0; i < list->length; i++) {
            free_dictionary(list->dictionaries[i]);
        }
        free(list->dictionaries);
    }
    free(list);
}

DictionaryList* create_empty_dictionary_list(size_t length, size_t bucket_count) {
    DictionaryList *list = malloc(sizeof(*list));
    if (!list) {
        return NULL;
    }
    
    list->length = length;
    
    if (length == 0) {
        list->dictionaries = NULL;
        return list;
    }
    
    list->dictionaries = calloc(length, sizeof(*(list->dictionaries)));
    if (!list->dictionaries) {
        free(list);
        return NULL;
    }
    
    for (size_t i = 0; i < length; i++) {
        list->dictionaries[i] = create_empty_dictionary(bucket_count);
        if (!list->dictionaries[i]) {
            for (size_t j = 0; j < i; j++) {
                free_dictionary(list->dictionaries[j]);
            }
            free(list->dictionaries);
            free(list);
            return NULL;
        }
    }
    
    return list;
}

int main(void) {
    size_t number_of_dicts = 5;
    size_t bucket_count = 16;
    
    DictionaryList *my_list = create_empty_dictionary_list(number_of_dicts, bucket_count);
    
    if (!my_list) {
        fprintf(stderr, "Failed to create dictionary list\n");
        return EXIT_FAILURE;
    }
    
    free_dictionary_list(my_list);
    
    return EXIT_SUCCESS;
}