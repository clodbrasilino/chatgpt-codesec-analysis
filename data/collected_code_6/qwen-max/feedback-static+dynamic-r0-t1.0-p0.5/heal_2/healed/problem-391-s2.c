#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    void *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->head = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, void *value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = dict->head;
    dict->head = new_node;
}

Dictionary* list_to_nested_dict(char **keys, int keys_len, char ***lists, const int *list_sizes) {
    if (keys_len != (int)(sizeof(lists) / sizeof(lists[0]))) return NULL;
    
    Dictionary *root = create_dictionary();
    for (int i = 0; i < keys_len; ++i) {
        Dictionary *current_dict = root;
        for (int j = 0; j < list_sizes[i]; ++j) {
            Dictionary *new_dict = create_dictionary();
            add_to_dictionary(current_dict, lists[i][j], new_dict);
            current_dict = new_dict;
        }
        add_to_dictionary(root, keys[i], current_dict);
    }
    return root;
}

void free_dictionary(Dictionary *dict) {
    Node *current = dict->head;
    while (current) {
        Node *next = current->next;
        free(current->key);
        if (current->value) free_dictionary((Dictionary*)current->value);
        free(current);
        current = next;
    }
    free(dict);
}

void print_dictionary(Dictionary *dict, int depth) {
    Node *current = dict->head;
    while (current) {
        for (int i = 0; i < depth; ++i) printf("  ");
        printf("%s: ", current->key);
        if (current->value == NULL || ((Dictionary*)current->value)->head == NULL) {
            printf("None\n");
        } else {
            printf("\n");
            print_dictionary((Dictionary*)current->value, depth + 1);
        }
        current = current->next;
    }
}

int main() {
    char *keys[] = {"key1", "key2"};
    char *list1[] = {"a", "b", "c"};
    char *list2[] = {"x", "y", "z"};
    char **lists[] = {list1, list2};
    const int list_sizes[] = {3, 3};
    int keys_len = 2;

    Dictionary *nested_dict = list_to_nested_dict(keys, keys_len, lists, list_sizes);
    print_dictionary(nested_dict, 0);
    free_dictionary(nested_dict);

    return 0;
}