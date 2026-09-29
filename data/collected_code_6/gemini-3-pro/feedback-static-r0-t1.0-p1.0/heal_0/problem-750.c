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
} List;

int add_tuple_to_list(List* list, Tuple tuple) {
    if (list == NULL) {
        return -1;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = tuple;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    return 0;
}

void free_list(List* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

void print_list(const List* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->head;
    while (current != NULL) {
        printf("(%d, %d) ", current->data.x, current->data.y);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List my_list = {NULL};
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};

    if (add_tuple_to_list(&my_list, t1) != 0) {
        fprintf(stderr, "Failed to add tuple to list.\n");
        free_list(&my_list);
        return EXIT_FAILURE;
    }

    if (add_tuple_to_list(&my_list, t2) != 0) {
        fprintf(stderr, "Failed to add tuple to list.\n");
        free_list(&my_list);
        return EXIT_FAILURE;
    }

    if (add_tuple_to_list(&my_list, t3) != 0) {
        fprintf(stderr, "Failed to add tuple to list.\n");
        free_list(&my_list);
        return EXIT_FAILURE;
    }

    print_list(&my_list);

    free_list(&my_list);

    return EXIT_SUCCESS;
}