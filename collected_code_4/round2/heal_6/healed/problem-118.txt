#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
    struct node *next;
} node;

node * convert_to_list(const char *str) {
    node * head = NULL;
    node * temp = NULL;
    node * prev = NULL;
    int i;
    
    if (str != NULL) {
        for(i = 0; str[i] != '\0'; i++) {
            temp = (node *) malloc(sizeof(node));

            if(temp == NULL) {
                temp = head;
                while(temp != NULL) {
                    head = temp->next;
                    free(temp);
                    temp = head;
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
    printf("\n");
}

int main() {
    char str[] = "hello";
    node * head = convert_to_list(str);

    if(head != NULL) {
        print_list(head);

        node * temp = head;
        while(temp != NULL) {
            head = temp->next;
            free(temp);
            temp = head;
        }
    } else {
        printf("Out of memory!\n");
    }

    return 0;
}