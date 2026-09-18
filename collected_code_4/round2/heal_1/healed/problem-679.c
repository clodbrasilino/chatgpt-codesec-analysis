#include <stdlib.h>
#include <stdio.h>

#define DICTIONARY_SIZE 10

typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair pairs[DICTIONARY_SIZE];
    size_t size;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dictionary = malloc(sizeof(Dictionary));
    if (dictionary == NULL) {
        printf("Failed to allocate memory for dictionary.\n");
        exit(EXIT_FAILURE);
    }
    dictionary->size = 0;
    return dictionary;
}

void delete_dictionary(Dictionary* dictionary) {
    free(dictionary);
}

void add_to_dictionary(Dictionary* dictionary, int key, int value) {
    if(dictionary->size < DICTIONARY_SIZE) {
        dictionary->pairs[dictionary->size].key = key;
        dictionary->pairs[dictionary->size].value = value;
        dictionary->size += 1;
    } else {
        printf("Dictionary is full. Cannot add new key-value pair.\n");
        exit(EXIT_FAILURE);
    }
}

int get_value_by_index(Dictionary* dictionary, int index) {
    if(index < 0 || index >= dictionary->size) {
        printf("Index out of range.\n");
        exit(EXIT_FAILURE);
    }
    return dictionary->pairs[index].value;
}

int main() {
    Dictionary* dictionary = create_dictionary();
    add_to_dictionary(dictionary, 1, 100);
    add_to_dictionary(dictionary, 2, 200);
    int value = get_value_by_index(dictionary, 1);
    printf("Value: %d\n", value);
    delete_dictionary(dictionary);
    return 0;
}
