#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    const char *start = str;
    while (*start != '\0') {
        while (*start == ' ') {
            start++;
        }
        if (*start == '\0') {
            break;
        }

        const char *end = start;
        while (*end != '\0' && *end != ' ') {
            end++;
        }

        size_t len = end - start;
        char *word = malloc(len + 1);
        if (word == NULL) {
            free_list(head);
            return NULL;
        }
        
        snprintf(word, len + 1, "%.*s", (int)len, start);

        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            free(word);
            free_list(head);
            return NULL;
        }

        new_node->data = word;
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

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("[%s]", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    const char *input = "Hello world from C";
    Node *list = string_to_list(input);

    if (list != NULL) {
        print_list(list);
        free_list(list);
    } else {
        printf("Failed to create list or empty string.\n");
    }

    return 0;
}