#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *data;
} Dictionary;

typedef struct {
    Dictionary **dicts;
    size_t count;
} DictList;

DictList* create_dict_list(size_t count) {
    if (count == 0) return NULL;

    DictList *list = (DictList *)malloc(sizeof(DictList));
    if (list == NULL) return NULL;

    list->dicts = (Dictionary **)calloc(count, sizeof(Dictionary *));
    if (list->dicts == NULL) {
        free(list);
        return NULL;
    }

    list->count = count;
    for (size_t i = 0; i < count; ++i) {
        list->dicts[i] = (Dictionary *)malloc(sizeof(Dictionary));
        if (list->dicts[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(list->dicts[j]);
            }
            free(list->dicts);
            free(list);
            return NULL;
        }
        list->dicts[i]->data = NULL;
    }

    return list;
}

void free_dict_list(DictList *list) {
    if (list == NULL) return;

    for (size_t i = 0; i < list->count; ++i) {
        free(list->dicts[i]);
    }
    free(list->dicts);
    free(list);
}

int main() {
    size_t count = 5;
    DictList *list = create_dict_list(count);

    if (list != NULL) {
        for (size_t i = 0; i < list->count; ++i) {
            printf("Dictionary %zu: %p\n", i, (void *)list->dicts[i]);
        }
        free_dict_list(list);
    } else {
        printf("Failed to create dictionary list.\n");
    }

    return 0;
}