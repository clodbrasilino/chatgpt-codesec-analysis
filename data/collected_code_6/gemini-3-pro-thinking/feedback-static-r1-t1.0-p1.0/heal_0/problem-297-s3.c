#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_ATOM,
    NODE_LIST
} NodeType;

typedef struct Node {
    NodeType type;
    union {
        int atom_value;
        struct Node* list_head;
    } data;
    struct Node* next;
} Node;

Node* create_atom(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        exit(EXIT_FAILURE);
    }
    node->type = NODE_ATOM;
    node->data.atom_value = value;
    node->next = NULL;
    return node;
}

Node* create_list(Node* head) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        exit(EXIT_FAILURE);
    }
    node->type = NODE_LIST;
    node->data.list_head = head;
    node->next = NULL;
    return node;
}

void flatten_helper(Node* curr, Node*** tail_link) {
    while (curr) {
        if (curr->type == NODE_ATOM) {
            Node* new_node = create_atom(curr->data.atom_value);
            **tail_link = new_node;
            *tail_link = &(new_node->next);
        } else if (curr->type == NODE_LIST) {
            flatten_helper(curr->data.list_head, tail_link);
        }
        curr = curr->next;
    }
}

Node* flatten(Node* head) {
    Node* flat_head = NULL;
    Node** tail_link = &flat_head;
    flatten_helper(head, &tail_link);
    return flat_head;
}

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        if (head->type == NODE_LIST) {
            free_list(head->data.list_head);
        }
        head = head->next;
        free(temp);
    }
}

void print_list(Node* head) {
    while (head) {
        if (head->type == NODE_ATOM) {
            printf("%d ", head->data.atom_value);
        }
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node* l1 = create_atom(1);
    l1->next = create_atom(2);

    Node* l2 = create_atom(4);
    l2->next = create_atom(5);
    
    Node* l3 = create_list(l2);
    l3->next = create_atom(6);

    Node* nested = create_list(l1);
    nested->next = create_atom(3);
    nested->next->next = create_list(l3);
    nested->next->next->next = create_atom(7);

    Node* flat = flatten(nested);

    print_list(flat);

    free_list(nested);
    free_list(flat);

    return EXIT_SUCCESS;
}