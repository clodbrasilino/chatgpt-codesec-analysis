#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    int count;
    struct Node *next;
} Node;

Node *create_node(int value, int count) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->count = count;
    node->next = NULL;
    return node;
}

void append_node(Node **head, Node **tail, int value, int count) {
    Node *node = create_node(value, count);
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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Node *modified_run_length_encode(int *input, int length) {
    if (input == NULL || length <= 0) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    int i = 0;

    while (i < length) {
        int current_value = input[i];
        int count = 1;
        int j = i + 1;

        while (j < length && input[j] == current_value) {
            count++;
            j++;
        }

        if (count > 1) {
            append_node(&head, &tail, current_value, count);
        } else {
            int single_start = i;
            int single_count = 0;
            int k = i;

            while (k < length) {
                if (k + 1 < length && input[k] == input[k + 1]) {
                    break;
                }
                single_count++;
                k++;
            }

            if (single_count == 1) {
                append_node(&head, &tail, current_value, 1);
            } else {
                append_node(&head, &tail, -single_count, 0);
                for (int m = single_start; m < single_start + single_count; m++) {
                    append_node(&head, &tail, input[m], 1);
                }
            }
            i = k;
            continue;
        }

        i = j;
    }

    return head;
}

void print_encoded_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        if (current->count == 0) {
            printf("[%d]", current->value);
        } else {
            printf("[%d,%d]", current->value, current->count);
        }
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int test1[] = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 5};
    int len1 = sizeof(test1) / sizeof(test1[0]);
    Node *result1 = modified_run_length_encode(test1, len1);
    printf("Test 1: ");
    print_encoded_list(result1);
    free_list(result1);

    int test2[] = {1, 2, 3, 4, 5};
    int len2 = sizeof(test2) / sizeof(test2[0]);
    Node *result2 = modified_run_length_encode(test2, len2);
    printf("Test 2: ");
    print_encoded_list(result2);
    free_list(result2);

    int test3[] = {1, 1, 2, 2, 3, 3};
    int len3 = sizeof(test3) / sizeof(test3[0]);
    Node *result3 = modified_run_length_encode(test3, len3);
    printf("Test 3: ");
    print_encoded_list(result3);
    free_list(result3);

    int test4[] = {5};
    int len4 = sizeof(test4) / sizeof(test4[0]);
    Node *result4 = modified_run_length_encode(test4, len4);
    printf("Test 4: ");
    print_encoded_list(result4);
    free_list(result4);

    int test5[] = {1, 2, 2, 3, 4, 4, 4, 5, 5};
    int len5 = sizeof(test5) / sizeof(test5[0]);
    Node *result5 = modified_run_length_encode(test5, len5);
    printf("Test 5: ");
    print_encoded_list(result5);
    free_list(result5);

    return 0;
}