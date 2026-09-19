#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node *tail = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    const char *start;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    char *word;
    Node *new_node;

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

        start = str;
        while (*str && !isspace((unsigned char)*str)) {
            str++;
        }
        len = str - start;

        word = malloc(len + 1);
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

        new_node = malloc(sizeof(*new_node));
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

int main(int argc, char *argv[]) {
    Node *list;

    if (argc < 2) {
        print_list(NULL);
        return EXIT_SUCCESS;
    }

    list = string_to_list(argv[1]);
    if (list == NULL && argv[1][0] != '\0') {
        fprintf(stderr, "Failed to allocate list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}