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

void dict_init(Dictionary *dict) {
    dict->head = NULL;
}

void dict_add(Dictionary *dict, const char *key, const char *value) {
    DictEntry *entry = dict->head;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            break;
        }
        entry = entry->next;
    }

    if (entry == NULL) {
        entry = (DictEntry *)malloc(sizeof(DictEntry));
        if (entry == NULL) {
            exit(EXIT_FAILURE);
        }
        size_t key_len = strnlen(key, SIZE_MAX);
        entry->key = (char *)malloc(key_len + 1);
        if (entry->key == NULL) {
            free(entry);
            exit(EXIT_FAILURE);
        }
        memcpy(entry->key, key, key_len + 1);
        entry->values = NULL;
        entry->next = dict->head;
        dict->head = entry;
    }

    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    size_t val_len = strnlen(value, SIZE_MAX);
    node->value = (char *)malloc(val_len + 1);
    if (node->value == NULL) {
        free(node);
        exit(EXIT_FAILURE);
    }
    memcpy(node->value, value, val_len + 1);
    node->next = entry->values;
    entry->values = node;
}

void dict_free(Dictionary *dict) {
    DictEntry *entry = dict->head;
    while (entry != NULL) {
        DictEntry *next_entry = entry->next;
        free(entry->key);
        ListNode *node = entry->values;
        while (node != NULL) {
            ListNode *next_node = node->next;
            free(node->value);
            free(node);
            node = next_node;
        }
        free(entry);
        entry = next_entry;
    }
    dict->head = NULL;
}

void group_key_values(KeyValuePair *pairs, size_t count, Dictionary *dict) {
    for (size_t i = 0; i < count; i++) {
        dict_add(dict, pairs[i].key, pairs[i].value);
    }
}

void dict_print(Dictionary *dict) {
    DictEntry *entry = dict->head;
    while (entry != NULL) {
        printf("%s: [", entry->key);
        ListNode *node = entry->values;
        while (node != NULL) {
            printf("\"%s\"", node->value);
            if (node->next != NULL) {
                printf(", ");
            }
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

    Dictionary dict;
    dict_init(&dict);

    group_key_values(pairs, count, &dict);

    dict_print(&dict);

    dict_free(&dict);

    return 0;
}