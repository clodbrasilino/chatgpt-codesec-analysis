#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { DICT_INT, DICT_STRING, DICT_DICT } DictType;

typedef struct DictEntry {
    char *key;
    DictType type;
    void *value;
    struct DictEntry *next;
} DictEntry;

typedef struct {
    DictEntry *head;
} Dict;

Dict *dict_create() {
    Dict *d = (Dict *)malloc(sizeof(Dict));
    if (!d) return NULL;
    d->head = NULL;
    return d;
}

int dict_insert(Dict *d, const char *key, DictType type, void *value) {
    if (!d || !key) return 0;
    DictEntry *entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (!entry) return 0;
    entry->key = strdup(key);
    if (!entry->key) {
        free(entry);
        return 0;
    }
    entry->type = type;
    entry->value = value;
    entry->next = d->head;
    d->head = entry;
    return 1;
}

int find_depth(Dict *d) {
    if (!d) return 0;
    int max_depth = 0;
    DictEntry *current = d->head;
    while (current) {
        if (current->type == DICT_DICT && current->value) {
            int sub_depth = find_depth((Dict *)current->value);
            if (sub_depth > max_depth) {
                max_depth = sub_depth;
            }
        }
        current = current->next;
    }
    return max_depth + 1;
}

void dict_free(Dict *d) {
    if (!d) return;
    DictEntry *current = d->head;
    while (current) {
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

int main() {
    Dict *d1 = dict_create();
    Dict *d2 = dict_create();
    Dict *d3 = dict_create();
    Dict *d4 = dict_create();

    int *val1 = (int *)malloc(sizeof(int));
    *val1 = 10;
    int *val2 = (int *)malloc(sizeof(int));
    *val2 = 20;
    int *val3 = (int *)malloc(sizeof(int));
    *val3 = 30;

    dict_insert(d3, "key3", DICT_INT, val3);
    dict_insert(d2, "key2", DICT_DICT, d3);
    dict_insert(d2, "key2b", DICT_INT, val2);
    dict_insert(d1, "key1", DICT_DICT, d2);
    dict_insert(d1, "key1b", DICT_INT, val1);
    dict_insert(d4, "key4", DICT_INT, val1);

    printf("Depth d1: %d\n", find_depth(d1));
    printf("Depth d2: %d\n", find_depth(d2));
    printf("Depth d3: %d\n", find_depth(d3));
    printf("Depth d4: %d\n", find_depth(d4));
    printf("Depth NULL: %d\n", find_depth(NULL));

    dict_free(d1);
    dict_free(d4);

    return 0;
}