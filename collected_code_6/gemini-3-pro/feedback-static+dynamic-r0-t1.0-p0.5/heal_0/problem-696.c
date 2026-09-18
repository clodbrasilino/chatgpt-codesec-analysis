#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list(Node* head) {
    List* new_list = (List*)malloc(sizeof(List));
    if (!new_list) {
        exit(EXIT_FAILURE);
    }
    new_list->head = head;
    new_list->next = NULL;
    return new_list;
}

void free_node_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_list_of_lists(List* head) {
    while (head) {
        List* temp = head;
        head = head->next;
        free_node_list(temp->head);
        free(temp);
    }
}

Node* copy_node_list(Node* head) {
    if (!head) return NULL;
    Node* new_head = create_node(head->data);
    Node* current = new_head;
    head = head->next;
    while (head) {
        current->next = create_node(head->data);
        current = current->next;
        head = head->next;
    }
    return new_head;
}

Node* concat_node_lists(Node* l1, Node* l2) {
    if (!l1) return copy_node_list(l2);
    Node* new_head = copy_node_list(l1);
    Node* current = new_head;
    while (current->next) {
        current = current->next;
    }
    current->next = copy_node_list(l2);
    return new_head;
}

List* zip_lists(List* l1, List* l2) {
    List* result_head = NULL;
    List* result_tail = NULL;

    while (l1 && l2) {
        Node* zipped_nodes = concat_node_lists(l1->head, l2->head);
        List* new_list = create_list(zipped_nodes);

        if (!result_head) {
            result_head = new_list;
            result_tail = new_list;
        } else {
            result_tail->next = new_list;
            result_tail = new_list;
        }

        l1 = l1->next;
        l2 = l2->next;
    }

    return result_head;
}

void print_node_list(Node* head) {
    printf("[");
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(", ");
        head = head->next;
    }
    printf("]");
}

void print_list_of_lists(List* head) {
    printf("[");
    while (head) {
        print_node_list(head->head);
        if (head->next) printf(", ");
        head = head->next;
    }
    printf("]\n");
}

int main(void) {
    Node* n1 = create_node(1);
    n1->next = create_node(2);
    List* l1 = create_list(n1);
    
    Node* n2 = create_node(3);
    l1->next = create_list(n2);

    Node* n3 = create_node(4);
    n3->next = create_node(5);
    List* l2 = create_list(n3);
    
    Node* n4 = create_node(6);
    l2->next = create_list(n4);

    List* zipped = zip_lists(l1, l2);

    print_list_of_lists(zipped);

    free_list_of_lists(l1);
    free_list_of_lists(l2);
    free_list_of_lists(zipped);

    return 0;
}