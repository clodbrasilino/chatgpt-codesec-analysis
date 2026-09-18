#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* appendNode(Node *head, int data) {
    if (head == NULL) {
        return createNode(data);
    } else {
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = createNode(data);
        return head;
    }
}

Node** splitList(Node* head, int n) {
    if (head == NULL || n <= 0) {
        return NULL;
    }

    Node **list_array = (Node **)malloc(sizeof(Node*));
    int list_count = 0;
    Node *temp = head;
    Node *prev = NULL;

    while (temp != NULL) {
        if (list_count % n == 0) {
            list_array = (Node **)realloc(list_array, (list_count / n + 1) * sizeof(Node *));
            list_array[list_count / n] = temp;
            if (prev != NULL) {
                prev->next = NULL;
            }
        }
        prev = temp;
        temp = temp->next;
        /* Possible weaknesses found:
         *  leak of 'list_array' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        list_count++;
    }
    if (prev != NULL) {
        prev->next = NULL;
    }
    /* Possible weaknesses found:
     *  leak of 'list_array' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return list_array;
}

int main() {
    Node *head = NULL;
    for (int i = 1; i <= 10; i++) {
        head = appendNode(head, i);
    }

    Node **list_array = splitList(head, 3);
    if (list_array != NULL) {
        for (int i = 0; i < 4; i++) {
            Node *temp = list_array[i];
            while (temp != NULL) {
                printf("%d ", temp->data);
                temp = temp->next;
            }
            printf("\n");
        }
    } else {
        printf("Zero or negative splitting size or empty list is not allowed!\n");
    }
    return 0;
}