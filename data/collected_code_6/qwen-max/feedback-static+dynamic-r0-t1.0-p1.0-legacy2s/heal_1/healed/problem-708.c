#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node* create_node(const char *value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = strdup(value);
    if (new_node->value == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}

Node* split_string_to_list(const char *str, char delimiter) {
    Node *head = NULL;
    Node **current = &head;
    const char *start = str;
    while (*str) {
        if (*str == delimiter) {
            size_t len = str - start;
            char *new_value = (char*)malloc((len + 1) * sizeof(char));
            if (new_value == NULL) {
                free_list(head);
                return NULL;
            }
            memcpy(new_value, start, len);
            new_value[len] = '\0';
            *current = create_node(new_value);
            free(new_value);
            if (*current == NULL) {
                free_list(head);
                return NULL;
            }
            current = &(*current)->next;
            start = str + 1;
        }
        str++;
    }
    if (start != str) {
        size_t len = str - start;
        char *new_value = (char*)malloc((len + 1) * sizeof(char));
        if (new_value == NULL) {
            free_list(head);
            return NULL;
        }
        memcpy(new_value, start, len);
        new_value[len] = '\0';
        *current = create_node(new_value);
        free(new_value);
        if (*current == NULL) {
            free_list(head);
            return NULL;
        }
    }
    return head;
}

int main() {
    const char *input = "apple,banana,orange,grape";
    Node *list = split_string_to_list(input, ',');
    for (Node *node = list; node != NULL; node = node->next) {
        printf("%s\n", node->value);
    }
    free_list(list);
    return 0;
}