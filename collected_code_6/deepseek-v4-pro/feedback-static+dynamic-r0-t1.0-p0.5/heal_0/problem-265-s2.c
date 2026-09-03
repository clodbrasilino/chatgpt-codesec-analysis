#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    int size;
} List;

List *create_list(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void append_node(List *list, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

void free_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List **split_list(List *source, int n, int *num_sublists) {
    if (source == NULL || n <= 0 || num_sublists == NULL) {
        return NULL;
    }
    
    if (source->size == 0) {
        *num_sublists = 0;
        return NULL;
    }
    
    *num_sublists = (source->size + n - 1) / n;
    
    List **result = (List **)malloc(sizeof(List *) * (*num_sublists));
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < *num_sublists; i++) {
        result[i] = create_list();
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free_list(result[j]);
            }
            free(result);
            return NULL;
        }
    }
    
    Node *current = source->head;
    int sublist_index = 0;
    int count = 0;
    
    while (current != NULL) {
        append_node(result[sublist_index], current->data);
        count++;
        
        if (count == n) {
            sublist_index++;
            count = 0;
        }
        
        current = current->next;
    }
    
    return result;
}

void print_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List *source = create_list();
    if (source == NULL) {
        return 1;
    }
    
    for (int i = 1; i <= 10; i++) {
        append_node(source, i);
    }
    
    printf("Original list: ");
    print_list(source);
    
    int num_sublists = 0;
    List **sublists = split_list(source, 3, &num_sublists);
    
    if (sublists != NULL) {
        printf("Split into %d sublists:\n", num_sublists);
        for (int i = 0; i < num_sublists; i++) {
            printf("Sublist %d: ", i + 1);
            print_list(sublists[i]);
            free_list(sublists[i]);
        }
        free(sublists);
    }
    
    free_list(source);
    
    return 0;
}