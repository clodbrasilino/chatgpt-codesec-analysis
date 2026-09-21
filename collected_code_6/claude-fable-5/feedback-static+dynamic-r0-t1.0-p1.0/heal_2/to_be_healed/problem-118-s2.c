#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node *create_node(const char *start, size_t length)
{
    Node *node;
    char *word;

    if (start == NULL || length == 0) {
        return NULL;
    }

    node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    word = malloc(length + 1);
    if (word == NULL) {
        free(node);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(word, start, length);
    word[length] = '\0';

    node->word = word;
    node->next = NULL;
    return node;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp->word);
        free(tmp);
    }
}

Node *string_to_word_list(const char *str, size_t max_len)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i = 0;

    if (str == NULL) {
        return NULL;
    }

    while (i < max_len && str[i] != '\0') {
        while (i < max_len && str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }

        if (i >= max_len || str[i] == '\0') {
            break;
        }

        {
            size_t start = i;
            size_t length;
            Node *node;

            while (i < max_len && str[i] != '\0' && !isspace((unsigned char)str[i])) {
                i++;
            }

            length = i - start;
            node = create_node(&str[start], length);
            if (node == NULL) {
                free_list(head);
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

    return head;
}

int print_word_list(const Node *head)
{
    const Node *current = head;

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    while (current != NULL) {
        if (printf("'%s'", current->word) < 0) {
            return -1;
        }
        if (current->next != NULL) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
        current = current->next;
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    Node *list;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    list = string_to_word_list(input, sizeof(input));
    if (list == NULL && len > 0) {
        int only_spaces = 1;
        size_t i;
        for (i = 0; i < len; i++) {
            if (!isspace((unsigned char)input[i])) {
                only_spaces = 0;
                break;
            }
        }
        if (!only_spaces) {
            fprintf(stderr, "Failed to convert string to list\n");
            return EXIT_FAILURE;
        }
    }

    if (print_word_list(list) != 0) {
        free_list(list);
        fprintf(stderr, "Failed to print list\n");
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}