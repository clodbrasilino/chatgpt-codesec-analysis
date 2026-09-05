#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    int start;
    int end;
} Range;

Node *create_node(void *data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *create_sublist(int start, int end) {
    Range *range = (Range *)malloc(sizeof(Range));
    if (range == NULL) {
        exit(EXIT_FAILURE);
    }
    range->start = start;
    range->end = end;
    return create_node(range);
}

Node *remove_out_of_range(Node *head, int min_val, int max_val) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *curr = head;

    while (curr != NULL) {
        Range *range = (Range *)curr->data;
        if (range == NULL) {
            prev = curr;
            curr = curr->next;
            continue;
        }

        if (range->start < min_val || range->end > max_val) {
            Node *to_delete = curr;
            prev->next = curr->next;
            curr = curr->next;
            free(to_delete->data);
            free(to_delete);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        if (curr->data != NULL) {
            free(curr->data);
        }
        free(curr);
        curr = next;
    }
}

void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Range *range = (Range *)curr->data;
        if (range != NULL) {
            printf("[%d, %d] ", range->start, range->end);
        }
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = create_sublist(1, 5);
    head->next = create_sublist(2, 8);
    head->next->next = create_sublist(0, 3);
    head->next->next->next = create_sublist(4, 9);

    printf("Original list:\n");
    print_list(head);

    int min_val = 1;
    int max_val = 8;

    head = remove_out_of_range(head, min_val, max_val);

    printf("List after removing out of range [%d, %d]:\n", min_val, max_val);
    print_list(head);

    free_list(head);

    return 0;
}