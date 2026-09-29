#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static char *dict_string_dup(const char *src)
{
    const char *terminator;
    size_t length;
    char *copy;

    terminator = memchr(src, '\0', DICT_MAX_STRING_LEN);
    if (terminator == NULL) {
        return NULL;
    }
    length = (size_t)(terminator - src);
    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, length + 1);
    return copy;
}

int dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL || capacity == 0) {
        return -1;
    }
    dict->items = calloc(capacity, sizeof(DictItem));
    if (dict->items == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy = NULL;

    if (dict == NULL || key == NULL || dict->items == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        return -1;
    }
    key_copy = dict_string_dup(key);
    if (key_copy == NULL) {
        return -1;
    }
    if (value != NULL) {
        value_copy = dict_string_dup(value);
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

void dict_drop_empty(Dictionary *dict)
{
    size_t write_index = 0;

    if (dict == NULL || dict->items == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->items[i].value == NULL || dict->items[i].value[0] == '\0') {
            free(dict->items[i].key);
            free(dict->items[i].value);
            dict->items[i].key = NULL;
            dict->items[i].value = NULL;
        } else {
            if (write_index != i) {
                dict->items[write_index] = dict->items[i];
                dict->items[i].key = NULL;
                dict->items[i].value = NULL;
            }
            write_index++;
        }
    }
    dict->size = write_index;
}

void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->items != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->items[i].key);
            free(dict->items[i].value);
        }
        free(dict->items);
        dict->items = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

void dict_print(const Dictionary *dict)
{
    if (dict == NULL || dict->items == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n",
               dict->items[i].key != NULL ? dict->items[i].key : "(null)",
               dict->items[i].value != NULL ? dict->items[i].value : "(null)");
    }
}

int main(void)
{
    Dictionary dict;

    if (dict_init(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    if (dict_add(&dict, "name", "John") != 0 ||
        dict_add(&dict, "age", "") != 0 ||
        dict_add(&dict, "city", "New York") != 0 ||
        dict_add(&dict, "country", NULL) != 0 ||
        dict_add(&dict, "email", "john@example.com") != 0) {
        fprintf(stderr, "Failed to add item to dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    printf("Before dropping empty items:\n");
    dict_print(&dict);
    dict_drop_empty(&dict);
    printf("\nAfter dropping empty items:\n");
    dict_print(&dict);
    dict_free(&dict);
    return EXIT_SUCCESS;
}