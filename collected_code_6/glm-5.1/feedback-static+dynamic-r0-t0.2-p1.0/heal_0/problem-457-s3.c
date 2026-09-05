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

    if (min_start != NULL) {
        Node *sub_head = NULL;
        Node *sub_tail = NULL;
        Node *temp = min_start;
        for (int i = 0; i < min_len; i++) {
            Node *new_node = create_node(temp->data);
            if (sub_head == NULL) {
                sub_head = new_node;
                sub_tail = new_node;
            } else {
                sub_tail->next = new_node;
                sub_tail = new_node;
            }
            temp = temp->next;
        }
        result.head = sub_head;
        result.length = min_len;
    }

    return result;
}

int main() {
    Node *head = create_node(0);
    head->next = create_node(1);
    head->next->next = create_node(2);
    head->next->next->next = create_node(0);
    head->next->next->next->next = create_node(3);
    head->next->next->next->next->next = create_node(4);
    head->next->next->next->next->next->next = create_node(5);
    head->next->next->next->next->next->next->next = create_node(0);
    head->next->next->next->next->next->next->next->next = create_node(6);

    SubListResult result = find_min_sublist(head);

    if (result.head != NULL) {
        printf("Minimum sublist length: %d\n", result.length);
        printf("Sublist elements: ");
        Node *curr = result.head;
        while (curr != NULL) {
            printf("%d ", curr->data);
            curr = curr->next;
        }
        printf("\n");
    } else {
        printf("No sublist found.\n");
    }

    free_list(head);
    free_list(result.head);

    return 0;
}