#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 64
#define MAX_ENTRIES 100

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} DictionaryEntry;

typedef struct {
    DictionaryEntry entries[MAX_ENTRIES];
    int count;
} Dictionary;

static size_t safe_strncpy(char *dest, const char *src, size_t dest_size) {
    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return i;
}

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->count <= 0 || dict->count > MAX_ENTRIES) {
        return true;
    }

    const char *first_value = dict->entries[0].value;

    for (int i = 1; i < dict->count; i++) {
        if (strncmp(first_value, dict->entries[i].value, MAX_VALUE_LENGTH - 1) != 0) {
            return false;
        }
    }

    return true;
}

static void set_entry(DictionaryEntry *entry, const char *key, const char *value) {
    if (entry == NULL) {
        return;
    }

    if (key != NULL) {
        safe_strncpy(entry->key, key, MAX_KEY_LENGTH);
    } else {
        entry->key[0] = '\0';
    }

    if (value != NULL) {
        safe_strncpy(entry->value, value, MAX_VALUE_LENGTH);
    } else {
        entry->value[0] = '\0';
    }
}

int main(void) {
    const char *apple_value = "apple";
    const char *orange_value = "orange";
    Dictionary dict;
    dict.count = 0;

    if (dict.count < MAX_ENTRIES) {
        set_entry(&dict.entries[dict.count], "first", apple_value);
        dict.count++;
    }

    if (dict.count < MAX_ENTRIES) {
        set_entry(&dict.entries[dict.count], "second", apple_value);
        dict.count++;
    }

    if (dict.count < MAX_ENTRIES) {
        set_entry(&dict.entries[dict.count], "third", apple_value);
        dict.count++;
    }

    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }

    if (dict.count < MAX_ENTRIES) {
        set_entry(&dict.entries[dict.count], "fourth", orange_value);
        dict.count++;
    }

    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }

    return 0;
}