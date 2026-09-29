#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *data;
    struct node *next;
};

static struct node *create_node(const char *word)
{
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    n->data = malloc(strlen(word) + 1);
    if (n->data == NULL) {
        free(n);
        return NULL;
    }
    strcpy(n->data, word);
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
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

static struct node *string_to_list(const char *str)
{
    struct node *head = NULL;
    struct node *tail = NULL;
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

    token = strtok(copy, " \t\r\n");
    while (token != NULL) {
        struct node *n = create_node(token);
        if (n == NULL) {
            free_list(head);
            free(copy);
            return NULL;
        }
        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        token = strtok(NULL, " \t\r\n");
    }

    free(copy);
    return head;
}

static void print_list(const struct node *head)
{
    const struct node *cur = head;
    putchar('[');
    while (cur != NULL) {
        printf("'%s'", cur->data);
        if (cur->next != NULL) {
            printf(", ");
        }
        cur = cur->next;
    }
    printf("]\n");
    fflush(stdout);
}

static char *read_line(FILE *fp)
{
    size_t cap = 256;
    size_t len = 0;
    char *buf = malloc(cap);
    int c;

    if (buf == NULL) {
        return NULL;
    }

    c = fgetc(fp);
    if (c == EOF) {
        free(buf);
        return NULL;
    }

    while (c != EOF && c != '\n') {
        if (len + 2 > cap) {
            char *tmp;
            cap *= 2;
            tmp = realloc(buf, cap);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
        c = fgetc(fp);
    }
    buf[len] = '\0';
    return buf;
}

static char *build_from_args(int argc, char *argv[])
{
    size_t total = 0;
    int i;
    char *buf;

    for (i = 1; i < argc; i++) {
        total += strlen(argv[i]) + 1;
    }

    buf = malloc(total + 1);
    if (buf == NULL) {
        return NULL;
    }
    buf[0] = '\0';

    for (i = 1; i < argc; i++) {
        if (i > 1) {
            strcat(buf, " ");
        }
        strcat(buf, argv[i]);
    }
    return buf;
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc > 1) {
        char *input = build_from_args(argc, argv);
        struct node *list;
        if (input == NULL) {
            printf("[]\n");
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        list = string_to_list(input);
        print_list(list);
        free_list(list);
        free(input);
        return EXIT_SUCCESS;
    }

    for (;;) {
        char *line = read_line(stdin);
        struct node *list;
        if (line == NULL) {
            break;
        }
        list = string_to_list(line);
        print_list(list);
        free_list(list);
        free(line);
    }

    return EXIT_SUCCESS;
}