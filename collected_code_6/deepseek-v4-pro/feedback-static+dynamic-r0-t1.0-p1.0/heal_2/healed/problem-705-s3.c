#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int length;
    struct List *next;
} List;

Node *create_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

List *create_list(const int *values, int count) {
    List *list = (List *)malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->length = 0;
    list->next = NULL;
    for (int i = count - 1; i >= 0; i--) {
        Node *node = create_node(values[i]);
        if (!node) {
            Node *current = list->head;
            while (current) {
                Node *temp = current;
                current = current->next;
                free(temp);
            }
            free(list);
            return NULL;
        }
        node->next = list->head;
        list->head = node;
        list->length++;
    }
    return list;
}

int compare_lists(List *a, List *b) {
    if (a->length != b->length) {
        return a->length - b->length;
    }
    Node *na = a->head;
    Node *nb = b->head;
    while (na && nb) {
        if (na->value != nb->value) {
            return na->value - nb->value;
        }
        na = na->next;
        nb = nb->next;
    }
    return 0;
}

List *merge_lists(List *a, List *b) {
    List *result = NULL;
    List **tail = &result;
    while (a && b) {
        if (compare_lists(a, b) <= 0) {
            *tail = a;
            a = a->next;
        } else {
            *tail = b;
            b = b->next;
        }
        tail = &((*tail)->next);
    }
    if (a) {
        *tail = a;
    }
    if (b) {
        *tail = b;
    }
    return result;
}

void split_list(List *source, List **front, List **back) {
    List *slow = source;
    List *fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void sort_lists(List **list_ptr) {
    List *head = *list_ptr;
    if (!head || !head->next) {
        return;
    }
    List *a = NULL;
    List *b = NULL;
    split_list(head, &a, &b);
    sort_lists(&a);
    sort_lists(&b);
    *list_ptr = merge_lists(a, b);
}

void free_list(List *list) {
    while (list) {
        List *next_list = list->next;
        Node *current = list->head;
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        free(list);
        list = next_list;
    }
}

void print_lists(List *list) {
    while (list) {
        Node *current = list->head;
        while (current) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("(len=%d)\n", list->length);
        list = list->next;
    }
}

int main(void) {
    const int vals1[] = {3, 1, 2};
    const int vals2[] = {1, 2};
    const int vals3[] = {3, 1, 2, 0};
    const int vals4[] = {5, 4};
    
    List *list1 = create_list(vals1, 3);
    List *list2 = create_list(vals2, 2);
    List *list3 = create_list(vals3, 4);
    List *list4 = create_list(vals4, 2);
    
    if (!list1 || !list2 || !list3 || !list4) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        free_list(list4);
        return 1;
    }
    
    list1->next = list2;
    list2->next = list3;
    list3->next = list4;
    
    List *head = list1;
    sort_lists(&head);
    print_lists(head);
    free_list(head);
    
    return 0;
}