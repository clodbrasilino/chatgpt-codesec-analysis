#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    char *value;
} KeyValue;

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct DictEntry {
    char *key;
    Node *values;
    struct DictEntry *next;
} DictEntry;

typedef struct Dictionary {
    DictEntry *head;
    int size;
} Dictionary;

void free_dictionary(Dictionary *dict);

Dictionary *create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

DictEntry *find_entry(Dictionary *dict, const char *key) {
    DictEntry *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int add_to_dict(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    DictEntry *entry = find_entry(dict, key);
    if (entry != NULL) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            return -1;
        }
        new_node->value = (char *)malloc(strlen(value) + 1);
        if (new_node->value == NULL) {
            free(new_node);
            return -1;
        }
        strcpy(new_node->value, value);
        new_node->next = entry->values;
        entry->values = new_node;
        return 0;
    }

    DictEntry *new_entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (new_entry == NULL) {
        return -1;
    }
    new_entry->key = (char *)malloc(strlen(key) + 1);
    if (new_entry->key == NULL) {
        free(new_entry);
        return -1;
    }
    strcpy(new_entry->key, key);

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    new_node->value = (char *)malloc(strlen(value) + 1);
    if (new_node->value == NULL) {
        free(new_node);
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    strcpy(new_node->value, value);
    new_node->next = NULL;

    new_entry->values = new_node;
    new_entry->next = dict->head;
    dict->head = new_entry;
    dict->size++;
    return 0;
}

Dictionary *group_by_key(KeyValue *pairs, int count) {
    if (pairs == NULL || count <= 0) {
        return NULL;
    }

    Dictionary *dict = create_dictionary();
    if (dict == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        if (pairs[i].key == NULL || pairs[i].value == NULL) {
            continue;
        }
        if (add_to_dict(dict, pairs[i].key, pairs[i].value) != 0) {
            free_dictionary(dict);
            return NULL;
        }
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    DictEntry *entry = dict->head;
    while (entry != NULL) {
        DictEntry *next_entry = entry->next;
        Node *node = entry->values;
        while (node != NULL) {
            Node *next_node = node->next;
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

void print_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        printf("Dictionary is NULL\n");
        return;
    }

    DictEntry *entry = dict->head;
    while (entry != NULL) {
        printf("%s: [", entry->key);
        Node *node = entry->values;
        while (node != NULL) {
            printf("%s", node->value);
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
    KeyValue pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"animal", "dog"},
        {"fruit", "cherry"}
    };
    int count = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary *dict = group_by_key(pairs, count);
    if (dict == NULL) {
        printf("Failed to group pairs\n");
        return 1;
    }

    print_dictionary(dict);
    free_dictionary(dict);

    return 0;
}