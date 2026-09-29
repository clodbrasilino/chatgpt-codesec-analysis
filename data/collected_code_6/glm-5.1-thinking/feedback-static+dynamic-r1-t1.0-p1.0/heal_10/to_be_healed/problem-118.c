#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *create_node(const char *token, size_t len) {
    if (token == NULL) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    if (len == (size_t)-1) {
        free(node);
        return NULL;
    }
    node->value = malloc(len + 1);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        node->value[i] = token[i];
    }
    node->value[len] = '\0';
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
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  */

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
        while (*str && strchr(delim, (unsigned char)*str)) {
            str++;
        }
        if (!*str) {
            break;
        }
        
        const char *start = str;
        while (*str && !strchr(delim, (unsigned char)*str)) {
            str++;
        }
        
        size_t len = str - start;
        Node *node = create_node(start, len);
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

int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[8192];
    const char *text = NULL;
    const char *delim = NULL;
    
    if (argc > 1) {
        text = argv[1];
    } else {
        if (fgets(buf, sizeof(buf), stdin)) {
            buf[strcspn(buf, "\n")] = '\0';
            text = buf;
        }
    }
    if (argc > 2) {
        delim = argv[2];
    }
    
    Node *list = string_to_list(text, delim);
    printf("[");
    Node *current = list;
    while (current != NULL) {
        printf("'%s'", current->value);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
    
    free_list(list);
    return 0;
}