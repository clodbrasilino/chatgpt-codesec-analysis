#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

static void free_list_partial(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

Node *create_node(const char *str, size_t len) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    
    if (len >= (size_t)-1) {
        free(node);
        return NULL;
    }
    
    node->data = (char *)malloc(len + 1);
    if (!node->data) {
        free(node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(node->data, str, len);
    node->data[len] = '\0';
    node->next = NULL;
    return node;
}

Node *string_to_list(const char *str) {
    if (!str) return NULL;
    
    Node *head = NULL;
    Node *tail = NULL;
    const char *start = str;
    const char *p = str;
    
    while (*p) {
        if (*p == ' ' || *p == '\t' || *p == '\n' || *p == ',') {
            if (p > start) {
                size_t len = (size_t)(p - start);
                Node *node = create_node(start, len);
                if (!node) {
                    free_list_partial(head);
                    return NULL;
                }
                
                if (!head) {
                    head = node;
                    tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
            }
            start = p + 1;
        }
        p++;
    }
    
    if (p > start) {
        size_t len = (size_t)(p - start);
        Node *node = create_node(start, len);
        if (!node) {
            free_list_partial(head);
            return NULL;
        }
        
        if (!head) {
            head = node;
        } else {
            tail->next = node;
        }
    }
    
    return head;
}

void free_list(Node *head) {
    free_list_partial(head);
}

void print_list(Node *head) {
    Node *current = head;
    while (current) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *input = "hello world foo bar";
    Node *list = string_to_list(input);
    
    if (list) {
        print_list(list);
        free_list(list);
    } else {
        fprintf(stderr, "Error converting string to list\n");
        return 1;
    }
    
    return 0;
}