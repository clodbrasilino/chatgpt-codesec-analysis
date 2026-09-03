#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
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

Node *remove_tuples(Node *head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }

    Node *current = head;
    Node *prev = NULL;
    int count = 0;

    while (current != NULL) {
        count++;
        if (count == k) {
            Node *tuple_start = prev == NULL ? head : prev->next;
            /* Possible weaknesses found:
             *  Variable 'tuple_end' can be declared as pointer to const [constVariablePointer]
             *  Variable 'tuple_end' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'tuple_end' during its initialization is never read [deadcode.DeadStores]
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
            count = 0;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

int main(void) {
    Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        append_node(&head, values[i]);
    }

    printf("Original list: ");
    print_list(head);

    int k = 3;
    head = remove_tuples(head, k);

    printf("After removing tuples of length %d: ", k);
    print_list(head);

    free_list(head);
    return 0;
}