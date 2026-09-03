#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} ListOfLists;

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->size = size;
    node->next = NULL;
    return node;
}

ListOfLists *create_list_of_lists(void) {
    ListOfLists *list = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    return list;
}

int append_list(ListOfLists *list, int *data, int size) {
    if (list == NULL || data == NULL || size <= 0) {
        return -1;
    }
    Node *node = create_node(data, size);
    if (node == NULL) {
        return -1;
    }
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
    return 0;
}

int sum_column(ListOfLists *list, int column_index) {
    if (list == NULL || list->head == NULL || column_index < 0) {
        return 0;
    }
    int sum = 0;
    Node *current = list->head;
    while (current != NULL) {
        if (column_index < current->size) {
            sum += current->data[column_index];
        }
        current = current->next;
    }
    return sum;
}

void free_list_of_lists(ListOfLists *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int main(void) {
    int *data1 = (int *)malloc(3 * sizeof(int));
    int *data2 = (int *)malloc(3 * sizeof(int));
    int *data3 = (int *)malloc(4 * sizeof(int));
    
    if (data1 == NULL || data2 == NULL || data3 == NULL) {
        free(data1);
        free(data2);
        free(data3);
        return 1;
    }
    
    data1[0] = 1;
    data1[1] = 2;
    data1[2] = 3;
    
    data2[0] = 4;
    data2[1] = 5;
    data2[2] = 6;
    
    data3[0] = 7;
    data3[1] = 8;
    data3[2] = 9;
    data3[3] = 10;

    ListOfLists *list = create_list_of_lists();
    if (list == NULL) {
        free(data1);
        free(data2);
        free(data3);
        return 1;
    }

    if (append_list(list, data1, 3) != 0) {
        free(data1);
        free(data2);
        free(data3);
        free_list_of_lists(list);
        return 1;
    }
    if (append_list(list, data2, 3) != 0) {
        free(data1);
        free(data2);
        free(data3);
        free_list_of_lists(list);
        return 1;
    }
    if (append_list(list, data3, 4) != 0) {
        free(data1);
        free(data2);
        free(data3);
        free_list_of_lists(list);
        return 1;
    }

    int result = sum_column(list, 1);
    printf("%d\n", result);

    free_list_of_lists(list);
    return 0;
}