#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *item;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->item = strdup(str);
    if (new_node->item == NULL) {
        free(new_node);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    return new_node;
}

void insert_at_beginning(Node **head, const char *prefix, const char *item) {
    if (prefix == NULL || item == NULL) {
        fprintf(stderr, "Prefix or item is NULL\n");
        exit(EXIT_FAILURE);
    }
    
    /* Possible weaknesses found:
     *  Condition 'prefix' is always true [knownConditionTrueFalse]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_prefix = prefix ? strlen(prefix) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'item' is always true [knownConditionTrueFalse]
     */
    size_t len_item = item ? strlen(item) : 0;

    char *new_item = (char*)malloc(len_prefix + len_item + 1);
    if (new_item == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    snprintf(new_item, len_prefix + len_item + 1, "%s%s", prefix, item);

    Node *new_node = create_node(new_item);
    free(new_item);

    new_node->next = *head;
    *head = new_node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->item);
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    const char *prefix = "pre_";

    insert_at_beginning(&head, prefix, "one");
    insert_at_beginning(&head, prefix, "two");
    insert_at_beginning(&head, prefix, "three");

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->item);
    }

    free_list(head);
    return 0;
}