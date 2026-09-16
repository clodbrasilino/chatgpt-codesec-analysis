#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val1;
    int val2;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

int list_init(List* list) {
    if (list == NULL) {
        return -1;
    }
    list->head = NULL;
    list->tail = NULL;
    return 0;
}

int list_append(List* list, Tuple data) {
    if (list == NULL) {
        return -1;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
    return 0;
}

int extract_rear(List* list, Tuple* out) {
    if (list == NULL || out == NULL) {
        return -1;
    }
    if (list->tail == NULL) {
        return -1;
    }

    Node* target = list->tail;
    *out = target->data;

    list->tail = target->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    free(target);
    return 0;
}

void list_free(List* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

int main(void) {
    List list;
    if (list_init(&list) != 0) {
        return EXIT_FAILURE;
    }

    Tuple t1 = {10, 20};
    Tuple t2 = {30, 40};
    Tuple t3 = {50, 60};

    if (list_append(&list, t1) != 0) {
        list_free(&list);
        return EXIT_FAILURE;
    }
    if (list_append(&list, t2) != 0) {
        list_free(&list);
        return EXIT_FAILURE;
    }
    if (list_append(&list, t3) != 0) {
        list_free(&list);
        return EXIT_FAILURE;
    }

    Tuple extracted;
    while (extract_rear(&list, &extracted) == 0) {
        printf("Extracted: (%d, %d)\n", extracted.val1, extracted.val2);
    }

    list_free(&list);
    return EXIT_SUCCESS;
}