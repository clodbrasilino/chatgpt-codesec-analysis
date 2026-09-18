#include <stdio.h>
#include <stdlib.h>

struct list_node {
    int data;
    struct list_node *next;
};

struct list_node *rotate_right(struct list_node *head, size_t k);
struct list_node *create_node(int data);
void free_list(struct list_node *head);
void print_list(const struct list_node *head);

struct list_node *rotate_right(struct list_node *head, size_t k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    size_t len = 1;
    struct list_node *tail = head;
    
    while (tail->next != NULL) {
        tail = tail->next;
        len++;
    }

    k = k % len;
    if (k == 0) {
        return head;
    }

    size_t new_tail_pos = len - k;
    struct list_node *new_tail = head;
    
    for (size_t i = 1; i < new_tail_pos; i++) {
        new_tail = new_tail->next;
    }

    struct list_node *new_head = new_tail->next;
    new_tail->next = NULL;
    tail->next = head;

    return new_head;
}

struct list_node *create_node(int data) {
    struct list_node *new_node = malloc(sizeof(struct list_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct list_node *head) {
    struct list_node *current = head;
    while (current != NULL) {
        struct list_node *next_node = current->next;
        free(current);
        current = next_node;
    }
}

void print_list(const struct list_node *head) {
    const struct list_node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct list_node *head = NULL;
    struct list_node *tail = NULL;

    for (int i = 1; i <= 5; i++) {
        struct list_node *new_node = create_node(i);
        if (new_node == NULL) {
            free_list(head);
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    print_list(head);
    
    head = rotate_right(head, 2);
    
    print_list(head);
    
    free_list(head);

    return EXIT_SUCCESS;
}