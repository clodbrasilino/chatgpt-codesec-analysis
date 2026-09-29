#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
Node* interleave_lists(Node* list1, Node* list2);
void print_list(Node* head);
void free_list(Node* head);

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* interleave_lists(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }

    Node* head = list1;
    Node* curr1 = list1;
    Node* curr2 = list2;
    Node* next1 = NULL;
    Node* next2 = NULL;

    while (curr1 != NULL && curr2 != NULL) {
        next1 = curr1->next;
        next2 = curr2->next;

        curr1->next = curr2;
        if (next1 != NULL) {
            curr2->next = next1;
        }

        curr1 = next1;
        curr2 = next2;
    }

    return head;
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* list1 = create_node(1);
    list1->next = create_node(3);
    list1->next->next = create_node(5);

    Node* list2 = create_node(2);
    list2->next = create_node(4);
    list2->next->next = create_node(6);

    Node* interleaved = interleave_lists(list1, list2);

    print_list(interleaved);

    free_list(interleaved);

    return EXIT_SUCCESS;
}