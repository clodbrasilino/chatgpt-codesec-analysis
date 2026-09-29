#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

bool isSublist(Node* list, Node* sublist) {
    if (sublist == NULL) {
        return true;
    }
    if (list == NULL) {
        return false;
    }

    Node* currentList = list;
    
    while (currentList != NULL) {
        Node* ptr1 = currentList;
        Node* ptr2 = sublist;
        
        while (ptr1 != NULL && ptr2 != NULL && ptr1->data == ptr2->data) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        
        if (ptr2 == NULL) {
            return true;
        }
        
        currentList = currentList->next;
    }
    
    return false;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void append(Node** head, int data) {
    if (head == NULL) return;
    
    Node* newNode = createNode(data);
    if (newNode == NULL) return;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void parseLine(Node** head) {
    int ch;
    long long num = 0;
    int sign = 1;
    bool in_num = false;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (ch == '-') {
            sign = -1;
        } else if (ch >= '0' && ch <= '9') {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 7777777777777777777 * 10 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000000,time:10056,execs:4286,op:havoc,rep:13)
             * UBSan: signed integer overflow: 6666666666666666666 * 10 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:5081,execs:2224,op:havoc,rep:15)
             * UBSan: signed integer overflow: 8888888888888888888 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:671,execs:334,op:havoc,rep:14)
             * UBSan: signed integer overflow: 3333333333333333333 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:742,execs:367,op:havoc,rep:6)
             * UBSan: signed integer overflow: 7999999999999999999 * 10 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000000,time:19006,execs:8249,op:havoc,rep:8)
             */
            num = num * 10 + (ch - '0');
            in_num = true;
        } else {
            if (in_num) {
                append(head, (int)(num * sign));
                in_num = false;
                num = 0;
                sign = 1;
            }
        }
    }
    if (in_num) {
        append(head, (int)(num * sign));
    }
}

int main(void) {
    Node* list = NULL;
    Node* sublist = NULL;

    parseLine(&list);
    parseLine(&sublist);

    if (isSublist(list, sublist)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    freeList(list);
    freeList(sublist);

    return 0;
}