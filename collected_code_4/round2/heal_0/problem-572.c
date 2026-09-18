#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *remove_duplicate(node *head, int val) {
    node *ptr = head;
    node *prev_ptr = NULL;

    while(ptr != NULL) {
        if (ptr->data == val) {

            if (prev_ptr == NULL) {
                head = ptr->next;
            } else {
                prev_ptr->next = ptr->next;
            }

            node* tmp = ptr;
            ptr = ptr->next;
            free(tmp);
            continue;
        }
        prev_ptr = ptr;
        ptr = ptr->next;
    }

    return head;
}

node *new_node(int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void print_list(node *head) {
    while (head != NULL) {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main()
{
    int duplicate_number1 = 2, duplicate_number2 = 3;

    node *head = new_node(1);
    head->next = new_node(2);
    head->next->next = new_node(3);
    head->next->next->next = new_node(2);
    head->next->next->next->next = new_node(3);

    printf("Original list: ");
    print_list(head);

    head = remove_duplicate(head, duplicate_number1);
    head = remove_duplicate(head, duplicate_number2);

    printf("After removing duplicates: ");
    print_list(head);

    return 0;
}