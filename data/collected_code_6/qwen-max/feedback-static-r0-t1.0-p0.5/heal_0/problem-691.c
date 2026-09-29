#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void add_to_list(Node **head, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

void group_by_second(Tuple *tuples, int n, Node ***groups, int *group_count) {
    for (int i = 0; i < n; ++i) {
        if (tuples[i].second >= *group_count) {
            *group_count = tuples[i].second + 1;
            *groups = (Node **)realloc(*groups, *group_count * sizeof(Node *));
            (*groups)[tuples[i].second] = NULL;
        }
        add_to_list(&(*groups)[tuples[i].second], tuples[i].first);
    }
}

void print_groups(Node **groups, int group_count) {
    for (int i = 0; i < group_count; ++i) {
        printf("Group %d: ", i);
        Node *current = groups[i];
        while (current) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void free_groups(Node **groups, int group_count) {
    for (int i = 0; i < group_count; ++i) {
        Node *current = groups[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(groups);
}

int main() {
    Tuple tuples[] = {{1, 2}, {2, 2}, {3, 1}, {4, 1}, {5, 3}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    Node **groups = NULL;
    int group_count = 0;

    group_by_second(tuples, n, &groups, &group_count);
    print_groups(groups, group_count);
    free_groups(groups, group_count);

    return 0;
}