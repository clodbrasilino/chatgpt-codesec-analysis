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
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node *string_to_list(const char *str, const char *delim) {
    Node *head = NULL;
    Node *tail = NULL;
    const char *p = str;

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
        
        const char *start = p;
        while (*p && !strchr(delim, *p)) {
            p++;
        }
        
        size_t len = p - start;
        char *value = (char *)malloc(len + 1);
        if (value == NULL) {
            free_list(head);
            return NULL;
        }
        memcpy(value, start, len);
        value[len] = '\0';
        
        Node *node = (Node *)malloc(sizeof(Node));
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
    Node *head = NULL;
    Node *tail = NULL;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (argv[i] != NULL) {
                Node *arg_list = string_to_list(argv[i], ", ");
                if (arg_list != NULL) {
                    if (head == NULL) {
                        head = arg_list;
                    } else {
                        tail->next = arg_list;
                    }
                    tail = arg_list;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                }
            }
        }
        if (head != NULL) {
            printf("[");
            Node *current = head;
            while (current != NULL) {
                printf("'%s'", current->value);
                if (current->next != NULL) {
                    printf(", ");
                }
                current = current->next;
            }
            printf("]\n");
            free_list(head);
        }
    } else {
        while (1) {
            char text[1024];
            if (!fgets(text, sizeof(text), stdin)) {
                break;
            }
            size_t len = strlen(text);
            while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r')) {
                text[--len] = '\0';
            }
            head = string_to_list(text, ", ");
            if (head != NULL) {
                printf("[");
                Node *current = head;
                while (current != NULL) {
                    printf("'%s'", current->value);
                    if (current->next != NULL) {
                        printf(", ");
                    }
                    current = current->next;
                }
                printf("]\n");
                free_list(head);
            }
        }
    }
    fflush(stdout);
    return 0;
}