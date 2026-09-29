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
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
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

int main(void)
{
    char buffer[4096];
    Node *list;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("[]\n");
        fflush(stdout);
        return EXIT_SUCCESS;
    }

    list = string_to_word_list(buffer);
    if (list == NULL && buffer[strspn(buffer, " \t\r\n,.")] != '\0') {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_word_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}