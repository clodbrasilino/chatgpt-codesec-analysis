#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue *head;
} Dictionary;

int sum_dictionary_values(const Dictionary *dict) {
    int sum = 0;
    KeyValue *current = dict->head;
    while (current != NULL) {
        sum += current->value;
        current = current->next;
    }
    return sum;
}

Dictionary *create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    return dict;
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return 0;
    }
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return 0;
    }
    new_pair->key = (char *)malloc(strlen(key) + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        return 0;
    }
    strcpy(new_pair->key, key);
    new_pair->value = value;
    new_pair->next = dict->head;
    dict->head = new_pair;
    return 1;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    KeyValue *current = dict->head;
    while (current != NULL) {
        KeyValue *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary();
    if (dict == NULL) {
        return 1;
    }

    if (!dictionary_insert(dict, "one", 1) ||
        !dictionary_insert(dict, "two", 2) ||
        !dictionary_insert(dict, "three", 3)) {
        free_dictionary(dict);
        return 1;
    }

    int total = sum_dictionary_values(dict);

    free_dictionary(dict);

    return total;
}