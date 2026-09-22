#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct node {
    Tuple data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
} List;

void init_list(List *l) {
    l->head = NULL;
}

Node* create_node(Tuple t) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = t;
    new_node->next = NULL;
    return new_node;
}

int add_tuple_to_list(List *l, Tuple t) {
    Node *new_node = create_node(t);
    if (!new_node) return -1;

    new_node->next = l->head;
    l->head = new_node;
    return 0;
}

void free_list(List *l) {
    Node *current = l->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    l->head = NULL;
}

int main() {
    List list;
    init_list(&list);

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};

    if (add_tuple_to_list(&list, t1) == -1 || add_tuple_to_list(&list, t2) == -1) {
        printf("Error adding tuple to list\n");
        free_list(&list);
        return 1;
    }

    // Print the list for verification
    Node *current = list.head;
    while (current != NULL) {
        printf("(%d, %d) -> ", current->data.first, current->data.second);
        current = current->next;
    }
    printf("NULL\n");

    free_list(&list);
    return 0;
}