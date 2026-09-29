#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void add_node(List *list, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

List* extract_column(List *lists, int column_index) {
    List *result = create_list();
    for (List *current_list = lists; current_list != NULL; current_list = (List*)current_list->head->next) {
        Node *node = current_list->head;
        for (int i = 0; i < column_index && node != NULL; i++) {
            node = node->next;
        }
        if (node != NULL) {
            add_node(result, node->value);
        }
    }
    return result;
}

void print_list(List *list) {
    for (Node *node = list->head; node != NULL; node = node->next) {
        printf("%d ", node->value);
    }
    printf("\n");
}

void free_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main() {
    List *lists = create_list();
    List *list1 = create_list();
    add_node(list1, 3);
    add_node(list1, 2);
    add_node(list1, 1);
    add_node(lists, (int)list1);

    List *list2 = create_list();
    add_node(list2, 6);
    add_node(list2, 5);
    add_node(list2, 4);
    add_node(lists, (int)list2);

    List *list3 = create_list();
    add_node(list3, 9);
    add_node(list3, 8);
    add_node(list3, 7);
    add_node(lists, (int)list3);

    List *column = extract_column((List*)lists, 1);
    print_list(column);

    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_list(lists);
    free_list(column);

    return 0;
}