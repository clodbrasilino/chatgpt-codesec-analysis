#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

static int is_separator_char(char c)
{
    unsigned char uc = (unsigned char)c;
    if (isspace(uc)) {
        return 1;
    }
    return c == '"' || c == '\'' || c == ',' || c == ';' ||
           c == ':' || c == '.' || c == '!' || c == '?' ||
           c == '[' || c == ']' || c == '(' || c == ')';
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
        while (str[i] != '\0' && is_separator_char(str[i])) {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        {
            size_t start = i;
            struct node *n;

            while (str[i] != '\0' && !is_separator_char(str[i])) {
                i++;
            }

            n = create_node(&str[start], i - start);
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

static char *read_all_input(void)
{
    size_t cap = 4096;
    size_t len = 0;
    char *buf = malloc(cap);

    if (buf == NULL) {
        return NULL;
    }

    for (;;) {
        int c = fgetc(stdin);
        if (c == EOF) {
            break;
        }
        if (len + 1 >= cap) {
            size_t new_cap = cap * 2;
            char *tmp = realloc(buf, new_cap);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
            cap = new_cap;
        }
        buf[len++] = (char)c;
    }

    buf[len] = '\0';
    return buf;
}

static char *join_args(int argc, char **argv)
{
    size_t total = 0;
    size_t pos = 0;
    int i;
    char *buf;

    for (i = 1; i < argc; i++) {
        total += strlen(argv[i]) + 1;
    }

    buf = malloc(total + 1);
    if (buf == NULL) {
        return NULL;
    }

    for (i = 1; i < argc; i++) {
        size_t alen = strlen(argv[i]);
        memcpy(buf + pos, argv[i], alen);
        pos += alen;
        if (i + 1 < argc) {
            buf[pos++] = ' ';
        }
    }
    buf[pos] = '\0';

    return buf;
}

int main(int argc, char **argv)
{
    char *input;
    struct node *list;

    if (argc > 1) {
        input = join_args(argc, argv);
    } else {
        input = read_all_input();
    }

    if (input == NULL) {
        (void)printf("[]\n");
        (void)fflush(stdout);
        return EXIT_SUCCESS;
    }

    list = string_to_word_list(input);

    print_list(list);

    free_list(list);
    free(input);

    return EXIT_SUCCESS;
}