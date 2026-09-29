#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct Node {
    int data;
    struct Node* next;
};

struct Tuple {
    int* data;
    size_t size;
};

struct Tuple* convert_list_to_tuple(const struct Node* head) {
    size_t count = 0;
    const struct Node* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }

    struct Tuple* tuple = (struct Tuple*)malloc(sizeof(struct Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = count;
    
    if (count == 0) {
        tuple->data = NULL;
        return tuple;
    }

    tuple->data = (int*)malloc(count * sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }

    current = head;
    size_t i = 0;
    while (current != NULL) {
        tuple->data[i] = current->data;
        current = current->next;
        i++;
    }

    return tuple;
}

struct Node* create_node(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void free_tuple(struct Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

int main(void) {
    struct Node* head = create_node(10);
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    
    head->next = create_node(20);
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    head->next->next = create_node(30);
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    struct Tuple* tuple = convert_list_to_tuple(head);
    if (tuple == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d ", tuple->data[i]);
    }
    printf("\n");

    free_list(head);
    free_tuple(tuple);

    return EXIT_SUCCESS;
}