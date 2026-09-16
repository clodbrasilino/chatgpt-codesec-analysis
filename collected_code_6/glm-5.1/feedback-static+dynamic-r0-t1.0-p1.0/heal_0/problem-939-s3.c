#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
} Dictionary;

int compare_dictionaries(const void *a, const void *b) {
    const Dictionary *dict_a = (const Dictionary *)a;
    const Dictionary *dict_b = (const Dictionary *)b;
    
    if (dict_a->size == 0 && dict_b->size == 0) return 0;
    if (dict_a->size == 0) return -1;
    if (dict_b->size == 0) return 1;
    
    return strcmp(dict_a->entries[0].key, dict_b->entries[0].key);
}

void sort_dictionaries(Dictionary *list, size_t count) {
    qsort(list, count, sizeof(Dictionary), compare_dictionaries);
}

void free_dictionaries(Dictionary *list, size_t count) {
    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < list[i].size; j++) {
            free(list[i].entries[j].key);
            free(list[i].entries[j].value);
        }
        free(list[i].entries);
    }
    free(list);
}

int main(void) {
    size_t count = 3;
    Dictionary *list = malloc(count * sizeof(Dictionary));
    if (list == NULL) return EXIT_FAILURE;

    list[0].size = 1;
    list[0].entries = malloc(list[0].size * sizeof(DictEntry));
    if (list[0].entries == NULL) {
        free(list);
        return EXIT_FAILURE;
    }
    list[0].entries[0].key = strdup("zebra");
    list[0].entries[0].value = strdup("animal");
    if (list[0].entries[0].key == NULL || list[0].entries[0].value == NULL) {
        free(list[0].entries[0].key);
        free(list[0].entries[0].value);
        free(list[0].entries);
        free(list);
        return EXIT_FAILURE;
    }

    list[1].size = 1;
    list[1].entries = malloc(list[1].size * sizeof(DictEntry));
    if (list[1].entries == NULL) {
        free_dictionaries(list, 1);
        return EXIT_FAILURE;
    }
    list[1].entries[0].key = strdup("apple");
    list[1].entries[0].value = strdup("fruit");
    if (list[1].entries[0].key == NULL || list[1].entries[0].value == NULL) {
        free(list[1].entries[0].key);
        free(list[1].entries[0].value);
        free(list[1].entries);
        free(list[0].entries[0].key);
        free(list[0].entries[0].value);
        free(list[0].entries);
        free(list);
        return EXIT_FAILURE;
    }

    list[2].size = 1;
    list[2].entries = malloc(list[2].size * sizeof(DictEntry));
    if (list[2].entries == NULL) {
        free_dictionaries(list, 2);
        return EXIT_FAILURE;
    }
    list[2].entries[0].key = strdup("mango");
    list[2].entries[0].value = strdup("tropical");
    if (list[2].entries[0].key == NULL || list[2].entries[0].value == NULL) {
        free(list[2].entries[0].key);
        free(list[2].entries[0].value);
        free(list[2].entries);
        free_dictionaries(list, 2);
        return EXIT_FAILURE;
    }

    sort_dictionaries(list, count);

    for (size_t i = 0; i < count; i++) {
        printf("Dictionary %zu (First key: %s, value: %s)\n", i, list[i].entries[0].key, list[i].entries[0].value);
    }

    free_dictionaries(list, count);

    return EXIT_SUCCESS;
}