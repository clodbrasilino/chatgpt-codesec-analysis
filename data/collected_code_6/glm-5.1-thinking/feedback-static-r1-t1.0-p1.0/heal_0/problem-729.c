#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int append_node(Node **head, int data) {
    Node *node = create_node(data);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
    } else {
        Node *curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
    }
    return 0;
}

Node *add_lists(Node *l1, Node *l2) {
    Node dummy;
    dummy.next = NULL;
    Node *tail = &dummy;

    while (l1 != NULL || l2 != NULL) {
        int sum = 0;
        if (l1 != NULL) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->data;
            l2 = l2->next;
        }

        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            Node *curr = dummy.next;
            while (curr != NULL) {
                Node *temp = curr;
                curr = curr->next;
                free(temp);
            }
            return NULL;
        }
        new_node->data = sum;
        new_node->next = NULL;
        tail->next = new_node;
        tail = new_node;
    }
    return dummy.next;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
}

void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;

    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);

    append_node(&list2, 4);
    append_node(&list2, 5);
    append_node(&list2, 6);
    append_node(&list2, 7);

    Node *result = add_lists(list1, list2);
    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}