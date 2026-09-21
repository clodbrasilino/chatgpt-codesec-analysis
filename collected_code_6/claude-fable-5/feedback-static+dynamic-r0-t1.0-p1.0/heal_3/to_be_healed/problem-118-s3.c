#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

struct node {
    char *data;
    struct node *next;
};

static struct node *create_node(const char *word, size_t len)
{
    struct node *n;

    if (word == NULL || len == 0 || len >= MAX_INPUT) {
        return NULL;
    }

    n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }

    n->data = malloc(len + 1);
    if (n->data == NULL) {
        free(n);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(n->data, word, len);
    n->data[len] = '\0';
    n->next = NULL;
    return n;
}

static void free_list(struct node *head)
{
    while (head != NULL) {
        struct node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

static struct node *string_to_word_list(const char *str, size_t max_len)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    size_t i = 0;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    while (i < max_len && str[i] != '\0') {
        size_t start;
        size_t len;
        struct node *n;

        while (i < max_len && str[i] != '\0' &&
               (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) {
            i++;
        }

        if (i >= max_len || str[i] == '\0') {
            break;
        }

        start = i;
        while (i < max_len && str[i] != '\0' &&
               str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            i++;
        }
        len = i - start;

        n = create_node(&str[start], len);
        if (n == NULL) {
            free_list(head);
            return NULL;
        }

        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }

    return head;
}

static int print_word_list(const struct node *head)
{
    const struct node *cur = head;

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    while (cur != NULL) {
        if (printf("'%s'", cur->data) < 0) {
            return -1;
        }
        if (cur->next != NULL) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
        cur = cur->next;
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
    struct node *list;
    size_t len;

    memset(input, 0, sizeof(input));

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';
    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    list = string_to_word_list(input, sizeof(input));
    if (list == NULL && len > 0) {
        int only_whitespace = 1;
        size_t i;
        for (i = 0; i < len; i++) {
            if (input[i] != ' ' && input[i] != '\t') {
                only_whitespace = 0;
                break;
            }
        }
        if (!only_whitespace) {
            fprintf(stderr, "Failed to convert string to list\n");
            return EXIT_FAILURE;
        }
    }

    if (print_word_list(list) != 0) {
        free_list(list);
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}