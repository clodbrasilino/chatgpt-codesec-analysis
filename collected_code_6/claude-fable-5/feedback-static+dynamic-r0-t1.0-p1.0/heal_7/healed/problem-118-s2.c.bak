#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *word, size_t len)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = malloc(len + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    memcpy(node->data, word, len);
    node->data[len] = '\0';
    node->next = NULL;
    return node;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

Node *string_to_word_list(const char *str, int *error)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i = 0;

    *error = 0;

    if (str == NULL) {
        return NULL;
    }

    while (str[i] != '\0') {
        while (str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        {
            size_t start = i;
            while (str[i] != '\0' && !isspace((unsigned char)str[i])) {
                i++;
            }
            {
                Node *node = create_node(&str[start], i - start);
                if (node == NULL) {
                    free_list(head);
                    *error = 1;
                    return NULL;
                }
                if (head == NULL) {
                    head = node;
                    tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
            }
        }
    }

    return head;
}

void print_list(const Node *head)
{
    const Node *current = head;
    putchar('[');
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

int main(int argc, const char *argv[])
{
    char buffer[1024];
    Node *list;
    int error;

    if (argc > 1) {
        size_t pos = 0;
        int i;
        buffer[0] = '\0';
        for (i = 1; i < argc; i++) {
            size_t len = strlen(argv[i]);
            if (pos + len + 2 >= sizeof(buffer)) {
                break;
            }
            if (i > 1) {
                buffer[pos++] = ' ';
            }
            memcpy(&buffer[pos], argv[i], len);
            pos += len;
            buffer[pos] = '\0';
        }
    } else {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            buffer[0] = '\0';
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
    }

    list = string_to_word_list(buffer, &error);
    if (error) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}