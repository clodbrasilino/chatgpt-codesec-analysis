#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    struct Node *next;
};

struct Node *string_to_list(const char *str)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
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
        struct Node *node = malloc(sizeof(struct Node));
        if (node == NULL) {
            while (head != NULL) {
                struct Node *tmp = head;
                head = head->next;
                free(tmp);
            }
            return NULL;
        }
        node->data = str[i];
        node->next = NULL;

        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    return head;
}

void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(const struct Node *head)
{
    const struct Node *current = head;

    while (current != NULL) {
        if (printf("%c -> ", current->data) < 0) {
            return;
        }
        current = current->next;
    }
    (void)printf("NULL\n");
}

int main(void)
{
    const char *input = "Hello, World!";
    struct Node *list;

    list = string_to_list(input);
    if (list == NULL) {
        (void)fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}