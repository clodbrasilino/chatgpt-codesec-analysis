#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValuePair {
    char *key;
    char *value;
    struct KeyValuePair *next;
} KeyValuePair;

typedef struct Dictionary {
    KeyValuePair *head;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    return dict;
}

int add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    KeyValuePair *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            char *new_value = strdup(value);
            if (new_value == NULL) {
                return -1;
            }
            free(current->value);
            current->value = new_value;
            return 0;
        }
        current = current->next;
    }

    KeyValuePair *new_pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    if (new_pair == NULL) {
        return -1;
    }

    new_pair->key = strdup(key);
    if (new_pair->key == NULL) {
        free(new_pair);
        return -1;
    }

    new_pair->value = strdup(value);
    if (new_pair->value == NULL) {
        free(new_pair->key);
        free(new_pair);
        return -1;
    }

    new_pair->next = dict->head;
    dict->head = new_pair;
    return 0;
}

Dictionary* merge_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }

    Dictionary *merged_dict = create_dictionary();
    if (merged_dict == NULL) {
        return NULL;
    }

    KeyValuePair *current = dict1->head;
    while (current != NULL) {
        if (add_to_dictionary(merged_dict, current->key, current->value) != 0) {
            return NULL;
        }
        current = current->next;
    }

    current = dict2->head;
    while (current != NULL) {
        if (add_to_dictionary(merged_dict, current->key, current->value) != 0) {
            return NULL;
        }
        current = current->next;
    }

    return merged_dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    KeyValuePair *current = dict->head;
    while (current != NULL) {
        KeyValuePair *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(dict);
}

void print_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    KeyValuePair *current = dict->head;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}

int main() {
    Dictionary *dict1 = create_dictionary();
    if (dict1 == NULL) {
        return 1;
    }

    Dictionary *dict2 = create_dictionary();
    if (dict2 == NULL) {
        free_dictionary(dict1);
        return 1;
    }

    if (add_to_dictionary(dict1, "apple", "red") != 0 ||
        add_to_dictionary(dict1, "banana", "yellow") != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }

    if (add_to_dictionary(dict2, "banana", "green") != 0 ||
        add_to_dictionary(dict2, "grape", "purple") != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }

    Dictionary *merged = merge_dictionaries(dict1, dict2);
    if (merged == NULL) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }

    print_dictionary(merged);

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged);

    return 0;
}