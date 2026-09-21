#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

static void free_list_internal(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

Node* string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    const char *start = str;
    const char *end;

    while (*start != '\0') {
        while (*start == ' ' || *start == '\t' || *start == '\n') {
            start++;
        }
        
        if (*start == '\0') {
            break;
        }

        end = start;
        while (*end != '\0' && *end != ' ' && *end != '\t' && *end != '\n') {
            end++;
        }

        size_t len = (size_t)(end - start);
        
        if (len == 0 || len >= SIZE_MAX) {
            free_list_internal(head);
            errno = EINVAL;
            return NULL;
        }

        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list_internal(head);
            return NULL;
        }

        new_node->data = malloc(len + 1);
        if (new_node->data == NULL) {
            free(new_node);
            free_list_internal(head);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_node->data, start, len);
        new_node->data[len] = '\0';
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        start = end;
    }

    return head;
}

void free_list(Node *head) {
    free_list_internal(head);
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *input = "hello world this is a test";
    Node *list = string_to_list(input);
    
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);
    
    return EXIT_SUCCESS;
}