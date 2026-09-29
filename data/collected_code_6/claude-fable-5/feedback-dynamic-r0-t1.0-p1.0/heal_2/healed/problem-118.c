#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *word;
    struct node *next;
};

static struct node *create_node(const char *start, size_t len)
{
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    n->word = malloc(len + 1);
    if (n->word == NULL) {
        free(n);
        return NULL;
    }
    memcpy(n->word, start, len);
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

static struct node *string_to_word_list(const char *str)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    size_t i = 0;

    if (str == NULL) {
        return NULL;
    }

    while (str[i] != '\0') {
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r') {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        {
            size_t start = i;
            while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
                i++;
            }
            {
                struct node *n = create_node(&str[start], i - start);
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
        }
    }

    return head;
}

static void print_list(const struct node *head)
{
    const struct node *cur = head;

    (void)printf("[");
    while (cur != NULL) {
        (void)printf("'%s'", cur->word);
        if (cur->next != NULL) {
            (void)printf(", ");
        }
        cur = cur->next;
    }
    (void)printf("]\n");
    (void)fflush(stdout);
}

int main(void)
{
    char buffer[4096];
    struct node *list;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        (void)printf("[]\n");
        (void)fflush(stdout);
        return EXIT_SUCCESS;
    }

    list = string_to_word_list(buffer);

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}