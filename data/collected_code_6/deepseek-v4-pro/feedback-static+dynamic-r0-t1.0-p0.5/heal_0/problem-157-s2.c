#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    int value;
    int count;
    struct ListNode *next;
} ListNode;

ListNode *create_node(int value, int count) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->count = count;
    node->next = NULL;
    return node;
}

void append_node(ListNode **head, ListNode **tail, int value, int count) {
    ListNode *node = create_node(value, count);
    if (node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
}

void free_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current);
        current = next;
    }
}

ListNode *run_length_encode(const int *input, int length) {
    if (input == NULL || length <= 0) {
        return NULL;
    }

    ListNode *head = NULL;
    ListNode *tail = NULL;
    int current_value = input[0];
    int current_count = 1;

    for (int i = 1; i < length; i++) {
        if (input[i] == current_value) {
            current_count++;
        } else {
            append_node(&head, &tail, current_value, current_count);
            current_value = input[i];
            current_count = 1;
        }
    }
    append_node(&head, &tail, current_value, current_count);

    return head;
}

void print_encoded_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        printf("(%d,%d) ", current->value, current->count);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int input[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 1};
    int length = sizeof(input) / sizeof(input[0]);

    ListNode *encoded = run_length_encode(input, length);
    if (encoded == NULL) {
        fprintf(stderr, "Encoding failed\n");
        return EXIT_FAILURE;
    }

    print_encoded_list(encoded);
    free_list(encoded);

    return EXIT_SUCCESS;
}