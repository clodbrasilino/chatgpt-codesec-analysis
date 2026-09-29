#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct ListOfLists {
    Node *sublist;
    struct ListOfLists *next;
} ListOfLists;

int list_length(Node *head) {
    int length = 0;
    Node *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

Node *find_min_length_sublist(ListOfLists *head) {
    if (head == NULL) {
        return NULL;
    }

    Node *min_sublist = NULL;
    int min_len = INT_MAX;

    ListOfLists *current = head;
    while (current != NULL) {
        int current_len = list_length(current->sublist);
        if (current_len < min_len) {
            min_len = current_len;
            min_sublist = current->sublist;
        }
        current = current->next;
    }

    return min_sublist;
}

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

ListOfLists *create_list_of_lists(Node *sublist) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        return NULL;
    }
    lol->sublist = sublist;
    lol->next = NULL;
    return lol;
}

void free_node_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void free_list_of_lists(ListOfLists *head) {
    ListOfLists *current = head;
    while (current != NULL) {
        ListOfLists *next = current->next;
        free_node_list(current->sublist);
        free(current);
        current = next;
    }
}

int main() {
    Node *n1 = create_node(1);
    Node *n2 = create_node(2);
    Node *n3 = create_node(3);
    Node *n4 = create_node(4);

    if (n1 == NULL || n2 == NULL || n3 == NULL || n4 == NULL) {
        free_node_list(n1);
        free_node_list(n2);
        free_node_list(n3);
        free_node_list(n4);
        return EXIT_FAILURE;
    }

    n1->next = n2;

    ListOfLists *l1 = create_list_of_lists(n1);
    ListOfLists *l2 = create_list_of_lists(n3);
    ListOfLists *l3 = create_list_of_lists(n4);

    if (l1 == NULL || l2 == NULL || l3 == NULL) {
        free_list_of_lists(l1);
        free_list_of_lists(l2);
        free_list_of_lists(l3);
        return EXIT_FAILURE;
    }

    l1->next = l2;
    l2->next = l3;

    const Node *min_sublist = find_min_length_sublist(l1);
    if (min_sublist != NULL) {
        printf("Minimum length sublist starts with: %d\n", min_sublist->data);
    } else {
        printf("Minimum length sublist is empty or not found.\n");
    }

    free_list_of_lists(l1);

    return EXIT_SUCCESS;
}