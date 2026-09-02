#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

int sum_list(const List *list) {
    int sum = 0;
    const Node *current = list->head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

List *find_max_sum_list(List **lists, int num_lists) {
    if (lists == NULL || num_lists <= 0) {
        return NULL;
    }
    
    List *max_list = NULL;
    int max_sum = 0;
    int found = 0;
    
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            continue;
        }
        int current_sum = sum_list(lists[i]);
        if (!found || current_sum > max_sum) {
            max_sum = current_sum;
            max_list = lists[i];
            found = 1;
        }
    }
    
    return max_list;
}

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List *create_list(const int *arr, int size) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    
    if (size <= 0 || arr == NULL) {
        return list;
    }
    
    Node *current = NULL;
    for (int i = 0; i < size; i++) {
        Node *new_node = create_node(arr[i]);
        if (new_node == NULL) {
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
            list->head = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = new_node;
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
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {10, 20, 30};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {-5, -10, -15};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {100};
    
    List *list1 = create_list(arr1, 5);
    List *list2 = create_list(arr2, 3);
    List *list3 = create_list(arr3, 3);
    List *list4 = create_list(arr4, 1);
    
    if (list1 == NULL || list2 == NULL || list3 == NULL || list4 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        free_list(list4);
        return 1;
    }
    
    List *lists[] = {list1, list2, list3, list4};
    int num_lists = 4;
    
    List *max_list = find_max_sum_list(lists, num_lists);
    
    if (max_list != NULL) {
        printf("List with maximum sum: ");
        Node *current = max_list->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\nSum: %d\n", sum_list(max_list));
    }
    
    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_list(list4);
    
    return 0;
}