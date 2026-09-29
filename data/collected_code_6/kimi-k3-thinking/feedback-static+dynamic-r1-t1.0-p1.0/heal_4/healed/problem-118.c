#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *string_to_list(const char *str);
void print_list(const Node *head);
void free_list(Node *head);

static char *join_arguments(int argc, const char *const argv[])
{
    size_t total = 0;
    size_t remaining;
    int i;
    char *buffer;
    char *out;

    if (argv == NULL && argc > 1) {
        errno = EINVAL;
        return NULL;
    }

    for (i = 1; i < argc; i++) {
        size_t len;
        if (argv[i] == NULL) {
            break;
        }
        len = strlen(argv[i]);
        if (i > 1) {
            if (total >= SIZE_MAX - 1) {
                errno = ENOMEM;
                return NULL;
            }
            total += 1;
        }
        if (len >= SIZE_MAX - total) {
            errno = ENOMEM;
            return NULL;
        }
        total += len;
    }

    buffer = malloc(total + 1);
    if (buffer == NULL) {
        return NULL;
    }

    out = buffer;
    remaining = total + 1;
    for (i = 1; i < argc && argv[i] != NULL; i++) {
        size_t len = strlen(argv[i]);
        if (i > 1) {
            if (remaining < 2) {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }
            *out++ = ' ';
            remaining -= 1;
        }
        if (len >= remaining) {
            free(buffer);
            errno = ENOMEM;
            return NULL;
        }
        memcpy(out, argv[i], len);
        out += len;
        remaining -= len;
    }
    *out = '\0';

    return buffer;
}

static char *read_standard_input(void)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            char *grown;
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }
            grown = realloc(buffer, capacity * 2);
            if (grown == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = grown;
            capacity *= 2;
        }
        buffer[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        errno = EIO;
        return NULL;
    }

    buffer[length] = '\0';

    return buffer;
}

int main(int argc, char *argv[])
{
    char *input_buffer = NULL;
    const char *input;
    Node *list;

    if (argc > 1) {
        input_buffer = join_arguments(argc, (const char *const *)argv);
        if (input_buffer == NULL) {
            fprintf(stderr, "Error: out of memory\n");
            return EXIT_FAILURE;
        }
    } else {
        input_buffer = read_standard_input();
        if (input_buffer == NULL) {
            fprintf(stderr, "Error: out of memory\n");
            return EXIT_FAILURE;
        }
        if (input_buffer[0] == '\0') {
            free(input_buffer);
            input_buffer = NULL;
        }
    }

    input = (input_buffer != NULL) ? input_buffer : "Hello, World!";

    errno = 0;
    list = string_to_list(input);

    if (list == NULL && errno == ENOMEM) {
        fprintf(stderr, "Error: failed to convert string to list\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);
    free(input_buffer);

    return EXIT_SUCCESS;
}

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;

    if (str == NULL) {
        return NULL;
    }

    errno = 0;

    while (*str != '\0') {
        const char *start;
        size_t len;
        Node *new_node;

        while (*str != '\0' && isspace((unsigned char)*str)) {
            str++;
        }
        if (*str == '\0') {
            break;
        }

        start = str;
        while (*str != '\0' && !isspace((unsigned char)*str)) {
            str++;
        }
        len = (size_t)(str - start);

        if (len >= SIZE_MAX) {
            free_list(head);
            errno = ENOMEM;
            return NULL;
        }

        new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            free_list(head);
            errno = ENOMEM;
            return NULL;
        }

        new_node->data = malloc(len + 1);
        if (new_node->data == NULL) {
            free(new_node);
            free_list(head);
            errno = ENOMEM;
            return NULL;
        }

        memcpy(new_node->data, start, len);
        new_node->data[len] = '\0';
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

void print_list(const Node *head)
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
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}