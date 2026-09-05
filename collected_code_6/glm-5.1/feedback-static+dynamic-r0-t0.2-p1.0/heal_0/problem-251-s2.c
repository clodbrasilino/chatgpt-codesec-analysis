#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *insert_before_each(struct Node *head, int val) {
    if (head == NULL) {
        return NULL;
    }

    struct Node *current = head;
    while (current != NULL) {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        if (new_node == NULL) {
            struct Node *temp = head;
            while (temp != NULL) {
                struct Node *next = temp->next;
                free(temp);
                temp = next;
            }
            return NULL;
        }
        new_node->data = val;
        new_node->next = current->next;
        current->next = new_node;

        int temp_data = current->data;
        current->data = new_node->data;
        new_node->data = temp_data;

        current = new_node->next;
    }

    return head;
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

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
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

    print_list(head);

    head = insert_before_each(head, 0);
    if (head == NULL) {
        return 1;
    }

    print_list(head);

    free_list(head);

    return 0;
}