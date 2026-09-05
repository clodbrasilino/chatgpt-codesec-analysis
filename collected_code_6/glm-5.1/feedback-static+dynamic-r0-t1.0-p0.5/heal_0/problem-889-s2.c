#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct ListOfLists {
    Node *head;
} ListOfLists;

Node *create_node(void *data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

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
        if (current->data != NULL) {
            reverse_list((Node **)&current->data);
        }
        current = current->next;
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
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
        if (current->data != NULL) {
            free_list((Node *)current->data);
        }
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(lol);
}

int main(void) {
    Node *list1 = create_node((void *)(long)1);
    list1->next = create_node((void *)(long)2);
    list1->next->next = create_node((void *)(long)3);

    Node *list2 = create_node((void *)(long)4);
    list2->next = create_node((void *)(long)5);

    Node *list3 = create_node((void *)(long)6);
    list3->next = create_node((void *)(long)7);
    list3->next->next = create_node((void *)(long)8);
    list3->next->next->next = create_node((void *)(long)9);

    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        exit(EXIT_FAILURE);
    }
    lol->head = create_node(list1);
    lol->head->next = create_node(list2);
    lol->head->next->next = create_node(list3);

    reverse_each_list(lol);

    Node *lol_current = lol->head;
    while (lol_current != NULL) {
        Node *inner_current = (Node *)lol_current->data;
        while (inner_current != NULL) {
            printf("%ld ", (long)inner_current->data);
            inner_current = inner_current->next;
        }
        printf("\n");
        lol_current = lol_current->next;
    }

    free_list_of_lists(lol);

    return 0;
}