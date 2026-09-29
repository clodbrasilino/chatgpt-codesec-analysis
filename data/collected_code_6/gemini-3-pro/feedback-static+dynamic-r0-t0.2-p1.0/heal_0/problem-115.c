#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
} Dictionary;

bool are_all_dictionaries_empty(const Dictionary* dict_list, size_t num_dicts) {
    if (dict_list == NULL && num_dicts > 0) {
        return false;
    }

    for (size_t i = 0; i < num_dicts; ++i) {
        if (dict_list[i].size > 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    Dictionary dicts[3] = {0};
    
    dicts[0].size = 0;
    dicts[0].pairs = NULL;
    
    dicts[1].size = 0;
    dicts[1].pairs = NULL;
    
    dicts[2].size = 0;
    dicts[2].pairs = NULL;

    bool all_empty = are_all_dictionaries_empty(dicts, 3);
    
    if (all_empty) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }

    dicts[1].size = 1;
    KeyValuePair kv = {1, 100};
    dicts[1].pairs = &kv;

    all_empty = are_all_dictionaries_empty(dicts, 3);
    
    if (all_empty) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }

    return 0;
}