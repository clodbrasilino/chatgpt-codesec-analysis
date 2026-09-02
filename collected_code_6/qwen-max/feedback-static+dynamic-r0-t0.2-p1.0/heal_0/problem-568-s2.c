#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *data; // Placeholder for dictionary data
} Dictionary;

typedef struct {
    Dictionary **dictionaries;
    size_t count;
} DictionaryList;

DictionaryList* createEmptyDictionaries(size_t count) {
    if (count == 0) return NULL;

    DictionaryList *list = (DictionaryList *)malloc(sizeof(DictionaryList));
    if (list == NULL) return NULL;

    list->dictionaries = (Dictionary **)calloc(count, sizeof(Dictionary *));
    if (list->dictionaries == NULL) {
        free(list);
        return NULL;
    }

    list->count = count;
    for (size_t i = 0; i < count; ++i) {
        list->dictionaries[i] = (Dictionary *)malloc(sizeof(Dictionary));
        if (list->dictionaries[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(list->dictionaries[j]);
            }
            free(list->dictionaries);
            free(list);
            return NULL;
        }
        list->dictionaries[i]->data = NULL;
    }

    return list;
}

void freeDictionaryList(DictionaryList *list) {
    if (list == NULL) return;

    for (size_t i = 0; i < list->count; ++i) {
        free(list->dictionaries[i]);
    }
    free(list->dictionaries);
    free(list);
}

int main() {
    size_t count = 5;
    DictionaryList *list = createEmptyDictionaries(count);

    if (list != NULL) {
        printf("Created %zu empty dictionaries.\n", list->count);
        freeDictionaryList(list);
    } else {
        printf("Failed to create dictionaries.\n");
    }

    return 0;
}