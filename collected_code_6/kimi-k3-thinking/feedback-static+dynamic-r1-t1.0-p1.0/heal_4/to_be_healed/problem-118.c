#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *string_to_list(const char *str);
void print_list(const Node *head);
void free_list(Node *head);
char *read_stream(FILE *stream);
char *join_arguments(int argc, char * const argv[]);

int main(int argc, char *argv[])
{
    char *input;

    if (argc > 1) {
        input = join_arguments(argc, argv);
    } else {
        input = read_stream(stdin);
    }

    if (input == NULL) {
        fprintf(stderr, "Error: failed to obtain input\n");
        return EXIT_FAILURE;
    }

    Node *list = string_to_list(input);

    print_list(list);

    free_list(list);
    free(input);

    return EXIT_SUCCESS;
}

char *read_stream(FILE *stream)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    int ch;
    while ((ch = fgetc(stream)) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = resized;
            capacity = new_capacity;
        }
        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
char *join_arguments(int argc, char * const argv[])
{
    size_t total = 1;

    for (int i = 1; i < argc; i++) {
        total += strlen(argv[i]) + 1;
    }

    char *buffer = malloc(total);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    for (int i = 1; i < argc; i++) {
        strcat(buffer, argv[i]);
        if (i + 1 < argc) {
            strcat(buffer, " ");
        }
    }

    return buffer;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  */

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;

    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        while (*str != '\0' && isspace((unsigned char)*str)) {
            str++;
        }
        if (*str == '\0') {
            break;
        }

        const char *start = str;
        while (*str != '\0' && !isspace((unsigned char)*str)) {
            str++;
        }
        size_t len = (size_t)(str - start);

        Node *new_node = malloc(sizeof *new_node);
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        new_node->data = malloc(len + 1);
        if (new_node->data == NULL) {
            free(new_node);
            free_list(head);
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
    fflush(stdout);
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