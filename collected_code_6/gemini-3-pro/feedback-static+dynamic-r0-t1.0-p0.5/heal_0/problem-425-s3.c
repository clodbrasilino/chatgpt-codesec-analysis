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

int count_sublists_with_element(Sublist* list_of_lists, int target) {
    if (list_of_lists == NULL) {
        return 0;
    }

    int count = 0;
    Sublist* current_sublist = list_of_lists;

    while (current_sublist != NULL) {
        Node* current_node = current_sublist->head;
        while (current_node != NULL) {
            if (current_node->data == target) {
                count++;
                break;
            }
            current_node = current_node->next;
        }
        current_sublist = current_sublist->next;
    }

    return count;
}

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

void free_list_of_lists(Sublist* list_of_lists) {
    Sublist* current_sublist = list_of_lists;
    while (current_sublist != NULL) {
        Node* current_node = current_sublist->head;
        while (current_node != NULL) {
            Node* temp_node = current_node;
            current_node = current_node->next;
            free(temp_node);
        }
        Sublist* temp_sublist = current_sublist;
        current_sublist = current_sublist->next;
        free(temp_sublist);
    }
}

int main(void) {
    Node* n1 = create_node(1);
    n1->next = create_node(2);
    n1->next->next = create_node(3);

    Node* n2 = create_node(4);
    n2->next = create_node(2);

    Node* n3 = create_node(5);
    n3->next = create_node(6);

    Sublist* s1 = create_sublist(n1);
    Sublist* s2 = create_sublist(n2);
    Sublist* s3 = create_sublist(n3);

    s1->next = s2;
    s2->next = s3;

    int target = 2;
    int count = count_sublists_with_element(s1, target);

    printf("%d\n", count);

    free_list_of_lists(s1);

    return 0;
}