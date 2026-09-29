#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DICT_MAX_STRING_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

static size_t str_bounded_len(const char *s, size_t max_len) {
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static char *str_dup(const char *s) {
    size_t len;
    size_t i;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = str_bounded_len(s, DICT_MAX_STRING_LEN);
    if (len >= SIZE_MAX) {
        return NULL;
    }
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    for (i = 0; i < len; i++) {
        copy[i] = s[i];
    }
    copy[len] = '\0';
    return copy;
}

static int dict_index_in_bounds(const Dictionary *dict, size_t index) {
    return dict != NULL && dict->items != NULL && index < dict->capacity;
}

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict;

    if (capacity > SIZE_MAX / sizeof(DictItem)) {
        return NULL;
    }
    dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    if (capacity > 0) {
        dict->items = calloc(capacity, sizeof(DictItem));
        if (dict->items == NULL) {
            free(dict);
            return NULL;
        }
    } else {
        dict->items = NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    char *key_copy;
    char *value_copy = NULL;

    if (dict == NULL || key == NULL) {
        return -1;
    }
    if (dict->items == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    if (!dict_index_in_bounds(dict, dict->size)) {
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
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    size_t read;
    size_t limit;

    if (dict == NULL || dict->items == NULL || dict->capacity == 0) {
        return;
    }

    limit = dict->size;
    if (limit > dict->capacity) {
        limit = dict->capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (read = 0; read < limit && write < dict->capacity; read++) {
        DictItem *item;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!dict_index_in_bounds(dict, read)) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        item = &dict->items[read];

        if (item->value != NULL && item->value[0] != '\0') {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (write != read) {
                if (!dict_index_in_bounds(dict, write)) {
                    break;
                }
                dict->items[write].key = item->key;
                dict->items[write].value = item->value;
                item->key = NULL;
                item->value = NULL;
            }
            write++;
        } else {
            free(item->key);
            free(item->value);
            item->key = NULL;
            item->value = NULL;
        }
    }

    if (write > dict->capacity) {
        write = dict->capacity;
    }
    dict->size = write;
}

void dict_print(const Dictionary *dict) {
    size_t limit;
    size_t i;

    if (dict == NULL || dict->items == NULL) {
        return;
    }
    limit = dict->size;
    if (limit > dict->capacity) {
        limit = dict->capacity;
    }
    printf("{");
    for (i = 0; i < limit; i++) {
        if (!dict_index_in_bounds(dict, i)) {
            break;
        }
        printf("'%s': '%s'",
               dict->items[i].key != NULL ? dict->items[i].key : "(null)",
               dict->items[i].value != NULL ? dict->items[i].value : "(null)");
        if (i + 1 < limit) {
            printf(", ");
        }
    }
    printf("}\n");
}

void dict_free(Dictionary *dict) {
    /* Possible weaknesses found:
     *  The scope of the variable 'limit' can be reduced. [variableScope]
     */
    size_t limit;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (dict == NULL) {
        return;
    }
    if (dict->items != NULL) {
        limit = dict->size;
        if (limit > dict->capacity) {
            limit = dict->capacity;
        }
        for (i = 0; i < limit; i++) {
            if (!dict_index_in_bounds(dict, i)) {
                break;
            }
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