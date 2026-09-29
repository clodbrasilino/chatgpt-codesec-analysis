#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 4096

struct node {
    char *word;
    struct node *next;
};

static struct node *create_node(const char *start, size_t len)
{
    struct node *n;

    if (start == NULL || len == SIZE_MAX) {
        return NULL;
    }

    n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }

    n->word = malloc(len + 1);
    if (n->word == NULL) {
        free(n);
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(n->word, start, len);
    }
    n->word[len] = '\0';
    n->next = NULL;
    return n;
}

static void free_list(struct node *head)
{
    while (head != NULL) {
        struct node *tmp = head;
        head = head->next;
        free(tmp->word);
        free(tmp);
    }
}

static struct node *string_to_word_list(const char *str, size_t max_len)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    size_t i = 0;
    size_t len;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(str, max_len);

    while (i < len) {
        size_t start;
        size_t word_len;
        struct node *n;

        while (i < len && (str[i] == ' ' || str[i] == '\t')) {
            i++;
        }
        if (i >= len) {
            break;
        }
        start = i;
        while (i < len && str[i] != ' ' && str[i] != '\t') {
            i++;
        }
        word_len = i - start;

        n = create_node(&str[start], word_len);
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

static int print_list(const struct node *head)
{
    const struct node *cur = head;

    if (printf("[") < 0) {
        return -1;
    }
    while (cur != NULL) {
        if (printf("'%s'", cur->word) < 0) {
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

    if (fgets(input, sizeof(input), stdin) == NULL) {
        (void)fprintf(stderr, "Failed to read input\n");
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
        int only_spaces = 1;
        size_t i;
        for (i = 0; i < len; i++) {
            if (input[i] != ' ' && input[i] != '\t') {
                only_spaces = 0;
                break;
            }
        }
        if (!only_spaces) {
            (void)fprintf(stderr, "Failed to build list\n");
            return EXIT_FAILURE;
        }
    }

    if (print_list(list) != 0) {
        free_list(list);
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}