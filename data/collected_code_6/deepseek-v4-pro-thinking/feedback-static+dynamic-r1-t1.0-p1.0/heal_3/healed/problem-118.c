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
    const char *p = str;

    if (p == NULL) {
        return NULL;
    }

    while (*p != '\0') {
        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }
        size_t len = p - start;

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
        {
            size_t i;
            for (i = 0; i < len; i++) {
                word[i] = start[i];
            }
            word[len] = '\0';
        }

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
    const Node *current = head;
    putchar('[');
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

char *safe_read_line(void) {
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = (char)ch;
    }

    if (length == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    {
        char *shrunk = realloc(buffer, length + 1);
        if (shrunk != NULL) {
            buffer = shrunk;
        }
    }
    return buffer;
}

int main(void) {
    char *input = safe_read_line();
    if (input == NULL) {
        input = malloc(1);
        if (input != NULL) {
            input[0] = '\0';
        }
    }

    if (input == NULL) {
        fprintf(stderr, "Failed to allocate input\n");
        return EXIT_FAILURE;
    }

    Node *list = string_to_list(input);
    if (list == NULL && input[0] != '\0') {
        fprintf(stderr, "Failed to allocate list\n");
        free(input);
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);
    free(input);

    return EXIT_SUCCESS;
}