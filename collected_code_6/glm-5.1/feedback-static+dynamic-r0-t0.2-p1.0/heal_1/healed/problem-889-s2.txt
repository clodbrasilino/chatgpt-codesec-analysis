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
    while (current != NULL) {
        Node *next = current->next;
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
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
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
        current = current->next;
    }
    free_list(lol->head);
    free(lol);
}

int main(void) {
    int v1[] = {1, 2, 3};
    int v2[] = {4, 5};
    int v3[] = {6};

    Node *list1 = create_node(&v1[2]);
    list1->next = create_node(&v1[1]);
    list1->next->next = create_node(&v1[0]);

    Node *list2 = create_node(&v2[1]);
    list2->next = create_node(&v2[0]);

    Node *list3 = create_node(&v3[0]);

    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        exit(EXIT_FAILURE);
    }
    lol->head = create_node(list1);
    lol->head->next = create_node(list2);
    lol->head->next->next = create_node(list3);

    reverse_each_list(lol);

    Node *lol_curr = lol->head;
    while (lol_curr != NULL) {
        Node *inner_curr = (Node *)lol_curr->data;
        while (inner_curr != NULL) {
            printf("%d ", *(int *)inner_curr->data);
            inner_curr = inner_curr->next;
        }
        printf("\n");
        lol_curr = lol_curr->next;
    }

    free_list_of_lists(lol);

    return 0;
}