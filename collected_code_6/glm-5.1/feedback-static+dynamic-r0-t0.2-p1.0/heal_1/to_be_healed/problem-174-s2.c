#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValuePair {
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::key' is never used. [unusedStructMember]
     */
    char *key;
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::value' is never used. [unusedStructMember]
     */
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
        if (!entry->key) { free(entry); return; }
        entry->values = NULL;
        entry->next = dict->head;
        dict->head = entry;
    }

    ListNode *node = malloc(sizeof(ListNode));
    if (!node) return;
    node->value = strdup(value);
    if (!node->value) { free(node); return; }
    node->next = entry->values;
    entry->values = node;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    DictEntry *entry = dict->head;
    while (entry) {
        DictEntry *next_entry = entry->next;
        free(entry->key);
        ListNode *node = entry->values;
        while (node) {
            ListNode *next_node = node->next;
            free(node->value);
            free(node);
            node = next_node;
        }
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
            printf("\"%s\"", node->value);
            if (node->next) printf(", ");
            node = node->next;
        }
        printf("]\n");
        entry = entry->next;
    }
}

int main() {
    Dictionary *dict = create_dictionary();
    if (!dict) return EXIT_FAILURE;

    dict_add(dict, "fruit", "apple");
    dict_add(dict, "color", "red");
    dict_add(dict, "fruit", "banana");
    dict_add(dict, "color", "green");
    dict_add(dict, "fruit", "cherry");

    print_dictionary(dict);

    free_dictionary(dict);

    return EXIT_SUCCESS;
}