#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ENTRIES 16
#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 128
#define NUM_DICTS 3

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LEN];
} DictEntry;

typedef struct {
    DictEntry entries[MAX_ENTRIES];
    size_t size;
} Dict;

void dict_init(Dict *dict)
{
    if (dict == NULL) {
        return;
    }
    dict->size = 0;
    memset(dict->entries, 0, sizeof(dict->entries));
}

bool dict_insert(Dict *dict, const char *key, const char *value)
{
    int written;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->size >= MAX_ENTRIES) {
        return false;
    }
    written = snprintf(dict->entries[dict->size].key, MAX_KEY_LEN, "%s", key);
    if (written < 0 || (size_t)written >= MAX_KEY_LEN) {
        return false;
    }
    written = snprintf(dict->entries[dict->size].value, MAX_VALUE_LEN, "%s", value);
    if (written < 0 || (size_t)written >= MAX_VALUE_LEN) {
        return false;
    }
    dict->size++;
    return true;
}

bool dict_is_empty(const Dict *dict)
{
    if (dict == NULL) {
        return false;
    }
    return dict->size == 0;
}

bool all_dicts_empty(const Dict *dicts, size_t count)
{
    size_t i;

    if (count == 0) {
        return true;
    }
    if (dicts == NULL) {
        return false;
    }
    for (i = 0; i < count; i++) {
        if (!dict_is_empty(&dicts[i])) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Dict dicts[NUM_DICTS];
    size_t i;

    for (i = 0; i < NUM_DICTS; i++) {
        dict_init(&dicts[i]);
    }

    if (all_dicts_empty(dicts, NUM_DICTS)) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }

    if (!dict_insert(&dicts[1], "name", "example")) {
        fprintf(stderr, "Error: failed to insert entry.\n");
        return EXIT_FAILURE;
    }

    if (all_dicts_empty(dicts, NUM_DICTS)) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }

    return EXIT_SUCCESS;
}