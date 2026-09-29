#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** keys;
    size_t size;
} KeyList;

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue* elements;
    size_t size;
} Dictionary;

KeyList get_keys(Dictionary dict) {
    KeyList list;
    list.keys = malloc(dict.size * sizeof(char *));
    if(list.keys == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        list.size = 0;
        return list;
    }

    for(size_t i = 0; i < dict.size; ++i) {
        list.keys[i] = strdup(dict.elements[i].key);
        if(list.keys[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for(size_t j = 0; j < i; ++j) {
                free(list.keys[j]);
            }
            free(list.keys);
            list.size = 0;
            return list;
        }
    }

    list.size = dict.size;
    return list;
}

void free_key_list(KeyList list) {
    for(size_t i = 0; i < list.size; ++i) {
        free(list.keys[i]);
    }
    free(list.keys);
}

int main() {
    Dictionary dict;
    dict.elements = malloc(2 * sizeof(KeyValue));
    if(dict.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    dict.elements[0].key = "Key1";
    dict.elements[0].value = "Value1";
    dict.elements[1].key = "Key2";
    dict.elements[1].value = "Value2";

    dict.size = 2;
	
    KeyList keys = get_keys(dict);
    if(keys.size == 0) {
        free(dict.elements);
        return 1;
    }

    for(size_t i = 0; i < keys.size; ++i) {
        printf("Key[%zu]: %s\n", i, keys.keys[i]);
    }

    free_key_list(keys);
    free(dict.elements);

    return 0;
}