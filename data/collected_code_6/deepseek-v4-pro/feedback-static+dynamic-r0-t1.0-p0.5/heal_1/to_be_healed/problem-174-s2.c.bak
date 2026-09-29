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

static char *duplicate_string(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str) + 1;
    char *copy = (char *)malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, str, len);
    return copy;
}

static DictEntry *find_entry(Dictionary *dict, const char *key) {
    DictEntry *entry = dict->head;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

static int append_value(DictEntry *entry, const char *value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }
    new_node->value = duplicate_string(value);
    if (new_node->value == NULL) {
        free(new_node);
        return 0;
    }
    new_node->next = NULL;

    if (entry->values == NULL) {
        entry->values = new_node;
    } else {
        Node *current = entry->values;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return 1;
}

static int add_entry(Dictionary *dict, const char *key, const char *value) {
    DictEntry *new_entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (new_entry == NULL) {
        return 0;
    }
    new_entry->key = duplicate_string(key);
    if (new_entry->key == NULL) {
        free(new_entry);
        return 0;
    }
    new_entry->values = NULL;
    new_entry->next = dict->head;
    dict->head = new_entry;

    if (!append_value(new_entry, value)) {
        free(new_entry->key);
        free(new_entry);
        /* Possible weaknesses found:
         *  Dereferencing 'new_entry' after it is deallocated / released [deallocuse]
         */
        dict->head = new_entry->next;
        return 0;
    }
    return 1;
}

Dictionary *group_by_key(KeyValue *pairs, size_t count) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;

    for (size_t i = 0; i < count; i++) {
        if (pairs[i].key == NULL || pairs[i].value == NULL) {
            continue;
        }
        DictEntry *entry = find_entry(dict, pairs[i].key);
        if (entry != NULL) {
            if (!append_value(entry, pairs[i].value)) {
                /* Possible weaknesses found:
                 *  previous implicit declaration is here
                 *  call to undeclared function 'free_dictionary'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  implicit declaration of function 'free_dictionary' [-Wimplicit-function-declaration]
                 */
                free_dictionary(dict);
                return NULL;
            }
        } else {
            if (!add_entry(dict, pairs[i].key, pairs[i].value)) {
                /* Possible weaknesses found:
                 *  call to undeclared function 'free_dictionary'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 */
                free_dictionary(dict);
                return NULL;
            }
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

void print_dictionary(const Dictionary *dict) {
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
        {"animal", "dog"},
        {"fruit", "cherry"}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary *dict = group_by_key(pairs, count);
    if (dict == NULL) {
        fprintf(stderr, "Failed to group key-value pairs\n");
        return EXIT_FAILURE;
    }

    print_dictionary(dict);
    free_dictionary(dict);

    return EXIT_SUCCESS;
}