#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* find_max_length_list(Node** lists, size_t num_lists);
Node* create_node(int data);
void free_list(Node* head);

Node* find_max_length_list(Node** lists, size_t num_lists) {
    Node* max_list = NULL;
    size_t max_len = 0;

    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    for (size_t i = 0; i < num_lists; ++i) {
        size_t current_len = 0;
        Node* current_node = lists[i];

        while (current_node != NULL) {
            current_len++;
            current_node = current_node->next;
        }

        if (current_len > max_len || (current_len == 0 && max_list == NULL)) {
            max_len = current_len;
            max_list = lists[i];
        }
    }

    return max_list;
}

Node* create_node(int data) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* lists[3] = {NULL};
    size_t num_lists = 3;
    int allocation_failed = 0;
    Node* max_list = NULL;

    lists[0] = create_node(1);
    if (lists[0] != NULL) {
        lists[0]->next = create_node(2);
        if (lists[0]->next == NULL) {
            allocation_failed = 1;
        }
    } else {
        allocation_failed = 1;
    }

    if (!allocation_failed) {
        lists[1] = create_node(3);
        if (lists[1] == NULL) {
            allocation_failed = 1;
        }
    }

    if (!allocation_failed) {
        lists[2] = create_node(4);
        if (lists[2] != NULL) {
            lists[2]->next = create_node(5);
            if (lists[2]->next != NULL) {
                lists[2]->next->next = create_node(6);
                if (lists[2]->next->next == NULL) {
                    allocation_failed = 1;
                }
            } else {
                allocation_failed = 1;
            }
        } else {
            allocation_failed = 1;
        }
    }

    if (!allocation_failed) {
        max_list = find_max_length_list(lists, num_lists);
        if (max_list != NULL) {
            printf("%d\n", max_list->data);
        }
    }

    for (size_t i = 0; i < num_lists; ++i) {
        free_list(lists[i]);
        lists[i] = NULL;
    }

    if (allocation_failed) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}