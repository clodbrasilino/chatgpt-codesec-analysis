#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct ListOfLists {
    Node *head;
} ListOfLists;

void reverse_list(Node **head_ref) {
    Node *prev = NULL;
    Node *current = *head_ref;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

void reverse_each_list(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    Node *current = lol->head;
    while (current != NULL) {
        reverse_list((Node **)&current->data);
        current = current->next;
    }
}

Node *create_node(void *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head_ref, void *data) {
    Node *new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node *last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void free_int_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    Node *current = lol->head;
    while (current != NULL) {
        Node *tmp = current;
        current = current->next;
        free_int_list((Node *)tmp->data);
        free(tmp);
    }
    free(lol);
}

void print_int_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }
    printf("\n");
}

void print_list_of_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    Node *current = lol->head;
    while (current != NULL) {
        print_int_list((Node *)current->data);
        current = current->next;
    }
}

int main(void) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        return EXIT_FAILURE;
    }
    lol->head = NULL;

    Node *list1 = NULL;
    int *v1 = (int *)malloc(sizeof(int)); *v1 = 1;
    int *v2 = (int *)malloc(sizeof(int)); *v2 = 2;
    int *v3 = (int *)malloc(sizeof(int)); *v3 = 3;
    append_node(&list1, v1);
    append_node(&list1, v2);
    append_node(&list1, v3);

    Node *list2 = NULL;
    int *v4 = (int *)malloc(sizeof(int)); *v4 = 4;
    int *v5 = (int *)malloc(sizeof(int)); *v5 = 5;
    append_node(&list2, v4);
    append_node(&list2, v5);

    append_node(&lol->head, list1);
    append_node(&lol->head, list2);

    printf("Before reversal:\n");
    print_list_of_lists(lol);

    reverse_each_list(lol);

    printf("After reversal:\n");
    print_list_of_lists(lol);

    free_list_of_lists(lol);

    return EXIT_SUCCESS;
}