#include <stdio.h>
#include <stdlib.h>

typedef enum { VAL, DICT } NodeType;

typedef struct Node {
    const char *key;
    NodeType type;
    union {
        int val;
        struct Dictionary *dict;
    } data;
    struct Node *next;
} Node;

typedef struct Dictionary {
    Node *head;
} Dictionary;

int find_depth(Dictionary *dict) {
    if (dict == NULL) {
        return 0;
    }
    int max_depth = 1;
    Node *current = dict->head;
    while (current != NULL) {
        if (current->type == DICT) {
            int child_depth = find_depth(current->data.dict);
            if (child_depth + 1 > max_depth) {
                max_depth = child_depth + 1;
            }
        }
        current = current->next;
    }
    return max_depth;
}

Dictionary* create_dict() {
    Dictionary *d = malloc(sizeof(Dictionary));
    if (d == NULL) {
        return NULL;
    }
    d->head = NULL;
    return d;
}

Node* create_val_node(const char *key, int val) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return NULL;
    }
    n->key = key;
    n->type = VAL;
    n->data.val = val;
    n->next = NULL;
    return n;
}

Node* create_dict_node(const char *key, Dictionary *dict) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        return NULL;
    }
    n->key = key;
    n->type = DICT;
    n->data.dict = dict;
    n->next = NULL;
    return n;
}

void add_node(Dictionary *dict, Node *node) {
    if (dict == NULL || node == NULL) {
        return;
    }
    node->next = dict->head;
    dict->head = node;
}

void free_dict(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    Node *current = dict->head;
    while (current != NULL) {
        Node *next = current->next;
        if (current->type == DICT) {
            free_dict(current->data.dict);
        }
        free(current);
        current = next;
    }
    free(dict);
}

int main() {
    Dictionary *d1 = create_dict();
    if (d1 == NULL) {
        return 1;
    }
    add_node(d1, create_val_node("a", 1));

    Dictionary *d2 = create_dict();
    if (d2 == NULL) {
        free_dict(d1);
        return 1;
    }
    add_node(d2, create_val_node("b", 2));
    add_node(d2, create_dict_node("c", d1));

    Dictionary *d3 = create_dict();
    if (d3 == NULL) {
        free_dict(d2);
        return 1;
    }
    add_node(d3, create_val_node("d", 3));
    add_node(d3, create_dict_node("e", d2));

    printf("%d\n", find_depth(d3));

    free_dict(d3);

    return 0;
}