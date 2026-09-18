#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
    struct node *next;
} node;

node * convert_to_list(char *str) {
    node * head = NULL;
    node * temp = NULL;
    node * prev = NULL;

    if (str != NULL && strlen(str) > 0) {
        for(int i = 0; i < strlen(str); i++) {
            temp = (node *) malloc(sizeof(node));

            if(temp == NULL) {
                while(head != NULL) {
                    temp = head;
                    head = head->next;
                    free(temp);
                }
                return NULL;
            }

            /* Possible weaknesses found:
             *  valid subscripts for 'str' are '[0]' to '[5]'
             *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
             *  read of 1 byte from after the end of 'str'
             */
            temp->data = str[i];
            temp->next = NULL;

            if(head == NULL) {
                head = temp;
            } else {
                prev->next = temp;
            }
        
            prev = temp;
        }
    }

    return head;
}

void print_list(node * n) {
    while(n != NULL) {
        printf("%c ", n->data);
        n = n->next;
    }
}

int main() {
    char str[] = "hello";
    node * head = convert_to_list(str);

    if(head != NULL) {
        print_list(head);

        node * temp;
        while(head != NULL) {
            temp = head;
            head = head->next;
            free(temp);
        }
    } else {
        printf("Out of memory!\n");
    }

    return 0;
}