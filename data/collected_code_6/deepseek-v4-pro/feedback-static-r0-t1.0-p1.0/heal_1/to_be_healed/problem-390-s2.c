#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    new_node->data = (char *)malloc(strlen(str) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_node->data, str);
    new_node->next = NULL;
    return new_node;
}

void insert_at_beginning(Node **head, const char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

void prepend_to_all(Node *head, const char *prefix) {
    Node *current = head;
    while (current != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t new_len = strlen(prefix) + strlen(current->data) + 1;
        char *new_str = (char *)malloc(new_len);
        if (new_str == NULL) {
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(new_str, prefix);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(new_str, current->data);
        free(current->data);
        current->data = new_str;
        current = current->next;
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    Node *list = NULL;
    
    insert_at_beginning(&list, "world");
    insert_at_beginning(&list, "there");
    insert_at_beginning(&list, "hello");
    
    printf("Original list:\n");
    print_list(list);
    
    prepend_to_all(list, "say_");
    
    printf("\nModified list:\n");
    print_list(list);
    
    free_list(list);
    
    return 0;
}