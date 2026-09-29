#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 64
#define MAX_DICT_SIZE 100

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} DictEntry;

typedef struct {
    DictEntry entries[MAX_DICT_SIZE];
    int size;
} Dictionary;

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size <= 0) {
        return false;
    }

    const char *first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (strcmp(first_value, dict->entries[i].value) != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    dict.size = 0;

    strcpy(dict.entries[dict.size].key, "a");
    strcpy(dict.entries[dict.size].value, "same");
    dict.size++;

    strcpy(dict.entries[dict.size].key, "b");
    strcpy(dict.entries[dict.size].value, "same");
    dict.size++;

    strcpy(dict.entries[dict.size].key, "c");
    strcpy(dict.entries[dict.size].value, "same");
    dict.size++;

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    strcpy(dict.entries[dict.size].key, "d");
    strcpy(dict.entries[dict.size].value, "different");
    dict.size++;

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    return 0;
}