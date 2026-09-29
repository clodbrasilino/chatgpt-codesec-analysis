#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *elements; 
    int size;
} Tuple;

Tuple* create_tuple(int n)
{
    Tuple* new_tuple = (Tuple*) malloc(sizeof(Tuple));
    if(new_tuple == NULL) return NULL;

    new_tuple->elements = (int*) malloc(n * sizeof(int));
    if(new_tuple->elements == NULL)
    {
        free(new_tuple);
        return NULL;
    }
    new_tuple->size = n;

    return new_tuple;
}

void destroy_tuple(Tuple *tuple)
{
    if(tuple){
        if(tuple->elements){
            free(tuple->elements);
        }
        free(tuple);
    }
}

void chunk_tuples(Tuple* tuples, int tuple_size, int chunk_size)
{
    int i = 0, j = 0, chunk_counter = 0;

    for(i = 0; i < tuple_size; i++) {
        printf("%d ", tuples->elements[i]);
        chunk_counter++;

        if(chunk_counter == chunk_size) {
            printf("\n");
            chunk_counter = 0;
        }
    }

    if(chunk_counter != 0) {
        printf("\n");
    }
}

int main()
{
    int n = 10;
    Tuple *tuple = create_tuple(n);

    
    if(tuple == NULL)
    {
        printf("Failed to allocate memory for tuple!\n");
        return 1;
    }

    for(int i = 0; i < n; i++) {
        tuple->elements[i] = i + 1;
    }

    chunk_tuples(tuple, n, 3);

    destroy_tuple(tuple);
    return 0;
}