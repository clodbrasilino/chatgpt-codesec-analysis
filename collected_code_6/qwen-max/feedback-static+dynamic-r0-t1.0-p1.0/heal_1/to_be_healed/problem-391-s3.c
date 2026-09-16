#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

typedef struct {
    char *key;
    void *value;
    struct Dictionary *children;
} Dictionary;

List *create_list() {
    return (List *)calloc(1, sizeof(List));
}

Node *create_node(char *key, void *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

void append_to_list(List *list, Node *node) {
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            /* Possible weaknesses found:
             *  assignment to 'Node *' from incompatible pointer type 'struct Node *' [-Wincompatible-pointer-types]
             */
            current = current->next;
        }
        /* Possible weaknesses found:
         *  assignment to 'struct Node *' from incompatible pointer type 'Node *' [-Wincompatible-pointer-types]
         */
        current->next = node;
    }
    list->size++;
}

Dictionary *create_dictionary() {
    return (Dictionary *)calloc(1, sizeof(Dictionary));
}

void add_to_dictionary(Dictionary *dict, char *key, void *value) {
    dict->key = strdup(key);
    dict->value = value;
    /* Possible weaknesses found:
     *  assignment to 'struct Dictionary *' from incompatible pointer type 'Dictionary *' [-Wincompatible-pointer-types]
     */
    dict->children = create_dictionary();
}

void convert_lists_to_nested_dict(List *lists[], int num_lists, Dictionary *dict) {
    for (int i = 0; i < num_lists; ++i) {
        Node *current = lists[i]->head;
        Dictionary *current_dict = dict;
        while (current != NULL) {
            if (current_dict->value == NULL) {
                add_to_dictionary(current_dict, current->key, NULL);
            }
            if (strcasecmp(current_dict->key, current->key) == 0) {
                /* Possible weaknesses found:
                 *  assignment to 'Dictionary *' from incompatible pointer type 'struct Dictionary *' [-Wincompatible-pointer-types]
                 */
                current_dict = current_dict->children;
            }
            /* Possible weaknesses found:
             *  assignment to 'Node *' from incompatible pointer type 'struct Node *' [-Wincompatible-pointer-types]
             */
            current = current->next;
        }
    }
}

void free_node(Node *node) {
    if (node) {
        free(node->key);
        free(node);
    }
}

void free_list(List *list) {
    if (list) {
        Node *current = list->head;
        Node *next = NULL;
        while (current != NULL) {
            /* Possible weaknesses found:
             *  assignment to 'Node *' from incompatible pointer type 'struct Node *' [-Wincompatible-pointer-types]
             */
            next = current->next;
            free_node(current);
            current = next;
        }
        free(list);
    }
}

/* Possible weaknesses found:
 *  expected 'Dictionary *' but argument is of type 'struct Dictionary *'
 */
void free_dictionary(Dictionary *dict) {
    if (dict) {
        /* Possible weaknesses found:
         *  passing argument 1 of 'free_dictionary' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        free_dictionary(dict->children);
        free(dict->key);
        free(dict);
    }
}

int main() {
    List *list1 = create_list();
    List *list2 = create_list();
    List *list3 = create_list();

    append_to_list(list1, create_node("a", NULL));
    append_to_list(list1, create_node("b", NULL));
    append_to_list(list1, create_node("c", NULL));

    append_to_list(list2, create_node("d", NULL));
    append_to_list(list2, create_node("e", NULL));

    append_to_list(list3, create_node("f", NULL));
    append_to_list(list3, create_node("g", NULL));

    List *lists[] = {list1, list2, list3};
    Dictionary *root_dict = create_dictionary();
    convert_lists_to_nested_dict(lists, 3, root_dict);

    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_dictionary(root_dict);
    return 0;
}