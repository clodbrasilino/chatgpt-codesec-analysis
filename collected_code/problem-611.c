#include <stdio.h>

// Define the structure of each tuple
typedef struct 
{
    int col1;
    int col2;
    // ... repeat for each column
    int colN;
} Tuple;

// Function to find the maximum of nth column
int findMaxOfNthColumn(Tuple list[], int numOfTuples, int n)
{
    int max = list[0].colN; // Assume the first tuple has the maximum value of the nth column
    
    // Iterate through the remaining tuples
    for (int i = 1; i < numOfTuples; i++)
    {
        if (list[i].colN > max)
        {
            max = list[i].colN;
        }
    }
    
    return max;
}

int main()
{
    // Example usage
    Tuple list[] = {
        {1, 5, 9},
        {2, 8, 6},
        {3, 7, 4},
        {4, 6, 8},
        {5, 4, 2},
        {6, 3, 7}
    };
    
    int numOfTuples = sizeof(list) / sizeof(list[0]);
    int n = 2; // Find the maximum of the 2nd column
    
    int maxOfNthColumn = findMaxOfNthColumn(list, numOfTuples, n);
    printf("Maximum value of column %d: %d\n", n, maxOfNthColumn);
    
    return 0;
}