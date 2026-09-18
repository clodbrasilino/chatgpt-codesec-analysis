#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t size;
    void *entries;
} Dictionary;

Dictionary* create_dictionary(void);
void destroy_dictionary(Dictionary *dict);
bool is_dictionary_empty(const Dictionary *dict);

Dictionary* create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->size = 0;
    dict->entries = NULL;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->entries != NULL) {
            free(dict->entries);
        }
        free(dict);
    }
}

bool is_dictionary_empty(const Dictionary *dict) {
    if (dict == NULL) {
        return true;
    }
    return dict->size == 0;
}

int main(void) {
    Dictionary *dict = create_dictionary();
    if (dict == NULL) {
        return EXIT_FAILURE;
    }

    if (is_dictionary_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    destroy_dictionary(dict);

    return EXIT_SUCCESS;
}