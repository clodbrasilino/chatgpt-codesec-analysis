#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct DictNode {
    char *key;
    char *value;
    struct DictNode *next;
} DictNode;

typedef struct Dictionary {
    DictNode *head;
    size_t size;
} Dictionary;

static char *dup_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(s) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len);
    return copy;
}

Dictionary *dict_create(void)
{
    Dictionary *dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

void dict_free(Dictionary *dict)
{
    DictNode *node;
    DictNode *next;

    if (dict == NULL) {
        return;
    }
    node = dict->head;
    while (node != NULL) {
        next = node->next;
        free(node->key);
        free(node->value);
        free(node);
        node = next;
    }
    free(dict);
}

const char *dict_get(const Dictionary *dict, const char *key)
{
    DictNode *node;

    if (dict == NULL || key == NULL) {
        return NULL;
    }
    for (node = dict->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
    }
    return NULL;
}

bool dict_set(Dictionary *dict, const char *key, const char *value)
{
    DictNode *node;
    DictNode *new_node;
    char *new_value;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    for (node = dict->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            new_value = dup_string(value);
            if (new_value == NULL) {
                return false;
            }
            free(node->value);
            node->value = new_value;
            return true;
        }
    }
    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->key = dup_string(key);
    if (new_node->key == NULL) {
        free(new_node);
        return false;
    }
    new_node->value = dup_string(value);
    if (new_node->value == NULL) {
        free(new_node->key);
        free(new_node);
        return false;
    }
    new_node->next = dict->head;
    dict->head = new_node;
    dict->size++;
    return true;
}

bool dict_merge(Dictionary *dest, const Dictionary *src)
{
    DictNode *node;

    if (dest == NULL || src == NULL) {
        return false;
    }
    if (dest == src) {
        return true;
    }
    for (node = src->head; node != NULL; node = node->next) {
        if (!dict_set(dest, node->key, node->value)) {
            return false;
        }
    }
    return true;
}

void dict_print(const Dictionary *dict)
{
    DictNode *node;

    if (dict == NULL) {
        return;
    }
    for (node = dict->head; node != NULL; node = node->next) {
        printf("%s: %s\n", node->key, node->value);
    }
}

int main(void)
{
    Dictionary *dict1 = dict_create();
    Dictionary *dict2 = dict_create();

    if (dict1 == NULL || dict2 == NULL) {
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    if (!dict_set(dict1, "apple", "red") ||
        !dict_set(dict1, "banana", "yellow") ||
        !dict_set(dict1, "grape", "purple")) {
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    if (!dict_set(dict2, "grape", "green") ||
        !dict_set(dict2, "lemon", "yellow") ||
        !dict_set(dict2, "cherry", "dark red")) {
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    if (!dict_merge(dict1, dict2)) {
        dict_free(dict1);
        dict_free(dict2);
        return EXIT_FAILURE;
    }

    printf("Merged dictionary (%zu entries):\n", dict1->size);
    dict_print(dict1);

    dict_free(dict1);
    dict_free(dict2);
    return EXIT_SUCCESS;
}