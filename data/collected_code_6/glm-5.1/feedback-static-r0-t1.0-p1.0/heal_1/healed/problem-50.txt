#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int list_length(const Node* head) {
    int len = 0;
    const Node* curr = head;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}

Node* find_min_length_list(Node* const* lists, int num_lists) {
    if (lists == NULL || num_lists <= 0) {
        return NULL;
    }

    Node* min_list = NULL;
    int min_len = -1;

    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            int current_len = list_length(lists[i]);
            if (min_len == -1 || current_len < min_len) {
                min_len = current_len;
                min_list = lists[i];
            }
        }
    }

    return min_list;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(void) {
    Node* list1 = create_node(1);
    list1->next = create_node(2);
    list1->next->next = create_node(3);

    Node* list2 = create_node(4);
    list2->next = create_node(5);

    Node* list3 = NULL;

    Node* lists[3];
    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;

    const Node* min_list = find_min_length_list(lists, 3);

    if (min_list != NULL) {
        printf("List with minimum length starts with data: %d\n", min_list->data);
    } else {
        printf("All lists are empty.\n");
    }

    free_list(list1);
    free_list(list2);

    return 0;
}