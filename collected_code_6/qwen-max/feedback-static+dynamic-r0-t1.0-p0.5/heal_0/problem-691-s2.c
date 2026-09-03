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

typedef struct {
    int key;
    Node *head;
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
    if (group->head == NULL) {
        group->head = new_node;
    } else {
        Node *current = group->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void group_tuples(Tuple *tuples, int n, Group **groups, int *group_count) {
    qsort(tuples, n, sizeof(Tuple), compare);

    for (int i = 0; i < n; ++i) {
        if (*group_count == 0 || tuples[i].second != groups[*group_count - 1].key) {
            groups[*group_count].key = tuples[i].second;
            groups[*group_count].head = NULL;
            *group_count += 1;
        }
        add_to_group(&groups[*group_count - 1], tuples[i].first);
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 2}, {4, 3}, {5, 3}, {6, 4}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    Group *groups = (Group *)malloc(n * sizeof(Group));
    int group_count = 0;

    group_tuples(tuples, n, groups, &group_count);

    for (int i = 0; i < group_count; ++i) {
        printf("Group %d: ", groups[i].key);
        Node *current = groups[i].head;
        while (current != NULL) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n");
    }

    for (int i = 0; i < group_count; ++i) {
        free_list(groups[i].head);
    }
    free(groups);

    return 0;
}