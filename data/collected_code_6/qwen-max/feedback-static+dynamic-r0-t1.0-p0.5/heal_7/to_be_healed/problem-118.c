#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *data;
    struct ListNode *next;
} ListNode;

ListNode* createNode(const char *value) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) return NULL;
    newNode->data = strdup(value);
    if (newNode->data == NULL) {
        free(newNode);
        return NULL;
    }
    newNode->next = NULL;
    return newNode;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

ListNode* stringToList(const char *str, const char *delimiter) {
    char *strCopy = strdup(str);
    if (strCopy == NULL) return NULL;
    ListNode *head = NULL;
    ListNode *tail = NULL;
    char *token = strtok(strCopy, delimiter);

    while (token != NULL) {
        ListNode *newNode = createNode(token);
        if (newNode == NULL) {
            free(strCopy);
            while (head != NULL) {
                ListNode *temp = head;
                head = head->next;
                free(temp->data);
                free(temp);
            }
            return NULL;
        }
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        token = strtok(NULL, delimiter);
    }

    free(strCopy);
    return head;
}

void printList(ListNode *head) {
    for (ListNode *current = head; current != NULL; current = current->next)
        printf("%s -> ", current->data);
    printf("NULL\n");
}

void freeList(ListNode *head) {
    while (head) {
        ListNode *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main() {
    const char *input1 = "lists,tuples,strings";
    const char *input2 = "write,a,program";
    const char *input3 = "python,programming";
    const char *delimiter = ",";

    ListNode *list1 = stringToList(input1, delimiter);
    if (list1 == NULL) {
        fprintf(stderr, "Failed to create list from input1\n");
        return 1;
    }
    printList(list1);
    freeList(list1);

    ListNode *list2 = stringToList(input2, delimiter);
    if (list2 == NULL) {
        fprintf(stderr, "Failed to create list from input2\n");
        return 1;
    }
    printList(list2);
    freeList(list2);

    ListNode *list3 = stringToList(input3, delimiter);
    if (list3 == NULL) {
        fprintf(stderr, "Failed to create list from input3\n");
        return 1;
    }
    printList(list3);
    freeList(list3);

    return 0;
}