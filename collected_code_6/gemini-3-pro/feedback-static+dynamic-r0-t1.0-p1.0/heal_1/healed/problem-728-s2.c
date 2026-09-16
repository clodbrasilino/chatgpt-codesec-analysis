#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int sum_lists(struct Node* list1, struct Node* list2) {
    int sum = 0;
    
    struct Node* current = list1;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    
    current = list2;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    
    return sum;
}

void free_list(struct Node* head) {
    while (head != NULL) {
        struct Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    push(&list1, 3);
    push(&list1, 2);
    push(&list1, 1);

    push(&list2, 6);
    push(&list2, 5);
    push(&list2, 4);

    int total_sum = sum_lists(list1, list2);

    printf("Sum of elements in both lists: %d\n", total_sum);

    free_list(list1);
    free_list(list2);

    return EXIT_SUCCESS;
}