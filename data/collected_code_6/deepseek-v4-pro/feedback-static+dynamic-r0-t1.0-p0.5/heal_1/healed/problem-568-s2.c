#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary {
    void *data;
    struct Dictionary *next;
} Dictionary;

typedef struct DictionaryList {
    Dictionary *head;
    size_t count;
} DictionaryList;

DictionaryList *create_empty_dictionary_list(size_t num_dictionaries) {
    DictionaryList *list;
    Dictionary *current;
    Dictionary *new_dict;
    size_t i;

    if (num_dictionaries == 0) {
        return NULL;
    }

    list = (DictionaryList *)malloc(sizeof(DictionaryList));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->count = 0;

    for (i = 0; i < num_dictionaries; i++) {
        new_dict = (Dictionary *)malloc(sizeof(Dictionary));
        if (new_dict == NULL) {
            current = list->head;
            while (current != NULL) {
                Dictionary *next = current->next;
                free(current);
                current = next;
            }
            free(list);
            return NULL;
        }

        new_dict->data = NULL;
        new_dict->next = NULL;

        if (list->head == NULL) {
            list->head = new_dict;
        } else {
            current = list->head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_dict;
        }

        list->count++;
    }

    return list;
}

void free_dictionary_list(DictionaryList *list) {
    Dictionary *current;
    Dictionary *next;

    if (list == NULL) {
        return;
    }

    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int main(void) {
    DictionaryList *dict_list;
    size_t num_dicts = 5;

    dict_list = create_empty_dictionary_list(num_dicts);
    if (dict_list == NULL) {
        fprintf(stderr, "Failed to create dictionary list\n");
        return 1;
    }

    printf("Created %zu empty dictionaries\n", dict_list->count);

    free_dictionary_list(dict_list);

    return 0;
}