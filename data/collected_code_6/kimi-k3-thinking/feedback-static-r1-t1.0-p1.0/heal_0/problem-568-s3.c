#include <stdio.h>
#include <stdlib.h>

#define DICT_INITIAL_CAPACITY 16

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(void)
{
    Dictionary *dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = calloc(DICT_INITIAL_CAPACITY, sizeof(*dict->entries));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = DICT_INITIAL_CAPACITY;
    return dict;
}

void dict_destroy(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

Dictionary **create_dict_list(size_t count)
{
    if (count == 0) {
        return NULL;
    }
    Dictionary **list = calloc(count, sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        list[i] = dict_create();
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                dict_destroy(list[j]);
            }
            free(list);
            return NULL;
        }
    }
    return list;
}

void destroy_dict_list(Dictionary **list, size_t count)
{
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        dict_destroy(list[i]);
    }
    free(list);
}

int main(void)
{
    const size_t count = 5;
    Dictionary **dicts = create_dict_list(count);
    if (dicts == NULL) {
        fprintf(stderr, "Error: failed to create dictionary list\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < count; i++) {
        printf("Dictionary %zu created: size=%zu capacity=%zu\n",
               i, dicts[i]->size, dicts[i]->capacity);
    }
    destroy_dict_list(dicts, count);
    return EXIT_SUCCESS;
}