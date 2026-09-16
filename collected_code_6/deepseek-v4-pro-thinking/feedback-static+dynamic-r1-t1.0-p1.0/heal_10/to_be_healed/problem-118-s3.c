#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node **current = &head;

    if (str == NULL) {
        return NULL;
    }

    const char *p = str;
    while (*p) {
        while (*p && !isalnum((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char *start = p;
        while (*p && isalnum((unsigned char)*p)) {
            p++;
        }
        size_t len = p - start;
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }
        new_node->data = malloc(len + 1);
        if (new_node->data == NULL) {
            free(new_node);
            free_list(head);
            return NULL;
        }
        memcpy(new_node->data, start, len);
        new_node->data[len] = '\0';
        new_node->next = NULL;
        *current = new_node;
        current = &new_node->next;
    }
    return head;
}

void print_list(const Node *list) {
    if (list == NULL) {
        return;
    }
    printf("[");
    for (const Node *n = list; n != NULL; n = n->next) {
        printf("'%s'", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

static char *read_line(void) {
    size_t size = 128;
    size_t len = 0;
    char *buf = malloc(size);
    int c;
    if (!buf) return NULL;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size *= 2;
            char *tmp = realloc(buf, size);
            if (!tmp) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    if (len == 0 && c == EOF) {
        free(buf);
        return NULL;
    }
    buf[len] = '\0';
    return buf;
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            Node *list = string_to_list(argv[i]);
            print_list(list);
            free_list(list);
        }
    } else {
        char *line;
        while ((line = read_line()) != NULL) {
            Node *list = string_to_list(line);
            print_list(list);
            free_list(list);
            free(line);
        }
    }
    return EXIT_SUCCESS;
}