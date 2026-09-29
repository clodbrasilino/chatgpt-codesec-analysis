#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int x;
    int y;
} Tuple;

void clearTupleValues(Tuple* tuple) 
{
    if (tuple == NULL) 
    {
        fprintf(stderr, "Pointer to Tuple is NULL.\n");
        return;
    }
    tuple->x = 0;
    tuple->y = 0;
}

int main()
{
    Tuple* tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for Tuple.\n");
        return 1;
    }

    tuple->x = 5;
    tuple->y = 10;

    clearTupleValues(tuple);

    printf("Tuple values: x = %d, y = %d\n", tuple->x, tuple->y);

    free(tuple);
    return 0;
}