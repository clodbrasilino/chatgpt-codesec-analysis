#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    node->data = malloc(len + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(node->data, str, len);
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
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    Node *list = string_to_list(buffer);

    if (list == NULL && buffer[0] != '\0') {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);
    list = NULL;

    return EXIT_SUCCESS;
}