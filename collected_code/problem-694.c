#include <stdio.h>

void extractUniqueValues(int *dictionary, int dictLength, int *uniqueValues, int *uniqueCount)
{
    int i, j, count;
    *uniqueCount = 0;

    for (i = 0; i < dictLength; i++)
    {
        count = 0;
        for (j = i + 1; j < dictLength; j++)
        {
            if (dictionary[i] == dictionary[j])
            {
                count++;
                break;
            }
        }

        if (count == 0)
        {
            uniqueValues[*uniqueCount] = dictionary[i];
            (*uniqueCount)++;
        }
    }
}

int main()
{
    int dictionary[] = {1, 2, 3, 2, 4, 5, 1, 6, 3};
    int dictLength = sizeof(dictionary) / sizeof(int);
    int uniqueValues[dictLength];
    int uniqueCount;

    extractUniqueValues(dictionary, dictLength, uniqueValues, &uniqueCount);

    printf("Unique Values: ");
    for (int i = 0; i < uniqueCount; i++)
    {
        printf("%d ", uniqueValues[i]);
    }

    return 0;
}