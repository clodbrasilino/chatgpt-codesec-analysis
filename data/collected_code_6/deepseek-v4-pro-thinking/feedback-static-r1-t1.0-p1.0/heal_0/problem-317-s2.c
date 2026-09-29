#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct RleNode {
    size_t count;
    int data;
    struct RleNode *next;
} RleNode;

RleNode *modified_run_length_encode(const Node *list) {
    RleNode *head = NULL;
    RleNode **tail = &head;

    while (list != NULL) {
        int data = list->data;
        size_t count = 1;
        list = list->next;

        while (list != NULL && list->data == data) {
            count++;
            list = list->next;
        }

        RleNode *node = malloc(sizeof(*node));
        if (node == NULL) {
            while (head != NULL) {
                RleNode *next = head->next;
                free(head);
                head = next;
            }
            return NULL;
        }

        node->count = count;
        node->data = data;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return head;
}

void print_list(const Node *list) {
    while (list != NULL) {
        printf("%d", list->data);
        if (list->next != NULL) {
            printf(" ");
        }
        list = list->next;
    }
    printf("\n");
}

void print_rle(const RleNode *list) {
    while (list != NULL) {
        if (list->count == 1) {
            printf("%d", list->data);
        } else {
            printf("[%zu,%d]", list->count, list->data);
        }
        if (list->next != NULL) {
            printf(" ");
        }
        list = list->next;
    }
    printf("\n");
}

void free_list(Node *list) {
    while (list != NULL) {
        Node *next = list->next;
        free(list);
        list = next;
    }
}

void free_rle(RleNode *list) {
    while (list != NULL) {
        RleNode *next = list->next;
        free(list);
        list = next;
    }
}

Node *make_node(int data, Node *next) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = next;
    return node;
}

int main(void) {
    Node *list = NULL;
    Node *tail = NULL;
    const int values[] = {1, 1, 2, 3, 3, 3, 4};
    size_t i;

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        Node *node = make_node(values[i], NULL);
        if (node == NULL) {
            free_list(list);
            return 1;
        }
        if (tail == NULL) {
            list = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    RleNode *encoded = modified_run_length_encode(list);
    if (encoded == NULL) {
        free_list(list);
        return 1;
    }

    print_list(list);
    print_rle(encoded);

    free_rle(encoded);
    free_list(list);

    return 0;
}