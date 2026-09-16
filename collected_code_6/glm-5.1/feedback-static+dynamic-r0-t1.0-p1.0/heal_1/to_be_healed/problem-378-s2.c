#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *shift_last_to_first(struct Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Node *second_to_last = head;
    while (second_to_last->next->next != NULL) {
        second_to_last = second_to_last->next;
    }

    struct Node *last = second_to_last->next;
    second_to_last->next = NULL;
    last->next = head;
    head = last;

    return head;
}

void free_list(struct Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

struct Node *create_node(int data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node *head = create_node(1);
    if (head == NULL) {
        return 1;
    }

    head->next = create_node(2);
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }

    head->next->next = create_node(3);
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }

    head->next->next->next = create_node(4);
    if (head->next->next->next == NULL) {
        free_list(head);
        return 1;
    }

    print_list(head);
    head = shift_last_to_first(head);
    print_list(head);
    free_list(head);

    return 0;
}