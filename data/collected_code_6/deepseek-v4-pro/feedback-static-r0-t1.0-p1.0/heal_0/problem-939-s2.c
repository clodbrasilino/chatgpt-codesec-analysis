#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Dictionary;

typedef struct {
    Dictionary *items;
    size_t count;
    size_t capacity;
} DictionaryList;

static int compare_dictionaries(const void *a, const void *b) {
    const Dictionary *dict_a = (const Dictionary *)a;
    const Dictionary *dict_b = (const Dictionary *)b;
    int key_cmp = strcmp(dict_a->key, dict_b->key);
    if (key_cmp != 0) {
        return key_cmp;
    }
    return strcmp(dict_a->value, dict_b->value);
}

static int dictionary_list_init(DictionaryList *list, size_t initial_capacity) {
    if (!list || initial_capacity == 0) {
        return -1;
    }
    list->items = (Dictionary *)malloc(initial_capacity * sizeof(Dictionary));
    if (!list->items) {
        return -1;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return 0;
}

static int dictionary_list_add(DictionaryList *list, const char *key, const char *value) {
    if (!list || !key || !value) {
        return -1;
    }
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Dictionary *new_items = (Dictionary *)realloc(list->items, new_capacity * sizeof(Dictionary));
        if (!new_items) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    char *key_copy = strdup(key);
    char *value_copy = strdup(value);
    if (!key_copy || !value_copy) {
        free(key_copy);
        free(value_copy);
        return -1;
    }
    list->items[list->count].key = key_copy;
    list->items[list->count].value = value_copy;
    list->count++;
    return 0;
}

static void dictionary_list_free(DictionaryList *list) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i].key);
        free(list->items[i].value);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int sort_dictionary_list(DictionaryList *list) {
    if (!list || !list->items || list->count == 0) {
        return -1;
    }
    qsort(list->items, list->count, sizeof(Dictionary), compare_dictionaries);
    return 0;
}

int main(void) {
    DictionaryList list;
    if (dictionary_list_init(&list, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary list\n");
        return EXIT_FAILURE;
    }

    if (dictionary_list_add(&list, "banana", "yellow") != 0 ||
        dictionary_list_add(&list, "apple", "red") != 0 ||
        dictionary_list_add(&list, "cherry", "red") != 0 ||
        dictionary_list_add(&list, "date", "brown") != 0 ||
        dictionary_list_add(&list, "elderberry", "purple") != 0) {
        fprintf(stderr, "Failed to add dictionary entries\n");
        dictionary_list_free(&list);
        return EXIT_FAILURE;
    }

    if (sort_dictionary_list(&list) != 0) {
        fprintf(stderr, "Failed to sort dictionary list\n");
        dictionary_list_free(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; i++) {
        printf("%s: %s\n", list.items[i].key, list.items[i].value);
    }

    dictionary_list_free(&list);
    return EXIT_SUCCESS;
}