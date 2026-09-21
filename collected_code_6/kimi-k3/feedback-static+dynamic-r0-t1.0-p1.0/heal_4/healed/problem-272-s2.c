#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 32

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    double value;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} TupleList;

void list_init(TupleList *list) {
    if (list == NULL) {
        return;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int list_append(TupleList *list, const Tuple *tuple) {
    Node *new_node;
    
    if (list == NULL || tuple == NULL) {
        return -1;
    }
    
    new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    
    new_node->data = *tuple;
    new_node->next = NULL;
    
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    
    return 0;
}

int list_extract_rear(TupleList *list, Tuple *out_tuple) {
    Node *current;
    Node *prev;
    
    if (list == NULL || out_tuple == NULL) {
        return -1;
    }
    
    if (list->tail == NULL) {
        return -1;
    }
    
    *out_tuple = list->tail->data;
    
    if (list->head == list->tail) {
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
    } else {
        current = list->head;
        prev = NULL;
        
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        
        if (prev != NULL) {
            free(current);
            prev->next = NULL;
            list->tail = prev;
        }
    }
    list->size--;
    
    return 0;
}

void list_destroy(TupleList *list) {
    Node *current;
    Node *next;
    
    if (list == NULL) {
        return;
    }
    
    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int tuple_init(Tuple *tuple, int id, const char *name, double value) {
    size_t name_len;
    
    if (tuple == NULL || name == NULL) {
        return -1;
    }
    
    name_len = strnlen(name, MAX_NAME_LEN);
    if (name_len >= MAX_NAME_LEN) {
        return -1;
    }
    
    tuple->id = id;
    strncpy(tuple->name, name, MAX_NAME_LEN - 1);
    tuple->name[MAX_NAME_LEN - 1] = '\0';
    tuple->value = value;
    
    return 0;
}

int main(void) {
    TupleList list;
    Tuple t1, t2, t3;
    Tuple extracted;
    int status;
    
    list_init(&list);
    
    if (tuple_init(&t1, 1, "record_one", 10.5) != 0) {
        fprintf(stderr, "Failed to initialize t1\n");
        return EXIT_FAILURE;
    }
    
    if (tuple_init(&t2, 2, "record_two", 20.75) != 0) {
        fprintf(stderr, "Failed to initialize t2\n");
        return EXIT_FAILURE;
    }
    
    if (tuple_init(&t3, 3, "record_three", 30.25) != 0) {
        fprintf(stderr, "Failed to initialize t3\n");
        return EXIT_FAILURE;
    }
    
    if (list_append(&list, &t1) != 0) {
        fprintf(stderr, "Failed to append t1\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }
    
    if (list_append(&list, &t2) != 0) {
        fprintf(stderr, "Failed to append t2\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }
    
    if (list_append(&list, &t3) != 0) {
        fprintf(stderr, "Failed to append t3\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }
    
    printf("List size before extraction: %zu\n", list.size);
    
    status = list_extract_rear(&list, &extracted);
    if (status == 0) {
        printf("Extracted: id=%d, name=%s, value=%.2f\n", 
               extracted.id, extracted.name, extracted.value);
        printf("List size after extraction: %zu\n", list.size);
    } else {
        fprintf(stderr, "Failed to extract rear element\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }
    
    status = list_extract_rear(&list, &extracted);
    if (status == 0) {
        printf("Extracted: id=%d, name=%s, value=%.2f\n", 
               extracted.id, extracted.name, extracted.value);
        printf("List size after extraction: %zu\n", list.size);
    } else {
        fprintf(stderr, "Failed to extract rear element\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }
    
    list_destroy(&list);
    
    return EXIT_SUCCESS;
}