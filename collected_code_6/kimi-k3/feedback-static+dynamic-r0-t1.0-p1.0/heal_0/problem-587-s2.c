#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    int* elements;
    size_t size;
} Tuple;

Tuple* list_to_tuple(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    size_t count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = (int*)malloc(count * sizeof(int));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->size = count;

    current = head;
    for (size_t i = 0; i < count; i++) {
        tuple->elements[i] = current->data;
        current = current->next;
    }

    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int main(void) {
    Node* head = create_node(1);
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    head->next = create_node(2);
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    head->next->next = create_node(3);
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    Tuple* tuple = list_to_tuple(head);
    if (tuple == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("Tuple: (");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free_tuple(tuple);
    free_list(head);

    return EXIT_SUCCESS;
}