#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int add_tuple_to_list(List* list, Tuple tuple) {
    if (!list) {
        return -1;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return -1;
    }

    new_node->data = tuple;
    new_node->next = NULL;

    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    return 0;
}

void free_list(List* list) {
    if (!list) {
        return;
    }

    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void print_list(List* list) {
    if (!list) {
        return;
    }

    Node* current = list->head;
    while (current) {
        printf("(%d, %d) ", current->data.x, current->data.y);
        current = current->next;
    }
    printf("\n");
}

int main() {
    List* my_list = create_list();
    if (!my_list) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};

    if (add_tuple_to_list(my_list, t1) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        free_list(my_list);
        return 1;
    }
    if (add_tuple_to_list(my_list, t2) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        free_list(my_list);
        return 1;
    }
    if (add_tuple_to_list(my_list, t3) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        free_list(my_list);
        return 1;
    }

    print_list(my_list);

    free_list(my_list);

    return 0;
}