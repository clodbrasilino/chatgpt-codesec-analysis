#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *next;
} List;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List *create_list(void) {
    List *new_list = (List *)malloc(sizeof(List));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->next = NULL;
    return new_list;
}

void free_node_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void free_list_of_lists(List *head) {
    List *current = head;
    while (current != NULL) {
        List *temp = current;
        free_node_list(current->head);
        current = current->next;
        free(temp);
    }
}

int lists_equal(Node *a, Node *b) {
    Node *current_a = a;
    Node *current_b = b;
    
    while (current_a != NULL && current_b != NULL) {
        if (current_a->data != current_b->data) {
            return 0;
        }
        current_a = current_a->next;
        current_b = current_b->next;
    }
    
    return current_a == NULL && current_b == NULL;
}

List *remove_duplicates(List *head) {
    if (head == NULL) {
        return NULL;
    }
    
    List *current = head;
    
    while (current != NULL) {
        List *runner = current;
        
        while (runner->next != NULL) {
            if (lists_equal(current->head, runner->next->head)) {
                List *duplicate = runner->next;
                runner->next = duplicate->next;
                free_node_list(duplicate->head);
                free(duplicate);
            } else {
                runner = runner->next;
            }
        }
        
        current = current->next;
    }
    
    return head;
}

void print_list_of_lists(List *head) {
    List *current = head;
    while (current != NULL) {
        Node *node = current->head;
        printf("[");
        while (node != NULL) {
            printf("%d", node->data);
            if (node->next != NULL) {
                printf(", ");
            }
            node = node->next;
        }
        printf("]");
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List *list_head = create_list();
    if (list_head == NULL) {
        return 1;
    }
    
    Node *n1 = create_node(1);
    Node *n2 = create_node(2);
    Node *n3 = create_node(3);
    if (n1 == NULL || n2 == NULL || n3 == NULL) {
        free_node_list(n1);
        free_node_list(n2);
        free_node_list(n3);
        free(list_head);
        return 1;
    }
    n1->next = n2;
    n2->next = n3;
    list_head->head = n1;
    
    List *list2 = create_list();
    if (list2 == NULL) {
        free_list_of_lists(list_head);
        return 1;
    }
    Node *n4 = create_node(4);
    Node *n5 = create_node(5);
    if (n4 == NULL || n5 == NULL) {
        free_node_list(n4);
        free_node_list(n5);
        free(list2);
        free_list_of_lists(list_head);
        return 1;
    }
    n4->next = n5;
    list2->head = n4;
    list_head->next = list2;
    
    List *list3 = create_list();
    if (list3 == NULL) {
        free_list_of_lists(list_head);
        return 1;
    }
    Node *n6 = create_node(1);
    Node *n7 = create_node(2);
    Node *n8 = create_node(3);
    if (n6 == NULL || n7 == NULL || n8 == NULL) {
        free_node_list(n6);
        free_node_list(n7);
        free_node_list(n8);
        free(list3);
        free_list_of_lists(list_head);
        return 1;
    }
    n6->next = n7;
    n7->next = n8;
    list3->head = n6;
    list2->next = list3;
    
    List *list4 = create_list();
    if (list4 == NULL) {
        free_list_of_lists(list_head);
        return 1;
    }
    Node *n9 = create_node(4);
    Node *n10 = create_node(5);
    if (n9 == NULL || n10 == NULL) {
        free_node_list(n9);
        free_node_list(n10);
        free(list4);
        free_list_of_lists(list_head);
        return 1;
    }
    n9->next = n10;
    list4->head = n9;
    list3->next = list4;
    
    printf("Original list of lists:\n");
    print_list_of_lists(list_head);
    
    list_head = remove_duplicates(list_head);
    
    printf("After removing duplicates:\n");
    print_list_of_lists(list_head);
    
    free_list_of_lists(list_head);
    
    return 0;
}