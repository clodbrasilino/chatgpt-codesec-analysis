#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = strdup(str);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void insert_node(Node **head, const char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

void free_list(Node **head) {
    Node *current = *head;
    while (current != NULL) {
        Node *temp = current->next;
        free(current->data);
        free(current);
        current = temp;
    }
    *head = NULL;
}

Node* string_to_list(const char *str, char delimiter) {
    Node *head = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *str_copy = (char *)malloc(len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str_copy, str);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char delimiters[2] = {delimiter, '\0'};
    char *token = strtok(str_copy, delimiters);
    while (token != NULL) {
        insert_node(&head, token);
        token = strtok(NULL, delimiters);
    }
    free(str_copy);
    return head;
}

int main() {
    const char *input = "apple,banana,cherry";
    char delimiter = ',';
    Node *head = string_to_list(input, delimiter);

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    free_list(&head);
    return 0;
}