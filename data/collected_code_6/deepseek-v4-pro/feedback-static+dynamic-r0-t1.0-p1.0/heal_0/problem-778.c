#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Sublist {
    int *items;
    int count;
    struct Sublist *next;
} Sublist;

Sublist *pack_duplicates(Node *head) {
    if (head == NULL) {
        return NULL;
    }

    Sublist *result = NULL;
    Sublist *tail = NULL;
    Node *current = head;

    while (current != NULL) {
        int value = current->data;
        int count = 0;
        Node *temp = current;

        while (temp != NULL && temp->data == value) {
            count++;
            temp = temp->next;
        }

        Sublist *new_sublist = (Sublist *)malloc(sizeof(Sublist));
        if (new_sublist == NULL) {
            Sublist *cleanup = result;
            while (cleanup != NULL) {
                Sublist *next = cleanup->next;
                free(cleanup->items);
                free(cleanup);
                cleanup = next;
            }
            return NULL;
        }

        new_sublist->items = (int *)malloc(sizeof(int) * count);
        if (new_sublist->items == NULL) {
            free(new_sublist);
            Sublist *cleanup = result;
            while (cleanup != NULL) {
                Sublist *next = cleanup->next;
                free(cleanup->items);
                free(cleanup);
                cleanup = next;
            }
            return NULL;
        }

        for (int i = 0; i < count; i++) {
            new_sublist->items[i] = value;
        }
        new_sublist->count = count;
        new_sublist->next = NULL;

        if (result == NULL) {
            result = new_sublist;
            tail = new_sublist;
        } else {
            tail->next = new_sublist;
            tail = new_sublist;
        }

        current = temp;
    }

    return result;
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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void free_sublists(Sublist *head) {
    Sublist *current = head;
    while (current != NULL) {
        Sublist *next = current->next;
        free(current->items);
        free(current);
        current = next;
    }
}

void print_sublists(Sublist *head) {
    Sublist *current = head;
    while (current != NULL) {
        printf("[");
        for (int i = 0; i < current->count; i++) {
            printf("%d", current->items[i]);
            if (i < current->count - 1) {
                printf(", ");
            }
        }
        printf("]");
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(1);
    head->next->next = create_node(2);
    head->next->next->next = create_node(3);
    head->next->next->next->next = create_node(3);
    head->next->next->next->next->next = create_node(3);
    head->next->next->next->next->next->next = create_node(4);
    head->next->next->next->next->next->next->next = create_node(5);
    head->next->next->next->next->next->next->next->next = create_node(5);

    Sublist *packed = pack_duplicates(head);

    print_sublists(packed);

    free_sublists(packed);
    free_list(head);

    return 0;
}