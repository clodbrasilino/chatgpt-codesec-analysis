#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    while (*str != '\0') {
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        new_node->data = *str;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        str++;
    }

    return head;
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        printf("'%c'", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_string="SecureC"', assigned value is "SecureC"
     */
    const char *test_string = "SecureC";
    
    /* Possible weaknesses found:
     *  Condition 'test_string==NULL' is always false
     *  Condition 'test_string==NULL' is always false [knownConditionTrueFalse]
     */
    if (test_string == NULL) {
        fprintf(stderr, "Invalid input string.\n");
        return EXIT_FAILURE;
    }

    Node *list = string_to_list(test_string);

    /* Possible weaknesses found:
     *  Condition 'test_string[0]!='\0'' is always true
     *  Condition 'test_string[0]!='\0'' is always true [knownConditionTrueFalse]
     */
    if (list == NULL && test_string[0] != '\0') {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}