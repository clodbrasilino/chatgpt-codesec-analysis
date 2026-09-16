#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary {
    char** keys;
    char** values;
    size_t size;
} Dictionary;

typedef struct List {
    Dictionary** dictionaries;
    size_t size;
} List;

Dictionary* create_empty_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->keys = NULL;
    dict->values = NULL;
    dict->size = 0;
    return dict;
}

List* create_list_of_empty_dictionaries(size_t num_dicts) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->dictionaries = (Dictionary**)malloc(num_dicts * sizeof(Dictionary*));
    if (list->dictionaries == NULL) {
        free(list);
        return NULL;
    }

    list->size = num_dicts;

    for (size_t i = 0; i < num_dicts; ++i) {
        list->dictionaries[i] = create_empty_dictionary();
        if (list->dictionaries[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(list->dictionaries[j]);
            }
            free(list->dictionaries);
            free(list);
            return NULL;
        }
    }

    return list;
}

void free_dictionary(Dictionary* dict) {
    if (dict != NULL) {
        free(dict->keys);
        free(dict->values);
        free(dict);
    }
}

void free_list(List* list) {
    if (list != NULL) {
        if (list->dictionaries != NULL) {
            for (size_t i = 0; i < list->size; ++i) {
                free_dictionary(list->dictionaries[i]);
            }
            free(list->dictionaries);
        }
        free(list);
    }
}

int main() {
    size_t num_dicts = 5;
    List* dict_list = create_list_of_empty_dictionaries(num_dicts);

    if (dict_list == NULL) {
        fprintf(stderr, "Failed to create the list of dictionaries.\n");
        return EXIT_FAILURE;
    }

    printf("Successfully created a list of %zu empty dictionaries.\n", dict_list->size);

    free_list(dict_list);

    return EXIT_SUCCESS;
}