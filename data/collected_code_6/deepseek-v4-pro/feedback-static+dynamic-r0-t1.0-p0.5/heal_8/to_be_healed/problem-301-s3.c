#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict_entry {
    char *key;
    void *value;
    int is_dict;
    struct dict_entry *next;
} dict_entry;

typedef struct {
    dict_entry *head;
} dict;

dict *dict_create(void) {
    dict *d = (dict *)malloc(sizeof(dict));
    if (d == NULL) {
        return NULL;
    }
    d->head = NULL;
    return d;
}

void dict_set(dict *d, const char *key, void *value, int is_dict) {
    if (d == NULL || key == NULL) {
        return;
    }
    size_t key_len = strnlen(key, 4096);
    if (key_len >= 4096) {
        return;
    }
    dict_entry *entry = (dict_entry *)malloc(sizeof(dict_entry));
    if (entry == NULL) {
        return;
    }
    /* Possible weaknesses found:
     *  alloc_size is assigned 'key_len+1' here.
     */
    size_t alloc_size = key_len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<key_len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<key_len' is always false
     */
    if (alloc_size < key_len) {
        free(entry);
        return;
    }
    entry->key = (char *)malloc(alloc_size);
    if (entry->key == NULL) {
        free(entry);
        return;
    }
    if (key_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(entry->key, key, key_len);
    }
    entry->key[key_len] = '\0';
    entry->value = value;
    entry->is_dict = is_dict;
    entry->next = d->head;
    d->head = entry;
}

void *dict_get(dict *d, const char *key) {
    if (d == NULL || key == NULL) {
        return NULL;
    }
    dict_entry *current = d->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

int dict_is_dict(dict *d, const char *key) {
    if (d == NULL || key == NULL) {
        return 0;
    }
    dict_entry *current = d->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->is_dict;
        }
        current = current->next;
    }
    return 0;
}

static void dict_free_impl(dict *d, int is_toplevel) {
    if (d == NULL) {
        return;
    }
    dict_entry *current = d->head;
    while (current != NULL) {
        dict_entry *next = current->next;
        free(current->key);
        if (current->is_dict) {
            dict_free_impl((dict *)current->value, 0);
        }
        free(current);
        current = next;
    }
    if (is_toplevel) {
        free(d);
    }
}

void dict_free(dict *d) {
    dict_free_impl(d, 1);
}

int dict_depth(dict *d) {
    if (d == NULL) {
        return 0;
    }
    int max_depth = 0;
    dict_entry *current = d->head;
    while (current != NULL) {
        if (current->is_dict) {
            int child_depth = dict_depth((dict *)current->value);
            if (child_depth > max_depth) {
                max_depth = child_depth;
            }
        }
        current = current->next;
    }
    return max_depth + 1;
}

int main(void) {
    dict *root = dict_create();
    if (root == NULL) {
        return 1;
    }

    dict *level1 = dict_create();
    if (level1 == NULL) {
        dict_free(root);
        return 1;
    }

    dict *level2 = dict_create();
    if (level2 == NULL) {
        dict_free(level1);
        dict_free(root);
        return 1;
    }

    dict *level3 = dict_create();
    if (level3 == NULL) {
        dict_free(level2);
        dict_free(level1);
        dict_free(root);
        return 1;
    }

    dict_set(level3, "value", (void *)"deep", 0);
    dict_set(level2, "nested", level3, 1);
    dict_set(level1, "nested", level2, 1);
    dict_set(root, "nested", level1, 1);
    dict_set(root, "simple", (void *)"value", 0);

    printf("Depth: %d\n", dict_depth(root));

    dict_free(root);
    return 0;
}