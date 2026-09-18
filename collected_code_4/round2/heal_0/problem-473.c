#include <stdio.h>
#include <string.h>

#define MAX 100

void intersection(char tuple1[MAX][MAX], char tuple2[MAX][MAX], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (strcmp(tuple1[i], tuple2[j]) == 0)
            {
                printf("Intersection is %s\n", tuple1[i]);
            }
        }
    }
}

int main()
{
    char tuple1[MAX][MAX] = {"apple", "banana", "mango", "grape"};
    char tuple2[MAX][MAX] = {"banana", "pineapple", "apple", "cherry"};
    int m = sizeof(tuple1) / sizeof(tuple1[0]);
    int n = sizeof(tuple2) / sizeof(tuple2[0]);

    intersection(tuple1, tuple2, m, n);

    return 0;
}