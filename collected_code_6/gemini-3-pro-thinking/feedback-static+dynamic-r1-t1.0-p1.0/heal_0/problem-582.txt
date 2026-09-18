#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t size;
    void** keys;
    void** values;
} Dictionary;

Dictionary* create_dictionary(void);
void destroy_dictionary(Dictionary* dict);
bool is_dictionary_empty(const Dictionary* dict);

Dictionary* create_dictionary(void) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->size = 0;
    dict->keys = NULL;
    dict->values = NULL;
    return dict;
}

void destroy_dictionary(Dictionary* dict) {
    if (dict != NULL) {
        free(dict->keys);
        free(dict->values);
        free(dict);
    }
}

bool is_dictionary_empty(const Dictionary* dict) {
    if (dict == NULL) {
        return true;
    }
    return dict->size == 0;
}

int main(void) {
    Dictionary* dict = create_dictionary();
    if (dict == NULL) {
        return EXIT_FAILURE;
    }

    bool empty_status = is_dictionary_empty(dict);
    printf("%d\n", empty_status);

    destroy_dictionary(dict);
    dict = NULL;

    return EXIT_SUCCESS;
}