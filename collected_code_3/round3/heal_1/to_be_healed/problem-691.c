#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int first;
    int second;
} Tuple;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node** groupBySecond(Tuple* tuples, int size) {
    Node** groups = (Node**)malloc(sizeof(Node*) * size);
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'groups' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        groups[i] = NULL;
    }

    for(int i = 0; i < size; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        newNode->data = tuples[i].first;
        newNode->next = groups[tuples[i].second];
        groups[tuples[i].second] = newNode;
    }

    return groups;
}

void printGroups(Node** groups, int size) {
    for(int i = 0; i < size; i++) {
        Node* temp = groups[i];
        printf("Group %d: ", i);
        while(temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    Tuple tuples[] = {{1, 0}, {2, 1}, {3, 0}, {4, 1}, {5, 0}};
    int size = sizeof(tuples) / sizeof(Tuple);

    Node** groups = groupBySecond(tuples, size);

    printGroups(groups, size);

    for(int i = 0; i < size; i++) {
        Node* temp = groups[i];
        while(temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }

    free(groups);

    return 0;
}