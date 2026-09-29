#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define MAX_KEY_LENGTH 1024

typedef struct DictNode {
    char *key;
    int value;
    struct DictNode *next;
} DictNode;

typedef struct {
    DictNode *head;
    size_t size;
} Dict;

Dict *dict_create(void) {
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

static size_t bounded_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static int key_is_valid(const char *key) {
    if (key == NULL) {
        return 0;
    }
    return bounded_strlen(key, MAX_KEY_LENGTH + 1) <= MAX_KEY_LENGTH;
}

static char *duplicate_string(const char *str) {
    size_t len;
    char *copy;
    if (!key_is_valid(str)) {
        return NULL;
    }
    len = bounded_strlen(str, MAX_KEY_LENGTH + 1);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, str, len);
    copy[len] = '\0';
    return copy;
}

int dict_set(Dict *dict, const char *key, int value) {
    DictNode *current;
    DictNode *node;
    if (dict == NULL || !key_is_valid(key)) {
        return -1;
    }
    current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    if (dict->size == SIZE_MAX) {
        return -1;
    }
    node = malloc(sizeof(DictNode));
    if (node == NULL) {
        return -1;
    }
    node->key = duplicate_string(key);
    if (node->key == NULL) {
        free(node);
        return -1;
    }
    node->value = value;
    node->next = dict->head;
    dict->head = node;
    dict->size++;
    return 0;
}

int dict_add(Dict *dict, const char *key, int value) {
    DictNode *current;
    if (dict == NULL || !key_is_valid(key)) {
        return -1;
    }
    current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if ((value > 0 && current->value > INT_MAX - value) ||
                (value < 0 && current->value < INT_MIN - value)) {
                return -1;
            }
            current->value += value;
            return 0;
        }
        current = current->next;
    }
    return dict_set(dict, key, value);
}

void dict_free(Dict *dict) {
    DictNode *current;
    DictNode *next;
    if (dict == NULL) {
        return;
    }
    current = dict->head;
    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    free(dict);
}

Dict *dict_combine(const Dict *dict1, const Dict *dict2) {
    Dict *result;
    DictNode *current;
    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }
    result = dict_create();
    if (result == NULL) {
        return NULL;
    }
    current = dict1->head;
    while (current != NULL) {
        if (dict_add(result, current->key, current->value) != 0) {
            dict_free(result);
            return NULL;
        }
        current = current->next;
    }
    current = dict2->head;
    while (current != NULL) {
        if (dict_add(result, current->key, current->value) != 0) {
            dict_free(result);
            return NULL;
        }
        current = current->next;
    }
    return result;
}

void dict_print(const Dict *dict) {
    DictNode *current;
    if (dict == NULL) {
        return;
    }
    current = dict->head;
    printf("{");
    while (current != NULL) {
        printf("%s: %d", current->key, current->value);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("}\n");
}

int main(void) {
    Dict *dict1 = dict_create();
    if (dict1 == NULL) {
        fprintf(stderr, "Failed to create dictionary 1\n");
        return EXIT_FAILURE;
    }

    Dict *dict2 = dict_create();
    if (dict2 == NULL) {
        fprintf(stderr, "Failed to create dictionary 2\n");
        dict_free(dict1);
        return EXIT_FAILURE;
    }

    if (dict_set(dict1, "apple", 5) != 0 ||
        dict_set(dict1, "banana", 3) != 0 ||
        dict_set(dict1, "cherry", 7) != 0) {
        fprintf(stderr, "Failed to populate dictionary 1\n");
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    if (dict_set(dict2, "banana", 2) != 0 ||
        dict_set(dict2, "cherry", 1) != 0 ||
        dict_set(dict2, "date", 4) != 0) {
        fprintf(stderr, "Failed to populate dictionary 2\n");
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    printf("Dictionary 1: ");
    dict_print(dict1);
    printf("Dictionary 2: ");
    dict_print(dict2);

    Dict *combined = dict_combine(dict1, dict2);
    if (combined == NULL) {
        fprintf(stderr, "Failed to combine dictionaries\n");
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    printf("Combined: ");
    dict_print(combined);

    dict_free(dict1);
    dict_free(dict2);
    dict_free(combined);

    return EXIT_SUCCESS;
}