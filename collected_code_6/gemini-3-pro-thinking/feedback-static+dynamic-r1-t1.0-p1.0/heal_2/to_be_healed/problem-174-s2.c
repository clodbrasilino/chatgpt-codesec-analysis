#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 4096

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct DictEntry {
    char *key;
    ListNode *values;
    struct DictEntry *next;
} DictEntry;

typedef struct Dictionary {
    DictEntry **table;
    size_t size;
} Dictionary;

typedef struct KeyValuePair {
    const char *key;
    int value;
} KeyValuePair;

static char *duplicate_string(const char *s) {
    if (!s) return NULL;
    
    size_t len = 0;
    while (len < MAX_KEY_LEN && s[len] != '\0') {
        len++;
    }
    
    char *dup = (char *)malloc(len + 1);
    if (!dup) return NULL;
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dup, s, len);
    dup[len] = '\0';
    
    return dup;
}

static unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    size_t i = 0;
    while (i < MAX_KEY_LEN && (c = str[i++])) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        DictEntry *entry = dict->table[i];
        while (entry != NULL) {
            DictEntry *next_entry = entry->next;
            ListNode *node = entry->values;
            while (node != NULL) {
                ListNode *next_node = node->next;
                free(node);
                node = next_node;
            }
            free(entry->key);
            free(entry);
            entry = next_entry;
        }
    }
    free(dict->table);
    free(dict);
}

Dictionary *create_dictionary(size_t size) {
    if (size == 0) return NULL;
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->size = size;
    dict->table = (DictEntry **)calloc(size, sizeof(DictEntry *));
    if (!dict->table) {
        free(dict);
        return NULL;
    }
    return dict;
}

int insert_into_dictionary(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) return -1;

    unsigned long hash = hash_function(key);
    size_t index = hash % dict->size;

    DictEntry *entry = dict->table[index];
    while (entry != NULL) {
        if (strncmp(entry->key, key, MAX_KEY_LEN) == 0) {
            ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
            if (!new_node) return -1;
            new_node->value = value;
            new_node->next = entry->values;
            entry->values = new_node;
            return 0;
        }
        entry = entry->next;
    }

    DictEntry *new_entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (!new_entry) return -1;

    new_entry->key = duplicate_string(key);
    if (!new_entry->key) {
        free(new_entry);
        return -1;
    }

    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    if (!new_node) {
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    new_node->value = value;
    new_node->next = NULL;

    new_entry->values = new_node;
    new_entry->next = dict->table[index];
    dict->table[index] = new_entry;

    return 0;
}

Dictionary *group_by_key(const KeyValuePair *pairs, size_t num_pairs) {
    if (!pairs || num_pairs == 0) return NULL;

    size_t table_size = num_pairs * 2;
    Dictionary *dict = create_dictionary(table_size);
    if (!dict) return NULL;

    for (size_t i = 0; i < num_pairs; i++) {
        if (insert_into_dictionary(dict, pairs[i].key, pairs[i].value) != 0) {
            free_dictionary(dict);
            return NULL;
        }
    }
    return dict;
}

int main(void) {
    KeyValuePair pairs[] = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"orange", 4},
        {"banana", 5}
    };
    size_t num_pairs = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary *dict = group_by_key(pairs, num_pairs);
    if (!dict) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict->size; i++) {
        DictEntry *entry = dict->table[i];
        while (entry != NULL) {
            printf("%s: [", entry->key);
            ListNode *node = entry->values;
            while (node != NULL) {
                printf("%d", node->value);
                if (node->next) printf(", ");
                node = node->next;
            }
            printf("]\n");
            entry = entry->next;
        }
    }

    free_dictionary(dict);
    return EXIT_SUCCESS;
}