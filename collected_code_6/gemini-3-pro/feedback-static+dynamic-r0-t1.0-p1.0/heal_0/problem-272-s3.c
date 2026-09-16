#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

List* create_list(void) {
    List* list = (List*)malloc(sizeof(List));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

int add_tuple(List* list, int id, int value) {
    if (list == NULL) {
        return -1;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data.id = id;
    new_node->data.value = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    return 0;
}

int extract_rear(List* list, Tuple* extracted) {
    if (list == NULL || list->head == NULL || extracted == NULL) {
        return -1;
    }

    if (list->head == list->tail) {
        *extracted = list->head->data;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return 0;
    }

    Node* current = list->head;
    while (current->next != list->tail) {
        current = current->next;
    }

    *extracted = list->tail->data;
    free(list->tail);
    list->tail = current;
    list->tail->next = NULL;

    return 0;
}

void free_list(List* list) {
    if (list != NULL) {
        Node* current = list->head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        free(list);
    }
}

int main(void) {
    List* my_list = create_list();
    if (my_list == NULL) {
        return EXIT_FAILURE;
    }

    if (add_tuple(my_list, 1, 100) != 0 ||
        add_tuple(my_list, 2, 200) != 0 ||
        add_tuple(my_list, 3, 300) != 0) {
        free_list(my_list);
        return EXIT_FAILURE;
    }

    Tuple rear_tuple;
    if (extract_rear(my_list, &rear_tuple) == 0) {
        printf("Extracted Rear - ID: %d, Value: %d\n", rear_tuple.id, rear_tuple.value);
    }

    if (extract_rear(my_list, &rear_tuple) == 0) {
        printf("Extracted Rear - ID: %d, Value: %d\n", rear_tuple.id, rear_tuple.value);
    }

    free_list(my_list);
    return EXIT_SUCCESS;
}