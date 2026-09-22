#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t size;
} Dictionary;

bool are_all_dictionaries_empty(const Dictionary *dict_list, size_t num_dicts) {
    if (dict_list == NULL) {
        return true; 
    }

    for (size_t i = 0; i < num_dicts; ++i) {
        if (dict_list[i].size > 0) {
            return false;
        }
    }

    return true;
}

void print_dictionary(const Dictionary *dict) {
    for (size_t i = 0; i < dict->size; ++i) {
        printf("  %s: %s\n", dict->items[i].key, dict->items[i].value);
    }
}

int main() {
    Dictionary empty_dict = {NULL, 0};
    
    KeyValuePair item1 = {"key1", "value1"};
    Dictionary non_empty_dict = {&item1, 1};

    Dictionary list1[] = {empty_dict, empty_dict, empty_dict};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    Dictionary list2[] = {empty_dict, non_empty_dict, empty_dict};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    if (are_all_dictionaries_empty(list1, size1)) {
        printf("List 1: All dictionaries are empty.\n");
    } else {
        printf("List 1: Not all dictionaries are empty.\n");
    }

    if (are_all_dictionaries_empty(list2, size2)) {
        printf("List 2: All dictionaries are empty.\n");
    } else {
        printf("List 2: Not all dictionaries are empty.\n");
        for (size_t i = 0; i < size2; ++i) {
            if (list2[i].size > 0) {
                print_dictionary(&list2[i]);
            }
        }
    }

    return 0;
}