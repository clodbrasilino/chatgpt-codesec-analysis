#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct ListOfLists {
    Node *head;
    struct ListOfLists *next;
} ListOfLists;

size_t count_lists(ListOfLists *lists) {
    size_t count = 0;
    ListOfLists *current = lists;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

ListOfLists *create_list_of_lists(Node *head) {
    ListOfLists *list = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (list == NULL) {
        return NULL;
    }
    list->head = head;
    list->next = NULL;
    return list;
}

void free_node(Node *node) {
    while (node != NULL) {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
}

void free_list_of_lists(ListOfLists *lists) {
    while (lists != NULL) {
        ListOfLists *temp = lists;
        free_node(lists->head);
        lists = lists->next;
        free(temp);
    }
}

int main(void) {
    ListOfLists *head_list = NULL;
    ListOfLists *tail_list = NULL;

    for (int i = 0; i < 3; i++) {
        Node *sub_head = create_node(i * 10);
        if (sub_head == NULL) {
            free_list_of_lists(head_list);
            return 1;
        }
        
        Node *second = create_node(i * 10 + 1);
        if (second == NULL) {
            free_node(sub_head);
            free_list_of_lists(head_list);
            return 1;
        }
        sub_head->next = second;

        ListOfLists *new_list = create_list_of_lists(sub_head);
        if (new_list == NULL) {
            free_node(sub_head);
            free_list_of_lists(head_list);
            return 1;
        }

        if (head_list == NULL) {
            head_list = new_list;
            tail_list = new_list;
        } else {
            tail_list->next = new_list;
            tail_list = new_list;
        }
    }

    size_t total_lists = count_lists(head_list);
    printf("%zu\n", total_lists);

    free_list_of_lists(head_list);
    return 0;
}