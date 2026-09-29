#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    char *value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue *head;
    int size;
} Dictionary;

void dict_init(Dictionary *dict) {
    dict->head = NULL;
    dict->size = 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    KeyValue *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            if (current->value == NULL) {
                return -1;
            }
            return 0;
        }
        current = current->next;
    }

    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return -1;
    }

    new_pair->key = strdup(key);
    new_pair->value = strdup(value);
    if (new_pair->key == NULL || new_pair->value == NULL) {
        free(new_pair->key);
        free(new_pair->value);
        free(new_pair);
        return -1;
    }

    new_pair->next = dict->head;
    dict->head = new_pair;
    dict->size++;
    return 0;
}

char *dict_get_by_index(Dictionary *dict, int index) {
    if (dict == NULL || index < 0 || index >= dict->size) {
        return NULL;
    }

    KeyValue *current = dict->head;
    int current_index = 0;
    while (current != NULL) {
        if (current_index == index) {
            return current->value;
        }
        current = current->next;
        current_index++;
    }
    return NULL;
}

char *dict_get_key_by_index(Dictionary *dict, int index) {
    if (dict == NULL || index < 0 || index >= dict->size) {
        return NULL;
    }

    KeyValue *current = dict->head;
    int current_index = 0;
    while (current != NULL) {
        if (current_index == index) {
            return current->key;
        }
        current = current->next;
        current_index++;
    }
    return NULL;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    KeyValue *current = dict->head;
    while (current != NULL) {
        KeyValue *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    dict->head = NULL;
    dict->size = 0;
}

int main(void) {
    Dictionary dict;
    dict_init(&dict);

    dict_add(&dict, "name", "John");
    dict_add(&dict, "age", "30");
    dict_add(&dict, "city", "New York");

    for (int i = 0; i < dict.size; i++) {
        char *key = dict_get_key_by_index(&dict, i);
        char *value = dict_get_by_index(&dict, i);
        if (key != NULL && value != NULL) {
            printf("%s: %s\n", key, value);
        }
    }

    char *value_at_1 = dict_get_by_index(&dict, 1);
    if (value_at_1 != NULL) {
        printf("Value at index 1: %s\n", value_at_1);
    }

    /* Possible weaknesses found:
     *  Variable 'invalid_value' can be declared as pointer to const [constVariablePointer]
     */
    char *invalid_value = dict_get_by_index(&dict, 10);
    if (invalid_value == NULL) {
        printf("Invalid index returns NULL\n");
    }

    dict_free(&dict);
    return 0;
}