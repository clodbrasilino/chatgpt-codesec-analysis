#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *node = malloc(sizeof(struct Node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int append(struct Node **head_ref, int data) {
    struct Node *new_node = create_node(data);
    if (!new_node) {
        return 0;
    }
    if (!*head_ref) {
        *head_ref = new_node;
        return 1;
    }
    struct Node *last = *head_ref;
    while (last->next) {
        last = last->next;
    }
    last->next = new_node;
    return 1;
}

struct Node *alternate_list(struct Node *head) {
    struct Node *new_head = NULL;
    struct Node *new_tail = NULL;
    struct Node *current = head;
    int take = 1;

    while (current) {
        if (take) {
            struct Node *new_node = create_node(current->data);
            if (!new_node) {
                free_list(new_head);
                return NULL;
            }
            if (!new_head) {
                new_head = new_node;
                new_tail = new_node;
            } else {
                new_tail->next = new_node;
                new_tail = new_node;
            }
        }
        take = !take;
        current = current->next;
    }
    return new_head;
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *original = NULL;
    
    if (!append(&original, 1) || !append(&original, 2) || !append(&original, 3) ||
        !append(&original, 4) || !append(&original, 5)) {
        free_list(original);
        return EXIT_FAILURE;
    }

    struct Node *alt = alternate_list(original);
    if (!alt) {
        free_list(original);
        return EXIT_FAILURE;
    }

    printf("Original: ");
    print_list(original);
    printf("Alternate: ");
    print_list(alt);

    free_list(original);
    free_list(alt);

    return EXIT_SUCCESS;
}