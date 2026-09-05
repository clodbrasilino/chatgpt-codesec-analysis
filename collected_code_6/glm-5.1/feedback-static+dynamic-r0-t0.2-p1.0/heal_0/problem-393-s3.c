#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

size_t list_length(Node *head) {
    size_t len = 0;
    Node *current = head;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *find_max_length_list(Node **lists, size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }
    
    Node *max_list = lists[0];
    size_t max_len = list_length(lists[0]);
    
    for (size_t i = 1; i < count; i++) {
        size_t current_len = list_length(lists[i]);
        if (current_len > max_len) {
            max_len = current_len;
            max_list = lists[i];
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

int main(void) {
    Node *list1 = create_node(1);
    list1->next = create_node(2);
    
    Node *list2 = create_node(3);
    list2->next = create_node(4);
    list2->next->next = create_node(5);
    
    Node *list3 = create_node(6);
    
    Node *lists[] = {list1, list2, list3};
    size_t count = sizeof(lists) / sizeof(lists[0]);
    
    Node *max_list = find_max_length_list(lists, count);
    
    if (max_list != NULL) {
        printf("List with max length starts at node with data: %d\n", max_list->data);
        printf("Its length is: %zu\n", list_length(max_list));
    }
    
    free_list(list1);
    free_list(list2);
    free_list(list3);
    
    return 0;
}