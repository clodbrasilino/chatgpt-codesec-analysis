#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

int count_lists(const List* lists, int num_lists) {
    if (lists == NULL || num_lists <= 0) {
        return 0;
    }
    return num_lists;
}

List* create_lists(int num_lists) {
    if (num_lists <= 0) {
        return NULL;
    }
    
    List* lists = malloc((size_t)num_lists * sizeof(List));
    if (lists == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < num_lists; i++) {
        lists[i].head = NULL;
    }
    
    return lists;
}

void destroy_lists(List* lists, int num_lists) {
    if (lists == NULL) {
        return;
    }
    
    for (int i = 0; i < num_lists; i++) {
        Node* current = lists[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(lists);
}

int add_node(List* list, int data) {
    if (list == NULL) {
        return 0;
    }
    
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }
    
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    
    return 1;
}

int main(void) {
    int num_lists = 5;
    List* lists = create_lists(num_lists);
    
    if (lists == NULL) {
        fprintf(stderr, "Failed to create lists\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < num_lists; i++) {
        if (!add_node(&lists[i], i * 10)) {
            fprintf(stderr, "Failed to add node to list %d\n", i);
            destroy_lists(lists, num_lists);
            return EXIT_FAILURE;
        }
    }
    
    int count = count_lists(lists, num_lists);
    printf("Number of lists: %d\n", count);
    
    destroy_lists(lists, num_lists);
    
    return EXIT_SUCCESS;
}