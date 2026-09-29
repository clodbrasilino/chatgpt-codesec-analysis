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

void free_list(Node *head) {
    Node *current = head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

SubListResult find_min_sublist(Node *head) {
    SubListResult result = {NULL, 0};
    if (head == NULL) {
        return result;
    }

    Node *min_start = NULL;
    int min_len = 0;
    int current_len = 0;
    Node *current_start = NULL;
    Node *current = head;

    while (current != NULL) {
        if (current->data > 0) {
            if (current_len == 0) {
                current_start = current;
            }
            current_len++;
        } else {
            if (current_len > 0) {
                if (min_len == 0 || current_len < min_len) {
                    min_len = current_len;
                    min_start = current_start;
                }
                current_len = 0;
            }
        }
        current = current->next;
    }

    if (current_len > 0) {
        if (min_len == 0 || current_len < min_len) {
            min_len = current_len;
            min_start = current_start;
        }
    }

    result.length = min_len;

    if (min_start != NULL && min_len > 0) {
        result.head = create_node(min_start->data);
        Node *temp = result.head;
        Node *src = min_start->next;
        for (int i = 1; i < min_len; i++) {
            temp->next = create_node(src->data);
            temp = temp->next;
            src = src->next;
        }
    }

    return result;
}

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(-1);
    head->next->next->next = create_node(5);
    head->next->next->next->next = create_node(-2);
    head->next->next->next->next->next = create_node(3);

    SubListResult result = find_min_sublist(head);

    if (result.head != NULL) {
        Node *curr = result.head;
        while (curr != NULL) {
            printf("%d ", curr->data);
            curr = curr->next;
        }
        printf("\nLength: %d\n", result.length);
    } else {
        printf("No sublist found\n");
    }

    free_list(result.head);
    free_list(head);

    return 0;
}