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
} Dictionary;

/* Possible weaknesses found:
 *  'create_dictionary' declared here
 */
Dictionary *create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    return dict;
}

DictEntry *find_entry(Dictionary *dict, const char *key) {
    DictEntry *entry = dict->head;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

int add_to_dict(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return 0;
    }

    DictEntry *entry = find_entry(dict, key);
    if (entry == NULL) {
        entry = (DictEntry *)malloc(sizeof(DictEntry));
        if (entry == NULL) {
            return 0;
        }
        entry->key = (char *)malloc(strlen(key) + 1);
        if (entry->key == NULL) {
            free(entry);
            return 0;
        }
        strcpy(entry->key, key);
        entry->values = NULL;
        entry->next = dict->head;
        dict->head = entry;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }
    new_node->value = (char *)malloc(strlen(value) + 1);
    if (new_node->value == NULL) {
        free(new_node);
        return 0;
    }
    strcpy(new_node->value, value);
    new_node->next = entry->values;
    entry->values = new_node;

    return 1;
}

Dictionary *group_pairs(KeyValue *pairs, int count) {
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
        if (!add_to_dict(dict, pairs[i].key, pairs[i].value)) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'free_dictionary'; did you mean 'create_dictionary'? [-Wimplicit-function-declaration]
             *  call to undeclared function 'free_dictionary'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  previous implicit declaration is here
             *  did you mean 'create_dictionary'?
             */
            free_dictionary(dict);
            return NULL;
        }
    }

    return dict;
}

/* Possible weaknesses found:
 *  conflicting types for 'free_dictionary'
 */
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
        {"fruit", "cherry"},
        {"animal", "dog"}
    };
    int count = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary *dict = group_pairs(pairs, count);
    if (dict == NULL) {
        fprintf(stderr, "Failed to group pairs\n");
        return 1;
    }

    print_dictionary(dict);
    free_dictionary(dict);

    return 0;
}