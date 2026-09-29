#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* append_node(Node* head, int data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) {
        return head;
    }
    
    if (head == NULL) {
        return new_node;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

bool check_common_order(Node* list1, Node* list2) {
    if (list1 == NULL || list2 == NULL) {
        return false;
    }
    
    Node* current1 = list1;
    /* Possible weaknesses found:
     *  Variable 'current2' is assigned a value that is never used. [unreadVariable]
     */
    Node* current2 = list2;
    bool found_common = false;
    int last_common = 0;
    
    while (current1 != NULL) {
        current2 = list2;
        while (current2 != NULL) {
            if (current1->data == current2->data) {
                if (found_common && current1->data <= last_common) {
                    return false;
                }
                found_common = true;
                last_common = current1->data;
                break;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    
    return true;
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    
    list1 = append_node(list1, 1);
    list1 = append_node(list1, 2);
    list1 = append_node(list1, 3);
    list1 = append_node(list1, 4);
    list1 = append_node(list1, 5);
    
    list2 = append_node(list2, 2);
    list2 = append_node(list2, 4);
    list2 = append_node(list2, 6);
    
    if (check_common_order(list1, list2)) {
        printf("Common elements are in the same order\n");
    } else {
        printf("Common elements are not in the same order\n");
    }
    
    free_list(list1);
    free_list(list2);
    
    return 0;
}