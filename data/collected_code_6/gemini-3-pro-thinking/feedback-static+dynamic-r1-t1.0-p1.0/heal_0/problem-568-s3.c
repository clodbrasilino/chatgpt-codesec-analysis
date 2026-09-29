#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
} Dictionary;

typedef struct {
    Dictionary *items;
    size_t count;
} DictionaryList;

DictionaryList* create_empty_dictionary_list(size_t count);
void free_dictionary_list(DictionaryList *list);

DictionaryList* create_empty_dictionary_list(size_t count) {
    DictionaryList *list = (DictionaryList*)malloc(sizeof(DictionaryList));
    if (list == NULL) {
        return NULL;
    }

    if (count == 0) {
        list->items = NULL;
        list->count = 0;
        return list;
    }

    list->items = (Dictionary*)calloc(count, sizeof(Dictionary));
    if (list->items == NULL) {
        free(list);
        return NULL;
    }

    list->count = count;
    return list;
}

void free_dictionary_list(DictionaryList *list) {
    if (list == NULL) {
        return;
    }
    
    if (list->items != NULL) {
        free(list->items);
    }
    
    free(list);
}

int main(void) {
    size_t list_size = 10;
    DictionaryList *my_list = create_empty_dictionary_list(list_size);
    
    if (my_list == NULL) {
        fprintf(stderr, "Failed to allocate memory for dictionary list.\n");
        return EXIT_FAILURE;
    }

    free_dictionary_list(my_list);

    return EXIT_SUCCESS;
}