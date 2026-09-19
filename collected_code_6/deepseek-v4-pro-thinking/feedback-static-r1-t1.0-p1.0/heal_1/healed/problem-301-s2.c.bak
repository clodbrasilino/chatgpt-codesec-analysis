#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dict Dict;
typedef struct DictEntry DictEntry;

struct DictEntry {
    char *key;
    Dict *nested;
    DictEntry *next;
};

struct Dict {
    DictEntry *entries;
};

static Dict *dict_create(void) {
    Dict *dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = NULL;
    return dict;
}

static int dict_add(Dict *dict, const char *key, Dict *nested) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    DictEntry *entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        return -1;
    }
    size_t key_len = strlen(key) + 1;
    entry->key = malloc(key_len);
    if (entry->key == NULL) {
        free(entry);
        return -1;
    }
    memcpy(entry->key, key, key_len);
    entry->nested = nested;
    entry->next = dict->entries;
    dict->entries = entry;
    return 0;
}

static void dict_free(Dict *dict) {
    if (dict == NULL) {
        return;
    }
    DictEntry *entry = dict->entries;
    while (entry != NULL) {
        DictEntry *next = entry->next;
        free(entry->key);
        dict_free(entry->nested);
        free(entry);
        entry = next;
    }
    free(dict);
}

int dict_depth(const Dict *dict) {
    if (dict == NULL) {
        return 0;
    }
    int max_child_depth = 0;
    const DictEntry *entry = dict->entries;
    while (entry != NULL) {
        if (entry->nested != NULL) {
            int child_depth = dict_depth(entry->nested);
            if (child_depth > max_child_depth) {
                max_child_depth = child_depth;
            }
        }
        entry = entry->next;
    }
    return max_child_depth + 1;
}

int main(void) {
    Dict *root = dict_create();
    if (root == NULL) {
        return 1;
    }

    Dict *level1 = dict_create();
    if (level1 == NULL) {
        dict_free(root);
        return 1;
    }

    Dict *level2 = dict_create();
    if (level2 == NULL) {
        dict_free(level1);
        dict_free(root);
        return 1;
    }

    if (dict_add(level2, "a", NULL) != 0) {
        goto fail;
    }
    if (dict_add(level1, "b", level2) != 0) {
        goto fail;
    }
    level2 = NULL;

    if (dict_add(root, "c", NULL) != 0) {
        goto fail;
    }
    if (dict_add(root, "d", level1) != 0) {
        goto fail;
    }

    printf("%d\n", dict_depth(root));

    dict_free(root);
    return 0;

fail:
    dict_free(level2);
    dict_free(level1);
    dict_free(root);
    return 1;
}