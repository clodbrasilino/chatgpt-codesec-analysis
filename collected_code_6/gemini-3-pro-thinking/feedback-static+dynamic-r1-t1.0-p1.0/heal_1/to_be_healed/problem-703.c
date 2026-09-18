#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    const char *key;
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::value' is never used. [unusedStructMember]
     */
    int value;
} KeyValuePair;

typedef struct {
    const KeyValuePair *items;
    size_t size;
} Dictionary;

bool contains_key(const Dictionary *dict, const char *key);

bool contains_key(const Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL || dict->items == NULL) {
        return false;
    }

    for (size_t i = 0; i < dict->size; i++) {
        if (dict->items[i].key != NULL && strcmp(dict->items[i].key, key) == 0) {
            return true;
        }
    }

    return false;
}

int main(void) {
    KeyValuePair pairs[] = {
        {"apple", 1},
        {"banana", 2},
        {"orange", 3}
    };

    Dictionary dict = {
        .items = pairs,
        .size = sizeof(pairs) / sizeof(pairs[0])
    };

    const char *search_key_1 = "banana";
    const char *search_key_2 = "grape";

    bool found_1 = contains_key(&dict, search_key_1);
    bool found_2 = contains_key(&dict, search_key_2);
    bool found_3 = contains_key(&dict, NULL);
    /* Possible weaknesses found:
     *  Assignment 'found_4=contains_key(NULL,search_key_1)', assigned value is 0
     *  Calling function 'contains_key' returns 0
     */
    bool found_4 = contains_key(NULL, search_key_1);

    printf("%s: %s\n", search_key_1, found_1 ? "true" : "false");
    printf("%s: %s\n", search_key_2, found_2 ? "true" : "false");
    printf("NULL key: %s\n", found_3 ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'found_4' is always false [knownConditionTrueFalse]
     *  Condition 'found_4' is always false
     */
    printf("NULL dict: %s\n", found_4 ? "true" : "false");

    return EXIT_SUCCESS;
}