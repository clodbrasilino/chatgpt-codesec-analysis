#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int list_length(Node *head) {
    int length = 0;
    Node *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int find_max_length_list(Node **lists, int num_lists) {
    if (lists == NULL || num_lists <= 0) {
        return -1;
    }
    int max_index = 0;
    int max_len = list_length(lists[0]);
    for (int i = 1; i < num_lists; i++) {
        int current_len = list_length(lists[i]);
        if (current_len > max_len) {
            max_len = current_len;
            max_index = i;
        }
    }
    return max_index;
}

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

Node *append_node(Node *head, int value) {
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return head;
    }
    if (head == NULL) {
        return new_node;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
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

int main(void) {
    int num_lists = 3;
    Node **lists = (Node **)malloc(num_lists * sizeof(Node *));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0] = NULL;
    lists[1] = NULL;
    lists[2] = NULL;

    lists[0] = append_node(lists[0], 1);
    lists[0] = append_node(lists[0], 2);
    lists[0] = append_node(lists[0], 3);

    lists[1] = append_node(lists[1], 4);
    lists[1] = append_node(lists[1], 5);

    lists[2] = append_node(lists[2], 6);

    int max_index = find_max_length_list(lists, num_lists);
    if (max_index != -1) {
        printf("List with maximum length is at index %d with length %d\n", max_index, list_length(lists[max_index]));
    }

    for (int i = 0; i < num_lists; i++) {
        free_list(lists[i]);
    }
    free(lists);

    return EXIT_SUCCESS;
}