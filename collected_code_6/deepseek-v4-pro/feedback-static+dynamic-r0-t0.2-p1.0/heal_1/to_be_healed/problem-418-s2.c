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
    /* Possible weaknesses found:
     *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
     */
    Node *max_end = head;
    int max_length = 1;

    Node *temp_start = head;
    Node *temp_end = head;
    int temp_length = 1;

    while (current->next != NULL) {
        if (current->next->data == current->data) {
            temp_end = current->next;
            temp_length++;
        } else {
            if (temp_length > max_length) {
                max_length = temp_length;
                max_start = temp_start;
                /* Possible weaknesses found:
                 *  Value stored to 'max_end' is never read [deadcode.DeadStores]
                 *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
                 */
                max_end = temp_end;
            }
            temp_start = current->next;
            temp_end = current->next;
            temp_length = 1;
        }
        current = current->next;
    }

    if (temp_length > max_length) {
        max_length = temp_length;
        max_start = temp_start;
        /* Possible weaknesses found:
         *  Value stored to 'max_end' is never read [deadcode.DeadStores]
         *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
         */
        max_end = temp_end;
    }

    result.head = max_start;
    result.length = max_length;
    return result;
}

Node *copy_sublist(Node *start, int length) {
    if (start == NULL || length <= 0) {
        return NULL;
    }

    Node *new_head = NULL;
    Node *new_tail = NULL;
    Node *current = start;

    for (int i = 0; i < length && current != NULL; i++) {
        Node *new_node = create_node(current->data);
        if (new_node == NULL) {
            free_list(new_head);
            return NULL;
        }
        if (new_head == NULL) {
            new_head = new_node;
            new_tail = new_node;
        } else {
            new_tail->next = new_node;
            new_tail = new_node;
        }
        current = current->next;
    }

    return new_head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int values[] = {1, 1, 2, 2, 2, 3, 4, 4, 4, 4, 5};
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

    printf("Original list: ");
    print_list(head);

    Sublist max_sub = find_max_sublist(head);
    Node *max_sublist_copy = copy_sublist(max_sub.head, max_sub.length);

    printf("Maximum sublist: ");
    print_list(max_sublist_copy);
    printf("Length: %d\n", max_sub.length);

    free_list(max_sublist_copy);
    free_list(head);

    return 0;
}