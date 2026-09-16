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

int contains(Node *list, int value) {
    Node *current = list;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node *divide_lists(Node *list1, Node *list2) {
    if (list1 == NULL) {
        return NULL;
    }
    Node *result = NULL;
    Node *tail = NULL;
    Node *current = list1;
    while (current != NULL) {
        if (!contains(list2, current->data)) {
            Node *new_node = create_node(current->data);
            if (new_node == NULL) {
                Node *temp = result;
                while (temp != NULL) {
                    Node *next = temp->next;
                    free(temp);
                    temp = next;
                }
                return NULL;
            }
            if (result == NULL) {
                result = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
        current = current->next;
    }
    return result;
}

Node *append(Node *list, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return list;
    }
    if (list == NULL) {
        return new_node;
    }
    Node *current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return list;
}

void free_list(Node *list) {
    Node *current = list;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(Node *list) {
    Node *current = list;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *result = NULL;

    list1 = append(list1, 1);
    list1 = append(list1, 2);
    list1 = append(list1, 3);
    list1 = append(list1, 4);
    list1 = append(list1, 5);

    list2 = append(list2, 2);
    list2 = append(list2, 4);
    list2 = append(list2, 6);

    result = divide_lists(list1, list2);
    if (result == NULL) {
        fprintf(stderr, "Division failed\n");
    } else {
        print_list(result);
    }

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}