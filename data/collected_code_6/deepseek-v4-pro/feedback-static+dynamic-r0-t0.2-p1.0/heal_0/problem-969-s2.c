#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int key;
    char value[64];
    struct Tuple *next;
} Tuple;

typedef struct TupleList {
    Tuple *head;
    int size;
} TupleList;

TupleList *create_tuple_list(void) {
    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int add_tuple(TupleList *list, int key, const char *value) {
    if (list == NULL || value == NULL) {
        return -1;
    }
    Tuple *new_tuple = (Tuple *)malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return -1;
    }
    new_tuple->key = key;
    strncpy(new_tuple->value, value, sizeof(new_tuple->value) - 1);
    new_tuple->value[sizeof(new_tuple->value) - 1] = '\0';
    new_tuple->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_tuple;
    } else {
        Tuple *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_tuple;
    }
    list->size++;
    return 0;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    Tuple *current = list->head;
    while (current != NULL) {
        Tuple *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

TupleList *join_tuples(TupleList *list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    
    TupleList *result = create_tuple_list();
    if (result == NULL) {
        return NULL;
    }
    
    Tuple *current = list->head;
    while (current != NULL) {
        Tuple *next = current->next;
        int found = 0;
        
        Tuple *result_current = result->head;
        while (result_current != NULL) {
            if (result_current->key == current->key) {
                size_t current_len = strlen(result_current->value);
                size_t add_len = strlen(current->value);
                if (current_len + add_len + 2 < sizeof(result_current->value)) {
                    strcat(result_current->value, ",");
                    strcat(result_current->value, current->value);
                }
                found = 1;
                break;
            }
            result_current = result_current->next;
        }
        
        if (!found) {
            if (add_tuple(result, current->key, current->value) != 0) {
                free_tuple_list(result);
                return NULL;
            }
        }
        
        current = next;
    }
    
    return result;
}

void print_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    Tuple *current = list->head;
    while (current != NULL) {
        printf("(%d, %s) ", current->key, current->value);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    TupleList *list = create_tuple_list();
    if (list == NULL) {
        return 1;
    }
    
    add_tuple(list, 1, "a");
    add_tuple(list, 2, "b");
    add_tuple(list, 1, "c");
    add_tuple(list, 3, "d");
    add_tuple(list, 2, "e");
    add_tuple(list, 1, "f");
    
    printf("Original tuples: ");
    print_tuple_list(list);
    
    TupleList *joined = join_tuples(list);
    if (joined != NULL) {
        printf("Joined tuples: ");
        print_tuple_list(joined);
        free_tuple_list(joined);
    }
    
    free_tuple_list(list);
    return 0;
}