#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

void free_list(Node *head) {
    Node *current = head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

Node *string_to_list(const char *str, const char *delim) {
    Node *head = NULL;
    Node *tail = NULL;
    const char *p = str;
    const char *start;
    size_t len;
    char *value;
    Node *node;

    if (str == NULL || delim == NULL) {
        return NULL;
    }
    
    while (*p) {
        while (*p && strchr(delim, *p)) {
            p++;
        }
        if (!*p) {
            break;
        }
        
        start = p;
        while (*p && !strchr(delim, *p)) {
            p++;
        }
        
        len = p - start;
        value = (char *)malloc(len + 1);
        if (value == NULL) {
            free_list(head);
            return NULL;
        }
        memcpy(value, start, len);
        value[len] = '\0';
        
        node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
            free(value);
            free_list(head);
            return NULL;
        }
        node->value = value;
        node->next = NULL;
        
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

int main(int argc, const char *const argv[]) {
    int i;
    char text[1024];
    size_t len;
    Node *list;
    Node *current;

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (argv[i] != NULL) {
                list = string_to_list(argv[i], ", ");
                if (list != NULL) {
                    printf("[");
                    current = list;
                    while (current != NULL) {
                        printf("'%s'", current->value);
                        if (current->next != NULL) {
                            printf(", ");
                        }
                        current = current->next;
                    }
                    printf("]\n");
                    free_list(list);
                }
            }
        }
    } else {
        while (1) {
            if (!fgets(text, sizeof(text), stdin)) {
                break;
            }
            len = strlen(text);
            while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r')) {
                text[--len] = '\0';
            }
            list = string_to_list(text, ", ");
            if (list != NULL) {
                printf("[");
                current = list;
                while (current != NULL) {
                    printf("'%s'", current->value);
                    if (current->next != NULL) {
                        printf(", ");
                    }
                    current = current->next;
                }
                printf("]\n");
                free_list(list);
            }
        }
    }
    fflush(stdout);
    return 0;
}