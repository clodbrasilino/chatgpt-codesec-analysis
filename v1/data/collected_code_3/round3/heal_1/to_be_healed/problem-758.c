#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int compareLists(struct Node* a, struct Node* b) {
    while (a != NULL && b != NULL) {
        if (a->data != b->data)
            return 0;
        a = a->next;
        b = b->next;
    }
    return (a == NULL && b == NULL);
}

int countUnique(struct Node* arr[], int n) {
    int count = 1;
    for (int i = 1; i < n; i++) {
        int j = 0;
        for (j = 0; j < i; j++)
            if (compareLists(arr[i], arr[j]))
                break;
        if (i == j)
            count++;
    }
    return count;
}

int main() {
    struct Node* arr[5];

    arr[0] = newNode(10);
    arr[0]->next = newNode(20);
    arr[0]->next->next = newNode(30);

    arr[1] = newNode(10);
    arr[1]->next = newNode(20);
    arr[1]->next->next = newNode(30);

    arr[2] = newNode(40);
    arr[2]->next = newNode(50);

    arr[3] = newNode(10);
    arr[3]->next = newNode(20);
    arr[3]->next->next = newNode(30);

    arr[4] = newNode(40);
    arr[4]->next = newNode(50);

    printf("Number of unique lists : %d", countUnique(arr, 5));

    return 0;
}