#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node *tail = NULL;

    if (str == NULL) {
        return NULL;
    }

    while (*str) {
        while (*str && isspace((unsigned char)*str)) {
            str++;
        }
        if (*str == '\0') {
            break;
        }

        const char *start = str;
        while (*str && !isspace((unsigned char)*str)) {
            str++;
        }
        size_t len = str - start;

        char *word = malloc(len + 1);
        if (word == NULL) {
            while (head != NULL) {
                Node *tmp = head;
                head = head->next;
                free(tmp->data);
                free(tmp);
            }
            return NULL;
        }
        memcpy(word, start, len);
        word[len] = '\0';

        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            free(word);
            while (head != NULL) {
                Node *tmp = head;
                head = head->next;
                free(tmp->data);
                free(tmp);
            }
            return NULL;
        }

        new_node->data = word;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    return head;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

void print_list(const Node *head) {
    putchar('[');
    const Node *current = head;
    while (current != NULL) {
        printf("'%s'", current->data);
        current = current->next;
        if (current != NULL) {
            printf(", ");
        }
    }
    putchar(']');
    putchar('\n');
}

int main(void) {
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        print_list(NULL);
        return EXIT_SUCCESS;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    Node *list = string_to_list(buffer);
    if (list == NULL && buffer[0] != '\0') {
        fprintf(stderr, "Failed to allocate list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}