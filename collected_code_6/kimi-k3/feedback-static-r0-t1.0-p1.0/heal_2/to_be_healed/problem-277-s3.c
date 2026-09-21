#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

int dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0) {
        return -1;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

void dict_free(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
            }
            free(dict->entries);
        }
        dict->entries = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int dict_add(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    char *new_key = malloc(key_len + 1);
    if (new_key == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_key, key, key_len + 1);
    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = value;
    dict->size++;
    return 0;
}

int dict_filter_by_value(const Dictionary *src, Dictionary *dest, int min_value) {
    if (src == NULL || dest == NULL || src->entries == NULL) {
        return -1;
    }
    if (dict_init(dest, src->size) != 0) {
        return -1;
    }
    for (size_t i = 0; i < src->size; i++) {
        if (src->entries[i].value >= min_value) {
            if (dict_add(dest, src->entries[i].key, src->entries[i].value) != 0) {
                dict_free(dest);
                return -1;
            }
        }
    }
    return 0;
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %d\n", dict->entries[i].key, dict->entries[i].value);
    }
}

int main(void) {
    Dictionary dict;
    Dictionary filtered;

    if (dict_init(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&dict, "apple", 5) != 0 ||
        dict_add(&dict, "banana", 12) != 0 ||
        dict_add(&dict, "cherry", 3) != 0 ||
        dict_add(&dict, "date", 8) != 0 ||
        dict_add(&dict, "elderberry", 15) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Original dictionary:\n");
    dict_print(&dict);

    if (dict_filter_by_value(&dict, &filtered, 8) != 0) {
        fprintf(stderr, "Failed to filter dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("\nFiltered dictionary (value >= 8):\n");
    dict_print(&filtered);

    dict_free(&dict);
    dict_free(&filtered);

    return EXIT_SUCCESS;
}