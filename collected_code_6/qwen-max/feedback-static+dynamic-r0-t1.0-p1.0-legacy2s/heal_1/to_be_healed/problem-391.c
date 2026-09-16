#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    char *key;
    struct _node *value;
    struct _node *next;
} Node;

typedef struct _dict {
    Node *head;
} Dict;

Dict* create_dict() {
    return (Dict*)malloc(sizeof(Dict));
}

/* Possible weaknesses found:
 *  expected 'Dict *' {aka 'struct _dict *'} but argument is of type 'struct _node *'
 */
Node* create_node(char *key, Dict *value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = (struct _node*)value;
    node->next = NULL;
    return node;
}

void add_to_dict(Dict *dict, char *key, Dict *value) {
    if (!dict || !key) return;
    /* Possible weaknesses found:
     *  passing argument 2 of 'create_node' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    Node *new_node = create_node(key, (struct _node*)value);
    new_node->next = dict->head;
    dict->head = new_node;
}

Dict* list_to_nested_dict(int count, char **lists[]) {
    if (count < 2) return NULL;
    Dict *result = create_dict();
    
    for (int i = 0; lists[0][i] != NULL; ++i) {
        Dict *current = result;
        for (int j = 1; j < count && lists[j][i] != NULL; ++j) {
            int found = 0;
            for (Node *n = current->head; n != NULL; n = n->next) {
                if (strcmp(n->key, lists[j-1][i]) == 0) {
                    current = (Dict*)n->value;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                Dict *new_dict = create_dict();
                add_to_dict(current, lists[j-1][i], new_dict);
                current = new_dict;
            }
        }
        add_to_dict(current, lists[count-1][i], create_dict());
    }

    return result;
}

void free_dict(Dict *dict) {
    if (!dict) return;
    while (dict->head) {
        Node *temp = dict->head;
        dict->head = dict->head->next;
        free(temp->key);
        free_dict((Dict*)temp->value);
        free(temp);
    }
    free(dict);
}

void print_dict(Dict *dict, int level) {
    for (Node *n = dict->head; n != NULL; n = n->next) {
        for (int i = 0; i < level; ++i) printf("  ");
        printf("%s: ", n->key);
        /* Possible weaknesses found:
         *  Return value of allocation function 'create_dict' is not stored. [leakReturnValNotUsed]
         */
        if (n->value != (struct _node*)create_dict())
            print_dict((Dict*)n->value, level + 1);
        else
            printf("(empty)\n");
    }
}

int main() {
    char *list1[] = {"a", "b", "c", NULL};
    char *list2[] = {"x", "y", "z", NULL};
    char *list3[] = {"1", "2", "3", NULL};
    char **lists[] = {list1, list2, list3};

    Dict *nested_dict = list_to_nested_dict(3, lists);
    print_dict(nested_dict, 0);

    free_dict(nested_dict);

    return 0;
}