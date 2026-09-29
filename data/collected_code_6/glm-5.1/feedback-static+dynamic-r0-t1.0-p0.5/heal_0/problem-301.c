#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { DICT_NULL, DICT_INT, DICT_STRING, DICT_DICT } DictType;

typedef struct DictEntry {
    char *key;
    DictType type;
    void *value;
    struct DictEntry *next;
} DictEntry;

typedef struct {
    DictEntry *head;
} Dict;

Dict *dict_create(void) {
    Dict *d = (Dict *)malloc(sizeof(Dict));
    if (d == NULL) {
        exit(EXIT_FAILURE);
    }
    d->head = NULL;
    return d;
}

void dict_add(Dict *d, const char *key, DictType type, void *value) {
    if (d == NULL || key == NULL) {
        return;
    }
    DictEntry *entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (entry == NULL) {
        exit(EXIT_FAILURE);
    }
    entry->key = strdup(key);
    if (entry->key == NULL) {
        free(entry);
        exit(EXIT_FAILURE);
    }
    entry->type = type;
    entry->value = value;
    entry->next = d->head;
    d->head = entry;
}

int find_depth(Dict *d) {
    if (d == NULL) {
        return 0;
    }
    int max_depth = 0;
    DictEntry *current = d->head;
    while (current != NULL) {
        if (current->type == DICT_DICT && current->value != NULL) {
            int child_depth = find_depth((Dict *)current->value);
            if (child_depth > max_depth) {
                max_depth = child_depth;
            }
        }
        current = current->next;
    }
    return max_depth + 1;
}

void dict_free(Dict *d) {
    if (d == NULL) {
        return;
    }
    DictEntry *current = d->head;
    while (current != NULL) {
        DictEntry *next = current->next;
        free(current->key);
        if (current->type == DICT_DICT) {
            dict_free((Dict *)current->value);
        } else {
            free(current->value);
        }
        free(current);
        current = next;
    }
    free(d);
}

int main(void) {
    Dict *d1 = dict_create();
    Dict *d2 = dict_create();
    Dict *d3 = dict_create();

    int *val1 = (int *)malloc(sizeof(int));
    char *val2 = (char *)malloc(6 * sizeof(char));
    int *val3 = (int *)malloc(sizeof(int));

    if (val1 == NULL || val2 == NULL || val3 == NULL) {
        exit(EXIT_FAILURE);
    }

    *val1 = 10;
    strncpy(val2, "hello", 6);
    *val3 = 20;

    dict_add(d3, "key3", DICT_INT, val3);
    dict_add(d2, "key2", DICT_DICT, d3);
    dict_add(d2, "key2b", DICT_STRING, val2);
    dict_add(d1, "key1", DICT_DICT, d2);
    dict_add(d1, "key1b", DICT_INT, val1);

    int depth = find_depth(d1);
    printf("%d\n", depth);

    dict_free(d1);

    return 0;
}