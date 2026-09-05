#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dict {
    char *key;
    void *value;
    int is_dict;
    struct Dict *next;
} Dict;

Dict *create_dict() {
    return calloc(1, sizeof(Dict));
}

void dict_add(Dict *d, const char *key, void *value, int is_dict) {
    if (!d) return;
    Dict *entry = malloc(sizeof(Dict));
    if (!entry) return;
    entry->key = strdup(key);
    if (!entry->key) { free(entry); return; }
    entry->value = value;
    entry->is_dict = is_dict;
    entry->next = NULL;
    Dict *curr = d;
    while (curr->next) curr = curr->next;
    curr->next = entry;
}

Dict *lists_to_nested_dict(char **keys, int keys_len, char **values, int values_len) {
    if (!keys || keys_len <= 0 || !values || values_len <= 0) return NULL;
    Dict *root = create_dict();
    if (!root) return NULL;
    Dict *current = root;
    for (int i = 0; i < keys_len; i++) {
        Dict *next_dict = create_dict();
        if (!next_dict) return root;
        if (i == keys_len - 1) {
            char *val = (i < values_len && values[i]) ? strdup(values[i]) : strdup("");
            if (!val) return root;
            dict_add(current, keys[i], val, 0);
        } else {
            dict_add(current, keys[i], next_dict, 1);
            current = next_dict;
        }
    }
    return root;
}

void print_dict(Dict *d, int depth) {
    if (!d) return;
    Dict *curr = d->next;
    while (curr) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("%s: ", curr->key);
        if (curr->is_dict && curr->value) {
            printf("\n");
            print_dict((Dict *)curr->value, depth + 1);
        } else {
            printf("%s\n", (char *)curr->value);
        }
        curr = curr->next;
    }
}

void free_dict(Dict *d) {
    if (!d) return;
    Dict *curr = d->next;
    while (curr) {
        Dict *next = curr->next;
        free(curr->key);
        if (curr->is_dict) {
            free_dict((Dict *)curr->value);
        } else {
            free(curr->value);
        }
        free(curr);
        curr = next;
    }
    free(d);
}

int main() {
    char *keys[] = {"level1", "level2", "level3"};
    char *values[] = {"val1", "val2", "val3"};
    int keys_len = sizeof(keys) / sizeof(keys[0]);
    int values_len = sizeof(values) / sizeof(values[0]);
    Dict *nested = lists_to_nested_dict(keys, keys_len, values, values_len);
    if (nested) {
        print_dict(nested, 0);
        free_dict(nested);
    }
    return 0;
}