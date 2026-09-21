#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head);
Node* string_to_list(const char *str, const char *delim);
void print_list(const Node *head);

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        if (current->data != NULL) {
            free(current->data);
        }
        free(current);
        current = next;
    }
}

Node* string_to_list(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node **tail = &head;
    const char *p = str;

    while (*p != '\0') {
        p += strspn(p, delim);
        if (*p == '\0') {
            break;
        }

        size_t len = strcspn(p, delim);
        
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        new_node->data = (char *)malloc(len + 1);
        if (new_node->data == NULL) {
            free(new_node);
            free_list(head);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_node->data, p, len);
        new_node->data[len] = '\0';
        new_node->next = NULL;

        *tail = new_node;
        tail = &(new_node->next);

        p += len;
    }

    return head;
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *input_string = "Convert this string into a list";
    const char *delimiter = " ";

    Node *list = string_to_list(input_string, delimiter);
    
    if (list != NULL) {
        print_list(list);
        free_list(list);
    }

    return 0;
}