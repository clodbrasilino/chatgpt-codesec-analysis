#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

int list_sum(List *list) {
    int sum = 0;
    Node *current = list->head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

List *find_max_sum_list(List **lists, int count) {
    if (lists == NULL || count <= 0) {
        return NULL;
    }

    List *max_list = lists[0];
    int max_sum = list_sum(max_list);

    for (int i = 1; i < count; i++) {
        int current_sum = list_sum(lists[i]);
        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_list = lists[i];
        }
    }

    return max_list;
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

List *create_list(const int *values, int count) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;

    if (count <= 0) {
        return list;
    }

    Node *current = NULL;
    for (int i = 0; i < count; i++) {
        Node *node = create_node(values[i]);
        if (node == NULL) {
            Node *temp = list->head;
            while (temp != NULL) {
                Node *next = temp->next;
                free(temp);
                temp = next;
            }
            free(list);
            return NULL;
        }
        if (list->head == NULL) {
            list->head = node;
            current = node;
        } else {
            current->next = node;
            current = node;
        }
    }

    return list;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main(void) {
    int values1[] = {1, 2, 3};
    int values2[] = {10, 20};
    int values3[] = {5, 6, 7, 8};

    List *list1 = create_list(values1, 3);
    List *list2 = create_list(values2, 2);
    List *list3 = create_list(values3, 4);

    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        return 1;
    }

    List *lists[] = {list1, list2, list3};
    List *max_list = find_max_sum_list(lists, 3);

    if (max_list != NULL) {
        printf("List with highest sum: ");
        Node *current = max_list->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}