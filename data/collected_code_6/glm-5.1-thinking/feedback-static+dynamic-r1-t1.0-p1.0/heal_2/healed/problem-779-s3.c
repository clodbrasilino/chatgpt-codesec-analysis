#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct OuterNode {
    Node *list;
    struct OuterNode *next;
} OuterNode;

int list_equal(Node *a, Node *b) {
    Node *pa = a;
    Node *pb = b;
    while (pa != NULL && pb != NULL) {
        if (pa->value != pb->value) {
            return 0;
        }
        pa = pa->next;
        pb = pb->next;
    }
    return pa == NULL && pb == NULL;
}

int count_unique_lists(OuterNode *head) {
    int count = 0;
    OuterNode *unique_head = NULL;
    OuterNode *curr = head;
    while (curr != NULL) {
        int is_duplicate = 0;
        OuterNode *u_curr = unique_head;
        while (u_curr != NULL) {
            if (list_equal(curr->list, u_curr->list)) {
                is_duplicate = 1;
                break;
            }
            u_curr = u_curr->next;
        }
        if (!is_duplicate) {
            count++;
            OuterNode *new_unique = (OuterNode *)malloc(sizeof(OuterNode));
            if (new_unique == NULL) {
                OuterNode *temp = unique_head;
                while (temp != NULL) {
                    OuterNode *next = temp->next;
                    free(temp);
                    temp = next;
                }
                return -1;
            }
            new_unique->list = curr->list;
            new_unique->next = unique_head;
            unique_head = new_unique;
        }
        curr = curr->next;
    }
    OuterNode *temp = unique_head;
    while (temp != NULL) {
        OuterNode *next = temp->next;
        free(temp);
        temp = next;
    }
    return count;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
}

void free_outer_list(OuterNode *head) {
    OuterNode *curr = head;
    while (curr != NULL) {
        OuterNode *next = curr->next;
        free_list(curr->list);
        free(curr);
        curr = next;
    }
}

Node *create_list(const int *arr, int size) {
    Node *head = NULL;
    Node *tail = NULL;
    for (int i = 0; i < size; i++) {
        Node *n = (Node *)malloc(sizeof(Node));
        if (n == NULL) {
            free_list(head);
            return NULL;
        }
        n->value = arr[i];
        n->next = NULL;
        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }
    return head;
}

OuterNode *create_outer_list(Node **lists, int size) {
    OuterNode *head = NULL;
    OuterNode *tail = NULL;
    for (int i = 0; i < size; i++) {
        OuterNode *n = (OuterNode *)malloc(sizeof(OuterNode));
        if (n == NULL) {
            OuterNode *curr = head;
            while (curr != NULL) {
                OuterNode *next = curr->next;
                free_list(curr->list);
                free(curr);
                curr = next;
            }
            for (int j = i; j < size; j++) {
                free_list(lists[j]);
            }
            return NULL;
        }
        n->list = lists[i];
        n->next = NULL;
        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }
    return head;
}

int main(void) {
    const int arr1[] = {1, 2, 3};
    const int arr2[] = {1, 2, 3};
    const int arr3[] = {4, 5};
    const int arr4[] = {1, 2};

    Node *l1 = create_list(arr1, 3);
    Node *l2 = create_list(arr2, 3);
    Node *l3 = create_list(arr3, 2);
    Node *l4 = create_list(arr4, 2);

    if (l1 == NULL || l2 == NULL || l3 == NULL || l4 == NULL) {
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        return 1;
    }

    Node *lists[] = {l1, l2, l3, l4};
    OuterNode *outer = create_outer_list(lists, 4);

    if (outer == NULL) {
        return 1;
    }

    int unique_count = count_unique_lists(outer);
    printf("%d\n", unique_count);

    free_outer_list(outer);

    return 0;
}