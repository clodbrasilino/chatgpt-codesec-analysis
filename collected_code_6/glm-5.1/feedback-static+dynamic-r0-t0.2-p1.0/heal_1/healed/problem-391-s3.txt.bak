#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    struct Node *value;
    struct Node *next;
} Node;

Node *create_node(const char *key) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->key = strdup(key);
    if (!n->key) { free(n); return NULL; }
    n->value = NULL;
    n->next = NULL;
    return n;
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->value);
    free_tree(root->next);
    free(root->key);
    free(root);
}

Node *list_to_nested_dict(char **lists[], int num_lists) {
    if (!lists || num_lists <= 0) return NULL;
    
    Node *head = NULL;
    Node *tail = NULL;
    
    for (int i = 0; lists[0][i] != NULL; i++) {
        Node *current = create_node(lists[0][i]);
        if (!current) {
            free_tree(head);
            return NULL;
        }
        if (!head) {
            head = current;
        } else {
            tail->next = current;
        }
        tail = current;
    }
    
    if (num_lists == 1) return head;
    
    Node *curr = head;
    int idx = 0;
    while (curr) {
        char **remaining = malloc((num_lists - 1) * sizeof(char **));
        if (!remaining) {
            free_tree(head);
            return NULL;
        }
        for (int j = 1; j < num_lists; j++) {
            remaining[j - 1] = lists[j];
        }
        curr->value = list_to_nested_dict(remaining, num_lists - 1);
        free(remaining);
        if (!curr->value) {
            free_tree(head);
            return NULL;
        }
        curr = curr->next;
        idx++;
    }
    
    return head;
}

void print_nested_dict(Node *root, int depth) {
    if (!root) return;
    Node *curr = root;
    while (curr) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("%s", curr->key);
        if (curr->value) {
            printf(":\n");
            print_nested_dict(curr->value, depth + 1);
        } else {
            printf("\n");
        }
        curr = curr->next;
    }
}

int main(void) {
    char *list1[] = {"A", "B", "C", NULL};
    char *list2[] = {"1", "2", "3", NULL};
    char *list3[] = {"x", "y", "z", NULL};
    
    char **lists[] = {list1, list2, list3};
    
    Node *dict = list_to_nested_dict(lists, 3);
    if (dict) {
        print_nested_dict(dict, 0);
        free_tree(dict);
    }
    
    return 0;
}