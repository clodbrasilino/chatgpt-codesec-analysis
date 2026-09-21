#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct KeyValue {
    char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue *head;
} Dictionary;

void dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    dict->head = NULL;
}

void dict_free(Dictionary *dict) {
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
    dict->head = NULL;
}

static size_t safe_strlen(const char *str, size_t max_size) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_size && str[len] != '\0') {
        len++;
    }
    if (len == max_size) {
        return 0;
    }
    return len;
}

int dict_add(Dictionary *dict, const char *key, int value) {
    if (key == NULL || dict == NULL) {
        return -1;
    }

    KeyValue *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value += value;
            return 0;
        }
        current = current->next;
    }

    size_t key_len = safe_strlen(key, SIZE_MAX);
    if (key_len == 0 && key[0] != '\0') {
        return -1;
    }

    if (key_len >= SIZE_MAX) {
        return -1;
    }

    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return -1;
    }

    char *new_key = (char *)malloc(key_len + 1);
    if (new_key == NULL) {
        free(new_pair);
        return -1;
    }

    if (key_len + 1 <= key_len) {
        free(new_key);
        free(new_pair);
        return -1;
    }

    memcpy(new_key, key, key_len + 1);
    new_pair->key = new_key;
    new_pair->value = value;
    new_pair->next = dict->head;
    dict->head = new_pair;
    return 0;
}

Dictionary dict_combine(Dictionary *dict1, Dictionary *dict2) {
    Dictionary result;
    dict_init(&result);

    if (dict1 == NULL || dict2 == NULL) {
        return result;
    }

    KeyValue *current = dict1->head;
    while (current != NULL) {
        if (dict_add(&result, current->key, current->value) != 0) {
            dict_free(&result);
            dict_init(&result);
            return result;
        }
        current = current->next;
    }

    current = dict2->head;
    while (current != NULL) {
        if (dict_add(&result, current->key, current->value) != 0) {
            dict_free(&result);
            dict_init(&result);
            return result;
        }
        current = current->next;
    }

    return result;
}

void dict_print(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    KeyValue *current = dict->head;
    while (current != NULL) {
        printf("%s: %d\n", current->key, current->value);
        current = current->next;
    }
}

int main(void) {
    Dictionary dict1, dict2, combined;

    dict_init(&dict1);
    dict_init(&dict2);

    dict_add(&dict1, "apple", 3);
    dict_add(&dict1, "banana", 2);
    dict_add(&dict1, "cherry", 5);

    dict_add(&dict2, "banana", 4);
    dict_add(&dict2, "date", 1);
    dict_add(&dict2, "apple", 1);

    combined = dict_combine(&dict1, &dict2);

    printf("Combined dictionary:\n");
    dict_print(&combined);

    dict_free(&dict1);
    dict_free(&dict2);
    dict_free(&combined);

    return 0;
}