#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got ["python","0"
  */

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node **current = &head;
    if (!str) return NULL;
    const char *p = str;
    while (*p) {
        while (*p && isspace((unsigned char)*p)) p++;
        if (!*p) break;
        const char *start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        size_t len = p - start;
        Node *new_node = malloc(sizeof(*new_node));
        if (!new_node) {
            free_list(head);
            return NULL;
        }
        new_node->data = malloc(len + 1);
        if (!new_node->data) {
            free(new_node);
            free_list(head);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_node->data, start, len);
        new_node->data[len] = '\0';
        new_node->next = NULL;
        *current = new_node;
        current = &new_node->next;
    }
    return head;
}

char *read_line(FILE *stream) {
    size_t cap = 128;
    char *buf = malloc(cap);
    if (!buf) return NULL;
    size_t len = 0;
    int c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF) {
        if (c == '\n') {
            buf[len] = '\0';
            return buf;
        }
        if (len + 2 > cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    if (len == 0) {
        free(buf);
        return NULL;
    }
    if (len + 1 > cap) {
        char *tmp = realloc(buf, len + 1);
        if (!tmp) {
            free(buf);
            return NULL;
        }
        buf = tmp;
    }
    buf[len] = '\0';
    return buf;
}

int main(void) {
    char *line;
    while ((line = read_line(stdin)) != NULL) {
        Node *list = string_to_list(line);
        free(line);
        if (!list) continue;
        printf("[");
        for (Node *n = list; n; n = n->next) {
            printf("'%s'", n->data);
            if (n->next) printf(", ");
        }
        printf("]\n");
        free_list(list);
    }
    return EXIT_SUCCESS;
}