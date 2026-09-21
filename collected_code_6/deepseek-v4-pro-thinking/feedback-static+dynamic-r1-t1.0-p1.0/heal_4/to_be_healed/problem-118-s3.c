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
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node **current = &head;

    if (str == NULL) {
        return NULL;
    }

    const char *p = str;
    while (*p) {
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char *start = p;
        while (*p && !isspace((unsigned char)*p)) {
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
    size_t size = 128;
    char *buffer = malloc(size);
    if (!buffer) return NULL;
    size_t pos = 0;
    int c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= size) {
            size *= 2;
            char *newbuf = realloc(buffer, size);
            if (!newbuf) {
                free(buffer);
                return NULL;
            }
            buffer = newbuf;
        }
        if (c == '\n') {
            buffer[pos] = '\0';
            return buffer;
        }
        buffer[pos++] = (char)c;
    }
    if (pos == 0) {
        free(buffer);
        return NULL;
    }
    if (pos >= size) {
        size = pos + 1;
        char *newbuf = realloc(buffer, size);
        if (!newbuf) {
            free(buffer);
            return NULL;
        }
        buffer = newbuf;
    }
    buffer[pos] = '\0';
    return buffer;
}

int main(void) {
    char *line;
    while ((line = read_line(stdin)) != NULL) {
        Node *list = string_to_list(line);
        free(line);
        if (list == NULL) {
            continue;
        }
        for (Node *n = list; n != NULL; n = n->next) {
            printf("%s\n", n->data);
        }
        free_list(list);
    }
    return EXIT_SUCCESS;
}