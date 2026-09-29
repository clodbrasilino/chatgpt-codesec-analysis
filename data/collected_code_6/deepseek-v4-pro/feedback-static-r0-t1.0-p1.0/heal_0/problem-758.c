#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

typedef struct ListNode {
    List* list;
    struct ListNode* next;
} ListNode;

int lists_equal(List* a, List* b) {
    Node* na = a->head;
    Node* nb = b->head;
    while (na != NULL && nb != NULL) {
        if (na->data != nb->data) return 0;
        na = na->next;
        nb = nb->next;
    }
    return na == NULL && nb == NULL;
}

int count_unique_lists(ListNode* list_of_lists) {
    int unique_count = 0;
    ListNode* current = list_of_lists;
    while (current != NULL) {
        int is_unique = 1;
        ListNode* checker = list_of_lists;
        while (checker != current) {
            if (lists_equal(checker->list, current->list)) {
                is_unique = 0;
                break;
            }
            checker = checker->next;
        }
        if (is_unique) unique_count++;
        current = current->next;
    }
    return unique_count;
}

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) exit(EXIT_FAILURE);
    node->data = data;
    node->next = NULL;
    return node;
}

void list_append(List* list, int data) {
    Node* node = create_node(data);
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) current = current->next;
        current->next = node;
    }
}

void free_list(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    free(list);
}

int main(void) {
    List* l1 = (List*)malloc(sizeof(List));
    List* l2 = (List*)malloc(sizeof(List));
    List* l3 = (List*)malloc(sizeof(List));
    if (l1 == NULL || l2 == NULL || l3 == NULL) exit(EXIT_FAILURE);
    l1->head = NULL;
    l2->head = NULL;
    l3->head = NULL;

    list_append(l1, 1);
    list_append(l1, 2);
    list_append(l1, 3);

    list_append(l2, 1);
    list_append(l2, 2);
    list_append(l2, 3);

    list_append(l3, 4);
    list_append(l3, 5);

    ListNode* n1 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n2 = (ListNode*)malloc(sizeof(ListNode));
    ListNode* n3 = (ListNode*)malloc(sizeof(ListNode));
    if (n1 == NULL || n2 == NULL || n3 == NULL) exit(EXIT_FAILURE);

    n1->list = l1;
    n1->next = n2;
    n2->list = l2;
    n2->next = n3;
    n3->list = l3;
    n3->next = NULL;

    int unique = count_unique_lists(n1);

    free(n1);
    free(n2);
    free(n3);
    free_list(l1);
    free_list(l2);
    free_list(l3);

    return unique == 2 ? 0 : 1;
}