#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Sublist {
    Node* head;
    struct Sublist* next;
} Sublist;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Sublist* create_sublist(Node* head) {
    Sublist* new_sublist = (Sublist*)malloc(sizeof(Sublist));
    if (new_sublist == NULL) {
        exit(EXIT_FAILURE);
    }
    new_sublist->head = head;
    new_sublist->next = NULL;
    return new_sublist;
}

Sublist* pack_duplicates(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Sublist* sub_head = NULL;
    /* Possible weaknesses found:
     *  Assignment 'sub_tail=NULL', assigned value is 0
     */
    Sublist* sub_tail = NULL;
    
    Node* current = head;
    while (current != NULL) {
        Node* sublist_node_head = create_node(current->data);
        Node* sublist_node_tail = sublist_node_head;
        
        while (current->next != NULL && current->data == current->next->data) {
            current = current->next;
            sublist_node_tail->next = create_node(current->data);
            sublist_node_tail = sublist_node_tail->next;
        }
        
        Sublist* new_sublist = create_sublist(sublist_node_head);
        if (sub_head == NULL) {
            sub_head = new_sublist;
            sub_tail = new_sublist;
        } else {
            /* Possible weaknesses found:
             *  Possible null pointer dereference: sub_tail [nullPointer]
             *  Null pointer dereference
             */
            sub_tail->next = new_sublist;
            /* Possible weaknesses found:
             *  Possible null pointer dereference: sub_tail [nullPointer]
             *  Null pointer dereference
             */
            sub_tail = sub_tail->next;
        }
        
        current = current->next;
    }
    
    return sub_head;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_sublists(Sublist* head) {
    while (head != NULL) {
        Sublist* temp = head;
        head = head->next;
        free_list(temp->head);
        free(temp);
    }
}

void print_sublists(Sublist* head) {
    printf("[");
    Sublist* current = head;
    while (current != NULL) {
        printf("[");
        Node* node_current = current->head;
        while (node_current != NULL) {
            printf("%d", node_current->data);
            if (node_current->next != NULL) {
                printf(", ");
            }
            node_current = node_current->next;
        }
        printf("]");
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

int main(void) {
    int arr[] = {1, 1, 1, 2, 3, 3, 4, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Node* head = NULL;
    /* Possible weaknesses found:
     *  Assignment 'tail=NULL', assigned value is 0
     */
    Node* tail = NULL;
    
    for (int i = 0; i < n; i++) {
        Node* new_node = create_node(arr[i]);
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            /* Possible weaknesses found:
             *  Null pointer dereference
             *  Possible null pointer dereference: tail [nullPointer]
             */
            tail->next = new_node;
            /* Possible weaknesses found:
             *  Null pointer dereference
             *  Possible null pointer dereference: tail [nullPointer]
             */
            tail = tail->next;
        }
    }
    
    Sublist* packed = pack_duplicates(head);
    print_sublists(packed);
    
    free_list(head);
    free_sublists(packed);
    
    return EXIT_SUCCESS;
}