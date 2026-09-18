#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

typedef struct {
    Tuple *items;
    int size;
} TupleList;

Tuple create_tuple(int *data, int size){
    Tuple tuple;
    tuple.data = (int *) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuple.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple.data[i] = data[i];
    }
    tuple.size = size;
    return tuple;
}

void remove_empty_tuples(TupleList *list){
    for(int i = 0; i < list->size; i++){
        if(list->items[i].size == 0){
            free(list->items[i].data);
            for(int j = i; j < list->size - 1; j++){
                list->items[j] = list->items[j+1];
            }
            list->size--;
            i--;
        }
    }
}

void free_tuple_list(TupleList *list){
    for(int i = 0; i < list->size; i++){
        /* Possible weaknesses found:
         *  read of 8 bytes from after the end of the region
         *  use of uninitialized value '*_1 + _3.data' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         */
        free(list->items[i].data);
    }
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    free(list->items);
}

int main(){
    TupleList list;
    list.size = 3;
    list.items = (Tuple *)malloc(sizeof(Tuple)* list.size);

    int data1[] = {1, 2, 3};
    int data2[] = {};
    int data3[] = {4, 5, 6};

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list.items' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list.items[0] = create_tuple(data1, sizeof(data1)/sizeof(int));
    list.items[1] = create_tuple(data2, sizeof(data2)/sizeof(int));
    list.items[2] = create_tuple(data3, sizeof(data3)/sizeof(int));

    remove_empty_tuples(&list);

    for(int i = 0; i < list.size; i++){
        for(int j = 0; j < list.items[i].size; j++){
            printf("%d ", list.items[i].data[j]);
        }
        printf("\n");
    }

    free_tuple_list(&list);

    return 0;
}