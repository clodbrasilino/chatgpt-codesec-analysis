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
    if(tuple.data)
    {
        for (int i = 0; i < size; i++) {
            tuple.data[i] = data[i];
        }
    }
    tuple.size = size;
    return tuple;
}

void remove_empty_tuples(TupleList *list){
    for(int i = 0; i < list->size; i++)
    {
        if((list->items[i]).size == 0)
        {
            free((list->items[i]).data);
            for(int j = i; j < list->size - 1; j++)
            {
                (list->items[j]) = (list->items[j+1]);
            }
            list->size--;
            i--;
        }
    }
}

void free_tuple_list(TupleList *list){
    for(int i = 0; i < list->size; i++)
    {
        free(list->items[i].data);
    }
    free(list->items);
    list->items = NULL;
    list->size = 0;
}

int main(){

    TupleList list;

    list.size = 3;
    list.items = (Tuple *)malloc(sizeof(Tuple)* list.size);

    if(list.items)
    {
        int data1[] = {1, 2, 3};
        int data2[] = {};
        int data3[] = {4, 5, 6};

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
    }

    free_tuple_list(&list);

    return 0;
}