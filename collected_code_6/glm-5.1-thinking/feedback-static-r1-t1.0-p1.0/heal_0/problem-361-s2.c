#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct ListOfLists {
    Node *list;
    struct ListOfLists *next;
} ListOfLists;

Node *create_node(int val) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        exit(EXIT_FAILURE);
    }
    n->value = val;
    n->next = NULL;
    return n;
}

ListOfLists *create_list_node(Node *list) {
    ListOfLists *l = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (l == NULL) {
        exit(EXIT_FAILURE);
    }
    l->list = list;
    l->next = NULL;
    return l;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void free_list_of_lists(ListOfLists *head) {
    while (head != NULL) {
        ListOfLists *tmp = head;
        free_list(head->list);
        head = head->next;
        free(tmp);
    }
}

ListOfLists *remove_empty_lists(ListOfLists *head) {
    ListOfLists **current = &head;
    while (*current != NULL) {
        if ((*current)->list == NULL) {
            ListOfLists *to_free = *current;
            *current = (*current)->next;
            free(to_free);
        } else {
            current = &((*current)->next);
        }
    }
    return head;
}

int main(void) {
    Node *l1 = NULL;
    Node *l2 = create_node(1);
    l2->next = create_node(2);
    Node *l3 = NULL;
    Node *l4 = create_node(3);

    ListOfLists *head = create_list_node(l1);
    head->next = create_list_node(l2);
    head->next->next = create_list_node(l3);
    head->next->next->next = create_list_node(l4);

    head = remove_empty_lists(head);

    ListOfLists *curr = head;
    while (curr != NULL) {
        printf("List: ");
        Node *inner = curr->list;
        while (inner != NULL) {
            printf("%d ", inner->value);
            inner = inner->next;
        }
        printf("\n");
        curr = curr->next;
    }

    free_list_of_lists(head);
    return 0;
}