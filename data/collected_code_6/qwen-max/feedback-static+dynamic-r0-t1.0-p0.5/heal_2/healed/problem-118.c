#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *data;
    struct ListNode *next;
} ListNode;

ListNode* createNode(char *value) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = strdup(value);
    if (newNode->data == NULL) {
        free(newNode);
        return NULL;
    }
    newNode->next = NULL;
    return newNode;
}

ListNode* stringToList(const char *str, char delimiter) {
    char *strCopy = strdup(str);
    if (strCopy == NULL) {
        return NULL;
    }
    ListNode *head = NULL;
    ListNode *tail = NULL;
    char *token = strtok(strCopy, &delimiter);

    while (token != NULL) {
        ListNode *newNode = createNode(token);
        if (newNode == NULL) {
            free(strCopy);
            return NULL;
        }
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        token = strtok(NULL, &delimiter);
    }

    free(strCopy);
    return head;
}

void printList(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

int main() {
    const char *input = "apple,banana,orange,grape";
    char delimiter = ',';
    ListNode *list = stringToList(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }
    printList(list);
    freeList(list);
    return 0;
}