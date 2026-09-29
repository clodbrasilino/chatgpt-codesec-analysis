#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *create_node(const char *token) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    node->value = malloc(strlen(token) + 1);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(node->value, token);
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

Node *string_to_list(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(buffer, str);
    
    Node *head = NULL;
    Node *tail = NULL;
    
    char *token = strtok(buffer, delim);
    while (token != NULL) {
        Node *node = create_node(token);
        if (node == NULL) {
            free(buffer);
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        token = strtok(NULL, delim);
    }
    
    free(buffer);
    return head;
}

int main(void) {
    const char *text = "Convert this string to a list";
    Node *list = string_to_list(text, " ");
    if (list != NULL) {
        Node *current = list;
        while (current != NULL) {
            printf("%s\n", current->value);
            current = current->next;
        }
        free_list(list);
    }
    return 0;
}