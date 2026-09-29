#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[64];
} DictEntry;

typedef struct {
    DictEntry* entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary* dicts;
    size_t size;
    size_t capacity;
} Tuple;

void dict_free(Dictionary* dict);

void tuple_init(Tuple* tuple) {
    tuple->dicts = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

void dict_init(Dictionary* dict) {
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

bool dict_add_entry(Dictionary* dict, const char* key, const char* value) {
    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        DictEntry* new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (!new_entries) {
            return false;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    snprintf(dict->entries[dict->size].key, sizeof(dict->entries[dict->size].key), "%s", key);
    snprintf(dict->entries[dict->size].value, sizeof(dict->entries[dict->size].value), "%s", value);
    dict->size++;
    return true;
}

bool tuple_add_dict(Tuple* tuple, const Dictionary* dict) {
    if (tuple->size == tuple->capacity) {
        size_t new_capacity = tuple->capacity == 0 ? 4 : tuple->capacity * 2;
        Dictionary* new_dicts = realloc(tuple->dicts, new_capacity * sizeof(Dictionary));
        if (!new_dicts) {
            return false;
        }
        tuple->dicts = new_dicts;
        tuple->capacity = new_capacity;
    }
    dict_init(&tuple->dicts[tuple->size]);
    
    for (size_t i = 0; i < dict->size; i++) {
        if (!dict_add_entry(&tuple->dicts[tuple->size], dict->entries[i].key, dict->entries[i].value)) {
            dict_free(&tuple->dicts[tuple->size]);
            return false;
        }
    }
    
    tuple->size++;
    return true;
}

void dict_free(Dictionary* dict) {
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

void tuple_free(Tuple* tuple) {
    for (size_t i = 0; i < tuple->size; i++) {
        dict_free(&tuple->dicts[i]);
    }
    free(tuple->dicts);
    tuple->dicts = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

int main() {
    Tuple tuple;
    tuple_init(&tuple);
    
    Dictionary dict1;
    dict_init(&dict1);
    
    if (!dict_add_entry(&dict1, "id", "123")) {
        dict_free(&dict1);
        tuple_free(&tuple);
        return 1;
    }
    if (!dict_add_entry(&dict1, "name", "alice")) {
        dict_free(&dict1);
        tuple_free(&tuple);
        return 1;
    }
    
    if (!tuple_add_dict(&tuple, &dict1)) {
        dict_free(&dict1);
        tuple_free(&tuple);
        return 1;
    }
    
    Dictionary dict2;
    dict_init(&dict2);
    
    if (!dict_add_entry(&dict2, "status", "active")) {
        dict_free(&dict1);
        dict_free(&dict2);
        tuple_free(&tuple);
        return 1;
    }
    
    if (!tuple_add_dict(&tuple, &dict2)) {
        dict_free(&dict1);
        dict_free(&dict2);
        tuple_free(&tuple);
        return 1;
    }
    
    for (size_t i = 0; i < tuple.size; i++) {
        printf("Dictionary %zu:\n", i);
        for (size_t j = 0; j < tuple.dicts[i].size; j++) {
            printf("  %s: %s\n", tuple.dicts[i].entries[j].key, tuple.dicts[i].entries[j].value);
        }
    }
    
    dict_free(&dict1);
    dict_free(&dict2);
    tuple_free(&tuple);
    
    return 0;
}