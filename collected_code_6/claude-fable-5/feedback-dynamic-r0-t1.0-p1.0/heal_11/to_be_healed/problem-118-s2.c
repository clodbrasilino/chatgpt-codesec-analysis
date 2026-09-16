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
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

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

char *read_line_from_stdin(void)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int c = EOF;

    if (buffer == NULL) {
        return NULL;
    }

    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (length + 2 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length++] = (char)c;
    }

    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(int argc, char *argv[])
{
    char *input = NULL;
    Node *list;

    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc > 1) {
        input = build_input_from_args(argc, argv);
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        list = string_to_word_list(input);
        print_word_list(list);
        free_list(list);
        free(input);
        return EXIT_SUCCESS;
    }

    while ((input = read_line_from_stdin()) != NULL) {
        list = string_to_word_list(input);
        print_word_list(list);
        free_list(list);
        free(input);
    }

    return EXIT_SUCCESS;
}