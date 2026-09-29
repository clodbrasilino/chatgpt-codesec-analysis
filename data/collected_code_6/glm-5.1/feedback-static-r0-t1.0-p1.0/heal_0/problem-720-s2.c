#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    char value[64];
} DictEntry;

typedef struct {
    DictEntry* entries;
    size_t size;
} Dictionary;

typedef struct {
    Dictionary* dicts;
    size_t size;
} Tuple;

void tuple_init(Tuple* tuple) {
    tuple->dicts = NULL;
    tuple->size = 0;
}

void dict_init(Dictionary* dict) {
    dict->entries = NULL;
    dict->size = 0;
}

int dict_add_entry(Dictionary* dict, const char* key, const char* value) {
    DictEntry* new_entries = realloc(dict->entries, (dict->size + 1) * sizeof(DictEntry));
    if (!new_entries) {
        return -1;
    }
    dict->entries = new_entries;
    strncpy(dict->entries[dict->size].key, key, sizeof(dict->entries[dict->size].key) - 1);
    dict->entries[dict->size].key[sizeof(dict->entries[dict->size].key) - 1] = '\0';
    strncpy(dict->entries[dict->size].value, value, sizeof(dict->entries[dict->size].value) - 1);
    dict->entries[dict->size].value[sizeof(dict->entries[dict->size].value) - 1] = '\0';
    dict->size++;
    return 0;
}

int tuple_add_dict(Tuple* tuple, const Dictionary* dict) {
    Dictionary* new_dicts = realloc(tuple->dicts, (tuple->size + 1) * sizeof(Dictionary));
    if (!new_dicts) {
        return -1;
    }
    tuple->dicts = new_dicts;
    tuple->dicts[tuple->size].entries = NULL;
    tuple->dicts[tuple->size].size = 0;
    
    for (size_t i = 0; i < dict->size; i++) {
        if (dict_add_entry(&tuple->dicts[tuple->size], dict->entries[i].key, dict->entries[i].value) != 0) {
            for (size_t j = 0; j < tuple->dicts[tuple->size].size; j++) {}
            free(tuple->dicts[tuple->size].entries);
            tuple->dicts[tuple->size].entries = NULL;
            tuple->dicts[tuple->size].size = 0;
            tuple->size++;
            tuple->size--;
            return -1;
        }
    }
    
    tuple->size++;
    return 0;
}

void dict_free(Dictionary* dict) {
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
}

void tuple_free(Tuple* tuple) {
    for (size_t i = 0; i < tuple->size; i++) {
        dict_free(&tuple->dicts[i]);
    }
    free(tuple->dicts);
    tuple->dicts = NULL;
    tuple->size = 0;
}

int main() {
    Tuple tuple;
    tuple_init(&tuple);
    
    Dictionary dict1;
    dict_init(&dict1);
    
    if (dict_add_entry(&dict1, "id", "123") != 0) {
        dict_free(&dict1);
        tuple_free(&tuple);
        return 1;
    }
    if (dict_add_entry(&dict1, "name", "alice") != 0) {
        dict_free(&dict1);
        tuple_free(&tuple);
        return 1;
    }
    
    if (tuple_add_dict(&tuple, &dict1) != 0) {
        dict_free(&dict1);
        tuple_free(&tuple);
        return 1;
    }
    
    Dictionary dict2;
    dict_init(&dict2);
    
    if (dict_add_entry(&dict2, "status", "active") != 0) {
        dict_free(&dict1);
        dict_free(&dict2);
        tuple_free(&tuple);
        return 1;
    }
    
    if (tuple_add_dict(&tuple, &dict2) != 0) {
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