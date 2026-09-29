#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *create_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

size_t list_length(const Node *head) {
    size_t length = 0;
    const Node *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

Node *find_max_length_list(Node **lists, size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }
    Node *max_list = NULL;
    size_t max_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (lists[i] != NULL) {
            size_t current_length = list_length(lists[i]);
            if (current_length > max_length) {
                max_length = current_length;
                max_list = lists[i];
            }
        }
    }
    return max_list;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void free_all_lists(Node **lists, size_t count) {
    if (lists == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free_list(lists[i]);
    }
}

int main(void) {
    Node *list1 = create_node(1);
    if (list1 != NULL) {
        list1->next = create_node(2);
    }

    Node *list2 = create_node(10);
    if (list2 != NULL) {
        list2->next = create_node(20);
        if (list2->next != NULL) {
            list2->next->next = create_node(30);
        }
    }

    Node *list3 = NULL;

    Node *lists[] = {list1, list2, list3};
    size_t list_count = sizeof(lists) / sizeof(lists[0]);

    Node *longest = find_max_length_list(lists, list_count);

    if (longest != NULL) {
        printf("List with max length starts with value: %d, length: %zu\n", longest->value, list_length(longest));
    } else {
        printf("All lists are empty or no lists provided.\n");
    }

    free_all_lists(lists, list_count);

    return 0;
}