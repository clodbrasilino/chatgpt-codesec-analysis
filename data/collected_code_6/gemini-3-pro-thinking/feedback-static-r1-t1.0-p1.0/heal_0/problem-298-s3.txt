#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

bool append_node(Node** head, int data) {
    if (!head) {
        return false;
    }
    Node* new_node = create_node(data);
    if (!new_node) {
        return false;
    }

    if (!*head) {
        *head = new_node;
        return true;
    }

    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
    return true;
}

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

bool contains(const Node* head, int value) {
    const Node* current = head;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool find_common_elements(Node** nested_list, size_t nested_count, const Node* target_list, Node** result_out) {
    if (!nested_list || !target_list || !result_out) {
        return false;
    }

    *result_out = NULL;

    for (size_t i = 0; i < nested_count; ++i) {
        Node* current_sublist = nested_list[i];
        while (current_sublist) {
            if (contains(target_list, current_sublist->data)) {
                if (!contains(*result_out, current_sublist->data)) {
                    if (!append_node(result_out, current_sublist->data)) {
                        free_list(*result_out);
                        *result_out = NULL;
                        return false;
                    }
                }
            }
            current_sublist = current_sublist->next;
        }
    }

    return true;
}

int main(void) {
    int status = EXIT_SUCCESS;
    Node* target_list = NULL;
    Node** nested_list = NULL;
    Node* common_elements = NULL;
    size_t nested_count = 2;

    if (!append_node(&target_list, 2) ||
        !append_node(&target_list, 4) ||
        !append_node(&target_list, 6) ||
        !append_node(&target_list, 8)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    nested_list = (Node**)calloc(nested_count, sizeof(Node*));
    if (!nested_list) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!append_node(&nested_list[0], 1) ||
        !append_node(&nested_list[0], 2) ||
        !append_node(&nested_list[0], 3)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!append_node(&nested_list[1], 4) ||
        !append_node(&nested_list[1], 5) ||
        !append_node(&nested_list[1], 6)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!find_common_elements(nested_list, nested_count, target_list, &common_elements)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    Node* current = common_elements;
    while (current) {
        printf("%d\n", current->data);
        current = current->next;
    }

cleanup:
    free_list(target_list);
    if (nested_list) {
        for (size_t i = 0; i < nested_count; ++i) {
            free_list(nested_list[i]);
        }
        free(nested_list);
    }
    free_list(common_elements);

    return status;
}