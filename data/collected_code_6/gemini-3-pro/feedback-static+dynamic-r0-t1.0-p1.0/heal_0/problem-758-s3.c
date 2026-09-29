#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListList {
    Node* head;
    struct ListList* next;
} ListList;

bool are_lists_equal(Node* list1, Node* list2) {
    while (list1 != NULL && list2 != NULL) {
        if (list1->data != list2->data) {
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return (list1 == NULL && list2 == NULL);
}

int count_unique_lists(ListList* head) {
    if (head == NULL) {
        return 0;
    }

    int unique_count = 0;
    ListList* current = head;

    while (current != NULL) {
        bool is_unique = true;
        ListList* checker = head;

        while (checker != current) {
            if (are_lists_equal(current->head, checker->head)) {
                is_unique = false;
                break;
            }
            checker = checker->next;
        }

        if (is_unique) {
            unique_count++;
        }
        current = current->next;
    }

    return unique_count;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

ListList* create_list_list(Node* head) {
    ListList* new_list = (ListList*)malloc(sizeof(ListList));
    if (new_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_list->head = head;
    new_list->next = NULL;
    return new_list;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_list_list(ListList* head) {
    while (head != NULL) {
        ListList* temp = head;
        head = head->next;
        free_list(temp->head);
        free(temp);
    }
}

int main(void) {
    Node* list1 = create_node(1);
    list1->next = create_node(2);
    list1->next->next = create_node(3);

    Node* list2 = create_node(4);
    list2->next = create_node(5);

    Node* list3 = create_node(1);
    list3->next = create_node(2);
    list3->next->next = create_node(3);

    Node* list4 = create_node(6);

    ListList* ll_head = create_list_list(list1);
    ll_head->next = create_list_list(list2);
    ll_head->next->next = create_list_list(list3);
    ll_head->next->next->next = create_list_list(list4);

    int unique_count = count_unique_lists(ll_head);
    printf("%d\n", unique_count);

    free_list_list(ll_head);

    return 0;
}