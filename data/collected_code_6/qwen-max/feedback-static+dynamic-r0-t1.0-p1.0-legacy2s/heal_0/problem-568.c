#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char value[256];
} Dictionary;

typedef struct {
    Dictionary **dicts;
    size_t count;
} DictList;

DictList* create_empty_dicts(size_t num) {
    DictList *list = (DictList*)malloc(sizeof(DictList));
    if (!list) return NULL;

    list->dicts = (Dictionary**)calloc(num, sizeof(Dictionary*));
    if (!list->dicts) {
        free(list);
        return NULL;
    }

    list->count = num;
    for (size_t i = 0; i < num; ++i) {
        list->dicts[i] = (Dictionary*)calloc(1, sizeof(Dictionary));
        if (!list->dicts[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(list->dicts[j]);
            }
            free(list->dicts);
            free(list);
            return NULL;
        }
    }
    return list;
}

void free_dict_list(DictList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        free(list->dicts[i]);
    }
    free(list->dicts);
    free(list);
}

int main() {
    DictList *my_dict_list = create_empty_dicts(5);
    if (my_dict_list == NULL) {
        fprintf(stderr, "Failed to create dictionary list\n");
        return 1;
    }

    free_dict_list(my_dict_list);
    return 0;
}