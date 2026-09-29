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

/* Possible weaknesses found:
 *  expected 'Group *' but argument is of type 'Group **'
 */
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

/* Possible weaknesses found:
 *  expected 'Group **' but argument is of type 'Group *'
 */
void group_tuples(Tuple *tuples, int n, Group **groups, int *group_count) {
    qsort(tuples, n, sizeof(Tuple), compare);

    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  '*(groups + ((sizetype)((long unsigned int)*group_count * 8) - 8))' is a pointer; did you mean to use '->'?
         *  member reference type 'Group *' is a pointer; did you mean to use '->'?
         */
        if (*group_count == 0 || tuples[i].second != groups[*group_count - 1].key) {
            /* Possible weaknesses found:
             *  '*(groups + (sizetype)((long unsigned int)*group_count * 8))' is a pointer; did you mean to use '->'?
             *  member reference type 'Group *' is a pointer; did you mean to use '->'?
             */
            groups[*group_count].key = tuples[i].second;
            /* Possible weaknesses found:
             *  '*(groups + (sizetype)((long unsigned int)*group_count * 8))' is a pointer; did you mean to use '->'?
             *  member reference type 'Group *' is a pointer; did you mean to use '->'?
             */
            groups[*group_count].head = NULL;
            *group_count += 1;
        }
        /* Possible weaknesses found:
         *  passing argument 1 of 'add_to_group' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        add_to_group(&groups[*group_count - 1], tuples[i].first);
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 2}, {4, 3}, {5, 3}, {6, 4}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    Group *groups = (Group *)malloc(n * sizeof(Group));
    int group_count = 0;

    /* Possible weaknesses found:
     *  passing argument 3 of 'group_tuples' from incompatible pointer type [-Wincompatible-pointer-types]
     */
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