#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

struct Node *replace_last(struct Node *list1, struct Node *list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list1->next == NULL) {
        free(list1);
        return list2;
    }
    struct Node *current = list1;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = list2;
    return list1;
}

void free_list(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    struct Node *list1 = create_node(1);
    list1->next = create_node(2);
    list1->next->next = create_node(3);

    struct Node *list2 = create_node(4);
    list2->next = create_node(5);

    list1 = replace_last(list1, list2);

    struct Node *curr = list1;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    free_list(list1);

    return 0;
}