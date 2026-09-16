#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int recursive_list_sum(const struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + recursive_list_sum(head->next);
}

struct Node* create_node(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    struct Node* head = create_node(1);
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

    int sum = recursive_list_sum(head);
    printf("Sum: %d\n", sum);

    free_list(head);

    return EXIT_SUCCESS;
}