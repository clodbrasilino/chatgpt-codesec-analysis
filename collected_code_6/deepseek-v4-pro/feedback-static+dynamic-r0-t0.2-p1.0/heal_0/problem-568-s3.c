#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary {
    void *data;
    struct Dictionary *next;
} Dictionary;

typedef struct DictionaryList {
    Dictionary *head;
    size_t size;
} DictionaryList;

DictionaryList *create_empty_dictionary_list(size_t count) {
    DictionaryList *list = (DictionaryList *)malloc(sizeof(DictionaryList));
    if (list == NULL) {
        return NULL;
    }
    
    list->head = NULL;
    list->size = 0;
    
    for (size_t i = 0; i < count; i++) {
        Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
        if (dict == NULL) {
            Dictionary *current = list->head;
            while (current != NULL) {
                Dictionary *next = current->next;
                free(current);
                current = next;
            }
            free(list);
            return NULL;
        }
        
        dict->data = NULL;
        dict->next = list->head;
        list->head = dict;
        list->size++;
    }
    
    return list;
}

void free_dictionary_list(DictionaryList *list) {
    if (list == NULL) {
        return;
    }
    
    Dictionary *current = list->head;
    while (current != NULL) {
        Dictionary *next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

int main(void) {
    DictionaryList *list = create_empty_dictionary_list(5);
    
    if (list == NULL) {
        fprintf(stderr, "Failed to create dictionary list\n");
        return EXIT_FAILURE;
    }
    
    printf("Created list with %zu dictionaries\n", list->size);
    
    free_dictionary_list(list);
    
    return EXIT_SUCCESS;
}