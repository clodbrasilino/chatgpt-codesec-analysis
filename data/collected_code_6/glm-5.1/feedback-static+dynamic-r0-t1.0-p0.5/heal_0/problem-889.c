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

void free_int_list(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
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
    Node *tmp;
    while (current != NULL) {
        tmp = current;
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

    int *v1 = (int *)malloc(sizeof(int));
    int *v2 = (int *)malloc(sizeof(int));
    int *v3 = (int *)malloc(sizeof(int));
    int *v4 = (int *)malloc(sizeof(int));
    int *v5 = (int *)malloc(sizeof(int));
    int *v6 = (int *)malloc(sizeof(int));

    if (!v1 || !v2 || !v3 || !v4 || !v5 || !v6) {
        free(v1); free(v2); free(v3); free(v4); free(v5); free(v6);
        free_list_of_lists(lol);
        return EXIT_FAILURE;
    }

    *v1 = 1; *v2 = 2; *v3 = 3; *v4 = 4; *v5 = 5; *v6 = 6;

    Node *n1 = create_node(v1);
    Node *n2 = create_node(v2);
    Node *n3 = create_node(v3);
    n1->next = n2;
    n2->next = n3;
    Node *list1 = n1;

    Node *n4 = create_node(v4);
    Node *n5 = create_node(v5);
    Node *n6 = create_node(v6);
    n4->next = n5;
    n5->next = n6;
    Node *list2 = n4;

    Node *lol_n1 = create_node(list1);
    Node *lol_n2 = create_node(list2);
    lol_n1->next = lol_n2;
    lol->head = lol_n1;

    printf("Before:\n");
    print_list_of_lists(lol);

    reverse_each_list(lol);

    printf("After:\n");
    print_list_of_lists(lol);

    free_list_of_lists(lol);

    return EXIT_SUCCESS;
}