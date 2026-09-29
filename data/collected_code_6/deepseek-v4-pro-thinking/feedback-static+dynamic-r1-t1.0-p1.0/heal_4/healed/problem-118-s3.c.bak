#define _GNU_SOURCE
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
        memcpy(new_node->data, start, len);
        new_node->data[len] = '\0';
        new_node->next = NULL;
        *current = new_node;
        current = &new_node->next;
    }
    return head;
}

void print_list(Node *list) {
    if (list == NULL) {
        return;
    }
    printf("[");
    for (Node *n = list; n != NULL; n = n->next) {
        printf("'%s'", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            Node *list = string_to_list(argv[i]);
            print_list(list);
            free_list(list);
        }
    } else {
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;

        while ((nread = getline(&line, &len, stdin)) != -1) {
            if (nread > 0 && line[nread - 1] == '\n') {
                line[nread - 1] = '\0';
            }
            Node *list = string_to_list(line);
            print_list(list);
            free_list(list);
        }
        free(line);
    }
    return EXIT_SUCCESS;
}