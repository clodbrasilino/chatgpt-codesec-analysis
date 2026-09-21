#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char data;
    struct node *next;
};

static struct node *create_node(char c)
{
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    n->data = c;
    n->next = NULL;
    return n;
}

static void free_list(struct node *head)
{
    while (head != NULL) {
        struct node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

static struct node *string_to_list(const char *str)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    size_t i;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0; i < len; i++) {
        struct node *n = create_node(str[i]);
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

static void print_list(const struct node *head)
{
    const struct node *cur = head;
    while (cur != NULL) {
        if (printf("%c -> ", cur->data) < 0) {
            return;
        }
        cur = cur->next;
    }
    if (printf("NULL\n") < 0) {
        return;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     *  Assignment 'input="hello"', assigned value is "hello"
     */
    const char *input = "hello";
    struct node *list = string_to_list(input);

    /* Possible weaknesses found:
     *  Condition 'strlen(input)>0' is always true [knownConditionTrueFalse]
     *  Condition 'strlen(input)>0' is always true
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (list == NULL && strlen(input) > 0) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}