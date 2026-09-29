#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} tuple;

typedef struct {
    tuple *data;
    int count;
    int size;
} tuple_list;

void init_list(tuple_list *list, int initial_size) {
    list->data = (tuple *)malloc(sizeof(tuple) * initial_size);
    list->count = 0;
    list->size = initial_size;
}

void append_to_list(tuple_list *list, tuple t) {
    if (list->count >= list->size) {
        list->size *= 2;
        list->data = (tuple *)realloc(list->data, sizeof(tuple) * list->size);
    }
    list->data[list->count++] = t;
}

tuple extract_rear(tuple_list *list) {
    if(list->count == 0){
        printf("List is empty, no elements to extract\n");
        exit(0);
    }
    tuple t = list->data[list->count-1];
    list->count--;
    return t;
}

void free_list(tuple_list *list) {
    free(list->data);
    list->count = 0;
    list->size = 0;
}

int main(void) {
    tuple_list list;
    init_list(&list, 10);

    tuple t1;
    t1.first = 1;
    t1.second = 2;
    append_to_list(&list, t1);

    tuple t2;
    t2.first = 3;
    t2.second = 4;
    append_to_list(&list, t2);

    tuple last = extract_rear(&list);
    printf("Extracted tuple: (%d, %d)\n", last.first, last.second);

    free_list(&list);
    return 0;
}