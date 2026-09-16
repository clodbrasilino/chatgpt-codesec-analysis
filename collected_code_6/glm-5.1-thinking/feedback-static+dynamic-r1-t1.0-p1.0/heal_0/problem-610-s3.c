#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

struct Node *append_node(struct Node *head, int data) {
    if (head == NULL) {
        return create_node(data);
    }
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = create_node(data);
    return head;
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

struct Node *remove_kth(struct Node *head, int k) {
    if (head == NULL || k < 1) {
        return head;
    }
    if (k == 1) {
        struct Node *new_head = head->next;
        free(head);
        return new_head;
    }
    struct Node *current = head;
    for (int i = 1; i < k - 1; i++) {
        if (current == NULL) {
            return head;
        }
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        return head;
    }
    struct Node *to_remove = current->next;
    current->next = to_remove->next;
    free(to_remove);
    return head;
}

int main(void) {
    struct Node *list = NULL;
    for (int i = 1; i <= 5; i++) {
        list = append_node(list, i);
    }
    print_list(list);
    list = remove_kth(list, 3);
    print_list(list);
    list = remove_kth(list, 1);
    print_list(list);
    list = remove_kth(list, 10);
    print_list(list);
    list = remove_kth(list, 0);
    print_list(list);
    list = remove_kth(NULL, 2);
    print_list(list);
    free_list(list);
    return 0;
}