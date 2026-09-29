#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int find_min_length(Node **lists, int num_lists) {
    if (lists == NULL || num_lists <= 0) {
        return -1;
    }

    int min_len = -1;

    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            return 0;
        }

        int current_len = 0;
        Node *current = lists[i];
        while (current != NULL) {
            current_len++;
            if (current_len < 0) {
                return -1;
            }
            current = current->next;
        }

        if (min_len == -1 || current_len < min_len) {
            min_len = current_len;
        }
    }

    return min_len;
}

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

int main() {
    Node *list1 = create_node(1);
    if (list1 == NULL) return 1;
    list1->next = create_node(2);
    if (list1->next == NULL) {
        free_list(list1);
        return 1;
    }
    list1->next->next = create_node(3);
    if (list1->next->next == NULL) {
        free_list(list1);
        return 1;
    }

    Node *list2 = create_node(4);
    if (list2 == NULL) {
        free_list(list1);
        return 1;
    }
    list2->next = create_node(5);
    if (list2->next == NULL) {
        free_list(list1);
        free_list(list2);
        return 1;
    }

    Node *list3 = create_node(6);
    if (list3 == NULL) {
        free_list(list1);
        free_list(list2);
        return 1;
    }

    Node *lists[] = {list1, list2, list3};
    int num_lists = sizeof(lists) / sizeof(lists[0]);

    int min_length = find_min_length(lists, num_lists);
    printf("%d\n", min_length);

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}