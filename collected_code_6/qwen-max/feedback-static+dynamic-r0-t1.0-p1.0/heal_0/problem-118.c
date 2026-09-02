#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *data;
    struct ListNode *next;
} ListNode;

ListNode *stringToList(const char *str) {
    if (str == NULL) return NULL;

    ListNode *head = NULL;
    ListNode *current = NULL;
    const char *start = str;

    while (*str) {
        if (*str == ' ') {
            if (start != str) {
                char *item = (char *)malloc((str - start + 1) * sizeof(char));
                if (item == NULL) return NULL;
                strncpy(item, start, str - start);
                item[str - start] = '\0';

                ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
                if (newNode == NULL) {
                    free(item);
                    return NULL;
                }
                newNode->data = item;
                newNode->next = NULL;

                if (head == NULL) {
                    head = newNode;
                    current = head;
                } else {
                    current->next = newNode;
                    current = newNode;
                }
            }
            start = str + 1;
        }
        ++str;
    }

    if (start != str) {
        char *item = (char *)malloc((str - start + 1) * sizeof(char));
        if (item == NULL) return NULL;
        strncpy(item, start, str - start);
        item[str - start] = '\0';

        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        if (newNode == NULL) {
            free(item);
            return NULL;
        }
        newNode->data = item;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            current->next = newNode;
        }
    }

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
    const char *input = "Hello World This is a test";
    ListNode *list = stringToList(input);
    if (list == NULL) {
        fprintf(stderr, "Error in creating list\n");
        return EXIT_FAILURE;
    }
    printList(list);
    freeList(list);
    return EXIT_SUCCESS;
}