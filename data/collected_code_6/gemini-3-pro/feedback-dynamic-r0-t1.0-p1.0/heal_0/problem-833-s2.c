#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValuePair {
    char* key;
    char* value;
    struct KeyValuePair* next;
} KeyValuePair;

typedef struct Dictionary {
    KeyValuePair* head;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        exit(EXIT_FAILURE);
    }
    dict->head = NULL;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return;
    }

    KeyValuePair* new_pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    if (new_pair == NULL) {
        return;
    }

    new_pair->key = strdup(key);
    if (new_pair->key == NULL) {
        free(new_pair);
        return;
    }

    new_pair->value = strdup(value);
    if (new_pair->value == NULL) {
        free(new_pair->key);
        free(new_pair);
        return;
    }

    new_pair->next = dict->head;
    dict->head = new_pair;
}

char** get_dictionary_keys(Dictionary* dict, size_t* num_keys) {
    if (dict == NULL || num_keys == NULL) {
        return NULL;
    }

    size_t count = 0;
    KeyValuePair* current = dict->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    char** keys = (char**)malloc(count * sizeof(char*));
    if (keys == NULL && count > 0) {
        return NULL;
    }

    current = dict->head;
    size_t i = 0;
    while (current != NULL) {
        keys[i] = strdup(current->key);
        if (keys[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        i++;
        current = current->next;
    }

    *num_keys = count;
    return keys;
}

void free_dictionary(Dictionary* dict) {
    if (dict == NULL) {
        return;
    }

    KeyValuePair* current = dict->head;
    while (current != NULL) {
        KeyValuePair* next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(dict);
}

int main() {
    Dictionary* dict = create_dictionary();

    add_to_dictionary(dict, "apple", "red");
    add_to_dictionary(dict, "banana", "yellow");
    add_to_dictionary(dict, "grape", "purple");

    size_t num_keys = 0;
    char** keys = get_dictionary_keys(dict, &num_keys);

    if (keys != NULL) {
        for (size_t i = 0; i < num_keys; i++) {
            printf("%s\n", keys[i]);
            free(keys[i]); 
        }
        free(keys); 
    }

    free_dictionary(dict);

    return 0;
}