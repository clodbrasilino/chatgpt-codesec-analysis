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
    int len;

    if (str != NULL) {
        len = strlen(str);
        for(int i = 0; i < len; i++) {
            temp = (node *) malloc(sizeof(node));
            
            if(temp == NULL) {
                node* cleanup = head;
                while(cleanup != NULL) {
                    temp = cleanup;
                    cleanup = cleanup->next;
                    free(temp);
                }
                return NULL;
            }
            
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