#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    ListNode *tail;
} List;

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL) exit(1);
    list->head = NULL;
    list->tail = NULL;
    return list;
}

ListNode* create_node(int value) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (node == NULL) exit(1);
    node->val = value;
    node->next = NULL;
    return node;
}

void add_to_list(List *list, int value) {
    ListNode *node = create_node(value);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
}

List** create_list_of_lists(int num_lists) {
    List **lists = (List**)malloc(num_lists * sizeof(List*));
    if (lists == NULL) exit(1);
    for (int i = 0; i < num_lists; ++i) {
        lists[i] = create_list();
    }
    return lists;
}

void reverse_list(List *list) {
    ListNode *prev = NULL;
    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->tail = list->head;
    list->head = prev;
}

void reverse_each_list_in(List **lists, int num_lists) {
    for (int i = 0; i < num_lists; ++i) {
        reverse_list(lists[i]);
    }
}

void print_list(List *list) {
    ListNode *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(List *list) {
    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void free_list_of_lists(List **lists, int num_lists) {
    for (int i = 0; i < num_lists; ++i) {
        free_list(lists[i]);
    }
    free(lists);
}

int main() {
    int num_lists = 3;
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    List **lists = create_list_of_lists(num_lists);

    int index = 0;
    for (int i = 0; i < num_lists; ++i) {
        for (int j = 0; j < 3; ++j) {
            add_to_list(lists[i], values[index++]);
        }
    }

    for (int i = 0; i < num_lists; ++i) {
        print_list(lists[i]);
    }

    reverse_each_list_in(lists, num_lists);

    for (int i = 0; i < num_lists; ++i) {
        print_list(lists[i]);
    }

    free_list_of_lists(lists, num_lists);

    return 0;
}