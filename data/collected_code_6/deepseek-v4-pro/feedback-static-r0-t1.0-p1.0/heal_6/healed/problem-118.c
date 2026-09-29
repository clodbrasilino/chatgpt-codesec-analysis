#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

static void free_node_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

static Node *create_node(const char *start, size_t length) {
    if (start == NULL || length == 0) {
        return NULL;
    }

    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    char *word = (char *)malloc(length + 1);
    if (word == NULL) {
        return NULL;
    }

    memcpy(word, start, length);
    word[length] = '\0';

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        free(word);
        return NULL;
    }

    node->data = word;
    node->next = NULL;
    return node;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = safe_strlen(str, 4096);
    if (len == 0) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    size_t start = 0;
    size_t end = 0;

    while (end <= len) {
        if (str[end] == ' ' || str[end] == '\0') {
            if (end > start) {
                size_t word_len = end - start;
                Node *new_node = create_node(str + start, word_len);
                if (new_node == NULL) {
                    free_node_list(head);
                    return NULL;
                }

                if (head == NULL) {
                    head = new_node;
                    tail = new_node;
                } else {
                    tail->next = new_node;
                    tail = new_node;
                }
            }
            start = end + 1;
        }
        end++;
    }

    return head;
}

void free_list(Node *head) {
    free_node_list(head);
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *test_str = "Hello world from C";
    Node *list = string_to_list(test_str);

    if (list != NULL) {
        print_list(list);
        free_list(list);
    }

    return 0;
}