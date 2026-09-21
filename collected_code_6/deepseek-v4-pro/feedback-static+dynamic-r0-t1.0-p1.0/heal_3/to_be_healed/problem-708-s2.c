#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *node = NULL;
    size_t len;
    
    if (!str) return NULL;
    
    len = strnlen(str, 4096);
    if (len == 4096 && str[len] != '\0') {
        return NULL;
    }
    
    node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    
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

static void free_list_partial(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

Node *string_to_list(const char *str) {
    if (!str) return NULL;
    
    Node *head = NULL;
    Node *tail = NULL;
    const char *start = str;
    const char *p = str;
    char *token = NULL;
    size_t len;
    
    while (*p) {
        if (*p == ' ' || *p == '\t' || *p == '\n' || *p == ',') {
            /* Possible weaknesses found:
             *  Assuming that condition 'p>start' is not redundant
             */
            if (p > start) {
                /* Possible weaknesses found:
                 *  Assignment 'len=(unsigned long)(p-start)', assigned value is greater than 0
                 */
                len = (size_t)(p - start);
                /* Possible weaknesses found:
                 *  Condition 'len>0' is always true
                 *  Condition 'len>0' is always true [knownConditionTrueFalse]
                 */
                if (len > 0) {
                    token = (char *)malloc(len + 1);
                    /* Possible weaknesses found:
                     *  Assuming condition is false
                     */
                    if (!token) {
                        free_list_partial(head);
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     *  Condition 'len>0' is always true
                     *  Condition 'len>0' is always true [knownConditionTrueFalse]
                     */
                    if (len > 0) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(token, start, len);
                    }
                    token[len] = '\0';
                    
                    Node *node = create_node(token);
                    free(token);
                    token = NULL;
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
            }
            start = p + 1;
        }
        p++;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'p>start' is not redundant
     */
    if (p > start) {
        /* Possible weaknesses found:
         *  Assignment 'len=(unsigned long)(p-start)', assigned value is greater than 0
         */
        len = (size_t)(p - start);
        /* Possible weaknesses found:
         *  Condition 'len>0' is always true
         *  Condition 'len>0' is always true [knownConditionTrueFalse]
         */
        if (len > 0) {
            token = (char *)malloc(len + 1);
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (!token) {
                free_list_partial(head);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Condition 'len>0' is always true
             *  Condition 'len>0' is always true [knownConditionTrueFalse]
             */
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(token, start, len);
            }
            token[len] = '\0';
            
            Node *node = create_node(token);
            free(token);
            token = NULL;
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
    }
    
    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
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