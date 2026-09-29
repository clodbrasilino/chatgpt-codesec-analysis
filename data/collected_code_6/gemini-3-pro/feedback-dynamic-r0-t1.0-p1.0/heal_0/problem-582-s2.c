#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct {
    Node** table;
    size_t size;
    size_t count;
} Dictionary;

Dictionary* create_dictionary(size_t size) {
    if (size == 0) {
        return NULL;
    }

    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->table = (Node**)calloc(size, sizeof(Node*));
    if (!dict->table) {
        free(dict);
        return NULL;
    }

    dict->size = size;
    dict->count = 0;
    return dict;
}

void destroy_dictionary(Dictionary* dict) {
    if (!dict) {
        return;
    }

    for (size_t i = 0; i < dict->size; i++) {
        Node* current = dict->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(dict->table);
    free(dict);
}

bool is_dictionary_empty(const Dictionary* dict) {
    if (!dict) {
        return true;
    }
    return dict->count == 0;
}

int main(void) {
    Dictionary* dict = create_dictionary(10);
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (is_dictionary_empty(dict)) {
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }

    destroy_dictionary(dict);
    return EXIT_SUCCESS;
}