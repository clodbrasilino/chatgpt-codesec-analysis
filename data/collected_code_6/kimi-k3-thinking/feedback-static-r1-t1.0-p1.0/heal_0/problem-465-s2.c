#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, s, len);
    }
    return copy;
}

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
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

    if (dict == NULL || key == NULL || dict->size >= dict->capacity) {
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
    size_t read;
    size_t write = 0;

    if (dict == NULL) {
        return;
    }
    for (read = 0; read < dict->size; read++) {
        if (dict->items[read].value != NULL && dict->items[read].value[0] != '\0') {
            if (write != read) {
                dict->items[write] = dict->items[read];
            }
            write++;
        } else {
            free(dict->items[read].key);
            free(dict->items[read].value);
        }
    }
    dict->size = write;
}

void dict_print(const Dictionary *dict) {
    size_t i;

    if (dict == NULL) {
        return;
    }
    printf("{");
    for (i = 0; i < dict->size; i++) {
        printf("'%s': '%s'", dict->items[i].key, dict->items[i].value);
        if (i + 1 < dict->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

void dict_free(Dictionary *dict) {
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
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