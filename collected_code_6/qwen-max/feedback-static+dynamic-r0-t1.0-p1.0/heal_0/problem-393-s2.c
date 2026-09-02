#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

int list_length(Node *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

Node* find_max_length_list(Node **lists, int num_lists) {
    if (num_lists == 0) return NULL;

    Node *max_list = lists[0];
    int max_length = list_length(lists[0]);

    for (int i = 1; i < num_lists; i++) {
        int current_length = list_length(lists[i]);
        if (current_length > max_length) {
            max_length = current_length;
            max_list = lists[i];
        }
    }

    return max_list;
}

int main() {
    Node *list1 = create_node(1);
    list1->next = create_node(2);
    list1->next->next = create_node(3);

    Node *list2 = create_node(4);
    list2->next = create_node(5);

    Node *list3 = create_node(6);
    list3->next = create_node(7);
    list3->next->next = create_node(8);
    list3->next->next->next = create_node(9);

    Node *lists[] = {list1, list2, list3};
    int num_lists = 3;

    Node *max_list = find_max_length_list(lists, num_lists);

    printf("Max Length List: ");
    while (max_list != NULL) {
        printf("%d -> ", max_list->value);
        max_list = max_list->next;
    }
    printf("NULL\n");

    // Clean up
    for (int i = 0; i < num_lists; i++) {
        Node *current = lists[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}