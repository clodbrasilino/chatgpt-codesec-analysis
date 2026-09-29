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

Node *create_int_node(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    int *data = (int *)malloc(sizeof(int));
    if (data == NULL) {
        free(node);
        exit(EXIT_FAILURE);
    }
    *data = val;
    node->data = data;
    node->next = NULL;
    return node;
}

Node *create_list_node(Node *list_head) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = list_head;
    node->next = NULL;
    return node;
}

void free_int_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    Node *current = lol->head;
    while (current != NULL) {
        Node *next = current->next;
        free_int_list((Node *)current->data);
        free(current);
        current = next;
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

int main(void) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        return EXIT_FAILURE;
    }
    lol->head = NULL;

    Node *list1 = create_int_node(1);
    list1->next = create_int_node(2);
    list1->next->next = create_int_node(3);

    Node *list2 = create_int_node(4);
    list2->next = create_int_node(5);

    Node *list3 = create_int_node(6);

    lol->head = create_list_node(list1);
    lol->head->next = create_list_node(list2);
    lol->head->next->next = create_list_node(list3);

    Node *curr = lol->head;
    while (curr != NULL) {
        print_int_list((Node *)curr->data);
        curr = curr->next;
    }

    reverse_each_list(lol);

    printf("Reversed:\n");
    curr = lol->head;
    while (curr != NULL) {
        print_int_list((Node *)curr->data);
        curr = curr->next;
    }

    free_list_of_lists(lol);

    return EXIT_SUCCESS;
}