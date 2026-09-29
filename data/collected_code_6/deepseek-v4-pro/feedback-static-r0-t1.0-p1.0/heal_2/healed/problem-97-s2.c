#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** lists;
    int size;
    int* counts;
} ListContainer;

int contains(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int* frequency_count(ListContainer* container) {
    if (container == NULL || container->lists == NULL || container->counts == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < container->size; i++) {
        if (container->lists[i] == NULL) {
            container->counts[i] = 0;
            continue;
        }
        
        Node* current = container->lists[i];
        int count = 0;
        
        while (current != NULL) {
            count++;
            current = current->next;
        }
        
        container->counts[i] = count;
    }
    
    return container->counts;
}

Node* create_list(const int* arr, int size) {
    if (size <= 0 || arr == NULL) {
        return NULL;
    }
    
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        return NULL;
    }
    
    head->value = arr[0];
    head->next = NULL;
    Node* current = head;
    
    for (int i = 1; i < size; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }
        new_node->value = arr[i];
        new_node->next = NULL;
        current->next = new_node;
        current = new_node;
    }
    
    return head;
}

ListContainer* create_container(int num_lists) {
    if (num_lists <= 0) {
        return NULL;
    }
    
    ListContainer* container = (ListContainer*)malloc(sizeof(ListContainer));
    if (container == NULL) {
        return NULL;
    }
    
    container->lists = (Node**)calloc(num_lists, sizeof(Node*));
    if (container->lists == NULL) {
        free(container);
        return NULL;
    }
    
    container->counts = (int*)calloc(num_lists, sizeof(int));
    if (container->counts == NULL) {
        free(container->lists);
        free(container);
        return NULL;
    }
    
    container->size = num_lists;
    return container;
}

void free_container(ListContainer* container) {
    if (container == NULL) {
        return;
    }
    
    if (container->lists != NULL) {
        for (int i = 0; i < container->size; i++) {
            if (container->lists[i] != NULL) {
                free_list(container->lists[i]);
            }
        }
        free(container->lists);
    }
    
    if (container->counts != NULL) {
        free(container->counts);
    }
    
    free(container);
}

int main(void) {
    const int list1_data[] = {1, 2, 3, 4, 5};
    const int list2_data[] = {10, 20};
    const int list3_data[] = {7, 8, 9, 10, 11, 12};
    const int list4_data[] = {42};
    
    ListContainer* container = create_container(4);
    if (container == NULL) {
        fprintf(stderr, "Failed to create container\n");
        return 1;
    }
    
    container->lists[0] = create_list(list1_data, 5);
    container->lists[1] = create_list(list2_data, 2);
    container->lists[2] = create_list(list3_data, 6);
    container->lists[3] = create_list(list4_data, 1);
    
    if (container->lists[0] == NULL || container->lists[1] == NULL ||
        container->lists[2] == NULL || container->lists[3] == NULL) {
        fprintf(stderr, "Failed to create lists\n");
        free_container(container);
        return 1;
    }
    
    const int* frequencies = frequency_count(container);
    if (frequencies == NULL) {
        fprintf(stderr, "Failed to compute frequencies\n");
        free_container(container);
        return 1;
    }
    
    printf("Frequency counts:\n");
    for (int i = 0; i < container->size; i++) {
        printf("List %d: %d\n", i + 1, frequencies[i]);
    }
    
    free_container(container);
    return 0;
}