#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
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

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void parseLine(Node** head) {
    Node* tail = NULL;
    int c;
    long long num = 0;
    int sign = 1;
    int has_digit = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (c == '-') {
            sign = -1;
        } else if (c >= '0' && c <= '9') {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 4444444444444444444 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:1987,execs:252,op:havoc,rep:8)
             * UBSan: signed integer overflow: 5555555555555555555 * 10 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:10386,execs:1131,op:havoc,rep:4)
             * UBSan: signed integer overflow: 6333333333333333333 * 10 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000000,time:29173,execs:3439,op:havoc,rep:8)
             * UBSan: signed integer overflow: 2222222222222222222 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:5950,execs:678,op:havoc,rep:6)
             */
            num = num * 10 + (c - '0');
            has_digit = 1;
        } else {
            if (has_digit) {
                Node* newNode = createNode((int)(num * sign));
                if (*head == NULL) {
                    *head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
                has_digit = 0;
                num = 0;
                sign = 1;
            }
        }
    }
    
    if (has_digit) {
        Node* newNode = createNode((int)(num * sign));
        if (*head == NULL) {
            *head = newNode;
        } else {
            tail->next = newNode;
        }
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000000,time:25352,execs:2914,op:havoc,rep:3; likely memory-safety defect
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