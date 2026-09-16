#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

typedef struct {
    int *elements;
    int size;
} Tuple;

LinkedList *create_list(void) {
    LinkedList *list = malloc(sizeof(*list));
    if (!list) return NULL;
    list->head = NULL;
    return list;
}

void free_list(LinkedList *list) {
    if (!list) return;
    Node *cur = list->head;
    while (cur) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(list);
}

int list_append(LinkedList *list, int value) {
    if (!list) return -1;
    Node *new_node = malloc(sizeof(*new_node));
    if (!new_node) return -1;
    new_node->data = value;
    new_node->next = NULL;
    if (!list->head) {
        list->head = new_node;
    } else {
        Node *cur = list->head;
        while (cur->next) cur = cur->next;
        cur->next = new_node;
    }
    return 0;
}

Tuple *create_tuple(int size) {
    Tuple *tuple = malloc(sizeof(*tuple));
    if (!tuple) return NULL;
    tuple->elements = malloc(sizeof(int) * (size > 0 ? size : 1));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) return;
    free(tuple->elements);
    free(tuple);
}

Tuple *add_list_to_tuples(LinkedList *list, Tuple *tuples[], int tuple_count) {
    if (!list || !tuples || tuple_count <= 0) return NULL;
    
    int list_size = 0;
    Node *cur = list->head;
    while (cur) {
        list_size++;
        cur = cur->next;
    }
    
    Tuple *result = create_tuple(list_size);
    if (!result) return NULL;
    
    cur = list->head;
    for (int i = 0; i < list_size && cur; i++) {
        int sum = cur->data;
        for (int j = 0; j < tuple_count; j++) {
            if (tuples[j] && i < tuples[j]->size) {
                sum += tuples[j]->elements[i];
            }
        }
        result->elements[i] = sum;
        cur = cur->next;
    }
    
    return result;
}

int main(void) {
    LinkedList *list = create_list();
    if (!list) return 1;
    
    list_append(list, 1);
    list_append(list, 2);
    list_append(list, 3);
    list_append(list, 4);
    
    Tuple *t1 = create_tuple(4);
    Tuple *t2 = create_tuple(3);
    if (!t1 || !t2) {
        free_list(list);
        free_tuple(t1);
        free_tuple(t2);
        return 1;
    }
    
    for (int i = 0; i < 4; i++) t1->elements[i] = i + 10;
    for (int i = 0; i < 3; i++) t2->elements[i] = i + 100;
    
    Tuple *tuples[] = {t1, t2};
    Tuple *result = add_list_to_tuples(list, tuples, 2);
    
    if (result) {
        for (int i = 0; i < result->size; i++) {
            printf("%d ", result->elements[i]);
        }
        printf("\n");
        free_tuple(result);
    }
    
    free_tuple(t1);
    free_tuple(t2);
    free_list(list);
    
    return 0;
}