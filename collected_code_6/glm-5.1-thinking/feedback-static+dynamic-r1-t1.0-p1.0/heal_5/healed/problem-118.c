#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

static char *duplicate_string(const char *s) {
    size_t len = strlen(s);
    char *d = malloc(len + 1);
    if (d != NULL) {
        memcpy(d, s, len + 1);
    }
    return d;
}

Node *create_node(const char *token) {
    if (token == NULL) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = duplicate_string(token);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

Node *string_to_list(const char *str, const char *delim) {
    if (str == NULL) {
        return NULL;
    }
    if (delim == NULL || delim[0] == '\0') {
        delim = " \t\n\r\f\v";
    }
    
    Node *head = NULL;
    Node *tail = NULL;
    
    while (*str) {
        while (*str && strchr(delim, *str)) {
            str++;
        }
        if (!*str) {
            break;
        }
        
        const char *start = str;
        while (*str && !strchr(delim, *str)) {
            str++;
        }
        
        size_t len = str - start;
        char *token = malloc(len + 1);
        if (token == NULL) {
            free_list(head);
            return NULL;
        }
        memcpy(token, start, len);
        token[len] = '\0';
        
        Node *node = create_node(token);
        free(token);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    return head;
}

int main(void) {
    const char *text = "Convert this string to a list";
    Node *list = string_to_list(text, NULL);
    if (list != NULL) {
        Node *current = list;
        while (current != NULL) {
            printf("%s\n", current->value);
            current = current->next;
        }
        free_list(list);
    }
    return 0;
}