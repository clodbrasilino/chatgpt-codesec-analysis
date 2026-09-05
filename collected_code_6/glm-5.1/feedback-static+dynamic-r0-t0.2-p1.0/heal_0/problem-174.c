#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValuePair {
    char *key;
    char *value;
} KeyValuePair;

typedef struct ListNode {
    char *value;
    struct ListNode *next;
} ListNode;

typedef struct DictEntry {
    char *key;
    ListNode *values;
    struct DictEntry *next;
} DictEntry;

typedef struct Dictionary {
    DictEntry *head;
} Dictionary;

Dictionary *create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->head = NULL;
    return dict;
}

void dict_add(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return;

    DictEntry *entry = dict->head;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            break;
        }
        entry = entry->next;
    }

    if (!entry) {
        entry = malloc(sizeof(DictEntry));
        if (!entry) return;
        
        entry->key = strdup(key);
        if (!entry->key) {
            free(entry);
            return;
        }
        
        entry->values = NULL;
        entry->next = dict->head;
        dict->head = entry;
    }

    ListNode *node = malloc(sizeof(ListNode));
    if (!node) return;

    node->value = strdup(value);
    if (!node->value) {
        free(node);
        return;
    }

    node->next = entry->values;
    entry->values = node;
}

Dictionary *group_key_value_pairs(KeyValuePair *pairs, size_t count) {
    if (!pairs) return NULL;

    Dictionary *dict = create_dictionary();
    if (!dict) return NULL;

    for (size_t i = 0; i < count; i++) {
        dict_add(dict, pairs[i].key, pairs[i].value);
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;

    DictEntry *entry = dict->head;
    while (entry) {
        DictEntry *next_entry = entry->next;
        
        ListNode *node = entry->values;
        while (node) {
            ListNode *next_node = node->next;
            free(node->value);
            free(node);
            node = next_node;
        }

        free(entry->key);
        free(entry);
        entry = next_entry;
    }

    free(dict);
}

void print_dictionary(const Dictionary *dict) {
    if (!dict) return;

    DictEntry *entry = dict->head;
    while (entry) {
        printf("%s: [", entry->key);
        ListNode *node = entry->values;
        while (node) {
            printf("'%s'", node->value);
            if (node->next) printf(", ");
            node = node->next;
        }
        printf("]\n");
        entry = entry->next;
    }
}

int main(void) {
    KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "green"},
        {"fruit", "cherry"}
    };

    size_t count = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary *dict = group_key_value_pairs(pairs, count);
    if (!dict) {
        return EXIT_FAILURE;
    }

    print_dictionary(dict);
    free_dictionary(dict);

    return EXIT_SUCCESS;
}