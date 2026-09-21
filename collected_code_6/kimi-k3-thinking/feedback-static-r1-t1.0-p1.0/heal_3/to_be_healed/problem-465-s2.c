#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STR_DUP_MAX_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

static char *str_dup(const char *s) {
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strnlen(s, STR_DUP_MAX_LEN + 1);
    if (len > STR_DUP_MAX_LEN) {
        return NULL;
    }
    copy = malloc(len + 1);
    if (copy != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, s, len);
        copy[len] = '\0';
    }
    return copy;
}

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(DictItem)) {
        return NULL;
    }
    dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->items = malloc(capacity * sizeof(DictItem));
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    char *key_copy;
    char *value_copy = NULL;

    if (dict == NULL || dict->items == NULL || key == NULL ||
        dict->size >= dict->capacity) {
        return -1;
    }
    key_copy = str_dup(key);
    if (key_copy == NULL) {
        return -1;
    }
    if (value != NULL) {
        value_copy = str_dup(value);
        if (value_copy == NULL) {
            free(key_copy);
            return -1;
        }
    }
    dict->items[dict->size].key = key_copy;
    dict->items[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

void dict_drop_empty(Dictionary *dict) {
    size_t write = 0;

    if (dict == NULL || dict->items == NULL) {
        return;
    }
    if (dict->size > dict->capacity) {
        dict->size = dict->capacity;
    }
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t read = 0; read < dict->size; read++) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (dict->items[read].value != NULL &&
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            dict->items[read].value[0] != '\0') {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (write != read) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                dict->items[write] = dict->items[read];
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                dict->items[read].key = NULL;
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                dict->items[read].value = NULL;
            }
            write++;
        } else {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            free(dict->items[read].key);
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            dict->items[read].key = NULL;
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            free(dict->items[read].value);
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            dict->items[read].value = NULL;
        }
    }
    dict->size = write;
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL || dict->items == NULL) {
        return;
    }
    size_t count = dict->size;
    if (count > dict->capacity) {
        count = dict->capacity;
    }
    printf("{");
    for (size_t i = 0; i < count; i++) {
        const char *key = dict->items[i].key != NULL ? dict->items[i].key : "(null)";
        const char *value = dict->items[i].value != NULL ? dict->items[i].value : "(null)";
        printf("'%s': '%s'", key, value);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("}\n");
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    if (dict->items != NULL) {
        size_t count = dict->size;
        if (count > dict->capacity) {
            count = dict->capacity;
        }
        for (size_t i = 0; i < count; i++) {
            free(dict->items[i].key);
            dict->items[i].key = NULL;
            free(dict->items[i].value);
            dict->items[i].value = NULL;
        }
        free(dict->items);
        dict->items = NULL;
    }
    free(dict);
}

int main(void) {
    Dictionary *dict = dict_create(10);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(dict, "name", "Alice") != 0 ||
        dict_add(dict, "age", "") != 0 ||
        dict_add(dict, "city", "New York") != 0 ||
        dict_add(dict, "email", NULL) != 0 ||
        dict_add(dict, "country", "USA") != 0) {
        fprintf(stderr, "Failed to add item\n");
        dict_free(dict);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    dict_print(dict);

    dict_drop_empty(dict);

    printf("After: ");
    dict_print(dict);

    dict_free(dict);
    return EXIT_SUCCESS;
}