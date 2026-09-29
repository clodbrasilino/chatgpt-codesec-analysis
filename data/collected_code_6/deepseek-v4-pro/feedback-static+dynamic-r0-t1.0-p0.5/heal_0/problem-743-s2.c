#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
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
    list->size = 0;
    return list;
}

int append(List *list, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return 0;
    }
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 1;
}

void rotate_right(List *list, int k) {
    if (list == NULL || list->head == NULL || list->size <= 1 || k <= 0) {
        return;
    }
    k = k % list->size;
    if (k == 0) {
        return;
    }
    int steps = list->size - k;
    Node *current = list->head;
    for (int i = 1; i < steps; i++) {
        current = current->next;
    }
    Node *new_head = current->next;
    current->next = NULL;
    Node *tail = new_head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = list->head;
    list->head = new_head;
}

void print_list(List *list) {
    if (list == NULL || list->head == NULL) {
        printf("Empty list\n");
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main(void) {
    List *list = create_list();
    if (list == NULL) {
        return 1;
    }
    append(list, 1);
    append(list, 2);
    append(list, 3);
    append(list, 4);
    append(list, 5);
    printf("Original list: ");
    print_list(list);
    rotate_right(list, 2);
    printf("Rotated list: ");
    print_list(list);
    free_list(list);
    return 0;
}