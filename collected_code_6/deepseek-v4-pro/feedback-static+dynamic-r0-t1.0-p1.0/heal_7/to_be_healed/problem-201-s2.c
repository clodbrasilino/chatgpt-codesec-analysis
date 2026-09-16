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
        return 0;
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
    struct Node *list3 = NULL;

    append_node(&list1, 5);
    append_node(&list1, 5);
    append_node(&list1, 5);
    append_node(&list1, 5);

    append_node(&list2, 5);
    append_node(&list2, 3);
    append_node(&list2, 5);

    printf("List 1 all same: %s\n", all_elements_same(list1) ? "Yes" : "No");
    printf("List 2 all same: %s\n", all_elements_same(list2) ? "Yes" : "No");
    
    /* Possible weaknesses found:
     *  Calling function 'all_elements_same' returns 0
     *  Assignment 'result=all_elements_same(list3)', assigned value is 0
     */
    int result = all_elements_same(list3);
    /* Possible weaknesses found:
     *  Condition 'result==0' is always true
     *  Condition 'result==0' is always true [knownConditionTrueFalse]
     */
    if (result == 0) {
        printf("List 3 (empty) all same: Undefined\n");
    } else {
        /* Possible weaknesses found:
         *  Condition 'result' is always true [knownConditionTrueFalse]
         */
        printf("List 3 (empty) all same: %s\n", result ? "Yes" : "No");
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}