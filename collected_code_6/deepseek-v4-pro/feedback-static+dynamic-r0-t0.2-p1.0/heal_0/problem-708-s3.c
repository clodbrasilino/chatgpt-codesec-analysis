#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    const char *start = str;
    size_t len = strlen(str);

    for (size_t i = 0; i <= len; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i > 0 && str[i - 1] != ' ') {
                size_t word_len = (size_t)(&str[i] - start);
                char *word = (char *)malloc(word_len + 1);
                if (word == NULL) {
                    Node *current = head;
                    while (current != NULL) {
                        Node *next = current->next;
                        free(current->data);
                        free(current);
                        current = next;
                    }
                    return NULL;
                }
                strncpy(word, start, word_len);
                word[word_len] = '\0';

                Node *new_node = (Node *)malloc(sizeof(Node));
                if (new_node == NULL) {
                    free(word);
                    Node *current = head;
                    while (current != NULL) {
                        Node *next = current->next;
                        free(current->data);
                        free(current);
                        current = next;
                    }
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
            }
            start = &str[i + 1];
        }
    }

    return head;
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
    const char *test_str = "hello world from c";
    Node *list = string_to_list(test_str);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}