#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

typedef struct Node {
    char *str;
    float value;
    int is_float;
    struct Node *next;
} Node;

static size_t safe_strlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

Node *create_node(const char *text) {
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    if (text == NULL) {
        free(new_node);
        return NULL;
    }
    size_t len = safe_strlen(text, MAX_STRING_LENGTH);
    new_node->str = malloc(len + 1);
    if (new_node->str == NULL) {
        free(new_node);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->str, text, len);
    new_node->str[len] = '\0';
    new_node->value = 0.0f;
    new_node->is_float = 0;
    new_node->next = NULL;
    return new_node;
}

int append_node(Node **head, const char *text) {
    Node *new_node = create_node(text);
    if (new_node == NULL) {
        return 0;
    }
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return 1;
}

void convert_list_to_float(Node *head) {
    Node *current = head;
    while (current != NULL) {
        if (current->is_float == 0 && current->str != NULL) {
            char *endptr = NULL;
            errno = 0;
            float converted = strtof(current->str, &endptr);
            if (endptr != current->str) {
                while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
                    endptr++;
                }
                if (*endptr == '\0') {
                    if (errno != ERANGE || (converted != HUGE_VALF && converted != -HUGE_VALF)) {
                        free(current->str);
                        current->str = NULL;
                        current->value = converted;
                        current->is_float = 1;
                    }
                }
            }
        }
        current = current->next;
    }
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        if (current->is_float) {
            printf("%f\n", current->value);
        } else if (current->str != NULL) {
            printf("%s\n", current->str);
        }
        current = current->next;
    }
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head->str);
        free(head);
        head = next;
    }
}

int main(void) {
    Node *head = NULL;
    if (!append_node(&head, "3.14") ||
        !append_node(&head, "abc") ||
        !append_node(&head, "2.718") ||
        !append_node(&head, " 1.5 ") ||
        !append_node(&head, "") ||
        !append_node(&head, "42")) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(head);
        return EXIT_FAILURE;
    }
    convert_list_to_float(head);
    print_list(head);
    free_list(head);
    return EXIT_SUCCESS;
}