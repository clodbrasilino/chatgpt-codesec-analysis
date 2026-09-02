#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int length;
} Sublist;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Sublist find_max_sublist(Node *head) {
    Sublist result;
    result.head = NULL;
    result.length = 0;

    if (head == NULL) {
        return result;
    }

    Node *current = head;
    Node *max_start = head;
    int max_length = 1;

    Node *temp_start = head;
    /* Possible weaknesses found:
     *  Variable 'temp_end' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'temp_end' can be reduced. [variableScope]
     */
    Node *temp_end = head;
    int temp_length = 1;

    while (current->next != NULL) {
        if (current->next->data > current->data) {
            /* Possible weaknesses found:
             *  Variable 'temp_end' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'temp_end' is never read [deadcode.DeadStores]
             */
            temp_end = current->next;
            temp_length++;
        } else {
            if (temp_length > max_length) {
                max_length = temp_length;
                max_start = temp_start;
            }
            temp_start = current->next;
            /* Possible weaknesses found:
             *  Variable 'temp_end' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'temp_end' is never read [deadcode.DeadStores]
             */
            temp_end = current->next;
            temp_length = 1;
        }
        current = current->next;
    }

    if (temp_length > max_length) {
        max_length = temp_length;
        max_start = temp_start;
    }

    result.head = max_start;
    result.length = max_length;
    return result;
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int values[] = {1, 2, 3, 2, 4, 5, 6, 7, 1, 2};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        Node *new_node = create_node(values[i]);
        if (new_node == NULL) {
            free_list(head);
            return 1;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    Sublist max_sublist = find_max_sublist(head);

    printf("Maximum increasing sublist length: %d\n", max_sublist.length);
    printf("Sublist elements: ");
    Node *current = max_sublist.head;
    for (int i = 0; i < max_sublist.length && current != NULL; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(head);
    return 0;
}