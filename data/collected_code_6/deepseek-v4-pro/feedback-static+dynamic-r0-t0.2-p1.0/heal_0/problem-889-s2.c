#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *next;
} List;

Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

void reverse_all_lists(List *list_of_lists) {
    List *current_list = list_of_lists;
    while (current_list != NULL) {
        current_list->head = reverse_list(current_list->head);
        current_list = current_list->next;
    }
}

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List *create_list_node(Node *head) {
    List *new_list = (List *)malloc(sizeof(List));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = head;
    new_list->next = NULL;
    return new_list;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void append_list(List **list_of_lists, Node *head) {
    List *new_list = create_list_node(head);
    if (new_list == NULL) {
        return;
    }
    if (*list_of_lists == NULL) {
        *list_of_lists = new_list;
        return;
    }
    List *current = *list_of_lists;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_list;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void print_all_lists(List *list_of_lists) {
    List *current_list = list_of_lists;
    while (current_list != NULL) {
        print_list(current_list->head);
        current_list = current_list->next;
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void free_all_lists(List *list_of_lists) {
    List *current_list = list_of_lists;
    while (current_list != NULL) {
        List *temp = current_list;
        free_list(current_list->head);
        current_list = current_list->next;
        free(temp);
    }
}

int main() {
    List *list_of_lists = NULL;
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *list3 = NULL;

    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);

    append_node(&list2, 4);
    append_node(&list2, 5);

    append_node(&list3, 6);
    append_node(&list3, 7);
    append_node(&list3, 8);
    append_node(&list3, 9);

    append_list(&list_of_lists, list1);
    append_list(&list_of_lists, list2);
    append_list(&list_of_lists, list3);

    printf("Original lists:\n");
    print_all_lists(list_of_lists);

    reverse_all_lists(list_of_lists);

    printf("Reversed lists:\n");
    print_all_lists(list_of_lists);

    free_all_lists(list_of_lists);

    return 0;
}