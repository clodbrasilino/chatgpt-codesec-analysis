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
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void add_node(List *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

List* extract_column(List *nested_list, int column_index) {
    if (nested_list == NULL || nested_list->head == NULL) {
        return NULL;
    }

    List *result = create_list();
    for (Node *current = nested_list->head; current != NULL; current = current->next) {
        if (column_index == 0) {
            add_node(result, current->value);
        } else {
            Node *inner = current->next;
            for (int i = 1; i <= column_index && inner != NULL; ++i, inner = inner->next) {
                if (i == column_index) {
                    add_node(result, inner->value);
                }
            }
        }
    }
    return result;
}

void print_list(List *list) {
    for (Node *current = list->head; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");
}

void free_list(List *list) {
    while (list->head != NULL) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    free(list);
}

int main() {
    List *nested_list = create_list();
    add_node(nested_list, 3);
    add_node(nested_list, 2);
    add_node(nested_list, 1);

    Node *node1 = (Node *)malloc(sizeof(Node));
    node1->value = 6;
    node1->next = (Node *)malloc(sizeof(Node));
    node1->next->value = 5;
    node1->next->next = (Node *)malloc(sizeof(Node));
    node1->next->next->value = 4;
    node1->next->next->next = NULL;

    List *nested_list_2 = create_list();
    nested_list_2->head = node1;

    add_node(nested_list, (int)nested_list_2);

    List *result = extract_column(nested_list, 1);

    print_list(result);

    free_list(nested_list);
    free_list(nested_list_2);
    free_list(result);

    return 0;
}