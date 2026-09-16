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
    Node *data;
} Group;

int compare(const void *a, const void *b) {
    return ((Tuple *)a)->second - ((Tuple *)b)->second;
}

void addValueToGroup(Group *group, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (group->data == NULL) {
        group->data = newNode;
    } else {
        Node *temp = group->data;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void freeGroup(Group *group) {
    Node *current = group->data;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void printGroups(Group *groups, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d: ", groups[i].key);
        Node *temp = groups[i].data;
        while (temp != NULL) {
            printf("%d -> ", temp->value);
            temp = temp->temp;
        }
        printf("NULL\n");
    }
}

int main() {
    Tuple list[] = {{1, 2}, {3, 2}, {4, 3}, {5, 3}, {6, 1}};
    int n = sizeof(list) / sizeof(list[0]);

    qsort(list, n, sizeof(Tuple), compare);

    Group *groups = (Group *)malloc(n * sizeof(Group));
    int groupIndex = 0;
    groups[groupIndex].key = list[0].second;
    addValueToGroup(&groups[groupIndex], list[0].first);

    for (int i = 1; i < n; i++) {
        if (list[i].second == groups[groupIndex].key) {
            addValueToGroup(&groups[groupIndex], list[i].first);
        } else {
            groupIndex++;
            groups[groupIndex].key = list[i].second;
            addValueToGroup(&groups[groupIndex], list[i].first);
        }
    }

    printGroups(groups, groupIndex + 1);

    for (int i = 0; i <= groupIndex; i++) {
        freeGroup(&groups[i]);
    }
    free(groups);

    return 0;
}