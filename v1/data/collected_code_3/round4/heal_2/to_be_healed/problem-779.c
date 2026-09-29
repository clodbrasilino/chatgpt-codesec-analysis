#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
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

void deleteList(struct Node* node) {
    struct Node* next_node;
    while(node != NULL) {
        next_node = node->next;
        free(node);
        node = next_node;
    }
}

int main() {
    struct Node* arr[5];

    arr[0] = newNode(10);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    arr[0]->next = newNode(20);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    arr[0]->next->next = newNode(30);

    arr[1] = newNode(10);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    arr[1]->next = newNode(20);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    arr[1]->next->next = newNode(30);

    arr[2] = newNode(40);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    arr[2]->next = newNode(50);

    arr[3] = newNode(10);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    arr[3]->next = newNode(20);
    arr[3]->next->next = newNode(30);

    arr[4] = newNode(40);
    arr[4]->next = newNode(50);

    printf("Number of unique lists: %d", countUnique(arr, 5));

    for (int i = 0; i < 5; i++) {
        deleteList(arr[i]);
    }

    return 0;
}