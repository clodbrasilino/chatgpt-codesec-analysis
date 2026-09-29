#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    int size;
} List;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List *create_list(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int append_node(List *list, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return 0;
    }
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 1;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int replace_last_with_list(List *target, List *replacement) {
    if (target == NULL || replacement == NULL) {
        return 0;
    }
    if (target->head == NULL) {
        return 0;
    }
    if (target->size == 1) {
        Node *old_head = target->head;
        target->head = replacement->head;
        target->tail = replacement->tail;
        target->size = replacement->size;
        free(old_head);
        replacement->head = NULL;
        replacement->tail = NULL;
        replacement->size = 0;
        return 1;
    }
    Node *current = target->head;
    while (current->next != target->tail) {
        current = current->next;
    }
    Node *old_tail = target->tail;
    current->next = replacement->head;
    if (replacement->tail != NULL) {
        target->tail = replacement->tail;
    } else {
        target->tail = current;
    }
    target->size = target->size - 1 + replacement->size;
    free(old_tail);
    replacement->head = NULL;
    replacement->tail = NULL;
    replacement->size = 0;
    return 1;
}

void print_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List *list1 = create_list();
    List *list2 = create_list();
    if (list1 == NULL || list2 == NULL) {
        free_list(list1);
        free_list(list2);
        return 1;
    }
    append_node(list1, 1);
    append_node(list1, 2);
    append_node(list1, 3);
    append_node(list2, 10);
    append_node(list2, 20);
    append_node(list2, 30);
    printf("Before replacement:\n");
    printf("List1: ");
    print_list(list1);
    printf("List2: ");
    print_list(list2);
    replace_last_with_list(list1, list2);
    printf("After replacement:\n");
    printf("List1: ");
    print_list(list1);
    printf("List2: ");
    print_list(list2);
    free_list(list1);
    free_list(list2);
    return 0;
}