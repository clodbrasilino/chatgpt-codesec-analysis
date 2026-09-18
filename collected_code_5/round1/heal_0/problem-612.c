#include<stdio.h>
#include<stdlib.h>

#define SIZE 5

int **mergeLists(int **lists, int *sizes, int listCount)
{
    int i, j, front, back, **mergedLists;

    if((lists == NULL) || (sizes == NULL) || (listCount <= 0))
    {
        return NULL;
    }

    mergedLists = (int **) malloc(listCount * sizeof(int *));
    if (!mergedLists)
    {
        return NULL;
    }

    for(i = 0; i < listCount; i++)
    {
        if(sizes[i] <= 0)
        {
            mergedLists[i] = NULL;
            continue;
        }
        
        mergedLists[i] = (int *) malloc(2 * sizeof(int));
        if(!mergedLists[i])
        {
            for(j = 0; j < i; j++)
            {
                free(mergedLists[j]);
            }
            free(mergedLists);
            return NULL;
        }
        
        front = lists[i][0];
        back = lists[i][sizes[i]-1];

        mergedLists[i][0] = front;
        mergedLists[i][1] = back;
    }
    
    return mergedLists;
}

int main()
{
    int i, j, **lists, sizes[SIZE] = {5, 4, 3, 2, 1}, **mergedLists;
    lists = (int **) malloc(SIZE * sizeof(int *));

    for(i = 0; i < SIZE; i++)
    {
        lists[i] = (int *) malloc(sizes[i] * sizeof(int));
        for(j = 0; j < sizes[i]; j++)
        {
            lists[i][j] = j+1;
        }
    }

    mergedLists = mergeLists(lists, sizes, SIZE);

    if(mergedLists != NULL)
    {
        for(i = 0; i < SIZE; i++)
        {
            if(mergedLists[i] != NULL)
            {
                printf("{%d, %d}\n", mergedLists[i][0], mergedLists[i][1]);
            }
            else
            {
                printf("NULL\n");
            }
        }
    }

    for(i = 0; i < SIZE; i++)
    {
        free(lists[i]);
        free(mergedLists[i]);
    }
    
    free(lists);
    free(mergedLists);

    return 0;
}