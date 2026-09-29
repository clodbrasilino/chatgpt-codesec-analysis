#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

int list_cmp(Node *a, Node *b) {
    while (a && b) {
        if (a->data != b->data) {
            return 0;
        }
        a = a->next;
        b = b->next;
    }
    return a == NULL && b == NULL;
}

void insert_sorted(List **lists, List *insert_list, int size) {
    if (*lists == NULL || list_cmp(insert_list->head, (*lists)->head)) {
        /* Possible weaknesses found:
         *  no member named 'next' in 'struct List'
         *  'List' has no member named 'next'
         */
        insert_list->next = *lists;
        *lists = insert_list;
    } else {
        List *current = *lists;
        /* Possible weaknesses found:
         *  no member named 'next' in 'struct List'
         *  'List' has no member named 'next'
         */
        while (current->next && !list_cmp(insert_list->head, current->next->head)) {
            /* Possible weaknesses found:
             *  no member named 'next' in 'struct List'
             *  'List' has no member named 'next'
             */
            current = current->next;
        }
        if (!list_cmp(insert_list->head, current->head)) {
            /* Possible weaknesses found:
             *  no member named 'next' in 'struct List'
             *  'List' has no member named 'next'
             */
            insert_list->next = current->next;
            /* Possible weaknesses found:
             *  no member named 'next' in 'struct List'
             *  'List' has no member named 'next'
             */
            current->next = insert_list;
        }
    }
}

List* remove_duplicates(List *lists) {
    if (lists == NULL) {
        return NULL;
    }

    List *result = NULL;
    while (lists) {
        List *current = lists;
        /* Possible weaknesses found:
         *  no member named 'next' in 'struct List'
         *  'List' has no member named 'next'
         */
        lists = lists->next;
        if (result == NULL || !list_cmp(current->head, result->head)) {
            insert_sorted(&result, current, 0);
        } else {
            while (current->head) {
                Node *temp = current->head;
                current->head = current->head->next;
                free(temp);
            }
            free(current);
        }
    }
    return result;
}

Node* create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

List* create_list() {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    /* Possible weaknesses found:
     *  no member named 'next' in 'struct List'
     *  'List' has no member named 'next'
     */
    list->next = NULL;
    return list;
}

void add_to_list(List *list, int data) {
    Node *new_node = create_node(data);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_list(List *list) {
    Node *current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_lists(List *lists) {
    while (lists) {
        List *temp = lists;
        /* Possible weaknesses found:
         *  no member named 'next' in 'struct List'
         *  'List' has no member named 'next'
         */
        lists = lists->next;
        while (temp->head) {
            Node *del_node = temp->head;
            temp->head = temp->head->next;
            free(del_node);
        }
        free(temp);
    }
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'lists' can be declared as pointer to const [constVariablePointer]
     *  Variable 'lists' is assigned a value that is never used. [unreadVariable]
     */
    List *lists = create_list();
    List *l1 = create_list();
    add_to_list(l1, 1);
    add_to_list(l1, 2);
    add_to_list(l1, 3);

    List *l2 = create_list();
    add_to_list(l2, 4);
    add_to_list(l2, 5);

    List *l3 = create_list();
    add_to_list(l3, 1);
    add_to_list(l3, 2);
    add_to_list(l3, 3);

    List *l4 = create_list();
    add_to_list(l4, 6);

    /* Possible weaknesses found:
     *  no member named 'next' in 'struct List'
     *  'List' has no member named 'next'
     */
    l1->next = l2;
    /* Possible weaknesses found:
     *  no member named 'next' in 'struct List'
     *  'List' has no member named 'next'
     */
    l2->next = l3;
    /* Possible weaknesses found:
     *  no member named 'next' in 'struct List'
     *  'List' has no member named 'next'
     */
    l3->next = l4;

    List *result = remove_duplicates(l1);

    while (result) {
        print_list(result);
        /* Possible weaknesses found:
         *  no member named 'next' in 'struct List'
         *  'List' has no member named 'next'
         */
        result = result->next;
    }

    free_lists(l1);

    return 0;
}