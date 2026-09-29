#include <stdio.h>
#include <stdlib.h>

struct Tuple
{
    int first;
    int second;
};

void groupTupleBySecond(struct Tuple *tupleList, int size)
{
    // Create an array to store the count of different second values
    int maxSecond = 0;
    for (int i = 0; i < size; i++)
    {
        if (tupleList[i].second > maxSecond)
        {
            maxSecond = tupleList[i].second;
        }
    }
    int *count = (int *)calloc(maxSecond + 1, sizeof(int));

    // Count the occurrence of each second value
    for (int i = 0; i < size; i++)
    {
        count[tupleList[i].second]++;
    }
    
    // Create an array of arrays to store the grouped tuples
    struct Tuple **groupedTuples = (struct Tuple **)calloc(maxSecond + 1, sizeof(struct Tuple *));

    // Allocate memory for each inner array based on the count of second values
    for (int i = 0; i <= maxSecond; i++)
    {
        groupedTuples[i] = (struct Tuple *)calloc(count[i], sizeof(struct Tuple));
    }

    // Copy tuples to their corresponding groups
    for (int i = 0; i < size; i++)
    {
        struct Tuple tuple = tupleList[i];
        groupedTuples[tuple.second][--count[tuple.second]] = tuple;
    }

    // Print the grouped tuples
    for (int i = 0; i <= maxSecond; i++)
    {
        printf("Group %d: ", i);
        for (int j = 0; j < count[i]; j++)
        {
            printf("(%d, %d) ", groupedTuples[i][j].first, groupedTuples[i][j].second);
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i <= maxSecond; i++)
    {
        free(groupedTuples[i]);
    }
    free(groupedTuples);
    free(count);
}

int main()
{
    struct Tuple tupleList[] = {{1, 2}, {2, 1}, {3, 2}, {4, 1}, {5, 3}};
    int size = sizeof(tupleList) / sizeof(tupleList[0]);

    groupTupleBySecond(tupleList, size);
    
    return 0;
}