#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    int second;
    Node* head;
} Group;

int compare(const void* a, const void* b) {
    return ((Tuple*)a)->second - ((Tuple*)b)->second;
}

void add_to_group(Group* group, int first) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = first;
    new_node->next = NULL;

    if (group->head == NULL) {
        group->head = new_node;
    } else {
        Node* current = group->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_groups(Group* groups, int size) {
    for (int i = 0; i < size; i++) {
        printf("Group %d: ", groups[i].second);
        Node* current = groups[i].head;
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}

void free_groups(Group* groups, int size) {
    for (int i = 0; i < size; i++) {
        Node* current = groups[i].head;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(groups);
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 2}, {7, 4}, {9, 6}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    qsort(tuples, n, sizeof(Tuple), compare);

    int group_count = 1;
    for (int i = 1; i < n; i++) {
        if (tuples[i].second != tuples[i-1].second) {
            group_count++;
        }
    }

    Group* groups = (Group*)calloc(group_count, sizeof(Group));
    if (groups == NULL) return 1;

    int group_index = 0;
    groups[group_index].second = tuples[0].second;
    add_to_group(&groups[group_index], tuples[0].first);

    for (int i = 1; i < n; i++) {
        if (tuples[i].second != groups[group_index].second) {
            group_index++;
            groups[group_index].second = tuples[i].second;
        }
        add_to_group(&groups[group_index], tuples[i].first);
    }

    print_groups(groups, group_count);
    free_groups(groups, group_count);

    return 0;
}