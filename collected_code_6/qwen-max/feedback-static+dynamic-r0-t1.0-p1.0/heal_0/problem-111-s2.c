#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

void add_element(List *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

List *find_common_elements(List *list1, List *list2) {
    List *common = (List *)malloc(sizeof(List));
    common->head = NULL;

    Node *p1 = list1->head;
    while (p1 != NULL) {
        Node *p2 = list2->head;
        while (p2 != NULL) {
            if (p1->value == p2->value) {
                add_element(common, p1->value);
                break;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return common;
}

void print_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void free_list(List *list) {
    Node *current = list->head;
    Node *tmp;
    while (current != NULL) {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    free(list);
}

int main() {
    List list1 = {NULL};
    List list2 = {NULL};

    add_element(&list1, 1);
    add_element(&list1, 2);
    add_element(&list1, 3);
    add_element(&list1, 4);

    add_element(&list2, 3);
    add_element(&list2, 4);
    add_element(&list2, 5);
    add_element(&list2, 6);

    List *common = find_common_elements(&list1, &list2);
    print_list(common);

    free_list(&list1);
    free_list(&list2);
    free_list(common);

    return 0;
}