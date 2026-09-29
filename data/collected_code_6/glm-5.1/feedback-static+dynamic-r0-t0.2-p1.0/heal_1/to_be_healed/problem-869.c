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

Node *remove_sublists(Node *head, int min_val, int max_val) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *curr = head;

    while (curr != NULL) {
        /* Possible weaknesses found:
         *  Variable 'range' can be declared as pointer to const [constVariablePointer]
         */
        Range *range = (Range *)curr->data;
        if (range != NULL && (range->start < min_val || range->end > max_val)) {
            prev->next = curr->next;
            if (curr->data != NULL) {
                free(curr->data);
            }
            free(curr);
            curr = prev->next;
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
        /* Possible weaknesses found:
         *  Variable 'range' can be declared as pointer to const [constVariablePointer]
         */
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
    head->next = create_sublist(3, 8);
    head->next->next = create_sublist(2, 4);
    head->next->next->next = create_sublist(6, 10);

    printf("Original list:\n");
    print_list(head);

    int min_val = 2;
    int max_val = 8;
    head = remove_sublists(head, min_val, max_val);

    printf("List after removing sublists outside [%d, %d]:\n", min_val, max_val);
    print_list(head);

    free_list(head);

    return 0;
}