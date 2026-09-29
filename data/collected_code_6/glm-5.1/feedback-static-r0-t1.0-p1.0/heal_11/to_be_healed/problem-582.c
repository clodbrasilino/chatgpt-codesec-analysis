#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dictionary_create(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->buckets = calloc(capacity, sizeof(Node *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void dictionary_destroy(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->capacity; i++) {
        Node *current = dict->buckets[i];
        while (current != NULL) {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

bool dictionary_is_valid(const Dictionary *dict) {
    return dict != NULL;
}

bool dictionary_is_empty(const Dictionary *dict) {
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!dictionary_is_valid(dict)) {
        return true;
    }
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Possible null pointer dereference: dict [nullPointer]
     */
    return dict->size == 0;
}

int main(void) {
    Dictionary *dict = dictionary_create(16);
    if (!dictionary_is_valid(dict)) {
        return EXIT_FAILURE;
    }
    
    if (dictionary_is_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    dictionary_destroy(dict);
    /* Possible weaknesses found:
     *  Assignment 'dict=NULL', assigned value is 0
     */
    dict = NULL;

    /* Possible weaknesses found:
     *  Condition '!dictionary_is_valid(dict)' is always true
     *  Calling function 'dictionary_is_valid' returns 0
     *  Condition '!dictionary_is_valid(dict)' is always true [knownConditionTrueFalse]
     */
    if (!dictionary_is_valid(dict)) {
        printf("NULL dictionary is invalid\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'dictionary_is_empty', 1st argument 'dict' value is 0
     */
    if (dictionary_is_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    return EXIT_SUCCESS;
}