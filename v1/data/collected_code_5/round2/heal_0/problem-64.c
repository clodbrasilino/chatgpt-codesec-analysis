#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int x;
    int y;
} tuple;

int comparison(const void *a, const void *b)
{
    tuple *orderA = (tuple *)a;
    tuple *orderB = (tuple *)b;

    if (orderA->x > orderB->x)
        return 1;
    else if (orderA->x < orderB->x)
        return -1;
    else 
        return 0;
}

int main()
{
    tuple arr[] = {{2, 3}, {1, 7}, {8, 10}, {5, 6}, {7, 2}};
    int size = sizeof(arr) / sizeof(arr[0]);

    qsort((void *)arr, size, sizeof(arr[0]), comparison);

    for (int i = 0; i < size; i++)
        printf("(%d, %d) ", arr[i].x, arr[i].y);

    //Ensure successful termination of the program
    return 0;
}