#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

void free_list(List* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void remove_empty_lists(List** lists, int* size) {
    if (lists == NULL || *lists == NULL || size == NULL || *size <= 0) {
        return;
    }
    
    int new_size = 0;
    List** temp = (List**)malloc((*size) * sizeof(List*));
    if (temp == NULL) {
        return;
    }
    
    for (int i = 0; i < *size; i++) {
        if ((*lists)[i].head != NULL) {
            temp[new_size++] = &(*lists)[i];
        } else {
            free_list(&(*lists)[i]);
        }
    }
    
    if (new_size == 0) {
        free(*lists);
        *lists = NULL;
        *size = 0;
        free(temp);
        return;
    }
    
    List* new_lists = (List*)malloc(new_size * sizeof(List));
    if (new_lists == NULL) {
        free(temp);
        return;
    }
    
    for (int i = 0; i < new_size; i++) {
        new_lists[i] = *temp[i];
    }
    
    free(temp);
    free(*lists);
    *lists = new_lists;
    *size = new_size;
}

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

List* create_list_with_nodes(const int* values, int count) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    
    if (count == 0 || values == NULL) {
        return list;
    }
    
    Node* current = NULL;
    for (int i = 0; i < count; i++) {
        Node* node = create_node(values[i]);
        if (node == NULL) {
            free_list(list);
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

int main() {
    const int values1[] = {1, 2, 3};
    const int values2[] = {4, 5};
    
    List* lists = (List*)malloc(4 * sizeof(List));
    if (lists == NULL) {
        return 1;
    }
    
    List* temp_list0 = create_list_with_nodes(values1, 3);
    List* temp_list1 = create_list_with_nodes(NULL, 0);
    List* temp_list2 = create_list_with_nodes(values2, 2);
    List* temp_list3 = create_list_with_nodes(NULL, 0);
    
    if (temp_list0 == NULL || temp_list1 == NULL || temp_list2 == NULL || temp_list3 == NULL) {
        if (temp_list0 != NULL) free_list(temp_list0);
        if (temp_list1 != NULL) free_list(temp_list1);
        if (temp_list2 != NULL) free_list(temp_list2);
        if (temp_list3 != NULL) free_list(temp_list3);
        free(lists);
        return 1;
    }
    
    lists[0] = *temp_list0;
    lists[1] = *temp_list1;
    lists[2] = *temp_list2;
    lists[3] = *temp_list3;
    
    free(temp_list0);
    free(temp_list1);
    free(temp_list2);
    free(temp_list3);
    
    int size = 4;
    
    printf("Before removal: %d lists\n", size);
    for (int i = 0; i < size; i++) {
        printf("List %d: %s\n", i, lists[i].head != NULL ? "non-empty" : "empty");
    }
    
    remove_empty_lists(&lists, &size);
    
    printf("After removal: %d lists\n", size);
    if (lists != NULL) {
        for (int i = 0; i < size; i++) {
            printf("List %d: ", i);
            Node* current = lists[i].head;
            while (current != NULL) {
                printf("%d ", current->data);
                current = current->next;
            }
            printf("\n");
        }
        
        for (int i = 0; i < size; i++) {
            free_list(&lists[i]);
        }
        free(lists);
    }
    
    return 0;
}