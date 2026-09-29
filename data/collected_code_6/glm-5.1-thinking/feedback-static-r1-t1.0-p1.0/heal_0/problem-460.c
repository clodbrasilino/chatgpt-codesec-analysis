#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *sublist;
    struct List *next;
} List;

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

List *create_list(Node *sublist) {
    List *list = malloc(sizeof(List));
    if (!list) {
        exit(EXIT_FAILURE);
    }
    list->sublist = sublist;
    list->next = NULL;
    return list;
}

Node *get_first_elements(List *lists) {
    Node *head = NULL;
    Node *tail = NULL;
    
    while (lists != NULL) {
        if (lists->sublist != NULL) {
            Node *new_node = malloc(sizeof(Node));
            if (!new_node) {
                while (head != NULL) {
                    Node *temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(EXIT_FAILURE);
            }
            new_node->data = lists->sublist->data;
            new_node->next = NULL;
            
            if (tail == NULL) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
        lists = lists->next;
    }
    
    return head;
}

void free_sublists(List *lists) {
    while (lists != NULL) {
        Node *sub = lists->sublist;
        while (sub != NULL) {
            Node *temp = sub;
            sub = sub->next;
            free(temp);
        }
        List *temp_list = lists;
        lists = lists->next;
        free(temp_list);
    }
}

void free_result(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node *sub1 = create_node(1);
    sub1->next = create_node(2);
    sub1->next->next = create_node(3);

    Node *sub2 = create_node(4);
    sub2->next = create_node(5);

    Node *sub3 = create_node(6);
    sub3->next = create_node(7);
    sub3->next->next = create_node(8);

    List *lists = create_list(sub1);
    lists->next = create_list(sub2);
    lists->next->next = create_list(sub3);

    Node *result = get_first_elements(lists);

    Node *curr = result;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    free_result(result);
    free_sublists(lists);

    return 0;
}