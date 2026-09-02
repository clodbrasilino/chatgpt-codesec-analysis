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

Group* create_group(int key) {
    Group *group = (Group *)malloc(sizeof(Group));
    group->key = key;
    group->values = NULL;
    return group;
}

void add_to_group(Group *group, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = group->values;
    group->values = new_node;
}

void free_group(Group *group) {
    Node *current = group->values;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(group);
}

void group_tuples(Tuple *tuples, int n, Group **groups, int *group_count) {
    qsort(tuples, n, sizeof(Tuple), compare);

    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  Uninitialized variable: groups [uninitvar]
         *  Uninitialized variable: groups
         */
        if (*group_count == 0 || groups[*group_count - 1]->key != tuples[i].second) {
            groups[*group_count] = create_group(tuples[i].second);
            (*group_count)++;
        }
        add_to_group(groups[*group_count - 1], tuples[i].first);
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 2}, {4, 3}, {5, 3}, {6, 4}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    Group *groups[n];
    int group_count = 0;

    /* Possible weaknesses found:
     *  Calling function 'group_tuples', 3rd argument 'groups' value is <Uninit>
     */
    group_tuples(tuples, n, groups, &group_count);

    for (int i = 0; i < group_count; ++i) {
        printf("Group %d: ", groups[i]->key);
        Node *current = groups[i]->values;
        while (current) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
        free_group(groups[i]);
    }

    return 0;
}