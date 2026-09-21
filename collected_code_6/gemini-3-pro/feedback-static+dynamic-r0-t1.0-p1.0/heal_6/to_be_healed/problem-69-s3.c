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
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            if (in_num) {
                append(head, (int)(num * sign));
            }
            break;
        } else if (ch == '-') {
            sign = -1;
        } else if (ch >= '0' && ch <= '9') {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 6666666666666666666 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:5649,execs:2883,op:havoc,rep:4)
             * UBSan: signed integer overflow: 999999999999999999 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:3252,execs:1682,op:havoc,rep:3)
             * UBSan: signed integer overflow: 5555555555555555555 * 10 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000045,time:27908,execs:14287,op:havoc,rep:2)
             * UBSan: signed integer overflow: 5111111111111111111 * 10 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000015,time:26373,execs:13558,op:havoc,rep:6)
             * UBSan: signed integer overflow: 1111111111191111111 * 10 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000015,time:26365,execs:13555,op:havoc,rep:8)
             */
            num = num * 10 + (ch - '0');
            in_num = true;
        } else if (ch == ' ' || ch == '\t') {
            if (in_num) {
                append(head, (int)(num * sign));
                in_num = false;
                num = 0;
                sign = 1;
            }
        }
    }
    
    if (ch == EOF && in_num) {
        append(head, (int)(num * sign));
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000005,sig:06,src:000045,time:50653,execs:22095,op:havoc,rep:2; likely memory-safety defect
  */

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