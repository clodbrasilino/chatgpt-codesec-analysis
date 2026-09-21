#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *create_node(const char *token) {
    if (token == NULL) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = strdup(token);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }
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
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  */

Node *string_to_list(const char *str, const char *delim) {
    if (str == NULL) {
        return NULL;
    }
    if (delim == NULL || delim[0] == '\0') {
        delim = " \t\n\r\f\v";
    }
    char *buffer = strdup(str);
    if (buffer == NULL) {
        return NULL;
    }
    
    Node *head = NULL;
    Node *tail = NULL;
    
    char *saveptr;
    char *token = strtok_r(buffer, delim, &saveptr);
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
        token = strtok_r(NULL, delim, &saveptr);
    }
    
    free(buffer);
    return head;
}

int main(void) {
    const char *text = "Convert this string to a list";
    Node *list = string_to_list(text, NULL);
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