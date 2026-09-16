#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_SIZE 16

typedef enum { NODE_DICT, NODE_STR } NodeType;

typedef struct DictEntry {
    char *key;
    NodeType type;
    union {
        struct Dict *dict;
        char *str;
    } value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dict {
    DictEntry *buckets[BUCKET_SIZE];
} Dict;

unsigned long hash_key(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % BUCKET_SIZE;
}

Dict *dict_create(void);
void dict_free(Dict *dict);
void entry_free(DictEntry *entry);
DictEntry *dict_find_or_create_node(Dict *dict, const char *key);
int dict_insert_str(Dict *dict, const char *key, const char *val);
Dict *lists_to_nested_dict(char ***lists, const size_t *list_sizes, size_t num_lists);
void print_dict(Dict *dict, int indent);
void print_entry(DictEntry *entry, int indent);

Dict *dict_create(void) {
    Dict *dict = malloc(sizeof(Dict));
    if (!dict) return NULL;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        dict->buckets[i] = NULL;
    }
    return dict;
}

void entry_free(DictEntry *entry) {
    if (!entry) return;
    free(entry->key);
    if (entry->type == NODE_DICT) {
        dict_free(entry->value.dict);
    } else if (entry->type == NODE_STR) {
        free(entry->value.str);
    }
    entry_free(entry->next);
    free(entry);
}

void dict_free(Dict *dict) {
    if (!dict) return;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        entry_free(dict->buckets[i]);
    }
    free(dict);
}

DictEntry *dict_find_or_create_node(Dict *dict, const char *key) {
    unsigned long hash = hash_key(key);
    DictEntry *entry = dict->buckets[hash];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    DictEntry *new_entry = malloc(sizeof(DictEntry));
    if (!new_entry) return NULL;
    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        return NULL;
    }
    new_entry->type = NODE_DICT;
    new_entry->value.dict = dict_create();
    if (!new_entry->value.dict) {
        free(new_entry->key);
        free(new_entry);
        return NULL;
    }
    new_entry->next = dict->buckets[hash];
    dict->buckets[hash] = new_entry;
    return new_entry;
}

int dict_insert_str(Dict *dict, const char *key, const char *val) {
    unsigned long hash = hash_key(key);
    DictEntry *entry = dict->buckets[hash];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (entry->type == NODE_DICT) {
                dict_free(entry->value.dict);
            } else if (entry->type == NODE_STR) {
                free(entry->value.str);
            }
            entry->type = NODE_STR;
            entry->value.str = strdup(val);
            if (!entry->value.str) return -1;
            return 0;
        }
        entry = entry->next;
    }
    DictEntry *new_entry = malloc(sizeof(DictEntry));
    if (!new_entry) return -1;
    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        return -1;
    }
    new_entry->type = NODE_STR;
    new_entry->value.str = strdup(val);
    if (!new_entry->value.str) {
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    new_entry->next = dict->buckets[hash];
    dict->buckets[hash] = new_entry;
    return 0;
}

Dict *lists_to_nested_dict(char ***lists, const size_t *list_sizes, size_t num_lists) {
    Dict *root = dict_create();
    if (!root) return NULL;
    for (size_t i = 0; i < num_lists; i++) {
        if (list_sizes[i] == 0) continue;
        Dict *current = root;
        for (size_t j = 0; j < list_sizes[i] - 1; j++) {
            DictEntry *entry = dict_find_or_create_node(current, lists[i][j]);
            if (!entry) {
                dict_free(root);
                return NULL;
            }
            if (entry->type != NODE_DICT) {
                dict_free(root);
                return NULL;
            }
            current = entry->value.dict;
        }
        if (dict_insert_str(current, lists[i][list_sizes[i] - 1], "leaf") != 0) {
            dict_free(root);
            return NULL;
        }
    }
    return root;
}

void print_entry(DictEntry *entry, int indent) {
    while (entry) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("%s: ", entry->key);
        if (entry->type == NODE_DICT) {
            printf("\n");
            print_dict(entry->value.dict, indent + 1);
        } else {
            printf("%s\n", entry->value.str);
        }
        entry = entry->next;
    }
}

void print_dict(Dict *dict, int indent) {
    if (!dict) return;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        print_entry(dict->buckets[i], indent);
    }
}

int main(void) {
    char *list1[] = {"user", "profile", "name"};
    char *list2[] = {"user", "profile", "age"};
    char *list3[] = {"system", "version"};
    char *list4[] = {"user", "settings", "theme"};
    char **lists[] = {list1, list2, list3, list4};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    size_t sizes[] = {3, 3, 2, 3};

    Dict *dict = lists_to_nested_dict(lists, sizes, 4);
    if (dict) {
        print_dict(dict, 0);
        dict_free(dict);
    }
    return 0;
}