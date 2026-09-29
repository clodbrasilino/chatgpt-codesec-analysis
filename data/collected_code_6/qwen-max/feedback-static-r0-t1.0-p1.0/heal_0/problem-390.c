#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->value = strdup(str);
    if (!new_node->value) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}

Node* insert_before_all(Node *head, const char *prefix) {
    if (!prefix || !*prefix) return head;
    int prefix_len = strlen(prefix);
    Node *new_head = create_node(prefix);
    Node *last = new_head;
    for (Node *current = head; current; current = current->next) {
        int len = strlen(current->value) + prefix_len + 1;
        char *new_value = (char *)malloc(len);
        if (!new_value) continue;
        snprintf(new_value, len, "%s%s", prefix, current->value);
        last->next = create_node(new_value);
        free(new_value);
        if (!last->next) break;
        last = last->next;
    }
    return new_head;
}

int main() {
    Node *list = create_node("apple");
    list->next = create_node("banana");
    list->next->next = create_node("cherry");

    const char *prefix = "fruit-";
    Node *new_list = insert_before_all(list, prefix);

    for (Node *current = new_list; current; current = current->next) {
        printf("%s\n", current->value);
    }

    free_list(new_list);
    return 0;
}