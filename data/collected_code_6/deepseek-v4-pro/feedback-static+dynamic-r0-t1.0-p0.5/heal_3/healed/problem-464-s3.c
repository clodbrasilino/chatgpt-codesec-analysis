#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

    if (dict->size > MAX_DICT_SIZE) {
        return false;
    }

    const char *first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (strncmp(first_value, dict->entries[i].value, MAX_VALUE_LENGTH) != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    memset(&dict, 0, sizeof(dict));
    dict.size = 0;

    if (dict.size < MAX_DICT_SIZE) {
        strncpy(dict.entries[dict.size].key, "a", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        strncpy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (dict.size < MAX_DICT_SIZE) {
        strncpy(dict.entries[dict.size].key, "b", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        strncpy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (dict.size < MAX_DICT_SIZE) {
        strncpy(dict.entries[dict.size].key, "c", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        strncpy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    if (dict.size < MAX_DICT_SIZE) {
        strncpy(dict.entries[dict.size].key, "d", MAX_KEY_LENGTH - 1);
        dict.entries[dict.size].key[MAX_KEY_LENGTH - 1] = '\0';
        strncpy(dict.entries[dict.size].value, "different", MAX_VALUE_LENGTH - 1);
        dict.entries[dict.size].value[MAX_VALUE_LENGTH - 1] = '\0';
        dict.size++;
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    return 0;
}