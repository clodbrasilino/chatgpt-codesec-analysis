#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *data;
    struct ListNode *next;
} ListNode;

ListNode *createNode(char *value) {
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

void freeList(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

ListNode *stringToList(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    ListNode *head = NULL;
    ListNode *tail = NULL;

    const char *start = str;
    while (*start != '\0') {
        while (*start == ' ') {
            start++;
        }

        const char *end = start;
        while (*end != ' ' && *end != '\0') {
            end++;
        }

        if (end > start) {
            ListNode *newNode = createNode(strndup(start, end - start));
            if (newNode == NULL) {
                freeList(head);
                return NULL;
            }
            if (head == NULL) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        start = end;
    }

    return head;
}

int main() {
    const char *input = "  hello   world  C programming  ";
    ListNode *list = stringToList(input);

    if (list == NULL) {
        printf("Failed to create list\n");
        return 1;
    }

    ListNode *current = list;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    freeList(list);
    return 0;
}