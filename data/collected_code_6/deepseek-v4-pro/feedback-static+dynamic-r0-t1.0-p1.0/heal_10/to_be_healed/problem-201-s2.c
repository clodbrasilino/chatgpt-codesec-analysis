#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node **head, int data) {
    struct Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

int all_elements_same(struct Node *head) {
    if (head == NULL) {
        return -1;
    }
    int first_value = head->data;
    struct Node *current = head->next;
    while (current != NULL) {
        if (current->data != first_value) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    /* Possible weaknesses found:
     *  Assignment 'list3=NULL', assigned value is 0
     */
    struct Node *list3 = NULL;

    append_node(&list1, 5);
    append_node(&list1, 5);
    append_node(&list1, 5);
    append_node(&list1, 5);

    append_node(&list2, 5);
    append_node(&list2, 3);
    append_node(&list2, 5);

    int result1 = all_elements_same(list1);
    int result2 = all_elements_same(list2);
    int result3 = all_elements_same(list3);

    if (list1 == NULL) {
        printf("List 1 (empty) all same: Undefined\n");
    } else {
        printf("List 1 all same: %s\n", result1 ? "Yes" : "No");
    }

    if (list2 == NULL) {
        printf("List 2 (empty) all same: Undefined\n");
    } else {
        printf("List 2 all same: %s\n", result2 ? "Yes" : "No");
    }

    /* Possible weaknesses found:
     *  Condition 'list3==NULL' is always true
     *  Condition 'list3==NULL' is always true [knownConditionTrueFalse]
     */
    if (list3 == NULL) {
        printf("List 3 (empty) all same: Undefined\n");
    } else {
        printf("List 3 all same: %s\n", result3 ? "Yes" : "No");
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}