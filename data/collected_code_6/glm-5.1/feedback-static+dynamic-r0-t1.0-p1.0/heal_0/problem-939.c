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
    
    size_t min_size = dict_a->size < dict_b->size ? dict_a->size : dict_b->size;
    
    for (size_t i = 0; i < min_size; i++) {
        int cmp = strcmp(dict_a->entries[i].key, dict_b->entries[i].key);
        if (cmp != 0) {
            return cmp;
        }
        cmp = strcmp(dict_a->entries[i].value, dict_b->entries[i].value);
        if (cmp != 0) {
            return cmp;
        }
    }
    
    if (dict_a->size < dict_b->size) {
        return -1;
    }
    if (dict_a->size > dict_b->size) {
        return 1;
    }
    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
                free(dict->entries[i].value);
            }
            free(dict->entries);
            dict->entries = NULL;
        }
        dict->size = 0;
    }
}

void sort_dictionaries(Dictionary *dicts, size_t count) {
    qsort(dicts, count, sizeof(Dictionary), compare_dictionaries);
}

int main(void) {
    size_t dict_count = 3;
    Dictionary *dicts = (Dictionary *)malloc(dict_count * sizeof(Dictionary));
    if (dicts == NULL) {
        return EXIT_FAILURE;
    }

    dicts[0].size = 2;
    dicts[0].entries = (DictEntry *)malloc(dicts[0].size * sizeof(DictEntry));
    if (dicts[0].entries == NULL) {
        free(dicts);
        return EXIT_FAILURE;
    }
    dicts[0].entries[0].key = strdup("b");
    if (dicts[0].entries[0].key == NULL) { free(dicts[0].entries); free(dicts); return EXIT_FAILURE; }
    dicts[0].entries[0].value = strdup("2");
    if (dicts[0].entries[0].value == NULL) { free(dicts[0].entries[0].key); free(dicts[0].entries); free(dicts); return EXIT_FAILURE; }
    dicts[0].entries[1].key = strdup("c");
    if (dicts[0].entries[1].key == NULL) { free(dicts[0].entries[0].value); free(dicts[0].entries[0].key); free(dicts[0].entries); free(dicts); return EXIT_FAILURE; }
    dicts[0].entries[1].value = strdup("3");
    if (dicts[0].entries[1].value == NULL) { free(dicts[0].entries[1].key); free(dicts[0].entries[0].value); free(dicts[0].entries[0].key); free(dicts[0].entries); free(dicts); return EXIT_FAILURE; }

    dicts[1].size = 1;
    dicts[1].entries = (DictEntry *)malloc(dicts[1].size * sizeof(DictEntry));
    if (dicts[1].entries == NULL) {
        free_dictionary(&dicts[0]);
        free(dicts);
        return EXIT_FAILURE;
    }
    dicts[1].entries[0].key = strdup("a");
    if (dicts[1].entries[0].key == NULL) { free(dicts[1].entries); free_dictionary(&dicts[0]); free(dicts); return EXIT_FAILURE; }
    dicts[1].entries[0].value = strdup("1");
    if (dicts[1].entries[0].value == NULL) { free(dicts[1].entries[0].key); free(dicts[1].entries); free_dictionary(&dicts[0]); free(dicts); return EXIT_FAILURE; }

    dicts[2].size = 2;
    dicts[2].entries = (DictEntry *)malloc(dicts[2].size * sizeof(DictEntry));
    if (dicts[2].entries == NULL) {
        free_dictionary(&dicts[1]);
        free_dictionary(&dicts[0]);
        free(dicts);
        return EXIT_FAILURE;
    }
    dicts[2].entries[0].key = strdup("b");
    if (dicts[2].entries[0].key == NULL) { free(dicts[2].entries); free_dictionary(&dicts[1]); free_dictionary(&dicts[0]); free(dicts); return EXIT_FAILURE; }
    dicts[2].entries[0].value = strdup("1");
    if (dicts[2].entries[0].value == NULL) { free(dicts[2].entries[0].key); free(dicts[2].entries); free_dictionary(&dicts[1]); free_dictionary(&dicts[0]); free(dicts); return EXIT_FAILURE; }
    dicts[2].entries[1].key = strdup("c");
    if (dicts[2].entries[1].key == NULL) { free(dicts[2].entries[0].value); free(dicts[2].entries[0].key); free(dicts[2].entries); free_dictionary(&dicts[1]); free_dictionary(&dicts[0]); free(dicts); return EXIT_FAILURE; }
    dicts[2].entries[1].value = strdup("3");
    if (dicts[2].entries[1].value == NULL) { free(dicts[2].entries[1].key); free(dicts[2].entries[0].value); free(dicts[2].entries[0].key); free(dicts[2].entries); free_dictionary(&dicts[1]); free_dictionary(&dicts[0]); free(dicts); return EXIT_FAILURE; }

    sort_dictionaries(dicts, dict_count);

    for (size_t i = 0; i < dict_count; i++) {
        for (size_t j = 0; j < dicts[i].size; j++) {
            printf("%s:%s ", dicts[i].entries[j].key, dicts[i].entries[j].value);
        }
        printf("\n");
    }

    for (size_t i = 0; i < dict_count; i++) {
        free_dictionary(&dicts[i]);
    }
    free(dicts);

    return EXIT_SUCCESS;
}