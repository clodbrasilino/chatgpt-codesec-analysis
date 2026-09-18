#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int len;
    struct node** next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));

    if(temp == NULL) return NULL;
    temp->data = data;
    temp->len = 0;
    temp->next = NULL;
    return temp;
}

void addToList(Node** head, int data) {
    if (head == NULL) return;
    if (!(*head)) {
        *head = newNode(data);
        if (*head == NULL) return;
    } else {
        (*head)->len++;
        (*head)->next = (Node**)realloc((*head)->next, (*head)->len * sizeof(Node*));

        if((*head)->next == NULL) return;

        (*head)->next[(*head)->len - 1] = newNode(data);
        if((*head)->next[(*head)->len - 1] == NULL) (*head)->len--;
    }
}

int getLast(Node* head) {
    if (head == NULL) {
        return -1;
    }

    Node* temp = head;
    while(temp && temp->len != 0) {
        temp = temp->next[temp->len - 1];
    }

    return temp? temp->data: -1;
}

void freeNode(Node* head) {
    if (head == NULL) return;

    for (int i = 0; i < head->len; i++) {
        freeNode(head->next[i]);
    }
    free(head->next);
    free(head);
}

int main() {
    Node* head = NULL;

    addToList(&head, 5);
    if( head != NULL)
        addToList(&(head->next[0]), 10);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    if( head != NULL && head->next[0] != NULL)
        addToList(&(head->next[0]->next[0]), 15);

    printf("%d\n", getLast(head));
    if ( head != NULL && head->next[0] != NULL )
        printf("%d\n", getLast(head->next[0]));

    freeNode(head);

    return 0;
}