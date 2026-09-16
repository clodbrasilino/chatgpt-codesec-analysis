#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

TupleList create_tuple_list(size_t capacity) {
    TupleList list;
    list.data = (Tuple *)malloc(capacity * sizeof(Tuple));
    list.size = 0;
    list.capacity = capacity;
    return list;
}

void append_tuple_list(TupleList *list, Tuple t) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        Tuple *new_data = (Tuple *)realloc(list->data, list->capacity * sizeof(Tuple));
        if (!new_data) {
            free(list->data);
            exit(EXIT_FAILURE);
        }
        list->data = new_data;
    }
    list->data[list->size++] = t;
}

void free_tuple_list(TupleList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

TupleList find_similar_tuples(const TupleList *list1, const TupleList *list2) {
    TupleList result = create_tuple_list(list1->size < list2->size ? list1->size : list2->size);
    
    for (size_t i = 0; i < list1->size; i++) {
        for (size_t j = 0; j < list2->size; j++) {
            if (list1->data[i].a == list2->data[j].a && list1->data[i].b == list2->data[j].b) {
                append_tuple_list(&result, list1->data[i]);
                break;
            }
        }
    }
    
    return result;
}

int main(void) {
    TupleList list1 = create_tuple_list(4);
    TupleList list2 = create_tuple_list(4);
    
    append_tuple_list(&list1, (Tuple){1, 2});
    append_tuple_list(&list1, (Tuple){3, 4});
    append_tuple_list(&list1, (Tuple){5, 6});
    append_tuple_list(&list1, (Tuple){7, 8});
    
    append_tuple_list(&list2, (Tuple){3, 4});
    append_tuple_list(&list2, (Tuple){5, 6});
    append_tuple_list(&list2, (Tuple){9, 10});
    append_tuple_list(&list2, (Tuple){11, 12});
    
    TupleList similar = find_similar_tuples(&list1, &list2);
    
    for (size_t i = 0; i < similar.size; i++) {
        printf("(%d, %d)\n", similar.data[i].a, similar.data[i].b);
    }
    
    free_tuple_list(&list1);
    free_tuple_list(&list2);
    free_tuple_list(&similar);
    
    return 0;
}