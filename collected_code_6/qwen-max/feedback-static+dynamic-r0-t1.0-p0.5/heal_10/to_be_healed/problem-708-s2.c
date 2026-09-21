#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(char *str) {
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

void append_to_list(Node **head, char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node* string_to_list(const char *str) {
    Node *head = NULL;
    const char *start = str;
    while (*str) {
        if (*str == ' ') {
            if (start != str) {
                size_t len = str - start;
                char *token = (char *)malloc((len + 1) * sizeof(char));
                if (token == NULL) {
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(token, start, len);
                token[len] = '\0';
                append_to_list(&head, token);
                free(token);
            }
            start = str + 1;
        }
        str++;
    }
    if (start != str) {
        size_t len = str - start;
        char *token = (char *)malloc((len + 1) * sizeof(char));
        if (token == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(token, start, len);
        token[len] = '\0';
        append_to_list(&head, token);
        free(token);
    }
    return head;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%s -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main() {
    const char *input = "This is a test string";
    Node *list = string_to_list(input);
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }
    print_list(list);
    free_list(list);
    return 0;
}