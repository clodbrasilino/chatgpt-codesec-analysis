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
    int num = 0;
    int sign = 1;
    bool in_num = false;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            if (in_num) {
                append(head, num * sign);
            }
            break;
        } else if (ch == '-') {
            sign = -1;
        } else if (ch >= '0' && ch <= '9') {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 711111111 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:1472,execs:823,op:havoc,rep:10)
             * UBSan: signed integer overflow: 777777777 * 10 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000000,time:2287,execs:1246,op:havoc,rep:15)
             * UBSan: signed integer overflow: 350333333 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:2110,execs:1153,op:havoc,rep:12)
             * UBSan: signed integer overflow: 333333333 * 10 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000000,time:2612,execs:1413,op:havoc,rep:9)
             * UBSan: signed integer overflow: 999999999 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:590,execs:343,op:havoc,rep:5)
             * UBSan: signed integer overflow: 1111111111 * 10 cannot be represented in type 'int' (AFL crash: id:000005,sig:06,src:000000,time:2817,execs:1519,op:havoc,rep:15)
             */
            num = num * 10 + (ch - '0');
            in_num = true;
        } else if (ch == ' ' || ch == '\t') {
            if (in_num) {
                append(head, num * sign);
                in_num = false;
                num = 0;
                sign = 1;
            }
        }
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000006,sig:06,src:000000,time:5430,execs:2915,op:havoc,rep:13; likely memory-safety defect
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