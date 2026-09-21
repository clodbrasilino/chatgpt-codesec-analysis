#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

static Node *create_node(const char *str, size_t len)
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }
    if (len == SIZE_MAX) {
        free(node);
        return NULL;
    }
    node->data = malloc(len + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    if (len > 0) {
        memcpy(node->data, str, len);
    }
    node->data[len] = '\0';
    node->next = NULL;
    return node;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head->data);
        free(head);
        head = next;
    }
}

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;

    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        while (isspace((unsigned char)*str)) {
            str++;
        }
        if (*str == '\0') {
            break;
        }
        const char *start = str;
        while (*str != '\0' && !isspace((unsigned char)*str)) {
            str++;
        }
        Node *node = create_node(start, (size_t)(str - start));
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    return head;
}

void print_list(const Node *head)
{
    putchar('[');
    while (head != NULL) {
        printf("'%s'", head->data);
        head = head->next;
        if (head != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

static char *read_stream(FILE *stream)
{
    size_t capacity = 256;
    size_t length = 0;
    int ch;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            char *resized = realloc(buffer, capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = resized;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';
    return buffer;
}

static char *join_arguments(int argc, char *argv[])
{
    size_t total = 1;

    for (int i = 1; i < argc; i++) {
        size_t arg_len = strlen(argv[i]);
        if (arg_len > SIZE_MAX - total - 1) {
            return NULL;
        }
        total += arg_len + 1;
    }

    char *joined = malloc(total);
    if (joined == NULL) {
        return NULL;
    }

    char *out = joined;
    for (int i = 1; i < argc; i++) {
        if (i > 1) {
            *out++ = ' ';
        }
        size_t arg_len = strlen(argv[i]);
        memcpy(out, argv[i], arg_len);
        out += arg_len;
    }
    *out = '\0';
    return joined;
}

int main(int argc, char *argv[])
{
    char *input;

    if (argc > 1) {
        input = join_arguments(argc, argv);
    } else {
        input = read_stream(stdin);
    }

    if (input == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    Node *list = string_to_list(input);

    if (list == NULL) {
        const char *p = input;
        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p != '\0') {
            fprintf(stderr, "Failed to convert string to list\n");
            free(input);
            return EXIT_FAILURE;
        }
    }

    print_list(list);
    free_list(list);
    list = NULL;
    free(input);
    input = NULL;

    return EXIT_SUCCESS;
}