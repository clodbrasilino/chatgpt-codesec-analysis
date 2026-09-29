#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int length;
} SubListResult;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head_ref, int data) {
    Node *new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node *last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

SubListResult find_min_sublist(Node *head) {
    SubListResult result = {NULL, 0};
    if (head == NULL) {
        return result;
    }

    Node *min_start = NULL;
    Node *min_end = NULL;
    int min_len = 0;

    Node *curr_start = NULL;
    Node *curr_end = NULL;
    int curr_len = 0;

    Node *ptr = head;

    while (ptr != NULL) {
        if (ptr->data > 0) {
            if (curr_start == NULL) {
                curr_start = ptr;
            }
            curr_end = ptr;
            curr_len++;
        } else {
            if (curr_start != NULL) {
                if (min_start == NULL || curr_len < min_len) {
                    min_start = curr_start;
                    min_end = curr_end;
                    min_len = curr_len;
                }
                curr_start = NULL;
                curr_len = 0;
            }
        }
        ptr = ptr->next;
    }

    if (curr_start != NULL) {
        if (min_start == NULL || curr_len < min_len) {
            min_start = curr_start;
            min_end = curr_end;
            min_len = curr_len;
        }
    }

    if (min_start != NULL) {
        Node *new_head = NULL;
        Node *new_tail = NULL;
        ptr = min_start;
        while (ptr != min_end->next) {
            Node *new_node = create_node(ptr->data);
            if (new_head == NULL) {
                new_head = new_node;
                new_tail = new_node;
            } else {
                new_tail->next = new_node;
                new_tail = new_node;
            }
            ptr = ptr->next;
        }
        result.head = new_head;
        result.length = min_len;
    }

    return result;
}

void free_list(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node *head = NULL;
    append_node(&head, -1);
    append_node(&head, 5);
    append_node(&head, 6);
    append_node(&head, -2);
    append_node(&head, 3);
    append_node(&head, -4);
    append_node(&head, 8);
    append_node(&head, 9);
    append_node(&head, 10);
    append_node(&head, -5);

    SubListResult result = find_min_sublist(head);

    if (result.head != NULL) {
        printf("Minimum length sublist: ");
        Node *ptr = result.head;
        while (ptr != NULL) {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
        printf("\nLength: %d\n", result.length);
    } else {
        printf("No sublist found.\n");
    }

    free_list(head);
    free_list(result.head);

    return 0;
}