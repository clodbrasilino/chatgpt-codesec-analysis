#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

List* create_list_node(Node* head) {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        exit(EXIT_FAILURE);
    }
    new_list->head = head;
    new_list->next = NULL;
    return new_list;
}

void free_node_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void free_list(List* head) {
    List* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free_node_list(temp->head);
        free(temp);
    }
}

Node* copy_node_list(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    Node* new_head = create_node(head->value);
    Node* current = new_head;
    head = head->next;
    while (head != NULL) {
        current->next = create_node(head->value);
        current = current->next;
        head = head->next;
    }
    return new_head;
}

Node* concat_node_lists(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return copy_node_list(list2);
    }
    Node* result = copy_node_list(list1);
    Node* current = result;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = copy_node_list(list2);
    return result;
}

List* zip_lists(List* list1, List* list2) {
    List* dummy = create_list_node(NULL);
    List* tail = dummy;

    while (list1 != NULL && list2 != NULL) {
        Node* zipped_nodes = concat_node_lists(list1->head, list2->head);
        tail->next = create_list_node(zipped_nodes);
        tail = tail->next;
        list1 = list1->next;
        list2 = list2->next;
    }

    while (list1 != NULL) {
        tail->next = create_list_node(copy_node_list(list1->head));
        tail = tail->next;
        list1 = list1->next;
    }

    while (list2 != NULL) {
        tail->next = create_list_node(copy_node_list(list2->head));
        tail = tail->next;
        list2 = list2->next;
    }

    List* result = dummy->next;
    free(dummy);
    return result;
}

void print_list(List* list) {
    while (list != NULL) {
        Node* current = list->head;
        printf("[");
        while (current != NULL) {
            printf("%d", current->value);
            if (current->next != NULL) {
                printf(", ");
            }
            current = current->next;
        }
        printf("]");
        if (list->next != NULL) {
            printf(" -> ");
        }
        list = list->next;
    }
    printf("\n");
}

int main(void) {
    Node* n1 = create_node(1);
    n1->next = create_node(2);
    List* l1 = create_list_node(n1);
    
    Node* n2 = create_node(3);
    l1->next = create_list_node(n2);

    Node* n3 = create_node(4);
    List* l2 = create_list_node(n3);
    
    Node* n4 = create_node(5);
    n4->next = create_node(6);
    l2->next = create_list_node(n4);

    List* zipped = zip_lists(l1, l2);

    print_list(zipped);

    free_list(l1);
    free_list(l2);
    free_list(zipped);

    return 0;
}