#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    void *value;
} DictionaryElement;

typedef struct {
    DictionaryElement *elements;
    int size;
} Dictionary;

Dictionary* create_dictionary(int size) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->size = size;
    dict->elements = (DictionaryElement*)calloc(size, sizeof(DictionaryElement));
    if (dict->elements == NULL) {
        free(dict);
        return NULL;
    }
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        free(dict->elements[i].key);
        free(dict->elements[i].value);
    }
    free(dict->elements);
    free(dict);
}

void* get_element_by_index(Dictionary *dict, int index) {
    if (index < 0 || index >= dict->size) return NULL;
    return dict->elements[index].value;
}

int main() {
    Dictionary *dict = create_dictionary(3);
    if (dict == NULL) return -1;

    dict->elements[0].key = strdup("one");
    dict->elements[0].value = (void*)"Value One";
    dict->elements[1].key = strdup("two");
    dict->elements[1].value = (void*)"Value Two";
    dict->elements[2].key = strdup("three");
    dict->elements[2].value = (void*)"Value Three";

    void *value = get_element_by_index(dict, 1);
    if (value != NULL) {
        printf("%s\n", (char*)value);
    }

    destroy_dictionary(dict);
    return 0;
}