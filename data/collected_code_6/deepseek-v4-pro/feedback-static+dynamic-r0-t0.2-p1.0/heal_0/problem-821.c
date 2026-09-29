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

Dictionary *create_dict(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

void dict_set(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return;
    }

    KeyValue *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            if (current->value == NULL) {
                return;
            }
            return;
        }
        current = current->next;
    }

    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return;
    }
    new_pair->key = strdup(key);
    new_pair->value = strdup(value);
    if (new_pair->key == NULL || new_pair->value == NULL) {
        free(new_pair->key);
        free(new_pair->value);
        free(new_pair);
        return;
    }
    new_pair->next = dict->head;
    dict->head = new_pair;
    dict->size++;
}

const char *dict_get(const Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return NULL;
    }

    KeyValue *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

Dictionary *dict_merge(const Dictionary *dict1, const Dictionary *dict2) {
    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }

    Dictionary *merged = create_dict();
    if (merged == NULL) {
        return NULL;
    }

    KeyValue *current = dict1->head;
    while (current != NULL) {
        dict_set(merged, current->key, current->value);
        current = current->next;
    }

    current = dict2->head;
    while (current != NULL) {
        dict_set(merged, current->key, current->value);
        current = current->next;
    }

    return merged;
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
    free(dict);
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    KeyValue *current = dict->head;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}

int main(void) {
    Dictionary *dict1 = create_dict();
    Dictionary *dict2 = create_dict();
    Dictionary *merged = NULL;

    if (dict1 == NULL || dict2 == NULL) {
        dict_free(dict1);
        dict_free(dict2);
        return 1;
    }

    dict_set(dict1, "name", "Alice");
    dict_set(dict1, "age", "30");
    dict_set(dict2, "city", "New York");
    dict_set(dict2, "age", "31");

    merged = dict_merge(dict1, dict2);
    if (merged == NULL) {
        dict_free(dict1);
        dict_free(dict2);
        return 1;
    }

    printf("Merged dictionary:\n");
    dict_print(merged);

    dict_free(dict1);
    dict_free(dict2);
    dict_free(merged);

    return 0;
}