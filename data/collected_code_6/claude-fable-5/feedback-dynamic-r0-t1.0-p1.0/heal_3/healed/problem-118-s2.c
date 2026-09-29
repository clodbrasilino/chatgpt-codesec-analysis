#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *word)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = malloc(strlen(word) + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    strcpy(node->data, word);
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

Node *string_to_word_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;
    char *copy;
    char *token;

    if (str == NULL) {
        return NULL;
    }

    copy = malloc(strlen(str) + 1);
    if (copy == NULL) {
        return NULL;
    }
    strcpy(copy, str);

    token = strtok(copy, " \t\r\n,.");
    while (token != NULL) {
        Node *node = create_node(token);
        if (node == NULL) {
            free_list(head);
            free(copy);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        token = strtok(NULL, " \t\r\n,.");
    }

    free(copy);
    return head;
}

void print_word_list(const Node *head)
{
    const Node *current = head;

    printf("[");
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
    fflush(stdout);
}

char *build_input_from_args(int argc, char *argv[])
{
    size_t total = 1;
    int i;
    char *result;

    for (i = 1; i < argc; i++) {
        total += strlen(argv[i]) + 1;
    }

    result = malloc(total);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    for (i = 1; i < argc; i++) {
        strcat(result, argv[i]);
        if (i < argc - 1) {
            strcat(result, " ");
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    char buffer[4096];
    char *input = NULL;
    Node *list;

    if (argc > 1) {
        input = build_input_from_args(argc, argv);
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    } else {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("[]\n");
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        input = buffer;
    }

    list = string_to_word_list(input);
    if (list == NULL && input[strspn(input, " \t\r\n,.")] != '\0') {
        fprintf(stderr, "Failed to convert string to list\n");
        if (argc > 1) {
            free(input);
        }
        return EXIT_FAILURE;
    }

    print_word_list(list);
    free_list(list);
    if (argc > 1) {
        free(input);
    }

    return EXIT_SUCCESS;
}