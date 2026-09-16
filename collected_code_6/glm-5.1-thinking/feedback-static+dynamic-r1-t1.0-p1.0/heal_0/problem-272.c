#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int val1;
    int val2;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    size_t size;
} List;

int list_init(List *list) {
    if (list == NULL) {
        return -1;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return 0;
}

int list_append(List *list, Tuple t) {
    if (list == NULL) {
        return -1;
    }
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = t;
    new_node->next = NULL;

    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 0;
}

int extract_rear(List *list, Tuple *out) {
    if (list == NULL || out == NULL) {
        return -1;
    }
    if (list->head == NULL) {
        return -1;
    }

    Node *target = list->tail;
    *out = target->data;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node *current = list->head;
        while (current->next != list->tail) {
            current = current->next;
        }
        current->next = NULL;
        list->tail = current;
    }

    free(target);
    list->size--;
    return 0;
}

void list_free(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next_node = current->next;
        free(current);
        current = next_node;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int main(void) {
    List my_list;
    if (list_init(&my_list) != 0) {
        return EXIT_FAILURE;
    }

    Tuple t1 = {1, 10};
    Tuple t2 = {2, 20};
    Tuple t3 = {3, 30};

    list_append(&my_list, t1);
    list_append(&my_list, t2);
    list_append(&my_list, t3);

    Tuple extracted;
    while (extract_rear(&my_list, &extracted) == 0) {
        printf("Extracted: (%d, %d)\n", extracted.val1, extracted.val2);
    }

    list_free(&my_list);
    return EXIT_SUCCESS;
}