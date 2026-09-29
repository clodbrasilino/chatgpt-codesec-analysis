#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::value' is never used. [unusedStructMember]
     */
    int value;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void add_tuple(List *list, Tuple tuple) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = tuple;
    new_node->next = list->head;
    list->head = new_node;
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

int main() {
    List *list = create_list();
    Tuple t1 = {1};
    Tuple t2 = {2};

    add_tuple(list, t1);
    add_tuple(list, t2);

    free_list(list);
    return 0;
}