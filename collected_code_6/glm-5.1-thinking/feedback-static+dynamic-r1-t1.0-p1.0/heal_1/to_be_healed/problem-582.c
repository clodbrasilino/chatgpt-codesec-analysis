#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictEntry {
    char *key;
    int value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dict {
    DictEntry *head;
    size_t size;
} Dict;

static char *duplicate_string(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str) + 1;
    char *new_str = malloc(len);
    if (new_str == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str, str, len);
    return new_str;
}

int dict_is_empty(const Dict *dict) {
    if (dict == NULL) {
        return 1;
    }
    return dict->size == 0;
}

Dict *dict_create(void) {
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

void dict_destroy(Dict *dict) {
    if (dict == NULL) {
        return;
    }
    DictEntry *current = dict->head;
    while (current != NULL) {
        DictEntry *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    free(dict);
}

int dict_insert(Dict *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    DictEntry *entry = malloc(sizeof(DictEntry));
    if (entry == NULL) {
        return -1;
    }
    entry->key = duplicate_string(key);
    if (entry->key == NULL) {
        free(entry);
        return -1;
    }
    entry->value = value;
    entry->next = dict->head;
    dict->head = entry;
    dict->size++;
    return 0;
}

int main(void) {
    Dict *my_dict = dict_create();
    if (my_dict == NULL) {
        return EXIT_FAILURE;
    }
    
    if (dict_is_empty(my_dict)) {
        printf("Dictionary is empty\n");
    }
    
    if (dict_insert(my_dict, "test_key", 42) != 0) {
        dict_destroy(my_dict);
        return EXIT_FAILURE;
    }
    
    if (!dict_is_empty(my_dict)) {
        printf("Dictionary is not empty\n");
    }
    
    dict_destroy(my_dict);
    return EXIT_SUCCESS;
}