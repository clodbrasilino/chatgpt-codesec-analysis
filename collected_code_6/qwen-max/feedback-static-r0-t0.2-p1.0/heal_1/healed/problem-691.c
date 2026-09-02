#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    int key;
    Node *values;
} Group;

int compare(const void *a, const void *b) {
    return ((Tuple *)a)->second - ((Tuple *)b)->second;
}

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void add_to_group(Group *group, int value) {
    Node *new_node = create_node(value);
    new_node->next = group->values;
    group->values = new_node;
}

Group* create_group(int key) {
    Group *new_group = (Node *)malloc(sizeof(Group));
    new_group->key = key;
    new_group->values = NULL;
    return new_group;
}

void free_group(Group *group) {
    Node *current = group->values;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(group);
}

void group_tuples(Tuple *tuples, int n, Group **groups, int *group_count) {
    qsort(tuples, n, sizeof(Tuple), compare);

    for (int i = 0; i < n; ++i) {
        if (*group_count == 0 || tuples[i].second != groups[*group_count - 1]->key) {
            groups[*group_count] = create_group(tuples[i].second);
            (*group_count)++;
        }
        add_to_group(groups[*group_count - 1], tuples[i].first);
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 2}, {4, 3}, {5, 3}, {6, 1}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    Group *groups[n];
    int group_count = 0;

    group_tuples(tuples, n, groups, &group_count);

    for (int i = 0; i < group_count; ++i) {
        printf("Key: %d, Values: ", groups[i]->key);
        Node *current = groups[i]->values;
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
        free_group(groups[i]);
    }

    return 0;
}