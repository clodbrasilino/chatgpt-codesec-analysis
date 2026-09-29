#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING,
    TYPE_DICT
} ValueType;

typedef struct Dictionary Dictionary;

typedef struct {
    ValueType type;
    union {
        int int_val;
        char *str_val;
        Dictionary *dict_val;
    } value;
} Value;

typedef struct {
    char *key;
    Value val;
} KeyValuePair;

struct Dictionary {
    KeyValuePair *pairs;
    size_t size;
    size_t capacity;
};

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->size = 0;
    dict->capacity = 10;
    dict->pairs = (KeyValuePair*)malloc(dict->capacity * sizeof(KeyValuePair));
    if (!dict->pairs) {
        free(dict);
        return NULL;
    }
    return dict;
}

int add_dictionary_entry(Dictionary *dict, const char *key, Value val) {
    if (!dict || !key) return -1;
    
    if (dict->size == dict->capacity) {
        size_t new_cap = dict->capacity * 2;
        KeyValuePair *new_pairs = (KeyValuePair*)realloc(dict->pairs, new_cap * sizeof(KeyValuePair));
        if (!new_pairs) {
            return -1;
        }
        dict->pairs = new_pairs;
        dict->capacity = new_cap;
    }
    
    char *key_copy = strdup(key);
    if (!key_copy) return -1;
    
    dict->pairs[dict->size].key = key_copy;
    dict->pairs[dict->size].val = val;
    dict->size++;
    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->pairs[i].key);
        if (dict->pairs[i].val.type == TYPE_STRING) {
            free(dict->pairs[i].val.value.str_val);
        } else if (dict->pairs[i].val.type == TYPE_DICT) {
            free_dictionary(dict->pairs[i].val.value.dict_val);
        }
    }
    free(dict->pairs);
    free(dict);
}

int get_dictionary_depth(const Dictionary *dict) {
    if (!dict) return 0;
    
    int max_depth = 0;
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->pairs[i].val.type == TYPE_DICT) {
            int depth = get_dictionary_depth(dict->pairs[i].val.value.dict_val);
            if (depth > max_depth) {
                max_depth = depth;
            }
        }
    }
    return max_depth + 1;
}

int main() {
    Dictionary *dict1 = create_dictionary();
    if (!dict1) return 1;

    Dictionary *dict2 = create_dictionary();
    if (!dict2) {
        free_dictionary(dict1);
        return 1;
    }

    Dictionary *dict3 = create_dictionary();
    if (!dict3) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }

    Value val_int = { .type = TYPE_INT, .value.int_val = 42 };
    add_dictionary_entry(dict3, "key1", val_int);

    Value val_dict3 = { .type = TYPE_DICT, .value.dict_val = dict3 };
    add_dictionary_entry(dict2, "key2", val_dict3);

    Value val_dict2 = { .type = TYPE_DICT, .value.dict_val = dict2 };
    add_dictionary_entry(dict1, "key3", val_dict2);

    int depth = get_dictionary_depth(dict1);
    printf("Depth of dictionary: %d\n", depth);

    free_dictionary(dict1);

    return 0;
}