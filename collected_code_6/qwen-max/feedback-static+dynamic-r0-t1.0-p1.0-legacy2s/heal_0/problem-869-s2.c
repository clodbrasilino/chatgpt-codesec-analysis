#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void append_node(List *list, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void free_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

List** create_list_of_lists(int size) {
    List** lists = (List**)malloc(size * sizeof(List*));
    for (int i = 0; i < size; i++) {
        lists[i] = create_list();
    }
    return lists;
}

void free_list_of_lists(List** lists, int size) {
    for (int i = 0; i < size; i++) {
        free_list(lists[i]);
    }
    free(lists);
}

List** filter_lists(List** lists, int size, int min, int max) {
    List** filtered_lists = create_list_of_lists(size);

    for (int i = 0; i < size; i++) {
        Node *current = lists[i]->head;
        while (current != NULL) {
            if (current->value >= min && current->value <= max) {
                append_node(filtered_lists[i], current->value);
            }
            current = current->next;
        }
    }

    return filtered_lists;
}

void print_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    List** lists = create_list_of_lists(3);

    append_node(lists[0], 1);
    append_node(lists[0], 2);
    append_node(lists[0], 3);

    append_node(lists[1], 4);
    append_node(lists[1], 5);
    append_node(lists[1], 6);

    append_node(lists[2], 7);
    append_node(lists[2], 8);
    append_node(lists[2], 9);

    int min = 3;
    int max = 6;

    List** filtered_lists = filter_lists(lists, 3, min, max);

    for (int i = 0; i < 3; i++) {
        print_list(filtered_lists[i]);
    }

    free_list_of_lists(lists, 3);
    free_list_of_lists(filtered_lists, 3);

    return 0;
}