#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int recursive_sum(const struct Node* head);
struct Node* create_node(int data);
void free_list(struct Node* head);

int recursive_sum(const struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + recursive_sum(head->next);
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
    struct Node* current = head;
    struct Node* next_node = NULL;
    
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
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

    head->next->next->next = create_node(40);
    if (head->next->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    int total_sum = recursive_sum(head);
    
    printf("%d\n", total_sum);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}