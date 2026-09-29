#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

Node *remove_tuples_of_length_k(Node *head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }

    Node *current = head;
    Node *prev = NULL;
    int count = 1;

    while (current != NULL) {
        if (count == k) {
            Node *tuple_start = (prev == NULL) ? head : prev->next;
            /* Possible weaknesses found:
             *  Value stored to 'tuple_end' during its initialization is never read [deadcode.DeadStores]
             *  Variable 'tuple_end' is assigned a value that is never used. [unreadVariable]
             *  Variable 'tuple_end' can be declared as pointer to const [constVariablePointer]
             */
            Node *tuple_end = current;
            Node *next_node = current->next;

            if (prev == NULL) {
                head = next_node;
            } else {
                prev->next = next_node;
            }

            Node *temp = tuple_start;
            while (temp != NULL && temp != next_node) {
                Node *to_free = temp;
                temp = temp->next;
                free(to_free);
            }

            current = next_node;
            count = 1;
        } else {
            prev = current;
            current = current->next;
            count++;
        }
    }

    return head;
}

int main(void) {
    Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(values) / sizeof(values[0]);
    int k = 3;

    for (int i = 0; i < n; i++) {
        append_node(&head, values[i]);
    }

    printf("Original list: ");
    print_list(head);

    head = remove_tuples_of_length_k(head, k);

    printf("List after removing tuples of length %d: ", k);
    print_list(head);

    free_list(head);
    return 0;
}