#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data);
struct Node *remove_even(struct Node *head);
void print_list(const struct Node *head);
void free_list(struct Node *head);

struct Node *create_node(int data) {
    struct Node *new_node = malloc(sizeof(*new_node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

struct Node *remove_even(struct Node *head) {
    struct Node dummy;
    struct Node *prev = &dummy;
    struct Node *curr = head;
    dummy.next = head;

    while (curr != NULL) {
        if (curr->data % 2 == 0) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}

void print_list(const struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(struct Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    struct Node *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    int values[] = {1, 2, 3, 4, 5, 6};
    size_t i;

    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        struct Node *new_node = create_node(values[i]);
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    printf("Original list: ");
    print_list(head);

    head = remove_even(head);

    printf("After removing even numbers: ");
    print_list(head);

    free_list(head);

    return 0;
}